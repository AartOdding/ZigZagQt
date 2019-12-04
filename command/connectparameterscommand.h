#pragma once

#include <QUndoCommand>

#include "model/baseoperator.h"
#include "model/parameter/BaseComponent.hpp"

#include "utility/std_containers_helpers.h"



class ConnectParametersCommand : public QUndoCommand
{

public:

    ConnectParametersCommand(BaseComponent* exporter, BaseComponent* importer_)
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

    void make_connection(BaseComponent* exporter_, BaseComponent* importer_) const
    {
        // Add the importing/ exporting pointers in the parameters.
        importer_->import = exporter_;
        exporter_->exports.push_back(importer_);

        // Add the parameters to their parent's list of importing/ exporting parameters.
        importer_->getParameter()->get_operator()->m_importing_parameters.push_back(importer_);
        exporter_->getParameter()->get_operator()->m_exporting_parameters.push_back(exporter_);

        switch (exporter_->getComponentType())
        {
        case BaseComponent::Int64:
            QObject::connect(exporter_, qOverload<int64_t>(&BaseComponent::valueChanged), importer_, qOverload<int64_t>(&BaseComponent::store));
            importer_->store(static_cast<IntParameterComponent*>(exporter_)->get());
            break;
        case BaseComponent::Float64:
            QObject::connect(exporter_, qOverload<double>(&BaseComponent::valueChanged), importer_, qOverload<double>(&BaseComponent::store));
            importer_->store(static_cast<FloatComponent*>(exporter_)->get_value());
            break;
        case BaseComponent::Text:
            QObject::connect(exporter_, qOverload<const QString&>(&BaseComponent::valueChanged), importer_, qOverload<const QString&>(&BaseComponent::store));
            break;
        case BaseComponent::Reference:
            QObject::connect(exporter_, qOverload<QObject*>(&BaseComponent::valueChanged), importer_, qOverload<QObject*>(&BaseComponent::store));
            break;
        }

        emit importer_->getParameter()->get_operator()->parameter_started_importing(exporter_, importer_);
        emit importer_->startedImportingFrom(exporter_);
        emit exporter_->startedExportingTo(importer_);
    }

    void break_connection(BaseComponent* exporter_, BaseComponent* importer_) const
    {
        // Add the importing/ exporting pointers in the parameters.
        importer_->import = nullptr;
        erase(exporter_->exports, importer_);

        // Erase the parameters from their parent's list of importing/ exporting parameters.
        erase(importer_->getParameter()->get_operator()->m_importing_parameters, importer_);
        erase(exporter_->getParameter()->get_operator()->m_exporting_parameters, exporter_);

        switch (exporter_->getComponentType())
        {
        case BaseComponent::Int64:
            QObject::disconnect(exporter_, qOverload<int64_t>(&BaseComponent::valueChanged), importer_, qOverload<int64_t>(&BaseComponent::store));
            break;
        case BaseComponent::Float64:
            QObject::disconnect(exporter_, qOverload<double>(&BaseComponent::valueChanged), importer_, qOverload<double>(&BaseComponent::store));
            break;
        case BaseComponent::Text:
            QObject::disconnect(exporter_, qOverload<const QString&>(&BaseComponent::valueChanged), importer_, qOverload<const QString&>(&BaseComponent::store));
            break;
        case BaseComponent::Reference:
            QObject::disconnect(exporter_, qOverload<QObject*>(&BaseComponent::valueChanged), importer_, qOverload<QObject*>(&BaseComponent::store));
            break;
        }

        emit importer_->getParameter()->get_operator()->parameter_stopped_importing(exporter_, importer_);
        emit importer_->stoppedImportingFrom(exporter_);
        emit exporter_->stoppedExportingTo(importer_);
    }

    BaseComponent* const importer;
    BaseComponent* const new_exporter;
    BaseComponent* const initial_exporter;

};
