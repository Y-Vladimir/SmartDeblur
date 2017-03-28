/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFrame *frame;
    QToolButton *btnOpen;
    QLabel *label_4;
    QToolButton *btnSave;
    QToolButton *btnAbout;
    QFrame *frame_2;
    QToolButton *btnZoomIn;
    QToolButton *btnZoomOut;
    QToolButton *btnZoomNormal;
    QCheckBox *checkBoxFitToWindow;
    QLabel *label_3;
    QFrame *frame_3;
    QSlider *sliderRadius;
    QSlider *sliderPSNR;
    QLabel *labelRadius;
    QLabel *labelPSNR;
    QComboBox *comboBoxType;
    QSlider *sliderMotionLength;
    QLabel *labelMotionLength;
    QSlider *sliderMotionAngle;
    QLabel *labelMotionAngle;
    QLabel *label_2;
    QToolButton *btnShowOriginal;
    QLabel *labelMotionLengthCaption;
    QLabel *labelMotionAngleCaption;
    QLabel *labelRadiusCaption;
    QLabel *labelPSNRCaption;
    QLabel *label_7;
    QFrame *frame_5;
    QSlider *sliderKernelStrength;
    QSlider *sliderKernelFeather;
    QLabel *labelKernelPreview;
    QLabel *labelStrength;
    QLabel *labelFeather;
    QLabel *label_5;
    QLabel *labelStrengthCaption;
    QLabel *labelFeatherCaption;
    QWidget *tab_2;
    QFrame *frame_4;
    QLabel *label_6;
    QLabel *label;
    QSpinBox *imageSizeLimitSpinBox;
    QLabel *label_8;
    QFrame *frame_6;
    QLabel *label_9;
    QSpinBox *tvIterationsCountSpinBox;
    QLabel *label_10;
    QLabel *label_11;
    QComboBox *previewMethodComboBox;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1107, 527);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(400, 400));
        MainWindow->setAcceptDrops(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/SmartDeblur/Icons/Logo2.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setAcceptDrops(false);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMaximumSize(QSize(16777215, 140));
        tabWidget->setAcceptDrops(true);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        frame = new QFrame(tab);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(1, 2, 161, 110));
        frame->setStyleSheet(QLatin1String("QFrame  {background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(165, 206, 255, 255), stop:0.744318 rgba(219, 240, 255, 255))}\n"
"\n"
"QLabel {background-color: none;}\n"
""));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Sunken);
        btnOpen = new QToolButton(frame);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));
        btnOpen->setGeometry(QRect(3, 3, 51, 60));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/SmartDeblur/Icons/Open.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOpen->setIcon(icon1);
        btnOpen->setIconSize(QSize(32, 32));
        btnOpen->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btnOpen->setAutoRaise(true);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(0, 90, 162, 21));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_4->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(165, 206, 255, 255), stop:0.744318 rgba(219, 240, 255, 255))\n"
