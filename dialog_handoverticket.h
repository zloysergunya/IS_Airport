#ifndef DIALOG_HANDOVERTICKET_H
#define DIALOG_HANDOVERTICKET_H

#include <QDialog>
#include "passenger.h"

namespace Ui {
class Dialog_HandOverTicket;
}

class Dialog_HandOverTicket : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_HandOverTicket(const QList<Passenger> &listPassengers, QWidget *parent = nullptr);
    ~Dialog_HandOverTicket();

    QList<Passenger> listPassengers() const;

private:
    Ui::Dialog_HandOverTicket *mUi;
    QList<Passenger> m_listPassengers;

public slots:
    void accept();
};

#endif // DIALOG_HANDOVERTICKET_H
