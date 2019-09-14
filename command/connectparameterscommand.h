#pragma once

#include <QUndoCommand>

#include "model/baseoperator.h"
#include "model/parameter/baseparameter.h"

#include "utility/std_containers_helpers.h"



class ConnectParametersCommand : public QUndoCommand
{

public:

    ConnectParametersCommand(BaseParameter* exporter, BaseParameter* importer_)
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

            // Erase the importing/ exporting pointers in the parameters.
            importer->m_import = nullptr;
            try_erase(initial_exporter->m_exports, importer);

            // Erase the parameters from their parent's list of importing/ exporting parameters.
            try_erase(importer->parent_operator()->m_importing_parameters, importer);
            try_erase(initial_exporter->parent_operator()->m_exporting_parameters, initial_exporter);

            emit importer->parent_operator()->parameter_stopped_importing(initial_exporter, importer);
            emit importer->stopped_importing_from(initial_exporter);
            emit initial_exporter->stopped_exporting_to(importer);
        }
        Q_ASSERT(importer->m_import == nullptr);
        Q_ASSERT(!contains(new_exporter->m_exports, importer));

        // Add the importing/ exporting pointers in the parameters.
        importer->m_import = new_exporter;
        new_exporter->m_exports.push_back(importer);

        // Add the parameters to their parent's list of importing/ exporting parameters.
        importer->parent_operator()->m_importing_parameters.push_back(importer);
        new_exporter->parent_operator()->m_exporting_parameters.push_back(new_exporter);

        emit importer->parent_operator()->parameter_started_importing(new_exporter, importer);
        emit importer->started_importing_from(new_exporter);
        emit new_exporter->started_exporting_to(importer);
    }


    void undo() override
    {
        Q_ASSERT(importer->m_import == new_exporter);
        Q_ASSERT(contains(new_exporter->m_exports, importer));

        // Erase the importing/ exporting pointers in the parameters.
        importer->m_import = nullptr;
        try_erase(new_exporter->m_exports, importer);

        // Erase the parameters from their parent's list of importing/ exporting parameters.
        try_erase(importer->parent_operator()->m_importing_parameters, importer);
        try_erase(new_exporter->parent_operator()->m_exporting_parameters, new_exporter);

        emit importer->parent_operator()->parameter_stopped_importing(new_exporter, importer);
        emit importer->stopped_importing_from(new_exporter);
        emit new_exporter->stopped_exporting_to(importer);

        if (initial_exporter)
        {
            Q_ASSERT(importer->m_import == nullptr);
            Q_ASSERT(!contains(initial_exporter->m_exports, importer));

            // Add the importing/ exporting pointers in the parameters.
            importer->m_import = initial_exporter;
            initial_exporter->m_exports.push_back(importer);

            // Add the parameters to their parent's list of importing/ exporting parameters.
            importer->parent_operator()->m_importing_parameters.push_back(importer);
            initial_exporter->parent_operator()->m_exporting_parameters.push_back(initial_exporter);

            emit importer->parent_operator()->parameter_started_importing(initial_exporter, importer);
            emit importer->started_importing_from(initial_exporter);
            emit initial_exporter->started_exporting_to(importer);
        }
    }


private:

    BaseParameter* const importer;
    BaseParameter* const new_exporter;
    BaseParameter* const initial_exporter;

};
