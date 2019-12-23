#include "menuadmin.h"
#include "ui_dialog_menuadmin.h"

#include "controlusers.h"
#include "controlraces.h"
#include "workwidget.h"

MenuAdmin::MenuAdmin(QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::MenuAdmin)
{
    mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
}

MenuAdmin::~MenuAdmin()
{
    delete mUi;
}

void MenuAdmin::on_buttonControlUsers_clicked()
{
    ControlUsers dialog(this);
    dialog.setWindowTitle(windowTitle());

    dialog.exec();
}

void MenuAdmin::on_buttonControlRaces_clicked()
{
    const QList<Plane> &listPlanes = qobject_cast<WorkWidget*>(parent())->listPlanes();
    ControlRaces dialog(listPlanes, this);
    dialog.setWindowTitle(windowTitle());

    connect(&dialog, SIGNAL(addedRace(Plane)),
            parent(), SLOT(addRace(Plane)));
    connect(&dialog, SIGNAL(editedRace(int, Plane)),
            parent(), SLOT(editRace(int, Plane)));
    connect(&dialog, SIGNAL(deletedRace(int)),
            parent(), SLOT(deleteRace(int)));
    dialog.exec();
}
