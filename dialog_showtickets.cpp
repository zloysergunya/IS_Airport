#include "dialog_showtickets.h"
#include "ui_dialog_showtickets.h"

#include "config.h"
#include "ticket.h"
#include "plane.h"
#include "passenger.h"

Dialog_ShowTickets::Dialog_ShowTickets(const Plane &plane, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::Dialog_ShowTickets)
{
    mUi->setupUi(this);
    mUi->tableTickets->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

    int row = 0;
    foreach (const Passenger &passenger, plane.listPassengers()) {
        foreach (const Ticket &ticket, passenger.listTickets()) {
            QTableWidgetItem *item_id = new QTableWidgetItem(ticket.id());
            QTableWidgetItem *item_departure = new QTableWidgetItem(ticket.departure());
            QTableWidgetItem *item_arrival = new QTableWidgetItem(ticket.arrival());
            QTableWidgetItem *item_numberPlane = new QTableWidgetItem(ticket.numberPlane());
            QTableWidgetItem *item_numberPassengwer = new QTableWidgetItem(ticket.numberPassenger());
            QTableWidgetItem *item_dateTimeBuy = new QTableWidgetItem(ticket.dateTimeBuy().toString("dd.MM.yyyy hh:mm:ss"));

            mUi->tableTickets->insertRow(row);
            mUi->tableTickets->setItem(row, 0, item_id);
            mUi->tableTickets->setItem(row, 1, item_departure);
            mUi->tableTickets->setItem(row, 2, item_arrival);
            mUi->tableTickets->setItem(row, 3, item_numberPlane);
            mUi->tableTickets->setItem(row, 4, item_numberPassengwer);
            mUi->tableTickets->setItem(row, 5, item_dateTimeBuy);
            row++;
        }
    }
}

Dialog_ShowTickets::~Dialog_ShowTickets()
{
    delete mUi;
}
