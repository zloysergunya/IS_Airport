#ifndef SHOWTICKETS_H
#define SHOWTICKETS_H

#include <QDialog>
class Plane;

namespace Ui {
class ShowTickets;
}

class ShowTickets : public QDialog
{
    Q_OBJECT

public:
    explicit ShowTickets(const Plane &plane, QWidget *parent = nullptr);
    ~ShowTickets();

private:
    Ui::ShowTickets *mUi;
};

#endif // SHOWTICKETS_H
