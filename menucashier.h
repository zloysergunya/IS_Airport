#ifndef DIALOG_MENUCASHIER_H
#define DIALOG_MENUCASHIER_H

#include <QDialog>
#include "plane.h"

namespace Ui {
class MenuCashier;
}

class MenuCashier : public QDialog
{
    Q_OBJECT

public:
    explicit MenuCashier(int row, const Plane &plane, QWidget *parent = nullptr);
    ~MenuCashier();

private slots:
    void on_buttonBuyTicket_clicked();
    void on_buttonHandOverTicket_clicked();
    void on_buttonCheckTickets_clicked();
    void on_buttonReferenceRace_clicked();

signals:
    void editedRace(int, Plane);

private:
    Ui::MenuCashier *mUi;
    const Plane &m_plane;
    int m_rowPlane;
};

#endif // DIALOG_MENUCASHIER_H
