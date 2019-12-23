#ifndef TICKET_H
#define TICKET_H

#include <QString>
#include <QDate>
#include <QDataStream>
#include <QTextStream>

class Ticket
{
public:
    Ticket();
    Ticket(int number, const QString &numPlane, const QString &numPassenger, const QString &departure, const QString &arrival);

    void setData(int number, const QString &numPlane, const QString &numPassenger, const QString &departure, const QString &arrival);

    int number() const;
    void setNumber(int number);

    QString id() const;
    void setId(const QString &id);

    QString numberPlane() const;
    void setNumberPlane(const QString &numberPlane);

    QString numberPassenger() const;
    void setNumberPassenger(const QString &numberPassenger);

    QString departure() const;
    void setDeparture(const QString &departure);

    QString arrival() const;
    void setArrival(const QString &arrival);

    QDateTime dateTimeBuy() const;
    void setDateTimeBuy(const QDateTime &dateTimeBuy);

private:
    int m_number;
    QString m_id;
    QDateTime m_dateTimeBuy;
    QString m_numberPlane;
    QString m_numberPassenger;
    QString m_departure;
    QString m_arrival;
};

inline QDataStream &operator<< (QDataStream &ost, const Ticket &ticket)
{
    ost << ticket.number() << ticket.numberPlane() << ticket.numberPassenger() << ticket.departure() << ticket.id() << ticket.dateTimeBuy();
    return ost;
}

inline QDataStream &operator>> (QDataStream &ist, Ticket &ticket)
{
    int number;
    QString departure, arrival, id, numberPlane, numberPassenger;
    QDateTime dateTime;
    ist >> number >> numberPlane >> numberPassenger >> departure >> arrival >> id >> dateTime;
    ticket.setData(number, numberPlane, numberPassenger, departure, arrival);
    ticket.setId(id);
    ticket.setDateTimeBuy(dateTime);

    return ist;
}

inline QTextStream &operator<< (QTextStream &ost, const Ticket &ticket)
{
    ost << QString("ID: ") << ticket.id()
        << QString("\nДата и время покупки: ") << ticket.dateTimeBuy().toString("dd.MM.yyyy hh:mm") << "\n";
    return ost;
}

inline bool operator< (const Ticket &ticket1, const Ticket &ticket2)
{
    return ticket1.number() < ticket2.number() ? true : false;
}

#endif // TICKET_H
