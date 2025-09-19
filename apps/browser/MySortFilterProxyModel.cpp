#include "MySortFilterProxyModel.hpp"
#include "ServerModel.hpp"

#include <qdebug.h>
#include <apps/browser/netutils/Utils.hpp>

bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{

    QModelIndex pingIndex = sourceModel()->index(sourceRow, ServerData::PING, sourceParent);
    QModelIndex plIndex = sourceModel()->index(sourceRow, ServerData::PLAYERS, sourceParent);
    QModelIndex maxPlIndex = sourceModel()->index(sourceRow, ServerData::MAX_PLAYERS, sourceParent);
    QModelIndex passwordIndex = sourceModel()->index(sourceRow, ServerData::PASSW, sourceParent);

    bool pingOk;
    int ping = sourceModel()->data(pingIndex).toInt(&pingOk);
    int players =  sourceModel()->data(plIndex).toInt();
    int maxPlayers =  sourceModel()->data(maxPlIndex).toInt();

    if (maxPing > 0 && (ping == -1 || ping > maxPing || !pingOk))
        return false;
    if (filterEmpty && players == 0)
        return false;
    if (filterFull && players >= maxPlayers)
        return false;
    if(filterPasswEnabled && sourceModel()->data(passwordIndex).toString() == "Yes")
        return false;

    return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
}

bool MySortFilterProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    if(sortColumn() == ServerData::PING)
    {
        bool valid;

        int pingright = sourceModel()->data(source_right).toInt(&valid);
        pingright = valid ? pingright : PING_UNREACHABLE;

        int pingleft = sourceModel()->data(source_left).toInt(&valid);
        pingleft = valid ? pingleft : PING_UNREACHABLE;
        return pingleft < pingright;
    }
    else
        return QSortFilterProxyModel::lessThan(source_left, source_right);
}

MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    filterEmpty = false;
    filterFull = false;
    filterPasswEnabled = false;
    maxPing = 0;
    setSortCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
}

void MySortFilterProxyModel::filterEmptyServers(bool state)
{
    filterEmpty = state;
    invalidateFilter();
}

void MySortFilterProxyModel::filterFullServer(bool state)
{
    filterFull = state;
    invalidateFilter();
}

void MySortFilterProxyModel::pingLessThan(int maxPing)
{
    this->maxPing = maxPing;
    invalidateFilter();
}

void MySortFilterProxyModel::filterPassworded(bool state)
{
    filterPasswEnabled = state;
    invalidateFilter();
}
