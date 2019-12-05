#ifndef PLANE_H
#define PLANE_H

#include "passenger.h"
#include <QString>
#include <QDate>
#include <QTime>

#include <QDataStream>
#include <QTextStream>

class Plane
{
public:
    Plane();

    Plane(QString number, const QString departure, const QString arrival, const QString mark, const int countSeats, const int countFreeSeats, const QList<Passenger> listPassengers);
    void setData(QString number, const QString departure, const QString arrival, const QString mark, const int countSeats, const int countFreeSeats, const QList<Passenger> listPassengers);

    QString number() const;
    void setNumber(const QString &number);

    QString departure() const;
    void setDeparture(const QString &departure);

    QString arrival() const;
    void setArrival(const QString &arrival);

    QString mark() const;
    void setMark(const QString &mark);

    int countSeats() const;
    void setCountSeats(int countSeats);

    int countFreeSeats() const;
    void setCountFreeSeats(int countFreeSeats);

    QList<Passenger> listPassengers() const;
    void setListPassengers(const QList<Passenger> &listPassengers);

private:
    QString m_number;
    QString m_departure;
    QString m_arrival;
    QString m_mark;
    int m_countSeats;
    int m_countFreeSeats;
    QList<Passenger> m_listPassengers;
};

inline QDataStream &operator<< (QDataStream &ost, const Plane &plane)
{
    ost << plane.number() << plane.departure() << plane.arrival() << plane.mark() << plane.countSeats() << plane.countFreeSeats();
    foreach (const Passenger &passenger, plane.listPassengers()) {
        ost << passenger;
    }
    return ost;
}

inline QDataStream &operator>> (QDataStream &ist, Plane &plane)
{
    QString number;
    QString departure;
    QString arrival;
    QString mark;
    int countSeats;
    int countFreeSeats;
    int countPassengers;
    QList<Passenger> listPassengers;

    ist >> number >> departure >> arrival >> mark >> countSeats >> countFreeSeats >> countPassengers;
    for (int i = 0; i < countPassengers; i++) {
        Passenger passenger;
        ist >> passenger;
        listPassengers.append(passenger);
    }
    plane.setData(number, departure, arrival, mark, countSeats, countFreeSeats, listPassengers);
    return ist;
}

inline QTextStream &operator<< (QTextStream &ost, const Plane &plane)
{
    ost << QString("______Начало САМОЛЕТА______")
        << QString("Номер самолета: ") << plane.number()
        << QString("Пункт отправления: ") << plane.departure()
        << QString("Пункт назначения: ") << plane.arrival()
        << QString("Количество мест: ") << plane.countSeats()
        << QString("Количество свободных мест: ") << plane.countFreeSeats()
        << QString("\nКоличество вагонов: ") << plane.listPassengers().size() << "\n";
    foreach (const Passenger &passenger, plane.listPassengers()) {
        ost << "\n" << passenger;
    }
    ost << QString("______КОНЕЦ САМОЛЕТА______");
    return ost;
}

#endif // PLANE_H
