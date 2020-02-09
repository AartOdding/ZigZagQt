#pragma once

#include <QMutex>
#include <QObject>

#include <vector>
#include <memory>
#include <mutex>
#include <functional>

#include "model/parameter/IntParameter.hpp"
#include "model/parameter/FloatParameter.hpp"
#include "model/parameter/EnumParameter.hpp"
#include "model/parameter/ButtonParameter.hpp"
#include "model/parameter/ColorParameter.hpp"
#include "model/parameter/Transform2DParameter.hpp"


struct DataTypeDescription;
struct DataViewTypeInfo;
class BaseOperator;
class BaseDataType;
class DataInput;


struct OperatorDescription
{
    OperatorDescription() = delete;

    OperatorDescription(const QString& name,
                        const QString& package,
                        std::function<BaseOperator*(BaseZigZagObject* parent)> construct,
                        const std::vector<const DataTypeDescription*>& inputs = {},
                        const std::vector<const DataTypeDescription*>& outputs = {},
                        const DataViewTypeInfo * view = nullptr);

    QString name;
    QString package;
    std::function<BaseOperator*(BaseZigZagObject* parent)> construct;
    std::vector<const DataTypeDescription*> inputs;
    std::vector<const DataTypeDescription*> outputs;
    const DataViewTypeInfo * view;

    // Use OpenGL
    // Library
    // Image
    // Version
    // Description
    // Author
    // License
    // Etc
};


inline bool operator<(const OperatorDescription& t1, const OperatorDescription& t2)
{
    return t1.name < t2.name;
}



class BaseOperator : public BaseZigZagObject
{
    Q_OBJECT

    friend class MoveCommand;
    friend class OperatorNetwork;

public:

    BaseOperator(BaseZigZagObject* parent, const OperatorDescription& description);

    virtual ~BaseOperator() override;

    virtual void prepare() { }
    virtual void run() = 0;

    void lock();
    void unlock();
    std::shared_ptr<std::mutex> getLock();

    int positionX() const;
    int positionY() const;

    const OperatorDescription * description() const;


    QList<DataInput*> dataInputs() const;
    QList<BaseDataType*> dataOutputs() const;

    QList<DataInput*> activeDataInputs() const;
    QList<BaseDataType*> activeDataOutputs() const;

    bool hasActiveDataInputs() const;
    bool hasActiveDataOutputs() const;


    /*
     * Used for serialization
     */
    virtual void loadState(const QVariantMap& state) override;
    virtual QVariantMap storeState() const override;

public slots:

    // Undoable action.
    //void remove();

    // Undoable action.
    void move_to(int x, int y);


signals:

    void update_view_requested();

    void position_changed(int pos_x, int pos_y);

    // Only emitted for the operator that acts as the input!
    void dataConnected(BaseOperator* outputOperator, BaseDataType* outputData,
                       BaseOperator* inputOperator, DataInput* dataInput);

    // Only emitted for the operator that acts as the input!
    void dataDisconnected(BaseOperator* outputOperator, BaseDataType* outputData,
                          BaseOperator* inputOperator, DataInput* dataInput);

    // Only emitted for the operator that acts as the input!
    void parameterConnected(BaseOperator* exportingOperator, BaseComponent * exporter,
                            BaseOperator* importingOperator, BaseComponent * importer);

    // Only emitted for the operator that acts as the input!
    void parameterDisconnected(BaseOperator* exportingOperator, BaseComponent * exporter,
                               BaseOperator* importingOperator, BaseComponent * importer);


protected:


    void updateView();

    // Should be overriden to acquire resources.
    // Never call this function directly, this is done for you.
    virtual void acquireResources() { }


    // Should be overriden to release resources.
    // Never call this function directly, this is done for you.
    virtual void releaseResources() { }


private:

    friend class ConnectParametersCommand;
    friend class DisconnectParametersCommand;

    // Direct version of move_to (non-undoable)
    void set_position(int pos_x, int pos_y);

    int m_positionX = 0;
    int m_positionY = 0;

    std::shared_ptr<std::mutex> m_mutex;

    const OperatorDescription * m_description;

};

Q_DECLARE_METATYPE(BaseOperator*)
Q_DECLARE_METATYPE(QList<BaseOperator*>)
Q_DECLARE_METATYPE(std::vector<BaseOperator*>)

