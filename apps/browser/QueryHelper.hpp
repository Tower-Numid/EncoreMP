#ifndef OPENMW_QUERYHELPER_HPP
#define OPENMW_QUERYHELPER_HPP


#include <QObject>
#include <vector>
#include <QAbstractItemModel>
#include <components/openmw-mp/Master/MasterData.hpp>

Q_DECLARE_METATYPE(QueryData)

class QueryHelper : public QObject
{
Q_OBJECT
public:
    explicit QueryHelper(QAbstractItemModel *model);
public slots:
    void refresh();
    void terminate();
private slots:
    void update(const QString &addr, unsigned short port, const QueryData& data);
signals:
    void finished();
    void started();
private:
    QThread *queryThread;
    QAbstractItemModel *_model;
};

class QueryUpdate : public QObject
{
    friend class QueryHelper;
Q_OBJECT
signals:
    void finished();
    void updateModel(const QString &addr, unsigned short port, const QueryData& data);
public slots:
    void process();
};

#endif //OPENMW_QUERYHELPER_HPP
