#include "dialog_handoverticket.h"
#include "ui_dialog_handoverticket.h"

#include <QInputDialog>

#include <QDebug>

Dialog_HandOverTicket::Dialog_HandOverTicket(const QList<Passenger> &listPassengers, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::Dialog_HandOverTicket),
    m_listPassengers(listPassengers)
{
    mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
    mUi->tableWagons->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

    int row = 0;
    foreach (const Passenger &passenger, m_listPassengers) {
        QTableWidgetItem *item_firstName = new QTableWidgetItem(passenger.firstName());
        QTableWidgetItem *item_secondName = new QTableWidgetItem(passenger.secondName());
        QTableWidgetItem *item_middelName = new QTableWidgetItem(passenger.middleName());
        QTableWidgetItem *item_passport = new QTableWidgetItem(passenger.passport());
        QTableWidgetItem *item_flight = new QTableWidgetItem(passenger.flight());

        mUi->tableWagons->insertRow(row);
        mUi->tableWagons->setItem(row, 0, item_firstName);
        mUi->tableWagons->setItem(row, 1, item_secondName);
        mUi->tableWagons->setItem(row, 2, item_middelName);
        mUi->tableWagons->setItem(row, 3, item_passport);
        mUi->tableWagons->setItem(row, 4, item_flight);
        row++;
    }
}

Dialog_HandOverTicket::~Dialog_HandOverTicket()
{
    delete mUi;
}

QList<Passenger> Dialog_HandOverTicket::listPassengers() const
{
    return m_listPassengers;
}

void Dialog_HandOverTicket::accept()
{
    int currentRow = mUi->tableWagons->currentRow();
    if (currentRow != -1) {
        Passenger &passenger = m_listPassengers[currentRow];

        if (passenger.countBuyPlace() == 0) {
            mUi->labelError->setText("Ошибка: для данного пассажира не куплен ни один билет!");
        }
        else {
            QInputDialog dialog(this);
            dialog.setOption(QInputDialog::InputDialogOption::UseListViewForComboBoxItems);
            dialog.setLabelText("Выберите номер билета для сдачи");
            QStringList listId;
            foreach (const Ticket &ticket, passenger.listTickets()) {
                listId.append(ticket.id());
            }
            dialog.setComboBoxItems(listId);
            dialog.setWindowTitle(windowTitle());
            dialog.resize(dialog.sizeHint());
            if (dialog.exec() == QInputDialog::Accepted) {
                passenger.handOverOneTicket(dialog.textValue());
                QDialog::accept();
            }
        }
    }
    else {
        mUi->labelError->setText("Ошибка: выберите пассажира!");
    }
}
