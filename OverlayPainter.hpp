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


#include <QtGui/QPainter>


/// The overlay painter.
///
class OverlayPainter
{
public:
    /// ctor
    ///
    OverlayPainter(
        QPainter *painter,
        const QRect &updateRect,
        int displayFactor,
        const QSize &imageSize,
        const QSize &generatedSize);

public:
    /// Access the painter.
    ///
    inline QPainter *painter() const { return _p; };

    /// Access the display factor.
    ///
    inline int displayFactor() const { return _displayFactor; };

    /// Access the image size.
    ///
    inline const QSize& imageSize() const { return _imageSize; }

    /// Access the generated size.
    ///
    inline const QSize& generatedSize() const { return _generatedSize; }

    /// Access the image rect.
    ///
    inline const QRect imageRect() const { return QRect(QPoint(0, 0), imageSize()); }

    /// Access the generated rect
    ///
    inline const QRect generatedRect() const { return QRect(QPoint(0, 0), generatedSize()); }

    /// Get a rectangle for a pixal area.
    ///
    inline QRectF pixelRectF(int x, int y, int width, int height) const {
        return QRectF(x * _displayFactor, y * _displayFactor, width * _displayFactor, height * _displayFactor);
    }

    /// Get a rectangle for a pixel rect.
    ///
    inline QRectF pixelRectF(const QRect &rect) const {
        return pixelRectF(rect.x(), rect.y(), rect.width(), rect.height());
    }

    /// Draw a outline around a pixel area.
    ///
    /// @param rect The rect for the pixel area.
    /// @param outlineColor The color of the outline.
    /// @param outlineWidth THe width of the outline in pixels.
    /// @param offset The offset of the outline. +1 = around the area, 0 in the area.
    ///
    void drawPixelOutline(
        const QRect &rect,
        const QColor &outlineColor,
        int outlineWidth = 1,
        int offset = 0);

    /// Write text into a pixel area
    ///
    void drawPixelText(
        const QRect &rect,
        const QColor &textColor,
        const QString &text);

    /// Check if a pixel region ready for repaint.
    ///
    bool arePixelUpdated(const QRect &rect) const;

private:
    QPainter *_p; ///< The painter used.
    QRect _updateRect; ///< The update rect.
    int _displayFactor; ///< The display factor.
    QSize _imageSize; ///< The size of the image.
    QSize _generatedSize; ///< The generated size.
    QFont _pixelFont; ///< The font used to draw into the pixels.
};

