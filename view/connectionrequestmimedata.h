#pragma once

#include <QMimeData>

class DataConnectorView;



class ConnectionRequestMimeData : public QMimeData
{
    Q_OBJECT

public:

    ConnectionRequestMimeData(DataConnectorView* src)
        : source(src)
    { }


    DataConnectorView* const source;


};
