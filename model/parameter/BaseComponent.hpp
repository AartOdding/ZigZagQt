#pragma once

#include <vector>
#include <QObject>

class BaseParameterOld;

class XmlSerializer;
class QXmlStreamReader;



class BaseComponent : public QObject
{
    Q_OBJECT

public:

    enum ParameterFlags
    {
        CanImport      =  1<<0,
        CanExport      =  1<<1,
        IsEditable     =  1<<2, // When false The widget will appear in the gui but not be user editable.
        IsVisible      =  1<<3, // When false The widget will not appear in the gui at all.
        MinimalUpdates =  1<<4, // When true only receive one update when the widget is deselected, when false update a often as possible.

        DefaultFlags = CanImport | CanExport | IsEditable | IsVisible
    };

    BaseComponent(BaseParameterOld * parameter);

    virtual ~BaseComponent() = default;


    int getFlags() const;
    bool hasFlag(ParameterFlags flag) const;

    BaseParameterOld * getParameter() const;

    bool isImporting() const;
    bool isExporting() const;

    BaseComponent * getImport() const;
    const std::vector<BaseComponent *>& getExports() const;

    /*
     * Should process any pending changes, should return true if value of the component changed.
     */
    virtual bool run() = 0;

    void setFlags(ParameterFlags flags);
    void setFlag(ParameterFlags flag, bool value);

    void setImport(BaseComponent * exporter);
    void stopImporting();
    void stopExporting();

    virtual void readXml(QXmlStreamReader& xml);
    virtual void writeXml(XmlSerializer& xml);

public slots:

    /*
     * The idea of the change functions is that they don't directly change the value, but instead
     * store the value, so it can actually be changed during the run function. Their base implementation
     * is empty and does nothing, deriving classes can choose which update methods to implement.
     * This means a component can choose to ignore updates from certain types, but listen to others.
     */
    virtual void change()               { }
    virtual void change(int64_t)        { }
    virtual void change(double)         { }
    virtual void change(const QString&) { }

signals:

    /*
     * Send out when the components flags have been changed.
     */
    void flagsChanged(ParameterFlags old_flags, ParameterFlags new_flags);

    /*
     * Signals send out when import/ export connections are made/ destroyed.
     */
    void startedImportingFrom(BaseComponent* exporter);
    void stoppedImportingFrom(BaseComponent* exporter);
    void startedExportingTo(BaseComponent* importer);
    void stoppedExportingTo(BaseComponent* importer);

    /*
     * Can be used by deriving classes to signal that the components value has changed.
     * When importing exporting components these signals are connected to the store slots.
     */
    void valueChanged();
    void valueChanged(int64_t value);
    void valueChanged(double value);
    void valueChanged(const QString& value);

private:

    friend class ConnectParametersCommand;
    friend class DisconnectParametersCommand;

    BaseParameterOld * parameter = nullptr;
    BaseComponent * import = nullptr;
    std::vector<BaseComponent *> exports;

    ParameterFlags flags = DefaultFlags;

};
