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

            /**
             * connect items with signals and slots
             */
            void createConnections();

            /**
             * @brief - vector of pointers to QPushButton. Each button  contains a digit
             */
            QVector<QPushButton *> digitVector_;
            /**
             * @brief- vector of pointers to QPushButton. Each button  contains a operator symbol
             */
            QVector<QPushButton *> operatorVector_;
            /**
             * @brief - read only QLineEdit for view the expression and  result of calculation
             */
            QLineEdit *display_;
            /**
             * @brief - button separation integer and fractional part of the number
             */
            QPushButton *pointButton_;
            /**
             * @brief - check waiting operand and send expression to server
             */
            QPushButton *equalButton_;
            /**
             * @brief - removing last symbol
             */
            QPushButton *backspaceButton_;
            /**
             * @brief - clear displat and set value 0
             */
            QPushButton *clearAllButton_;
            /**
             * @brief - true if last clicked button is a operator or display has been cleared
             * (calculated expression is empty)
             */
            bool waitingOperand_ = true;
            /**
             * @brief - expression to calculation
             */
            QStringList expression_;
            /**
             * @brief init - init fields a default value
             */
            void init();
        };
    }//namespace gui
}//namespace calculator