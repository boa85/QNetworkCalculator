//
// Created by boa on 15.07.17.
//
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include "calc_widget.h"

#pragma once
using namespace calculator;
using namespace gui;
namespace calculator {
    namespace gui {
        /**
         *
         */
        class MainWindow : public QMainWindow {
        Q_OBJECT
        public:
            MainWindow();

        private:
            void createUi();

            void createConnections();

            void createMenus();

            void createActions();

            void createToolBars();

            void createStatusBar();

            CalcWidget *calcWidget_;
            QMenu *fileMenu_;
            QAction *settingsAction_;
            QAction *quitAction_;
            QList<QAction *> fileActions_;
            QMenu *aboutMenu_;
            QAction *aboutAction_;
            QAction *aboutQtAction_;
            QList<QAction *> aboutActions_;

        public:
            const unsigned X_ = 200;
            const unsigned Y_ = 200;
        };
    }
}