//
// Created by boa on 15.07.17.
//
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QListWidget>
#include "calc_widget.h"
#include "../../network/include/tcp_socket.h"

#pragma once
using namespace calculator;
using namespace gui;
using namespace network;
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



        private:
            void createUi();

            void createConnections();

            void createMenus();

            void createActions();

            void createToolBars();

            void createStatusBar();

            void init();
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
            QString hostName_;
            int portNumber_;
            bool isConnected_;
            QListWidget *eventList_;
            TcpSocket *tcpSocket_;

        private Q_SLOTS:

            void setServerSettings(const QString &name, const QString &hostName, const int portNumber);

            void addEvent(const QString &message);

            void showSettingsDialog();

            void sendCalculatedExpression(const QStringList &expression);
        public:
            const unsigned X_ = 200;
            const unsigned Y_ = 200;


        };
    }//namespace gui
}//namespace calculator