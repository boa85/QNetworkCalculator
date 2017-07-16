//
// Created by boa on 15.07.17.
//
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QLayout>
#include <QLineEdit>
namespace calculator {
    namespace gui {
        class CalcWidget : public QWidget {
        public:
            CalcWidget(QWidget *parent = Q_NULLPTR);

            const unsigned DIGIT_COUNT = 10;
            const unsigned OPERATOR_COUNT = 4;

            void calculate(const QStringList &expression);

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

            QVector<QPushButton *> digitVector_;
            QVector<QPushButton *> operatorVector_;
            QLineEdit *display_;
            QPushButton *pointButton_;
            QPushButton *equalButton_;
            QPushButton *backspaceButton_;
            QPushButton *clearAllButton_;
            bool waitingOperand_ = false;
            QStringList expression_;

            void init();
        };
    }
}