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
#include "MainWindow.hpp"


#include "ApplicationController.hpp"
#include "BitmapPanel.hpp"
#include "ConverterFramebufMonoVLSB.hpp"
#include "ConverterFramebufMonoHLSB.hpp"
#include "ConverterFramebufMonoHMSB.hpp"
#include "FontConverterFramebufMono.hpp"

#include <QtCore/QSettings>
#include <QtGui/QAction>
#include <QtGui/QClipboard>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtGui/QDesktopServices>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initializeConverterList();
    initializeUi();
    initializeMenu();
    loadSettings();
    onFormatChanged();
    onFontChanged();
    onCharactersChanged();
}


MainWindow::~MainWindow()
{
}


void MainWindow::initializeConverterList()
{
    _converterList.append(new ConverterFramebufMonoVLSB());
    _converterList.append(new ConverterFramebufMonoHMSB());
    _converterList.append(new ConverterFramebufMonoHLSB());
    _converterList.append(new FontConverterFramebufMono());
}


void MainWindow::initializeUi()
{
    const int cFixedWidth = 400;

    setMinimumSize(800, 600);
    setWindowTitle(tr("MicroPython Bitmap Tool - V%1 - Lucky Resistor").arg(qApp->applicationVersion()));

    auto centralWidget = new QWidget();
    centralWidget->setObjectName("CentralWidget");
    setCentralWidget(centralWidget);

    auto mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto settingsPanel = new QFrame();
    settingsPanel->setObjectName("SettingsPanel");
    mainLayout->addWidget(settingsPanel);

    auto settingsLayout = new QVBoxLayout(settingsPanel);
    settingsLayout->setSpacing(4);

    auto logo = new QLabel();
    logo->setFixedSize(cFixedWidth, 100);
    logo->setPixmap(QPixmap(":/images/AppLogo.png"));
    logo->setAlignment(Qt::AlignCenter);
    settingsLayout->addWidget(logo);
    auto versionLabel = new QLabel(tr("<b>Version %1</b>").arg(qApp->applicationVersion()));
    versionLabel->setAlignment(Qt::AlignCenter);
    settingsLayout->addWidget(versionLabel);
    settingsLayout->addSpacing(16);

    settingsLayout->addWidget(new QLabel(tr("<b>Generated Format:</b>")));
    _formatSelector = new QComboBox();
    for (auto converter : _converterList) {
        _formatSelector->addItem(converter->displayName());
    }
    _formatSelector->setCurrentIndex(0);
    settingsLayout->addWidget(_formatSelector);

    settingsLayout->addWidget(new QLabel(tr("<b>Parameters:</b>")));

    auto parameterScroll = new QScrollArea();
    parameterScroll->setObjectName("ParameterScrollArea");
    _parameterFrame = new QFrame();
    _parameterFrame->setObjectName("ParameterFrame");
    _parameterFrame->setFixedWidth(cFixedWidth);
    _parameterLayout = new QFormLayout(_parameterFrame);
    _parameterLayout->setContentsMargins(8, 8, 8, 8);
    parameterScroll->setWidget(_parameterFrame);
    parameterScroll->setWidgetResizable(true);
    parameterScroll->setFixedWidth(cFixedWidth);
    parameterScroll->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    //parameterScroll->setBackgroundRole(QPalette::Window);
    settingsLayout->addWidget(parameterScroll);

    _bitmapConverterFrame = new QFrame();
    auto bitmapConverterLayout = new QVBoxLayout(_bitmapConverterFrame);
    bitmapConverterLayout->setContentsMargins(0, 0, 0, 0);
    bitmapConverterLayout->setSpacing(4);
    settingsLayout->addWidget(_bitmapConverterFrame);

    bitmapConverterLayout->addWidget(new QLabel(tr("<b>Loaded Bitmap Info:</b>")));
    _bitmapInfo = new QLabel(tr("No Bitmap Loaded"));
    _bitmapInfo->setObjectName("BitmapInfo");
    _bitmapInfo->setMinimumHeight(100);
    _bitmapInfo->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    bitmapConverterLayout->addWidget(_bitmapInfo);

    auto loadButton = new QPushButton();
    loadButton->setText(tr("Load Bitmap"));
    bitmapConverterLayout->addWidget(loadButton);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadBitmap);

    _fontConverterFrame = new QFrame();
    auto fontConverterLayout = new QVBoxLayout(_fontConverterFrame);
    fontConverterLayout->setContentsMargins(0, 0, 0, 0);
    fontConverterLayout->setSpacing(4);
    settingsLayout->addWidget(_fontConverterFrame);

    fontConverterLayout->addWidget(new QLabel(tr("<b>Selected Font Info:</b>")));
    _fontInfo = new QLabel(tr("No Font Seleccted"));
    _fontInfo->setObjectName("FontInfo");
    _fontInfo->setMinimumHeight(100);
    _fontInfo->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    fontConverterLayout->addWidget(_fontInfo);

    fontConverterLayout->addWidget(new QLabel(tr("<b>Selected Font:</b>")));
    _fontSelector = new QFontComboBox();
    fontConverterLayout->addWidget(_fontSelector);
    auto fontDetailsLayout = new QHBoxLayout();
    fontDetailsLayout->setContentsMargins(0, 0, 0, 0);
    fontDetailsLayout->setSpacing(4);
    fontConverterLayout->addLayout(fontDetailsLayout);
    _fontWeightSelector = new QComboBox();
    _fontWeightSelector->addItem(tr("Thin"), static_cast<int>(QFont::Thin));
    _fontWeightSelector->addItem(tr("Extra Light"), static_cast<int>(QFont::ExtraLight));
    _fontWeightSelector->addItem(tr("Light"), static_cast<int>(QFont::Light));
    _fontWeightSelector->addItem(tr("Normal"), static_cast<int>(QFont::Normal));
    _fontWeightSelector->addItem(tr("Medium"), static_cast<int>(QFont::Medium));
    _fontWeightSelector->addItem(tr("Demi Bold"), static_cast<int>(QFont::DemiBold));
    _fontWeightSelector->addItem(tr("Bold"), static_cast<int>(QFont::Bold));
    _fontWeightSelector->addItem(tr("Extra Bold"), static_cast<int>(QFont::ExtraBold));
    _fontWeightSelector->addItem(tr("Black"), static_cast<int>(QFont::Black));
    _fontWeightSelector->setCurrentIndex(3);
    _fontSizeSelector = new QSpinBox();
    _fontSizeSelector->setRange(4, 200);
    _fontSizeSelector->setValue(12);
    _fontHinting = new QComboBox();
    _fontHinting->addItem(tr("Default"), static_cast<int>(QFont::PreferDefaultHinting));
    _fontHinting->addItem(tr("None"), static_cast<int>(QFont::PreferNoHinting));
    _fontHinting->addItem(tr("Vertical"), static_cast<int>(QFont::PreferVerticalHinting));
    _fontHinting->addItem(tr("Full"), static_cast<int>(QFont::PreferFullHinting));
    _fontHinting->setCurrentIndex(0);
    fontDetailsLayout->addWidget(new QLabel(tr("Size:")));
    fontDetailsLayout->addWidget(_fontSizeSelector);
    fontDetailsLayout->addWidget(new QLabel(tr("Weight:")));
    fontDetailsLayout->addWidget(_fontWeightSelector);
    fontDetailsLayout->addWidget(new QLabel(tr("Hinting:")));
    fontDetailsLayout->addWidget(_fontHinting);
    fontConverterLayout->addWidget(new QLabel(tr("Characters to convert:")));
    _fontCharacters = new QPlainTextEdit();
    _fontCharacters->setFixedHeight(100);
    _fontCharacters->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    _fontCharacters->setWordWrapMode(QTextOption::WrapAnywhere);
    _fontCharacters->setPlainText("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,:;!?()+-=\"'<>");
    _fontCharacters->setReadOnly(true);
    fontConverterLayout->addWidget(_fontCharacters);
    connect(_fontCharacters, &QPlainTextEdit::textChanged, this, &MainWindow::onCharactersChanged);

    auto previewSplittter = new QSplitter(Qt::Vertical);
    previewSplittter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    previewSplittter->setChildrenCollapsible(false);
    mainLayout->addWidget(previewSplittter);

    _bitmapPanel = new BitmapPanel();
    previewSplittter->addWidget(_bitmapPanel);

    auto codePanel = new QWidget();
    codePanel->setMinimumHeight(200);
    auto codeLayout = new QVBoxLayout(codePanel);
    codeLayout->setContentsMargins(16, 4, 16, 16);
    codeLayout->setSpacing(4);
    codeLayout->addWidget(new QLabel(tr("Generated Code:")));
    _codePreview = new QPlainTextEdit();
    _codePreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _codePreview->setReadOnly(true);
    _codePreview->setWordWrapMode(QTextOption::NoWrap);
    codeLayout->addWidget(_codePreview);

    const auto monospaceFont = gApp()->monospaceFont();
    _codePreview->setFont(monospaceFont);
    _fontCharacters->setFont(monospaceFont);

    auto codeActions = new QFrame();
    auto codeActionsLayout = new QHBoxLayout(codeActions);
    codeActionsLayout->setContentsMargins(0, 0, 0, 0);
    codeActionsLayout->setSpacing(4);
    codeActionsLayout->addStretch();

    auto copyCodeButton = new QPushButton();
    copyCodeButton->setText(tr("Copy Code"));
    codeActionsLayout->addWidget(copyCodeButton);
    connect(copyCodeButton, &QPushButton::clicked, [=]{
       qApp->clipboard()->setText(_codePreview->toPlainText());
    });
    codeLayout->addWidget(codeActions);

    previewSplittter->addWidget(codePanel);
    previewSplittter->setStretchFactor(0, 4);
    previewSplittter->setStretchFactor(1, 1);

    connect(_formatSelector, &QComboBox::currentIndexChanged, this, &MainWindow::onFormatChanged);
    connect(_fontSelector, &QFontComboBox::currentFontChanged, this, &MainWindow::onFontChanged);
    connect(_fontSizeSelector, &QSpinBox::valueChanged, this, &MainWindow::onFontChanged);
    connect(_fontWeightSelector, &QComboBox::currentIndexChanged, this, &MainWindow::onFontChanged);
    connect(_fontHinting, &QComboBox::currentIndexChanged, this, &MainWindow::onFontChanged);
    connect(_bitmapPanel, &BitmapPanel::selectedCharacterChanged, this, &MainWindow::onSelectedCharacterChanged);
}


