#ifndef OPENMW_MWMECHANICS_DIFFICULTYSCALING_H
#define OPENMW_MWMECHANICS_DIFFICULTYSCALING_H

namespace MWWorld
{
    class Ptr;
}

// Scales damage dealt to an actor based on difficulty setting
float scaleDamage(float damage, const MWWorld::Ptr& attacker, const MWWorld::Ptr& victim);

// Scales damage dealt to an actor based on difficulty setting for hand to hand
float scaleHandDamage(float damage, const MWWorld::Ptr& attacker, const MWWorld::Ptr& victim);

// new EncoreMP difficulty tier functions
int difficultyTier();

float onstrikeDamageScale();

float castenchantedDamagescale();

float magicdamagetaken();

float armourdamagetaken();

float weapondamagetaken();

#endif
