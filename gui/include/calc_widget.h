//
// Created by boa on 15.07.17.
//
#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QLayout>
#include <QLineEdit>
namespace calculator {
    namespace gui {
        class CalcWidget : public QWidget {
        Q_OBJECT
        public:
            CalcWidget(QWidget *parent = Q_NULLPTR);

            const unsigned DIGIT_COUNT = 10;
            const unsigned OPERATOR_COUNT = 4;
        signals:

            void calculate(QStringList &expression);


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
            bool waitingOperand_ = true;
            QStringList expression_;

            void init();
        };
    }
}