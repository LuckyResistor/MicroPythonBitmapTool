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


/// The base class for all font converters.
///
class FontConverter : public Converter
{
public:
    /// ctor
    ///
    FontConverter(const QString &displayName);

public: // implement Converter
    Mode mode() const override;
    ParameterDefinitionPtr createParameterDefinition() const override;

public:
    /// Create a bitmap for a given character.
    ///
    /// This method should return the given character in exact the size and format it will
    /// be converted as bitmap.
    ///
    /// @param font The font for the character.
    /// @param c The character to convert.
    /// @param parameter The current map of parameters.
    ///
    virtual QImage generateImage(const QFont &font, QChar c, const QVariantMap &parameter) const;

    /// Generate the code from the given font.
    ///
    /// The string with all characters to convert is passed as parameter 'characters'.
    ///
    /// @param font The font to convert.
    /// @param parameter A map with parameters passed to this converter.
    /// @return The generated code.
    ///
    virtual QString generateCode(const QFont &font, const QVariantMap &parameter) const = 0;
};

