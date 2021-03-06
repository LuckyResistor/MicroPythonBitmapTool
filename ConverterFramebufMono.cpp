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
#include "ConverterFramebufMono.hpp"



ConverterFramebufMono::ConverterFramebufMono(
    const QString &displayName,
    UnitOrientation unitOrientation,
    BitDirection bitDirection,
    int unitSize)
:
    ConverterFramebuf(displayName),
    MonoTools(unitOrientation, bitDirection, unitSize)
{
}


QSize ConverterFramebufMono::generatedSize(const QSize &imageSize, const QVariantMap &parameter) const
{
    return monoGeneratedSize(imageSize, parameter);
}


LegendDataPtr ConverterFramebufMono::legendData(OverlayMode mode) const
{
    auto data = ConverterFramebuf::legendData(mode);
    addMonoLegendData(data, mode);
    return data;
}


void ConverterFramebufMono::paintOverlay(OverlayPainter &p, OverlayMode mode, const QImage &image, const QVariantMap &parameter) const
{
    ConverterFramebuf::paintOverlay(p, mode, image, parameter);
    monoPaintOverlay(p, mode, image, parameter);
}


