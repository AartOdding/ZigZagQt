#pragma once

#include <QUndoCommand>

#include "model/BaseOperator.hpp"
#include "model/parameter/BaseComponent.hpp"
#include "model/parameter/TextComponent.hpp"

#include "utility/stdLibraryHelpers.hpp"



class DisconnectParametersCommand : public QUndoCommand
{

public:

    DisconnectParametersCommand(BaseComponent* exporter_, BaseComponent* importer_)
        : exporter(exporter_), importer(importer_)
    {
        Q_ASSERT(exporter && importer && exporter != importer);
    }


    void redo() override
    {
        Q_ASSERT(importer->m_import == exporter);
        Q_ASSERT(contains(exporter->m_exports, importer));

        importer->m_import = nullptr;
        erase(exporter->m_exports, importer);

        if (qobject_cast<TriggerComponent*>(exporter))
        {
            QObject::disconnect(exporter, qOverload<>(&BaseComponent::exportChange),
                                importer, qOverload<>(&BaseComponent::importChange));
        }
        else if (qobject_cast<Int64Component*>(exporter))
        {
            QObject::disconnect(exporter, qOverload<int64_t>(&BaseComponent::exportChange),
                                importer, qOverload<int64_t>(&BaseComponent::importChange));
        }
        else if (qobject_cast<Float64Component*>(exporter))
        {
            QObject::disconnect(exporter, qOverload<double>(&BaseComponent::exportChange),
                                importer, qOverload<double>(&BaseComponent::importChange));
        }
        else if (qobject_cast<TextComponent*>(exporter))
        {
            QObject::disconnect(exporter, qOverload<const QString&>(&BaseComponent::exportChange),
                                importer, qOverload<const QString&>(&BaseComponent::importChange));
        }


        auto importingOperator = importer->findParent<BaseOperator*>();
        auto exportingOperator = exporter->findParent<BaseOperator*>();

        emit importingOperator->parameterDisconnected(exportingOperator, exporter, importingOperator, importer);
        emit importer->stoppedImportingFrom(exporter);
        emit exporter->stoppedExportingTo(importer);
    }


    void undo() override
    {
        Q_ASSERT(importer->m_import == nullptr);
        Q_ASSERT(!contains(exporter->m_exports, importer));

        // Add the importing/ exporting pointers in the parameters.
        importer->m_import = exporter;
        exporter->m_exports.push_back(importer);


        if (qobject_cast<TriggerComponent*>(exporter))
        {
            QObject::connect(exporter, qOverload<>(&BaseComponent::exportChange),
                             importer, qOverload<>(&BaseComponent::importChange));
        }
        else if (qobject_cast<Int64Component*>(exporter))
        {
            QObject::connect(exporter, qOverload<int64_t>(&BaseComponent::exportChange),
                             importer, qOverload<int64_t>(&BaseComponent::importChange));
            importer->importChange(static_cast<Int64Component*>(exporter)->getValue());
        }
        else if (qobject_cast<Float64Component*>(exporter))
        {
            QObject::connect(exporter, qOverload<double>(&BaseComponent::exportChange),
                             importer, qOverload<double>(&BaseComponent::importChange));
            importer->importChange(static_cast<Float64Component*>(exporter)->getValue());
        }
        else if (qobject_cast<TextComponent*>(exporter))
        {
            QObject::connect(exporter, qOverload<const QString&>(&BaseComponent::exportChange),
                             importer, qOverload<const QString&>(&BaseComponent::importChange));
            importer->importChange(static_cast<TextComponent*>(exporter)->getText());
        }

        auto importingOperator = importer->findParent<BaseOperator*>();
        auto exportingOperator = exporter->findParent<BaseOperator*>();

        emit importingOperator->parameterConnected(exportingOperator, exporter, importingOperator, importer);
        emit importer->startedImportingFrom(exporter);
        emit exporter->startedExportingTo(importer);
    }


private:

    BaseComponent* const exporter;
    BaseComponent* const importer;

};
