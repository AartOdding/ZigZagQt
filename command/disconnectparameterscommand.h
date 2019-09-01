#pragma once

#include <QUndoCommand>

#include "model/parameter/baseparameter.h"

#include "utility/std_containers_helpers.h"



class DisconnectParametersCommand : public QUndoCommand
{

public:

    DisconnectParametersCommand(BaseParameter* exporter_, BaseParameter* importer_)
        : exporter(exporter_), importer(importer_)
    {
        Q_ASSERT(exporter && importer);
        Q_ASSERT(importer->m_import == exporter);
        Q_ASSERT(contains(exporter->m_exports, importer));
    }

    void redo() override
    {
        importer->m_import = nullptr;
        try_erase(exporter->m_exports, importer);
    }


    void undo() override
    {
        importer->m_import = exporter;
        exporter->m_exports.push_back(importer);
    }


private:

    BaseParameter* exporter;
    BaseParameter* importer;

};
