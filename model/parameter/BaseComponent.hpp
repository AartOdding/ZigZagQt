#pragma once

#include <array>
#include <vector>
#include <bitset>
#include <QObject>

class BaseParameter;

class XmlSerializer;
class QXmlStreamReader;



enum class ParameterFlags
{
    CanImport      =  0,
    CanExport      =  1,
    IsEditable     =  2, // When false The widget will appear in the gui but not be user editable.
    IsVisible      =  3, // When false The widget will not appear in the gui at all.
    MinimalUpdates =  4  // When true only receive one update when the widget is deselected, when false update a often as possible.
};

static constexpr std::array<ParameterFlags, 4> defaultParameterFlags
{
    ParameterFlags::CanImport,
    ParameterFlags::CanExport,
    ParameterFlags::IsEditable,
    ParameterFlags::IsVisible
};



class BaseComponent : public QObject
{
    Q_OBJECT

public:

    BaseComponent(BaseParameter * parameter);

    virtual ~BaseComponent() = default;


    /*
     * Should process any pending changes, should return true if value of the component changed.
     */
    virtual bool update() = 0;


    bool isImporting() const;
    bool isExporting() const;

    void startImporting(BaseComponent * exportingComponent);
    void stopImporting();
    void stopExporting();

    BaseComponent * getImport() const;
    const std::vector<BaseComponent *>& getExports() const;


    bool hasFlag(ParameterFlags flag) const;
    void setFlag(ParameterFlags flag, bool value);


    BaseParameter * getParameter() const;


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
    void flagChanged(ParameterFlags flag, bool value);

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

    BaseParameter * m_parameter = nullptr;
    BaseComponent * m_import = nullptr;
    std::vector<BaseComponent *> m_exports;

    std::bitset<32> m_flags;

};
