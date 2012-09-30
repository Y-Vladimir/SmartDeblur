#include "HelpDialog.h"
#include "ui_HelpDialog.h"
#include "MainWindow.h"



HelpDialog::HelpDialog(QWidget *parent):QDialog(parent),ui(new Ui::HelpDialog) {
    ui->setupUi(this);
    ui->mainTextLabel->setText(ui->mainTextLabel->text().arg(MainWindow::appVersion));

    // Load settings
    settings = new QSettings("SmartDeblur", "SmartDeblur");
    ui->showOnStartupCheckBox->setChecked(settings->value("ShowHelpOnStartup", true).toBool());
    ui->openExampleCheckBox->setChecked(settings->value("OpenExampleAfterHelp", true).toBool());

    connect(ui->showOnStartupCheckBox, SIGNAL(toggled(bool)), SLOT(saveSettings(bool)));
    connect(ui->openExampleCheckBox, SIGNAL(toggled(bool)), SLOT(saveSettings(bool)));
}

HelpDialog::~HelpDialog() {
    delete ui;
}

bool HelpDialog::isShowOnStartup() {
    return ui->showOnStartupCheckBox->isChecked();
}

bool HelpDialog::isOpenExampleAfterClose() {
    return ui->openExampleCheckBox->isChecked();
}

void HelpDialog::saveSettings(bool value) {
    settings->setValue("ShowHelpOnStartup", ui->showOnStartupCheckBox->isChecked());
    settings->setValue("OpenExampleAfterHelp", ui->openExampleCheckBox->isChecked());
}