""));
        label_4->setFrameShape(QFrame::Box);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);
        btnSave = new QToolButton(frame);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(56, 3, 51, 60));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/SmartDeblur/Icons/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSave->setIcon(icon2);
        btnSave->setIconSize(QSize(32, 32));
        btnSave->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btnSave->setAutoRaise(true);
        btnAbout = new QToolButton(frame);
        btnAbout->setObjectName(QStringLiteral("btnAbout"));
        btnAbout->setGeometry(QRect(109, 3, 51, 60));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/SmartDeblur/Icons/About.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAbout->setIcon(icon3);
        btnAbout->setIconSize(QSize(32, 32));
        btnAbout->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btnAbout->setAutoRaise(true);
        frame_2 = new QFrame(tab);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(165, 2, 114, 110));
        frame_2->setStyleSheet(QLatin1String("QFrame  {background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(165, 206, 255, 255), stop:0.744318 rgba(219, 240, 255, 255))}\n"
"\n"
"QLabel {background-color: none;}\n"
"\n"
""));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Sunken);
        btnZoomIn = new QToolButton(frame_2);
        btnZoomIn->setObjectName(QStringLiteral("btnZoomIn"));
        btnZoomIn->setGeometry(QRect(75, 10, 31, 31));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/SmartDeblur/Icons/Zoom In.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnZoomIn->setIcon(icon4);
        btnZoomIn->setIconSize(QSize(24, 24));
        btnZoomIn->setAutoRaise(true);
        btnZoomOut = new QToolButton(frame_2);
        btnZoomOut->setObjectName(QStringLiteral("btnZoomOut"));
        btnZoomOut->setGeometry(QRect(41, 10, 31, 31));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/SmartDeblur/Icons/Zoom Out.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnZoomOut->setIcon(icon5);
        btnZoomOut->setIconSize(QSize(24, 24));
        btnZoomOut->setAutoRaise(true);
        btnZoomNormal = new QToolButton(frame_2);
        btnZoomNormal->setObjectName(QStringLiteral("btnZoomNormal"));
        btnZoomNormal->setGeometry(QRect(6, 10, 31, 31));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/SmartDeblur/Icons/Zoom_Actual.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnZoomNormal->setIcon(icon6);
        btnZoomNormal->setIconSize(QSize(24, 24));
        btnZoomNormal->setAutoRaise(true);
        checkBoxFitToWindow = new QCheckBox(frame_2);
        checkBoxFitToWindow->setObjectName(QStringLiteral("checkBoxFitToWindow"));
        checkBoxFitToWindow->setGeometry(QRect(16, 51, 91, 17));
        checkBoxFitToWindow->setChecked(true);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 90, 115, 21));
        label_3->setFont(font);
        label_3->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(165, 206, 255, 255), stop:0.744318 rgba(219, 240, 255, 255))\n"
