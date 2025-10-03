#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    countdownTimer(new QTimer(this)),
    counter(cntr),
    trayIcon(new QSystemTrayIcon(this)),
    adBlocker(new AdBlockerFunc())
{
    ui->setupUi(this);

    adBlocker->loadAdDomainList("ad_domains.txt");

    connect(ui->chBox, &QCheckBox::stateChanged, this, &MainWindow::onCheckBoxStateChanged);
    connect(countdownTimer, &QTimer::timeout, this, &MainWindow::onCountdown);
    connect(ui->rBtnA, &QRadioButton::clicked, this, &MainWindow::onRadioButtonASelected);
    connect(ui->rBtnB, &QRadioButton::clicked, this, &MainWindow::onRadioButtonBSelected);

    trayIcon->setIcon(QIcon("C:/dev/Git/AdBlocker/icon/ShowHide/ads.png"));
    trayIcon->setToolTip("광고 차단 활성화됨");

    connect(trayIcon, &QSystemTrayIcon::activated, this, [=](QSystemTrayIcon::ActivationReason reason){
        if (reason == QSystemTrayIcon::Trigger) {
            this->showNormal();
            this->raise();
            this->activateWindow();
        }
    });
}

MainWindow::~MainWindow() {
    delete adBlocker;
    delete ui;
}

void MainWindow::onCheckBoxStateChanged(int state) {
    if (state == Qt::Checked) {
        counter = cntr;
        ui->chBox->setText(QString::number(counter));
        countdownTimer->start(1000);
    } else {
        countdownTimer->stop();
        ui->chBox->setText("");
        this->show();
    }
}

void MainWindow::onCountdown() {
    if (counter > 0) {
        counter--;
        ui->chBox->setText(QString::number(counter));
    } else {
        countdownTimer->stop();
        ui->chBox->setText("");
        this->hide();
        trayIcon->show();
    }
}

void MainWindow::onRadioButtonASelected() {
    adBlocker->enableAdBlocking();
    adBlocker->blockDNSRequest("ads.example.com");
    adBlocker->blockDNSRequest("tracking.adsite.net");
    adBlocker->blockDNSRequest("banner.ads.org");
}

void MainWindow::onRadioButtonBSelected() {
    adBlocker->disableAdBlocking();
}
