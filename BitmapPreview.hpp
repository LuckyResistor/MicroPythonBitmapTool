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


#include "OverlayMode.hpp"

#include <QtWidgets/QWidget>
#include <QtGui/QImage>
#include <QtGui/QPixmap>


class Converter;


/// Preview the bitmap.
///
class BitmapPreview : public QWidget
{
    Q_OBJECT

public:
    explicit BitmapPreview(QWidget *parent = nullptr);

public:
    /// Assign a new image.
    ///
    void setImage(const QImage &image);

    /// Set the overlay mode.
    ///
    void setOverlayMode(OverlayMode overlayMode);

    /// Set the current converter.
    ///
    void setConverter(const Converter *converter);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected: // QWidget interface
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    /// Recalculate all sizes
    ///
    void recalculate();

    /// Set the generated image size.
    ///
    void setGeneratedSize(const QSize &size);

private:
    QImage _image; ///< The current image.
    QSize _generatedSize; ///< The generated image size.
    QPixmap _pixmap; ///< QPixmap representation of the image.
    int _displayFactor; ///< The display factor.
    QSize _minimumSize; ///< The preferred size of this widget.
    OverlayMode _overlayMode; ///< The overlay mode.
    const Converter *_converter; ///< The current converter.
};

