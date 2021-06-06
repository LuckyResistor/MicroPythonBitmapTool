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


#include "LegendData.hpp"
#include "OverlayPainter.hpp"
#include "OverlayMode.hpp"
#include "ParameterDefinition.hpp"

#include <QtGui/QImage>
#include <QtCore/QObject>
#include <QtCore/QString>


/// Base class for all converters
///
class Converter
{
public:
    enum class Mode {
        Bitmap,
        Font
    };

public:
    /// Create a new converter.
    ///
    /// @param displayName The name displayed in the UI for this coonverter.
    /// @param mode The converter mode.
    ///
    Converter(const QString &displayName);

    /// dtor
    ///
    virtual ~Converter() = default;

public:
    /// Get the display name for the converter.
    ///
    QString displayName() const;

    /// Get the mode for this converter.
    ///
    virtual Mode mode() const = 0;

public:
    /// Return the size of the generated bitmap data.
    ///
    /// @param imageSize The size of the image.
    /// @return The size of the generated bitmap data.
    ///
    virtual QSize generatedSize(const QSize &imageSize, const QVariantMap &parameter) const;

    /// Create the parameter definition for the converter.
    ///
    virtual ParameterDefinitionPtr createParameterDefinition() const;

    /// Return a legend for the bitmap preview.
    ///
    virtual LegendDataPtr legendData(OverlayMode mode) const;

    /// Draw the bitmap overlay.
    ///
    /// @param p The painter.
    /// @param mode The overlay mode (never `None`).
    /// @param image The image.
    /// @param parameter The current set of parameter.
    ///
    virtual void paintOverlay(OverlayPainter &p, OverlayMode mode, const QImage &image, const QVariantMap &parameter) const;

protected:
    /// The color for the image frame.
    ///
    static constexpr QColor colorBitmapSizeOriginal = QColor(64, 64, 255);

    /// The color for the generated frame.
    ///
    static constexpr QColor colorBitmapSizeGenerated = QColor(128, 128, 255);

private:
    QString _displayName; ///< The displayed name.
};

