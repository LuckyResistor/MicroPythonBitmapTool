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


#include "MonoTools.hpp"
#include "ConverterFramebuf.hpp"


/// The base class of all mono converters
///
class ConverterFramebufMono : public ConverterFramebuf, public MonoTools
{
public:
    /// Create a new mono converter.
    ///
    /// @param displayName The display name.
    /// @param unitOrientation The unit direction.
    /// @param unitSize The number of bits per unit.
    ///
    ConverterFramebufMono(
        const QString &displayName,
        UnitOrientation unitOrientation,
        BitDirection bitDirection,
        int unitSize);

public: // Converter interface
    QSize generatedSize(const QSize &imageSize, const QVariantMap &parameter) const override;
    LegendDataPtr legendData(OverlayMode mode) const override;
    void paintOverlay(OverlayPainter &p, OverlayMode mode, const QImage &image, const QVariantMap &parameter) const override;
};

