#pragma once

#include <bitset>

#include <QMetaType>



enum class ParameterFlag : quint32
{
    /*
     * Whether the component/parameter is allowed to import from other components/parameters.
     * When this flag is false, the value can only be changed from GUI or from code, but it cannot
     * import changes from another component/parameter.
     * The default value is on.
     */
    CanImport                = 0,

    /*
     * Whether the component/parameter is allowed to export its changes to other components/parameters.
     * If this value is false you will not be able to connect it to another component/parameter.
     * The default value is on.
     */
    CanExport                = 1,

    /*
     * Whether or not the widget will be shown in the GUI. If the flag is chnaged from true to false all
     * imports and exports will be disconnected.
     * The default value is on.
     */
    IsVisible                = 2,

    /*
     * Whether the value of the parameter/component can be edited by the user from the GUI.
     * When false The widget will appear in the gui but not be editable.
     * The default value is on.
     */
    IsEditable               = 3,

    /*
     * Whether or not the value will be continuously send updates when a user interaction is still in
     * progress, but not yet finished. For something like a color you would want to see all the intermediate
     * values as well, but for something like changing the size of a texture you would only want to send an
     * update to the parameter/component when the user is finsihes with editing, in order to receive less updates.
     * The default value is on.
     */
    UpdatesWhileEditing      = 4,

    /*
     * Whether or not the value is still allowed to be modified from the GUI even though it is also
     * importing its value from another parameter/component. This can be very useful with for instance
     * push buttons. When an update is send from the imported parameter/component you want an update,
     * but you might also want to press the button from the GUI to send extra updates.
     * The default value is on.
     */
    IsDisabledWhileImporting = 5,
};



class ParameterFlags
{
public:

    bool getFlag(ParameterFlag flag) const;

    void setFlag(ParameterFlag flag, bool value = true);

    void operator=(quint32 value);

    explicit operator quint32() const;


private:

    static unsigned long m_defaultFlags;

    std::bitset<32> m_flags = m_defaultFlags;

};



Q_DECLARE_METATYPE(ParameterFlags);
