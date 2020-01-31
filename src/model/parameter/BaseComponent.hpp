#pragma once

#include <array>
#include <bitset>
#include <vector>
#include <QMap>
#include <QObject>
#include <QVariant>

#include "model/BaseZigZagObject.hpp"
#include "model/parameter/ParameterFlags.hpp"

class BaseParameter;

class XmlSerializer;
class QXmlStreamReader;




class BaseComponent : public BaseZigZagObject
{
    Q_OBJECT

public:

    BaseComponent(BaseParameter * parentParameter, const QString& name);

    virtual ~BaseComponent() override;

    /*
     * Should process any pending changes, should return true if value of the component changed.
     */
    virtual bool update() = 0;


    bool isImporting() const;
    bool isExporting() const;
    bool isImportingFrom(BaseComponent * exporter) const;
    bool isExportingTo(BaseComponent * importer) const;

    void startImporting(BaseComponent * exporter);
    void stopImporting();
    void stopExporting();

    BaseComponent * getImport() const;
    const std::vector<BaseComponent *>& getExports() const;


    ParameterFlags getFlags() const;

    bool getFlag(ParameterFlag flag) const;
    void setFlag(ParameterFlag flag, bool value = true);


    BaseParameter * getParameter() const;


    virtual void loadState(const QVariantMap&) override;
    virtual QVariantMap storeState() const override;

    virtual void disconnectParameters() override;

public slots:

    /*
     * The idea of the change functions is that they don't directly change the value, but instead
     * store the value, so it can actually be changed during the run function. Their base implementation
     * is empty and does nothing, deriving classes can choose which update methods to implement.
     * This means a component can choose to ignore updates from certain types, but listen to others.
     */
    virtual void importChange()               { }
    virtual void importChange(int64_t)        { }
    virtual void importChange(double)         { }
    virtual void importChange(const QString&) { }

signals:

    /*
     * Send out when the components flags have been changed.
     */
    void flagsChanged(ParameterFlags newFlags);

    /*
     * Signals send out when import/ export connections are made/ destroyed.
     */
    void startedImportingFrom(BaseComponent* exporter);
    void stoppedImportingFrom(BaseComponent* exporter);
    void startedExportingTo(BaseComponent* importer);
    void stoppedExportingTo(BaseComponent* importer);

    /*
     * Can be used by deriving classes to signal that the components value has changed.
     * When importing exporting components these signals are connected to the store slots.
     */
    void exportChange();
    void exportChange(int64_t value);
    void exportChange(double value);
    void exportChange(const QString& value);

private:

    friend class ConnectParametersCommand;
    friend class DisconnectParametersCommand;

    BaseParameter * m_parameter = nullptr;

    BaseComponent * m_import = nullptr;
    std::vector<BaseComponent *> m_exports;

    ParameterFlags m_flags;

};



Q_DECLARE_METATYPE(BaseComponent*)
