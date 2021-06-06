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
#include "ApplicationController.hpp"


ApplicationController *ApplicationController::_instance = nullptr;


ApplicationController::ApplicationController(QObject *parent)
    : QObject(parent)
{
    _instance = this;

    // Start as soon the main loop is running.
    QMetaObject::invokeMethod(this, &ApplicationController::start, Qt::QueuedConnection);
}


QFont ApplicationController::monospaceFont() const
{
    QFont monospaceFont;
#ifdef Q_OS_WIN32
    monospaceFont = QFont("Consolas", 12);
#else
#ifdef Q_OS_MAC
    monospaceFont = QFont("Menlo", 12);
#else
    monospaceFont = QFont("Lucida Console", 12);
#endif
#endif
    return monospaceFont;
}


void ApplicationController::start()
{
    _mainWindow = new MainWindow();
    _mainWindow->show();
}


ApplicationController *ApplicationController::instance()
{
    return _instance;
}


ApplicationController* gApp()
{
    return ApplicationController::instance();
}


