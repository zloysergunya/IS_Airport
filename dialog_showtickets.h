#ifndef DIALOG_SHOWTICKETS_H
#define DIALOG_SHOWTICKETS_H

#include <QDialog>
class Plane;

namespace Ui {
class Dialog_ShowTickets;
}

class Dialog_ShowTickets : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ShowTickets(const Plane &plane, QWidget *parent = nullptr);
    ~Dialog_ShowTickets();

private:
    Ui::Dialog_ShowTickets *mUi;
};

#endif // DIALOG_SHOWTICKETS_H
