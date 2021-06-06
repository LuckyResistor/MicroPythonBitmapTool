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
#include "FontConverter.hpp"


FontConverter::FontConverter(const QString &displayName)
    : Converter(displayName)
{
}


Converter::Mode FontConverter::mode() const
{
    return Mode::Font;
}


ParameterDefinitionPtr FontConverter::createParameterDefinition() const
{
    auto pd = Converter::createParameterDefinition();
    pd->addIntegerSize("maximumSize", QObject::tr("Maximum Size"),
                       QSize(12, 16), QSize(8, 8), QSize(256, 256));
    pd->addIntegerPosition("charOffset", QObject::tr("Char Offset"),
                       QPoint(0, 0), QPoint(-256, -256), QPoint(256, 256));
    pd->addCheckbox("convertMono", QObject::tr("Convert to Mono"), false);
    pd->addInteger("convertMonoThreshold", QObject::tr("Conversion Threshold"), 128, 0, 255);
    pd->addCheckbox("preferBitmapFont", QObject::tr("Prefer Bitmap Font"), false);
    pd->addCheckbox("noAntialiasFont", QObject::tr("No Antialias Font"), false);
    pd->addCheckbox("trimLeft", QObject::tr("Trim Left Side"), true);
    pd->addCheckbox("trimRight", QObject::tr("Trim Right Side"), true);
    pd->addCheckbox("invertFont", QObject::tr("Invert the Font"), false);
    return pd;
}


QImage FontConverter::generateImage(const QFont &font, QChar c, const QVariantMap &parameter) const
{
    auto maximumSize = parameter["maximumSize"].toSize();
    if (!maximumSize.isValid() || maximumSize.isNull()) {
        maximumSize = QSize(8, 8);
    }
    const auto charOffset = parameter["charOffset"].toPoint();
    QImage result(maximumSize, QImage::Format_ARGB32_Premultiplied);
    result.setDevicePixelRatio(1.0);
    QPainter p;
    p.begin(&result);
    p.fillRect(result.rect(), Qt::white);
    p.setRenderHint(QPainter::TextAntialiasing, false);
    auto fontForDrawing = font;
    int fontStyleStrategy = 0;
    if (parameter["preferBitmapFont"].toBool()) {
        fontStyleStrategy |= QFont::PreferBitmap;
    }
    if (parameter["noAntialiasFont"].toBool()) {
        fontStyleStrategy |= QFont::NoAntialias;
    }
    fontStyleStrategy |= QFont::NoSubpixelAntialias;
    fontForDrawing.setStyleStrategy(static_cast<QFont::StyleStrategy>(fontStyleStrategy));
    QFontMetrics fontMetrics(fontForDrawing);
    auto charBoundingRect = fontMetrics.boundingRect(c);
    // Make sure the first pixel is in the bitmap, draw baseline at ascent.
    QPoint targetPoint(-charBoundingRect.left(), fontMetrics.ascent());
    targetPoint += charOffset;
    p.setFont(fontForDrawing);
    p.drawText(targetPoint, QString(c));
    p.end();
    // Postprocess the font.
    const auto threshold = static_cast<unsigned int>(parameter["convertMonoThreshold"].toInt());
    if (parameter["convertMono"].toBool()) {
        for (int x = 0; x < result.width(); ++x) {
            for (int y = 0; y < result.height(); ++y) {
                const auto pixel = result.pixel(x, y);
                if ((pixel & 0xff) <= threshold) {
                    result.setPixel(x, y, qRgb(0, 0, 0));
                } else {
                    result.setPixel(x, y, qRgb(255, 255, 255));
                }
            }
        }
    }
    // Trim the font.
    const auto trimLeft = parameter["trimLeft"].toBool();
    const auto trimRight = parameter["trimRight"].toBool();
    if (trimLeft || trimRight) {
        auto resultRect = result.rect();
        int leftTrim = 0;
        int rightTrim = 0;
        if (trimLeft) {
            for (int x = 0; x < result.width(); ++x) {
                bool hasPixelSet = false;
                for (int y = 0; y < result.height(); ++y) {
                    const auto pixel = result.pixel(x, y);
                    if ((pixel & 0xff) <= threshold) {
                        hasPixelSet = true;
                        break;
                    }
                }
                if (hasPixelSet) {
                    break;
                }
                leftTrim += 1;
            }
        }
        if (trimRight) {
            for (int x = result.width()-1; x >= 0; --x) {
                bool hasPixelSet = false;
                for (int y = 0; y < result.width(); ++y) {
                    const auto pixel = result.pixel(x, y);
                    if ((pixel & 0xff) <= threshold) {
                        hasPixelSet = true;
                        break;
                    }
                }
                if (hasPixelSet) {
                    break;
                }
                rightTrim += 1;
            }
        }
        if ((resultRect.width() - leftTrim - rightTrim) <= 0) {
            // The font image is empty, use one pixel line.
            resultRect.setWidth(1);
        } else {
            resultRect = resultRect.marginsRemoved(QMargins(leftTrim, 0, rightTrim, 0));
        }
        if (resultRect != result.rect()) {
            result = result.copy(resultRect);
        }
    }
    // Invert the font.
    if (parameter["invertFont"].toBool()) {
        result.invertPixels();
    }
    return result;
}
