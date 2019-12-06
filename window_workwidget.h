#ifndef WINDOW_WORKWIDGET_H
#define WINDOW_WORKWIDGET_H

#include <QWidget>
#include "plane.h"
#include "user.h"
class Dialog_InfoUser;

namespace Ui {
class Window_WorkWidget;
}

class Window_WorkWidget : public QWidget
{
	Q_OBJECT

public:
	explicit Window_WorkWidget(User &user, QWidget *parent = nullptr);
	~Window_WorkWidget();

    const QList<Plane> &listPlanes() const;

public slots:
    void addRace(Plane plane);
    void editRace(int row, Plane plane);
    void deleteRace(int row);

private slots:
	void on_infoUser_clicked();
    void on_menuAdmin_clicked();
    void menuCashier(int row, int column);

    void on_lineFind_textChanged(const QString &arg1);

signals:
	void changeUser();

private:
	Ui::Window_WorkWidget *mUi;
	User &m_user;
	Dialog_InfoUser *m_infoDialog;

    QList<Plane> m_listPlanes;

    void loadTrains();
};

#endif // WINDOW_WORKWIDGET_H
