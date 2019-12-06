#ifndef WINDOW_AUTHORIZATION_H
#define WINDOW_AUTHORIZATION_H

#include <QWidget>
class User;

namespace Ui {
class Window_Authorization;
}

class Window_Authorization : public QWidget
{
	Q_OBJECT

public:
	explicit Window_Authorization(QWidget *parent = nullptr);
	~Window_Authorization();

private:
	Ui::Window_Authorization *mUi;

	User *checkUser(const QString &login, const QString &password);

signals:
	void openRegistration();
	void succesfulEntry(User*);

private slots:
	void on_buttonEntry_clicked();
};

#endif // WINDOW_AUTHORIZATION_H
