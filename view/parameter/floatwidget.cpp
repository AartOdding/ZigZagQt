#include "floatwidget.h"

#include <iostream>


FloatWidget::FloatWidget(QWidget * parent, BaseParameter* par)
    : QWidget(parent), parameter(par)
{
    OpenSans.setPixelSize(14);
    setLayout(&layout);
    layout.setMargin(0);

    bounded_value<double> val;

    num_components = static_cast<int>(par->type()) - static_cast<int>(ParameterType::Float) + 1;
    Q_ASSERT(num_components >= 1 && num_components <= 4);
    spinboxes.reserve(num_components);

    for (int i = 0; i < num_components; ++i)
    {
        spinboxes.emplace_back(new QDoubleSpinBox());
        spinboxes.back()->setFont(OpenSans);
        spinboxes.back()->setButtonSymbols(QAbstractSpinBox::NoButtons);
        layout.addWidget(spinboxes.back());
    }

    if (num_components == 1)
    {
        auto p = static_cast<FloatPar*>(parameter);
        spinboxes[0]->setRange(p->min(), p->max());
        spinboxes[0]->setValue(p->get());
    }
    else if (num_components == 2)
    {
        auto p = static_cast<Float2Par*>(parameter);
        spinboxes[0]->setRange(p->min(), p->max());
        spinboxes[1]->setRange(p->min(), p->max());
        spinboxes[0]->setValue(p->x());
        spinboxes[1]->setValue(p->y());
    }
    else if (num_components == 3)
    {
        auto p = static_cast<Float3Par*>(parameter);
        spinboxes[0]->setRange(p->min(), p->max());
        spinboxes[1]->setRange(p->min(), p->max());
        spinboxes[2]->setRange(p->min(), p->max());
        spinboxes[0]->setValue(p->x());
        spinboxes[1]->setValue(p->y());
        spinboxes[2]->setValue(p->z());
    }
    else if (num_components == 4)
    {
        auto p = static_cast<Float4Par*>(parameter);
        spinboxes[0]->setRange(p->min(), p->max());
        spinboxes[1]->setRange(p->min(), p->max());
        spinboxes[2]->setRange(p->min(), p->max());
        spinboxes[3]->setRange(p->min(), p->max());
        spinboxes[0]->setValue(p->x());
        spinboxes[1]->setValue(p->y());
        spinboxes[2]->setValue(p->z());
        spinboxes[3]->setValue(p->w());
    }


    if (parameter->minimal_updates())
    {
        for (auto& sb : spinboxes)
        {
            connect(sb, &QAbstractSpinBox::editingFinished, this, &FloatWidget::on_editing_finished);
        }
    }
    else
    {
        for (auto& sb : spinboxes)
        {
            connect(sb, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &FloatWidget::on_value_changed);
        }
    }
}


void FloatWidget::on_value_changed(int)
{
    std::cout << "on value changed" << spinboxes[0]->value() << "\n";
    if (num_components == 1)
    {
        auto p = static_cast<FloatPar*>(parameter);
        p->set(spinboxes[0]->value());
    }
    else if (num_components == 2)
    {
        auto p = static_cast<Float2Par*>(parameter);
        p->set(spinboxes[0]->value(), spinboxes[1]->value());
    }
    else if (num_components == 3)
    {
        auto p = static_cast<Float3Par*>(parameter);
        p->set(spinboxes[0]->value(), spinboxes[1]->value(), spinboxes[2]->value());
    }
    else if (num_components == 4)
    {
        auto p = static_cast<Float4Par*>(parameter);
        p->set(spinboxes[0]->value(), spinboxes[1]->value(), spinboxes[2]->value(), spinboxes[3]->value());
    }
}


void FloatWidget::on_editing_finished()
{
    std::cout << "on edit finished\n";
    if (num_components == 1)
    {
        auto p = static_cast<FloatPar*>(parameter);
        p->set(spinboxes[0]->value());
    }
    else if (num_components == 2)
    {
        auto p = static_cast<Float2Par*>(parameter);
        p->set(spinboxes[0]->value(), spinboxes[1]->value());
    }
    else if (num_components == 3)
    {
        auto p = static_cast<Float3Par*>(parameter);
        p->set(spinboxes[0]->value(), spinboxes[1]->value(), spinboxes[2]->value());
    }
    else if (num_components == 4)
    {
        auto p = static_cast<Float4Par*>(parameter);
        p->set(spinboxes[0]->value(), spinboxes[1]->value(), spinboxes[2]->value(), spinboxes[3]->value());
    }
}
