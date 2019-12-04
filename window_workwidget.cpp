#include "window_workwidget.h"
#include "ui_window_workwidget.h"

#include "config.h"
#include "dialog_infouser.h"
//#include "dialog_menuadmin.h"
//#include "dialog_menucashier.h"

#include <QFile>
#include <QDataStream>

#include <QDebug>

Window_WorkWidget::Window_WorkWidget(User &user, QWidget *parent) :
	QWidget(parent),
	mUi(new Ui::Window_WorkWidget),
	m_user(user)
{
	mUi->setupUi(this);
	// Устанавливаем ширину столбцов под размер содержимого.
	mUi->tableRaces->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

	// Выделяем память под окно с информацией о пользователе
	m_infoDialog = new Dialog_InfoUser(m_user, this);
	m_infoDialog->setWindowTitle(Config::nameApplication);

	// Если статус пользователя не равен Администратору, то прячем кнопку с открытием меню администратора
	if (m_user.status() != User::Admin)
		mUi->menuAdmin->hide();

	if (m_user.status() != User::Passenger)
		connect(mUi->tableRaces, SIGNAL(cellActivated(int, int)),
				this, SLOT(menuCashier(int, int)));

	// Загружаем список поездов и вагонов из файла в лист и таблицу
    //loadTrains();
}

Window_WorkWidget::~Window_WorkWidget()
{
	// Очищаем память
	delete mUi;
	delete m_infoDialog;

	delete &m_user;
}


void Window_WorkWidget::on_infoUser_clicked()
{
	// Если была нажата кнопка "Сменить пользователя" то окно вернет значение QDialog::Accepted
	// Иначе же QDialog::Rejected
	if (m_infoDialog->exec() == QDialog::Accepted) {
		// Посылаем сигнал об необходимости сменить пользователя
		emit changeUser();
	}
}

