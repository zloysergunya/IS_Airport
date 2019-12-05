#include "window_workwidget.h"
#include "ui_window_workwidget.h"

#include "config.h"
#include "dialog_infouser.h"
#include "dialog_menuadmin.h"
#include "dialog_menucashier.h"

#include <QFile>
#include <QDataStream>

#include <QDebug>

Window_WorkWidget::Window_WorkWidget(User &user, QWidget *parent) :
	QWidget(parent),
	mUi(new Ui::Window_WorkWidget),
	m_user(user)
{
	mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
	mUi->tableRaces->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

	m_infoDialog = new Dialog_InfoUser(m_user, this);
	m_infoDialog->setWindowTitle(Config::nameApplication);

	if (m_user.status() != User::Admin)
		mUi->menuAdmin->hide();

	if (m_user.status() != User::Passenger)
		connect(mUi->tableRaces, SIGNAL(cellActivated(int, int)),
				this, SLOT(menuCashier(int, int)));

    //loadTrains();
}

Window_WorkWidget::~Window_WorkWidget()
{
	delete mUi;
	delete m_infoDialog;

	delete &m_user;
}

void Window_WorkWidget::on_infoUser_clicked()
{
	if (m_infoDialog->exec() == QDialog::Accepted) {
		emit changeUser();
	}
}

void Window_WorkWidget::on_menuAdmin_clicked()
{
    Dialog_MenuAdmin dialog(this);
    dialog.setWindowTitle(Config::nameApplication);
    dialog.exec();
}

void Window_WorkWidget::menuCashier(int row, int /*column*/)
{
    const Plane &plane = m_listPlanes[row];
    Dialog_MenuCashier dialog(row, plane, this);
    dialog.setWindowTitle(Config::nameApplication);
    connect(&dialog, SIGNAL(editedRace(int, Train)),
            this, SLOT(editRace(int, Train)));

    dialog.exec();
}

const QList<Plane> &Window_WorkWidget::listPlanes() const
{
    return m_listPlanes;
}
