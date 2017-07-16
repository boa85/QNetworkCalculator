//
// Created by boa on 16.07.17.
//
#pragma once

#include <QTcpSocket>

namespace calculator {
    namespace network {
        enum CalculationStatus {
            SUCCESS = 0,
            FAILED = 1
        };

        class TcpSocket : public QTcpSocket {
        Q_OBJECT


        public:
            TcpSocket(QObject *parent = Q_NULLPTR);

            virtual ~TcpSocket();

            const QString &lastError();

        Q_SIGNALS:

            void socketMessage(const QString &message);

            void calculationResult(const QString &result);

        public Q_SLOTS:

            void sendCalculatedExpression(const QStringList &expression);

        private Q_SLOTS:

            void connectionOk();

            void slotReadyRead();

            void slotSocketError(QAbstractSocket::SocketError socketError);

        private:
            QString lastEroror_;
            quint16 nextBlockSize_;
            QString name_;
        public:
            const QString &getName() const;

            void setName(const QString &name_);
        };

    }
}


