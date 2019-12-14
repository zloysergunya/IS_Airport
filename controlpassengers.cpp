#include "controlpassengers.h"
#include "ui_dialog_controlpassengers.h"

#include "passenger.h"
#include "addpassenger.h"

#include <QMessageBox>

ControlPassengers::ControlPassengers(QList<Passenger> listPassengers, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::ControlPassengers),
    m_listPassengers(listPassengers)
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

ControlPassengers::~ControlPassengers()
{
    delete mUi;
}

void ControlPassengers::on_buttonAdd_clicked()
{
    Passenger passenger;
    AddPassenger dialog(&passenger, m_listPassengers, AddPassenger::Create, this);
    dialog.setWindowTitle(windowTitle());

    if (dialog.exec() == QDialog::Accepted) {
        m_listPassengers.append(passenger);

        QTableWidgetItem *item_firstName = new QTableWidgetItem(passenger.firstName());
        QTableWidgetItem *item_secondName = new QTableWidgetItem(passenger.secondName());
        QTableWidgetItem *item_middleName = new QTableWidgetItem(passenger.middleName());
        QTableWidgetItem *item_passport = new QTableWidgetItem(passenger.passport());
        QTableWidgetItem *item_flight = new QTableWidgetItem(passenger.flight());

        int row = mUi->tablePassengers->rowCount();
        mUi->tablePassengers->insertRow(row);
        mUi->tablePassengers->setItem(row, 0, item_firstName);
        mUi->tablePassengers->setItem(row, 1, item_secondName);
        mUi->tablePassengers->setItem(row, 2, item_middleName);
        mUi->tablePassengers->setItem(row, 3, item_passport);
        mUi->tablePassengers->setItem(row, 4, item_flight);
    }
}

void ControlPassengers::on_buttonEdit_clicked()
{
    int currentRow = mUi->tablePassengers->currentRow();
    if (currentRow != -1) {
        Passenger &passenger = m_listPassengers[currentRow];
        AddPassenger dialog(&passenger, m_listPassengers, AddPassenger::Edit, this);
        dialog.setWindowTitle(windowTitle());

        if (dialog.exec() == QDialog::Accepted) {
            mUi->tablePassengers->item(currentRow, 0)->setText(passenger.firstName());
            mUi->tablePassengers->item(currentRow, 1)->setText(passenger.secondName());
            mUi->tablePassengers->item(currentRow, 2)->setText(passenger.middleName());
            mUi->tablePassengers->item(currentRow, 3)->setText(passenger.passport());
            mUi->tablePassengers->item(currentRow, 4)->setText(passenger.flight());
        }
    }
    else {
        QMessageBox::warning(this, windowTitle(), "Ошибка: не выбран ни один пассажир!");
    }
}

void ControlPassengers::on_buttonDelete_clicked()
{
    int currentRow = mUi->tablePassengers->currentRow();
    if (currentRow != -1) {
        m_listPassengers.removeAt(currentRow);
        mUi->tablePassengers->removeRow(currentRow);
    }
    else {
        QMessageBox::warning(this, windowTitle(), "Ошибка: не выбран ни один пассажир!");
    }
}

QList<Passenger> ControlPassengers::listPassengers() const
{
    return m_listPassengers;
}

void ControlPassengers::on_lineFind_textChanged(const QString &text)
{
    QStringList listStr = text.split(" ");
    listStr.removeAll(QString());

    for (int i = 0; i < m_listPassengers.size(); i++) {
        mUi->tablePassengers->showRow(i);
    }

    int row = 0;
    foreach (const Passenger &passenger, m_listPassengers) {
        int count = 0;
        foreach (const QString &str, listStr) {
            if (passenger.firstName().contains(str) ||
                passenger.secondName().contains(str) ||
                passenger.middleName().contains(str) ||
                passenger.passport().contains(str) ||
                passenger.flight().contains(str)) {
                count++;
            }
        }
        if (count != listStr.size()) {
            mUi->tablePassengers->hideRow(row);
        }
        row++;
    }
}
