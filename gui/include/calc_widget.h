//
// Created by boa on 15.07.17.
//
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QLayout>

namespace calculator {
    namespace gui {
        class CalcWidget : public QWidget {
        public:
            CalcWidget(QWidget *parent = Q_NULLPTR);

        private:
            void createUi();

            void createConnections();

        };
    }
}