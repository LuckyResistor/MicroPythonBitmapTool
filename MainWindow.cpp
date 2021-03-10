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


#include "BitmapPanel.hpp"
#include "ConverterFramebufMonoVLSB.hpp"
#include "ConverterFramebufMonoHLSB.hpp"
#include "ConverterFramebufMonoHMSB.hpp"

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
#include <QtGui/QDesktopServices>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initializeConverterList();
    initializeUi();
    initializeMenu();
    loadSettings();
}


MainWindow::~MainWindow()
{
}


void MainWindow::initializeConverterList()
{
    _converterList.append(new ConverterFramebufMonoVLSB());
    _converterList.append(new ConverterFramebufMonoHMSB());
    _converterList.append(new ConverterFramebufMonoHLSB());
}


void MainWindow::initializeUi()
{
    setMinimumSize(800, 600);
    setWindowTitle(tr("Micropython Bitmap Tool - V%1 - Lucky Resistor").arg(qApp->applicationVersion()));

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
    logo->setFixedSize(300, 250);
    logo->setPixmap(QPixmap(":/images/AppLogo.png"));
    settingsLayout->addWidget(logo);
    auto versionLabel = new QLabel(tr("<b>Version %1</b>").arg(qApp->applicationVersion()));
    versionLabel->setAlignment(Qt::AlignCenter);
    settingsLayout->addWidget(versionLabel);
    settingsLayout->addSpacing(16);

    settingsLayout->addWidget(new QLabel(tr("Generated Format:")));
    _formatSelector = new QComboBox();
    for (auto converter : _converterList) {
        _formatSelector->addItem(converter->displayName());
    }
    _formatSelector->setCurrentIndex(0);
    settingsLayout->addWidget(_formatSelector);

    settingsLayout->addStretch();

    settingsLayout->addWidget(new QLabel(tr("<b>Loaded Bitmap Info:</b>")));
    _bitmapInfo = new QLabel(tr("No Bitmap Loaded"));
    _bitmapInfo->setObjectName("BitmapInfo");
    _bitmapInfo->setMinimumHeight(200);
    _bitmapInfo->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    settingsLayout->addWidget(_bitmapInfo);

    auto loadButton = new QPushButton();
    loadButton->setText(tr("Load Bitmap"));
    settingsLayout->addWidget(loadButton);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadBitmap);

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

#ifdef Q_OS_WIN32
    _codePreview->setFont(QFont("Consolas", 12));
#else
#ifdef Q_OS_MAC
    _codePreview->setFont(QFont("Menlo", 12));
#else
    _codePreview->setFont(QFont("Lucida Console", 12));
#endif
#endif

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

    connect(_formatSelector, &QComboBox::currentIndexChanged, [=]{
        _bitmapPanel->setConverter(selectedConverter());
        updateBitmapInfo();
        updateCode();
    });
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
}


void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("mainWindow.geometry", saveGeometry());
    settings.setValue("mainWindow.state", saveState());
    settings.setValue("format.index", _formatSelector->currentIndex());
}


Converter *MainWindow::selectedConverter() const
{
    auto converter = _converterList.value(_formatSelector->currentIndex());
    if (converter == nullptr) {
        converter = _converterList.first();
    }
    return converter;
}


void MainWindow::updateBitmapInfo()
{
    QString text;
    QTextStream ts(&text);
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
    const auto gs = selectedConverter()->generatedSize(_currentImage.size());
    ts << "Generated Size: " << gs.width() << "x" << gs.height() << "</p>";
    _bitmapInfo->setText(text);
}


void MainWindow::updateCode()
{
    QString code;
    if (!_currentImage.isNull()) {
        code = selectedConverter()->generateCode(_currentImage, QVariantMap());
    }
    _codePreview->setPlainText(code);
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
    updateBitmapInfo();
    updateCode();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    QMainWindow::closeEvent(event);
}

