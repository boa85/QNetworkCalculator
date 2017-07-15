//
// Created by boa on 15.07.17.
//
#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QDialogButtonBox>

namespace calculator {
    namespace gui {
        class SettingsDialog : public QDialog {
        Q_OBJECT
        public:
            SettingsDialog(QWidget *parent = Q_NULLPTR);

            virtual ~SettingsDialog();

        private:
            void createUi();

            void createConnections();

            QLabel *hostLabel;
            QLabel *portLabel;
            QLabel *nameLabel;
            QCheckBox *rememberMeBox;
            QPushButton *acceptButton;
            QPushButton *cancelButton;
            QPushButton *helpButton;
            QDialogButtonBox *buttonBox;
            QLabel *statusLabel;
        };
    }
}
