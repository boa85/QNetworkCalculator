//
// Created by boa on 15.07.17.
//


#include "../include/main_window.h"
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
namespace calculator {
    namespace gui {
        MainWindow::MainWindow() {
            createUi();
            createConnections();
        }

        void MainWindow::createUi() {
            calcWidget_ = new CalcWidget();
            createMenus();
            createToolBars();
            createStatusBar();
        }

        void MainWindow::createConnections() {

        }

        void MainWindow::createMenus() {

        }

        void MainWindow::createToolBars() {

        }

        void MainWindow::createStatusBar() {

        }
    }
}