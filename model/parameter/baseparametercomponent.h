#pragma once

#include <vector>
#include <QObject>

class BaseParameter;




class BaseParameterComponent : public QObject
{
    Q_OBJECT

public:

    enum ParameterComponentType : int32_t
    {
        Int64,
        Float64,
        Text,
        Reference
    };

    enum ParameterFlags : int32_t   // Consequence when false.
    {
        CanImport     =  1<<0,       // When false parameter will be hidden from import menu.
        CanExport     =  1<<1,       // When false arameter will be hidden from export menu.
        IsEditable    =  1<<2,       // When false The widget will appear in the gui but not be editable.
        IsVisible     =  1<<3,       // When false The widget will not appear in the gui at all.
        IsUpdateEager =  1<<4,       // When false only receive the minimal amount of updates, when the parameter is being changed.

        // Add more flags here
        AllFlags      = (1<<5)-1
    };


    BaseParameterComponent(BaseParameter * parameter, ParameterComponentType component_type);

    virtual ~BaseParameterComponent() = default;


    int get_flags() const;

    bool has_flag(ParameterFlags flag) const;


    BaseParameter * get_parameter() const;

    ParameterComponentType get_component_type() const;


    bool is_importing() const;

    bool is_exporting() const;


    BaseParameterComponent * get_import() const;

    const std::vector<BaseParameterComponent *>& get_exports() const;


    // Should return true if the value was changed, because the owning parameter has to know.
    virtual bool process_changes() = 0;


public slots:

    void set_flags(ParameterFlags flags);
    void set_flag(ParameterFlags flag, bool value);


    void set_import(BaseParameterComponent * exporter);

    void stop_importing();

    void stop_exporting();


    /* The idea of the set_later functions is that they store the future value, and only
     * actually apply the change in the process_changes function. */
    virtual void set_later(int64_t) { }
    virtual void set_later(double) { }
    virtual void set_later(const QString&) { }
    virtual void set_later(QObject *) { }


signals:

    void started_importing_from(BaseParameterComponent* exporter);
    void stopped_importing_from(BaseParameterComponent* exporter);
    void started_exporting_to(BaseParameterComponent* importer);
    void stopped_exporting_to(BaseParameterComponent* importer);

    void flags_changed(ParameterFlags old_flags, ParameterFlags new_flags);

    void value_changed(int64_t value);
    void value_changed(double value);
    void value_changed(const QString& value);
    void value_changed(QObject * value);


private:

    friend class ConnectParametersCommand;
    friend class DisconnectParametersCommand;

    std::vector<BaseParameterComponent *> exports;

    BaseParameterComponent * import = nullptr;

    BaseParameter * parameter;

    ParameterComponentType component_type;

    ParameterFlags flags = AllFlags;


};
