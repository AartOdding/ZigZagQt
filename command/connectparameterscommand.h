#pragma once

#include <QUndoCommand>

#include "model/parameter/baseparameter.h"
#include "model/parameter/parameterowner.h"

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
            importer->owner()->top_level_owner()->flag_parameter_disconnection(initial_exporter, importer);
            try_erase(initial_exporter->m_exports, importer);
            importer->m_import = nullptr;
        }

        Q_ASSERT(importer->m_import == nullptr);
        Q_ASSERT(!contains(new_exporter->m_exports, importer));
        new_exporter->m_exports.push_back(importer);
        importer->m_import = new_exporter;
        importer->owner()->top_level_owner()->flag_parameter_connection(new_exporter, importer);
    }


    void undo() override
    {
        Q_ASSERT(importer->m_import == new_exporter);
        Q_ASSERT(contains(new_exporter->m_exports, importer));

        importer->owner()->top_level_owner()->flag_parameter_disconnection(new_exporter, importer);
        try_erase(new_exporter->m_exports, importer);
        importer->m_import = nullptr;

        if (initial_exporter)
        {
            Q_ASSERT(importer->m_import == nullptr);
            Q_ASSERT(!contains(initial_exporter->m_exports, importer));
            initial_exporter->m_exports.push_back(importer);
            importer->m_import = initial_exporter;
            importer->owner()->top_level_owner()->flag_parameter_connection(initial_exporter, importer);
        }

    }


private:

    BaseParameter* const importer;
    BaseParameter* const new_exporter;
    BaseParameter* const initial_exporter;

};
