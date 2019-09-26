#pragma once

#include <QUndoCommand>

#include "model/baseoperator.h"
#include "model/parameter/parametercomponent.h"

#include "utility/std_containers_helpers.h"



class ConnectParametersCommand : public QUndoCommand
{

public:

    ConnectParametersCommand(ParameterComponent* exporter, ParameterComponent* importer_)
        : importer(importer_), new_exporter(exporter), initial_exporter(importer->import)
    {
        Q_ASSERT(exporter && importer && exporter != importer);
        Q_ASSERT(new_exporter != importer->import);
    }


    void redo() override
    {
        if (initial_exporter)
        {
            Q_ASSERT(importer->import == initial_exporter);
            Q_ASSERT(contains(initial_exporter->exports, importer));

            break_connection(initial_exporter, importer);
        }
        Q_ASSERT(importer->import == nullptr);
        Q_ASSERT(!contains(new_exporter->exports, importer));

        make_connection(new_exporter, importer);
    }


    void undo() override
    {
        Q_ASSERT(importer->import == new_exporter);
        Q_ASSERT(contains(new_exporter->exports, importer));

        break_connection(new_exporter, importer);

        if (initial_exporter)
        {
            Q_ASSERT(importer->import == nullptr);
            Q_ASSERT(!contains(initial_exporter->exports, importer));

            make_connection(initial_exporter, importer);
        }
    }


private:

    void make_connection(ParameterComponent* exporter_, ParameterComponent* importer_) const
    {
        // Add the importing/ exporting pointers in the parameters.
        importer_->import = exporter_;
        exporter_->exports.push_back(importer_);

        // Add the parameters to their parent's list of importing/ exporting parameters.
        importer_->get_parameter()->get_operator()->m_importing_parameters.push_back(importer_);
        exporter_->get_parameter()->get_operator()->m_exporting_parameters.push_back(exporter_);

        switch (exporter_->get_type())
        {
        case ParameterComponent::Int64:
            QObject::connect(exporter_, qOverload<int64_t>(&ParameterComponent::value_changed), importer_, qOverload<int64_t>(&ParameterComponent::set_later));
            importer_->set_later(static_cast<ParameterComponentInt64*>(exporter_)->get());
            break;
        case ParameterComponent::Double:
            QObject::connect(exporter_, qOverload<double>(&ParameterComponent::value_changed), importer_, qOverload<double>(&ParameterComponent::set_later));
            importer_->set_later(static_cast<ParameterComponentDouble*>(exporter_)->get());
            break;
        case ParameterComponent::Text:
            QObject::connect(exporter_, qOverload<const QString&>(&ParameterComponent::value_changed), importer_, qOverload<const QString&>(&ParameterComponent::set_later));
            break;
        case ParameterComponent::Reference:
            QObject::connect(exporter_, qOverload<QObject*>(&ParameterComponent::value_changed), importer_, qOverload<QObject*>(&ParameterComponent::set_later));
            break;
        }

        emit importer_->get_parameter()->get_operator()->parameter_started_importing(exporter_, importer_);
        emit importer_->started_importing_from(exporter_);
        emit exporter_->started_exporting_to(importer_);
    }

    void break_connection(ParameterComponent* exporter_, ParameterComponent* importer_) const
    {
        // Add the importing/ exporting pointers in the parameters.
        importer_->import = nullptr;
        erase(exporter_->exports, importer_);

        // Erase the parameters from their parent's list of importing/ exporting parameters.
        erase(importer_->get_parameter()->get_operator()->m_importing_parameters, importer_);
        erase(exporter_->get_parameter()->get_operator()->m_exporting_parameters, exporter_);

        switch (exporter_->get_type())
        {
        case ParameterComponent::Int64:
            QObject::disconnect(exporter_, qOverload<int64_t>(&ParameterComponent::value_changed), importer_, qOverload<int64_t>(&ParameterComponent::set_later));
            break;
        case ParameterComponent::Double:
            QObject::disconnect(exporter_, qOverload<double>(&ParameterComponent::value_changed), importer_, qOverload<double>(&ParameterComponent::set_later));
            break;
        case ParameterComponent::Text:
            QObject::disconnect(exporter_, qOverload<const QString&>(&ParameterComponent::value_changed), importer_, qOverload<const QString&>(&ParameterComponent::set_later));
            break;
        case ParameterComponent::Reference:
            QObject::disconnect(exporter_, qOverload<QObject*>(&ParameterComponent::value_changed), importer_, qOverload<QObject*>(&ParameterComponent::set_later));
            break;
        }

        emit importer_->get_parameter()->get_operator()->parameter_stopped_importing(exporter_, importer_);
        emit importer_->stopped_importing_from(exporter_);
        emit exporter_->stopped_exporting_to(importer_);
    }

    ParameterComponent* const importer;
    ParameterComponent* const new_exporter;
    ParameterComponent* const initial_exporter;

};
