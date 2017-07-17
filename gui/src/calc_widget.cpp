//
// Created by boa on 15.07.17.
//

#include "../include/calc_widget.h"
#include <QDebug>
namespace calculator {
    namespace gui {

        CalcWidget::CalcWidget(QWidget *parent) : QWidget(parent) {
            init();
            createUi();
            createConnections();
        }

        void CalcWidget::createUi() {
            for (unsigned i = 0; i < DIGIT_COUNT; ++i) {
                digitVector_.append(new QPushButton(QString::number(i), this));
            }
            operatorVector_.append(new QPushButton(QString("+"), this));
            operatorVector_.append(new QPushButton("-", this));
            operatorVector_.append(new QPushButton("\303\227", this));
            operatorVector_.append(new QPushButton("/", this));
            pointButton_ = new QPushButton(".", this);
            equalButton_ = new QPushButton("=", this);
            auto *gridLayout = new QGridLayout;
            gridLayout->setSizeConstraint(QLayout::SetFixedSize);
            display_ = new QLineEdit("0", this);
            display_->setReadOnly(true);
            display_->setAlignment(Qt::AlignRight);
            display_->setMaxLength(15);
            QFont font = display_->font();
            font.setPointSize(font.pointSize() + 8);
            display_->setFont(font);
            gridLayout->addWidget(display_, 0, 0, 1, 4);
            backspaceButton_ = new QPushButton("Backspace", this);
            gridLayout->addWidget(backspaceButton_, 1, 0, 1, 2);
            clearAllButton_ = new QPushButton("Clear All", this);
            gridLayout->addWidget(clearAllButton_, 1, 2);
            for (unsigned i = 1; i < DIGIT_COUNT; ++i) {
                int row = ((9 - i) / 3) + 2;
                int column = ((i - 1) % 3);
                gridLayout->addWidget(digitVector_[i], row, column);
            }
            for (auto i = 0; i < operatorVector_.count(); ++i) {
                gridLayout->addWidget(operatorVector_[i], i + 1, 3);
            }
            gridLayout->addWidget(digitVector_[0], 5, 0, 1, 2);
            gridLayout->addWidget(pointButton_, 5, 2);
            gridLayout->addWidget(equalButton_, 5, 3);
            setLayout(gridLayout);
        }

        void CalcWidget::createConnections() {
            for (auto button : digitVector_) {
                connect(button, &QPushButton::clicked, this, [this, button]() mutable {
                    auto digitValue = button->text().toInt();
                    if (display_->text() == "0" && digitValue == 0.0) { return; }
                    if (waitingOperand_) {
                        display_->clear();
                        waitingOperand_ = false;
                    }
                    display_->setText(display_->text() + QString::number(digitValue));
                });
            }
            connect(backspaceButton_, &QPushButton::clicked, this, [this]() mutable {
                if (waitingOperand_) { return; }
                QString text = display_->text();
                text.chop(1);
                if (text.isEmpty()) {
                    text = "0";
                    waitingOperand_ = true;
                }
                display_->setText(text);
            });
            connect(clearAllButton_, &QPushButton::clicked, this, [this]() mutable {
                if (waitingOperand_) { return; }
                display_->clear();
                display_->setText("0");
                waitingOperand_ = true;
            });

            connect(pointButton_, &QPushButton::clicked, this, [this]() mutable {
                if (waitingOperand_) {
                    display_->setText("0");
                }
                if (!display_->text().contains('.')) {
                    display_->setText(display_->text() + ".");
                }
                waitingOperand_ = false;
            });
            for (auto button : operatorVector_) {
                connect(button, &QPushButton::clicked, this, [this, button]() mutable {
                    expression_ << display_->text();
                    button->text() == "\303\227" ? expression_ << "*" : expression_ << button->text();
                    waitingOperand_ = true;
                });
            }
            connect(equalButton_, &QPushButton::clicked, this, [this]() {
                if (waitingOperand_) {
                    return;
                }
                expression_ << display_->text();//append last operand
                emit calculate(expression_);
            });
        }

        void CalcWidget::init() {
            digitVector_.reserve(DIGIT_COUNT);
            operatorVector_.reserve(OPERATOR_COUNT);
        }

        void CalcWidget::setCalcResult(const QString result) {
                    display_->setText(result);
        }
    }//namespace gui
}//namespace calculator