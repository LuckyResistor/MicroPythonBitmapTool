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
#include "ParameterDefinition.hpp"


ParameterDefinitionPtr ParameterDefinition::create()
{
    return ParameterDefinitionPtr(new ParameterDefinition());
}


void ParameterDefinition::addCheckbox(
    const QString &identifier,
    const QString &label,
    bool defaultValue)
{
    QVariantMap settings;
    settings["default"] = defaultValue;
    _parameterList.append(ParameterEntry::create(
        ParameterType::Checkbox, identifier, label, settings));
}


void ParameterDefinition::addInteger(
    const QString &identifier,
    const QString &label,
    int defaultValue,
    int minimum,
    int maximum)
{
    QVariantMap settings;
    settings["default"] = defaultValue;
    settings["minimum"] = minimum;
    settings["maximum"] = maximum;
    _parameterList.append(ParameterEntry::create(ParameterType::IntegerValue, identifier, label, settings));
}


void ParameterDefinition::addIntegerSize(const QString &identifier, const QString &label, QSize defaultValue, QSize minimum, QSize maximum)
{
    QVariantMap settings;
    settings["default"] = defaultValue;
    settings["minimum"] = minimum;
    settings["maximum"] = maximum;
    _parameterList.append(ParameterEntry::create(ParameterType::IntegerSize, identifier, label, settings));
}


void ParameterDefinition::addIntegerPosition(const QString &identifier, const QString &label, QPoint defaultValue, QPoint minimum, QPoint maximum)
{
    QVariantMap settings;
    settings["default"] = defaultValue;
    settings["minimum"] = minimum;
    settings["maximum"] = maximum;
    _parameterList.append(ParameterEntry::create(ParameterType::IntegerPosition, identifier, label, settings));
}


const ParameterDefinition::ParameterList &ParameterDefinition::parameterList() const
{
    return _parameterList;
}


ParameterDefinition::ParameterDefinition()
{
}
