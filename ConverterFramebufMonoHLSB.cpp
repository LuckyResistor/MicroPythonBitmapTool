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
#include "ConverterFramebufMonoHLSB.hpp"


#include <QtCore/QTextStream>


ConverterFramebufMonoHLSB::ConverterFramebufMonoHLSB()
    : ConverterFramebufMono("MicroPython Framebuf Mono HLSB", UnitOrientation::Horizontal, BitDirection::LSB, 8)
{
}


QString ConverterFramebufMonoHLSB::generateCode(const QImage &image, const QVariantMap&) const
{
    QByteArray data;
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); x += 8) {
            data.append(static_cast<uint8_t>(readUnit(x, y, 1, 0, 8, image)));
        }
    }
    return createCode(data, generatedSize(image.size()), "MONO_HLSB");
}
