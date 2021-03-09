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


#include <QtWidgets/QMainWindow>


class Converter;
class QPlainTextEdit;
class QComboBox;
class QLabel;
class BitmapPanel;


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
    void updateBitmapInfo();

    /// Update the code.
    ///
    void updateCode();

private Q_SLOTS:
    /// Load a bitmap.
    ///
    void onLoadBitmap();

protected: // Implement QWidget
    void closeEvent(QCloseEvent *event) override;

private:
    QComboBox *_formatSelector; ///< The format selector.
    QPlainTextEdit *_codePreview; ///< The generated code.
    BitmapPanel *_bitmapPanel; ///< The bitmap panel.
    QImage _currentImage; ///< The current loaded image
    QLabel *_bitmapInfo; ///< The label with the image info.
    QList<Converter*> _converterList; ///< A list of available converters.
};

