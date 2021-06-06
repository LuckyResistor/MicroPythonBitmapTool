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


#include "ApplicationController.hpp"
#include "Converter.hpp"
#include "BitmapPreview.hpp"

#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>


BitmapPanel::BitmapPanel(QWidget *parent)
    : QWidget(parent), _converter(nullptr)
{
    initializeUi();
}


void BitmapPanel::setImage(const QImage &image)
{
    _bitmapPreview->setImage(image);
    _bitmapPreview->setFixedSize(_bitmapPreview->sizeHint());
}


void BitmapPanel::setConverter(const Converter *converter)
{
    if (_converter != converter) {
        _converter = converter;
        _bitmapPreview->setConverter(converter);
        _bitmapPreview->setFixedSize(_bitmapPreview->sizeHint());
        _characterSelector->setVisible(_converter->mode() == Converter::Mode::Font);
    }
}


void BitmapPanel::setCharacters(const QString &characters)
{
    if (_characters != characters) {
        _characters = characters;
        _characterSelector->clear();
       for (int i = 0; i < characters.size(); ++i) {
            const auto c = _characters.at(i);
            _characterSelector->addItem(QString("%1:  %2  0x%3").arg(i, 3, 10, QChar('0'))
                                        .arg(QString(c)).arg(c.unicode(), 4, 16, QChar('0')), c);
       }
       _characterSelector->setCurrentIndex(0);
    }
}


void BitmapPanel::setParameter(const QVariantMap &parameter)
{
    _bitmapPreview->setParameter(parameter);
    _bitmapPreview->setFixedSize(_bitmapPreview->sizeHint());
}


QChar BitmapPanel::selectedCharacter() const
{
    return _characterSelector->currentData().toChar();
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

    _fontConversionTools = new QFrame();
    auto fontConversionLayout = new QHBoxLayout(_fontConversionTools);
    fontConversionLayout->setContentsMargins(0, 0, 0, 0);
    fontConversionLayout->setSpacing(2);
    previewSettingsLayout->addWidget(_fontConversionTools);

    auto previousCharButton = new QPushButton("<");
    fontConversionLayout->addWidget(previousCharButton);
    _characterSelector = new QComboBox();
    _characterSelector->setFont(gApp()->monospaceFont());
    fontConversionLayout->addWidget(_characterSelector);
    auto nextCharButton = new QPushButton(">");
    fontConversionLayout->addWidget(nextCharButton);
    connect(_characterSelector, &QComboBox::currentIndexChanged, [=]{
        Q_EMIT selectedCharacterChanged(_characterSelector->currentData().toChar());
    });
    connect(previousCharButton, &QPushButton::clicked, [=]{
        auto currentIndex = _characterSelector->currentIndex();
        if (currentIndex > 0) {
            _characterSelector->setCurrentIndex(currentIndex - 1);
        }
    });
    connect(nextCharButton, &QPushButton::clicked, [=]{
        auto currentIndex = _characterSelector->currentIndex();
        if (currentIndex < (_characterSelector->count()-1)) {
            _characterSelector->setCurrentIndex(currentIndex + 1);
        }
    });
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


