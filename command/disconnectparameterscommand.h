#pragma once

#include <QUndoCommand>

#include "model/baseoperator.h"
#include "model/parameter/baseparameter.h"

#include "utility/std_containers_helpers.h"



class DisconnectParametersCommand : public QUndoCommand
{

public:

    DisconnectParametersCommand(BaseParameter* exporter_, BaseParameter* importer_)
        : exporter(exporter_), importer(importer_)
    {
        Q_ASSERT(exporter && importer && exporter != importer);
    }


    void redo() override
    {
        Q_ASSERT(importer->m_import == exporter);
        Q_ASSERT(contains(exporter->m_exports, importer));

        importer->m_import = nullptr;
        try_erase(exporter->m_exports, importer);

        // Erase the parameters from their parent's list of importing/ exporting parameters.
        try_erase(importer->parent_operator()->m_importing_parameters, importer);
        try_erase(exporter->parent_operator()->m_exporting_parameters, exporter);

        emit importer->parent_operator()->parameter_stopped_importing(exporter, importer);
        emit importer->stopped_importing_from(exporter);
        emit exporter->stopped_exporting_to(importer);
    }


    void undo() override
    {
        Q_ASSERT(importer->m_import == nullptr);
        Q_ASSERT(!contains(exporter->m_exports, importer));

        // Add the importing/ exporting pointers in the parameters.
        importer->m_import = exporter;
        exporter->m_exports.push_back(importer);

        // Add the parameters to their parent's list of importing/ exporting parameters.
        importer->parent_operator()->m_importing_parameters.push_back(importer);
        exporter->parent_operator()->m_exporting_parameters.push_back(exporter);

        emit importer->parent_operator()->parameter_started_importing(exporter, importer);
        emit importer->started_importing_from(exporter);
        emit exporter->started_exporting_to(importer);
    }


private:

    BaseParameter* const exporter;
    BaseParameter* const importer;

};
