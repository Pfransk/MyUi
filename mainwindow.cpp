#include "mainwindow.h"
#include "settingsdialog.h"
#include <QSettings>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set up the UI: label and menu
    label = new QLabel("MyUI Adaptive design challenge");
    label2 = new QLabel("Select the following options for different voice");

    // setCentralWidget(label);

    // Create menu for settings
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *settingsMenu = new QMenu("Settings", this);
    QAction *openSettingsAction = new QAction("Open Settings", this);
    settingsMenu->addAction(openSettingsAction);
    menuBar->addMenu(settingsMenu);
    setMenuBar(menuBar);

    // Connect the settings action to the dialog
    connect(openSettingsAction, &QAction::triggered, this, &MainWindow::openSettingsDialog);

    // Load and apply settings at startup
    loadSettings();


    // Set up the Text-to-Speech engine
    speech = new QTextToSpeech(this);

    // Create a simple input field and button
    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Type something here...and hit button below for Text-to-speech");  // Set hint text

    languageComboBox = new QComboBox(this);
    // List available voices and populate the combo box
    QList<QVoice> voices = speech->availableVoices();
    for (const QVoice &voice : voices) {
        languageComboBox->addItem(voice.name(), QVariant::fromValue(voice));
    }

    speakButton = new QPushButton("Speak", this);

    speakButton->setFixedHeight(30);
    // Set button style using stylesheets
    speakButton->setStyleSheet("QPushButton {"
                          "background-color: #3498db;"  // Set background color
                          "color: white;"              // Set text color
                          "border: 2px solid #2980b9;" // Set border color
                          "border-radius: 5px;"        // Set border radius for rounded corners
                          "}");

    // Connect the button to the TTS functionality
    connect(speakButton, &QPushButton::clicked, this, &MainWindow::speakText);

    // Set up the layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(label);
    layout->addWidget(label2);
    layout->addWidget(languageComboBox);
    layout->addWidget(inputField);
    layout->addWidget(speakButton);
    setCentralWidget(centralWidget);


}

MainWindow::~MainWindow()
{
    delete speech;
}

void MainWindow::loadSettings()
{
    // Load saved settings from QSettings
    QSettings settings("MyCompany", "AdaptiveApp");
    QString fontSize = settings.value("fontSize", "Medium").toString();
    QString theme = settings.value("theme", "Light").toString();

    // Apply font size settings
    QFont font = label->font();
    QFont fontLabel2 = label2->font();
    if (fontSize == "Small") {
        font.setPointSize(10);
        fontLabel2.setPointSize(10);
    } else if (fontSize == "Medium") {
        font.setPointSize(20);
        fontLabel2.setPointSize(20);
    } else if (fontSize == "Large") {
        font.setPointSize(30);
        fontLabel2.setPointSize(30);
    }
    label->setFont(font);
    label2->setFont(font);

    // Apply theme settings
    if (theme == "Dark") {
        setStyleSheet("background-color: #2d2d2d; color: #ffffff;");
    } else {
        setStyleSheet(""); // Light theme, use default colors
    }
}

void MainWindow::applySettings()
{
    // Reload settings after changes and update the UI
    loadSettings();
}

void MainWindow::openSettingsDialog()
{
    // Open the settings dialog
    SettingsDialog settingsDialog(this);

    // Connect the signal to refresh the UI when settings change
    connect(&settingsDialog, &SettingsDialog::settingsChanged, this, &MainWindow::applySettings);

    // Show the dialog modally
    settingsDialog.exec();
}


void MainWindow::speakText()
{
    QString text = inputField->text();
    QVoice selectedVoice = languageComboBox->currentData().value<QVoice>();
    speech->setVoice(selectedVoice);  // Set the selected voice
    speech->say(text); // Text-to-speech will read the input text
}
