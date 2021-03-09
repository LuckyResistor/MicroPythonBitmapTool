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
#include "BitmapPanel.hpp"


#include "Converter.hpp"
#include "BitmapPreview.hpp"

#include <QComboBox>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>


BitmapPanel::BitmapPanel(QWidget *parent) : QWidget(parent)
{
    initializeUi();
}


void BitmapPanel::setImage(const QImage &image)
{
    _bitmapPreview->setImage(image);
}


void BitmapPanel::setConverter(const Converter *converter)
{
    _bitmapPreview->setConverter(converter);
    _bitmapPreview->setFixedSize(_bitmapPreview->sizeHint());
}


void BitmapPanel::initializeUi()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumHeight(300);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 4);
    mainLayout->setSpacing(4);
    mainLayout->addWidget(new QLabel(tr("Loaded Bitmap:")));

    auto scrollArea = new QScrollArea();
    QPalette imagePalette = palette();
    imagePalette.setColor(QPalette::Window, QColor::fromRgb(32, 32, 32));
    scrollArea->setPalette(imagePalette);
    scrollArea->setBackgroundRole(QPalette::Window);
    mainLayout->addWidget(scrollArea);

    _bitmapPreview = new BitmapPreview();
    _bitmapPreview->setFixedSize(_bitmapPreview->sizeHint());
    _bitmapPreview->setPalette(imagePalette);
    scrollArea->setWidget(_bitmapPreview);
    scrollArea->setAlignment(Qt::AlignCenter);

    auto previewSettingsPanel = new QFrame();
    auto previewSettingsLayout = new QHBoxLayout(previewSettingsPanel);
    previewSettingsLayout->setContentsMargins(0, 0, 0, 0);
    previewSettingsLayout->setSpacing(4);
    previewSettingsLayout->addStretch();
    previewSettingsLayout->addWidget(new QLabel(tr("Overlay Mode:")));
    _overlaySelector = new QComboBox();
    _overlaySelector->addItem(tr("None"), static_cast<int>(OverlayMode::None));
    _overlaySelector->addItem(tr("Bit Assignments"), static_cast<int>(OverlayMode::BitAssigments));
    _overlaySelector->addItem(tr("Pixel Interpretation"), static_cast<int>(OverlayMode::PixelInterpretation));
    _overlaySelector->setCurrentIndex(0);
    previewSettingsLayout->addWidget(_overlaySelector);
    mainLayout->addWidget(previewSettingsPanel);

    connect(_overlaySelector, &QComboBox::currentIndexChanged, [=]{
        _bitmapPreview->setOverlayMode(static_cast<OverlayMode>(_overlaySelector->currentData().toInt()));
    });
}


