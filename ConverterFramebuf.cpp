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
#include "ConverterFramebuf.hpp"


#include <QtCore/QTextStream>


ConverterFramebuf::ConverterFramebuf(const QString &displayName)
    : Converter(displayName)
{
}


QString ConverterFramebuf::createCode(const QByteArray &data, const QSize &size, const QString &format)
{
    QString result;
    QTextStream ts(&result);
    ts << "fb = framebuf.FrameBuffer(bytearray(\n";
    for (int i = 0; i < data.size(); ++i) {
        if ((i & 0x1f) == 0) {
            if (i > 0) {
                ts << "'\n";
            }
            ts << "    b'";
        }
        ts << QString("\\x%1").arg(static_cast<uint32_t>(data.at(i))&0xff, 2, 16, QChar('0'));
    }
    ts << "'),\n";
    ts << "    " << size.width() << ", " << size.height() << ", framebuf." << format << ")\n";
    return result;
}
