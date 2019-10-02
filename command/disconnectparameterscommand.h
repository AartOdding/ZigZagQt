#pragma once

#include <QUndoCommand>

#include "model/baseoperator.h"
#include "model/parameter/baseparametercomponent.h"

#include "utility/std_containers_helpers.h"



class DisconnectParametersCommand : public QUndoCommand
{

public:

    DisconnectParametersCommand(BaseParameterComponent* exporter_, BaseParameterComponent* importer_)
        : exporter(exporter_), importer(importer_)
    {
        Q_ASSERT(exporter && importer && exporter != importer);
    }


    void redo() override
    {
        Q_ASSERT(importer->import == exporter);
        Q_ASSERT(contains(exporter->exports, importer));

        importer->import = nullptr;
        erase(exporter->exports, importer);

        // Erase the parameters from their parent's list of importing/ exporting parameters.
        erase(importer->get_parameter()->get_operator()->m_importing_parameters, importer);
        erase(exporter->get_parameter()->get_operator()->m_exporting_parameters, exporter);

        emit importer->get_parameter()->get_operator()->parameter_stopped_importing(exporter, importer);
        emit importer->stopped_importing_from(exporter);
        emit exporter->stopped_exporting_to(importer);
    }


    void undo() override
    {
        Q_ASSERT(importer->import == nullptr);
        Q_ASSERT(!contains(exporter->exports, importer));

        // Add the importing/ exporting pointers in the parameters.
        importer->import = exporter;
        exporter->exports.push_back(importer);

        // Add the parameters to their parent's list of importing/ exporting parameters.
        importer->get_parameter()->get_operator()->m_importing_parameters.push_back(importer);
        exporter->get_parameter()->get_operator()->m_exporting_parameters.push_back(exporter);

        emit importer->get_parameter()->get_operator()->parameter_started_importing(exporter, importer);
        emit importer->started_importing_from(exporter);
        emit exporter->started_exporting_to(importer);
    }


private:

    BaseParameterComponent* const exporter;
    BaseParameterComponent* const importer;

};
