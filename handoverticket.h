#ifndef HANDOVERTICKET_H
#define HANDOVERTICKET_H

#include <QDialog>
#include "passenger.h"

namespace Ui {
class HandOverTicket;
}

class HandOverTicket : public QDialog
{
    Q_OBJECT

public:
    explicit HandOverTicket(const QList<Passenger> &listPassengers, QWidget *parent = nullptr);
    ~HandOverTicket();

    QList<Passenger> listPassengers() const;

private:
    Ui::HandOverTicket *mUi;
    QList<Passenger> m_listPassengers;

public slots:
    void accept();
};

#endif // HANDOVERTICKET_H
