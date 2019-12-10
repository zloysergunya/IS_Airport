#ifndef WINDOW_AUTHORIZATION_H
#define WINDOW_AUTHORIZATION_H

#include <QWidget>
class User;

namespace Ui {
class SignIn;
}

class SignIn : public QWidget
{
	Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

private:
    Ui::SignIn *mUi;

	User *checkUser(const QString &login, const QString &password);

signals:
	void openRegistration();
	void succesfulEntry(User*);

private slots:
	void on_buttonEntry_clicked();
};

#endif // WINDOW_AUTHORIZATION_H