void MainWindow::initializeMenu()
{
    auto menuFile = menuBar()->addMenu(tr("File"));
    auto actionLoadBitmap = menuFile->addAction(tr("Load Bitmap..."));
    actionLoadBitmap->setShortcut(QKeySequence("Ctrl+O"));
    connect(actionLoadBitmap, &QAction::triggered, this, &MainWindow::onLoadBitmap);
    auto actionQuit = menuFile->addAction(tr("Quit"));
    connect(actionQuit, &QAction::triggered, [=]{
        qApp->quit();
    });

    auto menuEdit = menuBar()->addMenu(tr("Edit"));
    menuEdit->addAction(tr("Cut"), [=]{
        QMetaObject::invokeMethod(focusWidget(), "cut");
    }, QKeySequence("Ctrl+X"));
    menuEdit->addAction(tr("Copy"), [=]{
        QMetaObject::invokeMethod(focusWidget(), "copy");
    }, QKeySequence("Ctrl+C"));
    menuEdit->addAction(tr("Paste"), [=]{
        QMetaObject::invokeMethod(focusWidget(), "paste");
    }, QKeySequence("Ctrl+V"));

    auto menuHelp = menuBar()->addMenu(tr("Help"));
    auto actionAbout = menuHelp->addAction(tr("About..."));
    menuHelp->addAction(tr("Lucky Resistor..."), []{
        QDesktopServices::openUrl(QUrl("https://luckyresistor.me/"));
    });
    menuHelp->addAction(tr("Project Page..."), []{
        QDesktopServices::openUrl(QUrl("https://luckyresistor.me/applications/micropython-bitmap-tool/"));
    });
    connect(actionAbout, &QAction::triggered, [=]{
        QMessageBox::about(this, tr("Micropython Bitmap Tool by Lucky Resistor"),
            tr("<h1>Micropython Bitmap Tool</h1>"
                "<p>Copyright (c)2021 by Lucky Resistor</p>"
                "<p><b>Version %1</b></p>"
                "<h2>License</h2>"
                "<p>This program is free software: you can redistribute it and/or modify "
                "it under the terms of the GNU General Public License as published by "
                "the Free Software Foundation, either version 3 of the License, or "
                "(at your option) any later version.</p>"
                "<p>This program is distributed in the hope that it will be useful, "
                "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
                "GNU General Public License for more details. </p>"
                "You should have received a copy of the GNU General Public License "
                "along with this program.  If not, see https://www.gnu.org/licenses/.</p>").arg(qApp->applicationVersion()));
    });
    auto actionAboutQt = menuHelp->addAction(tr("Information About Qt..."));
    connect(actionAboutQt, &QAction::triggered, [=]{
        QMessageBox::aboutQt(this);
    });
}


