#ifndef DATAINPUTVIEW_H
#define DATAINPUTVIEW_H

#include <QObject>

class DataInputView : public QObject
{
    Q_OBJECT
public:
    explicit DataInputView(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DATAINPUTVIEW_H
