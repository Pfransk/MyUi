#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QComboBox>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

signals:
    void settingsChanged();

private slots:
    void saveSettings();

private:
    QComboBox *fontSizeComboBox;
    QComboBox *themeComboBox;

    void loadSettings();
};



#endif // SETTINGSDIALOG_H
