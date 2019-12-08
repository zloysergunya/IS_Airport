#ifndef DIALOG_MENUCASHIER_H
#define DIALOG_MENUCASHIER_H

#include <QDialog>
#include "plane.h"

namespace Ui {
class Dialog_MenuCashier;
}

class Dialog_MenuCashier : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_MenuCashier(int row, const Plane &plane, QWidget *parent = nullptr);
    ~Dialog_MenuCashier();

private slots:
    void on_buttonBuyTicket_clicked();
//    void on_buttonHandOverTicket_clicked();
    void on_buttonCheckTickets_clicked();
    void on_buttonReferenceRace_clicked();

signals:
    void editedRace(int, Plane);

private:
    Ui::Dialog_MenuCashier *mUi;
    const Plane &m_plane;
    int m_rowPlane;
};

#endif // DIALOG_MENUCASHIER_H
