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
#include <QtCore/QSharedPointer>


class LegendEntry;


class LegendData;
using LegendDataPtr = QSharedPointer<LegendData>;


/// Legend data.
///
class LegendData
{
public:
    /// Create a new legend data object.
    ///
    static LegendDataPtr create();

private:
    /// private ctor
    ///
    LegendData() = default;

public:
    /// dtor
    ///
    ~LegendData();

public:
    /// Add a new entry to the legend.
    ///
    /// @param color The color.
    /// @param text The text for the entry.
    ///
    void addEntry(const QColor &color, const QString &text);

    /// Add a new entry to the legend.
    ///
    /// @param color1 The first color.
    /// @param color2 The second color.
    /// @param text The text for the entry.
    ///
    void addEntry(const QColor &color1, const QColor &color2, const QString &text);

    /// Get the list with all entries.
    ///
    const QList<const LegendEntry*>& entryList() const;

private:
    QList<const LegendEntry*> _entryList; ///< The list with all entries.
};



