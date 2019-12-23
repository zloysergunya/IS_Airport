#ifndef INFOUSER_H
#define INFOUSER_H

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

#endif // INFOUSER_H
