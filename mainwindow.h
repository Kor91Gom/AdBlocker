#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QIcon>
#include <QRadioButton>
#include <QCheckBox>
#include "adblockerfunc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCheckBoxStateChanged(int state);
    void onCountdown();
    void onRadioButtonASelected();
    void onRadioButtonBSelected();

private:
    Ui::MainWindow *ui;
    QTimer *countdownTimer;
    int counter;
    constexpr static int cntr = 14;
    QSystemTrayIcon *trayIcon;
    AdBlockerFunc *adBlocker;
};

#endif // MAINWINDOW_H
