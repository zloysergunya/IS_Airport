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
    Ticket(int number, int numPlane, int numPassenger, const QString &departure, const QString &arrival);

    void setData(int number, int numPlane, int numPassenger, const QString &departure, const QString &arrival);

    int number() const;
    void setNumber(int number);

    QString id() const;
    void setId(const QString &id);

    int numberPlane() const;
    void setNumberPlane(int numberPlane);

    int numberPassenger() const;
    void setNumberPassenger(int numberPassenger);

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
    int m_numberPlane;
    int m_numberPassenger;
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
    int number, numberTrain, numberWagon;
    QString departure, arrival, id;
    QDateTime dateTime;
    ist >> number >> numberTrain >> numberWagon >> departure >> arrival >> id >> dateTime;
    ticket.setData(number, numberTrain, numberWagon, departure, arrival);
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
