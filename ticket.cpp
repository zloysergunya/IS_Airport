#include "ticket.h"

Ticket::Ticket()
{

}

Ticket::Ticket(int number, int numPlane, int numPassenger, const QString &departure, const QString &arrival)
{
    setData(number, numPlane, numPassenger, departure, arrival);
}

void Ticket::setData(int number, int numPlane, int numPassenger, const QString &departure, const QString &arrival)
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

int Ticket::numberPlane() const
{
    return m_numberPlane;
}

void Ticket::setNumberPlane(int numberTrain)
{
    m_numberPlane = numberTrain;
}

int Ticket::numberPassenger() const
{
    return m_numberPassenger;
}

void Ticket::setNumberPassenger(int numberWagon)
{
    m_numberPassenger = numberWagon;
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
