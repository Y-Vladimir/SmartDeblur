#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QSettings>


namespace Ui {
class HelpDialog;
}

class HelpDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit HelpDialog(QWidget *parent = 0);
    ~HelpDialog();
    bool isShowOnStartup();
    bool isOpenExampleAfterClose();

private slots:
    void saveSettings(bool value);

private:
    Ui::HelpDialog *ui;
    QSettings *settings;
};

#endif // HELPDIALOG_H
