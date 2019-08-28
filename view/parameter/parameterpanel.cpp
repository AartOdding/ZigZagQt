#include "parameterpanel.h"
#include "parametereditor.h"
#include "parameterpanelgroup.h"

#include <QGraphicsScene>

#include "model/datainput.h"
#include "model/basedatatype.h"
#include "model/baseoperator.h"

#include "view/operatorview.h"



ParameterPanel::ParameterPanel(ParameterEditor* e)
    : editor(e)
{
    setAutoFillBackground(true);
    layout.setContentsMargins(10, 10, 10, 10);
    layout.setSpacing(10);
    layout.addStretch();
}


void ParameterPanel::set_scene(QGraphicsScene* new_scene)
{
    if (scene != new_scene)
    {
        if (scene != nullptr)
        {
            disconnect(scene, &QGraphicsScene::selectionChanged, this, &ParameterPanel::on_selection_changed);
        }
        if (new_scene)
        {
            scene = new_scene;
            connect(scene, &QGraphicsScene::selectionChanged, this, &ParameterPanel::on_selection_changed);
        }
    }
}


void ParameterPanel::on_selection_changed()
{
    auto selected_items = scene->selectedItems();

    if (selected_items.size() == 1)
    {
        auto selected = dynamic_cast<OperatorView*>(selected_items[0]);

        if (selected)
        {
            clear();
            build_ui(selected->operator_model);
            editor->setVisible(true);
            return;
        }
    }
    editor->setVisible(false);
}


void ParameterPanel::build_ui(BaseOperator& op)
{
    layout.insertWidget(layout.count()-1, new ParameterPanelGroup(this, op));
    for (auto output : op.data_outputs())
    {
        layout.insertWidget(layout.count()-1, new ParameterPanelGroup(this, *output));
    }
    for (auto input : op.data_inputs())
    {
        layout.insertWidget(layout.count()-1, new ParameterPanelGroup(this, *input));
    }
}


void ParameterPanel::clear()
{
    for (auto child : findChildren<ParameterPanelGroup*>())
    {
        delete child;
    }
}
