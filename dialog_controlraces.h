#ifndef DIALOG_CONTROLRACES_H
#define DIALOG_CONTROLRACES_H

#include <QDialog>
#include "plane.h"

namespace Ui {
class Dialog_ControlRaces;
}

class Dialog_ControlRaces : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ControlRaces(const QList<Plane> &listPlanes, QWidget *parent = nullptr);
    ~Dialog_ControlRaces();

private slots:
    void on_buttonAddRace_clicked();
    void on_buttonEditRace_clicked();
    void on_buttonDeleteRace_clicked();

    void on_lineFind_textChanged(const QString &arg1);

private:
    Ui::Dialog_ControlRaces *mUi;
    const QList<Plane> &m_listPlanes;

signals:
    void addedRace(Plane);
    void editedRace(int, Plane);
    void deletedRace(int);
};

#endif // DIALOG_CONTROLRACES_H
