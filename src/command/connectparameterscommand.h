#pragma once

#include <QUndoCommand>

#include "app.h"
#include "model/BaseOperator.hpp"
#include "model/parameter/BaseComponent.hpp"
#include "model/parameter/TextComponent.hpp"

#include "utility/stdLibraryHelpers.hpp"



class ConnectParametersCommand : public QUndoCommand
{

public:

    ConnectParametersCommand(BaseComponent* exporter, BaseComponent* importer_)
        : importer(importer_), new_exporter(exporter), initial_exporter(importer->m_import)
    {
        Q_ASSERT(exporter && importer && exporter != importer);
        Q_ASSERT(new_exporter != importer->m_import);
    }


    void redo() override
    {
        if (initial_exporter)
        {
            Q_ASSERT(importer->m_import == initial_exporter);
            Q_ASSERT(contains(initial_exporter->m_exports, importer));

            break_connection(initial_exporter, importer);
        }
        Q_ASSERT(importer->m_import == nullptr);
        Q_ASSERT(!contains(new_exporter->m_exports, importer));

        make_connection(new_exporter, importer);
    }


    void undo() override
    {
        Q_ASSERT(importer->m_import == new_exporter);
        Q_ASSERT(contains(new_exporter->m_exports, importer));

        break_connection(new_exporter, importer);

        if (initial_exporter)
        {
            Q_ASSERT(importer->m_import == nullptr);
            Q_ASSERT(!contains(initial_exporter->m_exports, importer));

            make_connection(initial_exporter, importer);
        }
    }


private:

    void make_connection(BaseComponent* exporter_, BaseComponent* importer_) const
    {
        // Add the importing/ exporting pointers in the parameters.
        importer_->m_import = exporter_;
        exporter_->m_exports.push_back(importer_);

        // Add the parameters to their parent's list of importing/ exporting parameters.
        //importer_->getParameter()->get_operator()->m_importing_parameters.push_back(importer_);
        //exporter_->getParameter()->get_operator()->m_exporting_parameters.push_back(exporter_);

        if (qobject_cast<TriggerComponent*>(exporter_))
        {
            QObject::connect(exporter_, qOverload<>(&BaseComponent::exportChange),
                             importer_, qOverload<>(&BaseComponent::importChange));
        }
        else if (qobject_cast<Int64Component*>(exporter_))
        {
            QObject::connect(exporter_, qOverload<int64_t>(&BaseComponent::exportChange),
                             importer_, qOverload<int64_t>(&BaseComponent::importChange));
            importer_->importChange(static_cast<Int64Component*>(exporter_)->getValue());
        }
        else if (qobject_cast<Float64Component*>(exporter_))
        {
            QObject::connect(exporter_, qOverload<double>(&BaseComponent::exportChange),
                             importer_, qOverload<double>(&BaseComponent::importChange));
            importer_->importChange(static_cast<Float64Component*>(exporter_)->getValue());
        }
        else if (qobject_cast<TextComponent*>(exporter_))
        {
            QObject::connect(exporter_, qOverload<const QString&>(&BaseComponent::exportChange),
                             importer_, qOverload<const QString&>(&BaseComponent::importChange));
            importer_->importChange(static_cast<TextComponent*>(exporter_)->getText());
        }

        auto importingOperator = importer_->findParent<BaseOperator*>();
        auto exportingOperator = exporter_->findParent<BaseOperator*>();

        emit importingOperator->parameterConnected(exportingOperator, exporter_, importingOperator, importer_);
        emit importer_->startedImportingFrom(exporter_);
        emit exporter_->startedExportingTo(importer_);
    }

    void break_connection(BaseComponent* exporter_, BaseComponent* importer_) const
    {
        // Add the importing/ exporting pointers in the parameters.
        importer_->m_import = nullptr;
        erase(exporter_->m_exports, importer_);

        // Erase the parameters from their parent's list of importing/ exporting parameters.
        //erase(importer_->getParameter()->findParent<BaseOperator>()->m_importing_parameters, importer_);
        //erase(exporter_->getParameter()->findParent<BaseOperator>()->m_exporting_parameters, exporter_);

        if (qobject_cast<TriggerComponent*>(exporter_))
        {
            QObject::disconnect(exporter_, qOverload<>(&BaseComponent::exportChange),
                                importer_, qOverload<>(&BaseComponent::importChange));
        }
        else if (qobject_cast<Int64Component*>(exporter_))
        {
            QObject::disconnect(exporter_, qOverload<int64_t>(&BaseComponent::exportChange),
                                importer_, qOverload<int64_t>(&BaseComponent::importChange));
        }
        else if (qobject_cast<Float64Component*>(exporter_))
        {
            QObject::disconnect(exporter_, qOverload<double>(&BaseComponent::exportChange),
                                importer_, qOverload<double>(&BaseComponent::importChange));
        }
        else if (qobject_cast<TextComponent*>(exporter_))
        {
            QObject::disconnect(exporter_, qOverload<const QString&>(&BaseComponent::exportChange),
                                importer_, qOverload<const QString&>(&BaseComponent::importChange));
        }

        auto importingOperator = importer_->findParent<BaseOperator*>();
        auto exportingOperator = exporter_->findParent<BaseOperator*>();

        emit importingOperator->parameterDisconnected(exportingOperator, exporter_, importingOperator, importer_);
        emit importer_->stoppedImportingFrom(exporter_);
        emit exporter_->stoppedExportingTo(importer_);
    }

    BaseComponent* const importer;
    BaseComponent* const new_exporter;
    BaseComponent* const initial_exporter;

};
