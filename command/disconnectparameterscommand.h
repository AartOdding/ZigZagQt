#pragma once

#include <QUndoCommand>

#include "model/baseoperator.h"
#include "model/parameter/BaseComponent.hpp"

#include "utility/std_containers_helpers.h"



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

        // Erase the parameters from their parent's list of importing/ exporting parameters.
        erase(importer->getParameter()->get_operator()->m_importing_parameters, importer);
        erase(exporter->getParameter()->get_operator()->m_exporting_parameters, exporter);

        emit importer->getParameter()->get_operator()->parameter_stopped_importing(exporter, importer);
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

        // Add the parameters to their parent's list of importing/ exporting parameters.
        importer->getParameter()->get_operator()->m_importing_parameters.push_back(importer);
        exporter->getParameter()->get_operator()->m_exporting_parameters.push_back(exporter);

        emit importer->getParameter()->get_operator()->parameter_started_importing(exporter, importer);
        emit importer->startedImportingFrom(exporter);
        emit exporter->startedExportingTo(importer);
    }


private:

    BaseComponent* const exporter;
    BaseComponent* const importer;

};
