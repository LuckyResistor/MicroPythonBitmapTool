QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += sdk_no_version_check

TARGET = "MicroPythonBitmapTool"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ApplicationController.cpp \
    BitmapConverter.cpp \
    BitmapPanel.cpp \
    BitmapPreview.cpp \
    Converter.cpp \
    ConverterFramebuf.cpp \
    ConverterFramebufMono.cpp \
    ConverterFramebufMonoHLSB.cpp \
    ConverterFramebufMonoHMSB.cpp \
    ConverterFramebufMonoVLSB.cpp \
    FontConverter.cpp \
    FontConverterFramebufMono.cpp \
    LegendData.cpp \
    LegendEntry.cpp \
    MonoTools.cpp \
    OverlayPainter.cpp \
    ParameterDefinition.cpp \
    ParameterEntry.cpp \
    ParameterFactory.cpp \
    ParameterWidget.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    ApplicationController.hpp \
    BitmapConverter.hpp \
    BitmapPanel.hpp \
    BitmapPreview.hpp \
    Converter.hpp \
    ConverterFramebuf.hpp \
    ConverterFramebufMono.hpp \
    ConverterFramebufMonoHLSB.hpp \
    ConverterFramebufMonoHMSB.hpp \
    ConverterFramebufMonoVLSB.hpp \
    FontConverter.hpp \
    FontConverterFramebufMono.hpp \
    LegendData.hpp \
    LegendEntry.hpp \
    MainWindow.hpp \
    MonoTools.hpp \
    OverlayMode.hpp \
    OverlayPainter.hpp \
    ParameterDefinition.hpp \
    ParameterEntry.hpp \
    ParameterFactory.hpp \
    ParameterType.hpp \
    ParameterWidget.hpp

RESOURCES += \
    data/data.qrc

macos:ICON = data/AppIcon.icns
win32:RC_ICONS = data/AppIcon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    data/application.css