""));
        label_3->setFrameShape(QFrame::Box);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        frame_3 = new QFrame(tab);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(282, 2, 437, 110));
        frame_3->setStyleSheet(QLatin1String("QFrame  {background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(165, 206, 255, 255), stop:0.744318 rgba(219, 240, 255, 255))}\n"
"\n"
"QLabel {background-color: none;}\n"
""));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Sunken);
        sliderRadius = new QSlider(frame_3);
        sliderRadius->setObjectName(QStringLiteral("sliderRadius"));
        sliderRadius->setGeometry(QRect(77, 55, 356, 19));
        sliderRadius->setMinimum(1);
        sliderRadius->setMaximum(500);
        sliderRadius->setValue(50);
        sliderRadius->setOrientation(Qt::Horizontal);
        sliderPSNR = new QSlider(frame_3);
        sliderPSNR->setObjectName(QStringLiteral("sliderPSNR"));
        sliderPSNR->setGeometry(QRect(77, 70, 356, 19));
        sliderPSNR->setMinimum(1);
        sliderPSNR->setMaximum(99);
        sliderPSNR->setValue(30);
        sliderPSNR->setOrientation(Qt::Horizontal);
        labelRadius = new QLabel(frame_3);
        labelRadius->setObjectName(QStringLiteral("labelRadius"));
        labelRadius->setGeometry(QRect(49, 57, 32, 13));
        labelPSNR = new QLabel(frame_3);
        labelPSNR->setObjectName(QStringLiteral("labelPSNR"));
        labelPSNR->setGeometry(QRect(49, 72, 32, 13));
        comboBoxType = new QComboBox(frame_3);
        comboBoxType->setObjectName(QStringLiteral("comboBoxType"));
        comboBoxType->setGeometry(QRect(85, 3, 140, 21));
        sliderMotionLength = new QSlider(frame_3);
        sliderMotionLength->setObjectName(QStringLiteral("sliderMotionLength"));
        sliderMotionLength->setGeometry(QRect(77, 23, 356, 19));
        sliderMotionLength->setMinimum(1);
        sliderMotionLength->setMaximum(500);
        sliderMotionLength->setValue(50);
        sliderMotionLength->setOrientation(Qt::Horizontal);
        labelMotionLength = new QLabel(frame_3);
        labelMotionLength->setObjectName(QStringLiteral("labelMotionLength"));
        labelMotionLength->setGeometry(QRect(49, 24, 32, 13));
        sliderMotionAngle = new QSlider(frame_3);
        sliderMotionAngle->setObjectName(QStringLiteral("sliderMotionAngle"));
        sliderMotionAngle->setGeometry(QRect(77, 39, 356, 19));
        sliderMotionAngle->setMinimum(-90);
        sliderMotionAngle->setMaximum(90);
        sliderMotionAngle->setValue(50);
        sliderMotionAngle->setOrientation(Qt::Horizontal);
        labelMotionAngle = new QLabel(frame_3);
        labelMotionAngle->setObjectName(QStringLiteral("labelMotionAngle"));
        labelMotionAngle->setGeometry(QRect(49, 41, 32, 13));
        label_2 = new QLabel(frame_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(6, 5, 70, 16));
        label_2->setFont(font);
        btnShowOriginal = new QToolButton(frame_3);
        btnShowOriginal->setObjectName(QStringLiteral("btnShowOriginal"));
        btnShowOriginal->setGeometry(QRect(235, 0, 105, 28));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/SmartDeblur/Icons/image.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnShowOriginal->setIcon(icon7);
        btnShowOriginal->setIconSize(QSize(24, 24));
        btnShowOriginal->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnShowOriginal->setAutoRaise(true);
        labelMotionLengthCaption = new QLabel(frame_3);
        labelMotionLengthCaption->setObjectName(QStringLiteral("labelMotionLengthCaption"));
        labelMotionLengthCaption->setGeometry(QRect(5, 23, 47, 16));
        labelMotionAngleCaption = new QLabel(frame_3);
        labelMotionAngleCaption->setObjectName(QStringLiteral("labelMotionAngleCaption"));
        labelMotionAngleCaption->setGeometry(QRect(5, 40, 47, 16));
        labelRadiusCaption = new QLabel(frame_3);
        labelRadiusCaption->setObjectName(QStringLiteral("labelRadiusCaption"));
        labelRadiusCaption->setGeometry(QRect(5, 56, 47, 16));
        labelPSNRCaption = new QLabel(frame_3);
        labelPSNRCaption->setObjectName(QStringLiteral("labelPSNRCaption"));
        labelPSNRCaption->setGeometry(QRect(5, 71, 47, 16));
        label_7 = new QLabel(frame_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(0, 90, 438, 21));
        label_7->setFont(font);
        label_7->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(165, 206, 255, 255), stop:0.744318 rgba(219, 240, 255, 255))\n"
""));
        label_7->setFrameShape(QFrame::Box);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);
        frame_5 = new QFrame(tab);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setGeometry(QRect(722, 2, 231, 110));
        frame_5->setStyleSheet(QLatin1String("QFrame  {background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(165, 206, 255, 255), stop:0.744318 rgba(219, 240, 255, 255))}\n"
"\n"
"QLabel {background-color: none;}\n"
""));
        frame_5->setFrameShape(QFrame::NoFrame);
        frame_5->setFrameShadow(QFrame::Sunken);
        sliderKernelStrength = new QSlider(frame_5);
        sliderKernelStrength->setObjectName(QStringLiteral("sliderKernelStrength"));
        sliderKernelStrength->setGeometry(QRect(94, 22, 131, 19));
        sliderKernelStrength->setMinimum(-99);
        sliderKernelStrength->setMaximum(99);
        sliderKernelStrength->setOrientation(Qt::Horizontal);
        sliderKernelStrength->setTickPosition(QSlider::NoTicks);
        sliderKernelStrength->setTickInterval(20);
        sliderKernelFeather = new QSlider(frame_5);
        sliderKernelFeather->setObjectName(QStringLiteral("sliderKernelFeather"));
        sliderKernelFeather->setGeometry(QRect(94, 66, 131, 19));
        sliderKernelFeather->setMinimum(1);
        sliderKernelFeather->setMaximum(99);
        sliderKernelFeather->setValue(10);
        sliderKernelFeather->setOrientation(Qt::Horizontal);
        sliderKernelFeather->setTickPosition(QSlider::NoTicks);
        sliderKernelFeather->setTickInterval(10);
        labelKernelPreview = new QLabel(frame_5);
        labelKernelPreview->setObjectName(QStringLiteral("labelKernelPreview"));
        labelKernelPreview->setGeometry(QRect(3, 3, 85, 85));
        labelKernelPreview->setAutoFillBackground(false);
        labelKernelPreview->setStyleSheet(QStringLiteral("background-color: rgb(191, 191, 191);"));
        labelStrength = new QLabel(frame_5);
        labelStrength->setObjectName(QStringLiteral("labelStrength"));
        labelStrength->setGeometry(QRect(198, 5, 31, 16));
        labelFeather = new QLabel(frame_5);
        labelFeather->setObjectName(QStringLiteral("labelFeather"));
        labelFeather->setGeometry(QRect(200, 47, 31, 16));
        label_5 = new QLabel(frame_5);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(0, 90, 232, 21));
        label_5->setFont(font);
        label_5->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(165, 206, 255, 255), stop:0.744318 rgba(219, 240, 255, 255))\n"
