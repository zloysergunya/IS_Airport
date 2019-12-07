#include "dialog_menuadmin.h"
#include "ui_dialog_menuadmin.h"

#include "dialog_controlusers.h"
#include "dialog_controlraces.h"
#include "window_workwidget.h"

Dialog_MenuAdmin::Dialog_MenuAdmin(QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::Dialog_MenuAdmin)
{
    mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
}

Dialog_MenuAdmin::~Dialog_MenuAdmin()
{
    delete mUi;
}

void Dialog_MenuAdmin::on_buttonControlUsers_clicked()
{
    Dialog_ControlUsers dialog(this);
    dialog.setWindowTitle(windowTitle());

    dialog.exec();
}

void Dialog_MenuAdmin::on_buttonControlRaces_clicked()
{
    const QList<Plane> &listPlanes = qobject_cast<Window_WorkWidget*>(parent())->listPlanes();
    Dialog_ControlRaces dialog(listPlanes, this);
    dialog.setWindowTitle(windowTitle());

    connect(&dialog, SIGNAL(addedRace(Plane)),
            parent(), SLOT(addRace(Plane)));
    connect(&dialog, SIGNAL(editedRace(int, Plane)),
            parent(), SLOT(editRace(int, Plane)));
    connect(&dialog, SIGNAL(deletedRace(int)),
            parent(), SLOT(deleteRace(int)));
    dialog.exec();
}
