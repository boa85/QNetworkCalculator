//
// Created by boa on 16.07.17.
//

#include "../include/tcp_socket.h"
#include <QDataStream>

namespace calculator {
    namespace network {

        TcpSocket::TcpSocket(QObject *parent) : QTcpSocket(parent),
                                                nextBlockSize_(0) {
            connect(this, &QTcpSocket::readyRead, this, &TcpSocket::slotReadyRead);
            connect(this, SIGNAL(error(QAbstractSocket::SocketError)),
                    SLOT(slotSocketError(QAbstractSocket::SocketError)));
            connect(this, &QTcpSocket::connected, this, &TcpSocket::connectionOk);
        }

        TcpSocket::~TcpSocket() {

        }

        void TcpSocket::slotReadyRead() {
            QDataStream in(this);
            in.setVersion(QDataStream::Qt_4_3);
            if (nextBlockSize_ == 0) {
                if (bytesAvailable() < (int) sizeof(quint16)) {
                    return;
                }
                in >> nextBlockSize_;
            }
            if (bytesAvailable() < nextBlockSize_) {
                return;
            }
            int status;
            in >> status;
            switch (status) {
                case CalculationStatus::SUCCESS: {
                    QString res;
                    in >> res;
                    emit calculationResult(res);
                    break;
                }
                case CalculationStatus::FAILED: {
                    QString serverMessage;
                    in >> serverMessage;
                    emit socketMessage(serverMessage);
                    break;
                }
                default:
                    emit socketMessage("unknown server operation type");
                    break;
            }
        }

        void TcpSocket::slotSocketError(QAbstractSocket::SocketError socketError) {
            switch (socketError) {
                case QAbstractSocket::RemoteHostClosedError: {
                    lastEroror_ = "Remote host close error";
                    emit socketMessage(lastEroror_);
                    break;
                }
                case QAbstractSocket::HostNotFoundError: {
                    lastEroror_ = "The host was not found. Please check the host name and port settings.\n";
                    emit socketMessage(lastEroror_);
                    break;
                }
                case QAbstractSocket::ConnectionRefusedError: {
                    lastEroror_ = "The connection was refused by the peer.\n"
                            "Make sure the  server is running,\n"
                            "and check that the host name and port\n"
                            "settings are correct.\n";
                    emit socketMessage(lastEroror_);
                    break;
                }
                default:
                    lastEroror_ = QString("The following error occurred: %1.\n").arg(errorString());
                    emit socketMessage(lastEroror_);
            }

        }

        void TcpSocket::sendCalculatedExpression(const QStringList &expression) {
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_3);
            out << quint16(0) << name_ << expression;
            out.device()->seek(0);
            out << quint16(block.size() - sizeof(quint16));
            write(block);
        }

        const QString &TcpSocket::lastError() {
            return lastEroror_;
        }

        void TcpSocket::connectionOk() {
            emit socketMessage("connections successful");
        }

        const QString &TcpSocket::getName() const {
            return name_;
        }

        void TcpSocket::setName(const QString &name_) {
            TcpSocket::name_ = name_;
        }
    }
}