void MainWindow::loadSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("mainWindow.geometry").toByteArray());
    restoreState(settings.value("mainWindow.state").toByteArray());
    _formatSelector->setCurrentIndex(settings.value("format.index").toInt(0));
    _currentFont = QFont(settings.value("font.family", "Arial").toString());
    _currentFont.setPixelSize(settings.value("font.size", 12).toInt());
    _currentFont.setWeight(static_cast<QFont::Weight>(settings.value("font.weight", 500).toInt()));
    _fontSelector->setCurrentFont(_currentFont);
    _fontSizeSelector->setValue(_currentFont.pixelSize());
    const int index = _fontWeightSelector->findData(static_cast<int>(_currentFont.weight()));
    if (index >= 0) {
        _fontWeightSelector->setCurrentIndex(index);
    } else {
        _fontWeightSelector->setCurrentIndex(3); // normal
    }
    _fontHinting->setCurrentIndex(settings.value("font.hinting", 0).toInt());
}


void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("mainWindow.geometry", saveGeometry());
    settings.setValue("mainWindow.state", saveState());
    settings.setValue("format.index", _formatSelector->currentIndex());
    settings.setValue("font.family", _currentFont.family());
    settings.setValue("font.size", _currentFont.pixelSize());
    settings.setValue("font.weight", static_cast<int>(_currentFont.weight()));
    settings.setValue("font.hinting", _fontHinting->currentIndex());
}


