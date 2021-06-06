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


#include <QtWidgets/QWidget>


class BitmapPreview;
class Converter;
class QComboBox;
class QFrame;


/// A panel with the scrollable bitmap preview.
///
class BitmapPanel : public QWidget
{
    Q_OBJECT

public:
    /// Create the panel.
    ///
    explicit BitmapPanel(QWidget *parent = nullptr);

public:
    /// Assign a new image.
    ///
    void setImage(const QImage &image);

    /// Set the current converter.
    ///
    void setConverter(const Converter *converter);

    /// Set the current character set.
    ///
    void setCharacters(const QString &characters);

    /// Set the current parameter.
    ///
    void setParameter(const QVariantMap &parameter);

    /// Get the current selected character
    ///
    QChar selectedCharacter() const;

private:
    /// Initialize all UI elements.
    ///
    void initializeUi();

Q_SIGNALS:
    /// Emitted if the selected character changes.
    ///
    void selectedCharacterChanged(QChar c);

private:
    const Converter *_converter; ///< The current converter.
    QString _characters; ///< The list of characters to convert.
    BitmapPreview *_bitmapPreview; ///< The bitmap preview;
    QFrame *_fontConversionTools; ///< The area with tools for font conversion.
    QComboBox *_characterSelector; ///< The selector for a single character.
    QComboBox *_overlaySelector; ///< The selector for the overlays.
};

