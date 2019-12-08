#include "dialog_menucashier.h"
#include "ui_dialog_menucashier.h"

#include "config.h"
#include "dialog_buyticket.h"
//#include "dialog_handoverticket.h"
#include "dialog_showtickets.h"

#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QTextStream>

Dialog_MenuCashier::Dialog_MenuCashier(int row, const Plane &plane, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::Dialog_MenuCashier),
    m_plane(plane),
    m_rowPlane(row)
{
    mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
    mUi->numberPlane->setText(m_plane.number());
    mUi->countPassengers->setText(QString::number(m_plane.listPassengers().size()));

    int countFreePlace = 1;
    foreach (const Passenger &passenger, m_plane.listPassengers()) {
        countFreePlace += m_plane.countFreeSeats();
    }

    if (countFreePlace == 0) {
        mUi->countFreePlace->setText("Увы, мест нет. Возвращайтесь через 3 000 лет!");
        mUi->buttonBuyTicket->setEnabled(false);
    }
    else {
        mUi->countFreePlace->setText(QString::number(countFreePlace));
    }
}

Dialog_MenuCashier::~Dialog_MenuCashier()
{
    delete mUi;
}

void Dialog_MenuCashier::on_buttonBuyTicket_clicked()
{
    Dialog_BuyTicket dialog(m_plane, this);
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

//void Dialog_MenuCashier::on_buttonHandOverTicket_clicked()
//{
//	Dialog_HandOverTicket dialog(m_train.listWagons(), this);
//	dialog.setWindowTitle(windowTitle());

//	if (dialog.exec() == QDialog::Accepted) {
//		// Создаем новый объект поезда
//		Train train = m_train;
//		// Устанавливаем в него измененные данные о вагонах
//		train.setListWagons(dialog.listWagons());

//		// Посылаем сигнал об изменении данных
//		emit editedRace(m_rowTrain, train);

//		// Изменяем информацию об количестве свободных мест
//		int countFreePlace = mUi->countFreePlace->text().toInt();
//		countFreePlace++;
//		if (countFreePlace == 0) {
//			mUi->countFreePlace->setText("НЕТ МЕСТ");
//			mUi->buttonBuyTicket->setEnabled(false);
//		}
//		else {
//			mUi->countFreePlace->setText(QString::number(countFreePlace));
//		}
//	}
//}

void Dialog_MenuCashier::on_buttonCheckTickets_clicked()
{
    Dialog_ShowTickets dialog(m_plane, this);
    dialog.setWindowTitle(windowTitle());
    dialog.exec();
}

void Dialog_MenuCashier::on_buttonReferenceRace_clicked()
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
