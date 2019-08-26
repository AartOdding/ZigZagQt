#pragma once

#include <vector>

#include <QObject>


#include "baseparameter.h"


namespace parameter
{

    class ParameterOwner : public QObject
    {
        Q_OBJECT

    public:

        ParameterOwner(QObject *parent = nullptr);

        const std::vector<BaseParameter*>& parameters() const;

        // Should not be necessary to be used by the user, called from BaseParameter.
        void register_parameter(BaseParameter* parameter);


    signals:

        void parameter_added(BaseParameter* parameter);


    protected:

        std::vector<BaseParameter*> m_parameters;


    };


}
