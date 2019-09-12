#pragma once

#include <QUndoCommand>

#include "model/parameter/baseparameter.h"
#include "model/parameter/parameterowner.h"

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
        importer->owner()->top_level_owner()->flag_parameter_disconnection(exporter, importer);
        importer->m_import = nullptr;
        try_erase(exporter->m_exports, importer);
    }


    void undo() override
    {
        Q_ASSERT(importer->m_import == nullptr);
        Q_ASSERT(!contains(exporter->m_exports, importer));
        importer->m_import = exporter;
        exporter->m_exports.push_back(importer);
        importer->owner()->top_level_owner()->flag_parameter_connection(exporter, importer);
    }


private:

    BaseParameter* const exporter;
    BaseParameter* const importer;

};
