#pragma once

#include <utility>

class BaseConnector;


/*
 * Class used to keep track connections between Connectors.
 * Creating a connection between two connectors is a two step process:
 * starting a connection and finishing a connections.
 * To keep track of the state we use this class.
 */
class ConnectionManager
{
public:

    void startConnection(BaseConnector* connector);

    std::pair<bool, BaseConnector*> finishConnection(BaseConnector* connector);

    void cancelConnection();


    bool connectionStarted() const;

    BaseConnector * getStartingConnector() const;

    bool canFinishConnection(BaseConnector* connector) const;


private:

    BaseConnector * m_startingConnector = nullptr;


};
