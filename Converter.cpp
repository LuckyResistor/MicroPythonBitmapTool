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
#include "Converter.hpp"


Converter::Converter(const QString &displayName)
    : _displayName(displayName)
{
}


QString Converter::displayName() const
{
    return _displayName;
}


QSize Converter::generatedSize(const QSize &imageSize, const QVariantMap&) const
{
    return imageSize;
}


ParameterDefinitionPtr Converter::createParameterDefinition() const
{
    return ParameterDefinition::create();
}


LegendDataPtr Converter::legendData(OverlayMode) const
{
    auto ld = LegendData::create();
    ld->addEntry(colorBitmapSizeOriginal, colorBitmapSizeGenerated, QObject::tr("Bitmap Size Original/Generated"));
    return ld;
}


void Converter::paintOverlay(OverlayPainter &op, OverlayMode, const QImage&, const QVariantMap&) const
{
    op.drawPixelOutline(op.imageRect(), colorBitmapSizeOriginal, 1, 2);
    if (op.generatedSize().isValid() && !op.generatedSize().isEmpty()) {
        op.drawPixelOutline(op.generatedRect(), colorBitmapSizeGenerated, 1, 2);
    }
}

