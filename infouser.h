#ifndef DIALOG_INFOUSER_H
#define DIALOG_INFOUSER_H

#include <QDialog>
class User;

namespace Ui {
class InfoUser;
}

class InfoUser : public QDialog
{
    Q_OBJECT

public:

    explicit InfoUser(const User &user, QWidget *parent = nullptr);
    ~InfoUser();

private:
    Ui::InfoUser *mUi;
};

#endif // DIALOG_INFOUSER_H
