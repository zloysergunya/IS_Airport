#include "dialog_adduser.h"
#include "ui_dialog_adduser.h"

Dialog_AddUser::Dialog_AddUser(QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::Dialog_AddUser)
{
    mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
}

Dialog_AddUser::~Dialog_AddUser()
{
    delete mUi;
}

const User &Dialog_AddUser::getUser() const
{
    return m_user;
}

void Dialog_AddUser::accept()
{
    const QString login = mUi->login->text();
    const QString password = mUi->password->text();
    User::Status status = User::getListStatus().key(mUi->status->currentText());

    if (login.isEmpty() || password.isEmpty()) {
        mUi->labelError->setText("Ошибка: заполните все поля!");
    }
    else if (login.size() < 3 || login.size() > 20) {
        mUi->labelError->setText("Ошибка: имя пользователя должено содержать от 3 до 20 символов!");
    }
    else if (password.size() < 6 || password.size() > 15) {
        mUi->labelError->setText("Ошибка: пароль должен содержать от 6 до 15 символов!");
    }
    else { // Если всё ОК...
        m_user.setData(login, password, status);

        QDialog::accept();
    }
}
