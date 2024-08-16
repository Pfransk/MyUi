#include "settingsdialog.h"
#include <QSettings>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    // Set up the UI layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Font size selector
    QLabel *fontSizeLabel = new QLabel("Font Size", this);
    layout->addWidget(fontSizeLabel);

    fontSizeComboBox = new QComboBox(this);
    fontSizeComboBox->addItem("Small");
    fontSizeComboBox->addItem("Medium");
    fontSizeComboBox->addItem("Large");
    layout->addWidget(fontSizeComboBox);

    // Theme selector
    QLabel *themeLabel = new QLabel("Theme", this);
    layout->addWidget(themeLabel);

    themeComboBox = new QComboBox(this);
    themeComboBox->addItem("Light");
    themeComboBox->addItem("Dark");
    layout->addWidget(themeComboBox);

    // Save button
    QPushButton *saveButton = new QPushButton("Save", this);
    layout->addWidget(saveButton);
    connect(saveButton, &QPushButton::clicked, this, &SettingsDialog::saveSettings);

    // Load the current settings into the dialog
    loadSettings();

    setLayout(layout);
}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::loadSettings()
{
    // Load settings from QSettings
    QSettings settings("MyCompany", "AdaptiveApp");

    fontSizeComboBox->setCurrentText(settings.value("fontSize", "Medium").toString());
    themeComboBox->setCurrentText(settings.value("theme", "Light").toString());
}

void SettingsDialog::saveSettings()
{
    // Save the selected font size and theme to QSettings
    QSettings settings("MyCompany", "AdaptiveApp");

    settings.setValue("fontSize", fontSizeComboBox->currentText());
    settings.setValue("theme", themeComboBox->currentText());

    // Emit signal to notify that settings have changed
    emit settingsChanged();

    // Close the dialog
    accept();
}
