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


/// Base class of framebuf converters.
///
class ConverterFramebuf : public Converter
{
public:
    ConverterFramebuf(const QString &displayName);

protected:
    /// Create a framebuf code segment.
    ///
    /// @param data The byte data.
    /// @param size The buffer size.
    /// @param format The name of the format.
    ///
    static QString createCode(const QByteArray &data, const QSize &size, const QString &format);
};

