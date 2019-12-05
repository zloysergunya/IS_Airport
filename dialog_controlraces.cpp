#include "dialog_controlraces.h"
#include "ui_dialog_controlraces.h"

#include "config.h"
#include "dialog_addrace.h"

#include <QMessageBox>
#include <QFile>
#include <QDataStream>

Dialog_ControlRaces::Dialog_ControlRaces(const QList<Plane> &listPlanes, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::Dialog_ControlRaces),
    m_listPlanes(listPlanes)
{
    mUi->setupUi(this);
    this->setStyleSheet("background-color: #a8faff;");
    mUi->tableRaces->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

    int row = 0;
    foreach (const Plane &plane, m_listPlanes) {
        QTableWidgetItem *item_number = new QTableWidgetItem(plane.number());
        QTableWidgetItem *item_departure = new QTableWidgetItem(plane.departure());
        QTableWidgetItem *item_arrival = new QTableWidgetItem(plane.arrival());
        QTableWidgetItem *item_mark = new QTableWidgetItem(plane.mark());
        QTableWidgetItem *item_countSeats = new QTableWidgetItem(QString::number(plane.countSeats()));
        QTableWidgetItem *item_countFreeSeats = new QTableWidgetItem(QString::number(plane.countFreeSeats()));
        QTableWidgetItem *item_countPassengers = new QTableWidgetItem(QString::number(plane.listPassengers().size()));

        mUi->tableRaces->insertRow(row);
        mUi->tableRaces->setItem(row, 0, item_number);
        mUi->tableRaces->setItem(row, 1, item_departure);
        mUi->tableRaces->setItem(row, 2, item_arrival);
        mUi->tableRaces->setItem(row, 3, item_mark);
        mUi->tableRaces->setItem(row, 4, item_countSeats);
        mUi->tableRaces->setItem(row, 5, item_countFreeSeats);
        mUi->tableRaces->setItem(row, 6, item_countPassengers);
        row++;
    }
}

Dialog_ControlRaces::~Dialog_ControlRaces()
{
    delete mUi;
}

void Dialog_ControlRaces::on_buttonAddRace_clicked()
{
    Plane plane;
    Dialog_AddRace dialog(&plane, m_listPlanes, Dialog_AddRace::Create, this);
    dialog.setWindowTitle(windowTitle());

    if (dialog.exec() == QDialog::Accepted) {
        emit addedRace(plane);

        QTableWidgetItem *item_number = new QTableWidgetItem(plane.number());
        QTableWidgetItem *item_departure = new QTableWidgetItem(plane.departure());
        QTableWidgetItem *item_arrival = new QTableWidgetItem(plane.arrival());
        QTableWidgetItem *item_mark = new QTableWidgetItem(plane.mark());
        QTableWidgetItem *item_countSeats = new QTableWidgetItem(QString::number(plane.countSeats()));
        QTableWidgetItem *item_countFreeSeats = new QTableWidgetItem(QString::number(plane.countFreeSeats()));
        QTableWidgetItem *item_countPassengers = new QTableWidgetItem(QString::number(plane.listPassengers().size()));

        int row = mUi->tableRaces->rowCount();
        mUi->tableRaces->setItem(row, 0, item_number);
        mUi->tableRaces->setItem(row, 1, item_departure);
        mUi->tableRaces->setItem(row, 2, item_arrival);
        mUi->tableRaces->setItem(row, 3, item_mark);
        mUi->tableRaces->setItem(row, 4, item_countSeats);
        mUi->tableRaces->setItem(row, 5, item_countFreeSeats);
        mUi->tableRaces->setItem(row, 6, item_countPassengers);
    }
}

//void Dialog_ControlRaces::on_buttonEditRace_clicked()
//{
//	// Проверяем какая страка была выбрана для редактирования
//	int currentRow = mUi->tableRaces->currentRow();
//	// Если строка не выбрана то currentRow будет равно -1
//	if (currentRow != -1) {
//		// Создаем копию выбранного рейса.
//		Train train = m_listTrains[currentRow];
//		// Создаем окно и передаем ему ссылку на объект поезда
//		// Также устанавливаем значение что наш поезд будет "Редактироваться"
//		Dialog_AddRace dialog(&train, m_listTrains, Dialog_AddRace::Edit, this);
//		dialog.setWindowTitle(windowTitle());

//		// Если окно было закрыто нажатием на кнопку "Ок"
//		if (dialog.exec() == QDialog::Accepted) {
//			// Посылаем сигнал в главный класс (Window_WorkWidget) в котором будет
//			// выполнена перезапись в файл и обновлена таблица.
//			// Передаем изменяемую строку и новые данные поезда.
//			emit editedRace(currentRow, train);

//			// Изменяем данные таблицы для текущего окна
//			mUi->tableRaces->item(currentRow, 0)->setText(QString::number(train.number()));
//			mUi->tableRaces->item(currentRow, 1)->setText(train.date().toString("dd.MM.yyyy"));
//			mUi->tableRaces->item(currentRow, 2)->setText(train.time().toString("hh:mm"));
//			mUi->tableRaces->item(currentRow, 3)->setText(train.routeFrom());
//			mUi->tableRaces->item(currentRow, 4)->setText(train.routeTo());
//			mUi->tableRaces->item(currentRow, 5)->setText(
//						QString::number(train.listWagons().size()));
//		}
//	}
//	else {
//		QMessageBox::warning(this, windowTitle(), "Ошибка: не выбран ни один рейс!");
//	}
//}

void Dialog_ControlRaces::on_buttonDeleteRace_clicked()
{
    int currentRow = mUi->tableRaces->currentRow();
    if (currentRow != -1) {
        emit deletedRace(currentRow);
        mUi->tableRaces->removeRow(currentRow);
    }
    else {
        QMessageBox::warning(this, windowTitle(), "Ошибка: не выбран ни один рейс!");
    }
}

void Dialog_ControlRaces::on_lineFind_textChanged(const QString &text)
{
    QStringList listStr = text.split(" ");
    listStr.removeAll(QString());
    for (int i = 0; i < m_listPlanes.size(); i++) {
        mUi->tableRaces->showRow(i);
    }
    int row = 0;
    foreach (const Plane &plane, m_listPlanes) {
        int count = 0;
        foreach (const QString &str, listStr) {
            if (plane.number().contains(str) ||
                plane.departure().contains(str) ||
                plane.arrival().contains(str) ||
                plane.mark().contains(str)) {
                count++;
            }
        }
        if (count != listStr.size()) {
            mUi->tableRaces->hideRow(row);
        }
        row++;
    }
}
