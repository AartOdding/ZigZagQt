#include "parametereditor.h"
#include "model/baseoperator.h"
#include "view/viewport.h"
#include "view/operatorview.h"

#include <QIcon>
#include <QtGlobal>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QGraphicsScene>


ParameterEditor::ParameterEditor(Viewport* viewport_)
    : viewport(viewport_)
{
    Q_ASSERT(viewport);

#ifdef Q_OS_MAC
    setParent(nullptr);
    setWindowFlags(Qt::WindowStaysOnTopHint);
#else
    setParent(viewport_);
    setWindowFlags(Qt::Window |Qt::CustomizeWindowHint | Qt::WindowTitleHint
                   /*| Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint*/);
#endif

    outer_layout.setMargin(0);
    outer_layout.setSpacing(0);
    outer_layout.addWidget(&scroll_area);

    scroll_area.setWidgetResizable(true);
    scroll_area.setWidget(&parameter_area);

    inner_layout.setMargin(10);
    inner_layout.setSpacing(10);
    inner_layout.addStretch();


    scroll_area.setFrameShape(QFrame::NoFrame);
}


void ParameterEditor::set_scene(QGraphicsScene* new_model)
{
    if (model != new_model)
    {
        if (model != nullptr)
        {
            disconnect(model, &QGraphicsScene::selectionChanged, this, &ParameterEditor::on_selection_changed);
        }
        if (new_model)
        {
            model = new_model;
            connect(model, &QGraphicsScene::selectionChanged, this, &ParameterEditor::on_selection_changed);
        }
    }
}


void ParameterEditor::on_selection_changed()
{
    auto selected_items = model->selectedItems();

    if (selected_items.size() == 1)
    {
        auto selected = dynamic_cast<OperatorView*>(selected_items[0]);

        if (selected)
        {
            if (parameters)
            {
                delete parameters;
                parameters = nullptr;
            }
            parameters = new ParameterGroup(this, &selected->operator_model);
            inner_layout.insertWidget(0, parameters);
            if (!isVisible()) show();
            setWindowTitle(selected->operator_model.type()->name.c_str());
            return;
        }
    }
    if (parameters)
    {
        delete parameters;
        parameters = nullptr;
        setWindowTitle("ZigZag");
    }
}
