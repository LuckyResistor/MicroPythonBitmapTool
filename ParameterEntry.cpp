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
#include "ParameterEntry.hpp"


ParameterEntryPtr ParameterEntry::create(
    ParameterType type,
    const QString &identifier,
    const QString &label,
    const QVariantMap &settings)
{
    return ParameterEntryPtr(new ParameterEntry(type, identifier, label, settings));
}


ParameterType ParameterEntry::type() const
{
    return _type;
}


QString ParameterEntry::identifier() const
{
    return _identifier;
}


QString ParameterEntry::label() const
{
    return _label;
}


QVariantMap ParameterEntry::settings() const
{
    return _settings;
}


ParameterEntry::ParameterEntry(
    ParameterType type,
    const QString &identifier,
    const QString &label,
    const QVariantMap &settings)
:
    _type(type),
    _identifier(identifier),
    _label(label),
    _settings(settings)
{
}
