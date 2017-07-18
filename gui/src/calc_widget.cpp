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
            for (unsigned i = 0; i < DIGIT_COUNT; ++i) {//create all digit buttons
                digitVector_.append(new QPushButton(QString::number(i), this));
            }
            operatorVector_.append(new QPushButton(QString("+"), this));// fill operator vector
            operatorVector_.append(new QPushButton("-", this));
            operatorVector_.append(new QPushButton("\303\227", this));
            operatorVector_.append(new QPushButton("/", this));
            pointButton_ = new QPushButton(".", this);//
            equalButton_ = new QPushButton("=", this);
            auto *gridLayout = new QGridLayout;//grid layout for placing elements
            gridLayout->setSizeConstraint(QLayout::SetFixedSize);// fixed layout size
            display_ = new QLineEdit("0", this);//init display
            display_->setReadOnly(true);
            display_->setAlignment(Qt::AlignRight);//set alignment to right
            display_->setMaxLength(15);// set max operand length
            QFont font = display_->font();// set display font
            font.setPointSize(font.pointSize() + 8);
            display_->setFont(font);
            gridLayout->addWidget(display_, 0, 0, 1, 4);//gill layout
            backspaceButton_ = new QPushButton("Backspace", this);
            gridLayout->addWidget(backspaceButton_, 1, 0, 1, 2);
            clearAllButton_ = new QPushButton("Clear All", this);
            gridLayout->addWidget(clearAllButton_, 1, 2);
            for (unsigned i = 1; i < DIGIT_COUNT; ++i) {
                int row = ((9 - i) / 3) + 2;// calculate row in layout
                int column = ((i - 1) % 3);// calculate column in layout
                gridLayout->addWidget(digitVector_[i], row, column);//place digit buttons in layout
            }
            for (auto i = 0; i < operatorVector_.count(); ++i) {//place operator buttons in layout
                gridLayout->addWidget(operatorVector_[i], i + 1, 3);
            }
            gridLayout->addWidget(digitVector_[0], 5, 0, 1, 2);
            gridLayout->addWidget(pointButton_, 5, 2);
            gridLayout->addWidget(equalButton_, 5, 3);
            setLayout(gridLayout);
        }

        void CalcWidget::createConnections() {
            for (auto button : digitVector_) {//connect with all digit buttons
                connect(button, &QPushButton::clicked, this, [this, button]() mutable {//i'm using lambda functions
                    // for  signal processing
                    auto digitValue = button->text().toInt();//get button integer value
                    if (display_->text() == "0" && digitValue == 0.0) { return; }//if first clicked button "0"
                    if (waitingOperand_) {//if previous clicked button is a operator
                        display_->clear();//clear display
                        waitingOperand_ = false;//Reset the operand's wait flag
                    }
                    display_->setText(display_->text() + QString::number(digitValue));//append next digit to operand
                });
            }
            connect(backspaceButton_, &QPushButton::clicked, this, [this]() mutable {
                if (waitingOperand_) { return; }//if waiting operand flag return
                QString text = display_->text();//get current display value
                text.chop(1);//remove last symbol
                if (text.isEmpty()) {//if all symbols removed
                    text = "0";//set default display value
                    waitingOperand_ = true;//set waiting operand flag
                }
                display_->setText(text);//update display text
            });
            connect(clearAllButton_, &QPushButton::clicked, this, [this]() mutable {
                if (waitingOperand_) { return; }//if waiting operand flag return
                display_->clear();//clear display
                display_->setText("0");//set display default value
                waitingOperand_ = true;//set waitng operand flag
            });

            connect(pointButton_, &QPushButton::clicked, this, [this]() mutable {
                if (waitingOperand_) {//if waiting operand flag
                    display_->setText("0");//set disolay default value
                }
                if (!display_->text().contains('.')) {//find the previous occurrence of the character
                    display_->setText(display_->text() + ".");//if not found, then append point symbol
                }
                waitingOperand_ = false;//reset waiting operand flag
            });
            for (auto button : operatorVector_) {//for all operator buttons
                connect(button, &QPushButton::clicked, this, [this, button]() mutable {
                    expression_ << display_->text();//append currend operand to expression
                    button->text() == "\303\227" ? expression_ << "*" : expression_ << button->text();//append operator
                    // symbol to expression
                    waitingOperand_ = true;//set waiting operand flag
                });
            }
            connect(equalButton_, &QPushButton::clicked, this, [this]() {
                if (waitingOperand_) {//check waiting operand flag
                    return;
                }
                expression_ << display_->text();//append last operand
                emit calculate(expression_);//send expression to server
            });
        }

        void CalcWidget::init() {
            digitVector_.reserve(DIGIT_COUNT);//reserve memory for digit buttons
            operatorVector_.reserve(OPERATOR_COUNT);//reserve memory for operator buttons
        }

        void CalcWidget::setCalcResult(const QString result) {

            display_->setText(result);//show calculation result
        }
    }//namespace gui
}//namespace calculator