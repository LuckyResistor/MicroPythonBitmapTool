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
#include "ParameterFactory.hpp"


ParameterFactory::ParameterFactory()
{
}


ParameterWidget *ParameterFactory::createWidget(const ParameterEntryPtr &parameter) const
{
    switch (parameter->type()) {
    case ParameterType::Checkbox:
        return new CheckBoxParameter(parameter);
    case ParameterType::IntegerValue:
        return new IntegerParameter(parameter);
    case ParameterType::IntegerSize:
        return new IntegerSizeParameter(parameter);
    case ParameterType::IntegerPosition:
        return new IntegerPositionParameter(parameter);
     default:
        break;
    }
    return nullptr;
}
