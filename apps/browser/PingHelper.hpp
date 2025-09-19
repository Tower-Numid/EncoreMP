#ifndef OPENMW_PINGHELPER_HPP
#define OPENMW_PINGHELPER_HPP

#include <QObject>
#include <QAbstractTableModel>
#include <QThread>
#include "Types.hpp"

class PingUpdater;

class PingHelper : public QObject
{
    Q_OBJECT
public:

    void Reset();
    void Add(int row, const AddrPair &addrPair);
    void Stop();
    void SetModel(QAbstractTableModel *model);
    //void UpdateImmedialy(PingUpdater::AddrPair addrPair);
    static PingHelper &Get();

    PingHelper(const PingHelper&) = delete;
    PingHelper& operator=(const PingHelper&) = delete;
private:
    PingHelper();
signals:
    void stop();
public slots:
    void update(int row, unsigned ping);
private:
    QThread *pingThread;
    PingUpdater *pingUpdater;
    QAbstractTableModel *model;
};


#endif //OPENMW_PINGHELPER_HPP
