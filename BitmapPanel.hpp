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


class BitmapPanel : public QWidget
{
    Q_OBJECT

public:
    explicit BitmapPanel(QWidget *parent = nullptr);

public:
    /// Assign a new image.
    ///
    void setImage(const QImage &image);

    /// Set the current converter.
    ///
    void setConverter(const Converter *converter);

private:
    void initializeUi();

private:
    BitmapPreview *_bitmapPreview; ///< The bitmap preview;
    QComboBox *_overlaySelector; ///< The selector for the overlays.
};

