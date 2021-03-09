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
#include "BitmapPreview.hpp"


#include "Converter.hpp"
#include "OverlayPainter.hpp"

#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>


namespace {
const int cImagePadding = 32;
const int cMinimumDisplayFactor = 12;
const int cMinimumWidth = 400;
const int cMinimumHeight = 200;
}


BitmapPreview::BitmapPreview(QWidget *parent)
:
    QWidget(parent),
    _displayFactor(cMinimumDisplayFactor),
    _minimumSize(cMinimumWidth, cMinimumHeight),
    _overlayMode(OverlayMode::None),
    _converter(nullptr)
{
}


void BitmapPreview::setImage(const QImage &image)
{
    if (_image != image) {
        _image = image;
        _pixmap = QPixmap::fromImage(image);
        if (_converter != nullptr) {
            setGeneratedSize(_converter->generatedSize(_image.size()));
        }
        recalculate();
        update();
    }
}


void BitmapPreview::setGeneratedSize(const QSize &size)
{
    if (_generatedSize != size) {
        _generatedSize = size;
        recalculate();
        update();
    }
}


void BitmapPreview::setOverlayMode(OverlayMode overlayMode)
{
    if (_overlayMode != overlayMode) {
        _overlayMode = overlayMode;
        update();
    }
}


void BitmapPreview::setConverter(const Converter *converter)
{
    if (_converter != converter) {
        _converter = converter;
        if (_converter != nullptr) {
            setGeneratedSize(_converter->generatedSize(_image.size()));
        }
        update();
    }
}


QSize BitmapPreview::sizeHint() const
{
    return _minimumSize;
}


QSize BitmapPreview::minimumSizeHint() const
{
    return _minimumSize;
}


void BitmapPreview::paintEvent(QPaintEvent *pe)
{
    QPainter p(this);
    if (!_pixmap.isNull()) {
        qreal x = (width() - _minimumSize.width())/2 + cImagePadding;
        qreal y = (height() - _minimumSize.height())/2 + cImagePadding;
        qreal width = (_pixmap.width()*_displayFactor);
        qreal height = (_pixmap.height()*_displayFactor);
        p.fillRect(QRectF(x, y, width, height), Qt::white);
        p.drawPixmap(QRectF(x, y, width, height), _pixmap, _pixmap.rect());
        if (_converter != nullptr) {
            if (_overlayMode != OverlayMode::None) {
                p.setOpacity(0.75);
                p.fillRect(rect(), palette().window());
            }
            p.setOpacity(1.0);
            p.translate(x, y);
            OverlayPainter op(&p, pe->rect(), _displayFactor, _pixmap.size(), _generatedSize);
            _converter->paintOverlay(op, _overlayMode, _image);
        }
    } else {
        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, tr("No Bitmap Loaded"));
    }
}


void BitmapPreview::resizeEvent(QResizeEvent *e)
{
    recalculate();
    QWidget::resizeEvent(e);
}


void BitmapPreview::recalculate()
{
    if (_pixmap.isNull()) {
        _displayFactor = cMinimumDisplayFactor;
        _minimumSize = QSize(cMinimumWidth, cMinimumHeight);
    } else {
        auto calculationSize = _pixmap.size();
        if (_generatedSize.width() > calculationSize.width() || _generatedSize.height() > calculationSize.height()) {
            calculationSize = _generatedSize;
        }
        int factorX = qMax(cMinimumWidth / calculationSize.width(), cMinimumDisplayFactor);
        int factorY = qMax(cMinimumWidth / calculationSize.height(), cMinimumDisplayFactor);
        _displayFactor = qMin(factorX, factorY);
        _minimumSize = QSize(calculationSize.width()*_displayFactor, calculationSize.height()*_displayFactor)
                + QSize(cImagePadding*2, cImagePadding*2);
    }
}


