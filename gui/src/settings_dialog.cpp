//
// Created by boa on 15.07.17.
//

#include "../include/settings_dialog.h"

namespace calculator {
    namespace gui {

        SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
            createUi();
            createConnections();
        }

        SettingsDialog::~SettingsDialog() {

        }

        void SettingsDialog::createUi() {
            setWindowTitle("Server settings");//
            hostLabel_ = new QLabel(trUtf8("host name"));
            hostEdit_ = new QLineEdit;
            QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
            /**
             * @brief ipRegex - simple regex for ip addresses
             * (only ip v4, ip v6 на сервере используется
             * только для демонстрации разбора аргументов командной строки)
             */
            QRegExp ipRegex("^" + ipRange
                            + "\\." + ipRange
                            + "\\." + ipRange
                            + "\\." + ipRange + "$");
            QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
            hostEdit_->setValidator(ipValidator);//set validator for correctly input ip address
            hostEdit_->setToolTip(trUtf8("Type a string of the form: 192.168.1.1"));
            //initialization the user interface items
            portLabel_ = new QLabel(trUtf8("port"));
            nameLabel_ = new QLabel(trUtf8("user name"));
            nameEdit_ = new QLineEdit;
            rememberMeBox_ = new QCheckBox(trUtf8("remember me"));
            acceptButton_ = new QPushButton(trUtf8("Ok"));
            cancelButton_ = new QPushButton(trUtf8("Cancel"));
            helpButton_ = new QPushButton(trUtf8("help"));
            buttonBox_ = new QDialogButtonBox;
            buttonBox_->addButton(acceptButton_, QDialogButtonBox::AcceptRole);
            buttonBox_->addButton(cancelButton_, QDialogButtonBox::RejectRole);
            buttonBox_->addButton(helpButton_, QDialogButtonBox::HelpRole);
            portBox_ = new QSpinBox;
            portBox_->setRange(MIN_PORT, MAX_PORT);
            //set layout, тута все просто - по сетке расставили и радуемся жизни
            QGridLayout *gridLayout = new QGridLayout;
            gridLayout->addWidget(nameLabel_, 0, 0);
            gridLayout->addWidget(nameEdit_, 0, 1, 1, 2);
            gridLayout->addWidget(hostLabel_, 1, 0);
            gridLayout->addWidget(hostEdit_, 1, 1, 1, 2);
            gridLayout->addWidget(portLabel_, 2, 0);
            gridLayout->addWidget(portBox_, 2, 2);
            gridLayout->addWidget(rememberMeBox_, 3, 2);
            QHBoxLayout *boxLayout = new QHBoxLayout;
            boxLayout->addWidget(buttonBox_);
            boxLayout->addStretch();
            gridLayout->addLayout(boxLayout, 4, 0, 1, 2);
            setLayout(gridLayout);
        }

        void SettingsDialog::createConnections() {
            connect(cancelButton_, &QPushButton::clicked, this, &QDialog::close);
            connect(helpButton_, &QPushButton::clicked, this, [this]() {
                QMessageBox::information(this, trUtf8("About settings"),
                                         trUtf8("Please enter username, "
                                                        "host address in format \"192.168.0.1\","
                                                        "port: in 1001-9999 range"),
                                         QMessageBox::Ok);
            });
            connect(acceptButton_, &QPushButton::clicked, this, [this]() {
                if (!nameEdit_->text().isEmpty() && !hostEdit_->text().isEmpty()) {//порт не проверяю специально,
                    //т.к. там задан диапазон значений и накосячить трудно
                    // проверкк поставил самую примитивную
                    //If all fields are filled correctly
                    emit serverSettings(nameEdit_->text(), hostEdit_->text(), portBox_->value());
                    close();
                } else {// show warning
                    QMessageBox::warning(this,
                                         trUtf8("WARNING"),
                                         trUtf8("Please fill in the username and server address fields,"
                                                        " see help for more information"),
                                         QMessageBox::Ok);
                    hostEdit_->setFocus();
                }
            });
        }

        void SettingsDialog::readSettings() {

        }

        void SettingsDialog::writeSettings() {

        }
    }//namespace gui
}//namespace calculator