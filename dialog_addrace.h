#ifndef DIALOG_ADDRACE_H
#define DIALOG_ADDRACE_H

#include <QDialog>
class Plane;
class Dialog_ControlWagons;

namespace Ui {
class Dialog_AddRace;
}

class Dialog_AddRace : public QDialog
{
    Q_OBJECT

public:
    enum Type { Create /*создание рейса*/,
                Edit /*редактирвоание рейса*/ };

    explicit Dialog_AddRace(Plane *plane, const QList<Plane> &listPlanes, Type type, QWidget *parent = nullptr);
    ~Dialog_AddRace();

private:
    Ui::Dialog_AddRace *mUi;
    QString m_startNumberPlane;
    Plane *m_plane;
    const QList<Plane> &m_listPlanes;
    Dialog_ControlWagons *m_dialogControlPassengers;

public slots:
    void accept();

private slots:
    // void on_buttonEditWagons_clicked();
};

#endif // DIALOG_ADDRACE_H
