//
// Created by boa on 15.07.17.
//


#include "../include/main_window.h"
#include "../include/settings_dialog.h"
/**
    hostEdit        = new QLineEdit;
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    hostEdit->setValidator(ipValidator);
    hostEdit->setToolTip(trUtf8("Введите строку вида 192.168.1.1"));
    widgetList.append(hostEdit);

    portBox         = new QSpinBox;
    portBox->setMaximum(9999);
    portBox->setMinimum(1025);
    portBox->setValue(1025);
 */
#include <QList>
#include <QtWidgets/QApplication>
#include <QMessageBox>
namespace calculator {
    namespace gui {
        MainWindow::MainWindow() {

            createUi();
            createConnections();
        }

        void MainWindow::createUi() {
            move(X_, Y_);
            calcWidget_ = new CalcWidget(this);
            createActions();
            createMenus();
            createToolBars();
            createStatusBar();
        }

        void MainWindow::createConnections() {

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

        }

        void MainWindow::createActions() {
            settingsAction_ = new QAction(trUtf8("Settings..."), this);
            settingsAction_->setIcon(QIcon(":/images/settings.png"));
            connect(settingsAction_, &QAction::triggered, this, [this]() {
                SettingsDialog *dialog = new SettingsDialog;
                dialog->show();
            });
            fileActions_.append(settingsAction_);
            quitAction_ = new QAction(trUtf8("quit"), this);
            connect(quitAction_, &QAction::triggered, this, [=]() {
                QApplication::closeAllWindows();
            });
            fileActions_.append(quitAction_);
            aboutAction_ = new QAction(trUtf8("About"), this);
            connect(aboutAction_, &QAction::triggered, this, [this]() {
                QMessageBox::information(this, trUtf8("About program"),
                                         trUtf8("Simple network calculator\n Author boa"),
                                         QMessageBox::Ok);
            });
            aboutActions_.append(aboutAction_);
            aboutQtAction_ = new QAction(trUtf8("About Qt..."), this);
            connect(aboutQtAction_, &QAction::triggered,
                    qApp, &QApplication::aboutQt);
            aboutActions_.append(aboutQtAction_);

        }
    }
}