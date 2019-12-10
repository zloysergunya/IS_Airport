#include "addpassenger.h"
#include "ui_dialog_addpassenger.h"

#include "passenger.h"

AddPassenger::AddPassenger(Passenger *passenger, const QList<Passenger> &listPassengers, Type type, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::AddPassenger),
    m_passenger(passenger),
    m_listPassengers(listPassengers)
{
    mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
    if (type == Edit) {
        mUi->mainLabel->setText("Редактирование пассажира");
        mUi->firstName->setText(passenger->firstName());
        mUi->secondName->setText(passenger->secondName());
        mUi->middleName->setText(passenger->middleName());
        mUi->passport->setText(passenger->passport());
        mUi->flight->setText(passenger->flight());
    }
    else {
        mUi->mainLabel->setText("Добавление пассажира");
    }
}

AddPassenger::~AddPassenger()
{
    delete mUi;
}

void AddPassenger::accept()
{
    mUi->labelError->clear();

    QString firstName = mUi->edit_firstName->text();
    QString secondName = mUi->edit_secondName->text();
    QString middleName = mUi->edit_middleName->text();
    QString passport = mUi->edit_passport->text();
    QString flight = mUi->edit_flight->text();

    if (firstName.isEmpty() ||
        secondName.isEmpty() ||
        middleName.isEmpty() ||
        passport.isEmpty() ||
        flight.isEmpty()) {
        mUi->labelError->setText("Ошибка: заполните все поля!");
    } else {
        m_passenger->setData(firstName, secondName, middleName, passport, flight);
        QDialog::accept();
    }
}
