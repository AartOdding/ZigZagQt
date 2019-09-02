#pragma once

class BaseConnector;



class ConnectionManager
{
public:

    ConnectionManager() = default;

    virtual ~ConnectionManager() = default;


    void try_connect(BaseConnector* connector);

    void cancel_connection();



    bool is_connecting() const;

    BaseConnector * active_connector() const;


private:

    BaseConnector * m_active_connector = nullptr;


};
