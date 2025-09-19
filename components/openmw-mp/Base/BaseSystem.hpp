#ifndef OPENMW_BASESYSTEM_HPP
#define OPENMW_BASESYSTEM_HPP

#include <string>

#include <RakNetTypes.h>

namespace mwmp
{
    class BaseSystem
    {
    public:

        BaseSystem(RakNet::RakNetGUID guid) : guid(guid)
        {

        }

        BaseSystem()
        {

        }

        RakNet::RakNetGUID guid;
        std::string playerName;
        std::string serverPassword;

    };
}

#endif //OPENMW_BASESYSTEM_HPP
