#include "parametereditor.h"
#include "model/BaseOperator.hpp"
#include "view/Viewport.hpp"
#include "view/operatorview.h"

#include <QIcon>
#include <QtGlobal>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QGraphicsScene>



ParameterEditor::ParameterEditor(QWidget* parent)
{

#ifdef Q_OS_MAC
    setParent(nullptr);
    setWindowFlags(Qt::WindowStaysOnTopHint);
#else
    setParent(parent);
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


void ParameterEditor::setScene(QGraphicsScene* new_model)
{
    if (model != new_model)
    {
        if (model != nullptr)
        {
            disconnect(model, &QGraphicsScene::selectionChanged, this, &ParameterEditor::onSelectionChanged);
        }
        if (new_model)
        {
            model = new_model;
            connect(model, &QGraphicsScene::selectionChanged, this, &ParameterEditor::onSelectionChanged);
        }
    }
}


void ParameterEditor::onSelectionChanged()
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
            setWindowTitle(selected->operator_model.description()->name);
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
