//
// Created by boa on 15.07.17.
//
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QListWidget>
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

        Q_SIGNALS:

            /**
             * @brief connectToHost - a signal sent when all fields are correctly filled
             * @param name - username, used as userId
             * @param ip - host address
             * @param port - port number
             */
            void connectToHost(const QString &name, const QString &ip, int port);


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
            QString clientName_;
            QString hostAddress_;
            int portNumber_;
            bool isConnected_;
            QListWidget *eventList_;
        private Q_SLOTS:

            void setServerSettings(const QString &name, const QString &hostAddress, const int portNumber);

            void sendCalculatedExpression(const QStringList &expression);
        public:
            const unsigned X_ = 200;
            const unsigned Y_ = 200;
        };
    }
}