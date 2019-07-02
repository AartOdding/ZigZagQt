#pragma once

#include <QPointer>
#include <QUndoCommand>

#include "model/program/programmodel.h"
#include "model/operator/shadertop.h"



/*
 * For now the remove command does not actually free any resources,
 * but instead just makes sure that the operator is not rendered anymore,
 * by removing it from the model. If we then want to bring it back we only
 * have to unhide it. Not actually build the whole object up again at a new
 * location in memory.
 *
 * Might need to be changed later into full serialization / deserialization
 * in order to actually give back gpu resources when the operator is deleted.
 *
 * Another option would be to keep the operator, but to deallocate and
 * reallocate its gpu resources only.
 *
 * It is important to think abou thwat happens to other operators that are still
 * dependant on this operator when it is "deleted"
 */

class RemoveCommand : public QUndoCommand
{

public:

    RemoveCommand(ProgramModel& model_, QPointer<BaseOperator> op)
        : model(model_), operator_(op)
    {
        // All connections have to be removed first with disconnect command!
        Q_ASSERT(op);
        Q_ASSERT(op->get_num_used_inputs() == 0);
        Q_ASSERT(op->get_num_output_users() == 0);
    }

    void redo() override
    {
        Q_ASSERT(!operator_owner);

        // Removing the operator from its parent, this means it will no longer be
        // deleted by the model, but that is now our responsibility. Therefore
        // we put the operator in a scopedPointer, so its lifetime is bound to
        // this command.
        operator_->setParent(nullptr);
        operator_owner.reset(operator_);
    }

    void undo() override
    {
        Q_ASSERT(operator_owner);

        operator_owner.take();        // Take back ownership
        operator_->setParent(&model); // Put the operator back in the model.
    }


private:

    ProgramModel& model;
    const QPointer<BaseOperator> operator_;
    QScopedPointer<BaseOperator> operator_owner;

};