""));
        label_5->setFrameShape(QFrame::Box);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);
        labelStrengthCaption = new QLabel(frame_5);
        labelStrengthCaption->setObjectName(QStringLiteral("labelStrengthCaption"));
        labelStrengthCaption->setGeometry(QRect(94, 5, 99, 16));
        labelFeatherCaption = new QLabel(frame_5);
        labelFeatherCaption->setObjectName(QStringLiteral("labelFeatherCaption"));
        labelFeatherCaption->setGeometry(QRect(97, 47, 91, 16));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        frame_4 = new QFrame(tab_2);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setGeometry(QRect(1, 2, 161, 110));
        frame_4->setStyleSheet(QLatin1String("QFrame  {background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(165, 206, 255, 255), stop:0.744318 rgba(219, 240, 255, 255))}\n"
"\n"
"QLabel {background-color: none;}\n"
"\n"
""));
        frame_4->setFrameShape(QFrame::NoFrame);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(0, 90, 162, 21));
        label_6->setFont(font);
        label_6->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(165, 206, 255, 255), stop:0.744318 rgba(219, 240, 255, 255))\n"
""));
        label_6->setFrameShape(QFrame::Box);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        label = new QLabel(frame_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(6, 7, 151, 16));
        imageSizeLimitSpinBox = new QSpinBox(frame_4);
        imageSizeLimitSpinBox->setObjectName(QStringLiteral("imageSizeLimitSpinBox"));
        imageSizeLimitSpinBox->setGeometry(QRect(8, 27, 81, 22));
        imageSizeLimitSpinBox->setMinimum(100);
        imageSizeLimitSpinBox->setMaximum(10000);
        imageSizeLimitSpinBox->setValue(3000);
        label_8 = new QLabel(frame_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(5, 52, 151, 31));
        label_8->setFont(font);
        label_8->setStyleSheet(QStringLiteral("color: rgb(214, 0, 0);"));
        label_8->setWordWrap(true);
        frame_6 = new QFrame(tab_2);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setGeometry(QRect(165, 2, 173, 110));
        frame_6->setStyleSheet(QLatin1String("QFrame  {background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(165, 206, 255, 255), stop:0.744318 rgba(219, 240, 255, 255))}\n"
"\n"
"QLabel {background-color: none;}\n"
"\n"
""));
        frame_6->setFrameShape(QFrame::NoFrame);
        frame_6->setFrameShadow(QFrame::Sunken);
        label_9 = new QLabel(frame_6);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(0, 90, 174, 21));
        label_9->setFont(font);
        label_9->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(165, 206, 255, 255), stop:0.744318 rgba(219, 240, 255, 255))\n"
