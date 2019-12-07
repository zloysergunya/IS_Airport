#include "dialog_addrace.h"
#include "ui_dialog_addrace.h"

#include "config.h"
#include "plane.h"
#include "dialog_controlpassengers.h"

Dialog_AddRace::Dialog_AddRace(Plane *plane, const QList<Plane> &listPlanes, Type type, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::Dialog_AddRace),
    m_plane(plane),
    m_listPlanes(listPlanes)
{
    mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");

    m_startNumberPlane = plane->number();

    if (type == Edit) {
        mUi->mainLabel->setText("Редактирование рейса");
        mUi->edit_number->setText(m_plane->number());
        mUi->edit_departure->setText(m_plane->departure());
        mUi->edit_arrival->setText(m_plane->departure());
        mUi->edit_mark->setText(m_plane->mark());
        mUi->edit_countSeats->setValue(m_plane->countSeats());
    }
    else {
        mUi->mainLabel->setText("Добавление рейса");
    }

    m_dialogControlPassengers = new Dialog_ControlPassengers(plane->listPassengers(), this);
    m_dialogControlPassengers->setWindowTitle(Config::nameApplication);
}

Dialog_AddRace::~Dialog_AddRace()
{
    delete mUi;
    delete m_dialogControlPassengers;
}

void Dialog_AddRace::accept()
{
    mUi->labelError->clear();

    QString number = mUi->edit_number->text();
    QString departure = mUi->edit_departure->text();
    QString arrival = mUi->edit_arrival->text();
    QString mark = mUi->edit_mark->text();
    int countSeats = mUi->edit_countSeats->value();
    int countFreeSeats = countSeats;
    if (number.isEmpty() ||
        departure.isEmpty() ||
        arrival.isEmpty() ||
        mark.isEmpty() ||
        countSeats == 0) {
        mUi->labelError->setText("Ошибка: заполните все поля!");
    } else {
        m_plane->setData(number, departure, arrival, mark, countSeats, countFreeSeats, m_dialogControlPassengers->listPassengers());
        QDialog::accept();
    }
}

void Dialog_AddRace::on_buttonEditPassengers_clicked()
{
    m_dialogControlPassengers->exec();
}
