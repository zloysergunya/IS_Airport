#include "dialog_controlraces.h"
#include "ui_dialog_controlraces.h"

#include "config.h"
#include "dialog_addrace.h"

#include <QMessageBox>
#include <QFile>
#include <QDataStream>

Dialog_ControlRaces::Dialog_ControlRaces(const QList<Plane> &listPlanes, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::Dialog_ControlRaces),
    m_listPlanes(listPlanes)
{
    mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
    mUi->tableRaces->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

    int row = 0;
    foreach (const Plane &plane, m_listPlanes) {
        QTableWidgetItem *item_number = new QTableWidgetItem(plane.number());
        QTableWidgetItem *item_departure = new QTableWidgetItem(plane.departure());
        QTableWidgetItem *item_arrival = new QTableWidgetItem(plane.arrival());
        QTableWidgetItem *item_mark = new QTableWidgetItem(plane.mark());
        QTableWidgetItem *item_countSeats = new QTableWidgetItem(QString::number(plane.countSeats()));
        QTableWidgetItem *item_countFreeSeats = new QTableWidgetItem(QString::number(plane.countFreeSeats()));
        QTableWidgetItem *item_countPassengers = new QTableWidgetItem(QString::number(plane.listPassengers().size()));

        mUi->tableRaces->insertRow(row);
        mUi->tableRaces->setItem(row, 0, item_number);
        mUi->tableRaces->setItem(row, 1, item_departure);
        mUi->tableRaces->setItem(row, 2, item_arrival);
        mUi->tableRaces->setItem(row, 3, item_mark);
        mUi->tableRaces->setItem(row, 4, item_countSeats);
        mUi->tableRaces->setItem(row, 5, item_countFreeSeats);
        mUi->tableRaces->setItem(row, 6, item_countPassengers);
        row++;
    }
}

Dialog_ControlRaces::~Dialog_ControlRaces()
{
    delete mUi;
}

void Dialog_ControlRaces::on_buttonAddRace_clicked()
{
    Plane plane;
    Dialog_AddRace dialog(&plane, m_listPlanes, Dialog_AddRace::Create, this);
    dialog.setWindowTitle(windowTitle());

    if (dialog.exec() == QDialog::Accepted) {
        emit addedRace(plane);

        QTableWidgetItem *item_number = new QTableWidgetItem(plane.number());
        QTableWidgetItem *item_departure = new QTableWidgetItem(plane.departure());
        QTableWidgetItem *item_arrival = new QTableWidgetItem(plane.arrival());
        QTableWidgetItem *item_mark = new QTableWidgetItem(plane.mark());
        QTableWidgetItem *item_countSeats = new QTableWidgetItem(QString::number(plane.countSeats()));
        QTableWidgetItem *item_countFreeSeats = new QTableWidgetItem(QString::number(plane.countFreeSeats()));
        QTableWidgetItem *item_countPassengers = new QTableWidgetItem(QString::number(plane.listPassengers().size()));

        int row = mUi->tableRaces->rowCount();
        mUi->tableRaces->insertRow(row);
        mUi->tableRaces->setItem(row, 0, item_number);
        mUi->tableRaces->setItem(row, 1, item_departure);
        mUi->tableRaces->setItem(row, 2, item_arrival);
        mUi->tableRaces->setItem(row, 3, item_mark);
        mUi->tableRaces->setItem(row, 4, item_countSeats);
        mUi->tableRaces->setItem(row, 5, item_countFreeSeats);
        mUi->tableRaces->setItem(row, 6, item_countPassengers);
    }
}

void Dialog_ControlRaces::on_buttonEditRace_clicked()
{
    int currentRow = mUi->tableRaces->currentRow();
    if (currentRow != -1) {
        Plane plane = m_listPlanes[currentRow];
        Dialog_AddRace dialog(&plane, m_listPlanes, Dialog_AddRace::Edit, this);
        dialog.setWindowTitle(windowTitle());

        if (dialog.exec() == QDialog::Accepted) {
            emit editedRace(currentRow, plane);

            mUi->tableRaces->item(currentRow, 0)->setText(plane.number());
            mUi->tableRaces->item(currentRow, 1)->setText(plane.departure());
            mUi->tableRaces->item(currentRow, 2)->setText(plane.arrival());
            mUi->tableRaces->item(currentRow, 3)->setText(plane.mark());
            mUi->tableRaces->item(currentRow, 4)->setText(QString::number(plane.countSeats()));
            mUi->tableRaces->item(currentRow, 5)->setText(QString::number(plane.countFreeSeats()));
            mUi->tableRaces->item(currentRow, 6)->setText(QString::number(plane.listPassengers().size()));
        }
    }
    else {
        QMessageBox::warning(this, windowTitle(), "Ошибка: не выбран ни один рейс!");
    }
}

void Dialog_ControlRaces::on_buttonDeleteRace_clicked()
{
    int currentRow = mUi->tableRaces->currentRow();
    if (currentRow != -1) {
        emit deletedRace(currentRow);
        mUi->tableRaces->removeRow(currentRow);
    }
    else {
        QMessageBox::warning(this, windowTitle(), "Ошибка: не выбран ни один рейс!");
    }
}

void Dialog_ControlRaces::on_lineFind_textChanged(const QString &text)
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
