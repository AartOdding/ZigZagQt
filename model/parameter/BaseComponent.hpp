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

    enum ComponentType : qint32
    {
        Int64,
        Float64,
        Text,
        Reference
    };

    enum ParameterFlags : quint32   // Consequence when false.
    {
        CanImport     =  1<<0,       // When false parameter will be hidden from import menu.
        CanExport     =  1<<1,       // When false arameter will be hidden from export menu.
        IsEditable    =  1<<2,       // When false The widget will appear in the gui but not be editable.
        IsVisible     =  1<<3,       // When false The widget will not appear in the gui at all.
        IsUpdateEager =  1<<4,       // When false only receive the minimal amount of updates, when the parameter is being changed.

        // Add more flags here
        AllFlags      = (1<<5)-1
    };


    BaseComponent(BaseParameterOld * parameter, ComponentType componentType);

    virtual ~BaseComponent() = default;


    int getFlags() const;

    bool hasFlag(ParameterFlags flag) const;


    BaseParameterOld * getParameter() const;

    ComponentType getComponentType() const;


    bool isImporting() const;

    bool isExporting() const;


    BaseComponent * getImport() const;

    const std::vector<BaseComponent *>& getExports() const;


    /*
     * Will process the pending changes if any. If the component changed this function
     * will return true.
     */
    virtual bool update() = 0;


    virtual void readXml(QXmlStreamReader& xml);

    virtual void writeXml(XmlSerializer& xml);

public slots:

    void setFlags(ParameterFlags flags);
    void setFlag(ParameterFlags flag, bool value);


    void setImport(BaseComponent * exporter);

    void stopImporting();

    void stopExporting();


    /*
     * The idea of the set functions is that they don't directly change the value, but instead
     * store the value, so it can actuallybe changed in the update function.
     */
    virtual void set(int64_t) { }
    virtual void set(double) { }
    virtual void set(const QString&) { }
    virtual void set(QObject *) { }


signals:

    void startedImportingFrom(BaseComponent* exporter);
    void stoppedImportingFrom(BaseComponent* exporter);
    void startedExportingTo(BaseComponent* importer);
    void stoppedExportingTo(BaseComponent* importer);

    void flagsChanged(ParameterFlags old_flags, ParameterFlags new_flags);

    void valueChanged(int64_t value);
    void valueChanged(double value);
    void valueChanged(const QString& value);
    void valueChanged(QObject * value);


private:

    friend class ConnectParametersCommand;
    friend class DisconnectParametersCommand;

    std::vector<BaseComponent *> exports;

    BaseComponent * import = nullptr;

    BaseParameterOld * parameter;

    ComponentType m_componentType;

    ParameterFlags flags = AllFlags;


};
