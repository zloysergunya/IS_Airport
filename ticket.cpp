#include "ticket.h"

Ticket::Ticket()
{

}

Ticket::Ticket(int number, const QString &numPlane, const QString &numPassenger, const QString &departure, const QString &arrival)
{
    setData(number, numPlane, numPassenger, departure, arrival);
}

void Ticket::setData(int number, const QString &numPlane, const QString &numPassenger, const QString &departure, const QString &arrival)
{
    m_number = number;
    m_numberPlane = numPlane;
    m_numberPassenger = numPassenger;
    m_departure = departure;
    m_arrival = arrival;
}

int Ticket::number() const
{
    return m_number;
}

void Ticket::setNumber(int number)
{
    m_number = number;
}

QString Ticket::id() const
{
    return m_id;
}

void Ticket::setId(const QString &id)
{
    m_id = id;
}

QString Ticket::numberPlane() const
{
    return m_numberPlane;
}

void Ticket::setNumberPlane(const QString &numberPlane)
{
    m_numberPlane = numberPlane;
}

QString Ticket::numberPassenger() const
{
    return m_numberPassenger;
}

void Ticket::setNumberPassenger(const QString &numberPassenger)
{
    m_numberPassenger = numberPassenger;
}

QString Ticket::departure() const
{
    return m_departure;
}

void Ticket::setDeparture(const QString &departure)
{
    m_departure = departure;
}

QString Ticket::arrival() const
{
    return m_arrival;
}

void Ticket::setArrival(const QString &arrival)
{
    m_arrival = arrival;
}

QDateTime Ticket::dateTimeBuy() const
{
    return m_dateTimeBuy;
}

void Ticket::setDateTimeBuy(const QDateTime &timeBuy)
{
    m_dateTimeBuy = timeBuy;
}
