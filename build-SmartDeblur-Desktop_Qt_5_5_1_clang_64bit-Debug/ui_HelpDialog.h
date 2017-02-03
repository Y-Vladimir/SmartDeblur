/********************************************************************************
** Form generated from reading UI file 'HelpDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPDIALOG_H
#define UI_HELPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_HelpDialog
{
public:
    QLabel *label;
    QLabel *mainTextLabel;
    QFrame *frame;
    QPushButton *okButton;
    QCheckBox *showOnStartupCheckBox;
    QCheckBox *openExampleCheckBox;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *HelpDialog)
    {
        if (HelpDialog->objectName().isEmpty())
            HelpDialog->setObjectName(QStringLiteral("HelpDialog"));
        HelpDialog->setWindowModality(Qt::ApplicationModal);
        HelpDialog->resize(550, 390);
        HelpDialog->setMinimumSize(QSize(550, 390));
        HelpDialog->setMaximumSize(QSize(550, 390));
        HelpDialog->setAutoFillBackground(false);
        HelpDialog->setStyleSheet(QStringLiteral("QDialog {background-color: rgb(255, 255, 255)}"));
        HelpDialog->setSizeGripEnabled(false);
        label = new QLabel(HelpDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(13, 8, 80, 80));
        label->setPixmap(QPixmap(QString::fromUtf8(":/SmartDeblur/Icons/Logo2.png")));
        label->setScaledContents(true);
        mainTextLabel = new QLabel(HelpDialog);
        mainTextLabel->setObjectName(QStringLiteral("mainTextLabel"));
        mainTextLabel->setGeometry(QRect(110, 5, 430, 221));
        mainTextLabel->setMinimumSize(QSize(0, 0));
        mainTextLabel->setMaximumSize(QSize(10000, 10000));
        QFont font;
        font.setPointSize(10);
        mainTextLabel->setFont(font);
        mainTextLabel->setWordWrap(true);
        frame = new QFrame(HelpDialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 340, 551, 51));
        frame->setAutoFillBackground(false);
        frame->setStyleSheet(QStringLiteral("QFrame {background-color: rgb(240, 240, 240)}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        okButton = new QPushButton(frame);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(430, 10, 111, 31));
        showOnStartupCheckBox = new QCheckBox(frame);
        showOnStartupCheckBox->setObjectName(QStringLiteral("showOnStartupCheckBox"));
        showOnStartupCheckBox->setGeometry(QRect(13, 5, 161, 17));
        showOnStartupCheckBox->setChecked(true);
        openExampleCheckBox = new QCheckBox(frame);
        openExampleCheckBox->setObjectName(QStringLiteral("openExampleCheckBox"));
        openExampleCheckBox->setGeometry(QRect(13, 28, 171, 17));
        openExampleCheckBox->setChecked(true);
        label_2 = new QLabel(HelpDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 240, 561, 101));
        QFont font1;
        font1.setPointSize(12);
        label_2->setFont(font1);
        label_2->setStyleSheet(QStringLiteral("background-color: rgb(189, 255, 169);"));
        label_2->setFrameShadow(QFrame::Raised);
        label_2->setLineWidth(1);
        label_2->setMidLineWidth(0);
        label_2->setWordWrap(true);
        label_2->setMargin(10);
        label_3 = new QLabel(HelpDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(9, 249, 41, 41));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/SmartDeblur/Icons/Attention.png")));
        label_3->setScaledContents(true);

        retranslateUi(HelpDialog);
        QObject::connect(okButton, SIGNAL(clicked()), HelpDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(HelpDialog);
    } // setupUi

    void retranslateUi(QDialog *HelpDialog)
    {
        HelpDialog->setWindowTitle(QApplication::translate("HelpDialog", "About SmartDeblur", 0));
        label->setText(QString());
        mainTextLabel->setText(QApplication::translate("HelpDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">The <span style=\" font-weight:600;\">SmartDeblur</span> is a tool for restoration of defocused and blurred images. Algorithm based on several deconvolution technics (Wiener, Tikhonov, Total Variation pior). Supported defect types:</p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Out-of-Focus blur (with kernel deep tuning)</li>\n"
"<li style=\" margin-top:0px; margin-b"
                        "ottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Motion blur</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Gaussian blur</li></ul>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">SmartDeblur uses the FFTW library which provides fast Fourier tranformation implementation. See <a href=\"www.fftw.org\"><span style=\" text-decoration: underline; color:#0000ff;\">www.fftw.org</span></a> for details </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Author: <span style=\" font-weight:600;\">Vladimir Yuzhikov</span> (yuvladimir@gmail.com), the latest sources and binaries are available on: <a href=\"https://github.com/Y-Vladimir/SmartDeblur\"><span style=\" text-decoration: underline; color:#0000ff;\">https://github.com/Y-Vladimir/SmartDeblur<"
                        "/span></a></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Version: %1</span></p></body></html>", 0));
        okButton->setText(QApplication::translate("HelpDialog", "OK", 0));
        showOnStartupCheckBox->setText(QApplication::translate("HelpDialog", "Show this dialog on startup", 0));
        openExampleCheckBox->setText(QApplication::translate("HelpDialog", "Open the example after close", 0));
        label_2->setText(QApplication::translate("HelpDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">         After close the Example with real Out-of-Focus blur will be opened.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">         Try that Example and read blurred text and car number! </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">First of all set <span style=\" font-weight:600;\">&quot;Radius&quot;</span> slider between<span style=\" font-weight:600;\"> 27</span> and<span style=\" font-wei"
                        "ght:600;\"> 29</span> (move slider carefully).</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Then choose desired quality level using <span style=\" font-weight:600;\">&quot;Smooth&quot;</span> slider (<span style=\" font-weight:600;\">30</span> for example).</p></body></html>", 0));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HelpDialog: public Ui_HelpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPDIALOG_H
