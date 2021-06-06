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


#include "Converter.hpp"


/// The base class for all bitmap converters.
///
class BitmapConverter : public Converter
{
public:
    /// ctor
    ///
    BitmapConverter(const QString &displayName);

public: // implement Converter
    Mode mode() const override;

public:
    /// Generate the code from the given image.
    ///
    /// @param image The image to convert.
    /// @param parameter A map with parameters passed to this converter.
    /// @return The generated code.
    ///
    virtual QString generateCode(const QImage &image, const QVariantMap &parameter) const = 0;
};


