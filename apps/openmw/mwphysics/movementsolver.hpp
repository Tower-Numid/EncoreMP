#ifndef OPENMW_MWPHYSICS_MOVEMENTSOLVER_H
#define OPENMW_MWPHYSICS_MOVEMENTSOLVER_H

#include <osg/Vec3f>

#include "constants.hpp"
#include "../mwworld/ptr.hpp"

// EncoreMP header additions

#include "../mwbase/world.hpp"
#include "../mwbase/environment.hpp"
#include "../mwbase/mechanicsmanager.hpp"

#include "../mwworld/esmstore.hpp"
#include "../mwworld/class.hpp"
#include "../mwworld/ptr.hpp"
#include "../mwworld/player.hpp"

#include "../mwmechanics/creaturestats.hpp"
#include "../mwmechanics/npcstats.hpp"

// EncoreMP header additions

class btCollisionWorld;

namespace MWWorld
{
    class Ptr;
}

namespace MWPhysics
{
    /// Vector projection
    static inline osg::Vec3f project(const osg::Vec3f& u, const osg::Vec3f &v)
    {
        return v * (u * v);
    }

    /// Vector rejection
    static inline osg::Vec3f reject(const osg::Vec3f& direction, const osg::Vec3f &planeNormal)
    {
        return direction - project(direction, planeNormal);
    }

    template <class Vec3>
    static bool isWalkableSlope(const Vec3 &normal)
    {
        // start of EncoreMP changes
        static const float sMaxSlopeCos = std::cos(osg::DegreesToRadians(sMaxSlope));
        float newmaxslopeholder = sMaxSlopeCos;

        const MWWorld::Ptr player = MWBase::Environment::get().getWorld()->getPlayerPtr();

        if (player == MWBase::Environment::get().getWorld()->getPlayerPtr()) 
        {
            const MWMechanics::NpcStats &ptrNpcStats = player.getClass().getNpcStats(player);
            const int baseAcrobatics = ptrNpcStats.getSkill(20).getBase();
            float basedegrees = 47.0f;
            if (baseAcrobatics > 30)
            {
                if (baseAcrobatics <= 60)
                {
                    // Skill divided by 3 is added to angle you can climb, up to 60. so 57.0f at 60 skill.
                    basedegrees += (baseAcrobatics - 30) / 3.0f;
                }
                else
                {
                    // At 61 and above just override the base angle to 57, and then start adding 1 degree per level
                    basedegrees = 57.0f + (baseAcrobatics - 60);
                    // Clamp max to 89 (at 92 skill)
                    if (basedegrees > 89.0f)
                        basedegrees = 89.0f;
                }
            }
            newmaxslopeholder = std::cos(osg::DegreesToRadians(basedegrees));
        }
        return (normal.z() > newmaxslopeholder);
        // end of EncoreMP changes
    }

    class Actor;
    struct ActorFrameData;
    struct WorldFrameData;

    class MovementSolver
    {
    public:
        static osg::Vec3f traceDown(const MWWorld::Ptr &ptr, const osg::Vec3f& position, Actor* actor, btCollisionWorld* collisionWorld, float maxHeight);
        static void move(ActorFrameData& actor, float time, const btCollisionWorld* collisionWorld, WorldFrameData& worldData);
        static void unstuck(ActorFrameData& actor, const btCollisionWorld* collisionWorld);
    };
}

#endif
