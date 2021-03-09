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
#include "ConverterFramebufMonoVLSB.hpp"


ConverterFramebufMonoVLSB::ConverterFramebufMonoVLSB()
    : ConverterFramebufMono("MicroPython Framebuf Mono VLSB", UnitOrientation::Vertical, BitDirection::LSB, 8)
{
}


QString ConverterFramebufMonoVLSB::generateCode(const QImage &image, const QVariantMap&) const
{
    QByteArray data;
    for (int y = 0; y < image.height(); y += 8) {
        for (int x = 0; x < image.width(); ++x) {
            data.append(static_cast<uint8_t>(readUnit(x, y+7, 0, -1, 8, image)));
        }
    }
    return createCode(data, generatedSize(image.size()), "MONO_VLSB");
}

