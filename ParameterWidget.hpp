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
#pragma once


#include "ParameterEntry.hpp"

#include <QtWidgets/QWidget>


class QCheckBox;
class QSpinBox;


/// The base class of all parameter widgets.
///
class ParameterWidget : public QWidget
{
    Q_OBJECT

public:
    /// Create the widget.
    ///
    ParameterWidget(const ParameterEntryPtr &parameter, QWidget *parent = nullptr);

    /// Get the current value for the widget.
    ///
    virtual QVariant value() const = 0;

    /// Set the value for this widget.
    ///
    virtual void setValue(const QVariant &value) = 0;

signals:
    /// Emitted if the value for this parameter changes.
    ///
    void valueChanged();

protected:
    QVariant _currentValue; ///< Buffer to limit signals.
};


class CheckBoxParameter : public ParameterWidget
{
    Q_OBJECT

public:
    CheckBoxParameter(const ParameterEntryPtr &parameter, QWidget *parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant &value) override;

private:
    QCheckBox *_value;
};


class IntegerParameter : public ParameterWidget
{
    Q_OBJECT

public:
    IntegerParameter(const ParameterEntryPtr &parameter, QWidget *parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant &value) override;

private:
    QSpinBox *_value;
};


class IntegerSizeParameter : public ParameterWidget
{
    Q_OBJECT

public:
    IntegerSizeParameter(const ParameterEntryPtr &parameter, QWidget *parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant &value) override;

private:
    QSpinBox *_a;
    QSpinBox *_b;
};


class IntegerPositionParameter : public ParameterWidget
{
    Q_OBJECT

public:
    IntegerPositionParameter(const ParameterEntryPtr &parameter, QWidget *parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant &value) override;

private:
    QSpinBox *_a;
    QSpinBox *_b;
};

