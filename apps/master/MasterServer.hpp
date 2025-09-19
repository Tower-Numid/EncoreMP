#ifndef NEWMASTERPROTO_MASTERSERVER_HPP
#define NEWMASTERPROTO_MASTERSERVER_HPP

#include <thread>
#include <chrono>
#include <RakPeerInterface.h>
#include <components/openmw-mp/Master/MasterData.hpp>

class MasterServer
{
public:
    struct Ban
    {
        RakNet::SystemAddress sa;
        bool permanent;
        struct Date
        {
        } date;
    };
    struct SServer : QueryData
    {
        std::chrono::steady_clock::time_point lastUpdate;
    };
    typedef std::map<RakNet::SystemAddress, SServer> ServerMap;
    //typedef ServerMap::const_iterator ServerCIter;
    typedef ServerMap::iterator ServerIter;

    MasterServer(unsigned short maxConnections, unsigned short port);
    ~MasterServer();

    void Start();
    void Stop(bool wait = false);
    bool isRunning();
    void Wait();

    ServerMap* GetServers();

private:
    void Thread();

private:
    std::thread tMasterThread;
    RakNet::RakPeerInterface* peer;
    RakNet::SocketDescriptor sockdescr;
    ServerMap servers;
    bool run;
    std::map<RakNet::RakNetGUID, std::chrono::steady_clock::time_point> pendingACKs;
};


#endif //NEWMASTERPROTO_MASTERSERVER_HPP
