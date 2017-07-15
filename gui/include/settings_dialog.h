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
#include <QSettings>
namespace calculator {
    namespace gui {
        /**
         * @class SettingsDialog - class derived from QDialog.
         * Dialog settings for connecting to the server.
         * Also contains the username field, to identify clients.
         */
        class SettingsDialog : public QDialog {
        Q_OBJECT
        public:
            /**
             * @brief SettingsDialog - default constructor
             * @param parent - parent widget, see official Qt documentation for more information
             */
            SettingsDialog(QWidget *parent = Q_NULLPTR);

            /**
             * @brief ~SettingsDialog - destructor.
             * Also write settings if rememberMeBox checked (не уверен, что  самое правильное рещение,
             * но оно неоднократно проверено практикой)
             */
            virtual ~SettingsDialog();

        Q_SIGNALS:

            /**
             * @brief connectToHost - a signal sent when all fields are correctly filled
             * @param name - username, used as userId
             * @param ip - host address
             * @param port - port number
             */
            void connectToHost(const QString &name, const QString &ip, int port);

        private:
            /**
             * @brief createUi - creation  and initialization  all items of the user interface
             */
            void createUi();

            /**
             * @brief readSettings - read the  previous session state.
             * Use QSettings
             */
            void readSettings();

            /**
             * @brief writeSettings - if rememberMeBox checked, write the  current session state
             */
            void writeSettings();

            /**
             * @brief createConnections - set all required connections
             */
            void createConnections();

            /**
             * @brief hostLabel_
             */
            QLabel *hostLabel_;
            /**
             * @brief portLabel_
             */
            QLabel *portLabel_;
            /**
             * @brief nameLabel_
             */
            QLabel *nameLabel_;
            /**
             * @brief rememberMeBox_ - if checked then write current session state
             */
            QCheckBox *rememberMeBox_;
            /**
             * @brief acceptButton_
             */
            QPushButton *acceptButton_;
            /**
             * @brief cancelButton_
             */
            QPushButton *cancelButton_;
            /**
             * @brief helpButton_
             */
            QPushButton *helpButton_;
            /**
             * @brief buttonBox_ - contains helpButton_, acceptButton_, cancelButton_
             */
            QDialogButtonBox *buttonBox_;
            /**
             * @brief portBox_
             */
            QSpinBox *portBox_;
            /**
             * @brief hostEdit_
             */
            QLineEdit *hostEdit_;
            /**
             * @brief nameEdit_
             */
            QLineEdit *nameEdit_;
        public:
            /**
             * @brief MAX_PORT - min port value
             */
            const unsigned MIN_PORT = 1001;
            /**
             * @brief MAX_PORT max port value
             */
            const unsigned MAX_PORT = 9999;
        };
    }
}
