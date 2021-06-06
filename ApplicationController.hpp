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


#include "MainWindow.hpp"

#include <QtCore/QObject>


/// The application controller
///
class ApplicationController : public QObject
{
    Q_OBJECT

public:
    /// ctor
    ///
    explicit ApplicationController(QObject *parent = nullptr);

public:
    /// Get the default monospaced font.
    ///
    QFont monospaceFont() const;

public:
    /// Get the global instance.
    ///
    static ApplicationController* instance();

private:
    /// Start the application.
    ///
    Q_SLOT void start();

private:
    static ApplicationController *_instance; ///< The controller instance.
    MainWindow *_mainWindow; ///< The main window.
};


ApplicationController* gApp();
