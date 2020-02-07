#pragma once

#include <vector>

#include <QList>
#include <QString>
#include <QUndoCommand>
#include <QUndoStack> // TODO: remove

#include "BaseZigZagObject.hpp"


class BaseOperator;
class OperatorDescription;



class OperatorNetwork : public BaseZigZagObject
{
    Q_OBJECT

public:

    OperatorNetwork(const QString& name);


    const std::vector<BaseOperator*>& getOperators() const;


    QUndoStack* get_undo_stack(); // TODO: move elsewhere


    virtual void loadState(const QVariantMap&) override;

    virtual QVariantMap storeState() const override;

    virtual void createChild(const QXmlStreamAttributes&) override;


signals:

    void operatorAdded(BaseOperator* operatorPtr);

    void operatorRemoved(BaseOperator* operatorPtr);


private slots:

    void redo();

    void undo();


    void addOperator(const OperatorDescription* operatorDescription, int xPos, int yPos);

    void removeOperator(BaseOperator* operatorPtr);

    void removeOperators(QList<BaseOperator*> operatorPtrs);

private:


    class AddOperatorCommand : public QUndoCommand
    {
    public:

        AddOperatorCommand(OperatorNetwork* network, BaseOperator* op);
        ~AddOperatorCommand() override;

        void redo() override;
        void undo() override;

    private:

        OperatorNetwork* m_network;
        BaseOperator* m_operator;
        bool m_hasOwnership;

    };


    class RemoveOperatorCommand : public QUndoCommand
    {
    public:

        RemoveOperatorCommand(OperatorNetwork* network, BaseOperator* op);
        ~RemoveOperatorCommand() override;

        void redo() override;
        void undo() override;

    private:

        OperatorNetwork* m_network;
        BaseOperator* m_operator;
        bool m_hasOwnership;

    };


    void addOperatorImplementation(BaseOperator * operator_ptr);

    void removeOperatorImplementation(BaseOperator * operator_ptr);


    QUndoStack undo_stack; // TODO: move elsewhere

    std::vector<BaseOperator*> m_operators;

};
