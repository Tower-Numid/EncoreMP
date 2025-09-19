#ifndef OPENMW_PINGUPDATER_HPP
#define OPENMW_PINGUPDATER_HPP

#include <QObject>
#include <QVector>

#include "Types.hpp"

class PingUpdater : public QObject
{
    Q_OBJECT
public:
    void addServer(int row, const AddrPair &addrPair);
public slots:
    void stop();
    void process();
signals:
    void start();
    void updateModel(int row, unsigned ping);
    void finished();
private:
    QVector<ServerRow> servers;
    bool run;
};


#endif //OPENMW_PINGUPDATER_HPP
