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
#include "LegendEntry.hpp"


LegendEntry::LegendEntry(const QColor &color, const QString &text)
    : _color1(color), _text(text)
{
}


LegendEntry::LegendEntry(const QColor &color1, const QColor &color2, const QString &text)
    : _color1(color1), _color2(color2), _text(text)
{
}


QColor LegendEntry::color1() const
{
    return _color1;
}


QColor LegendEntry::color2() const
{
    return _color2;
}


QString LegendEntry::text() const
{
    return _text;
}

