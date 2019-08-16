#include "parametereditor.h"
#include "operatorview.h"

#include "model/baseoperator.h"
#include "model/parameter/baseparameter.h"
#include "model/parameter/integerparameter.h"
#include "model/parameter/enumparameter.h"

#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QSizeGrip>
#include <QFormLayout>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGuiApplication>
#include <QOpenGLWidget>

#include <iostream>


ParameterEditorHeader::ParameterEditorHeader(ParameterEditor& e)
    : QWidget(&e), editor(e)
{
    setAutoFillBackground(true);
    setCursor(Qt::SizeVerCursor);
    auto p = QGuiApplication::palette();
    p.setColor(QPalette::All, QPalette::Window, QColor(160, 160, 160));
    setPalette(p);
}


void ParameterEditorHeader::mouseMoveEvent(QMouseEvent * event)
{
    event->accept();
    auto viewport = static_cast<QWidget*>(editor.parent());
    auto y = mapTo(viewport, event->pos()).y();
    auto top = y - offset_y;

    if (top < 1) top = 1;
    if (top > viewport->height() - height()) top = viewport->height() - height();

    auto g = editor.geometry();
    g.moveTop(top);
    editor.setGeometry(g);
}



void ParameterEditorHeader::mouseReleaseEvent(QMouseEvent * event)
{
    event->accept();
}

void ParameterEditorHeader::mousePressEvent(QMouseEvent * event)
{
    event->accept();
    start_y = mapTo(static_cast<QWidget*>(editor.parent()), event->pos()).y();
    offset_y = event->y();
}




ParameterEditor::ParameterEditor(QOpenGLWidget* gl)
    : QWidget(gl), form_layout(new QFormLayout()), size_grip(this), header(*this)
{
    form_layout->setContentsMargins(7, 35, 7, 10);
    size_grip.setGeometry(0, height() - 10, 10, 10);
    header.setGeometry(0, 0, width(), 25);

    setWindowFlags(Qt::SubWindow);
    setAutoFillBackground(true);
    setVisible(false);
    setLayout(form_layout);
}


void ParameterEditor::set_scene(QGraphicsScene* new_scene)
{
    if (scene != new_scene)
    {
        if (scene != nullptr)
        {
            disconnect(scene, &QGraphicsScene::selectionChanged, this, &ParameterEditor::on_selection_changed);
        }
        if (new_scene)
        {
            scene = new_scene;
            connect(scene, &QGraphicsScene::selectionChanged, this, &ParameterEditor::on_selection_changed);
        }
    }
}


void ParameterEditor::on_selection_changed()
{
    auto selected_items = scene->selectedItems();

    if (selected_items.size() == 1)
    {
        auto selected = dynamic_cast<OperatorView*>(selected_items[0]);

        if (selected && selected != focus_op)
        {
            if (focus_op)
            {
                tear_down_ui();
            }
            focus_op = selected;

            build_up_ui();
            setVisible(true);
            return;
        }
    }
    tear_down_ui();
    focus_op = nullptr;
    setVisible(false);
}


void ParameterEditor::resizeEvent(QResizeEvent *event)
{
    size_grip.setGeometry(0, height() - 10, 10, 10);
    header.setGeometry(0, 0, width(), 25);
}


void ParameterEditor::tear_down_ui()
{
    for (int i = form_layout->rowCount() - 1; i >= 0; --i)
    {
        form_layout->removeRow(i);
    }
}


void ParameterEditor::build_up_ui()
{
    auto & parameters = focus_op->operator_model.parameters();

    for (auto & p : parameters)
    {
        QLabel* label = new QLabel(p->name);

        if (p->type == ParameterType::Int)
        {
            auto par = qobject_cast<IntegerParameter*>(p);
            QSpinBox* spinbox = new QSpinBox(this);
            spinbox->setRange(INT_MIN, INT_MAX);
            spinbox->setValue(*par);
            connect(spinbox, qOverload<int>(&QSpinBox::valueChanged), par, &IntegerParameter::set);
            form_layout->addRow(label, spinbox);
        }
        else if (p->type == ParameterType::Enum)
        {
            auto par = qobject_cast<EnumParameter*>(p);
            QComboBox * combo_box = new QComboBox(this);
            for (const auto& value : *(par->definition))
            {
                combo_box->addItem(value.c_str());
            }
            combo_box->setCurrentIndex(*par);
            connect(combo_box, qOverload<int>(&QComboBox::currentIndexChanged), par, qOverload<int>(&EnumParameter::set));
            form_layout->addRow(label, combo_box);
        }
    }
}

