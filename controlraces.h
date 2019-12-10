#ifndef CONTROLRACES_H
#define CONTROLRACES_H

#include <QDialog>
#include "plane.h"

namespace Ui {
class ControlRaces;
}

class ControlRaces : public QDialog
{
    Q_OBJECT

public:
    explicit ControlRaces(const QList<Plane> &listPlanes, QWidget *parent = nullptr);
    ~ControlRaces();

private slots:
    void on_buttonAddRace_clicked();
    void on_buttonEditRace_clicked();
    void on_buttonDeleteRace_clicked();

    void on_lineFind_textChanged(const QString &arg1);

private:
    Ui::ControlRaces *mUi;
    const QList<Plane> &m_listPlanes;

signals:
    void addedRace(Plane);
    void editedRace(int, Plane);
    void deletedRace(int);
};

#endif // CONTROLRACES_H
