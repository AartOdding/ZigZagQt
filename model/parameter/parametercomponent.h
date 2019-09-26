#pragma once

#include <QObject>

#include "baseparameter.h"
//class BaseParameter;



class ParameterComponent : public QObject
{
    Q_OBJECT

public:

    enum ParameterComponentType
    {
        Int64,
        Double,
        Text,
        Reference
    };

    enum ParameterFlag         // Consequence when false.
    {
        CanImport     =  1<<0, // Parameter will be hidden from import menu.
        CanExport     =  1<<1, // Parameter will be hidden from export menu.
        IsEditable    =  1<<2, // The widget will always look disabled.
        IsVisible     =  1<<3, // Hides the widget from the parameter edit panel.
        IsUpdateEager =  1<<4, // Will only receive update when the user finishes editing.

        // Add more flags here
        AllFlags      = (1<<5)-1
    };


    ParameterComponent(BaseParameter * parameter, ParameterComponentType type);

    virtual ~ParameterComponent() = default;

    int get_flags() const;
    bool has_flag(ParameterFlag flag) const;

    BaseParameter * get_parameter() const;
    ParameterComponentType get_type() const;


    bool is_importing() const;
    bool is_exporting() const;

    ParameterComponent * get_import() const;
    const std::vector<ParameterComponent *>& get_exports() const;


    // Should return true if the value was changed, so that the parameter can notify the operator of the change.
    virtual bool process_changes() = 0;


public slots:

    void set_flags(int flags);
    void set_flag(ParameterFlag flag, bool value);

    void set_import(ParameterComponent * exporter);
    void stop_importing();
    void stop_exporting();

    /* The idea of the set_later functions is that they store the future value, and only
     * actually apply the change in the process_changes function. */
    virtual void set_later(int64_t) { }
    virtual void set_later(double) { }
    virtual void set_later(const QString&) { }
    virtual void set_later(QObject *) { }


signals:

    void started_importing_from(ParameterComponent* exporter);
    void stopped_importing_from(ParameterComponent* exporter);
    void started_exporting_to(ParameterComponent* importer);
    void stopped_exporting_to(ParameterComponent* importer);

    void flags_changed(int old_flags, int new_flags);

    void value_changed(int64_t value);
    void value_changed(double value);
    void value_changed(const QString& value);
    void value_changed(QObject * value);


private:

    friend class ConnectParametersCommand;
    friend class DisconnectParametersCommand;

    std::vector<ParameterComponent *> exports;

    ParameterComponent * import = nullptr;

    BaseParameter * parameter;

    ParameterComponentType type;

    int flags = AllFlags;


};
