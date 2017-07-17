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
         * @class MainWindow contains all user interface items
         */
        class MainWindow : public QMainWindow {
        Q_OBJECT
        public:
            /**
             * @brief MainWindow - default constructor
             */
            MainWindow();
        Q_SIGNALS:
        private:
            /**
             * @brief createUi - initialization user interface items: menu, statusBar, toolBar and other
             */
            void createUi();

            /**
             * @brief createConnections - connect items with signals and slots
             */
            void createConnections();

            /**
             * @brief createMenus - initialization and fill menu items
             */
            void createMenus();

            /**
             * @brief createActions - initialization actions
             */
            void createActions();

            /**
             * @brief createToolBars - see name
             */
            void createToolBars();

            /**
             * @brief createStatusBar - create status bar
             */
            void createStatusBar();

            /**
             * @brief init - init fields default values
             */
            void init();

            /**
             * @see @class CalcWidget
             */
            CalcWidget *calcWidget_;
            /**
             * @brief   fileMenu_ - contains the standard file menu
             */
            QMenu *fileMenu_;
            /**
             * @brief settingsAction_ - QAction, on triggered show SettingsDialog
             */
            QAction *settingsAction_;
            /**
             * @brief  quitAction_ - close all windows
             */
            QAction *quitAction_;
            /**
             * @brief  fileActions_ - container with file menu actions
             */
            QList<QAction *> fileActions_;
            /**
             * @brief aboutMenu_ - standard about menu
             */
            QMenu *aboutMenu_;
            /**
             * @brief  aboutAction_ - onTriggered - show standard about program dialog
             */
            QAction *aboutAction_;
            /**
             * @brief   aboutQtAction_ - show standard about Qt dialog
             */
            QAction *aboutQtAction_;
            /**
             * @brief  aboutActions_ - container with about menu items
             */
            QList<QAction *> aboutActions_;
            /**
             * @brief  clientName_ - client name for identification into server
             */
            QString clientName_;
            /**
             * @brief  hostName_ - server hostname
             */
            QString hostName_;
            /**
             * @brief  portNumber_ - server port
             */
            int portNumber_;
            /**
             * @brief  eventList - show all server and client messages into status bar
             */
            QListWidget *eventList_;
            /**
             * @brief  tcpSocket_ - socket for connection to server and send/receive messages
             */
            TcpSocket *tcpSocket_;

        private Q_SLOTS:

            /**
             * @brief setServerSettings - setter, called if SettingsDialog sent signal
             * @param name  - client name
             * @param hostName - hostname
             * @param portNumber - number of listen port
             */
            void setServerSettings(const QString &name, const QString &hostName, const int portNumber);
            /**
             * @brief addEvent - add item to eventList_
             * @param message
             */
            void addEvent(const QString &message);
            /**
             * @brief showSettingsDialog - created and show new SettingsDialog
             */
            void showSettingsDialog();
            /**
             * @brief sendCalculatedExpression - send calculated expression to server
             * @param expression calculated expression
             */
            void sendCalculatedExpression(const QStringList &expression);
        public:
            /**
             * @brief X_ - screen coordinates
             */
            const unsigned X_ = 200;
            /**
             * @brief  Y_ - screen coordinates
             */
            const unsigned Y_ = 200;


        };
    }//namespace gui
}//namespace calculator