#ifndef DIALOG_ADDWAGON_H
#define DIALOG_ADDWAGON_H

#include <QDialog>
class Passenger;

namespace Ui {
class AddPassenger;
}

class AddPassenger : public QDialog
{
    Q_OBJECT

public:
    enum Type {Create, Edit};

    explicit AddPassenger(Passenger *passenger, const QList<Passenger> &listPassengers, Type type, QWidget *parent = nullptr);
    ~AddPassenger();

private:
    Ui::AddPassenger *mUi;
    int m_startNumberPassenger;
    Passenger *m_passenger;
    const QList<Passenger> &m_listPassengers;

public slots:
    void accept();
};

#endif // DIALOG_ADDWAGON_H
