//
// (c)2021 by Lucky Resistor. https://luckyresistor.me/
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
#include "ParameterWidget.hpp"


#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>


ParameterWidget::ParameterWidget(const ParameterEntryPtr &parameter, QWidget *parent)
    : QWidget(parent), _currentValue(parameter->settings()["default"])
{
}


CheckBoxParameter::CheckBoxParameter(const ParameterEntryPtr &parameter, QWidget *parent)
    : ParameterWidget(parameter, parent)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(2);
    _value = new QCheckBox();
    mainLayout->addWidget(_value);
    _value->setChecked(_currentValue.toBool());
    connect(_value, &QCheckBox::toggled, this, &CheckBoxParameter::valueChanged);
}


QVariant CheckBoxParameter::value() const
{
    return static_cast<bool>(_value->isChecked());
}


void CheckBoxParameter::setValue(const QVariant &value)
{
    if (value != _currentValue) {
        _currentValue = value;
        _value->setChecked(value.toBool());
    }
}


IntegerParameter::IntegerParameter(const ParameterEntryPtr &parameter, QWidget *parent)
    : ParameterWidget(parameter, parent)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(2);
    _value = new QSpinBox();
    _value->setRange(
        parameter->settings()["minimum"].toInt(),
        parameter->settings()["maximum"].toInt()
    );
    mainLayout->addWidget(_value);
    _value->setValue(_currentValue.toInt());
    connect(_value, &QSpinBox::valueChanged, this, &CheckBoxParameter::valueChanged);
}


QVariant IntegerParameter::value() const
{
    return _value->value();
}


void IntegerParameter::setValue(const QVariant &value)
{
    if (value != _currentValue) {
        _value->setValue(value.toInt());
    }
}


IntegerSizeParameter::IntegerSizeParameter(const ParameterEntryPtr &parameter, QWidget *parent)
    : ParameterWidget(parameter, parent)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(2);
    mainLayout->addWidget(new QLabel(tr("W:")));
    _a = new QSpinBox();
    _a->setRange(
        parameter->settings()["minimum"].toSize().width(),
        parameter->settings()["maximum"].toSize().width()
    );
    mainLayout->addWidget(_a);
    _a->setValue(_currentValue.toSize().width());
    connect(_a, &QSpinBox::valueChanged, this, &CheckBoxParameter::valueChanged);
    mainLayout->addWidget(new QLabel(tr("H:")));
    _b = new QSpinBox();
    _b->setRange(
        parameter->settings()["minimum"].toSize().height(),
        parameter->settings()["maximum"].toSize().height()
    );
    mainLayout->addWidget(_b);
    _b->setValue(_currentValue.toSize().height());
    connect(_b, &QSpinBox::valueChanged, this, &CheckBoxParameter::valueChanged);
}


QVariant IntegerSizeParameter::value() const
{
    return QSize(_a->value(), _b->value());
}


void IntegerSizeParameter::setValue(const QVariant &value)
{
    if (_currentValue != value) {
        _a->setValue(value.toSize().width());
        _b->setValue(value.toSize().height());
    }
}


IntegerPositionParameter::IntegerPositionParameter(const ParameterEntryPtr &parameter, QWidget *parent)
    : ParameterWidget(parameter, parent)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(2);
    mainLayout->addWidget(new QLabel(tr("X:")));
    _a = new QSpinBox();
    _a->setRange(
        parameter->settings()["minimum"].toPoint().x(),
        parameter->settings()["maximum"].toPoint().x()
    );
    mainLayout->addWidget(_a);
    _a->setValue(_currentValue.toPoint().x());
    connect(_a, &QSpinBox::valueChanged, this, &CheckBoxParameter::valueChanged);
    mainLayout->addWidget(new QLabel(tr("Y:")));
    _b = new QSpinBox();
    _b->setRange(
        parameter->settings()["minimum"].toPoint().y(),
        parameter->settings()["maximum"].toPoint().y()
    );
    mainLayout->addWidget(_b);
    _b->setValue(_currentValue.toPoint().y());
    connect(_b, &QSpinBox::valueChanged, this, &CheckBoxParameter::valueChanged);
}


QVariant IntegerPositionParameter::value() const
{
    return QPoint(_a->value(), _b->value());
}


void IntegerPositionParameter::setValue(const QVariant &value)
{
    if (_currentValue != value) {
        _a->setValue(value.toPoint().x());
        _b->setValue(value.toPoint().y());
    }
}

