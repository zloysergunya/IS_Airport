#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include "user.h"

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    ~AddUser();
    const User &getUser() const;

private:
    Ui::AddUser *mUi;
    User m_user;

public slots:
    void accept();
    bool isLoginExists(const QString &login);
};

#endif // ADDUSER_H
