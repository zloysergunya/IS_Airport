#include "dialog_infouser.h"
#include "ui_dialog_infouser.h"

#include "user.h"

Dialog_InfoUser::Dialog_InfoUser(const User &user, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::Dialog_InfoUser)
{
    mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
    mUi->labelLogin->setText(user.login());
    QString pass = "";
    for (int i = 0; i < user.password().size(); i++) {
        pass += '*';
    }
    mUi->labelPassword->setText(pass);
    mUi->labelStatus->setText(user.statusString());
}

Dialog_InfoUser::~Dialog_InfoUser()
{
    delete mUi;
}