""));
        label_9->setFrameShape(QFrame::Box);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter);
        tvIterationsCountSpinBox = new QSpinBox(frame_6);
        tvIterationsCountSpinBox->setObjectName(QStringLiteral("tvIterationsCountSpinBox"));
        tvIterationsCountSpinBox->setGeometry(QRect(9, 27, 81, 22));
        tvIterationsCountSpinBox->setMinimum(50);
        tvIterationsCountSpinBox->setMaximum(1000);
        tvIterationsCountSpinBox->setValue(500);
        label_10 = new QLabel(frame_6);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(7, 7, 161, 16));
        label_11 = new QLabel(frame_6);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(9, 61, 91, 16));
        previewMethodComboBox = new QComboBox(frame_6);
        previewMethodComboBox->setObjectName(QStringLiteral("previewMethodComboBox"));
        previewMethodComboBox->setGeometry(QRect(98, 58, 70, 22));
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 470, 250));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SmartDeblur", 0));
        btnOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        label_4->setText(QApplication::translate("MainWindow", "File", 0));
        btnSave->setText(QApplication::translate("MainWindow", "Save", 0));
        btnAbout->setText(QApplication::translate("MainWindow", "Help", 0));
        btnZoomIn->setText(QApplication::translate("MainWindow", "+", 0));
        btnZoomOut->setText(QApplication::translate("MainWindow", "-", 0));
        btnZoomNormal->setText(QApplication::translate("MainWindow", "1:1", 0));
        checkBoxFitToWindow->setText(QApplication::translate("MainWindow", "Fit to Window", 0));
        label_3->setText(QApplication::translate("MainWindow", "Zoom", 0));
        labelRadius->setText(QApplication::translate("MainWindow", "5", 0));
        labelPSNR->setText(QApplication::translate("MainWindow", "5", 0));
        comboBoxType->clear();
        comboBoxType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Out of Focus Blur", 0)
         << QApplication::translate("MainWindow", "Motion Blur", 0)
         << QApplication::translate("MainWindow", "Gaussian Blur", 0)
        );
        labelMotionLength->setText(QApplication::translate("MainWindow", "5", 0));
        labelMotionAngle->setText(QApplication::translate("MainWindow", "5", 0));
        label_2->setText(QApplication::translate("MainWindow", "Defect type:", 0));
        btnShowOriginal->setText(QApplication::translate("MainWindow", "Show Original", 0));
        labelMotionLengthCaption->setText(QApplication::translate("MainWindow", "Length:", 0));
        labelMotionAngleCaption->setText(QApplication::translate("MainWindow", "Angle:", 0));
        labelRadiusCaption->setText(QApplication::translate("MainWindow", "Radius:", 0));
        labelPSNRCaption->setText(QApplication::translate("MainWindow", "Smooth:", 0));
        label_7->setText(QApplication::translate("MainWindow", "Blur Parameters", 0));
        labelKernelPreview->setText(QString());
        labelStrength->setText(QApplication::translate("MainWindow", "5", 0));
        labelFeather->setText(QApplication::translate("MainWindow", "5", 0));
        label_5->setText(QApplication::translate("MainWindow", "Kernel Preview & Tuning", 0));
        labelStrengthCaption->setText(QApplication::translate("MainWindow", "Correction Strength:", 0));
        labelFeatherCaption->setText(QApplication::translate("MainWindow", "Edge Feather:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Main", 0));
        label_6->setText(QApplication::translate("MainWindow", "General", 0));
        label->setText(QApplication::translate("MainWindow", "Image size limit (largest side):", 0));
        label_8->setText(QApplication::translate("MainWindow", "Increase the value may cause slow/unstable work!", 0));
        label_9->setText(QApplication::translate("MainWindow", "Deconvolution", 0));
        label_10->setText(QApplication::translate("MainWindow", "Iterations count for High-Quality:", 0));
        label_11->setText(QApplication::translate("MainWindow", "Preview method:", 0));
        previewMethodComboBox->clear();
        previewMethodComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Wiener", 0)
         << QApplication::translate("MainWindow", "Tikhonov", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
