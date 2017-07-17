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
#include "../../service/include/service.hpp"

using namespace calculator;
using namespace service;
namespace calculator {
    namespace gui {
        /**
         * @class CalcWidget - собственно сам калькулятор, с кнопочками
         */
        class CalcWidget : public QWidget {
        Q_OBJECT
        public:
            /**
             * @brief CalcWidget - default constructor
             * @param parent
             */
            CalcWidget(QWidget *parent = Q_NULLPTR);

            const unsigned DIGIT_COUNT = 10;
            const unsigned OPERATOR_COUNT = 4;
        signals:
            /**
             * @brief calculate - sent calculated expression to TcpSocket
             * @param expression
             */
            void calculate(QStringList &expression);

        public Q_SLOTS:
            /**
             * @brief setCalcResult - show calculations result into display
             * @param result calculations result
             */
            void setCalcResult(const QString result);
        private:
            /**
             * @brief createUi - init UI items and
             */
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
            /**
             * @brief init - init fields a default value
             */
            void init();
        };
    }//namespace gui
}//namespace calculator