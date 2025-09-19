#include "difficultyscaling.hpp"

#include <components/settings/settings.hpp>

/*
    Start of tes3mp addition

    Include additional headers for multiplayer purposes
*/
#include "../mwmp/Main.hpp"
#include "../mwmp/LocalPlayer.hpp"
/*
    End of tes3mp addition
*/

#include "../mwbase/world.hpp"
#include "../mwbase/environment.hpp"
#include "../mwworld/esmstore.hpp"

#include "actorutil.hpp"


/// new dwemercoda difficulty tier function
int difficultyTier()
{
    /// openmw difficulty check, code preserved as I dont know what effects removing it could have
    int difficultySetting = Settings::Manager::getInt("difficulty", "Game");
    difficultySetting = std::min(difficultySetting, 500);
    difficultySetting = std::max(difficultySetting, -500);


    /// difficulty is got from the local player info as per tes3mp change versus openmw and this overrides the openmw setting
    difficultySetting = mwmp::Main::get().getLocalPlayer()->difficulty;
    difficultySetting = std::min(difficultySetting, 500);
    difficultySetting = std::max(difficultySetting, -500);

    if (difficultySetting <= 0)
        return 1;
    else if (difficultySetting <= 50)
        return 2;
    else if (difficultySetting <= 100)
        return 3;
    else if (difficultySetting <= 150)
        return 4;
    else if (difficultySetting <= 200)
        return 5;
    else
        return 6;
}


float onstrikeDamageScale()
{
    int tier = difficultyTier();
    switch (tier)
    {
    case 1: return 1.00f;
    case 2: return 0.75f;
    case 3: return 0.50f;
    case 4: return 0.30f;
    case 5: return 0.20f;
    case 6: return 0.15f;
    default: return 1.0f;
    }
}

float castenchantedDamagescale()
{
    int tier = difficultyTier();
    switch (tier)
    {
    case 1: return 1.00f;
    case 2: return 0.85f;
    case 3: return 0.70f;
    case 4: return 0.50f;
    case 5: return 0.33f;
    case 6: return 0.25f;
    default: return 1.0f;
    }
}

float magicdamagetaken()
{
    int tier = difficultyTier();
    switch (tier)
    {
    case 1: return 1.00f;
    case 2: return 1.25f;
    case 3: return 1.50f;
    case 4: return 2.00f;
    case 5: return 2.50f;
    case 6: return 3.00f;
    default: return 1.0f;
    }
}

float armourdamagetaken()
{
    int tier = difficultyTier();
    switch (tier)
    {
    case 1: return 1.00f;
    case 2: return 1.50f;
    case 3: return 2.00f;
    case 4: return 3.00f;
    case 5: return 4.50f;
    case 6: return 5.00f;
    default: return 1.0f;
    }
}

float weapondamagetaken()
{
    int tier = difficultyTier();
    switch (tier)
    {
    case 1: return 1.00f;
    case 2: return 0.75f;
    case 3: return 0.50f;
    case 4: return 0.30f;
    case 5: return 0.20f;
    case 6: return 0.15f;
    default: return 1.0f;
    }
}


float scaleDamage(float damage, const MWWorld::Ptr& attacker, const MWWorld::Ptr& victim)
{
    const MWWorld::Ptr& player = MWMechanics::getPlayer();

    int tier = difficultyTier();

    float dealMult = 1.0f;
    float takeMult = 1.0f;

    switch (tier)
    {
    case 1:
        break;
    case 2:
        dealMult = 0.75f;   
        takeMult = 1.50f;  
        break;
    case 3:
        dealMult = 0.50f;  
        takeMult = 2.00f;   
        break;
    case 4:
        dealMult = 0.30f; 
        takeMult = 3.00f;  
        break;
    case 5:
        dealMult = 0.20f;  
        takeMult = 4.00f;  
        break;
    case 6:
        dealMult = 0.15f;  
        takeMult = 5.00f; 
        break;
    default:
        break;
    }

    if (attacker == player)
    {
        damage *= dealMult;
    }
    else if (victim == player)
    {
        damage *= takeMult;
    }

    return damage;
}

float scaleHandDamage(float damage, const MWWorld::Ptr& attacker, const MWWorld::Ptr& victim)
{
    const MWWorld::Ptr& player = MWMechanics::getPlayer();

    int tier = difficultyTier();

    float dealMult = 1.0f;
    float takeMult = 1.0f;

    switch (tier)
    {
    case 1:
        break;
    case 2:
        dealMult = 0.85f;
        takeMult = 1.25f;
        break;
    case 3:
        dealMult = 0.70f;
        takeMult = 1.50f;
        break;
    case 4:
        dealMult = 0.50f;
        takeMult = 2.00f;
        break;
    case 5:
        dealMult = 0.33f;
        takeMult = 2.50f;
        break;
    case 6:
        dealMult = 0.25f;
        takeMult = 3.00f;
        break;
    default:
        break;
    }

    if (attacker == player)
    {
        damage *= dealMult;
    }
    else if (victim == player)
    {
        damage *= takeMult;
    }

    return damage;
}
