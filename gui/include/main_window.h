//
// Created by boa on 15.07.17.
//
#include <QMainWindow>
#include "calc_widget.h"

#pragma once
using namespace calculator;
using namespace gui;
namespace calculator {
    namespace gui {
        class MainWindow : public QMainWindow {
        Q_OBJECT
        public:
            MainWindow();

        private:
            void createUi();

            void createConnections();

            void createMenus();

            void createToolBars();

            void createStatusBar();

            CalcWidget *calcWidget_;
        };
    }
}