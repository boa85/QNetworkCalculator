//
// Created by boa on 15.07.17.
//


#include "../include/main_window.h"
#include "../include/settings_dialog.h"
#include <QList>
#include <QtWidgets/QApplication>
#include <QStatusBar>
#include <QDateTime>
namespace calculator {
    namespace gui {
        MainWindow::MainWindow() {
            init();
            createUi();
            createConnections();
            eventList_->addItem(QString("%1 start program").arg(QTime::currentTime().toString()));
        }

        void MainWindow::createUi() {
            move(X_, Y_);//set window position
            calcWidget_ = new CalcWidget(this);//create new CalcWidget
            setCentralWidget(calcWidget_);
            createActions();
            createMenus();
            createToolBars();
            createStatusBar();
        }

        void MainWindow::createConnections() {
            connect(settingsAction_, &QAction::triggered,
                    this, &MainWindow::showSettingsDialog);

            connect(quitAction_, &QAction::triggered, this, []() {
                QApplication::closeAllWindows();//close all windows and quit
            });
            connect(aboutAction_, &QAction::triggered, this, [this]() {
                QMessageBox::information(this, trUtf8("About program"),//show information about program
                                         trUtf8("Simple network calculator\n Author boa"),
                                         QMessageBox::Ok);
            });
            connect(aboutQtAction_, &QAction::triggered,
                    qApp, &QApplication::aboutQt);//show information about Qt
            connect(calcWidget_, &CalcWidget::calculate,
                    this, &MainWindow::sendCalculatedExpression);//
            connect(tcpSocket_, &TcpSocket::calculationResult, this,
                    [this](const CalculationStatus status, const QString &result) mutable {
                        switch (status) {//check calculation status
                            case SUCCESS:
                                addEvent("calculation successful");
                                calcWidget_->setCalcResult(result);//see description TcpSocket::setCalcResult
                                break;
                            case FAILED:
                                addEvent("calculation failed " + result);//show info about calculation error
                                break;
                        }
                    });
        }

        void MainWindow::createMenus() {//create menu items
            fileMenu_ = menuBar()->addMenu(trUtf8("&File"));
            fileMenu_->addActions(fileActions_);
            aboutMenu_ = menuBar()->addMenu(trUtf8("&Help"));
            aboutMenu_->addActions(aboutActions_);
        }

        void MainWindow::createToolBars() {

        }

        void MainWindow::createStatusBar() {
            eventList_ = new QListWidget;//init eventList_
            eventList_->setFixedHeight(150);// fixed eventList_ height
            statusBar()->addWidget(eventList_, 1);//add eventList_ to statusBar
            eventList_->sortItems(Qt::DescendingOrder);//set event order
        }

        void MainWindow::createActions() {//init actions and append to action list
            settingsAction_ = new QAction(trUtf8("Settings..."), this);
            fileActions_.append(settingsAction_);
            quitAction_ = new QAction(trUtf8("quit"), this);
            fileActions_.append(quitAction_);
            aboutAction_ = new QAction(trUtf8("About"), this);
            aboutActions_.append(aboutAction_);
            aboutQtAction_ = new QAction(trUtf8("About Qt..."), this);
            aboutActions_.append(aboutQtAction_);

        }

        void MainWindow::setServerSettings(const QString &name, const QString &hostName, const int portNumber) {
            hostName_ = hostName;
            portNumber_ = portNumber;
            tcpSocket_->setName(name);
            tcpSocket_->connectToHost(hostName_, portNumber_);//connect to host with new parameters
            qDebug() << QString("name %1, ip %2, port %3").arg(clientName_).arg(hostName_).arg(portNumber_);
        }

        void MainWindow::sendCalculatedExpression(const QStringList &expression) {
            if (tcpSocket_->state() == QTcpSocket::ConnectedState) {//if connection to server success
                tcpSocket_->sendCalculatedExpression(expression);//send expression to server
            } else {
                addEvent(QString("connection error %1, please enter right server settings").arg(
                        tcpSocket_->lastError()));//show socket error message
                showSettingsDialog();// show settings dialog
            }
        }

        void MainWindow::addEvent(const QString &message) {
            eventList_->addItem(QTime::currentTime().toString() + " " + message);//show next message in statusBar
        }

        void MainWindow::init() {
            tcpSocket_ = new TcpSocket(this);
        }

        void MainWindow::showSettingsDialog() {
            SettingsDialog *dialog = new SettingsDialog(this);//blocked main window
            dialog->show();//show settings dialog
            connect(dialog, &SettingsDialog::serverSettings,
                    this, &MainWindow::setServerSettings);
        }
    }//namespace gui
}//namespace calculator