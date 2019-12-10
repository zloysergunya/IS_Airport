#include "buyticket.h"
#include "ui_dialog_buyticket.h"

#include "ticket.h"
#include "plane.h"

#include <algorithm>
#include <QMessageBox>
#include <QString>

BuyTicket::BuyTicket(const Plane &plane, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::BuyTicket),
    m_listPassengers(plane.listPassengers()),
    m_plane(plane)
{
    mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
    mUi->tablePassengers->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

    int row = 0;
    foreach (const Passenger &passenger, m_listPassengers) {
        QTableWidgetItem *item_firstName = new QTableWidgetItem(passenger.firstName());
        QTableWidgetItem *item_secondName = new QTableWidgetItem(passenger.secondName());
        QTableWidgetItem *item_middleName = new QTableWidgetItem(passenger.middleName());
        QTableWidgetItem *item_passport = new QTableWidgetItem(passenger.passport());
        QTableWidgetItem *item_flight = new QTableWidgetItem(passenger.flight());


        mUi->tablePassengers->insertRow(row);
        mUi->tablePassengers->setItem(row, 0, item_firstName);
        mUi->tablePassengers->setItem(row, 1, item_secondName);
        mUi->tablePassengers->setItem(row, 2, item_middleName);
        mUi->tablePassengers->setItem(row, 3, item_passport);
        mUi->tablePassengers->setItem(row, 4, item_flight);
        row++;
    }
}

BuyTicket::~BuyTicket()
{
    delete mUi;
}

QList<Passenger> BuyTicket::listPassengers() const
{
    return m_listPassengers;
}

void BuyTicket::accept()
{
    int currentRow = mUi->tablePassengers->currentRow();
    if (currentRow != -1) {
        Passenger &passenger = m_listPassengers[currentRow];

        if (/*wagon.countFreePlace() == 0*/false) {
            mUi->labelError->setText("Ошибка: на данный вагон нет мест!");
        }
        else {
            Ticket ticket;
            ticket.setDeparture(m_plane.departure());
            ticket.setArrival(m_plane.arrival());
            ticket.setNumberPlane(m_plane.number());
            ticket.setNumberPassenger(passenger.passport());

            int freeNumber;
            for (freeNumber = 0; freeNumber < passenger.listTickets().size(); freeNumber++) {
                if (freeNumber != passenger.listTickets()[freeNumber].number())
                    break;
            }
            ticket.setNumber(freeNumber);

            ticket.setId(m_plane.number() + "_" +
                         m_plane.departure() + "_" +
                         m_plane.arrival() + "_" +
                         QString::number(freeNumber));

            passenger.buyOneTicket(ticket);

            QList<Ticket> sortList = passenger.listTickets();
            std::sort(sortList.begin(), sortList.end());
            passenger.setListTickets(sortList);

            QMessageBox::information(this, windowTitle(),
                                     "Билет успешно приобретен!"
                                     "\n\nНомер билета: " + ticket.id() +
                                     "\nПункт отправления: " + ticket.departure() +
                                     "\nПункт прибытия: " + ticket.arrival() +
                                     "\n\nНомер самолета: " + ticket.numberPlane() +
                                     "\nНомер пассажира: " + ticket.numberPassenger());

            QDialog::accept();
        }
    }
    else {
        mUi->labelError->setText("Ошибка: выберите вагон!");
    }
}