Converter *MainWindow::selectedConverter() const
{
    auto converter = _converterList.value(_formatSelector->currentIndex());
    if (converter == nullptr) {
        converter = _converterList.first();
    }
    return converter;
}


void MainWindow::updateInfoBox()
{
    QString text;
    QTextStream ts(&text);
    if (selectedConverter()->mode() == Converter::Mode::Bitmap) {
        ts << "<p>";
        ts << "Bitmap Size: " << _currentImage.width() << "x" << _currentImage.height() << "<br>";
        ts << "Bit Depth: " << _currentImage.depth() << "<br>";
        ts << "Color Format: ";
        switch (_currentImage.pixelFormat().colorModel()) {
        case QPixelFormat::RGB: ts << "RGB"; break;
        case QPixelFormat::BGR: ts << "BGR"; break;
        case QPixelFormat::Indexed: ts << "Indexed"; break;
        case QPixelFormat::Grayscale: ts << "Grayscale"; break;
        case QPixelFormat::CMYK: ts << "CMYK"; break;
        case QPixelFormat::HSL: ts << "HSL"; break;
        case QPixelFormat::HSV: ts << "HSV"; break;
        case QPixelFormat::YUV: ts << "YUV"; break;
        case QPixelFormat::Alpha: ts << "Alpha"; break;
        }
        ts << "<br>";
        const auto gs = selectedConverter()->generatedSize(_currentImage.size(), createParameterMap());
        ts << "Generated Size: " << gs.width() << "x" << gs.height() << "</p>";
        _bitmapInfo->setText(text);
    } else {
        ts << "<p>";
        ts << "Family: " << _currentFont.family() << "<br>";
        ts << "Weight: ";
        switch (_currentFont.weight()) {
            case QFont::Thin: ts << tr("Thin"); break;
            case QFont::ExtraLight: ts << tr("Extra Light"); break;
            case QFont::Light: ts << tr("Light"); break;
            case QFont::Normal: ts << tr("Normal"); break;
            case QFont::Medium: ts << tr("Medium"); break;
            case QFont::DemiBold: ts << tr("Demi Bold"); break;
            case QFont::Bold: ts << tr("Bold"); break;
            case QFont::ExtraBold: ts << tr("Extra Bold"); break;
            case QFont::Black: ts << tr("Black"); break;
        }
        ts << "<br>";
        ts << "Pixel Size: " << _currentFont.pixelSize() << "<br>";
        ts << "</p>";
        _fontInfo->setText(text);
    }
}


