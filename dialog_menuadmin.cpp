#include "dialog_menuadmin.h"
#include "ui_dialog_menuadmin.h"

#include "dialog_controlusers.h"
// #include "dialog_controlraces.h"
#include "window_workwidget.h"

Dialog_MenuAdmin::Dialog_MenuAdmin(QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::Dialog_MenuAdmin)
{
    mUi->setupUi(this);
}

Dialog_MenuAdmin::~Dialog_MenuAdmin()
{
    delete mUi;
}

void Dialog_MenuAdmin::on_buttonControlUsers_clicked()
{
    // Создаем окно управления учетными записями
    Dialog_ControlUsers dialog(this);
    dialog.setWindowTitle(windowTitle());

    dialog.exec();
}

//void Dialog_MenuAdmin::on_buttonControlRaces_clicked()
//{
//	const QList<Plane> &listPlanes = qobject_cast<Window_WorkWidget*>(parent())->listPlanes();

//	Dialog_ControlRaces dialog(listPlanes, this);
//	dialog.setWindowTitle(windowTitle());

//	connect(&dialog, SIGNAL(addedRace(Train)),
//			parent(), SLOT(addRace(Train)));
//	connect(&dialog, SIGNAL(editedRace(int, Train)),
//			parent(), SLOT(editRace(int, Train)));
//	connect(&dialog, SIGNAL(deletedRace(int)),
//			parent(), SLOT(deleteRace(int)));

//	// Вызываем окно
//	dialog.exec();
//}
