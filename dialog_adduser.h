#ifndef DIALOG_ADDUSER_H
#define DIALOG_ADDUSER_H

#include <QDialog>
#include "user.h"

namespace Ui {
class Dialog_AddUser;
}

class Dialog_AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_AddUser(QWidget *parent = nullptr);
    ~Dialog_AddUser();
    const User &getUser() const;

private:
    Ui::Dialog_AddUser *mUi;
    User m_user;

public slots:
    void accept();
    bool isLoginExists(const QString &login);
};

#endif // DIALOG_ADDUSER_H