void MainWindow::updateCode()
{
    QString code;
    if (selectedConverter()->mode() == Converter::Mode::Bitmap) {
        auto bitmapConverter = static_cast<BitmapConverter*>(selectedConverter());
        if (!_currentImage.isNull()) {
            code = bitmapConverter->generateCode(_currentImage, QVariantMap());
        }
    } else {
        auto fontConverter = static_cast<FontConverter*>(selectedConverter());
        code = fontConverter->generateCode(_currentFont, createParameterMap());
    }
    _codePreview->setPlainText(code);
}


void MainWindow::updateParameters()
{
    auto converter = selectedConverter();
    if (converter == nullptr) {
        return;
    }

    // Replace the current parameter definition.
    _displayedParameters = converter->createParameterDefinition();
    // Remove the previous UI
    while (_parameterLayout->count() > 0) {
        auto item = _parameterLayout->takeAt(0);
        delete item;
    }
    for (auto w : _parameterFrame->findChildren<QWidget*>()) {
        w->deleteLater();
    }
    // Build the new parameter UI.
    if (_displayedParameters->parameterList().isEmpty()) {
        auto label = new QLabel();
        label->setText(tr("No Parameters"));
        _parameterLayout->addWidget(label);
    } else {
        for (const auto &parameter : _displayedParameters->parameterList()) {
            auto pw = parameterFactory.createWidget(parameter);
            pw->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            pw->setObjectName(parameter->identifier());
            _parameterLayout->addRow(parameter->label() + ":", pw);
            connect(pw, &ParameterWidget::valueChanged, this, &MainWindow::onParameterChanged);
        }
    }
    auto stretchItem = new QWidget();
    stretchItem->setFixedWidth(10);
    stretchItem->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    _parameterLayout->addRow(stretchItem);
}


QVariantMap MainWindow::createParameterMap() const
{
    QVariantMap result;
    result["characters"] = _fontCharacters->toPlainText();
    result["font"] = _currentFont;
    result["char"] = _bitmapPanel->selectedCharacter();
    for (auto pw : _parameterFrame->findChildren<ParameterWidget*>()) {
        result[pw->objectName()] = pw->value();
    }
    return result;
}


