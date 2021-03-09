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
    _unitOrientation(unitOrientation),
    _bitDirection(bitDirection),
    _unitSize(unitSize)
{
}


QSize ConverterFramebufMono::generatedSize(const QSize &imageSize) const
{
    if (_unitOrientation == UnitOrientation::Vertical) {
        if ((imageSize.height() % _unitSize) != 0) {
            return QSize(imageSize.width(), ((imageSize.height()/_unitSize)+1)*_unitSize);
        } else {
            return imageSize;
        }
    } else {
        if ((imageSize.width() % _unitSize) != 0) {
            return QSize(((imageSize.width()/_unitSize)+1)*_unitSize, imageSize.height());
        } else {
            return imageSize;
        }
    }
}


LegendDataPtr ConverterFramebufMono::legendData(OverlayMode mode) const
{
    auto data = ConverterFramebuf::legendData(mode);
    if (mode == OverlayMode::BitAssigments) {
        data->addEntry(colorBitAssignment1, colorBitAssignment2, QObject::tr("Bit Assignment"));
    } else {
        data->addEntry(colorPixelInterpretation, QObject::tr("Pixel Interpretation"));
    }
    return data;
}


void ConverterFramebufMono::paintOverlay(OverlayPainter &p, OverlayMode mode, const QImage &image) const
{
    ConverterFramebuf::paintOverlay(p, mode, image);
    if (mode == OverlayMode::BitAssigments) {
        const auto bitL = (_bitDirection == BitDirection::LSB ? "0" : QString::number(_unitSize-1));
        const auto bitH = (_bitDirection == BitDirection::LSB ? QString::number(_unitSize-1) : "0");
        bool colorFlag = false;
        if (_unitOrientation == UnitOrientation::Vertical) {
            for (int y = 0; y < p.imageSize().height(); y += _unitSize) {
                for (int x = 0; x < p.imageSize().width(); ++x) {
                    QRect rect(x, y, 1, _unitSize);
                    if (p.arePixelUpdated(rect)) {
                        const auto color = colorFlag ? colorBitAssignment1 : colorBitAssignment2;
                        p.drawPixelOutline(rect, color, 1);
                        p.drawPixelText(QRect(x, y, 1, 1), color, bitL);
                        p.drawPixelText(QRect(x, y+_unitSize-1, 1, 1), color, bitH);
                    }
                    colorFlag = !colorFlag;
                }
                if (p.imageSize().width() % 2 == 0) {
                    colorFlag = !colorFlag;
                }
            }
        } else {
            for (int y = 0; y < p.imageSize().height(); ++y) {
                for (int x = 0; x < p.imageSize().width(); x += _unitSize) {
                    QRect rect(x, y, _unitSize, 1);
                    if (p.arePixelUpdated(rect)) {
                        const auto color = colorFlag ? colorBitAssignment1 : colorBitAssignment2;
                        p.drawPixelOutline(rect, color, 1);
                        p.drawPixelText(QRect(x, y, 1, 1), color, bitH);
                        p.drawPixelText(QRect(x+_unitSize-1, y, 1, 1), color, bitL);
                    }
                    colorFlag = !colorFlag;
                }
                if ((p.imageSize().width()/_unitSize) % 2 == 0) {
                    colorFlag = !colorFlag;
                }
            }
        }
    } else if (mode == OverlayMode::PixelInterpretation) {
        for (int y = 0; y < p.generatedSize().height(); ++y) {
            for (int x = 0; x < p.generatedSize().width(); ++x) {
                auto text = (getPixel(x, y, image) ? "1" : "0");
                const QRect rect(x, y, 1, 1);
                if (p.arePixelUpdated(rect)) {
                    p.drawPixelText(rect, colorPixelInterpretation, text);
                }
            }
        }
    }
}


bool ConverterFramebufMono::getPixel(int x, int y, const QImage &image)
{
    if (x < 0 || y < 0 || x >= image.width() || y >= image.height()) {
        return false;
    }
    auto color = image.pixelColor(x, y);
    float h, s, l, a;
    color.getHslF(&h, &s, &l, &a);
    if (a < 0.5) {
        return false;
    }
    return l < 0.5;
}


uint32_t ConverterFramebufMono::readUnit(int x, int y, int dx, int dy, int count, const QImage &image)
{
    uint32_t result = 0;
    for (int i = 0; i < count; ++i) {
        result <<= 1;
        if (getPixel(x, y, image)) {
            result |= 0b1;
        }
        x += dx;
        y += dy;
    }
    return result;
}


