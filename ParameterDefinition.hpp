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

#include <QtCore/QSharedPointer>
#include <QtCore/QSize>
#include <QtCore/QPoint>


class ParameterDefinition;
using ParameterDefinitionPtr = QSharedPointer<ParameterDefinition>;
using ParameterDefinitionPtrConst = QSharedPointer<const ParameterDefinition>;


/// The definition of parameters, returned by a converter.
///
class ParameterDefinition
{
public:
    /// A parameter list.
    ///
    using ParameterList = QList<ParameterEntryPtr>;

public:
    /// Create a new parameter definition.
    ///
    static ParameterDefinitionPtr create();

public:
    /// Add a checkbox parameter.
    ///
    void addCheckbox(const QString &identifier, const QString &label, bool defaultValue);

    /// Add an integer parameter.
    ///
    void addInteger(const QString &identifier, const QString &label, int defaultValue, int minimum, int maximum);

    /// Add an integer size parameter.
    ///
    void addIntegerSize(const QString &identifier, const QString &label, QSize defaultValue, QSize minimum, QSize maximum);

    /// Add an integer position parameter.
    ///
    void addIntegerPosition(const QString &identifier, const QString &label, QPoint defaultValue, QPoint minimum, QPoint maximum);

    /// Get the parameter list.
    ///
    const ParameterList& parameterList() const;

private:
    ParameterDefinition();

private:
    ParameterList _parameterList; ///< The list with all parameters.
};