void MainWindow::onLoadBitmap()
{
    QSettings settings;
    auto lastDir = settings.value("bitmap.lastDir").toString();
    auto fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open Bitmap"),
        lastDir,
        tr("Images (*.png *.jpg *.jpeg *.gif *.pbm *.pgm *.ppm *.xbm *.xpm *.bpm)"));
    if (fileName.isEmpty()) {
        return;
    }
    QFileInfo fileInfo(fileName);
    settings.setValue("bitmap.lastDir", fileInfo.absoluteDir().path());
    QImage newImage;
    if (!newImage.load(fileName)) {
        QMessageBox::warning(this, tr("Loading Image Failed"),
                             tr("<h1>Failed to load the image</h1>"
                                "<p>Could not load the specified image file. "
                                "Make sure the image is in a supported format.</p>"));
        return;
    }
    if (newImage.width() > 0x100 || newImage.height() > 0x100) {
        QMessageBox::warning(this, tr("Image is Too Large"),
                             tr("<h1>Image is Too Large</h1>"
                                "<p>One dimension of the loaded image is larger than "
                                "256 pixel. This software is designed for small bitmaps.</p>"));
        return;
    }

    _currentImage = newImage;
    _bitmapPanel->setImage(newImage);
    _bitmapPanel->setConverter(selectedConverter());
    updateInfoBox();
    updateCode();
}


void MainWindow::onFormatChanged()
{
    const auto converter = selectedConverter();
    _bitmapPanel->setConverter(converter);
    if (converter->mode() == Converter::Mode::Bitmap) {
        _bitmapConverterFrame->setVisible(true);
        _fontConverterFrame->setVisible(false);
    } else {
        _bitmapConverterFrame->setVisible(false);
        _fontConverterFrame->setVisible(true);
    }
    updateParameters();
    updateInfoBox();
    updateCode();
    _bitmapPanel->setParameter(createParameterMap());
    onSelectedCharacterChanged(_bitmapPanel->selectedCharacter());
}


void MainWindow::onFontChanged()
{
    _currentFont = _fontSelector->currentFont();
    _currentFont.setWeight(static_cast<QFont::Weight>(_fontWeightSelector->currentData().toInt()));
    _currentFont.setPixelSize(_fontSizeSelector->value());
    const auto hintingPreferences = static_cast<QFont::HintingPreference>(_fontHinting->currentData().toInt());
    _currentFont.setHintingPreference(hintingPreferences);
    updateInfoBox();
    updateCode();
    _bitmapPanel->setParameter(createParameterMap());
    onSelectedCharacterChanged(_bitmapPanel->selectedCharacter());
}


void MainWindow::onCharactersChanged()
{
    auto characters = _fontCharacters->toPlainText();
    _bitmapPanel->setCharacters(characters);
    _bitmapPanel->setConverter(selectedConverter());
    _bitmapPanel->setParameter(createParameterMap());
    onSelectedCharacterChanged(_bitmapPanel->selectedCharacter());
}


void MainWindow::onSelectedCharacterChanged(QChar c)
{
    auto converter = selectedConverter();
    if (converter == nullptr) {
        return;
    }
    if (converter->mode() == Converter::Mode::Font) {
        auto fontConverter = static_cast<const FontConverter*>(converter);
        auto newImage = fontConverter->generateImage(_currentFont, c, createParameterMap());
        _currentImage = newImage;
        _bitmapPanel->setImage(newImage);
        _bitmapPanel->setConverter(selectedConverter());
        _bitmapPanel->setParameter(createParameterMap());
    }
}


void MainWindow::onParameterChanged()
{
    _bitmapPanel->setParameter(createParameterMap());
    onSelectedCharacterChanged(_bitmapPanel->selectedCharacter());
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    QMainWindow::closeEvent(event);
}

