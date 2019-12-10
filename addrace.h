#ifndef DIALOG_ADDRACE_H
#define DIALOG_ADDRACE_H

#include <QDialog>
class Plane;
class ControlPassengers;

namespace Ui {
class AddRace;
}

class AddRace : public QDialog
{
    Q_OBJECT

public:
    enum Type { Create /*создание рейса*/,
                Edit /*редактирвоание рейса*/ };

    explicit AddRace(Plane *plane, const QList<Plane> &listPlanes, Type type, QWidget *parent = nullptr);
    ~AddRace();

private:
    Ui::AddRace *mUi;
    QString m_startNumberPlane;
    Plane *m_plane;
    const QList<Plane> &m_listPlanes;
    ControlPassengers *m_dialogControlPassengers;

public slots:
    void accept();

private slots:
    void on_buttonEditPassengers_clicked();
};

#endif // DIALOG_ADDRACE_H
