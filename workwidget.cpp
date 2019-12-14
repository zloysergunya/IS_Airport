#include "workwidget.h"
#include "ui_window_workwidget.h"

#include "config.h"
#include "infouser.h"
#include "menuadmin.h"
#include "menucashier.h"

#include <QFile>
#include <QDataStream>

#include <QDebug>

WorkWidget::WorkWidget(User &user, QWidget *parent) :
	QWidget(parent),
	mUi(new Ui::WorkWidget),
	m_user(user)
{
	mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
	mUi->tableRaces->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

	m_infoDialog = new InfoUser(m_user, this);
	m_infoDialog->setWindowTitle(Config::nameApplication);

	if (m_user.status() != User::Admin)
		mUi->menuAdmin->hide();

	if (m_user.status() != User::Passenger)
		connect(mUi->tableRaces, SIGNAL(cellActivated(int, int)),
				this, SLOT(menuCashier(int, int)));

    loadPlanes();
}

WorkWidget::~WorkWidget()
{
	delete mUi;
	delete m_infoDialog;

	delete &m_user;
}

void WorkWidget::addRace(Plane plane)
{
    m_listPlanes.append(plane);

    QFile file(Config::filePlanes);
    file.open(QIODevice::Append);
    QDataStream ost(&file);
    ost << plane;

    QTableWidgetItem *item_number = new QTableWidgetItem(plane.number());
    QTableWidgetItem *item_departure = new QTableWidgetItem(plane.departure());
    QTableWidgetItem *item_arrival = new QTableWidgetItem(plane.arrival());
    QTableWidgetItem *item_mark = new QTableWidgetItem(plane.mark());
    QTableWidgetItem *item_countSeats = new QTableWidgetItem(plane.countSeats());
    QTableWidgetItem *item_countFreeSeats = new QTableWidgetItem(plane.countFreeSeats());

    int row = mUi->tableRaces->rowCount();
    mUi->tableRaces->insertRow(row);
    mUi->tableRaces->setItem(row, 0, item_number);
    mUi->tableRaces->setItem(row, 1, item_departure);
    mUi->tableRaces->setItem(row, 2, item_arrival);
    mUi->tableRaces->setItem(row, 3, item_mark);
    mUi->tableRaces->setItem(row, 4, item_countSeats);
    mUi->tableRaces->setItem(row, 5, item_countFreeSeats);
}

void WorkWidget::editRace(int row, Plane plane)
{
    m_listPlanes[row] = plane;

    QFile read_file(Config::filePlanes);
    if (read_file.open(QIODevice::ReadOnly)) {
        QFile write_file("buf_file_planes");
        write_file.open(QIODevice::WriteOnly);

        QDataStream read_ist(&read_file);
        QDataStream write_ist(&write_file);

        int countSeats = 0;
        while (!read_ist.atEnd()) {
            Plane buf_plane;
            read_ist >> buf_plane;

            if (countSeats++ == row) {
                buf_plane = plane;
            }

            write_ist << buf_plane;
        }
        read_file.close();
        read_file.remove();

        write_file.close();
        write_file.rename(Config::filePlanes);
    }
    plane.setCountFreeSeats(plane.countFreeSeats() - 1);
    mUi->tableRaces->item(row, 0)->setText(plane.number());
    mUi->tableRaces->item(row, 1)->setText(plane.departure());
    mUi->tableRaces->item(row, 2)->setText(plane.arrival());
    mUi->tableRaces->item(row, 3)->setText(plane.mark());
    mUi->tableRaces->item(row, 4)->setText(QString::number(plane.countSeats()));
    mUi->tableRaces->item(row, 5)->setText(QString::number(plane.countFreeSeats()));
}


void WorkWidget::deleteRace(int row)
{
    m_listPlanes.removeAt(row);

    QFile read_file(Config::filePlanes);
    if (read_file.open(QIODevice::ReadOnly)) {
        QFile write_file("buf_file_planes");
        write_file.open(QIODevice::WriteOnly);

        QDataStream read_ist(&read_file);
        QDataStream write_ist(&write_file);

        int countReads = 0;
        while (!read_ist.atEnd()) {
            Plane buf_plane;
            read_ist >> buf_plane;

            if (countReads++ != row) {
                write_ist << buf_plane;
            }
        }
        read_file.close();
        read_file.remove();
        write_file.close();
        write_file.rename(Config::filePlanes);
    }
    mUi->tableRaces->removeRow(row);
}

void WorkWidget::on_infoUser_clicked()
{
	if (m_infoDialog->exec() == QDialog::Accepted) {
		emit changeUser();
	}
}

void WorkWidget::on_menuAdmin_clicked()
{
    MenuAdmin dialog(this);
    dialog.setWindowTitle(Config::nameApplication);
    dialog.exec();
}

void WorkWidget::menuCashier(int row, int /*column*/)
{
    const Plane &plane = m_listPlanes[row];
    MenuCashier dialog(row, plane, this);
    dialog.setWindowTitle(Config::nameApplication);
    connect(&dialog, SIGNAL(editedRace(int, Plane)),
            this, SLOT(editRace(int, Plane)));

    dialog.exec();
}

const QList<Plane> &WorkWidget::listPlanes() const
{
    return m_listPlanes;
}

void WorkWidget::loadPlanes()
{
    m_listPlanes.clear();

    QFile file(Config::filePlanes);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream ist(&file);

        while (!ist.atEnd()) {
            Plane plane;
            ist >> plane;
            m_listPlanes.append(plane);
        }
    }

    int row = 0;
    foreach (const Plane &plane, m_listPlanes) {

        QTableWidgetItem *item_number = new QTableWidgetItem(plane.number());
        QTableWidgetItem *item_departure = new QTableWidgetItem(plane.departure());
        QTableWidgetItem *item_arrival = new QTableWidgetItem(plane.arrival());
        QTableWidgetItem *item_mark = new QTableWidgetItem(plane.mark());
        QTableWidgetItem *item_countSeats = new QTableWidgetItem(plane.countSeats());
        QTableWidgetItem *item_countFreeSeats = new QTableWidgetItem(plane.countFreeSeats());

        mUi->tableRaces->insertRow(row);
        mUi->tableRaces->setItem(row, 0, item_number);
        mUi->tableRaces->setItem(row, 1, item_departure);
        mUi->tableRaces->setItem(row, 2, item_arrival);
        mUi->tableRaces->setItem(row, 3, item_mark);
        mUi->tableRaces->setItem(row, 4, item_countSeats);
        mUi->tableRaces->setItem(row, 5, item_countFreeSeats);
        row++;
    }
}

void WorkWidget::on_lineFind_textChanged(const QString &text)
{
    QStringList listStr = text.split(" ");
    listStr.removeAll(QString());

    for (int i = 0; i < m_listPlanes.size(); i++) {
        mUi->tableRaces->showRow(i);
    }

    int row = 0;
    foreach (const Plane &plane, m_listPlanes) {
        int count = 0;
        foreach (const QString &str, listStr) {
            if (plane.number().contains(str) ||
                plane.departure().contains(str) ||
                plane.arrival().contains(str) ||
                plane.mark().contains(str)) {
                count++;
            }
        }
        if (count != listStr.size()) {
            mUi->tableRaces->hideRow(row);
        }
        row++;
    }
}
