#ifndef DIALOG_CONTROLUSERS_H
#define DIALOG_CONTROLUSERS_H

#include <QDialog>
#include "user.h"

namespace Ui {
class Dialog_ControlUsers;
}

class Dialog_ControlUsers : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ControlUsers(QWidget *parent = nullptr);
    ~Dialog_ControlUsers();

private slots:
    void slotUpAndDownStatus();
    void on_buttonDeleteUser_clicked();
    void on_buttonAddUser_clicked();
    void on_lineFind_textChanged(const QString &arg1);

private:
    Ui::Dialog_ControlUsers *mUi;
    QList<User> m_listUsers;
    int countAdmins() const;
};

#endif // DIALOG_CONTROLUSERS_H
