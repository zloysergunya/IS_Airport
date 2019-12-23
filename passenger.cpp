#include "passenger.h"

Passenger::Passenger()
{
    m_firstName = "";
    m_secondName = "";
    m_middleName = "";
    m_passport = "";
    m_flight = "";
}

Passenger::Passenger(QString firstName, QString secondName, QString middleName, QString passport, QString flight)
{
    setData(firstName, secondName, middleName, passport, flight);
}

void Passenger::setData(QString firstName, QString secondName, QString middleName, QString passport, QString flight)
{
    m_firstName = firstName;
    m_secondName = secondName;
    m_middleName = middleName;
    m_passport = passport;
    m_flight = flight;
}

QString Passenger::firstName() const
{
    return m_firstName;
}

void Passenger::setFirstName(const QString &firstName)
{
    m_firstName = firstName;
}

QString Passenger::secondName() const
{
    return m_secondName;
}

void Passenger::setSecondName(const QString &secondName)
{
    m_secondName = secondName;
}

QString Passenger::middleName() const
{
    return m_middleName;
}

void Passenger::setMiddleName(const QString &middleName)
{
    m_middleName = middleName;
}

QString Passenger::passport() const
{
    return m_passport;
}

void Passenger::setPassport(const QString &passport)
{
    m_passport = passport;
}

QString Passenger::flight() const
{
    return m_flight;
}

void Passenger::setFlight(const QString &flight)
{
    m_flight = flight;
}

QList<Ticket> Passenger::listTickets() const
{
    return m_listTickets;
}

void Passenger::setListTickets(const QList<Ticket> &listTickets)
{
    m_listTickets = listTickets;
}

void Passenger::buyOneTicket(Ticket ticket)
{
    m_listTickets.append(ticket);
}

int Passenger::countBuyPlace() const
{
    return m_listTickets.size();
}


bool Passenger::handOverOneTicket(const QString &id_ticket)
{
    int i = 0;
    foreach (const Ticket &ticket, m_listTickets) {
        if (ticket.id() == id_ticket) {
            m_listTickets.removeAt(i);
            return true;
        }
        i++;
    }
    return false;
}
