#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextToSpeech>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openSettingsDialog();
    void applySettings();

private:
    void loadSettings();

    QLabel *label;
    QLabel *label2;
    QComboBox *languageComboBox;


private slots:
    void speakText();

private:
QTextToSpeech *speech;
QLineEdit *inputField;
QPushButton *speakButton;
};

#endif // MAINWINDOW_H
