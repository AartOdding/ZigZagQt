#include "intwidget.h"

#include "model/parameter/int.h"


IntWidget::IntWidget(QWidget * parent, parameter::BaseParameter* par)
    : QWidget(parent), parameter(par)
{
    OpenSans.setPixelSize(14);
    setLayout(&layout);
    layout.setMargin(0);

    num_components = static_cast<int>(par->type) - static_cast<int>(parameter::ParameterType::Int) + 1;
    Q_ASSERT(num_components >= 1 && num_components <= 4);
    spinboxes.reserve(num_components);

    for (int i = 0; i < num_components; ++i)
    {
        spinboxes.emplace_back(new QSpinBox());
        spinboxes.back()->setFont(OpenSans);
        spinboxes.back()->setButtonSymbols(QAbstractSpinBox::NoButtons);
        layout.addWidget(spinboxes.back());
    }

    if (num_components == 1)
    {
        auto p = static_cast<parameter::Int*>(parameter);
        spinboxes[0]->setRange(p->get_min<0>(), p->get_max<0>());
        spinboxes[0]->setValue(p->get<0>());
    }
    else if (num_components == 2)
    {
        auto p = static_cast<parameter::Int2*>(parameter);
        spinboxes[0]->setRange(p->get_min<0>(), p->get_max<0>());
        spinboxes[1]->setRange(p->get_min<1>(), p->get_max<1>());
        spinboxes[0]->setValue(p->get<0>());
        spinboxes[1]->setValue(p->get<1>());
    }
    else if (num_components == 3)
    {
        auto p = static_cast<parameter::Int3*>(parameter);
        spinboxes[0]->setRange(p->get_min<0>(), p->get_max<0>());
        spinboxes[1]->setRange(p->get_min<1>(), p->get_max<1>());
        spinboxes[2]->setRange(p->get_min<2>(), p->get_max<2>());
        spinboxes[0]->setValue(p->get<0>());
        spinboxes[1]->setValue(p->get<1>());
        spinboxes[2]->setValue(p->get<2>());
    }
    else if (num_components == 4)
    {
        auto p = static_cast<parameter::Int4*>(parameter);
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
            connect(sb, qOverload<int>(&QSpinBox::valueChanged), this, &IntWidget::on_value_changed);
        }
    }
    else
    {
        for (auto& sb : spinboxes)
        {
            connect(sb, &QAbstractSpinBox::editingFinished, this, &IntWidget::on_editing_finished);
        }
    }
}


void IntWidget::on_value_changed(int)
{
    std::cout << "on value changed" << spinboxes[0]->value() << "\n";
    if (num_components == 1)
    {
        auto p = static_cast<parameter::Int*>(parameter);
        p->set(spinboxes[0]->value());
    }
    else if (num_components == 2)
    {
        auto p = static_cast<parameter::Int2*>(parameter);
        p->set({ spinboxes[0]->value(), spinboxes[1]->value() });
    }
    else if (num_components == 3)
    {
        auto p = static_cast<parameter::Int3*>(parameter);
        p->set({ spinboxes[0]->value(), spinboxes[1]->value(), spinboxes[2]->value() });
    }
    else if (num_components == 4)
    {
        auto p = static_cast<parameter::Int4*>(parameter);
        p->set({ spinboxes[0]->value(), spinboxes[1]->value(), spinboxes[2]->value(), spinboxes[3]->value() });
    }
}

void IntWidget::on_editing_finished()
{
    std::cout << "on edit finished\n";
    if (num_components == 1)
    {
        auto p = static_cast<parameter::Int*>(parameter);
        p->set(spinboxes[0]->value());
    }
    else if (num_components == 2)
    {
        auto p = static_cast<parameter::Int2*>(parameter);
        p->set({ spinboxes[0]->value(), spinboxes[1]->value() });
    }
    else if (num_components == 3)
    {
        auto p = static_cast<parameter::Int3*>(parameter);
        p->set({ spinboxes[0]->value(), spinboxes[1]->value(), spinboxes[2]->value() });
    }
    else if (num_components == 4)
    {
        auto p = static_cast<parameter::Int4*>(parameter);
        p->set({ spinboxes[0]->value(), spinboxes[1]->value(), spinboxes[2]->value(), spinboxes[3]->value() });
    }
}
