#ifndef DIALOG_BUYTICKET_H
#define DIALOG_BUYTICKET_H

#include <QDialog>
#include "passenger.h"
class Ticket;
class Plane;

namespace Ui {
class Dialog_BuyTicket;
}

class Dialog_BuyTicket : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_BuyTicket(const Plane &plane, QWidget *parent = nullptr);
    ~Dialog_BuyTicket();

    QList<Passenger> listPassengers() const;

private:
    Ui::Dialog_BuyTicket *mUi;
    QList<Passenger> m_listPassengers;
    const Plane &m_plane;

public slots:
    void accept();
};

#endif // DIALOG_BUYTICKET_H
