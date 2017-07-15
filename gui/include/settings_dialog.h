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
#include <QMessageBox>
namespace calculator {
    namespace gui {
        class SettingsDialog : public QDialog {
        Q_OBJECT
        public:
            SettingsDialog(QWidget *parent = Q_NULLPTR);

            virtual ~SettingsDialog();

        Q_SIGNALS:

            void connectToHost(const QString &name, const QString &ip, const unsigned port);
        private:
            void createUi();

            void createConnections();

            QLabel *hostLabel_;
            QLabel *portLabel_;
            QLabel *nameLabel_;
            QCheckBox *rememberMeBox_;
            QPushButton *acceptButton_;
            QPushButton *cancelButton_;
            QPushButton *helpButton_;
            QDialogButtonBox *buttonBox_;
            QSpinBox *portBox_;
            QLineEdit *hostEdit_;
            QLineEdit *nameEdit_;
            QLabel *statusLabel;
        public:
            const unsigned MIN_PORT = 1001;
            const unsigned MAX_PORT = 9999;
        };
    }
}
