#include "menucashier.h"
#include "ui_dialog_menucashier.h"

#include "config.h"
#include "buyticket.h"
#include "handoverticket.h"
#include "showtickets.h"

#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QTextStream>

MenuCashier::MenuCashier(int row, const Plane &plane, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::MenuCashier),
    m_plane(plane),
    m_rowPlane(row)
{
    mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
    mUi->numberPlane->setText(m_plane.number());
    mUi->countPassengers->setText(QString::number(m_plane.listPassengers().size()));

    int countFreePlace = m_plane.countFreeSeats();
//    foreach (const Passenger &passenger, m_plane.listPassengers()) {
//        countFreePlace += m_plane.countFreeSeats();
//    }

    if (countFreePlace == 0) {
        mUi->countFreePlace->setText("Увы, мест нет. Возвращайтесь через 3 000 лет!");
        mUi->buttonBuyTicket->setEnabled(false);
    }
    else {
        mUi->countFreePlace->setText(QString::number(countFreePlace));
    }
}

MenuCashier::~MenuCashier()
{
    delete mUi;
}

void MenuCashier::on_buttonBuyTicket_clicked()
{
    BuyTicket dialog(m_plane, this);
    dialog.setWindowTitle(windowTitle());

    if (dialog.exec() == QDialog::Accepted) {
        Plane plane = m_plane;
        plane.setListPassengers(dialog.listPassengers());

        emit editedRace(m_rowPlane, plane);
        int countFreePlace = mUi->countFreePlace->text().toInt();
        countFreePlace--;
        if (countFreePlace == 0) {
            mUi->countFreePlace->setText("А мест то нет!");
            mUi->buttonBuyTicket->setEnabled(false);
        }
        else {
            mUi->countFreePlace->setText(QString::number(countFreePlace));
        }
    }
}

void MenuCashier::on_buttonHandOverTicket_clicked()
{
    HandOverTicket dialog(m_plane.listPassengers(), this);
    dialog.setWindowTitle(windowTitle());

    if (dialog.exec() == QDialog::Accepted) {
        Plane plane = m_plane;
        plane.setListPassengers(dialog.listPassengers());

        emit editedRace(m_rowPlane, plane);

        int countFreePlace = mUi->countFreePlace->text().toInt();
        countFreePlace++;
        if (countFreePlace == 0) {
            mUi->countFreePlace->setText("НЕТ МЕСТ");
            mUi->buttonBuyTicket->setEnabled(false);
        }
        else {
            mUi->countFreePlace->setText(QString::number(countFreePlace));
        }
    }
}

void MenuCashier::on_buttonCheckTickets_clicked()
{
    ShowTickets dialog(m_plane, this);
    dialog.setWindowTitle(windowTitle());
    dialog.exec();
}

void MenuCashier::on_buttonReferenceRace_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    Config::nameApplication,
                                                    QString(),
                                                    "TXT (*.txt)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream ost(&file);
        ost.setCodec("UTF-8");

        ost << m_plane;
    }
}
