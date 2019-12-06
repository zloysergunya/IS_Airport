#ifndef DIALOG_CONTROLWAGONS_H
#define DIALOG_CONTROLWAGONS_H

#include <QDialog>
class Passenger;

namespace Ui {
class Dialog_ControlPassengers;
}

class Dialog_ControlPassengers : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ControlPassengers(QList<Passenger> listPassengers, QWidget *parent = nullptr);
    ~Dialog_ControlPassengers();
    void setNumberPlane(const int &number_train);
    QList<Passenger> listPassengers() const;

private slots:
    void on_buttonAdd_clicked();
    void on_buttonEdit_clicked();
    void on_buttonDelete_clicked();
    void on_lineFind_textChanged(const QString &arg1);

private:
    Ui::Dialog_ControlPassengers *mUi;
    QList<Passenger> m_listPassengers;
};

#endif // DIALOG_CONTROLWAGONS_H
