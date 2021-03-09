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


#include <QtGui/QColor>
#include <QtCore/QString>


/// A entry in the legend data.
///
class LegendEntry
{
public:
    enum Identifier : int {
        BitmapSize = 0,
        BitAssignment = 1,
        ReadDirection = 2,
    };

public:
    LegendEntry(const QColor &color, const QString &text);
    LegendEntry(const QColor &color1, const QColor &color2, const QString &text);

public:
    QColor color1() const;
    QColor color2() const;
    QString text() const;

private:
    QColor _color1;
    QColor _color2;
    QString _text;
};

