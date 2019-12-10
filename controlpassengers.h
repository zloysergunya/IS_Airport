#ifndef CONTROLWAGONS_H
#define CONTROLWAGONS_H

#include <QDialog>
class Passenger;

namespace Ui {
class ControlPassengers;
}

class ControlPassengers : public QDialog
{
    Q_OBJECT

public:
    explicit ControlPassengers(QList<Passenger> listPassengers, QWidget *parent = nullptr);
    ~ControlPassengers();
    void setNumberPlane(const int &number_plane);
    QList<Passenger> listPassengers() const;

private slots:
    void on_buttonAdd_clicked();
    void on_buttonEdit_clicked();
    void on_buttonDelete_clicked();
    void on_lineFind_textChanged(const QString &arg1);

private:
    Ui::ControlPassengers *mUi;
    QList<Passenger> m_listPassengers;
};

#endif // CONTROLWAGONS_H
