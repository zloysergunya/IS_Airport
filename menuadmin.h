#ifndef DIALOG_MENUADMIN_H
#define DIALOG_MENUADMIN_H

#include <QDialog>

namespace Ui {
class MenuAdmin;
}

class MenuAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit MenuAdmin(QWidget *parent = nullptr);
    ~MenuAdmin();

private slots:
    void on_buttonControlUsers_clicked();
    void on_buttonControlRaces_clicked();

private:
    Ui::MenuAdmin *mUi;
};

#endif // DIALOG_MENUADMIN_H
