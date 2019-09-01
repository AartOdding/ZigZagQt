#pragma once

#include <QUndoCommand>

#include "model/parameter/baseparameter.h"

#include "utility/std_containers_helpers.h"



class ConnectParametersCommand : public QUndoCommand
{

public:

    ConnectParametersCommand(BaseParameter* exporter, BaseParameter* importer_)
        : new_exporter(exporter), importer(importer_)
    {
        Q_ASSERT(new_exporter && importer);
        initial_exporter = importer->m_import;
    }

    void redo() override
    {
        if (initial_exporter)
        {
            try_erase(initial_exporter->m_exports, importer);
        }

        if (!contains(new_exporter->m_exports, importer))
        {
            new_exporter->m_exports.push_back(importer);
        }

        importer->m_import = new_exporter;
    }


    void undo() override
    {
        try_erase(new_exporter->m_exports, importer);

        if (initial_exporter && !contains(initial_exporter->m_exports, importer))
        {
            initial_exporter->m_exports.push_back(importer);
        }

        importer->m_import = initial_exporter;
    }


private:

    BaseParameter* new_exporter;
    BaseParameter* initial_exporter;
    BaseParameter* importer;

};
