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
#include "OverlayPainter.hpp"


OverlayPainter::OverlayPainter(
    QPainter *painter,
    const QRect &updateRect,
    int displayFactor,
    const QSize &imageSize,
    const QSize &generatedSize)
:
    _p(painter),
    _updateRect(updateRect),
    _displayFactor(displayFactor),
    _imageSize(imageSize),
    _generatedSize(generatedSize)
{
#ifdef Q_OS_WIN32
    _pixelFont = QFont("Consolas");
#else
#ifdef Q_OS_MAC
    _pixelFont = QFont("Menlo");
#else
    _pixelFont = QFont("Lucida Console");
#endif
#endif
    _pixelFont.setPixelSize(displayFactor - 1);
    _p->setFont(_pixelFont);
}


void OverlayPainter::drawPixelOutline(const QRect &rect, const QColor &outlineColor, int outlineWidth, int offset)
{
    _p->setBrush(QBrush());
    _p->setPen(QPen(outlineColor, outlineWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    const qreal offset1 = static_cast<qreal>(outlineWidth)/2 - static_cast<qreal>(offset);
    const qreal offset2 = -static_cast<qreal>(outlineWidth)/2 + static_cast<qreal>(offset);
    const auto rectToDraw = pixelRectF(rect).adjusted(offset1, offset1, offset2, offset2);
    _p->drawRect(rectToDraw);
}


void OverlayPainter::drawPixelText(const QRect &rect, const QColor &textColor, const QString &text)
{
    _p->setBrush(QBrush());
    _p->setPen(QPen(textColor));
    _p->drawText(pixelRectF(rect), Qt::AlignCenter, text);
}


bool OverlayPainter::arePixelUpdated(const QRect &rect) const
{
    const auto rectToDraw = pixelRectF(rect).adjusted(-64, -64, 64, 64);
    return rectToDraw.intersects(_updateRect);
}

