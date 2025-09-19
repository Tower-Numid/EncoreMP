#ifndef OPENMW_QUERYCLIENT_HPP
#define OPENMW_QUERYCLIENT_HPP

#include <string>
#include <RakPeerInterface.h>
#include <components/openmw-mp/Master/PacketMasterQuery.hpp>
#include <components/openmw-mp/Master/PacketMasterUpdate.hpp>
#include <apps/browser/ServerModel.hpp>
#include <mutex>

class QueryClient
{
public:
    QueryClient(QueryClient const &) = delete;
    QueryClient(QueryClient &&) = delete;
    QueryClient &operator=(QueryClient const &) = delete;
    QueryClient &operator=(QueryClient &&) = delete;

    static QueryClient &Get();
    void SetServer(const std::string &addr, unsigned short port);
    std::map<RakNet::SystemAddress, QueryData> Query();
    std::pair<RakNet::SystemAddress, QueryData> Update(const RakNet::SystemAddress &addr);
    int Status();
private:
    RakNet::ConnectionState Connect();
    MASTER_PACKETS GetAnswer(MASTER_PACKETS packet);
protected:
    QueryClient();
    ~QueryClient();
private:
    int status;
    RakNet::RakPeerInterface *peer;
    RakNet::SystemAddress masterAddr;
    mwmp::PacketMasterQuery *pmq;
    mwmp::PacketMasterUpdate *pmu;
    std::pair<RakNet::SystemAddress, ServerData> server;
    std::mutex mxServers;

};


#endif //OPENMW_QUERYCLIENT_HPP
