//
// Created by boa on 15.07.17.
//


#include "../include/main_window.h"
#include "../include/settings_dialog.h"
#include <QList>
#include <QtWidgets/QApplication>
#include <QDebug>
#include <QStatusBar>
#include <QDateTime>
namespace calculator {
    namespace gui {
        MainWindow::MainWindow() {
            createUi();
            createConnections();
            eventList_->addItem(QString("start program %1").arg(QTime::currentTime().toString()));
        }

        void MainWindow::createUi() {
            move(X_, Y_);
            calcWidget_ = new CalcWidget(this);
            setCentralWidget(calcWidget_);
            createActions();
            createMenus();
            createToolBars();
            createStatusBar();
        }

        void MainWindow::createConnections() {
            connect(settingsAction_, &QAction::triggered, this, [this]() {
                SettingsDialog *dialog = new SettingsDialog;
                dialog->show();
                connect(dialog, &SettingsDialog::serverSettings, this, &MainWindow::setServerSettings);
            });
            connect(quitAction_, &QAction::triggered, this, []() {
                QApplication::closeAllWindows();
            });
            connect(aboutAction_, &QAction::triggered, this, [this]() {
                QMessageBox::information(this, trUtf8("About program"),
                                         trUtf8("Simple network calculator\n Author boa"),
                                         QMessageBox::Ok);
            });
            connect(aboutQtAction_, &QAction::triggered,
                    qApp, &QApplication::aboutQt);
        }

        void MainWindow::createMenus() {
            fileMenu_ = menuBar()->addMenu(trUtf8("&File"));
            fileMenu_->addActions(fileActions_);
            aboutMenu_ = menuBar()->addMenu(trUtf8("&Help"));
            aboutMenu_->addActions(aboutActions_);

        }

        void MainWindow::createToolBars() {

        }

        void MainWindow::createStatusBar() {
            eventList_ = new QListWidget;
            eventList_->setFixedHeight(150);
            statusBar()->addWidget(eventList_, 1);
            eventList_->sortItems(Qt::DescendingOrder);
        }

        void MainWindow::createActions() {
            settingsAction_ = new QAction(trUtf8("Settings..."), this);
            settingsAction_->setIcon(QIcon(":/images/settings.png"));
            fileActions_.append(settingsAction_);
            quitAction_ = new QAction(trUtf8("quit"), this);
            fileActions_.append(quitAction_);
            aboutAction_ = new QAction(trUtf8("About"), this);
            aboutActions_.append(aboutAction_);
            aboutQtAction_ = new QAction(trUtf8("About Qt..."), this);
            aboutActions_.append(aboutQtAction_);

        }

        void MainWindow::setServerSettings(const QString &name, const QString &hostAddress, const int portNumber) {
            clientName_ = name;
            hostAddress_ = hostAddress;
            portNumber_ = portNumber;
            qDebug() << QString("name %1, ip %2, port %3").arg(clientName_).arg(hostAddress_).arg(portNumber_);
        }

        void MainWindow::sendCalculatedExpression(const QStringList &expression) {
            if (isConnected_) {
                
            }
        }
    }
}