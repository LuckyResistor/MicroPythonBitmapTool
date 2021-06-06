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
#include "FontConverterFramebufMono.hpp"


FontConverterFramebufMono::FontConverterFramebufMono()
:
    FontConverter("MicroPython Font Mono VLSB"),
    MonoTools(UnitOrientation::Vertical, BitDirection::LSB, 8)
{
}


QSize FontConverterFramebufMono::generatedSize(const QSize &imageSize, const QVariantMap &parameter) const
{
    return monoGeneratedSize(imageSize, parameter);
}


QString FontConverterFramebufMono::generateCode(const QFont&, const QVariantMap&) const
{
    return "The generated format is not decided yet.";
}


LegendDataPtr FontConverterFramebufMono::legendData(OverlayMode mode) const
{
    auto data = FontConverter::legendData(mode);
    addMonoLegendData(data, mode);
    return data;
}


void FontConverterFramebufMono::paintOverlay(OverlayPainter &p, OverlayMode mode, const QImage &image, const QVariantMap &parameter) const
{
    FontConverter::paintOverlay(p, mode, image, parameter);
    monoPaintOverlay(p, mode, image, parameter);
}
