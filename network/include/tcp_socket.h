//
// Created by boa on 16.07.17.
//
#pragma once

#include <QTcpSocket>
#include "../../service/include/service.hpp"

using namespace calculator;
using namespace service;
namespace calculator {
    namespace network {
        /**
         * @class TcpSocket - socket for connectiong to server and sending/receiving messages
         */
        class TcpSocket : public QTcpSocket {
        Q_OBJECT
        public:
            /**
             * @brief TcpSocket - default constructor
             * @param parent
             */
            TcpSocket(QObject *parent = Q_NULLPTR);

            virtual ~TcpSocket();
            /**
             * @brief lastError - getter
             * @return return last socket error text
             */
            const QString &lastError();

        Q_SIGNALS:
            /**
             * @brief socketMessage - sent socket message
             * @param message
             */
            void socketMessage(const QString &message);
            /**
             * @brief calculationResult - sent received from server expression calculating status and result
             * @param status - calculation status
             * @param result calculation result
             */
            void calculationResult(const CalculationStatus status, const QString &result);

        public Q_SLOTS:
            /**
             * @brief sendCalculatedExpression  - sent texpression to server
             * @param expression calculated expression
             */
            void sendCalculatedExpression(const QStringList &expression);

        private Q_SLOTS:
            /**
             * @brief connectionOk -
             */
            void connectionOk();
            /**
             * @brief slotReadyRead - read server messages
             */
            void slotReadyRead();
            /**
             * @brief slotSocketError - socket error handler
             * @param socketError - see official Qt documentation
             */
            void slotSocketError(QAbstractSocket::SocketError socketError);

        private:
            QString lastError_;
            quint16 nextBlockSize_;
            QString name_;
        public:
            /**
             * @brief getName - getter
             * @return  socket name
             */
            const QString &getName() const;
            /**
             * @brief setName - setter
             * @param name_  - socket name
             */
            void setName(const QString &name_);
        };
    }
}


