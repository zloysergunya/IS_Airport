#ifndef PASSENGER_H
#define PASSENGER_H

#include <QString>
#include <QDataStream>
#include <QTextStream>

#include "ticket.h"

class Passenger
{
public:
    Passenger();

    Passenger(QString firstName, QString secondName, QString middleName, QString passport, QString flight);
    void setData(QString firstName, QString secondName, QString middleName, QString passport, QString flight);

    QString firstName() const;
    void setFirstName(const QString &firstName);

    QString secondName() const;
    void setSecondName(const QString &secondName);

    QString middleName() const;
    void setMiddleName(const QString &middleName);

    QString passport() const;
    void setPassport(const QString &passport);

    QString flight() const;
    void setFlight(const QString &flight);

    QList<Ticket> listTickets() const;
    void setListTickets(const QList<Ticket> &listTickets);

    void buyOneTicket(Ticket ticket);
    bool handOverOneTicket(const QString &id_ticket);

    int countBuyPlace() const;

private:
    QString m_firstName;
    QString m_secondName;
    QString m_middleName;
    QString m_passport;
    QString m_flight;
    QList<Ticket> m_listTickets;
};

inline QDataStream &operator<< (QDataStream &ost, const Passenger &passenger)
{
    ost << passenger.firstName() << passenger.secondName() << passenger.middleName() << passenger.passport() << passenger.flight();
    return ost;
}

inline QDataStream &operator>> (QDataStream &ist, Passenger &passenger)
{
    QString firstName, secondName, middleName, passport, flight;
    ist >> firstName >> secondName >> middleName >> passport >> flight;
    passenger.setData(firstName, secondName, middleName, passport, flight);
    return ist;
}

inline QTextStream &operator<< (QTextStream &ost, const Passenger &passenger)
{
    ost << QString("_________НАЧАЛО ПАССАЖИРА_________")
        << QString("Имя: ") << passenger.firstName()
        << QString("Фамилия: ") << passenger.secondName()
        << QString("Отчество: ") << passenger.middleName()
        << QString("Паспорт: ") << passenger.passport()
        << QString("Рейс: ") << passenger.flight()
        << QString("_________КОНЕЦ ПАССАЖИРА_________");

    return ost;
}

#endif // PASSENGER_H

