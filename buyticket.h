#ifndef BUYTICKET_H
#define BUYTICKET_H

#include <QDialog>
#include "passenger.h"
class Ticket;
class Plane;

namespace Ui {
class BuyTicket;
}

class BuyTicket : public QDialog
{
    Q_OBJECT

public:
    explicit BuyTicket(const Plane &plane, QWidget *parent = nullptr);
    ~BuyTicket();

    QList<Passenger> listPassengers() const;

private:
    Ui::BuyTicket *mUi;
    QList<Passenger> m_listPassengers;
    const Plane &m_plane;

public slots:
    void accept();
};

#endif // BUYTICKET_H
