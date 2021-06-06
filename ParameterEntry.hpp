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


#include "ParameterType.hpp"

#include <QtCore/QString>
#include <QtCore/QVariantMap>
#include <QtCore/QSharedPointer>


class ParameterEntry;
using ParameterEntryPtr = QSharedPointer<ParameterEntry>;


/// One entry in the parameter definition.
///
class ParameterEntry
{
public:
    static ParameterEntryPtr create(
        ParameterType type,
        const QString &identifier,
        const QString &label,
        const QVariantMap &settings);

public:
    /// The parameter type.
    ///
    ParameterType type() const;

    /// The identifier of the parameter.
    ///
    QString identifier() const;

    /// The label for the parameter.
    ///
    QString label() const;

    /// Settings for the parameter.
    ///
    QVariantMap settings() const;

private:
    /// Create a new raw paremeter entry.
    ///
    ParameterEntry(
        ParameterType type,
        const QString &identifier,
        const QString &label,
        const QVariantMap &settings);

private:
    ParameterType _type;
    QString _identifier;
    QString _label;
    QVariantMap _settings;
};

