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


#include "ParameterDefinition.hpp"
#include "ParameterFactory.hpp"

#include <QtCore/QVariantMap>
#include <QtWidgets/QMainWindow>


class Converter;
class QPlainTextEdit;
class QComboBox;
class QLabel;
class BitmapPanel;
class QFrame;
class QFontComboBox;
class QLineEdit;
class QSpinBox;
class QFormLayout;


/// The main widnow
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    /// Initialize the converter list
    ///
    void initializeConverterList();

    /// Initialize the user interface.
    ///
    void initializeUi();

    /// Initialize the menu
    ///
    void initializeMenu();

    /// Load all settings
    ///
    void loadSettings();

    /// Save all settings.
    ///
    void saveSettings();

    /// The current converter.
    ///
    Converter* selectedConverter() const;

    /// Update the bitmap info.
    ///
    void updateInfoBox();

    /// Update the code.
    ///
    void updateCode();

    /// Update the parameter frame for the current converter.
    ///
    void updateParameters();

    /// Get the current parameters
    ///
    QVariantMap createParameterMap() const;

private Q_SLOTS:
    /// Load a bitmap.
    ///
    void onLoadBitmap();

    /// After a new converter is selected.
    ///
    void onFormatChanged();

    /// After a new font is selected.
    ///
    void onFontChanged();

    /// After the character list has changed
    ///
    void onCharactersChanged();

    /// If the selected character changed
    ///
    void onSelectedCharacterChanged(QChar c);

    /// After a parameter has changed.
    ///
    void onParameterChanged();

protected: // Implement QWidget
    void closeEvent(QCloseEvent *event) override;

private:
    ParameterFactory parameterFactory; ///< The parameter factory.

    QComboBox *_formatSelector; ///< The format selector.
    QPlainTextEdit *_codePreview; ///< The generated code.
    BitmapPanel *_bitmapPanel; ///< The bitmap panel.

    QFrame *_parameterFrame; ///< The frame with the parameters.
    QFormLayout *_parameterLayout; ///< The parameter layout.
    ParameterDefinitionPtr _displayedParameters; ///< The currently displayed parameters.

    QImage _currentImage; ///< The current loaded image for bitmap converters.
    QFont _currentFont; ///< The currently selected font for font converters.

    QFrame *_bitmapConverterFrame; ///< The frame for bitmap converters.
    QLabel *_bitmapInfo; ///< The label with the image info.

    QFrame *_fontConverterFrame; ///< The frame for font converters.
    QLabel *_fontInfo; ///< The label with the font info.
    QFontComboBox *_fontSelector; ///< The combo box to select a new font.
    QComboBox *_fontWeightSelector; ///< The selector for the font weight.
    QSpinBox *_fontSizeSelector; ///< The selector for the used font size.
    QComboBox *_fontHinting; ///< The hinting settings for the font.
    QPlainTextEdit *_fontCharacters; ///< The characters of the font to be converted.

    QList<Converter*> _converterList; ///< A list of available converters.
};

