#include "floatwidget.h"

#include "model/parameter/int.h"


FloatWidget::FloatWidget(QWidget * parent, parameter::BaseParameter* par)
    : QWidget(parent), parameter(par)
{
    OpenSans.setPixelSize(14);
    setLayout(&layout);
    layout.setMargin(0);

    bounded_value<double> val;

    num_components = static_cast<int>(par->type) - static_cast<int>(parameter::ParameterType::Float) + 1;
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
        auto p = static_cast<parameter::Float*>(parameter);
        spinboxes[0]->setRange(p->get_min<0>(), p->get_max<0>());
        spinboxes[0]->setValue(p->get<0>());
    }
    else if (num_components == 2)
    {
        auto p = static_cast<parameter::Float2*>(parameter);
        spinboxes[0]->setRange(p->get_min<0>(), p->get_max<0>());
        spinboxes[1]->setRange(p->get_min<1>(), p->get_max<1>());
        spinboxes[0]->setValue(p->get<0>());
        spinboxes[1]->setValue(p->get<1>());
    }
    else if (num_components == 3)
    {
        auto p = static_cast<parameter::Float3*>(parameter);
        spinboxes[0]->setRange(p->get_min<0>(), p->get_max<0>());
        spinboxes[1]->setRange(p->get_min<1>(), p->get_max<1>());
        spinboxes[2]->setRange(p->get_min<2>(), p->get_max<2>());
        spinboxes[0]->setValue(p->get<0>());
        spinboxes[1]->setValue(p->get<1>());
        spinboxes[2]->setValue(p->get<2>());
    }
    else if (num_components == 4)
    {
        auto p = static_cast<parameter::Float4*>(parameter);
        spinboxes[0]->setRange(p->get_min<0>(), p->get_max<0>());
        spinboxes[1]->setRange(p->get_min<1>(), p->get_max<1>());
        spinboxes[2]->setRange(p->get_min<2>(), p->get_max<2>());
        spinboxes[3]->setRange(p->get_min<3>(), p->get_max<3>());
        spinboxes[0]->setValue(p->get<0>());
        spinboxes[1]->setValue(p->get<1>());
        spinboxes[2]->setValue(p->get<2>());
        spinboxes[3]->setValue(p->get<3>());
    }


    if (parameter->update_mode() == parameter::UpdateMode::AllUpdates)
    {
        for (auto& sb : spinboxes)
        {
            connect(sb, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &FloatWidget::on_value_changed);
        }
    }
    else
    {
        for (auto& sb : spinboxes)
        {
            connect(sb, &QAbstractSpinBox::editingFinished, this, &FloatWidget::on_editing_finished);
        }
    }
}


void FloatWidget::on_value_changed(int)
{
    std::cout << "value changed\n";
}


void FloatWidget::on_editing_finished()
{
    std::cout << "value deselected\n";
    /*
    if (parameter->get<0>() != value())
    {
        emit has_changed(value());
    }*/
}
