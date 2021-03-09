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


#include "ConverterFramebuf.hpp"


/// The base class of all mono converters
///
class ConverterFramebufMono : public ConverterFramebuf
{
protected:
    enum class UnitOrientation {
        Horizontal,
        Vertical
    };

    enum class BitDirection {
        LSB,
        MSB
    };

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
    QSize generatedSize(const QSize &imageSize) const override;
    LegendDataPtr legendData(OverlayMode mode) const override;
    void paintOverlay(OverlayPainter &p, OverlayMode mode, const QImage &image) const override;

protected:
    /// Interpret a single pixel.
    ///
    /// Returns `false` if the pixel is out of bounds.
    ///
    static bool getPixel(int x, int y, const QImage &image);

    /// Read a single unit.
    ///
    static uint32_t readUnit(int x, int y, int dx, int dy, int count, const QImage &image);

    /// The colors for the bit assignments
    ///
    static constexpr QColor colorBitAssignment1 = QColor(240, 40, 40);
    static constexpr QColor colorBitAssignment2 = QColor(240, 80, 80);
    static constexpr QColor colorPixelInterpretation = QColor(240, 240, 40);

protected:
    UnitOrientation _unitOrientation; ///< The unit orientatioon.
    BitDirection _bitDirection; ///< The bit direction.
    int _unitSize; ///< The number of bits per unit.
};

