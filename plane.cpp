#include "plane.h"

Plane::Plane()
{
    m_number = "";
    m_departure = "";
    m_arrival = "";
    m_mark = "";
    m_countSeats = 0;
    m_countFreeSeats = 0;
}

Plane::Plane(QString number, const QString departure, const QString arrival, const QString mark, const int countSeats, const int countFreeSeats, const QList<Passenger> listPassengers)
{
    setData(number, departure, arrival, mark, countSeats, countFreeSeats, listPassengers);
}

void Plane::setData(QString number, const QString departure, const QString arrival, const QString mark, const int countSeats, const int countFreeSeats, const QList<Passenger> listPassengers)
{
    m_number = number;
    m_departure = departure;
    m_arrival = arrival;
    m_mark = mark;
    m_countSeats = countSeats;
    m_countFreeSeats = countFreeSeats;
    m_listPassengers = listPassengers;
}

QString Plane::number() const
{
    return m_number;
}

void Plane::setNumber(const QString &number)
{
    m_number = number;
}

QString Plane::departure() const
{
    return m_departure;
}

void Plane::setDeparture(const QString &departure)
{
    m_departure = departure;
}

QString Plane::arrival() const
{
    return m_arrival;
}

void Plane::setArrival(const QString &arrival)
{
    m_arrival = arrival;
}

QString Plane::mark() const
{
    return m_mark;
}

void Plane::setMark(const QString &mark)
{
    m_mark = mark;
}

int Plane::countSeats() const
{
    return m_countSeats;
}

void Plane::setCountSeats(int countSeats)
{
    m_countSeats = countSeats;
}

int Plane::countFreeSeats() const
{
    return m_countFreeSeats;
}

void Plane::setCountFreeSeats(int countFreeSeats)
{
    m_countFreeSeats = countFreeSeats;
}

QList<Passenger> Plane::listPassengers() const
{
    return m_listPassengers;
}

void Plane::setListPassengers(const QList<Passenger> &listPassengers)
{
    m_listPassengers = listPassengers;
}
