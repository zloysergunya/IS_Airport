#ifndef WINDOW_REGISTRATION_H
#define WINDOW_REGISTRATION_H

#include <QWidget>

namespace Ui {
class Window_Registration;
}

class Window_Registration : public QWidget
{
	Q_OBJECT

public:
	enum TypeRegistration { Passenger, Admin };

	explicit Window_Registration(TypeRegistration typeReg, QWidget *parent = nullptr);
	~Window_Registration();

private:
	Ui::Window_Registration *mUi;
	TypeRegistration m_typeReg;
	bool isLoginExists(const QString &login);

signals:
	void openAuthorization();

private slots:
	void on_buttonCreate_clicked();
};

#endif // WINDOW_REGISTRATION_H
