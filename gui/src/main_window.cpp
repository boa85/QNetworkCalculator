//
// Created by boa on 15.07.17.
//


#include "../include/main_window.h"

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