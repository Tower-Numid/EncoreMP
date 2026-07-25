
# Compiling Changelog
For the V0.93 release    

This is a guide to the coding changes made, and the reasoning behind them. Hopefully it's useful if you want to change parts of the project yourself, or learn about the engine structure.        

Some sections are missing, this is intentional, they have been removed as they became obsolete.    

## Table of contents

1. Enchanting    
2. XP gain    
3. Training costs    
4. Magic resist cap    
5. Miscellaneous changes     
6. Melee changes    
7. Ranged changes    
8. Acrobatics and climbing    
9. Difficuly overhaul (also see 29.)    
10. Equipment derived armour ratings    
11. Unarmored    
12. Creature armour ratings    
13. Armorer    
14. Swimming    
15. Removed - Obsolete Section    
16. Mercantile    
17. NPC spellcasting locked to base game spell effect costs   
18. Alchemy    
19. Removed - Obsolete Section    
20. Removed - Obsolete Section    
21. Variable spellcasting XP gain    
22. Removed - Obsolete Section    
23. Willpower changes    
24. Removed - Obsolete Section    
25. Hand to hand    
26. Pickpocketing    
27. Server checksum    
28. Caching stealth checks    
29. Ally difficulty scaling    
30. Spell buying menu substitution system   
31. New gameplay settings    


## 1, Enchanting
`openmw\enchanting.cpp`
`openmw\spellutil.cpp`

**Effect of soul size**
- Introduced variable XP gain based on soul size, scaling from 1.0x at 0 to 4.0x at 400+
    - The logic linearly scales the XP multiplier between the values shown below:
    - Soul size 0 - 60, 1.0f to 2.0f
    - 60 - 180, 2.0f to 3.0f
    - 180 - 400, 3.0f to 4.0f
    - 400+ 4.0f flat (no further increase in XP gain)
- Introduced a variable bonus to enchanting success rate (by effectively adding to the enchanting skill) based on soul size
	- Scales linearly between these values:
	- Soul size 0-30, from a +0 to a +5 modifier
	- Soul size 30-60, from a +5 to a +10 modifier
	- Soul size 60-120, from a +10 to a +15 modifier
	- Soul size 120-180, from a +15 to a +20 modifier
	- Soul size 180-400, from a +20 to a +30 modifier
	- Soul size 400+, a flat +30 modifier

**Item capacity**
- Changed the enchanting capacity of items by altering the equation to generate on a curve by introducing a SQRT to the equation. No other changes involved, all relevant code is within the `int Enchanting::getMaxEnchantValue() const` function.
	- Enchanting.cpp now requires `cmath` in the header to use the SQRT function.
		- Relies on `cmath`
	- There is a check to ensure that that SQRT equation will be skipped and instead 0 is returned, if the game detects an item has (somehow) got a capacity of -5 or less. The use of the SQRT would return unexpected behaviour in these situations otherwise. Should never be a problem if the game is being modded as intended (with values of 0 and above)

**On hit cost reduction**
- Added a 0.25x multiplier to on-hit item charge costs before they go into the on-use equation
- This change is made in `cast` in `spellcasting.cpp`

```
            //EncoreMP, reduce cost of on-strike enchantments, V0.92
            if (mCaster == getPlayer())
            {
                if (type == ESM::Enchantment::WhenStrikes)
                {
                    castCost *= 0.25;
                    castCost = std::max(1, castCost);
                }
            }
```

**School based cost modification**
- Within `getEnchantPoints`
    - All effects belonging to the destruction and restoration schools of magic have had their costs doubled when making any enchantments, to balance the power of enchanting and to give it a niche of "indirect" effects
    - The effects "absorb health" and "absorb fatigue" also had their costs doubled for all enchantments, as they are the only other sources of direct damage

```
			if (magicEffect)
			{
				int school = magicEffect->mData.mSchool;
                // EncoreMP, double the cost of all destruction and restoration enchants of any kind, for balance (stacks with on-strike mod)
				if (school == 2 || school == 5)
				{
                    multpool *= 2.0f;
				}
                if (effenumid == 86 || effenumid == 88)
                {
                    //EncoreMP, also double the cost of absorb health/fatigue when enchanting, as they are the only other sources of direct damage not in destruction
                    multpool *= 2.0f;
                }
			}
```


**Multiple effects no longer stack costs**
- Restructured `getEnchantPoints()`, which determines the capacity/on-use cost of enchantments in a few ways
	- Multiple enchantments on an item no longer cause the overall enchantment capacity to increase above the sum of the individual enchantments
	- Previously in core morrowind, the cost of multiple enchantments on an item compounded. This is no longer the case, and now you can enchant an item with any number of seperate enchantments without introducing an additional cost multiplier


**On-use enchantments**
- Enchanting difficulty modified
	- For on-use enchantments, the base game logic is used with three modifications
		- A flat invisible +5 to enchanting skill, to make low level enchanting slightly more reliable
		- An 1.5 increase in cost for all enchantments that exceed 30 points in cost, but just for the portion that goes over 30 (e.g. a 35 cost enchantment now has an effective difficulty of 37.5)
		- The success rate from soul size is added

**Use Once (scrolls)**
- Scrolls use half the enchanting capacity compared to all other enchantment types
- Scrolls are much easier to make at low costs (around +40% success rate at costs 1-3). This bonus linearly decreases until at costs of 10 or more there is no bonus

To halve the cost of enchantments on scrolls, this clause was added near the end of `getEnchantPoints`
```
//EncoreMP V0.92, halve all enchantment costs on scrolls
if (mCastStyle == ESM::Enchantment::CastOnce)
{
    cost *= 0.5f;
}
```

To add to the success rate for enchantment costs below 10 this clause was added to`getEnchantChance`
```
        //when used logic + cast once (scroll) logic
        //comes before the float x = equation so that this value is modified by fatigue, GMST, etc
        if (mCastStyle == ESM::Enchantment::WhenUsed || mCastStyle == ESM::Enchantment::CastOnce)
        {
            //small boost to generic success to smooth low levels
            d += 5;
            //add soul gem size bonus to success rate
            d += enchantDifficultyMod;
            //add a large boost for enchantments less than size 10, for scrolls only
            if (mCastStyle == ESM::Enchantment::CastOnce)
            {
                if (enchantPointsHolder < 10)
                {
                    d += 40;
                    d -= (enchantPointsHolder * 4);
                }
            }
            // increase difficulty when enchanting capacity exceeds 30
            // for every point over 30, add half its value again to the cost
            if (enchantPointsHolder > 30)
            {
                float enchantPenaltyB = enchantPointsHolder - 30;
                enchantPenaltyB *= 0.5;
                enchantPointsHolder += enchantPenaltyB;
            }
        }
```
This adds +40, and removes 4 for every point, resulting in no bonus remaining at 10

**On-Strike**
- This uses the same logic as on-use enchantments do for difficulty
- But all magic effects take up double capacity when used in an on-strike enchantment, for balance reasons


**Ammunition**
- Ammunition will now always enchant in batches of 20 and the OpenMW setting "projectiles enchant multiplier" has been disabled
- Ammunition recieves the same difficulty boost that scrolls do when cost is below 10, otherwise it obeys the on-strike difficulty and capacity rules

The server setting was commented out and the output was hardcoded to 0.05 for `getTypeMultiplier`
```
    float Enchanting::getTypeMultiplier() const
    {
        //static const bool useMultiplier = Settings::Manager::getFloat("projectiles enchant multiplier", "Game") > 0;
        //disabled for EncoreMP V0.92
        if (mWeaponType != -1 && getEnchantPoints() > 0)
        {
            ESM::WeaponType::Class weapclass = MWMechanics::getWeaponType(mWeaponType)->mWeaponClass;
            if (weapclass == ESM::WeaponType::Thrown || weapclass == ESM::WeaponType::Ammo)
                return 0.05f;
        }

        return 1.f;
    }
```
The setting was disabled here as well, and now `getEnchantItemsCount` always returns up to 20 of an ammunition stack if it is avaliable
```
    int Enchanting::getEnchantItemsCount() const
    {
        int count = 1;
        float enchantPoints = getEnchantPoints();
        if (mWeaponType != -1 && enchantPoints > 0)
        {
            ESM::WeaponType::Class weapclass = MWMechanics::getWeaponType(mWeaponType)->mWeaponClass;
            if (weapclass == ESM::WeaponType::Thrown || weapclass == ESM::WeaponType::Ammo)
            {
                //static const float multiplier = std::max(0.f, std::min(1.0f, Settings::Manager::getFloat("projectiles enchant multiplier", "Game")));
                //disabled for EncoreMP V0.92
                MWWorld::Ptr player = getPlayer();
                int itemsInInventoryCount = player.getClass().getContainerStore(player).count(mOldItemPtr.getCellRef().getRefId());
                count = std::min(itemsInInventoryCount, std::max(1, 20));
            }
        }

        return count;
    }
```

This block was added to `getEnchantChance` to account for enchanting less than 20 of an item, and to boost success rate when cost is below 10

```
        float typeMult = 1.0f;
        const int itemCount = getEnchantItemsCount();

        if (mWeaponType != -1)
        {
            //modify the per ammo difficulty to normalise it for all amounts of ammo
            if (weapclass == ESM::WeaponType::Thrown || weapclass == ESM::WeaponType::Ammo)
            {
                typeMult = (1.0f / itemCount);
                //add the same success rate for 10 and below that scrolls get, to make throwing weapons/ammo easier at low levels
                if (enchantPointsHolder < 10)
                {
                    d += 40;
                    d -= (enchantPointsHolder * 4);
                }
            }
        }
```


**Constant effects**
- Constant effect enchantments follow their own difficulty logic that scales off of the players base/unmodified enchanting skill
	- All constant effect enchantments check base enchanting skill, and either have a 0% or 100% chance of succeeding, based on the size of the enchantment vs your enchanting skill
	- [`A server setting has also been added which can toggle this feature off, and instead use base game constant effect enchanting logic`]
- The player can make constant effect enchantments of up to the following sizes at these skill levels:
	- Skill 59, no constant effect enchantments possible
	- Skill 60, up to 5 points CE
	- Skill 70, up to 15 points CE
	- Skill 80, up to 35 points CE
	- Skill 90, up to 65 points CE
	- Skill 99, up to 101 points CE
	- Skill 100, any sized constant effect enchantment
- The logic linearly interoplates between these values

Within `getEnchantChance`

```
        // get the lowest of base and modified skill, so that skill drain/damage is accounted for, but buffs to the skill are not
        float skillForCE = std::min(baseEnchantForCE, modifiedEnchantForCE);
        float allowedEnchantSize = 0.0f;
        float skillOverHolder = 0.0f;


        if (mCastStyle == ESM::Enchantment::ConstantEffect)
        {
            if (useEncoreConstantEffectLogic == true)
            {
                if (skillForCE < 60.0f)
                {
                    //always fail is skill is below 60
                    x = 0;
                }
                else if (skillForCE >= 100.0f)
                {
                    //always succed when skill is 100
                    x = 100;
                }
                else
                {
                    // calculate the allowed size you can make based on skill

                    if (skillForCE < 70.0f)
                    {
                        allowedEnchantSize = 5.0f;
                        skillOverHolder = (skillForCE - 60.0f);
                        allowedEnchantSize += skillOverHolder;
                    }
                    else if (skillForCE < 80.0f)
                    {
                        allowedEnchantSize = 15.0f;
                        skillOverHolder = (skillForCE - 70.0f);
                        allowedEnchantSize += (2.0f * skillOverHolder);
                    }
                    else if (skillForCE < 90.0f)
                    {
                        allowedEnchantSize = 35.0f;
                        skillOverHolder = (skillForCE - 80.0f);
                        allowedEnchantSize += (3.0f * skillOverHolder);
                    }
                    else
                    {
                        allowedEnchantSize = 65.0f;
                        skillOverHolder = (skillForCE - 90.0f);
                        allowedEnchantSize += (4.0f * skillOverHolder);
                    }

                    //if allowed size is equal to or greater than the size you are trying to make, always suceed, else always fail
                    if (allowedEnchantSize >= enchantPointsForCE)
                    {
                        x = 100;
                    }
                    else
                    {
                        x = 0;
                    }
                }
            }
            else
            {
                x *= fEnchantmentConstantChanceMult;
            }
```

---
	`TES3MP\apps\openmw\spellutil.cpp`
**Charge cost reduction from skill**
- The logic which governs how much the players enchanting skill reduces the cost of using/casting an enchantment was modified
- In `getEffectiveEnchantmentCastCost` within `spellutil.cpp` this block was added

```
    int getEffectiveEnchantmentCastCost(float castCost, const MWWorld::Ptr &actor)
    {
        int eSkill = actor.getClass().getSkill(actor, ESM::Skill::Enchant);
        MWWorld::Ptr player = MWMechanics::getPlayer();
        if (actor == player)
        {
            //EncoreMP adjusted logic for the player only
            eSkill = std::max(1, eSkill);
            eSkill = std::min(100, eSkill);
            const float result = castCost - (castCost*(eSkill*0.008));
            return static_cast<int>((result < 1) ? 1 : result);
        }
        else
        {
            // original base game logic
            const float result = castCost - (castCost / 100) * (eSkill - 10);
            return static_cast<int>((result < 1) ? 1 : result);
        }
    }
```
- It forks the logic if the caster is the player, so this change does not affect NPCs
- It caps the contribution from skill to 100, so enchanting past 100 provides no further benefit
- The cost of using an enchantment scales linearly down from 99.2% at 1 skill, to 20% at 100 skill

**Service costs**    
Enchanting service costs have been modified, all changes have been made in `getEnchantPrice` within `enchanting.cpp`

The function has been updated to:
```
   int Enchanting::getEnchantPrice() const
   {
       if(mEnchanter.isEmpty())
           return 0;

       // Encore, get enchantment points to allow cost modification
       float enchantpointforcost = getEnchantPoints();

       // Encore, apply a cost increase past 30 points, to mirror the new difficulty logic
       if (mCastStyle == ESM::Enchantment::WhenUsed || mCastStyle == ESM::Enchantment::CastOnce || mCastStyle == ESM::Enchantment::WhenStrikes)
       {
           if (enchantpointforcost > 30.0f)
           {
               enchantpointforcost = (30.0f + ((enchantpointforcost - 30.0f)*1.5f));
           }
       }

       // base game logic to calculate price, using enchantpointforcost now instead of getEnchantPoints()
       float priceMultipler = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find("fEnchantmentValueMult")->mValue.getFloat();
       int price = MWBase::Environment::get().getMechanicsManager()->getBarterOffer(mEnchanter, static_cast<int>(enchantpointforcost * priceMultipler), true);
       price *= getEnchantItemsCount() * getTypeMultiplier();

       // Encore, double the price for constant effects
       if (mCastStyle == ESM::Enchantment::ConstantEffect)
       {
           price *= 2;
       }

       // Encore, lower scroll costs to 1/25th
       if (mCastStyle == ESM::Enchantment::CastOnce)
       {
           price *= 0.04;
       }

       ESM::WeaponType::Class weapClass = MWMechanics::getWeaponType(mWeaponType)->mWeaponClass;

       //Encore, lower ammunition costs to 1/20th
       if (mCastStyle == ESM::Enchantment::WhenStrikes)
       {
           if (mWeaponType != -1)
           {
               if (weapClass == ESM::WeaponType::Thrown || weapClass == ESM::WeaponType::Ammo)
               {
                   price *= 0.05;
               }
           }
       }

       return std::max(1, price);
   }
```

Summary of changes:
- Constant effect enchantments are 2x GMST per point (GMST is 1000 by default, so a 100 point CE will now cost 200k gold before mercantile discounts apply)
- On-use, on-strike, scrolls, and ammunition, all retain the base game costs up until 30 points of enchantment value, after 30 points each point costs 1.5x (to mirror the change to difficulty logic in making enchantments)
	- e.g. for a 30 point enchantemnt you would pay 30k, for a 40 point enchantment you would pay 45k (because 10 of the capacity points are over 30, so 10*1.5 = 15, resulting in an effective cost of 45 points)
- Scrolls are then discounted to 1/25th of the GMST value per point, so a 20 point scroll costs 800gp before mercantile discounts apply
	- Note that scrolls use half the enchantment capacity compared to other items, so you are also getting a stronger effect for the equivalent point value
- Ammunition is discounted to 1/20th of the GMST value per point, per stack of 20 ammunition
	- So making 20 enchanted arrows with a 20 point enchantment would cost 1,000gp before mercantile discounts
	- If you made e.g. only 10 arrows in one batch, the price would lower accordingly to 500gp

**Bugfix: Ammunition no longer splits the charge of a soul gem**    
- This was likely intentional, but given that ammunition enchanting was poorly implemented (if at all), I have changed it so that making a stack of 20 ammunition no longer splits the charge of the soul gem
	- The issue was that you could make, e.g., 20 arrows using a size 5 soul, and the UI would then show the arrows as having "0/0" charge, as the actual charge value was less than 1 and being truncated to 0
	- I do not think this had any affect on the ammunition themselves, during previous testing they would still trigger their on-hit abilities regardless of charge, but making this change cleaned up a UI bug

Within the `create` function within `enchanting.cpp`

This block
```
        if(mCastStyle==ESM::Enchantment::ConstantEffect)
            enchantment.mData.mCharge = 0;
        else
            enchantment.mData.mCharge = getGemCharge() / count;
```

 was replaced with this
```
        if(mCastStyle==ESM::Enchantment::ConstantEffect)
            enchantment.mData.mCharge = 0;
        else
            enchantment.mData.mCharge = getGemCharge();
```
So now each item of ammunition recieves the full charge of the soul gem

---


## 2, XP gain
`npcstats.cpp`
- Changed the `useSkill` function to add a non-linear curve insertion of code block. Simply checks for players base skill level and reduces the XP gained by the multipliers shown in the mechanics changelog depending on level
- Also changed the `getSkillProgressRequirement` function in `npcstats.cpp` to have a floor value of 20, so skills below 20 will still require 20xp to advance. Done by adding a `std:: max 20` pre-check function to the existing calculation
- Added a new setting to the engine, `global XP gain multiplier` which is 1.0f by default
- This is a float value which is multiplied by all XP earned for all skills
- Good if you want to drag out the low levels and experience an epic TR game

## 3, Training costs
`trainingwindow.cpp`  
These changes are not well documented, look in `trainingwindow.cpp`  for all the changes made
- `trainingwindow.cpp` was modified in two locations to produce a non-linear increase in training costs for all skills whilst respecting the GMST. So the GMST training cost setting of 10 can be doubled to 20, for example, and the non-linear price increases will also double in line with this
- Note that two edits were required (with duplicate code) as this file calculates the cost mechanically and the cost in the UI (training window) independently

## 4, Magic resist cap
`spellcasting.cpp`
`inventorystore.cpp`

 - Magic resistance now has no mechanical effect beyond 60% (after accounting for weakness effects which negate it 1:1)
 - Added a clause each to each of `spellcasting.cpp` and `inventorystore.cpp`. It was necessary for it to be formatted differently in each location, but the function is the same
 - Had to manually define the list of effects which were to have their resistances capped
 - TGM is unaffected, it still gets full immunity due to the location this code change was positioned
 - In `spellcasting.cpp` the `inflict` function was modified with a conditional check that caps magic resist for a pre-defined list of effects
 - In `inventorystore.cpp` the `updateMagicEffects` function was modified with the same logic but formatted slightly differently as this file required
 - The two changes were necessary as `inflict` in `spellcasting.cpp` covers all possible sources of negative effects except for constant effect enchantments, which are handled via the `inventorystore.cpp` code

## 5, Miscellaneous changes   
`npcstats.cpp`
`repair.cpp`
`spellcasting.cpp`

- Skill books do not work at skill 90 and above anymore
	- Added a single conditional clause that returns the function if the skill-up gain is from a book and the base skill is 90 or above. The relevant function is `increaseSkill` in `npcstats.cpp` under the `if (readBook)` check.
	- Updated the `npcstats.cpp` file to include `settings.hpp` so that it can get settings
	- Added a fork in the logic that disables this feature if the Boolean `skill books have level limit` if set to false in the server config file
- Reduced the armorer sounds by changing the `repair` function within `repair.cpp` to play the sound at 0.5 instead of 1.0. 
	- This has to be done twice, as the tes3mp also sends a packet with the same information for others to hear. Also whilst the original values (from openmw) are written as "1.0" (which makes them doubles), I had to manually define them as floats when changing this otherwise a type conversion error was called. No effect on gameplay or code behaviour, just worth noting as an implicit conversion that has been made explicit

**Removing the out of charge message for empty on-strike weapons**    

 A bug was introduced to EncoreMP - the way I removed the "out of charge" message for on-hit effects resulted in it being removed from everything, but more than removing the message I appear to have removed the entire "stop" bit of the code - so as a result the game let's you cast enchanted items with 0 charge but they do nothing - however the entire animation plays, a bolt is generated, etc. So that's a problem that needs fixing, they need to register as out of charge still, go back and fix that

Current code in `spellcasting.cpp`
```
            if (item.getCellRef().getEnchantmentCharge() < castCost)
            {
                return false;
            }
```

original code (full block)

```
        if (!godmode && (type == ESM::Enchantment::WhenUsed || (!isProjectile && type == ESM::Enchantment::WhenStrikes)))
        {
            int castCost = getEffectiveEnchantmentCastCost(static_cast<float>(enchantment->mData.mCost), mCaster);

            if (item.getCellRef().getEnchantmentCharge() == -1)
                item.getCellRef().setEnchantmentCharge(static_cast<float>(enchantment->mData.mCharge));

            if (item.getCellRef().getEnchantmentCharge() < castCost)
            {
                if (mCaster == getPlayer())
                {
                    MWBase::Environment::get().getWindowManager()->messageBox("#{sMagicInsufficientCharge}");

                    // Failure sound
                    int school = 0;
                    if (!enchantment->mEffects.mList.empty())
                    {
                        short effectId = enchantment->mEffects.mList.front().mEffectID;
                        const ESM::MagicEffect* magicEffect = MWBase::Environment::get().getWorld()->getStore().get<ESM::MagicEffect>().find(effectId);
                        school = magicEffect->mData.mSchool;
                    }

                    static const std::string schools[] = {
                        "alteration", "conjuration", "destruction", "illusion", "mysticism", "restoration"
                    };
                    MWBase::SoundManager *sndMgr = MWBase::Environment::get().getSoundManager();
                    sndMgr->playSound3D(mCaster, "Spell Failure " + schools[school], 1.0f, 1.0f);

                    /*
                        Start of tes3mp addition

                        Send an ID_OBJECT_SOUND packet every time a sound is made here
                    */
                    mwmp::ObjectList* objectList = mwmp::Main::get().getNetworking()->getObjectList();
                    objectList->reset();
                    objectList->packetOrigin = mwmp::CLIENT_GAMEPLAY;
                    objectList->addObjectSound(mCaster, "Spell Failure " + schools[school], 1.0f, 1.0f);
                    objectList->sendObjectSound();
                    /*
                        End of tes3mp addition
                    */
                }
                return false;
            }
            // Reduce charge
            item.getCellRef().setEnchantmentCharge(item.getCellRef().getEnchantmentCharge() - castCost);
        }
```

The fixed code block

```
        if (!godmode && (type == ESM::Enchantment::WhenUsed || (!isProjectile && type == ESM::Enchantment::WhenStrikes)))
        {
            int castCost = getEffectiveEnchantmentCastCost(static_cast<float>(enchantment->mData.mCost), mCaster);

            if (item.getCellRef().getEnchantmentCharge() == -1)
                item.getCellRef().setEnchantmentCharge(static_cast<float>(enchantment->mData.mCharge));

            if (item.getCellRef().getEnchantmentCharge() < castCost)
            {
                if (mCaster == getPlayer())
                {
                    if (type == ESM::Enchantment::WhenStrikes)
                    {
                        return false;
                    }
                    MWBase::Environment::get().getWindowManager()->messageBox("#{sMagicInsufficientCharge}");

                    // Failure sound
                    int school = 0;
                    if (!enchantment->mEffects.mList.empty())
                    {
                        short effectId = enchantment->mEffects.mList.front().mEffectID;
                        const ESM::MagicEffect* magicEffect = MWBase::Environment::get().getWorld()->getStore().get<ESM::MagicEffect>().find(effectId);
                        school = magicEffect->mData.mSchool;
                    }

                    static const std::string schools[] = {
                        "alteration", "conjuration", "destruction", "illusion", "mysticism", "restoration"
                    };
                    MWBase::SoundManager *sndMgr = MWBase::Environment::get().getSoundManager();
                    sndMgr->playSound3D(mCaster, "Spell Failure " + schools[school], 1.0f, 1.0f);

                    /*
                        Start of tes3mp addition

                        Send an ID_OBJECT_SOUND packet every time a sound is made here
                    */
                    mwmp::ObjectList* objectList = mwmp::Main::get().getNetworking()->getObjectList();
                    objectList->reset();
                    objectList->packetOrigin = mwmp::CLIENT_GAMEPLAY;
                    objectList->addObjectSound(mCaster, "Spell Failure " + schools[school], 1.0f, 1.0f);
                    objectList->sendObjectSound();
                    /*
                        End of tes3mp addition
                    */
                }
                return false;
            }
            // Reduce charge
            item.getCellRef().setEnchantmentCharge(item.getCellRef().getEnchantmentCharge() - castCost);
        }
```

It already had the enchantment type data in the type variable, so I just asked it to early out and return if the type is on-strike (once it detects there is not enough charge)
The result is that behaviour is unchanged for on-use items, but for on-strike items the sound and error message no longer execute




## 6, Melee changes
`npc.cpp`
`combat.cpp`

**Accuracy**
- The change to base hit chance calculations are implemented in the function `getHitChance` within `combat.cpp`. Now accuracy is (skill x 0.8) + 10, instead of (skill x1). Agility, luck, fatigue and enemy evasion are all handled normally
- 2h accuracy penalties are implemented in the same function `hit` within `npc.cpp`

**Damage**
- The change to how base damage is calculated (using skill as well as an attribute, with the same sum benefit of +50%) is implemented in the function `adjustWeaponDamage` within `combat.cpp`

**Weapon type benefits**
- The short blade accuracy boost is implemented within `npc.cpp` in the `hit` function
- The changes to what contributes to damage for each weapon are implemented in the function `adjustWeaponDamage` within `combat.cpp`

**Gameplay settings**
- Two new gameplay settings have been added to toggle EncoreMP behaviour
- `two handed weapons receive an accuracy penalty`
	- If true: 2 handed weapons take the -15% to hit penalty
	- If false: 2 handed weapons recieve no penalty to their hit chance 
- `staves receive accuracy bonus instead of two handed penalty`
	- If true: Staves recieve the +20% to hit chance bonus
	- If false: Staves use whatever modifier applies to other 2h weapons (if 2h accuracy penalty is on, staves take the -15% hit chance penalty, if that setting is also false then staves take neither the +20% bonus nor the -15% penalty) 


## 7, Ranged changes
`combat.cpp`
**Accuracy**
- Ranged attacks follow the same accuracy change logic as implemented for melee, as determined in the `getHitChance` function within `combat.cpp`
	- In addition within the `projectileHit` function in `combat.cpp` ranged attacks are there given a flat +10 to hit, for balancing reasons (they are intended to be more accurate to make up for missed shots due to poor aim)

**Damage**
- Bows and crossbows have their damage modified to function similar to melee, increasing with skill and attribute, but they use agility as their damage attribute instead of strength. This is done in the `adjustWeaponDamage` function within `combat.cpp`
- Throwing scales differently, and uses strength and skill to determine damage. These are weighted equally as with melee, but the damage scaling for throwing progresses linearly from 0-100 to a higher cap of 200% weapon damage instead of 150% at 100 strength and 100 skill. Given that throwing weapons do 2x the stated damage, this means at max strength and skill throwing weapons do 4x the stated damage. This is also done in the `adjustWeaponDamage` function within `combat.cpp`

**Ammunition Recovery**
- Both enchanted and non-enchanted ammo recovery are handled via the `projectileHit` function within `combat.cpp` which has been modified
	- The function now checks player skill and uses it to multiply the GMST ammo recovery value. For non-enchanted the recovery rate cannot be less than 1x GMST, at from 25 to 100 it scales linearly up to 4x GMST (every 25 skill is another 1x GMST, it increments at each skill level as this is processed as a float)
	- The same function also allows for enchanted ammo recovery, but this only becomes possible at 50 skill and above. You start at 0 recovery rate at 50 skill, and each level beyond 50 adds 1/25th of the GMST recovery rate, so every 25 levels adds another 1x GMST up to 2x GMST total at 100 skill. This function hard caps the players skill it checks at 100 before processing, so there is no way to achieve beyond 2x GMST recovery rate.


## 8, Acrobatics and climbing
`movementsolver.hpp`
Headers added (to call player skill)

The `static bool isWalkableSlope` logic within `movementsolver.hpp` was updated to check if it is the player, and to get the players acrobatics skill and scale the climbing angle allowed based on skill as described in the mechanics changes.

The climbing angle is hard capped at 89° to prevent strange behaviour (90° resulted in players sticking to vertical walls during testing)

 - This change adjust the criteria for the engine to determine the boolean `iswalkableslope` and restricts it to the player
 - There is no effect on the default value (47°) at 30 skill or below, and no benefit beyond 92 skill (the angle you can climb to is hard capped to 89° for compatibility reasons)
 - Increasing the angle to 90° (or beyond) does not allow true wall climbing, due to separate logic checks in the openmw engine that exist  to prevent wall collision/sticking
	 - I did not attempt to resolve this, as this would require a more extensive rework of the physics engine which would further risk compatibility with new content.
	 - In short, whilst wall climbing is technically possible with some changes it meant (in the version I trialled) that you "stuck" to every wall you touched, which meant your speed slowed down to a crawl as you attempted to being moving vertically up it at greatly reduced speed, which was a huge problem in many urban areas and most interiors
- The `sMaxSlope` variable is seemingly not accessible to the compiler (47° - is it in the ESM file?) but it can be worked around in the way I have done without issues.
- Several functions within `movementsolver.cpp` call the Boolean `iswalkableslope`, these have been checked for unintended knock-on effects, and of the functions within the `cpp` file there are only two are of potential concern (although no issues have been seen yet during playtesting)
	- `osg::Vec3f MovementSolver::traceDown` beginning on line 80, but the bool starts getting called around line 106
		- I have no idea what the ray tracing logic does here, but it seems only to be involved in whether you can walk or not on a slope (so probably the actual post-hoc function that is implementing this change)
		- But since it involves ray tracing and ground offset there could be some object detection/collision issues that result in clipping(none seen yet during testing)
	- Also called twice between lines 367 to 392, to determine actor collision and determining if on slope. Again no idea what the impact of this is, but playtesting has not yet found an issue
	- Other areas of code checked and certainly of no concern for unintended behaviour, these two I couldn't pick apart in the time I spent on this (I am way out of my depth with the physics engine stuff)


## 9, Difficuly overhaul
Modified files:
`difficultyscaling.hpp`
`difficultyscaling.cpp`
`spellcasting.cpp` - headers added

[Note that in addition to these changes, further changes were made in later sections detailed here such as for hand to hand, which also affect the difficulty scaling files]

### 9.1, Tier function
In `difficultyscaling.hpp`
- `int difficultyTier();` function defined

In `difficultyscaling.cpp`:
- The function `int difficultyTier()` has been added 
	- This gets the difficulty and converts it to a tier
	- It gets the server config file difficulty setting (or player specific if overridden by server admins in tes3mp, the player specific values have not been play tested - as with base tes3mp it is not looking at the openmw difficulty setting)

The actual server config to difficulty tier conversion table as shown below:

| Server value | Tier | Comments                          | Tier name   |
| ------------ | ---- | --------------------------------- | ----------- |
| Less than 0  | 1    | 1 = normal, unchanged, difficulty | Apprentice  |
| 1-50         | 2    |                                   | Journeyman  |
| 51-100       | 3    |                                   | Master      |
| 101-150      | 4    |                                   | Grandmaster |
| 151-200      | 5    |                                   | Agent       |
| 201+         | 6    | 6 = absurdly difficult            | Nerevarine  |


```
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
```

### 9.2, Moving melee damage to tiers

In `difficultyscaling.cpp`:
The `float scaledamage` function has been updated to use the difficulty tier values as input for damage scaling, and now outputs pre-defined discrete damage modifiers at each tier as shown in this section. The effect of difficulty on melee damage dealt/taken now no longer operates via an equation which inputs `x` as difficulty.
Originally I think this was an int? In any case the original function has been completely overwritten.

- Note that this reduction in melee damage applies (as it does in the base game) after enemy armour is considered, so you will still be checking and overcoming armour using the same base game logic (for now, armour intentionally not touched at this stage of development as it's quite complicated and may not need adjusting at all)

Melee damage dealt/taken by difficulty tier:

| Difficulty setting | Tier | % Melee Dealt | % Melee Taken |
| ------------------ | ---- | ------------- | ------------- |
| Less than 0        | 1    | 100           | 100           |
| 1-50               | 2    | 75            | 150           |
| 51-100             | 3    | 50            | 200           |
| 101-150            | 4    | 30            | 300           |
| 151-200            | 5    | 20            | 400           |
| 201+               | 6    | 15            | 500           |

The `scaledamage` function just uses a `switch` logic table to choose the modifier based on tier got by `difficultyTier()`, as shown below:
```
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
```


### 9.3, Scaling on-strike and adding enchantment type detection

Via the following changes, on-strike enchantments specifically are tied to their own damage scaling table, which also operates off of difficulty tier - for now it is identical to melee damage dealt, but it is coded separately for ease of balancing

Tested and working for all effects, all sources of effect and also confirmed that absorb health correctly halves the magnitude of damage done and haling received  

| Difficulty setting | Tier | % Melee Dealt | % Melee Taken | % Enchantment damage dealt |
| ------------------ | ---- | ------------- | ------------- | -------------------------- |
| Less than 0        | 1    | 100           | 100           | 100                        |
| 1-50               | 2    | 75            | 150           | 75                         |
| 51-100             | 3    | 50            | 200           | 50                         |
| 101-150            | 4    | 30            | 300           | 30                         |
| 151-200            | 5    | 20            | 400           | 20                         |
| 201+               | 6    | 15            | 500           | 15                         |

Within `difficultyscaling.cpp`
`float onstrikeDamageScale()` function added, which simply gets tier and via a switch table returns a float modifier which is applied to spell effect magnitude. Unlike melee damage, for ease of implementation and changes, this does not take the damage and modify/return it, instead it locally only generates the multiplier, and spell magnitude is adjusted in situ for on-strike enchantments

Within `difficultyscaling.hpp`
defined that function via `float onstrikeDamageScale();`

```
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
```

However for this to work I had to enable the inflict portion of the `spellcasting.cpp` functions to get enchantment type (so I could filter there by enchantment type)

`spellcasting.cpp` headers update to include difficulty scaling via
`#include "difficultyscaling.hpp"`

The final block inserted within the `inflict` function in `spellcasting.cpp` - 
```
                if (mEnchantmentType == ESM::Enchantment::WhenStrikes && target != player && caster == player && (effectholder == 14 || effectholder == 15 || effectholder == 16 || effectholder == 18 || effectholder == 23 || effectholder == 27 || effectholder == 86))
                {
                    magnitude *= onstrikeDamageScale();
                }
```


[Notes on the base function without enchantment type additions]

First of all `!spell` checks the spell effect being inflicted is not in the players spell book (note that the `inflict` function processes all spell damaging effects)
`target != player` checks that the target is not the player (since this function is going to scale down damage, and we want to keep monster damage dealt the same)
`mCaster == player` checks the originator of the effect is the player, `mCaster` is already available in the base game, as it being handed to the generic `castspell` which is being overloaded into inflict
`effectholder` is defined just above this block via
`int effectholder = effectIt->mEffectID;`
and gets the spell effect enumeration as int, so that this function can be restricted to the manually curated list of effects only - I do not think this information (spell effect ID) was originally available in the function, but earlier coding changes to enchanting involved me making that information available locally, so no extra changes were needed by this stage, but see enchanting changes for how spell effect ID was made locally available within `spellcasting.cpp`

All of that (still excluding the `mEnchantmentType` check logic for now) would restrict the damage being dealt to when:
- It is a spell
- 'Cast' by the player
- That is not in the players spell book
- Whose target is anyone who is not the player
- Who effect is on the pre-defined list (each effect has it's magnitude checked, modified and applied separately, as per the base game functions in `spellcasting.cpp`)

[Adding enchantment type part 1 - header file + overload function]

That might be enough, but the only check so far (prior to me adding `mEnchantmentype`) to see that this was an on-strike was to check it was not a spell the player new, which probably was never going to work (scrolls may have been caught in this, as may have just about any other misc effects I wasn't expecting)

So then I wanted to give the function access to the type of enchantment which was the source of the effect, this was more complex as it involved tracing back the functions...

By default there is no enchantment information passed to this function.

`mEnchantmentType` was added to the generic `CastSpell::CastSpell` function so it could be overloaded whilst holding that data (set to a placeholder of -1, so that it wouldn't accidently trigger)
- Note that `mEnchantmentType` is stored and passed as an int, but can be (and is in my code) written as the string name of that enchantment type for readability

```
namespace MWMechanics
{
    CastSpell::CastSpell(const MWWorld::Ptr &caster, const MWWorld::Ptr &target, const bool fromProjectile, const bool manualSpell)
        : mCaster(caster)
        , mTarget(target)
        , mEnchantmentType(-1)
        , mSourceType(SourceType::Spell)
        , mFromProjectile(fromProjectile)
        , mManualSpell(manualSpell)
    {
    }
```

I'm pretty sure I added it here in the `spellcasting.hpp` header file, might have already been there, if not you need to add the line `struct Enchantment;`
```
namespace ESM
{
    struct Spell;
    struct Ingredient;
    struct Potion;
    struct EffectList;
    struct Enchantment;
}
```

Within `spellcasting.hpp`, within the `class castspell` space, the line
	- `int mEnchantmentType;` 
was added, so that the `castspell` function had that value initialised

```
    private:
        MWWorld::Ptr mCaster; // May be empty
        MWWorld::Ptr mTarget; // May be empty

        /// EncoreMP gets the enchantment type
        int mEnchantmentType;
```


[Adding enchantment type part 2 - sub-function within spellcasting.cpp]

Within `bool CastSpell::cast(const MWWorld::Ptr &item, bool launchProjectile)`,
which is the item specific function (the one that handles spells being cast from items, including those that apply on-strike),
The line
`        mEnchantmentType = enchantment->mData.mType;`
was added, which gets the enchantment type using the values initialised into the header file

I'm gonna be honest, at this point in the documentation I notice that the
 `bool CastSpell::cast(const MWWorld::Ptr &item, bool launchProjectile)`
 function already has all this data for decision like when to grant XP, so some or all my pre-steps in the header file may not have been necessary, oh well, I'm going to assume they are and just leave my steps in

Anyway, lastly because of all the above the `inflict` function now automatically has access to the `mEnchantmentType` data, as it passed to it from the `item` function automatically, so now in the `inflict` function I can then add the conditional check of,
`&& mEnchantmentType == ESM::Enchantment::WhenStrikes`,
in the if statement

This truly restricts these changes to spell effects coming from on-strike enchantments, so no unintended behaviour

The complete list of effects (for now) that will scale by difficulty are:
Destruction:
[14] Fire damage
[15] Shock damage
[16] Frost damage
[18] Drain health
[23] Damage health
[27] Poison
[86] Absorb health

[Going back and cleaning the function a little]

The function was trimmed a little to remove the `!spell` check, since it has become redundant since adding the enchantment type check, and actually I want this still to scale damage even if it is somehow in your spell book

So now it reads

```
if (mEnchantmentType == ESM::Enchantment::WhenStrikes && target != player && mCaster == player && (effectholder == 14 || effectholder == 15 || effectholder == 16 || effectholder == 18 || effectholder == 23 || effectholder == 27 || effectholder == 86))
 {
    magnitude *= onstrikeDamageScale();
 }
```


### 9.4, Castonce enchantment damage scaling

I scaled down this damage less aggressively than with melee, as unlike melee you can run out of mana/charge when casting, so it is a finite resource

| Difficulty Tier | % Enchantment magic damage dealt |
| --------------- | -------------------------------- |
| 1               | 1x                               |
| 2               | 0.85x                            |
| 3               | 0.7x                             |
| 4               | 0.5x                             |
| 5               | 0.33x                            |
| 6               | 0.25x                            |

Code changes,
`difficultyscaling.hpp` updated to include new function,
`float castenchantedDamagescale();`,
that function added to `difficultyscaling.cpp` and does,

```
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
```

then in `spellcasting.cpp`, a duplicate of the if statement used for on-strike damage modification was added with two changes, 1. it checks for on-use, 2. it applies `castenchantedDamagescale` instead

```
if ((mEnchantmentType == ESM::Enchantment::CastOnce || mEnchantmentType == ESM::Enchantment::WhenUsed) && target != player && caster == player && (effectholder == 14 || effectholder == 15 || effectholder == 16 || effectholder == 18 || effectholder == 23 || effectholder == 27 || effectholder == 86))
{
    magnitude *= castenchantedDamagescale();
}
```

### 9.5, On-use enchantment damage scaling

Done via updating the start of the above function to allow for either `castonce` or `whenused`. No other changes needed, working, they both use the same damage scaling function as a result (intended)

```
if ((mEnchantmentType == ESM::Enchantment::CastOnce || mEnchantmentType == ESM::Enchantment::WhenUsed)
```

### 9.6, Spell damage dealt

One change was left unfinished as it is not yet required, but will be:
- The actual scaling function that processes the spell magnitude in `difficultyscaling.cpp` is the same one that does enchanted items, etc, as for now I decided the scaling for each could match, but in the next revision it would be better to separate them so that they can be scaled separately 

**Summary**  

`spellcasting.hpp`

[1] `spellcasting.hpp` updated with new `enum class SourceType`, for use in tracking spell effect source/origin

[2] `spellcasting.hpp` also updated to initialise `SourceType` via the line

`SourceType mSourceType{ SourceType::None };` 

which was inserted at the bottom of the public space starting with

`bool mStack{false};`

[3] at some point in the `spellcasting.hpp` file I think I changed the order things are declared in that same public namespace, from what was default, I remember this was not necessary - in the end I can't see that I kept this change, but just keep it in mind in case there is an apparent different in line order in my version compared to the original, it was for this reason if so

`spellcasting.cpp`

[4] Also see the working out section below

**Working out**

Originally I just wanted to do something like
```
if ( spell && castByPlayer )
{
    // difficulty modifier goes here
}

```

The spellcasting.hpp header file had a new enumeration added to it for this purpose as below

```
    public:
        enum class SourceType
        {
            None,
            Spell,
            Potion,
            Ingredient,
            EnchantedItem
        };
```

this went right after 

```
    class CastSpell
    {

```

before the first private namespace

In addition to that, I also had to initialise the value in the `public:` space as shown below
```
    public:
        bool mStack{false};
        std::string mId; // ID of spell, potion, item etc
        std::string mSourceName; // Display name for spell, potion, etc
        osg::Vec3f mHitPosition{0,0,0}; // Used for spawning area orb
        bool mAlwaysSucceed{false}; // Always succeed spells casted by NPCs/creatures regardless of their chance (default: false)
        bool mFromProjectile; // True if spell is cast by enchantment of some projectile (arrow, bolt or thrown weapon)
        bool mManualSpell; // True if spell is casted from script and ignores some checks (mana level, success chance, etc.)
        SourceType mSourceType{ SourceType::None }; // EncoreMP addition
```
so just the last line was added


With all that done it was then used in `spellcasting.cpp` in the following way,
The `CastSpell::CastSpell` overload was updated to include the line
`, mSourceType(SourceType::Spell)`

```
{
    CastSpell::CastSpell(const MWWorld::Ptr &caster, const MWWorld::Ptr &target, const bool fromProjectile, const bool manualSpell)
        : mCaster(caster)
        , mTarget(target)
        , mEnchantmentType(-1)
        , mSourceType(SourceType::Spell)
        , mFromProjectile(fromProjectile)
        , mManualSpell(manualSpell)
    {
```


**Working out for the spellcasting.cpp file as opposed to the header**

Within `spellcasting.cpp`,
I updated the basic ` CastSpell::CastSpell` function to include the line
`, mSourceType(SourceType::Spell)` as shown below

```
{
    CastSpell::CastSpell(const MWWorld::Ptr &caster, const MWWorld::Ptr &target, const bool fromProjectile, const bool manualSpell)
        : mCaster(caster)
        , mTarget(target)
        , mEnchantmentType(-1)
        , mSourceType(SourceType::Spell)
        , mFromProjectile(fromProjectile)
        , mManualSpell(manualSpell)
    {
```

so that it would be a part of the overload to other functions

So this by default sets the source to spell (necessary as discussed later),

The overload  then passes to
`bool CastSpell::cast(const std::string &id)`
which sorts the spell effect into one of three functions, there were no changes here, just tracking it so the documentation is readable

Then within,
`bool CastSpell::cast(const ESM::Potion* potion)`
I added,
`mSourceType = SourceType::Potion;`,
as the first line

This means that the source type is flagged as potion when the overload passes to the potion function handler

The same was done for,
`bool CastSpell::cast (const ESM::Ingredient* ingredient)`, via
`mSourceType = SourceType::Ingredient;`
and
`bool CastSpell::cast(const ESM::Spell* spell)`, via
`mSourceType = SourceType::Spell;`

In addition for enchanted items handled via,
`bool CastSpell::cast(const MWWorld::Ptr &item, bool launchProjectile)`, I added,
`mSourceType = SourceType::EnchantedItem;`
but for this one it came after

```
        {
            const std::string &refId = item.getCellRef().getRefId();
            auto &store = MWBase::Environment::get().getWorld()->getStore();
            if (auto spell = store.get<ESM::Spell>().search(refId))
                return cast(spell);
        }
```

which I also had to add for bug fixing reasons (due to how spells are actually handled),

so the start of, `bool CastSpell::cast(const MWWorld::Ptr &item, bool launchProjectile)`,
now reads:

```
    bool CastSpell::cast(const MWWorld::Ptr &item, bool launchProjectile)
    {

        {
            const std::string &refId = item.getCellRef().getRefId();
            auto &store = MWBase::Environment::get().getWorld()->getStore();
            if (auto spell = store.get<ESM::Spell>().search(refId))
                return cast(spell);
        }

        mSourceType = SourceType::EnchantedItem;

        std::string enchantmentName = item.getClass().getEnchantment(item);
        (continues base code here...)
```

So with all of that set up, the following occurs,

The basic
`CastSpell::CastSpell(const MWWorld::Ptr &caster, const MWWorld::Ptr &target, const bool fromProjectile, const bool manualSpell)`
begins and sets source type to spell,
then,
`bool CastSpell::cast(const std::string &id)`,
passes to either the potion, ingredient, spell or item & ptr function, where at each it is correctly assigned that source type via my line additions,
(and some bug fixes detailed below),
then the data for source type is automatically made accessible in the inflict function and be used to filter spells by source

**Bug fixes**

Two issues with the above,

1. `bool CastSpell::cast(const MWWorld::Ptr &item, bool launchProjectile)` actually handles both items and spells saved in the game BSA/ESP files (so every spell you can learn which you do not make yourself), so they would otherwise bypass the cast as a spell function and be left with the enchanted item tag

This was fixed by adding the clause I detailed above,

```
        {
            const std::string &refId = item.getCellRef().getRefId();
            auto &store = MWBase::Environment::get().getWorld()->getStore();
            if (auto spell = store.get<ESM::Spell>().search(refId))
                return cast(spell);
        }
```

Which tries to check if the spell being passed to this function is in your spell book, and if so tries to pass to the spell cast as "spell", I can't remember if this became obsolete with the next change but I left it in as I have confirmed no unintended behaviour

Since the route of a spell being cast that was already in the BSA/ESM (and hence not being handled typically by the `spell` casting) somehow things were getting through with  no spell flag assigned at all

This was only an issue at first due to the fact that originally I had declared,
`, mSourceType(SourceType::None)`,
at the top in,
`CastSpell::CastSpell(const MWWorld::Ptr &caster, const MWWorld::Ptr &target, const bool fromProjectile, const bool manualSpell)`

so to fix that I had to update that line to:
`, mSourceType(SourceType::Spell)`

so that it defaults them to go through spell, and the other filters take everything out of that stream and put them into their proper functions

**Testing and confirmation**
- Potions and ingredients are not being affected (even when they allowed into the function implicitly by updating it to capture player casting on themselves), in other words the source type of spell check is correctly filtering them out
- With the updated logic for testing, spells cast on self were affected as intended
- Both custom and base game potions were tested
- All other spell sources were manually re-tested and confirmed working, for each of these items, both player made (custom) and pre-existing (base game) variants were tested and confirmed to follow the logic as intended (no unintended behaviour)
	- On-use items, on-strike effects, scrolls (aka cast once), and actual spells (including powers)

The original issue I found, and had to correct by defaulting the source type to spell rather than none, was that pre-made spells bought from vendors had a chance (unclear if all or just some did) to be passed straight to inflict via the ptr & item function, so they escaped the flag of spell as the source type, and were not being stepped down

### 9.7, Magic damage taken

This is a magic damage amplifier for damage taken by the player (restricted to certain, damaging, effects) that excludes non actor sources of magic (such as traps and scripted effects). It also excludes self targeted effects by the player

In `spellcasting.cpp`, within the `inflict` function,

```
if (target == player && mCaster != player && !caster.isEmpty() && !reflected && caster.getClass().isActor() && (effectholder == 14 || effectholder == 15 || effectholder == 16 || effectholder == 18 || effectholder == 23 || effectholder == 27 || effectholder == 86))
{
    magnitude *= magicdamagetaken();
}
```

the above conditional logic was added, which is linked to the `magicdamagetaken` function in `difficultyscaling.c/hpp`

In `difficultyscaling.cpp`

```
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
```

and in `difficultyscaling.hpp`

```
float magicdamagetaken();
```

**Explanation of above changes**

The `spellcasting.cpp` has a lot of guarding on, to be certain that spell magnitude is only being amplified under specific circumstances:

`if (target == player && mCaster != player` - ensures only the player is affected, and only when the player is not the source of the effect

`&& !caster.isEmpty()` and `&& caster.getClass().isActor() ` - is how non actor sources are filtered out, unless there is an actual entity that cast the spell it won't be modified, so this excludes (confirmed via testing) traps and scripted effects. This was added for traps, but also to proof this clause as strongly as I can against modded content where scripted effects are being used as effect sources (which they rarely are if at all in the base game)

`&& !reflected ` - for the reflect logic, covered in the section below

`&& (effectholder == 14 || effectholder == 15 || effectholder == 16 || effectholder == 18 || effectholder == 23 || effectholder == 27 || effectholder == 86))` - restricts it just to directly damaging effects: fire, frost, shock, poison, absorb health, damage health, drain health

Between the `&& !caster.isEmpty()` and `&& caster.getClass().isActor()` I think the former is now redundant - in testing it did not filter traps (didn't test it with scrips) as even an object springing a trap counted as being a caster, the latter is more watertight and may function on it's own, as it requires the caster is an actor (which excludes objects and the world, only NPCs and creatures fit this category)

Testing confirmed:
- All player self cast "spells" (potions, ingredients, enchantments) are unaffected
- Monsters casting spells on the player are affected
- Traps are not affected
- Constant effect items are not affected
- Damage reflected at you via the reflect effect is not amplified (See the reflect section below)

### 9.8, Accounting for reflected damage

By default all of the changes so far did not account for reflected effects (although some of the code above this may have been documented after reflect corrections were made to it).

The consequence of this in game-play was that:
- Magic effects being reflected onto monsters were not being properly stepped down by tier, and were applying at a flat 1x damage. This would have allowed by-passing the difficulty tier magic damage stepdown if left unchanged
- The player was also taking a flat 1x damage regardless of difficulty tier

I decided not to fix the second point (damage reflected onto the player), and the first point was fixed with the below changes...

**Damage reflected onto the player**
I did not fix this on purpose for balance reasons, but it could be in the same way as the inverse problem was fixed below.

The reasoning was that already in the base game, getting a spell reflected onto you is potentially lethal if you are not prepared for it - spellcasters will typically have lower health (if they are not min-maxing their attributes as they level), and are less likely to pick high endurance starts if they are roleplaying.

That and the base game has a non-linear health vs monster level curve (in practise, nothing in the code, just how the original developers designed creatures) for creatures which in effect means that until mid to high levels, and especially without good endurance, the player has much less health than monsters and relies more on healing, armour and positioning - which is great until you cast a 50 point shock spell and it's reflected onto your 80 health pool at level 10 (if you had 40 endurance from level 1 to 10). 
In other words the base game requires player spell damage output be disproportionally high compared to their own health pools due to the health it gives to monsters beyond the early game.

So for those reasons I intentionally did not correct player damage taken for now, for balance reasons, and it remains a flat 1x when reflected regardless of difficulty tier.

The reason it behaves this way is because of this bit of the if logic for player magic damage taken...

```
target == player && mCaster != player
```

It checks the target is the player (which it is when reflected) and the `mCaster` (essentially the original caster for the purpose of the current, base, overload implementation) is not the player - however in the case of a monster reflection, the `mCaster` is still the player (although the game does update the `caster` variable, which is tracked separately, to the monster as the new local `caster` within the overload loop)

**Damage reflected onto monsters**

This I did fix, as without these fixes it allowed the player to exploit at high difficulty settings by just reflecting monster spells back at them at 1x damage (for the same if statement logic reasons as above), letting the player bypass the intended player magic damage done step-down

The monster magic damage taken was checking (via the three separate functions that track spells, on-hit spells, and on-use together with cast-once sources),

`&& target != player && mCaster == player`
- So it checks the target is not the player via `target != player` (which is fine),
but it was also originally checking,

`mCaster == player`,
- so it was also requiring the original source of the spell effect to be the player, hence it was implicitly excluding all monster originating effects that were being reflected onto monsters - thus escaping out out of the effect magnitude reduction that should otherwise have applied

the fix was to change it to

`target != player && caster == player`
- so that instead it looks for effects locally originating from the player, regardless of the original source, and so now it includes all reflected effects and properly steps them down on high difficulties


### 9.9, Elemental shield damage scaling bug

Elemental shield was, up until V0.40 (pre public release), still operating off of the base game damage scaling function, and so was being scaled as if it were melee damage.

This was changed to bring it in line with all other spell effect difficulty scaling

Original code
```
            // Note swapped victim and attacker, since the attacker takes the damage here.
            x = scaleDamage(x, victim, attacker);
```

Replaced with
```
            MWWorld::Ptr player = MWMechanics::getPlayer();

            if (attacker == player)
            {
                x *= magicdamagetaken();
            }

            if (attacker != player)
            {
                x *= castenchantedDamagescale();
            }

```


## 10, Equipment derived armour ratings

`armor.cpp`

Within `armor.cpp`,

The base game function `getEffectiveArmorRating` (shown below in full),

```
    float Armor::getEffectiveArmorRating(const MWWorld::ConstPtr &ptr, const MWWorld::Ptr &actor) const
    {
        const MWWorld::LiveCellRef<ESM::Armor> *ref = ptr.get<ESM::Armor>();

        int armorSkillType = getEquipmentSkill(ptr);
        float armorSkill = actor.getClass().getSkill(actor, armorSkillType);

        const MWBase::World *world = MWBase::Environment::get().getWorld();
        int iBaseArmorSkill = world->getStore().get<ESM::GameSetting>().find("iBaseArmorSkill")->mValue.getInteger();

        if(ref->mBase->mData.mWeight == 0)
            return ref->mBase->mData.mArmor;
        else
            return ref->mBase->mData.mArmor * armorSkill / static_cast<float>(iBaseArmorSkill);
    }
```

was modified to say...

```
    float Armor::getEffectiveArmorRating(const MWWorld::ConstPtr &ptr, const MWWorld::Ptr &actor) const
    {
        const MWWorld::LiveCellRef<ESM::Armor> *ref = ptr.get<ESM::Armor>();

        MWWorld::Ptr player = MWMechanics::getPlayer();

        int armorSkillType = getEquipmentSkill(ptr);
        float armorSkill = actor.getClass().getSkill(actor, armorSkillType);

        const MWBase::World *world = MWBase::Environment::get().getWorld();
        int iBaseArmorSkill = world->getStore().get<ESM::GameSetting>().find("iBaseArmorSkill")->mValue.getInteger();

        if(ref->mBase->mData.mWeight == 0)
            return ref->mBase->mData.mArmor;

        if (actor == player && armorSkill < 30.0f)
            {
                return (ref->mBase->mData.mArmor * (armorSkill + 5) / (static_cast<float>(iBaseArmorSkill) + 5));
            }

        else
            return ref->mBase->mData.mArmor * armorSkill / static_cast<float>(iBaseArmorSkill);
    }
```

The change was to add the line
`MWWorld::Ptr player = MWMechanics::getPlayer();` to get the player ID,
and to add the if statement logic

```
        if (actor == player && armorSkill < 30.0f)
            {
                return (ref->mBase->mData.mArmor * (armorSkill + 5) / (static_cast<float>(iBaseArmorSkill) + 5));
            }
```

so that only in cases were armour is being calculated for the player, and their skill is below 30, the modified equation of (skill + 5) / (GMST + 5) is used


## 11, Unarmoured 
`npc.cpp`

Within `npc.cpp` the function `getArmorRating` calculates player armour rating locally

The function has a fork in it's logic for if the armour class is being calculated for the player. The below logic fork was inserted into the original function, immediately after it calculates the unarmoured score normally via `ratings[i] = (fUnarmoredBase1 * unarmoredSkill) * (fUnarmoredBase2 * unarmoredSkill);.`

It was done this way for testing. The engine still generates the armour score using the original logic first, and then the if the pointer is the player, then the new logic fork overwrites that value with the new one.

I could also have done a true fork to split the old and new equations, but I structured it in this way (to be overwritten) purely for code testing purposes and have not reverted it. It doesn't matter either way, the effect is the same, that the following code block is what calculates the player's unarmoured score.

The result is:
For skill levels below 30, `AC = Skill/3`
For skill levels 30 to 70,`AC = 10 + ( (Skill - 30) * 1.625 )`
For skill levels above 70`AC = 75 + ( (Skill - 70) * 2.5 )`

x1.25 at 100 agi
x1.25 at 100 speed


```
        MWWorld::Ptr player = MWMechanics::getPlayer();
        ...
        ...
        ...

                if (ptr == player)
                {
                    float playerunarmoured = 0.0f;
                    float unarmouredskillmod = 0.0f;

                    if (unarmoredSkill < 30.0f)
                    {
                        unarmouredskillmod = (unarmoredSkill / 3.0f);
                        playerunarmoured += unarmouredskillmod;
                    }
                    else if (unarmoredSkill < 70.0f)
                    {
                        unarmouredskillmod += 10.0f;
                        unarmouredskillmod += ((unarmoredSkill - 30.0f )*1.625f);
                        playerunarmoured += unarmouredskillmod;
                    }
                    else
                    {
                        unarmouredskillmod += 75.0f;
                        unarmouredskillmod += ((unarmoredSkill - 70.0f)*2.5f);
                        playerunarmoured += unarmouredskillmod;
                    }


                    float playerspeed = stats.getAttribute(ESM::Attribute::Speed).getModified();
                    float playeragility = stats.getAttribute(ESM::Attribute::Agility).getModified();

                    float statmultiplier = 1.0f;

                    if (playerspeed > 50.0f)
                    {
                        float speedholder = 0.0f;
                        speedholder = (playerspeed - 50.0f);
                        speedholder = (speedholder / 200.0f);
                        statmultiplier += speedholder;
                    }

                    if (playeragility > 50.0f)
                    {
                        float agilityholder = 0.0f;
                        agilityholder = (playeragility - 50.0f);
                        agilityholder = (agilityholder / 200.0f);
                        statmultiplier += agilityholder;
                    }

                    playerunarmoured *= statmultiplier;
	                
	            /// this x10 multiplier was added so that the GMST could be left at the base game value of 0.1f
                    playerunarmoured *= 10.0f;

                    playerunarmoured *= fUnarmoredBase1;

                    ratings[i] = playerunarmoured;
                }
            }
```


## 12, Creature armour ratings

`creature.cpp`

(within `creature.cpp`) By default within this file the following logic is used for creature armour ratings

```
    float Creature::getArmorRating (const MWWorld::Ptr& ptr) const
    {
        // Equipment armor rating is deliberately ignored.
        return getCreatureStats(ptr).getMagicEffects().get(ESM::MagicEffect::Shield).getMagnitude();
    }
```

Now it reads

```
    float Creature::getArmorRating (const MWWorld::Ptr& ptr) const
    {
        // Equipment armor rating is deliberately ignored.

        float creaturearmour = 0.0f;
        creaturearmour += 10.0f;
        creaturearmour += getCreatureStats(ptr).getMagicEffects().get(ESM::MagicEffect::Shield).getMagnitude();

        int creaturelevel = getCreatureStats(ptr).getLevel();

        if (creaturelevel >= 5)
        {
            creaturearmour += 2.0f;
        }

        if (creaturelevel >= 10)
        {
            creaturearmour += 3.0f;
        }

        return creaturearmour;
    }
```

The effect is creature armour rating is now 10AC at a minimum for everything, the full logic is now

10 + shield + level boost (which is +2 at level 5+, and +5 at level 10+)

## 13, Armorer

### 13.1, Equipment degradation rates
Changes made to
`npc.cpp`
`combat.cpp`
`difficultyscaling.cpp`
`difficultyscaling.hpp`
#### 13.1.1, Shields
Shields taking damage is governed in `combat.cpp` beginning at line 165

They take damage equal to the damage dealt by the creature (before difficulty and before armour applies, so the base damage in the engine for that creature)

The order of operations within `npc.cpp` that results in the call to `BlockMeleeattack` within `combat.cpp` is,
- Line 778, where the `BlockMeleeattack` function is called
- Line 942, where armour mitigation applies
- Line 1002, where difficulty scaling applies

So this means each hit on a shield will reduce it's durability by the un-mitigated damage done by the attacker. So a 5 damage hit will take exactly 5 off a shield.

The original code governing item health reduction was

```
// Reduce shield durability by incoming damage
int shieldhealth = shield->getClass().getItemHealth(*shield);
shieldhealth -= std::min(shieldhealth, int(damage));
shield->getCellRef().setCharge(shieldhealth);
if (shieldhealth == 0)
    inv.unequipItem(*shield, blocker);
```

and it was changed to this

```
// Reduce shield durability by incoming damage
int shieldhealth = shield->getClass().getItemHealth(*shield);

int damagetoshieldmodded = damage;

MWWorld::Ptr player = getPlayer();

if (blocker == getPlayer())
{
    float armorerSkill = player.getClass().getSkill(player, ESM::Skill::Armorer);
    armorerSkill = std::min(100.0f, armorerSkill);
    armorerSkill = std::max(1.0f, armorerSkill);

    float armorerx = 1.0f - (armorerSkill * 0.0075f);
    
    damagetoshieldmodded *= armourdamagetaken();
    /// new function, covered elsewhere in documentation

    damagetoshieldmodded = static_cast<int>(damagetoshieldmodded * armorerx);
    damagetoshieldmodded = std::max(1, damagetoshieldmodded);
}

shieldhealth -= std::min(shieldhealth, int(damagetoshieldmodded));
shield->getCellRef().setCharge(shieldhealth);
if (shieldhealth == 0)
    inv.unequipItem(*shield, blocker);

```

The changes are that,
- The damage is snapshotted as `damagetoshieldmodded` and if the blocker is not the applier, that is what is subtracted from the shield health at the end (so there is no change for non-player characters)
- Then for the player only...
- Get your armorer skill (modified) but clamp it to 1-100
- Multiply the amount of damage the shield was supposed to take by `1 - (skill * 0.0075`
	- This has the effect that at 100 armorer skill (the max that can be passed to this calculation) your shield takes 0.25x health damage
	- The final damage taken is raised to 1 if the multiplier reduces it to any less


#### 13.1.2, Armour
`npc.cpp`

The function changed was the following block of code, within `void Npc::onHit(const MWWorld::Ptr &ptr, float damage, bool ishealth, const MWWorld::Ptr &object, const MWWorld::Ptr &attacker, const osg::Vec3f &hitPosition, bool successful)` within `npc.cpp`

As with all other changes, it is player only

It just scales down the amount of armour damage taken exactly as it does for shields, -0.75% per skill level with a hard cap of -75% at skill 100


```
                if (hasArmor)
                {
                    if (!object.isEmpty() || attacker.isEmpty() || attacker.getClass().isNpc()) // Unarmed creature attacks don't affect armor condition
                    {
                        int armorhealth = armor.getClass().getItemHealth(armor);

                        int Diffholder = damageDiff;

                        if (ptr == MWMechanics::getPlayer())
                        {
                            MWWorld::Ptr player = MWMechanics::getPlayer();
                            float armorerSkill = player.getClass().getSkill(player, ESM::Skill::Armorer);
                            armorerSkill = std::min(100.0f, armorerSkill);
                            armorerSkill = std::max(1.0f, armorerSkill);

                            float armorerx = 1.0f - (armorerSkill * 0.0075f);
                            
                            Diffholder *= armourdamagetaken(); 
                            /// new function, covered elsewhere in documentation

                            Diffholder = static_cast<int>(Diffholder * armorerx);
                            Diffholder = std::max(1, Diffholder);

                        }

                        armorhealth -= std::min(Diffholder, armorhealth);
                        armor.getCellRef().setCharge(armorhealth);

                        // Armor broken? unequip it
                        if (armorhealth == 0)
                            armor = *inv.unequipItem(armor, ptr);
                    }
```

#### 13.1.3, Weapons
`combat.cpp`
function `reduceWeaponCondition`

Identical degradation reduction logic implemented as for armour and shields, 100-25%

```
    void reduceWeaponCondition(float damage, bool hit, MWWorld::Ptr &weapon, const MWWorld::Ptr &attacker)
    {
        if (weapon.isEmpty())
            return;

        if (!hit)
            damage = 0.f;

        const bool weaphashealth = weapon.getClass().hasItemHealth(weapon);
        if(weaphashealth)
        {
            int weaphealth = weapon.getClass().getItemHealth(weapon);

            bool godmode = attacker == MWMechanics::getPlayer() && MWBase::Environment::get().getWorld()->getGodModeState();

            // weapon condition does not degrade when godmode is on
            if (!godmode)
            {
                const float fWeaponDamageMult = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find("fWeaponDamageMult")->mValue.getFloat();
                float x = std::max(1.f, fWeaponDamageMult * damage);

                MWWorld::Ptr player = MWMechanics::getPlayer();
                if (attacker == player)
                {
                    /// get and clamp armorer skill
                    float armorerSkill = player.getClass().getSkill(player, ESM::Skill::Armorer);
                    armorerSkill = std::min(100.0f, armorerSkill);
                    armorerSkill = std::max(1.0f, armorerSkill);

                    float armorerx = 1.0f - (armorerSkill * 0.0075f);

                    x = (armorerx * x);
                    
	                x *= weapondamagetaken();

                    x = std::max(1.0f, x);

                }

                weaphealth -= std::min(int(x), weaphealth);
                weapon.getCellRef().setCharge(weaphealth);
            }

            // Weapon broken? unequip it
            if (weaphealth == 0)
                weapon = *attacker.getClass().getInventoryStore(attacker).unequipItem(weapon, attacker);
        }
    }
```

#### 13.1.4, Accounting for difficulty
`difficultyscaling.cpp`
`difficultyscaling.hpp`

Since I have previously overhauled the difficulty slider so that player damage dealt can drop as low as 15%, and damage taken (melee) as high as 500%, there is a knock-on effect on item degradation.

The order of operations is that the difficulty setting modifies the melee damage taken/dealt after all item health reductions are processed. On the face of it this means there is no effect, but it in fact introduces two types of unusual behaviour
- Now when you are on high difficulties, and dealing 15% melee damage, your weapon is still degrading as if you had dealt 100% damage (due to the order of operations, with all item health being processed before the difficulty tier steps down the melee damage done)
	- This means that relative to your melee damage done, your weapon ends up taking up to 7 times more durability damage, as it calculated all 7 of those 15% hits as 100% hits
- And the same issue applies in reverse to your armour, where the armour has it's health reduced by the damage mitigated, which is still 1x regardless of difficulty due to the order of operations, and then the player takes up to 5x damage
	- So your armour is taking damage as if you were on normal difficulty, but you are taking 5x damage, meaning you are probably getting hit about 5x less if you aren't past the power threshold. So your armour will on average degrade about 5 times slower

To address this I added some new functions in `difficultyscaling.cpp` which are used to adjust weapon/armour damage taken dependent on difficulty tier.
I decided to do it this way so as to preserve as much of the original order of operations as possible.

Function 1: modifying armour damage taken
```
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
```

Function 2: modifying weapon damage taken
```
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
```

These two registered in `difficultyscaling.hpp` via

```
float armourdamagetaken();

float weapondamagetaken();
```


These were then inserted into the already modified degradation rate equations as such,

```
	if (ptr == MWMechanics::getPlayer())
	{
	    MWWorld::Ptr player = MWMechanics::getPlayer();
	    float armorerSkill = player.getClass().getSkill(player, ESM::Skill::Armorer);
	    armorerSkill = std::min(100.0f, armorerSkill);
	    armorerSkill = std::max(1.0f, armorerSkill);
	
	    float armorerx = 1.0f - (armorerSkill * 0.0075f);
	
		Diffholder *= armourdamagetaken();
	
	    Diffholder = static_cast<int>(Diffholder * armorerx);
	    Diffholder = std::max(1, Diffholder);
	
	}

armorhealth -= std::min(Diffholder, armorhealth);
armor.getCellRef().setCharge(armorhealth);
```

for shields,

```
            if (blocker == getPlayer())
            {
                float armorerSkill = player.getClass().getSkill(player, ESM::Skill::Armorer);
                armorerSkill = std::min(100.0f, armorerSkill);
                armorerSkill = std::max(1.0f, armorerSkill);

                float armorerx = 1.0f - (armorerSkill * 0.0075f);

                damagetoshieldmodded *= armourdamagetaken();

                damagetoshieldmodded = static_cast<int>(damagetoshieldmodded * armorerx);
                damagetoshieldmodded = std::max(1, damagetoshieldmodded);
            }
```

and for weapons,

```
            if (attacker == player)
            {
                /// get and clamp armorer skill
                float armorerSkill = player.getClass().getSkill(player, ESM::Skill::Armorer);
                armorerSkill = std::min(100.0f, armorerSkill);
                armorerSkill = std::max(1.0f, armorerSkill);

                float armorerx = 1.0f - (armorerSkill * 0.0075f);

                x *= weapondamagetaken();

                x = (armorerx * x);

                x = std::max(1.0f, x);

```


### 13.2, Your armorer repair success rate now depends on item value
Header additions to `repair.cpp` and `merchantrepair.cpp`
`repair.cpp`
`merchantrepair.cpp`
#### 13.2.1, General changes
The following header addition was added to both `repair.cpp` and `merchantrepair.cpp`
`#include "../mwworld/inventorystore.hpp"`

This was required to allow these functions to do checks based on equipment slots, which take this form

```
    auto slotPair = itemToRepair.getClass().getEquipmentSlots(itemToRepair);
    const std::vector<int> &slots = slotPair.first;

    if (!slots.empty())
    {
        if (slots[0] == static_cast<int>(MWWorld::InventoryStore::Slot_Helmet))
        {
            x = 0;
        }
    }
```

This is how price/difficulty behaviour differs between weapons and armour, by checking the lot they are in

Weapons are separated from armour using a block like this

```
    if (!slots.empty())
    {
        if (slots[0] == static_cast<int>(MWWorld::InventoryStore::Slot_CarriedRight))
        {
            x = 0;
        }
        else
        {
            x = 100;
        }
    }
```


#### 13.2.2, Assigning item tiers
To make balancing and implementation easier, items have been broken up (within this code block) into 'tiers' which are determined by their price. So that an item in tier 5 can have one difficulty at skill 50, and an item in tier 7 can be much harder at the same skill.

Within `repair.cpp` the 'item price -> tier' logic results in the following tiers by equipment type

| ARMOUR          |          | (includes shields)                                                |
| --------------- | -------- | ----------------------------------------------------------------- |
| **Value range** | **Tier** | **Sample items in tier**                                          |
| 100g or less    | 1        | All basic light armour + the weakest heavy + medium armour        |
| 101 - 499g      | 2        | All common heavy + medium armour                                  |
| 500-1999g       | 3        | Rare medium and some heavy                                        |
| 2000-4999g      | 4        | Rare TR light + rare medium                                       |
| 5000-19,999g    | 5        | Glass, Ebony, Adamantium                                          |
| 20,000 - 49,999 | 6        | Daedric, Mithril, Ebony, Glass                                    |
| 50,000 +        | 7        | Artefacts + Daedric                                               |
|                 |          |                                                                   |
| **WEAPONS**     |          |                                                                   |
| **Value range** | **Tier** | **Sample items in tier**                                          |
| 100g or less    | 1        | Iron up to dwarven, some 2h and some magic items                  |
| 101 - 499g      | 1        | most common material weapons, magic items                         |
| 500-1999g       | 2        | strong magical items, some end-game base materials (orc)          |
| 2000-4999g      | 3.5      | combined T3+T4 difficulty, uniques, cheap ebony, most common weps |
| 5000-19,999g    | 5        | Glass, Ebony, Adamantium, Uniques, Artefacts                      |
| 20,000 - 49,999 | 6        | Daedric, Artefacts, Uniques                                       |
| 50,000 +        | 7        | Artefacts + Daedric                                               |

The tier assigning logic is

```
    int tier = 1;

    if (basePrice <= 100)
    {
        tier = 1;
    }
    if (basePrice > 100)
    {
        tier = 2;
    }
    if (basePrice >= 500)
    {
        tier = 3;
    }
    if (basePrice >= 2000)
    {
        tier = 4;
    }
    if (basePrice >= 5000)
    {
        tier = 5;
    }
    if (basePrice >= 20000)
    {
        tier = 6;
    }
    if (basePrice >= 50000)
    {
        tier = 7;
    }
```

Followed by this block, which processes weapons into lower tiers for balance reasons

```
    if (!slots.empty())
    {
        if (slots[0] == static_cast<int>(MWWorld::InventoryStore::Slot_CarriedRight))
        {

            /// step down of difficulty for all early and mig-game weapons, to help keep skill non-essential
            if (tier == 2)
            {
                tier = 1;
            }
            if (tier == 3)
            {
                tier = 2;
            }
            if (tier == 4)
            {
                tier = 3;
            }
        }
    }
```

To be honest, this was a very messy way to do it, and the entire concept of a tier 3.5 ended up being pretty much pointless. This needs a future clean-up, where I just adjust the initial tier assignment logic for weapons.

#### 13.2.3, Success rate equations
`repair.cpp`
The original code simply did
`float x = (0.1f * pcStrength + 0.1f * pcLuck + armorerSkill) * fatigueTerm;`

This section covers how this was changed to a tiered system, where each tier of item has it's own difficulty calculated.

First of all, since the later changes here involved calculating their new difficulties using curved line equations, I put a hard cap on x via some clamping. This was done to avoid any unusual math behaviour when otherwise very large x values are squared (because it's morrowind, getting 10,000 strength is not hard).

That clamping was just

```
    float basepercent = (0.1f * pcStrength + 0.1f * pcLuck + armorerSkill) * fatigueTerm;

    if (basepercent > 500.0f)
    {
        basepercent = 500.0f;
    }
```

note that x has become `basepercent`, which will be modified in the new equations

The idea was to get a value for x that was somewhat simplified, and then to feed it into curved line equations to produce something like sinusoidal difficulty curves.

To simplify what x is a little, the `fatigueTerm` was modified slightly, via the block
```
    /// adjust down fatigue term as part of this balance pass
    fatigueTerm -= 0.25f;


    /// calculate base percent
    float basepercent = (0.1f * pcStrength + 0.1f * pcLuck + armorerSkill) * fatigueTerm;
```

The idea is that now at full fatigue the `fatigueTerm` has a 1x modifier, and drops down to a 0.5x when you have no fatigue remaining
This was done because there is no reason you would not wait to get fatigue back if repairing, since you cannot do it in combat, so it seemed pointless adding a 1.25x modifier to the whole skill in practise - and having the 1.25x modifier complicated how x is calculated from skill and attributes for testing purposes

The individual difficulty modifiers by tier take the form shown below, note that all of the tiers have a floor success %. 

```
    float basepercent = (0.1f * pcStrength + 0.1f * pcLuck + armorerSkill) * fatigueTerm;


    if (tier == 1)
    {
        x = ((0.0136f * basepercent * basepercent) + (0.59f * basepercent) - 6.75f);
        if (x < 20.0f)
        {
            x = 20.0f;
        }
    }
```

There is one per tier, and the equations which govern them are,

```
    if (tier == 1)
    {
        x = ((0.0136f * basepercent * basepercent) + (0.59f * basepercent) - 6.75f);
        if (x < 20.0f)
        {
            x = 20.0f;
        }
    }

    if (tier == 2)
    {
        x = ((0.0128f * basepercent * basepercent) + (0.399f * basepercent) - 4.89f);
        if (x < 17.0f)
        {
            x = 17.0f;
        }
    }

    if (tier == 3)
    {
        if (slots[0] == static_cast<int>(MWWorld::InventoryStore::Slot_CarriedRight))
        {
            /// the tier 3.5 version, whcih is slightly harder than 3 but still easier than the 4 weapons would otherwise be
            x = ((0.0051f * basepercent * basepercent) + (1.121f * basepercent) - 39.15f);
            if (x < 15.0f)
            {
                x = 15.0f;
            }
        }

        else
        {
            x = ((0.0033f * basepercent * basepercent) + (1.342f * basepercent) - 30.0f);
            if (x < 15.0f)
            {
                x = 15.0f;
            }
        }
    }

    if (tier == 4)
    {
        x = ((0.0035f * basepercent * basepercent) + (1.21f * basepercent) - 36.34f);
        if (x < 15.0f)
        {
            x = 15.0f;
        }
    }

    if (tier == 5)
    {
        x = ((0.0114f * basepercent * basepercent) + (0.23f * basepercent) - 27.64f);
        if (x < 15.0f)
        {
            x = 15.0f;
        }
    }

    if (tier == 6)
    {
        x = ((0.0072f * basepercent * basepercent) + (0.51f * basepercent) - 41.4f);
        if (x < 15.0f)
        {
            x = 15.0f;
        }
    }

    if (tier == 7)
    {
        x = ((0.014f * basepercent * basepercent) - (0.552f * basepercent) - 14.63f);
        if (x < 15.0f)
        {
            x = 15.0f;
        }
    }
```

### 13.3, Armorer's tools now modify success rate
`repair.cpp`
This was done within `repair.cpp` as well, modifying the same block as was done above.

See the code block below, the relevant bit is the tool quality adjustment logic. I have shown the surrounding code to show the order of operations.

```

    /// adjust down fatigue term as part of this balance pass
    fatigueTerm -= 0.25f;


    /// calculate base percent
    float basepercent = (0.1f * pcStrength + 0.1f * pcLuck + armorerSkill) * fatigueTerm;


    /// new tool quality adjustments

    if (toolQuality > 1.0f)
    {
        float qualitymod = (toolQuality - 1.0f);
        qualitymod *= 10.0f;
        qualitymod *= 2.00f;
        basepercent += qualitymod;
    }


    /// a hard cap, some guarding to avoid silly numbers appearing in nonlinear squaring equations
    /// this does impose an arbitrarily high but final cap on success rate, as values of x beyond 100 do help

    if (basepercent > 500.0f)
    {
        basepercent = 500.0f;
    }


    if (tier == 1)
    {
        x = ((0.0136f * basepercent * basepercent) + (0.59f * basepercent) - 6.75f);
        if (x < 20.0f)
        {
            x = 20.0f;
        }
    }
```



### 13.4, Armour repair costs
`merchantrepair.cpp`
The core repair code now reads

```
        if (iter->getClass().hasItemHealth(*iter))
        {
            int maxDurability = iter->getClass().getItemMaxHealth(*iter);
            int durability = iter->getClass().getItemHealth(*iter);
            if (maxDurability == durability || maxDurability == 0)
                continue;

            int basePrice = iter->getClass().getValue(*iter);
            float fRepairMult = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>()
                    .find("fRepairMult")->mValue.getFloat();

            float p = static_cast<float>(std::max(1, basePrice));
            float r = static_cast<float>(maxDurability / p);

            r = std::max(0.1f, r);

            int x = static_cast<int>((maxDurability - durability) / r);
            x = static_cast<int>(fRepairMult * x * 0.333f);
            x = std::max(1, x);

            int price = MWBase::Environment::get().getMechanicsManager()->getBarterOffer(mActor, x, true);
```

The difference from the original code is that r is no longer set to 1 via `std::max`

Since the line for r was originally

```
float r = static_cast<float>(std::max(1, static_cast<int>(maxDurability / p)));
```

The effect was that r would never be less than 1, due to the `std::max` operation, and only r values less than 1 increase the price past 1gp per item health, since the cost is later calculated as health restored / r.

Now r cannot be less than 0.1, which equates to the player not being charged more than 10gp per point of item health before the 0.333x multiplier reduction applies.

By making this change, items now cost a % of their value equal to the % of their health being restored.

In addition the line
`x = static_cast<int>(fRepairMult * x * 0.333f);`
had the 0.333f multiplier added, so that final cost to repair an item fully is 33% of the item's full value

This was done to make the prices more reasonable for testing, and for the first version, but the player can adjust `fRepairMult` at an ESP level, so further in game changes can be made on the fly, to taste.



## 14, Swimming
`npc.cpp`

This change boosts how much the players athletics skill increases their swim speed (expressed as a % of their land running speed).

The player athletics now increases their swimming speed by 0.3% a level, up from 0.1% a level in the base game.  

This results in the player going from 50-80% swim speed from 1-100 athletics, vs 50-60% in the base game.

This is restricted to the player only via an if player is ptr check, and replacing a hardcoded value with a local variable in the function.

There is a hard cap to how much athletics can contribute to swim speed. At level 166 athletics you reach 100% of your land running speed, and there is no further benefit to increasing the athletics skill beyond this point.

The function `getSwimSpeed`,

```
    float Npc::getSwimSpeed(const MWWorld::Ptr& ptr) const
    {
        const GMST& gmst = getGmst();
        const MWBase::World* world = MWBase::Environment::get().getWorld();
        const MWMechanics::CreatureStats& stats = getCreatureStats(ptr);
        const NpcCustomData* npcdata = static_cast<const NpcCustomData*>(ptr.getRefData().getCustomData());
        const MWMechanics::MagicEffects& mageffects = npcdata->mNpcStats.getMagicEffects();
        const bool swimming = world->isSwimming(ptr);
        const bool inair = !world->isOnGround(ptr) && !swimming && !world->isFlying(ptr);
        const bool running = stats.getStance(MWMechanics::CreatureStats::Stance_Run)
                && (inair || MWBase::Environment::get().getMechanicsManager()->isRunning(ptr));

        float swimSpeed;

        if (running)
            swimSpeed = getRunSpeed(ptr);
        else
            swimSpeed = getWalkSpeed(ptr);

        swimSpeed *= 1.0f + 0.01f * mageffects.get(ESM::MagicEffect::SwiftSwim).getMagnitude();
        swimSpeed *= gmst.fSwimRunBase->mValue.getFloat()
                + 0.01f * getSkill(ptr, ESM::Skill::Athletics) * gmst.fSwimRunAthleticsMult->mValue.getFloat();

        return swimSpeed;
    }
```

was updated to the following

```
    float Npc::getSwimSpeed(const MWWorld::Ptr& ptr) const
    {
        const GMST& gmst = getGmst();
        const MWBase::World* world = MWBase::Environment::get().getWorld();
        const MWMechanics::CreatureStats& stats = getCreatureStats(ptr);
        const NpcCustomData* npcdata = static_cast<const NpcCustomData*>(ptr.getRefData().getCustomData());
        const MWMechanics::MagicEffects& mageffects = npcdata->mNpcStats.getMagicEffects();
        const bool swimming = world->isSwimming(ptr);
        const bool inair = !world->isOnGround(ptr) && !swimming && !world->isFlying(ptr);
        const bool running = stats.getStance(MWMechanics::CreatureStats::Stance_Run)
                && (inair || MWBase::Environment::get().getMechanicsManager()->isRunning(ptr));

        float swimSpeed;

        if (running)
            swimSpeed = getRunSpeed(ptr);
        else
            swimSpeed = getWalkSpeed(ptr);

        MWWorld::Ptr player = MWMechanics::getPlayer();

        float athleticsswimmod = 0.01f;

        float athleticsholder = getSkill(ptr, ESM::Skill::Athletics);

        if (ptr == player)
        {
            athleticsswimmod = 0.03f;
            if (athleticsholder > 166.0f)
            {
                athleticsholder = 166.0f;
            }
        }

        swimSpeed *= 1.0f + 0.01f * mageffects.get(ESM::MagicEffect::SwiftSwim).getMagnitude();
        swimSpeed *= gmst.fSwimRunBase->mValue.getFloat()
                + athleticsswimmod * athleticsholder * gmst.fSwimRunAthleticsMult->mValue.getFloat();

        return swimSpeed;
    }
```

This change
- Respects all GMSTs
- Caps skill contribution to swimming only
- Only affects the player

## 16, Mercantile
`mechanicsmanagerimp.cpp`
`tradewindow.cpp`
`trading.cpp`

To facilitate the changes listed in the mechanics changelog, the following changes were made at an engine level

### 16.2.1, Mercantile disposition has reduced effect on bartering
`mechanicsmanagerimp.cpp`

In the base game every points of disposition above or below 50 adds or removes 1 mercantile skill. This means that by bribing an NPC up to 100 disposition you effectively gain 50 mercantile skill, which reduces the value of levelling the actual skill quite a lot.

Disposition is processed via `getDerivedDisposition`. Exactly what it does is not relevant here, but that function is where things like disease, whether the player is holding a weapon, and faction bonuses, apply to your disposition.

Disposition has been reduced in importance by adjusting the base game function to include

```
float dispositionmodified = ((clampedDisposition - 50) * 0.25f);
float pcTerm = (dispositionmodified + a + b + c) * playerStats.getFatigueTerm();
```

whereas before it said

```
float pcTerm = (clampedDisposition - 50 + a + b + c) * playerStats.getFatigueTerm();
```

The result is that now every 4 points of disposition above or below 50 adds or removes 1 effective mercantile skill, and the highest effective boost you can get at 100 disposition is + 12.5 mercantile levels.


### 16.2.2, Mercantile disposition has reduced effect on haggling

Not actually a compiling level change, but listed here as it complements the engine level change made above. At an ESP level the GMST `fDispositionMod` governs the extent to which disposition affects haggling, it is 1.0 by default and was adjusted to 0.25 so that 4 points of disposition above or below 50 add or remove 1 effective mercantile level. Now as with bartering, the maximum benefit you can get from 100 disposition is +12.5 effective mercantile levels.


### 16.2.3, Adjustments to min and max buy/sell rates
`tradewindow.cpp`

To fix a loophole where with sufficient mercantile and haggling (quite easy to reach actually in the old system due to disposition) you could make infinite money buying and reselling items, the buying/selling rate caps were adjusted, and floors were put in as well.

In the base engine both buying and selling have a cap of 75%, which in theory is breaking even but allows haggling to exceed this limit trivially.

So to fix this,
in `tradewindow.cpp`, within the function `void TradeWindow::updateOffer()`,
the clamps on max buy and sell prices have been set to 90% and 60% respectively, so now you can never 'break even' when re-buying (which is necessary to allow room for haggling to be useful, without exceeding the break even ratio of 1:1 buy/sell)

In addition, within the same function in this file

- I added a floor to the maximum value you can be charged for something (150%)
- I added a floor to the minimum value you can sell something for (20%)

These two additions mean that no matter your skill, and no matter the merchant, you can still functionally trade with them (this is to guard against the removal of disposition boosts being available, as you are far more likely now to actually run into situations where you struggle to sell things for any reasonable price, if you rely on charming over your mercantile skill)

Note: these are local changes to item selling and buying, since this change is hosted within `tradewindow.cpp`, as a result all other service charges remain uncapped and be reduced much more than to 90%, if you have a high enough mercantile skill

### 16.2.4, Setting a hard limit on haggling of 10%
`trading.cpp`

To go with the change above which hard caps the barter rates, a hard limit has been placed on haggling rates (although this is not an ideal solution, and is likely to be revised in future versions).

Within `trading.cpp`, within the `bool Trading::haggle` function,

this clause has been added to it

```
        float ratio = std::abs(float(playerOffer)) / std::abs(float(merchantOffer));
        if (ratio < 0.9f || ratio > 1.1f)
        {
            x = 0.0f;
        }
```

This gets the ratio between what the player wants and what the merchant wants. If the amount exceeds 110% or is below 90%, then it sets x to 0 (you cannot succeed). 

This way you can still haggle past this point for one off purchases, but you cannot sell or buy anything that has been haggled past 10% of the original offer value. Combined with the previous buy cap of 90% (in the buy rate fix above) and the sell cap of 60%, this means at the absolute best you can haggle to a 80% buy and 70% sell rate, which prevents breaking even and circulating items infinitely for free XP (in the new XP gain system, covered below).

This is a very aggressive and crude fix, and will likely be replaced with something more nuanced in a later version, but for now it serves it's purpose without introducing any bugs.

### 16.2.5, XP gain overhaul

#### Generic XP gain functions

The generic XP gain function is

```
    void Npc::skillUsageSucceeded (const MWWorld::Ptr& ptr, int skill, int usageType, float extraFactor) const
    {
        MWMechanics::NpcStats& stats = getNpcStats (ptr);

        if (stats.isWerewolf())
            return;

        MWWorld::LiveCellRef<ESM::NPC> *ref = ptr.get<ESM::NPC>();

        const ESM::Class *class_ =
            MWBase::Environment::get().getWorld()->getStore().get<ESM::Class>().find (
                ref->mBase->mClass
            );

        stats.useSkill (skill, *class_, usageType, extraFactor);
    }
```

and it calls out to `useSkill` in `npcstats.cpp`

I have already modified this function previously to implement the XP curve, but you can see it begins with

```
void MWMechanics::NpcStats::useSkill (int skillIndex, const ESM::Class& class_, int usageType, float extraFactor)
{
    const ESM::Skill *skill =
        MWBase::Environment::get().getWorld()->getStore().get<ESM::Skill>().find (skillIndex);
    float skillGain = 1;
    float base = getSkill(skillIndex).getBase();
    if (usageType>=4)
        throw std::runtime_error ("skill usage type out of range");
    if (usageType>=0)
    {
        skillGain = skill->mData.mUseValue[usageType];
        if (skillGain<0)
            throw std::runtime_error ("invalid skill gain factor");
    }
    skillGain *= extraFactor;

```

So that the `extraFactor` which can optionally be passed at the point of skill gain acts as a multiplier to the final value.

So an `extraFactor` of exactly 1.0 means you gain the stated XP in the creation it ESP file, values above or below 1 multiply the XP up or down accordingly. Having an `extraFactor` is optional, you can call the function without it, and in that case it defaults to 1

#### Remove haggling based XP gain
`trading.cpp`

In `trading.cpp`, within the `haggle` function, the following code block was removed completely, so that you no longer gain XP from haggling

```
        // apply skill gain on successful barter
        float skillGain = 0.f;
        int finalPrice = std::abs(playerOffer);
        int initialMerchantOffer = std::abs(merchantOffer);

        if ( !buying && (finalPrice > initialMerchantOffer) ) {
            skillGain = floor(100.f * (finalPrice - initialMerchantOffer) / finalPrice);
        }
        else if ( buying && (finalPrice < initialMerchantOffer) ) {
            skillGain = floor(100.f * (initialMerchantOffer - finalPrice) / initialMerchantOffer);
        }
        player.getClass().skillUsageSucceeded(player, ESM::Skill::Mercantile, 0, skillGain);
```

#### Full new XP gain system
`tradewindow.cpp`

Experience gain from haggling has been removed, now XP is gained from the value of items sold.

Within `tradewindow.cpp` the `onOfferButtonClicked` function was updated extensively.

**The final function additions are:**

[1] Snapshot the amount of gold being transferred, if it is positive (meaning if it is towards the player). This is used in part [2]. This addition was done right before the sub-function tagged with `// transfer the gold`.

[1] snapshot of gold being transferred
```
        ///snapshot the gold you recieve, if any, for DC XP calculations further down
        int goldRecieved = 0;
        if (mCurrentBalance > 0)
        {
            goldRecieved = mCurrentBalance;
        }
```

[2] The main XP assigning function

```
        /// DC system for calcualting XP gained from sales

        int sumBaseSold = 0;
        int sumBasePurchased = 0;

        if (!merchantBought.empty())
        {
            ///sum the base gold value of all items you are selling
            for (const ItemStack& stack : merchantBought)
            {
                MWWorld::Ptr objectPtr = stack.mBase;
                int singleValue = objectPtr.getClass().getValue(objectPtr);

                for (int i = 0; i < stack.mCount; ++i)
                {
                    if (singleValue > 0)
                    {
                        sumBaseSold += singleValue;
                    }
                }
            }

            ///sum the base gold value of all items you are recieving
            if (!playerBought.empty())
            {
                for (const ItemStack& stack : playerBought)
                {
                    MWWorld::Ptr objectPtr = stack.mBase;
                    int singleValue = objectPtr.getClass().getValue(objectPtr);

                    for (int i = 0; i < stack.mCount; ++i)
                    {
                        if (singleValue > 0)
                        {
                            sumBasePurchased += singleValue;
                        }
                    }
                }

            }

        }

        MWWorld::Ptr playerPtr = MWBase::Environment::get().getWorld()->getPlayerPtr();

        /// calculate the barter value of everything you sold
        const int barterItemsSold = MWBase::Environment::get().getMechanicsManager()->getBarterOffer(playerPtr, sumBaseSold, false);

        ///calculate the barter value of everything you purchased
        const int barterItemsPurchased = MWBase::Environment::get().getMechanicsManager()->getBarterOffer(playerPtr, sumBasePurchased, true);

        ///sum the gold you recieved and the barter value of the items you recieved
        int totalValuePurchased = (barterItemsPurchased + goldRecieved);

        ///cap the total value of what you have gained to be no more than the barter value of what you sold
        totalValuePurchased = std::min(barterItemsSold, totalValuePurchased);

        ///calculate the ratio of what your items were worth in this transaction to what you got
        float xpMultiplier = 1.0f;
        if (barterItemsSold > 0)
        {
            xpMultiplier = ((float)totalValuePurchased / (float)barterItemsSold);
        }

        /// use the barter value of items sold to determine XP gain
        float xpAwardIncrements = 0.0f;
        if (barterItemsSold > 0)
        {
            xpAwardIncrements = (float(barterItemsSold) / 50.0f);
        }

        ///apply the multiplier for potentially underselling items
        xpAwardIncrements *= xpMultiplier;

        ///award experience if items were sold for a non zero value
        if (barterItemsSold > 0)
        {
            if (xpAwardIncrements > 0.0f)
            {
                player.getClass().skillUsageSucceeded(player, ESM::Skill::Mercantile, 0, xpAwardIncrements);
            }
        }


        /// end of DC xp gain system
```

How this works,
1. Snapshot the total value of gold being exchanged, and save it if it is a positive amount (which means in the engine that it is an amount being transferred to the player from an NPC)
2. If the player is selling something, get the sum base value of all items being sold
3. If in the same transaction the player is buying something (so a partial exchange for gold and items), get the sum base value of all items being received
4. Calculate the 'barter value' of all items being sold (the initial value they are offered at via the `getbarteroffer` function)
5. Calculate the 'barter value' of all items being bought in the same transaction (the initial value they are offered at via the `getbarteroffer` function)
6. Calculate the sum value of everything you received, in gold and barter value of items, but cap that sum value at no more than the barter value of what you sold.
	1. This cap is needed otherwise you can sell an item for 100g, buy 10,000g worth of items, and without this cap end up getting XP for 'selling' 10,000g worth of items
7. Calculate the ratio of the barter value of your items sold, to the value of what you got from the transaction (using the cap set in step 6)
8. Calculate the amount of XP you will be awarded, in increments of 0.3xp, based on the amount of barter value you sold. In the version this is 50gp per 0.3xp, or about 166.7gp per XP
9. Apply a potential step down multiplier to that XP amount used the ratio calculated in step 7. This means that if you intentionally undersell items to get rid of them, you will get proportionally less XP (as that is not something that a good merchant would do!)
10. Award XP, using the value calculated in step 9 as the extra factor

The end result is that
- You get XP based on the value of items you sell
- You get less XP if you intentionally undersell
- Items received in kind are accounted for, and count towards you receiving full payment
- Buying things intentionally does not give XP


## 17, NPC spellcasting locked to base game spell effect costs

`spellutil.cpp`
`spellutil.hpp`
`autocalcspell.cpp`
`autocalcspell.hpp`
`spellpriority.cpp`

An exhaustive search was done in the engine for all direct and indirect references to spell effect costs made by NPCs. Three areas were found and adjusted so that NPCs used new hard-coded base game spell effect cost values.

### 17.1, Locking `calcSpellBaseSuccessChance()`
`spellutil.cpp`

The function `calcSpellBaseSuccessChance()` iterates over the weakest school of magic in a spell that the player or an NPC is casting to determine which spell school is the least effective at casting a multi-school spell. It does by using live ESP values for spell effect costs, whereas actual spell cost is locked at the point of spell creation.

Original function

```
    float calcSpellBaseSuccessChance (const ESM::Spell* spell, const MWWorld::Ptr& actor, int* effectiveSchool)
    {
        // Morrowind for some reason uses a formula slightly different from magicka cost calculation
        float y = std::numeric_limits<float>::max();
        float lowestSkill = 0;

        for (const ESM::ENAMstruct& effect : spell->mEffects.mList)
        {
            float x = static_cast<float>(effect.mDuration);
            const auto magicEffect = MWBase::Environment::get().getWorld()->getStore().get<ESM::MagicEffect>().find(effect.mEffectID);

            if (!(magicEffect->mData.mFlags & ESM::MagicEffect::AppliedOnce))
                x = std::max(1.f, x);

            x *= 0.1f * magicEffect->mData.mBaseCost;
            x *= 0.5f * (effect.mMagnMin + effect.mMagnMax);
            x += effect.mArea * 0.05f * magicEffect->mData.mBaseCost;
            if (effect.mRange == ESM::RT_Target)
                x *= 1.5f;
            static const float fEffectCostMult = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find(
                        "fEffectCostMult")->mValue.getFloat();
            x *= fEffectCostMult;

            float s = 2.0f * actor.getClass().getSkill(actor, spellSchoolToSkill(magicEffect->mData.mSchool));
            if (s - x < y)
            {
                y = s - x;
                if (effectiveSchool)
                    *effectiveSchool = magicEffect->mData.mSchool;
                lowestSkill = s;
            }
        }

        CreatureStats& stats = actor.getClass().getCreatureStats(actor);

        float actorWillpower = stats.getAttribute(ESM::Attribute::Willpower).getModified();
        float actorLuck = stats.getAttribute(ESM::Attribute::Luck).getModified();

        float castChance = (lowestSkill - spell->mData.mCost + 0.2f * actorWillpower + 0.1f * actorLuck);

        return castChance;
    }
```

Updated function

```
    float calcSpellBaseSuccessChance (const ESM::Spell* spell, const MWWorld::Ptr& actor, int* effectiveSchool)
    {
        // Morrowind for some reason uses a formula slightly different from magicka cost calculation
        float y = std::numeric_limits<float>::max();
        float lowestSkill = 0;
        MWWorld::Ptr player = MWMechanics::getPlayer();

        for (const ESM::ENAMstruct& effect : spell->mEffects.mList)
        {
            float x = static_cast<float>(effect.mDuration);
            const auto magicEffect = MWBase::Environment::get().getWorld()->getStore().get<ESM::MagicEffect>().find(effect.mEffectID);

            if (!(magicEffect->mData.mFlags & ESM::MagicEffect::AppliedOnce))
                x = std::max(1.f, x);

            float effectCost = 1.0f;

            if (actor != player)
            {
                // NPC logic forks into the getBaseGameEffectCost function which manually defines all base game effect values
                effectCost = getBaseGameEffectCost(effect.mEffectID);
            }
            else
            {
                effectCost = magicEffect->mData.mBaseCost;
            }
            
            x *= 0.1f * effectCost;
            x *= 0.5f * (effect.mMagnMin + effect.mMagnMax);
            x += effect.mArea * 0.05f * effectCost;
            if (effect.mRange == ESM::RT_Target)
                x *= 1.5f;
            static const float fEffectCostMult = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find(
                        "fEffectCostMult")->mValue.getFloat();
            x *= fEffectCostMult;

            float s = 2.0f * actor.getClass().getSkill(actor, spellSchoolToSkill(magicEffect->mData.mSchool));
            if (s - x < y)
            {
                y = s - x;
                if (effectiveSchool)
                    *effectiveSchool = magicEffect->mData.mSchool;
                lowestSkill = s;
            }
        }

        CreatureStats& stats = actor.getClass().getCreatureStats(actor);

        float actorWillpower = stats.getAttribute(ESM::Attribute::Willpower).getModified();
        float actorLuck = stats.getAttribute(ESM::Attribute::Luck).getModified();

        float castChance = (lowestSkill - spell->mData.mCost + 0.2f * actorWillpower + 0.1f * actorLuck);

        return castChance;
    }
```

Changes
- The new function checks if it is running for the player or not for the player. For the player only now, it gets the ESP spell effect costs.
- For non players, it now calls out to the new function (discussed below) `getBaseGameEffectCost`

This only affects NPC spell selection priority, via their casting chances, and this change now means that NPCs operate independently of ESP level magic effect changes. This has the consequence that NPCs are now only compatible with base game magic effect costs, **so any modded content that changes ESP level magic effect costs, give those spells to NPCs and expects them to cast them will have balance issues.**
- This is an intentional design choice, as it is the easiest solution to fix this issue and to ensure full TR compatibility.

### 17.2, New hardcoded function, `getBaseGameEffectCost`
`spellutil.cpp`
`spellutil.hpp`

To facilitate the changes above, and the ones below in this section, a simple switch function was made for all base game spell effects.

This was added to `spellutil.cpp`, and the header file `spellutil.hpp` was updated with this line to initialise it,
`float getBaseGameEffectCost(int effectID);`

In `spellutil.cpp` the function was added as follows (this is an abbreviated version, the full function lists every spell effect with it's corresponding base game value)

```
    float getBaseGameEffectCost(int effectID)
    {
        switch (effectID)
        {
        case ESM::MagicEffect::WaterBreathing:           return 3.0f;
        case ESM::MagicEffect::SwiftSwim:                return 2.0f;
        case ESM::MagicEffect::WaterWalking:             return 3.0f;
        case ESM::MagicEffect::Shield:                   return 2.0f;
        case ESM::MagicEffect::FireShield:               return 3.0f;
        case ESM::MagicEffect::LightningShield:          return 3.0f;
        ... etc... [omitted for brevity]
        
        default:
            return 1.0f;
        }
    }
```

- It is a simple switch function
- If it fails to return anything (which should never happen, but to stop crashing just in case) it defaults to an effect cost of 1.0f


### 17.3, Locking `calcWeakestSchool()`
`autocalcspell.cpp`
`autocalcspell.hpp`

This is the most complicated change in this section. Since `calcWeakestSchool()` does not carry actor information, and for various reasons it would be not suitable to add it, instead I have added a Boolean flag to the surrounding functions to distinguish calls made by the player and calls made by NPCs.

Firstly the function `calcWeakestSchool()` was modified to carry a Boolean `useNpcCost` which is set to false by default.

The header file `autocalcspell.hpp` was updated so that `calcWeakestSchool()` is now defined like this,

```
void calcWeakestSchool(const ESM::Spell* spell, const int* actorSkills, int& effectiveSchool, float& skillTerm, bool useNpcCost = false);
```

and `autocalcspell.cpp` was updated to reflect that as follows

```
    void calcWeakestSchool (const ESM::Spell* spell, const int* actorSkills, int& effectiveSchool, float& skillTerm, bool useNpcCost)
    {
    ... [rest of function goes here]
```

Within `calcWeakestSchool()` there is a new logic fork which checks

```
            if (useNpcCost == false)
            {
                // Player behaviour, use live ESP mBaseCost values
                effectCost = magicEffect->mData.mBaseCost;
            }
            else
            {
                // NPC fork, use hardcoded base game values as per this function
                effectCost = getBaseGameEffectCost(effect.mEffectID);
            }
```

So if the flag is false, i.e. the function `calcWeakestSchool()` has not been called by an NPC, it retains the base game behaviour.

If the flag is true, i.e. when called by an NPC, then it calls out to `getBaseGameEffectCost()` as defined and used in the section above in this documentation.

Due to how the functions relate to each other, it was also necessary to update `calcAutoCastChance` to hold the same Boolean via header and main file changes as follows,

Header
```
float calcAutoCastChance(const ESM::Spell* spell, const int* actorSkills, const int* actorAttributes, int effectiveSchool, bool useNpcCost = false);
```

Main file
```
    float calcAutoCastChance(const ESM::Spell *spell, const int *actorSkills, const int *actorAttributes, int effectiveSchool, bool useNpcCost)
    {
    ... [rest of function goes here]
```

This is necessary as the function `calcWeakestSchool` can be called directly, or indirectly via `calcAutoCastChance`, so this function too needed updating to be able to hold the Boolean flag

Within `calcAutoCastChance` this line is modified to

```
        else
            calcWeakestSchool(spell, actorSkills, effectiveSchool, skillTerm, useNpcCost); // Note effectiveSchool is unused after this
```

so that when `calcAutoCastChance` calls `calcWeakestSchool`, it is passing it's Boolean flag which is false by default

Within `autoCalcNPCspells` the calls to those two functions are modified to pass true, as follows

```
            calcWeakestSchool(&spell, actorSkills, school, skillTerm, true);

			...

            if (calcAutoCastChance(&spell, actorSkills, actorAttributes, school, true) < fAutoSpellChance)
                continue;
```

Original function

```
    void calcWeakestSchool (const ESM::Spell* spell, const int* actorSkills, int& effectiveSchool, float& skillTerm, bool useNpcCost)
    {
        // Morrowind for some reason uses a formula slightly different from magicka cost calculation
        float minChance = std::numeric_limits<float>::max();
        for (const ESM::ENAMstruct& effect : spell->mEffects.mList)
        {
            const ESM::MagicEffect* magicEffect = MWBase::Environment::get().getWorld()->getStore().get<ESM::MagicEffect>().find(effect.mEffectID);

            int minMagn = 1;
            int maxMagn = 1;
            if (!(magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude))
            {
                minMagn = effect.mMagnMin;
                maxMagn = effect.mMagnMax;
            }

            int duration = 0;
            if (!(magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration))
                duration = effect.mDuration;
            if (!(magicEffect->mData.mFlags & ESM::MagicEffect::AppliedOnce))
                duration = std::max(1, duration);

            static const float fEffectCostMult = MWBase::Environment::get().getWorld()->getStore()
                .get<ESM::GameSetting>().find("fEffectCostMult")->mValue.getFloat();

            float x = 0.5 * (std::max(1, minMagn) + std::max(1, maxMagn));
            x *= 0.1 * magicEffect->mData.mBaseCost;
            x *= 1 + duration;
            x += 0.05 * std::max(1, effect.mArea) * magicEffect->mData.mBaseCost;
            x *= fEffectCostMult;

            if (effect.mRange == ESM::RT_Target)
                x *= 1.5f;

            float s = 2.f * actorSkills[spellSchoolToSkill(magicEffect->mData.mSchool)];
            if (s - x < minChance)
            {
                minChance = s - x;
                effectiveSchool = magicEffect->mData.mSchool;
                skillTerm = s;
            }
        }
    }
```


becomes

```
    void calcWeakestSchool (const ESM::Spell* spell, const int* actorSkills, int& effectiveSchool, float& skillTerm, bool useNpcCost)
    {
        // Morrowind for some reason uses a formula slightly different from magicka cost calculation
        float minChance = std::numeric_limits<float>::max();
        
        for (const ESM::ENAMstruct& effect : spell->mEffects.mList)
        {
            const ESM::MagicEffect* magicEffect = MWBase::Environment::get().getWorld()->getStore().get<ESM::MagicEffect>().find(effect.mEffectID);

            float effectCost = 1.0f;

            if (useNpcCost == false)
            {
                // Player behaviour, use live ESP mBaseCost values
                effectCost = magicEffect->mData.mBaseCost;
            }
            else
            {
                // NPC fork, use hardcoded base game values as per this function
                effectCost = getBaseGameEffectCost(effect.mEffectID);
            }


            int minMagn = 1;
            int maxMagn = 1;
            if (!(magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude))
            {
                minMagn = effect.mMagnMin;
                maxMagn = effect.mMagnMax;
            }

            int duration = 0;
            if (!(magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration))
                duration = effect.mDuration;
            if (!(magicEffect->mData.mFlags & ESM::MagicEffect::AppliedOnce))
                duration = std::max(1, duration);

            static const float fEffectCostMult = MWBase::Environment::get().getWorld()->getStore()
                .get<ESM::GameSetting>().find("fEffectCostMult")->mValue.getFloat();

            float x = 0.5 * (std::max(1, minMagn) + std::max(1, maxMagn));
            x *= 0.1 * effectCost;
            x *= 1 + duration;
            x += 0.05 * std::max(1, effect.mArea) * effectCost;
            x *= fEffectCostMult;

            if (effect.mRange == ESM::RT_Target)
                x *= 1.5f;

            float s = 2.f * actorSkills[spellSchoolToSkill(magicEffect->mData.mSchool)];
            if (s - x < minChance)
            {
                minChance = s - x;
                effectiveSchool = magicEffect->mData.mSchool;
                skillTerm = s;
            }
        }
    }
```

In summary
- `calcWeakestSchool` now has a Boolean flag to set to false by default
- `calcNpcSpells` now calls `calcWeakestSchool` with the Boolean flag set to true
- `calcAutoCastChance` now has a Boolean flag to set to false by default
- `calcNpcSpells` now calls `calcAutoCastChance` with the Boolean flag set to true, and `calcAutoCastChance` calls `calcWeakestSchool` with whatever it's Boolean flag is set to at the point of call
- The sum effect is that all NPC calls to `calcWeakestSchool` result in the Boolean being true, and it calling out to the hard coding function, and all player calls result in the Boolean being false

### 17.4, Locking `calcEffectCost()`
`spellpriority.cpp`

`calcEffectCost` modified to carry a Boolean that is false by default

First line,
```
    float calcEffectCost(const ESM::ENAMstruct& effect, const ESM::MagicEffect* magicEffect = nullptr, bool useNpcCost = false);
```

Main file,
```
    float calcEffectCost(const ESM::ENAMstruct& effect, const ESM::MagicEffect* magicEffect, bool useNpcCost)
    {
    ... [rest of function goes here]
```

Then in `rateEffect` the call to `calcEffectCost` was modified to be true

```
        rating *= calcEffectCost(effect, magicEffect, true);
```

`rateEffect` is called in many places by `rateEffects`, but it is only used ultimately for NPC decision making in `rateEffect`

Then `calcEffectCost` was modified to have the same internal logic fork change made elsewhere above,

Original,
```
    float calcEffectCost(const ESM::ENAMstruct& effect, const ESM::MagicEffect* magicEffect, bool useNpcCost)
    {
        const MWWorld::ESMStore& store = MWBase::Environment::get().getWorld()->getStore();
        if (!magicEffect)
            magicEffect = store.get<ESM::MagicEffect>().find(effect.mEffectID);
        bool hasMagnitude = !(magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude);
        bool hasDuration = !(magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration);
        bool appliedOnce = magicEffect->mData.mFlags & ESM::MagicEffect::AppliedOnce;
        int minMagn = hasMagnitude ? effect.mMagnMin : 1;
        int maxMagn = hasMagnitude ? effect.mMagnMax : 1;
        int duration = hasDuration ? effect.mDuration : 1;
        if (!appliedOnce)
            duration = std::max(1, duration);
        static const float fEffectCostMult = store.get<ESM::GameSetting>().find("fEffectCostMult")->mValue.getFloat();

        float x = 0.5 * (std::max(1, minMagn) + std::max(1, maxMagn));
        x *= 0.1 * magicEffect->mData.mBaseCost;
        x *= 1 + duration;
        x += 0.05 * std::max(1, effect.mArea) * magicEffect->mData.mBaseCost;

        return x * fEffectCostMult;
    }
```

Modified,
```
    float calcEffectCost(const ESM::ENAMstruct& effect, const ESM::MagicEffect* magicEffect, bool useNpcCost)
    {
        const MWWorld::ESMStore& store = MWBase::Environment::get().getWorld()->getStore();
        if (!magicEffect)
            magicEffect = store.get<ESM::MagicEffect>().find(effect.mEffectID);
        bool hasMagnitude = !(magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude);
        bool hasDuration = !(magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration);
        bool appliedOnce = magicEffect->mData.mFlags & ESM::MagicEffect::AppliedOnce;
        int minMagn = hasMagnitude ? effect.mMagnMin : 1;
        int maxMagn = hasMagnitude ? effect.mMagnMax : 1;
        int duration = hasDuration ? effect.mDuration : 1;
        if (!appliedOnce)
            duration = std::max(1, duration);
        static const float fEffectCostMult = store.get<ESM::GameSetting>().find("fEffectCostMult")->mValue.getFloat();

        float effectCost = 1.0f;

        if (useNpcCost == false)
        {
            // Player behaviour, use live ESP mBaseCost values
            effectCost = magicEffect->mData.mBaseCost;
        }
        else
        {
            // NPC fork, use hardcoded base game values as per this function
            effectCost = getBaseGameEffectCost(effect.mEffectID);
        }

        float x = 0.5 * (std::max(1, minMagn) + std::max(1, maxMagn));
        x *= 0.1 * effectCost;
        x *= 1 + duration;
        x += 0.05 * std::max(1, effect.mArea) * effectCost;

        return x * fEffectCostMult;
    }
```



## 18, Alchemy  
`alchemy.cpp`
`spellcasting.cpp`

### 18.1, Potion weight change

`alchemy.cpp`

Potion weight is no longer the sum of the two ingredients, but instead a value which is hard capped between 0.1 and 1.0, with the result getting progressively lower as you raise your skill.

Potion weight still depends on ingredient weight, using two 0.1 weight ingredients will still produce a 0.1 weight potion even at 1 skill.

In the base game
- No tools affect weight
- Potion weight is the average weight of all ingredients used

**Base game**

Potion weight is the average weight of all ingredients used in the potion
```
    for (TIngredientsIterator iter (beginIngredients()); iter!=endIngredients(); ++iter)
        if (!iter->isEmpty())
            newRecord.mData.mWeight += iter->get<ESM::Ingredient>()->mBase->mData.mWeight;

    if (countIngredients() > 0)
        newRecord.mData.mWeight /= countIngredients();

```

**The new weight logic**
```
    if (countIngredients() > 0)
    {
        newRecord.mData.mWeight /= countIngredients();
        float weightHolder = newRecord.mData.mWeight;
        weightHolder = std::min(weightHolder, 1.0f);
        float weightReduction = getAlchemyFactor();
        weightReduction /= 100.0f;
        weightHolder -= weightReduction;
        weightHolder = std::max(weightHolder, 0.1f);
        newRecord.mData.mWeight = weightHolder;
    }
```

This means that no potion can weight more than 1.0, or less than 0.1.
The average weight is still used, so light ingredients result in lighter potions still.
Your alchemy factor `(skill + int/10 + luck/10)` is divided by 100, and that amount is subtracted from the capped weight of 1.0.

So if you had 40 luck, 30 int, and 30 alchemy, your alchemy factor would be 37.
If you made a potion with an average weight of 10, it's final weight would be 0.63, as it would first be capped to 1.0, then 37/100 would be subtracted.
Whereas if you made a potion with an average weight of 0.3, it would have a final weight of 0.1, as first it would be reduced to -0.07, then it would be floored to 0.1.

So your skill and attributes help reduce potion weight, heavier potions take longer to mitigate, lighter ingredients still have an inherent advantage, but eventually a master alchemist can make any set of ingredients into a 0.1 strength potion.

Since potion weight is capped at 1 in the calculations before reduction apply, it doesn't matter what the original potion weight would have been if it would be above 1. The same skill is needed to mitigate the carry weight of an originally 20 weight potion, or a 2 weight potion.


### 18.2, Potions no longer stack
`spellcasting.cpp`

This block
```
    bool CastSpell::cast(const ESM::Potion* potion)
    {
        mSourceType = SourceType::Potion;
        mSourceName = potion->mName;
        mId = potion->mId;
        mStack = true;

        inflict(mCaster, mCaster, potion->mEffects, ESM::RT_Self);

        return true;
    }
```

was changed to
```
    bool CastSpell::cast(const ESM::Potion* potion)
    {
        mSourceType = SourceType::Potion;
        mSourceName = potion->mName;
        mId = potion->mId;
        mStack = false;

        inflict(mCaster, mCaster, potion->mEffects, ESM::RT_Self);

        return true;
    }
```

The line...
```
mStack = false;
```

means that the same potion will no longer stack.

So now if you drink 10 of the same healing potion using hotkeys, it does nothing except refresh the potion.
You can still drink 10 different potions to stack the effects, if you really want.


### 18.3, Potion making success rate
`alchemy.cpp`

**Base game**
```
    if (getAlchemyFactor() < Misc::Rng::roll0to99())
    {
        removeIngredients();
        return Result_RandomFailure;
    }
```

Where `AlchemyFactor` is skill + (luck/10) + (intelligence/10)

This results in very poor success rates for most of the early game, prohibitively so, and you reaching 100% about skill 80-90 depending on your attributes.

**New code**
```
    float successChance = 30.0f;
    successChance += ( getAlchemyFactor() / 1.5f);

    if (successChance < Misc::Rng::roll0to99())
    {
        removeIngredients();
        return Result_RandomFailure;
    }
```

The result is,
- Success chance is floored to a minimum of 30%
- Then it adds 2/3 of your alchemy factor as a %
- The result is that 
	- At 5 skill you have about a 40% success rate
	- At 30 skill you have about a 55% success rate
	- You reach 100% success rate at about 80 skill, depending on your attributes

It might appear that you still cannot make a potion at all at very low skills sometimes, but this is due to your alchemy factor being so low that you fail to generate any magnitude or duration of effect (even if you correctly use two ingredients with a matching effect).

This value is then modified by the average quality (gold value) of ingredients you use in the potion,

Within the function `MWMechanics::Alchemy::Result MWMechanics::Alchemy::createSingle ()`

The following block was added, to get the average ingredient value

```
    int numberIngredients = countIngredients();
    int sumIngredientValue = 0;
    for (TIngredientsIterator it = beginIngredients(); it != endIngredients(); ++it)
    {
        if (it->isEmpty()) continue;

        auto *wrap = it->get<ESM::Ingredient>();
        if (!wrap) continue;

        auto *base = wrap->mBase;
        if (!base) continue;

        sumIngredientValue += base->mData.mValue;
    }

    float averageIngredientValue = 0.0f;

    if ((sumIngredientValue > 0) && (numberIngredients > 0))
    {
        averageIngredientValue = static_cast<float>(sumIngredientValue) / static_cast<float>(numberIngredients);
    }
```

Then later in the same function I added

```
    float itemSuccessAddition = 0.0f;

    if (averageIngredientValue >= 10.0f)
    {
        itemSuccessAddition = (0.158f * averageIngredientValue);
        itemSuccessAddition += 8.42f;
    }

    successChance += itemSuccessAddition;
```

This is a straight line equation which converts the average gold value of the items to a flat addition to your potion making success rate.

| Avg item value | +Success % |
| -------------- | ---------- |
| 10             | +10        |
| 25             | +12        |
| 100            | +24        |
| 200            | +40        |

It's not perfect, but I went with a straight line instead of another non-linear to make it more understandable.

This function can be summarised as,
- Average item value multiplied by 0.158, + 8.4

### 18.4, Modifying alchemy factor based on ingredient quality
`alchemy.cpp`

This system gets the average value of all ingredients used in a potion, and increases or decreases the players alchemy factor based on what it gets

**Get the average gold value of the ingredients being used**
```
    //EncoreMP, ingredient value logic
    int numberIngredients = countIngredients();

    std::vector<int> ingredientValues;

    for (TIngredientsIterator it = beginIngredients(); it != endIngredients(); ++it)
    {
        if (it->isEmpty()) continue;

        auto *wrap = it->get<ESM::Ingredient>();
        if (!wrap) continue;

        auto *base = wrap->mBase;
        if (!base) continue;

        int value = base->mData.mValue;

        ingredientValues.push_back(value);
    }
    // the above iterates over the ingredients, checks they exist, gets their base ID, and adds their value to the vector

    int sumIngredientValue = 0;
    for (int v : ingredientValues) sumIngredientValue += v;
    // add them all up into sumIngredientValue as an int

    //EncoreMP end

```

**Use the average value to modify the alchemy factor**
```
    // general alchemy factor
    float x = getAlchemyFactor();

    float averageIngredientValue = 0.0f;
    float priceMod = 0.0f;
    float multMod = 1.0f;
    
    // average the ingredient values with guarding against 0s
    // then work out benefit from tiers and apply, EncoreMP
    if ((sumIngredientValue > 0) && (numberIngredients > 0))
    {
        averageIngredientValue = (sumIngredientValue / numberIngredients);

        if (averageIngredientValue < 5.0f)
        {
            multMod = 0.7f;
            if (averageIngredientValue > 0.1f)
            {
                multMod += (averageIngredientValue * 0.06f);
            }
        }
        else if ((averageIngredientValue >= 5.0f) && (averageIngredientValue < 200.0f))
        {
            // y = (1057 + (-1119 / (1 + (x / 81302080000)^0.1137))
            // where y is skill boost, and x is ingredient value

            float yf = 1057.0f + (-1119.0f / (1.0f + std::powf(averageIngredientValue / 81302080000.0f, 0.1137f)));
            priceMod += yf;

            // handle the multmod for normal range, 5-200gp average value ingredients
            multMod = 1.0f;
            float addToMod = 0.0f;

            // y = 22.87 + ((-47.5)/(1 + ((x/0.00000007014))^0.00415))
            // where y is % modifier addition, and x is ingredient value

            addToMod = 22.87f + (-47.5f / (1.0f + std::powf(averageIngredientValue / 0.00000007014f, 0.00415f)));;

            multMod += addToMod;

        }
        else if (averageIngredientValue >= 200.0f)
        {
            priceMod = 45.0f;
            float highValueHolder = (averageIngredientValue - 200.0f);
            highValueHolder /= 10.0f;
            priceMod += highValueHolder;
        }

        if (averageIngredientValue >= 200.0f)
        {
            multMod = 1.25f;
        }
    }

    if (sumIngredientValue == 0.0f)
    {
        multMod = 0.7f;
    }

    x += priceMod;
    x *= multMod;
```

Summary of changes
- Ingredient value now adds a flat bonus to your alchemy factor, and determines a % modifier to final potion strength
- % Modifier logic
	- Below average values of 5, you get no bonus to alchemy factor, and a % modifier penalty that scales from 70% of base strength at 0gp value average, linearly up to 100% of base strength at 5gp average
	- From 5gp to 200gp the % modifier scales non-linearly to produce the values below on a continous scale
		- 5gp, 1x
		- 10gp, 1.05x
		- 25gp, 1.10x
		- 100gp, 1.15x
		- 199gp, 1.20x
	- Above 200gp the modifier is set to a flat 1.25x
- Flat modifier
	- Below 5gp there is no bonus to alchemy factor
	- From 5 to 200gp the modifier is governed by a non-linear equation that results in these sample values
		- 5gp, +10
		- 10gp, +15
		- 25gp, +25
		- 100gp, +35
		- 200gp, +45
	- Past 200gp a new rule kicks in,
		- Start at +45 and gain +10 for every additional 100gp of item value


### 18.5, Reduce the impact of the mortar
`alchemy.cpp`

The aim here was to make mortar quality above or below 1.0 have 50% less of an effect, to limit how much the player can stack multipliers to potion strength, to avoid (or at least delay) making absurdly strong potions at the high end

**Original code**
```
    // general alchemy factor
    float x = getAlchemyFactor();

    x *= mTools[ESM::Apparatus::MortarPestle].get<ESM::Apparatus>()->mBase->mData.mQuality;
```

**New code**
- Does it what it says, mortar quality now has 50% less of an impact if it is below or above 1.0
```
    // general alchemy factor
    float x = getAlchemyFactor();

    // begin step down mortar effectiveness, EncoreMP
    float mortarQuality = mTools[ESM::Apparatus::MortarPestle].get<ESM::Apparatus>()->mBase->mData.mQuality;

    float mortarModifier = 1.0f;
    float qHolder = 1.0f;

    if (mortarQuality < 1.0f)
    {
        qHolder = (1.0f - mortarQuality);
        qHolder /= 2.0f;
        qHolder = (1.0f - qHolder);
        mortarModifier = qHolder;
    }

    if (mortarQuality > 1.0f)
    {
        qHolder = (mortarQuality - 1.0f);
        qHolder /= 2.0f;
        qHolder += 1.0f;
        mortarModifier = qHolder;
    }

    x *= mortarModifier;

    // end step down mortar effectiveness, EncoreMP
```

### 18.6, Switch potion making to a magicka costed system
`alchemy.cpp`

**Part one, converting alchemy factor into a magicka budget**

Magicka budget = alchemy factor / 4

Reasoning: you cannot reasonably have an alchemy factor of less than 12 (skill 5, intelligence 30, luck 40), so you will always start with a minimum potion spell cost equivalent of 3

So at 100 alchemy, luck, and intelligence, you will be making 30 magicka costed potions (assuming you don't have fancy tools by then, which you will)

**Base game behaviour**

Using the value for x calculated so far (which is the alchemy factor modified by the GMST and mortar quality),
```
float magnitude = (magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude) ?
    1.0f : (x / fPotionT1MagMul) / magicEffect->mData.mBaseCost;
float duration = (magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration) ?
    1.0f : (x / fPotionT1DurMult) / magicEffect->mData.mBaseCost;
```
Other than that, the rest of the function is applying the tools (which multiply these values by x, as determined by tools) and formatting the data into a final effect list 

**New behaviour**
```
float potionMagickaBudget = (x / 4.0f);

float vHolderOne = (potionMagickaBudget / magicEffect->mData.mBaseCost);
vHolderOne *= 40.0f;
float durHolder = sqrtf(vHolderOne);
float magHolder = (durHolder / 2.0f);

// EncoreMP budget to effect converter end
float magnitude = (magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude) ?
            1.0f : magHolder;
float duration = (magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration) ?
            1.0f : durHolder;
```
- Divides alchemy factor by 4 to get a magicka budget
- Uses the above equation to 'spend' the magicka budget of the alchemy result equally on duration and magnitude, as if you were casting an equivalent spell made with the spellmaking system

**If the potion effect is missing either it's magnitude or duration**

Some effects like water walking have a fixed magnitude of 1, so alternative logic is used to calculate their strenth. Overall this logic results in them being weaker than the equivalent magicka costed spells being cast, but this was the best compromise that resulted in smooth scaling for all effect cost values.

Went back to the original magnitude/duration budgeting code and did this,
```
        // EncoreMP budget to effect converter start

        float vHolderOne = (potionMagickaBudget / magicEffect->mData.mBaseCost);
        vHolderOne *= 40.0f;
        float durHolder = sqrtf(vHolderOne);
        float magHolder = (durHolder / 2.0f);

        // override duration, if the effect has no magnitude, to be triple what is calculated above
        // this is not triple the magicka cost, not even close, but it scales better
        if (magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude)
        {
            durHolder *= 3.0f;
        }

        // override magnitude to budget over six, if the effect has no duration
        // e.g. dispel
        // was originally over four, but the balance was off, this way you need middling skill to get 100% dispel potions
        if (magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration)
        {
            magHolder = (vHolderOne / 6.0f);
        }

        // EncoreMP budget to effect converter end

        float magnitude = (magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude) ?
            1.0f : magHolder;
        float duration = (magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration) ?
            1.0f : durHolder;
```

### 18.7, Adjusted behaviour for all other tools
`alchemy.cpp`

The full original function read:
```
void MWMechanics::Alchemy::applyTools (int flags, float& value) const
{
    bool magnitude = !(flags & ESM::MagicEffect::NoMagnitude);
    bool duration = !(flags & ESM::MagicEffect::NoDuration);
    bool negative = (flags & ESM::MagicEffect::Harmful) != 0;

    int tool = negative ? ESM::Apparatus::Alembic : ESM::Apparatus::Retort;

    int setup = 0;

    if (!mTools[tool].isEmpty() && !mTools[ESM::Apparatus::Calcinator].isEmpty())
        setup = 1;
    else if (!mTools[tool].isEmpty())
        setup = 2;
    else if (!mTools[ESM::Apparatus::Calcinator].isEmpty())
        setup = 3;
    else
        return;

    float toolQuality = setup==1 || setup==2 ? mTools[tool].get<ESM::Apparatus>()->mBase->mData.mQuality : 0;
    float calcinatorQuality = setup==1 || setup==3 ?
        mTools[ESM::Apparatus::Calcinator].get<ESM::Apparatus>()->mBase->mData.mQuality : 0;

    float quality = 1;

    switch (setup)
    {
        case 1:

            quality = negative ? 2 * toolQuality + 3 * calcinatorQuality :
                (magnitude && duration ?
                2 * toolQuality + calcinatorQuality : 2/3.0f * (toolQuality + calcinatorQuality) + 0.5f);
            break;

        case 2:

            quality = negative ? 1+toolQuality : (magnitude && duration ? toolQuality : toolQuality + 0.5f);
            break;

        case 3:

            quality = magnitude && duration ? calcinatorQuality : calcinatorQuality + 0.5f;
            break;
    }

    if (setup==3 || !negative)
    {
        value += quality;
    }
    else
    {
        if (quality==0)
            throw std::runtime_error ("invalid derived alchemy apparatus quality");

        value /= quality;
    }
}
```

**New version with changes**

The logic has overall been simplified, but is fundamentally different to the base game

- The retort multiplies the duration and magnitude of positive effects by `1+(retortQuality/10)`
	- So in practise, +5% at 0.5 Quality up to +20% at 2.0 Quality
- The calcinator boosts positive effects and negative effects, but negative effects more strongly (as a trade-off, hopefully making negative effects matter sometimes)
	- Same positive boost as Retort, +5% at 0.5 Quality up to +20% at 2.0 Quality
	- Three times that boost to negative effects, +15% at 0.5 Quality up to +60% at 2.0 Quality
- The alembic reduces negative effects via `effect * (1.0f-(alembicQuality*0.4))`
	- -20% at 0.5 quality, up to -80% at 1.5 quality
	- Hard cap of a 90% reduction at about 2.25 quality, only achievable if you have modded tools (the hard cap is to stop negative values occurring)

```
void MWMechanics::Alchemy::applyTools(int flags, float& value) const
{
    bool magnitude = !(flags & ESM::MagicEffect::NoMagnitude);
    bool duration = !(flags & ESM::MagicEffect::NoDuration);
    bool negative = (flags & ESM::MagicEffect::Harmful) != 0;

    if (!mTools[ESM::Apparatus::Calcinator].isEmpty())
    {
        float calcinatorQuality = mTools[ESM::Apparatus::Calcinator].get<ESM::Apparatus>()->mBase->mData.mQuality;
        if (negative == true)
        {
            calcinatorQuality /= (10.0f / 3.0f);
            calcinatorQuality += 1.0f;
            value *= calcinatorQuality;
        }
        else
        {
            calcinatorQuality /= 10.0f;
            calcinatorQuality += 1.0f;
            value *= calcinatorQuality;
        }
    }

    if (!mTools[ESM::Apparatus::Alembic].isEmpty())
    {
        if (negative == true)
        {
            float alembicQuality = mTools[ESM::Apparatus::Alembic].get<ESM::Apparatus>()->mBase->mData.mQuality;
            float alembicMod = (0.4f * alembicQuality);
            alembicMod = (1.0f - alembicMod);
            alembicMod = std::max(0.1f, alembicMod);
            value *= alembicMod;
        }
    }

    if (!mTools[ESM::Apparatus::Retort].isEmpty())
    {
        if (negative == true)
        {
            value = value;
        }
        else
        {
            float retortQuality = mTools[ESM::Apparatus::Retort].get<ESM::Apparatus>()->mBase->mData.mQuality;
            retortQuality /= 10.0f;
            retortQuality += 1.0f;
            value *= retortQuality;
        }
    }
}
```

### 18.8, Capping potion values at sum cost of ingredients
`alchemy.cpp`

Aim: Cap the value of a potion the player makes by the sum value of the ingredients used in the potion

Just did this
```
    // potion value, with EncoreMP cap added
    mValue = static_cast<int> (
        x * MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find ("iAlchemyMod")->mValue.getFloat());
    mValue = std::min(mValue, sumIngredientValue);
```

Only the `std::min` addition was new by me. It uses the sum ingredient value variable that was established above as part of the item value logic

**Comments:**
- This is a harsh cap, and means that you can never make money from alchemy by mass buying and processing ingredients. But this was intentional, to stop any exploitative gameplay loops.
	- The only problem with this first version, is that it is not realistic. You should be able to make money selling powerful healing potions, people would be willing to pay more than the base ingredients are worth. So this is something to revisit after some playtesting.

### 18.9, Modifying XP gain based on ingredient cost
`alchemy.cpp`

- Added reduced XP logic when average value is below 5gp, to incentivize using uncommon/expensive ingredients
- Increased XP gain from expensive ingredients, up to 3x when the average value is 200gp

The base function which adds to player skill is

```
void MWMechanics::Alchemy::increaseSkill()
{
    mAlchemist.getClass().skillUsageSucceeded (mAlchemist, ESM::Skill::Alchemy, 0);
}
```

I've commented out the call for this function `createSingle`, and instead moved the above line into the `createSingle` function, where the information about ingredient values is already available

Then it does this

```
    float alchemySkill = mAlchemist.getClass().getSkill(mAlchemist, ESM::Skill::Alchemy);

    float alchXpMod = 1.0f;

    //reduction in XP from potions with avg ingredient values less than 5gp
    //to reduce the 1gp ingredient spamming
    //above 5gp the XP gained increases to 4x at 200gp+
    if (averageIngredientValue < 5.0f)
    {
        alchXpMod = 0.5f;
        alchXpMod += (averageIngredientValue * 0.1f);

        if (alchemySkill > 30.0f)
        {
            alchXpMod /= 2.0f;
        }

        if (alchemySkill > 60.0f)
        {
            alchXpMod /= 2.0f;
        }

        if (alchemySkill > 90.0f)
        {
            alchXpMod /= 2.0f;
        }
    }
    else if (averageIngredientValue <= 200.0f)
    {
        alchXpMod += (0.01 * averageIngredientValue);
    }
    else
    {
        alchXpMod = 3.0f;
    }

    mAlchemist.getClass().skillUsageSucceeded(mAlchemist, ESM::Skill::Alchemy, 0, alchXpMod);
    //increaseSkill();

    return Result_Success;
}
```

Result:
- If average ingredient value is 5gp, earn 1x XP
- If average ingredient value is below 5gp, earn 0.5x to 1.0x XP as you scale from 0gp to 5gp linearly
	- At 30, 60, and 90 skill, halve all the XP gained for potions with average values below 5gp, this stacks
	- e.g. at 25 skill a 3gp average value potion will give 0.8x XP, at 34 skill it will give 0.4x XP, at 61 skill it will give 0.2x XP, and at 91 skill it will give 0.1XP
- If average ingredient value is 5-200gp, scale the gained linearly from 1x to 3x, every 10gp average value adds 0.1x to the XP gain multiplier, e.g. an average ingredient value of 100gp results in 2x XP, an average value of 35gp results in a 1.35x XP multiplier, etc

### 18.10, GMST value and behaviour changes
`alchemy.cpp`

To simplify the base game logic I have set `fPotionStrengthMult` to 1.0. 
- This still acts as in the base game as a % potion strength multiplier, but the new system is balanced around this being 1.0.

`fPotionT1MagMult` and `fPotionT1DurMult` were both changed to 1.0.
- These two have had their function changed from the base game, they both act as % modifiers, with 1.0 being 100%, as `fPotionStrengthMult` behaves

Right after tools are applied, and right before it rounds the values, the effect duration and magnitudes are multiplied by these values.

```
        if (!(magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude))
            applyTools (magicEffect->mData.mFlags, magnitude);

        if (!(magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration))
            applyTools (magicEffect->mData.mFlags, duration);

        duration *= fPotionT1DurMult;
        magnitude *= fPotionT1MagMul;

        duration = roundf(duration);
        magnitude = roundf(magnitude);
```

Since the spell making logic is (magnitude x 2) x duration, to generate effect cost, if you want to adjust that ratio for potions you just need to change the two GMSTs whilst respecting the ratio.

## 21, Variable spellcasting XP gain 
`spellcasting.cpp`


Original code, within `bool CastSpell::cast(const ESM::Spell* spell)`

```
if (!mManualSpell && mCaster == getPlayer() && spellIncreasesSkill(spell))
	mCaster.getClass().skillUsageSucceeded(mCaster, spellSchoolToSkill(school), 0);
```

New code as of V0.93

```
        // EncoreMP, grant more XP when costing spells above 5 magicka

        float xpMult = 1.0f;
        float spellCost = spell->mData.mCost;

        if (spellCost > 5.0f)
        {
            spellCost = std::min(spellCost, 50.f);
            xpMult += ((spellCost - 5.0f) * 0.0666f);
        }

        if (!mManualSpell && mCaster == getPlayer() && spellIncreasesSkill(spell))
            mCaster.getClass().skillUsageSucceeded(mCaster, spellSchoolToSkill(school), 0, xpMult);

        // end of EncoreMP increased XP from high cost spells
```

## 23, Willpower changes 
`spellutil.cpp`
`spellcasting.cpp`
`inventorystore.cpp`

**Willpower: spell success**
`spellutil.cpp`
- Increased benefit to spellcasting success by x1.5
	- Previously 50 willpower added 10% success (before fatigue mod)
		- Now it adds 15% (before fatigue mod)


In `calcSpellBaseSuccessChance` in `spellutil.cpp`, added a 1.5x multiplier for the player only

```
        float actorWillpower = stats.getAttribute(ESM::Attribute::Willpower).getModified();
        float actorLuck = stats.getAttribute(ESM::Attribute::Luck).getModified();

        if (actor == player)
        {
            actorWillpower *= 1.5f;
        }

        float castChance = (lowestSkill - spell->mData.mCost + 0.2f * actorWillpower + 0.1f * actorLuck);

        return castChance;
```


**Willpower: Resist magicka**  
`spellcasting.cpp`  
`inventorystore.cpp`

Within `spellcasting.cpp`, the magic resist capping system was modified to include a block that adds to the players magic resistance based on their willpower

For every 5 points of willpower above 50, add 1% magic resistance.
- So at 100 willpower, your character has a passive +10% resist magicka effect at all times

The modification to the `updateMagicEffects` function in `inventorystore.cpp`

```
                    // Start of EncoreMP resistance caps

                    float maxResistSetting = 0.6f;
                    maxResistSetting = std::max(0.0f, maxResistSetting);
                    maxResistSetting = std::min(1.0f, maxResistSetting);
                    float minimumAllowedMultiplier = (1.0f - maxResistSetting);

                    const bool isPlayer = (actor == MWMechanics::getPlayer());

                    float willMagicResist = 0.0f;

                    //sub system to add 10% of willpower to magic resist
                    if (isPlayer)
                    {
                        MWWorld::Ptr player = MWMechanics::getPlayer();
                        const MWMechanics::CreatureStats& playerStats = player.getClass().getCreatureStats(player);
                        float playerWill = playerStats.getAttribute(ESM::Attribute::Willpower).getModified();
                        // Apply bonus resist magicka based on willpower above 50, 1% for every 10 points, this obeys the cap
                        if (playerWill > 50.0f)
                        {
                            playerWill -= 50.0f;
                            willMagicResist = (playerWill / 500.0f);
                        }
                    }


                    // Check for drain effects
                    //DrainAttribute = 17, DrainHealth = 18, DrainMagicka = 19, DrainFatigue = 20, DrainSkill = 21
                    if (effect.mEffectID == 17 || effect.mEffectID == 18 || effect.mEffectID == 19 || effect.mEffectID == 20 || effect.mEffectID == 21)
                    {
                        if (isPlayer) 
                        {
                            params[i].mMultiplier -= willMagicResist;
                            params[i].mMultiplier = std::max(minimumAllowedMultiplier, params[i].mMultiplier);
                        }

                    }
```

and then it repeats that check for effects block for each set of effects included in the MR system.

The `inflict` function in `spellcasting.cpp` was modified in a similar way

```
            // Start of EncoreMP resistance caps

            if (target == getPlayer())
            {
                int effectholder = effectIt->mEffectID;

                bool applyCap = false;

                float maxResistSetting = 0.6f;

                maxResistSetting = std::max(0.0f, maxResistSetting);
                maxResistSetting = std::min(1.0f, maxResistSetting);

                float minimumAllowedMultiplier = (1.0f - maxResistSetting);


                //sub system to add 10% of willpower to magic resist
                MWWorld::Ptr player = getPlayer();
                const MWMechanics::CreatureStats &playerStats = player.getClass().getCreatureStats(player);
                float playerWill = playerStats.getAttribute(ESM::Attribute::Willpower).getModified();
                float willMagicResist = 0.0f;

                // Apply bonus resist magicka based on willpower above 50, 1% for every 10 points, this obeys the cap
                if (playerWill > 50.0f)
                {
                    playerWill -= 50.0f;
                    willMagicResist = (playerWill / 500.0f);
                }

                //check for drain effects
                //DrainAttribute = 17, DrainHealth = 18, DrainMagicka = 19, DrainFatigue = 20, DrainSkill = 21
                if (effectholder == 17 || effectholder == 18 || effectholder == 19 || effectholder == 20 || effectholder == 21)
                {
                    applyCap = true;
                }
				// etc for the other effect blocks

                if (applyCap == true)
                {
                    magnitudeMult -= willMagicResist;
                    if (magnitudeMult < minimumAllowedMultiplier)
                    {
                        magnitudeMult = minimumAllowedMultiplier;
                    }
                }

            }

```

## 25, Hand to Hand 
`combat.cpp`
`npc.cpp`
`creature.cpp`
`difficultyscaling.cpp`
`difficultyscaling.hpp`

### 25.1, Accuracy

This change has not been made here, it was done during the original melee accuracy pass, but I have included it as a reminder of what was done there.

**Hand to hand accuracy**

Tested and confirmed that hand to hand accuracy is also captured in the new weapon accuracy logic, so hand to hand combat accuracy is,
```
        if (attacker == getPlayer())
        {
            attackTerm += (skillValue * 0.8) +
                (stats.getAttribute(ESM::Attribute::Agility).getModified() / 5.0f) +
                (stats.getAttribute(ESM::Attribute::Luck).getModified() / 10.0f);
            attackTerm *= stats.getFatigueTerm();
            attackTerm += mageffects.get(ESM::MagicEffect::FortifyAttack).getMagnitude() -
                mageffects.get(ESM::MagicEffect::Blind).getMagnitude();
            attackTerm += 10;
        }
```
So it has a higher floor, and scales slower. This is the same code used for weapon accuracy.

### 25.2, Damage done at low skill levels
`combat.cpp`

Since in core the damage done by hand to hand is derived from your skill multiplied by your attack draw strength, you do trivial amounts of damage at low skill.

For example, given that a fully drawn attack caps out at a 0.5x multiplier,
- Skill 5 = 2.5 fatigue damage
- Skill 10 = 5
- Skill 20 = 10
- Skill 30 = 15

So the logic was changed to use (10 + (your skill x 0.9)),
which is then modified by the draw strength as in core, resulting in:  
- Skill 5 = 7.25 fatigue damage
- Skill 10 = 9.5
- Skill 20 = 14
- Skill 30 = 18.5
- It then becomes roughly equivalent to core behaviour from skill 40 onwards, scaling a little slower overall and reaching the same final damage value at 100 skill.
- Beyond 100 skill this does result in a reduction in damage gained from skill, but that is probably desirable due to the linear scaling already resulting in potentially absurd figures with some fortify skill effects

The code change was done in: `combat.cpp`, within the function `void getHandToHandDamage`

The first few lines were changed to
```
if (attacker == MWMechanics::getPlayer())
{
    damage = (0.9f * (static_cast<float>(attacker.getClass().getSkill(attacker, ESM::Skill::HandToHand))));
    damage += 10.0f;
}
else
{
    damage = static_cast<float>(attacker.getClass().getSkill(attacker, ESM::Skill::HandToHand));
}
```

Whereas before damage was just equal to your skill

### 25.3, Fatigue damage difficulty based scaling
`npc.cpp`
`creature.cpp`
`difficultyscaling.cpp`
`difficultyscaling.hpp`

This section changes it so that fatigue damage dealt by the player is reduced by difficulty setting (this was missed during my original difficulty scaling pass, and is not scaled at all in the core game), and fatigue damage taken is increased by difficulty scaling.
This involved the creation of a a new function in `difficultyscaling.cpp`, and update to it's header file `difficultyscaling.hpp`, and guarding and calls to the new function in both `npc.cpp` and `creature.cpp` (since each of creatures and NPC hand to hand attacks are handled elsewhere in the code, both when they are attacking or defending).

The reason for a new difficulty scaling function was because
- Fatigue damage taken is not reduced by armour, so it was too high if it was given the conventional melee damage taken 1-5x scaling
- Fatigue damage dealt has to overcome the targets passive fatigue regen, so lower values for damage dealt result in potentially being unable to reduce target fatigue at all (which was seen on the highest difficulties)

In `difficultyscaling.hpp`:
A new function was registered
```
float scaleHandDamage(float damage, const MWWorld::Ptr& attacker, const MWWorld::Ptr& victim);
```
This is an identical copy of the normal scale damage function, but with a new name

In `difficultyscaling.cpp`, the new function was added, again an identical copy of the normal scale damage function, but with new values for the multipliers

```
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
```

Another change was required within `npc.cpp`,
within the 'else' fork of that function (this else fork covers if `isHealth` if false) within `onHit`
```
        else
        {
            //add difficulty based scaling for H2H fatigue damage taken and dealt
            if (!attacker.isEmpty() && !godmode)
                if (damage > 0)
                {
                    damage = scaleHandDamage(damage, attacker, ptr);
                }

```
The check for damage greater than 0 may not be necessary, but there are a few calls in the engine to the `onHit` function from non-attack sources which pass `isHealth = false` and damage = 0. So I added the check for damage greater than 0 just in case.  

Within `creature.cpp`, within the else fork (else covers if `isHealth` if false) of `onHit`
```
            else
            {
                if (!attacker.isEmpty())
                {
                    if (damage > 0)
                    {
                        damage = scaleHandDamage(damage, attacker, ptr);
                    }
                }
                MWMechanics::DynamicStat<float> fatigue(stats.getFatigue());
                fatigue.setCurrent(fatigue.getCurrent() - damage, true);
                stats.setFatigue(fatigue);
            }
```

This is the exact same logic and reasoning as with the NPC file. Note there are some syntax changes, which I inferred from the creature files code for when `isHealth` is true. 
Also, for creatures I didn't check if there are any non-attack sourced calls to this function (as with the NPC function) where `isHealth = false` and damage = 0, but to be safe I put the guarding in anyway as a precaution.

### 25.4, Changing Openmw strength scaling behaviour
`combat.cpp`

Openmw adds an optional strength scaling for hand to hand combat. I would like to keep this, and suggest it be toggled on by default, however the way it is implemented is slightly buggy and not in line with how attributes affect other skills.

If this was toggled on it did this,
```
damage *= 
attacker.getClass().getCreatureStats(attacker).getAttribute(ESM::Attribute::Strength).getModified() / 40.0f;
```

Which is multiplying your hand to hand damage by your strength over 40, this causes two problems (one likely unintentional)
- At 100 strength you are doing 2.5x hand to hand damage, this seems excessive, and certainly will be as I revise this system
- At damaged strength values below 40, you do massively reduced damage (I assume this is unintentional), e.g. if you are damaged to strength 10, you do 10/40 = 25% of your normal damage
	- Whereas with all weapons in the base game, a strength of 10 would only reduce weapon damage to 60% of the base value, since that logic is counting values above and below 50

So to fix this, I am changing the strength scaling here to be in line with weapon scaling logic, and to scale based on the strength value above or below 50.

Within `combat.cpp`, within `void getHandToHandDamage`,

Originally it did,
```
        // Options in the launcher's combo box: unarmedFactorsStrengthComboBox
        // 0 = Do not factor strength into hand-to-hand combat.
        // 1 = Factor into werewolf hand-to-hand combat.
        // 2 = Ignore werewolves.
        int factorStrength = Settings::Manager::getInt("strength influences hand to hand", "Game");
        if (factorStrength == 1 || (factorStrength == 2 && !isWerewolf))
        {
        damage *= attacker.getClass().getCreatureStats(attacker).getAttribute(ESM::Attribute::Strength).getModified() / 40.0f;
        }
```

Now it does,

```
        // Options in the launcher's combo box: unarmedFactorsStrengthComboBox
        // 0 = Do not factor strength into hand-to-hand combat.
        // 1 = Factor into werewolf hand-to-hand combat.
        // 2 = Ignore werewolves.
        int factorStrength = Settings::Manager::getInt("strength influences hand to hand", "Game");
        if (factorStrength == 1 || (factorStrength == 2 && !isWerewolf))
        {
            // EncoreMP, change str scaling to behave like weapon scaling does in core
            float attackerStrength = attacker.getClass().getCreatureStats(attacker).getAttribute(ESM::Attribute::Strength).getModified();
            float strengthMult = 1.0f;
            float strengthHolder = 50.0f;
            attackerStrength = std::max(1.0f, attackerStrength);

            if (attackerStrength != 50.0f)
            {
                strengthHolder = (attackerStrength - 50.0f);
                strengthHolder /= 100.0f;
                strengthMult += strengthHolder;
            }
```
This has been tested and works fine with werewolves as well

## 26, Pickpocketing 
`pickpocket.cpp`
`pickpocketitemmodel.cpp`

### 26.1, You can no longer get caught when closing the pickpocketing UI
`pickpocket.cpp`

This finish function triggers when you close the menu, previously it was

```
    bool Pickpocket::finish()
    {
        return getDetected(0.f);
    }
```

However this still means you may get caught, as it runs the get detected logic but with an item value of 0.

Now it just does

```
    bool Pickpocket::finish()
    {
        //now the player will never be caught just from closing the window
        return false;
    }
```

So you can never fail closing the item menu

### 26.2, Item difficulty is value x1, providing GMST is 1.0. Change to expected GMST value
`pickpocket.cpp`

Updated `pick()` to
```
    bool Pickpocket::pick(MWWorld::Ptr item, int count)
    {
        float stackValue = static_cast<float>(item.getClass().getValue(item) * count);
        float fPickPocketMod = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>()
                .find("fPickPocketMod")->mValue.getFloat();
        float valueTerm = fPickPocketMod * stackValue;

        return getDetected(valueTerm);
    }
```
- Removed the 10x multiplier in the value term equation
- Set the GMST `fPickPocketMod` to 1.0 (up from 0.3 in the base game)
- So now providing the GMST is 1.0, the value term is equal to stack value

### 26.3, Updating what items can appear to the player in the NPC inventory window when sneaking
`pickpocketitemmodel.cpp`

Changed the item model function to the following:
```
    PickpocketItemModel::PickpocketItemModel(const MWWorld::Ptr& actor, ItemModel *sourceModel, bool hideItems)
        : mActor(actor), mPickpocketDetected(false)
    {
        MWWorld::Ptr player = MWMechanics::getPlayer();
        mSourceModel = sourceModel;
        //float chance = player.getClass().getSkill(player, ESM::Skill::Sneak);

        //updated chance logic to better mirror pickpocket success chance logic
        //note however that this does not include the fatigue term, an intentional choice
        //so by balancing around a 50% chance to steal, I am actually setting a baseline chance of 62.5% if the player is full fatigue
        const MWMechanics::CreatureStats &playerStats = player.getClass().getCreatureStats(player);
        float luck = playerStats.getAttribute(ESM::Attribute::Luck).getModified();
        float agility = playerStats.getAttribute(ESM::Attribute::Agility).getModified();
        float sneak = player.getClass().getSkill(player, ESM::Skill::Sneak);
        float chance = (sneak + (agility * 0.2) + (luck * 0.1));


        // gold per skill level logic, will mirror what the steal chances are

        chance *= 5.0f;

        //

        mSourceModel->update();

        // build list of items that player is unable to find when attempts to pickpocket.
        if (hideItems)
        {
            for (size_t i = 0; i<mSourceModel->getItemCount(); ++i)
            {
                const ItemStack& item = mSourceModel->getItem(i);
                MWWorld::Ptr itemPtr = item.mBase;
                if (itemPtr.isEmpty())
                    continue; // don't know if I needed to do this but its here just in case, I think 
                              // NPCs can carry non-item light sources as psuedo items as per base game behaviour, unsure if it would be an issue

                int singleValue = itemPtr.getClass().getValue(itemPtr);
                int count = item.mCount;
                float stackValue = static_cast<float>(singleValue) * static_cast<float>(count);

                //float chanceMod = (chance * 10.0f);

                if (stackValue > chance)
                {
                    mHiddenItems.push_back(mSourceModel->getItem(i));
                }
            }
        }
    }
```

and updated the `update()` function

```
    void PickpocketItemModel::update()
    {
        mSourceModel->update();
        mItems.clear();
        for (size_t i = 0; i<mSourceModel->getItemCount(); ++i)
        {
            const ItemStack& item = mSourceModel->getItem(i);

            // Bound items may not be stolen
            if (item.mFlags & ItemStack::Flag_Bound)
                continue;

            // Slight restructure of logic, an attempt at some backend guarding

            bool itemHidden = false;
            for (const ItemStack &h : mHiddenItems)
            {
                if (h.mBase.isEmpty()) continue;
                if (item.mBase.isEmpty()) { itemHidden = false; break; }
                if (h.mBase == item.mBase) { itemHidden = true; break; }
            }
            if (!itemHidden && item.mType != ItemStack::Type_Equipped && !(item.mFlags & ItemStack::Flag_Bound))
                mItems.push_back(item);


            //original logic
            //if (std::find(mHiddenItems.begin(), mHiddenItems.end(), item) == mHiddenItems.end()
            //        && item.mType != ItemStack::Type_Equipped)
            //   mItems.push_back(item);
        }
    }
```

These changes mean that when the player pickpockets, they can only see items up to their pickpocketing term (agi/5 + luck/10 + sneak), multiplied by 5
So at 30 agility, 40 luck and 5 skill, you have a term of 15
This means you can see items up to 75g in value

### 26.4, Change to pickpocketing difficulty logic
`pickpocket.cpp`

The `getDetected` function was completely overhauled to

```
    bool Pickpocket::getDetected(float valueTerm)
    {
        float playerTerm = getChanceModifier(mThief);

        float itemValue = valueTerm;

        itemValue = std::max(itemValue, 1.0f);

        float itemDifficulty = (itemValue / 5.0f);

        float difficultyMod = (playerTerm - itemDifficulty);

        difficultyMod *= 1.50f;

        int successChance = 50;

        successChance += static_cast<int>(difficultyMod);

        int iPickMinChance = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>()
            .find("iPickMinChance")->mValue.getInteger();
        int iPickMaxChance = MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>()
            .find("iPickMaxChance")->mValue.getInteger();

        int roll = Misc::Rng::roll0to99();

        successChance = std::min(int(iPickMaxChance), successChance);
        successChance = std::max(int(iPickMinChance), successChance);

        if (successChance > roll)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
```

So now you have a 50% chance (at 1x fatigue mod) to steal anything you can see, providing you aren't seen doing it.

It is balanced around 5g per term.

Every 5g in item value above or below 50%, adds plus or minus 1.5% success chance.

This mean at maximum fatigue, you have a baseline success chance of 62.5%. If you were 25 levels above the items value times 5, then you would never fail at pickpocketing it. So you don't start reliably pickpocketing cheap items until about 20-25 levels above the item value.

The idea with this change is to complement the menu logic, which determines which item appears, so that the player knows that any item they are capable of seeing is one they have a good chance of stealing. This is my way of unhiding the logic a little, without making the player memorise numbers.

## 27, Server checksum

`Version.hpp`

Changes `Version.hpp` to,

```
#ifndef OPENMW_VERSION_HPP
#define OPENMW_VERSION_HPP

#define TES3MP_VERSION "0.8.1"
#define TES3MP_PROTO_VERSION 806

#define TES3MP_DEFAULT_PASSW "blankpassword"
#define TES3MP_MASTERSERVER_PASSW "12345"


#endif //OPENMW_VERSION_HPP

```

Working, this now produces a server and client that both have the internal checksum version of 806, instead of 10 for the core tes3mp release.

I have tested and it properly prevents you from connecting with the wrong version to the server, and from using the wrong client on a normal server.

For some reason I decided not to get into, any change at all to the TESMP_VERSION (which is the user facing string) causes the build to fail with fatal errors. So I have left that as is, and as a consequence right now despite the checksum actually being different it still displays the same previous version on the server browser

## 28, Caching stealth checks

To implement the V0.50 OpenMW changes,

**Updating the base function to carry a Boolean**
The `awarenessCheck` function was updated to include a Boolean which is true by default,

In `mechanicsmanagerimp.hpp`
The function declaration was updated to include the Boolean as true by default
```
bool awarenessCheck(const MWWorld::Ptr& ptr, const MWWorld::Ptr& observer, bool useCache = true) override;
```

In `mechanicsmanager.hpp`
The function declaration was updated to include the Boolean as true by default
```
virtual bool awarenessCheck(const MWWorld::Ptr& ptr, const MWWorld::Ptr& observer, bool useCache = true) = 0;
```

Note that both have to updated, `mechanicsmanagerimp` is the implementation of the mechanic, but relies on `mechanicsmanager.hpp`

Within `mechanicsmanager.cpp` the function itself was updated to declare the Boolean

```
    bool MechanicsManager::awarenessCheck(const MWWorld::Ptr& ptr, const MWWorld::Ptr& observer, bool useCache)
    {
```

**Adding a logic fork within awarenessCheck to respond to the Boolean state**
Within the `awarenessCheck` function in `mechanicsmanager.cpp` this clause was added further down. 
```
        float target = x - y;

        if (useCache)
            return observerStats.getAwarenessRoll() >= target;
        return (Misc::Rng::roll0to99() >= target);
    }
```

**Adding the update awareness check to the generic update actor function**
Within `actors.cpp`
the `updateActor` function was updated to include an `updateAwareness` check

```
    void Actors::updateActor (const MWWorld::Ptr& ptr, float duration)
    {
        // Trial implementation of openMW 0.50 useCache change to stealth behaviour
        ptr.getClass().getCreatureStats(ptr).updateAwareness(duration);

        // magic effects
        adjustMagicEffects (ptr);
        if (ptr.getClass().getCreatureStats(ptr).needToRecalcDynamicStats())
            calculateDynamicStats (ptr);

        calculateCreatureStatModifiers (ptr, duration);
        // fatigue restoration
        calculateRestoration(ptr, duration);
    }
```


**Updating creature stats to add new awareness check functions**
In `creaturestats.cpp` 
Added this to the files included:
`#include <components/misc/rng.hpp>`
So that the dice roll (rng) function could be called within the file,

and the two new functions were added
```
    // Trial implementation of openMW 0.50 useCache change to stealth behaviour
    void CreatureStats::updateAwareness(float duration)
    {
        mAwarenessTimer += duration;
        // Only reroll for awareness every 5 seconds
        if (mAwarenessTimer >= 5.f)
        {
            mAwarenessTimer = 0.f;
            mAwarenessRoll = -1;
        }
    }

    // Trial implementation of openMW 0.50 useCache change to stealth behaviour
    int CreatureStats::getAwarenessRoll()
    {
        if (mAwarenessRoll >= 0)
            return mAwarenessRoll;

        mAwarenessRoll = Misc::Rng::roll0to99();

        return mAwarenessRoll;
    }
```

Then in `creaturestats.hpp`
in the private declarations these were added,
```
float mAwarenessTimer = 0.f;
int mAwarenessRoll = -1;
```
and at the end of the file
```
void updateAwareness(float duration);
int getAwarenessRoll();
```

**Updating the combat stealth functions to pass the boolean flag as false**

In `aipursue.cpp` updated
```
    if (isTargetMagicallyHidden(target) && !MWBase::Environment::get().getMechanicsManager()->awarenessCheck(target, actor, false))
        return false;
```
to pass the flag as false

In `aicombataction.cpp` updated
```
        if (isTargetMagicallyHidden(enemy) && !MWBase::Environment::get().getMechanicsManager()->awarenessCheck(enemy, actor, false))
        {
            return false;
        }
```
to pass the flag as false


## 29, Ally difficulty scaling

This is documented in sections, as like player difficulty scaling each part of allied damage is handled in a separate location in the code.

### 29.1, New difficulty scaling function

In `difficultyscaling.hpp` a new function was declared,
`float allyDamageDealt();`

In `difficultyscaling.cpp` the new function was added,

```
float allyDamageDealt()
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
```

This is what is called for all ally damage scaling

### 29.2, Creature allies physical damage

**Creature allies, melee attacks**
Within `creature.cpp`,
This include was added, needed below for the logic behind the new Boolean,
`#include "../mwmechanics/aipackage.hpp"`

Within `onHit()` this clause was added to define and toggle the new Boolean,

```
        // determine if the attacker is a creature allied with the player, and set Boolean to true if so

        bool attackerIsPlayerAlly = false;

        if (!attacker.isEmpty() && attacker.getClass().isActor())
        {
            MWMechanics::CreatureStats& statsAttacker = attacker.getClass().getCreatureStats(attacker);
            for (const auto& package : statsAttacker.getAiSequence())
            {
                if (!package) continue;
                if (package && package->followTargetThroughDoors())
                {
                    const MWWorld::Ptr& master = package->getTarget();
                    if (master.isEmpty()) continue;
                    bool masterIsPlayer = (master == MWMechanics::getPlayer()) || mwmp::PlayerList::isDedicatedPlayer(master);
                    if (!masterIsPlayer) continue;
                    attackerIsPlayerAlly = true;
                }
            }
        }
```

Anything that,
- Is following a target through doors
- and for whom that target is a player
Is considered a player ally

Then later on within the `onHit()` function, two new forks in the logic were added to make use of the new Boolean,

```
            if(ishealth)
            {
                damage *= damage / (damage + getArmorRating(ptr));
                damage = std::max(1.f, damage);
                if (!attacker.isEmpty())
                {
                    // neccessary here to introduce a fork in behaviour, otherwise attacks on the player
                    // would double dip in damage scaling by calling both difficulty scaling functions
                    // no need to guard here against attacker is player, since this is creature specific combat
                    MWWorld::Ptr player = MWMechanics::getPlayer();
                    if (ptr == player)
                    {
                        damage = scaleDamage(damage, attacker, ptr);
                    }
                    else
                    {
                        if (attackerIsPlayerAlly)
                        {
                            float allyDamageMult = allyDamageDealt();
                            damage *= allyDamageMult;
                        }
                    }
                    MWBase::Environment::get().getWorld()->spawnBloodEffect(ptr, hitPosition);
                }

                MWBase::Environment::get().getSoundManager()->playSound3D(ptr, "Health Damage", 1.0f, 1.0f);

                MWMechanics::DynamicStat<float> health(stats.getHealth());
                health.setCurrent(health.getCurrent() - damage);
                stats.setHealth(health);
            }
```

and

```
            else
            {
                if (!attacker.isEmpty())
                {
                    MWWorld::Ptr player = MWMechanics::getPlayer();
                    if (damage > 0)
                    {
                        if (ptr == player)
                        {
                            damage = scaleHandDamage(damage, attacker, ptr);
                        }
                        else
                        {
                            if (attackerIsPlayerAlly)
                            {
                                float allyDamageMult = allyDamageDealt();
                                damage *= allyDamageMult;
                            }
                        }
                        
                    }
                }
                MWMechanics::DynamicStat<float> fatigue(stats.getFatigue());
                fatigue.setCurrent(fatigue.getCurrent() - damage, true);
                stats.setFatigue(fatigue);
            }
```

- As per the code comments, I had to fork the logic so that only one type of damage scaling was called, otherwise a creature attacking the player on high difficulty would have called both the increased and decreased damage done functions


### 29.3, NPC allies physical damage

This was the same as the creature physical damage scaling logic, but it had to be implemented separately as NPCs handle their combat in their own file.

Within `npc.cpp`

Updated the headers to include `#include "../mwmechanics/aipackage.hpp"` for the ally detection boolean logic

Added the ally detection function used elsewhere, slightly modified for this file

```
        bool attackerIsPlayerAlly = false;

        if (!attacker.isEmpty() && attacker.getClass().isActor())
        {
            MWMechanics::CreatureStats& statsAttacker = attacker.getClass().getCreatureStats(attacker);
            for (const auto& package : statsAttacker.getAiSequence())
            {
                if (!package) continue;
                if (package && package->followTargetThroughDoors())
                {
                    const MWWorld::Ptr& master = package->getTarget();
                    if (master.isEmpty()) continue;
                    bool masterIsPlayer = (master == MWMechanics::getPlayer()) || mwmp::PlayerList::isDedicatedPlayer(master);
                    if (!masterIsPlayer) continue;
                    attackerIsPlayerAlly = true;
                }
            }
        }
```

Then called that boolean in two places to modify damage done if they are a player ally,

For health damage,

```
        if (ishealth)
        {
            if (!attacker.isEmpty() && !godmode)
            {
                if ((attacker == MWMechanics::getPlayer()) || (ptr == MWMechanics::getPlayer()))
                {
                    damage = scaleDamage(damage, attacker, ptr);
                }
                else
                {
                    if (attackerIsPlayerAlly)
                    {
                        float allyDamageMult = allyDamageDealt();
                        damage *= allyDamageMult;
                    }
                }
            }
```

For non-health damage (H2H fatigue),

```
            // add difficulty based scaling for H2H fatigue damage taken and dealt
            if (!attacker.isEmpty() && !godmode)
                if (damage > 0)
                {
                    if ((attacker == MWMechanics::getPlayer()) || (ptr == MWMechanics::getPlayer()))
                    {
                        damage = scaleDamage(damage, attacker, ptr);
                    }
                    else
                    {
                        if (attackerIsPlayerAlly)
                        {
                            float allyDamageMult = allyDamageDealt();
                            damage *= allyDamageMult;
                        }
                    }
                }
```

As with the other ally changes, I had to fork the logic to make sure the difficulty scaling didn't double dip with player difficulty scaling.

Also unlike the creature changes, I had to also check here that the neither the attacker nor the victim was the player - as the player character routes it's combat behaviour through the NPC file, so the player can potentially be an attacker here unlike in the creature file.


### 29.4, Allied elemental shield damage
- This captures both NPC and creature allies

Within `combat.cpp` the `applyElementalShields()` function was modified,

First added the ally detection logic

```
            // determine if the source of the Elemental shield is a creature allied with the player, and set Boolean to true if so
            bool sourceIsPlayerAlly = false;

            if (!victim.isEmpty() && victim.getClass().isActor())
            {
                MWMechanics::CreatureStats& statsSource = victim.getClass().getCreatureStats(victim);
                for (const auto& package : statsSource.getAiSequence())
                {
                    if (!package) continue;
                    if (package && package->followTargetThroughDoors())
                    {
                        const MWWorld::Ptr& master = package->getTarget();
                        if (master.isEmpty()) continue;
                        bool masterIsPlayer = (master == MWMechanics::getPlayer()) || mwmp::PlayerList::isDedicatedPlayer(master);
                        if (!masterIsPlayer) continue;
                        sourceIsPlayerAlly = true;
                    }
                }
            }
```

Then forked elemental shield behaviour based on the result of the Boolean,

```
            MWWorld::Ptr player = MWMechanics::getPlayer();

            if (attacker == player)
            {
                x *= magicdamagetaken();
            }
            else if ((victim == player) || (sourceIsPlayerAlly == true))
            {
                x *= castenchantedDamagescale();
            }


            MWMechanics::DynamicStat<float> health = attackerStats.getHealth();
            health.setCurrent(health.getCurrent() - x);
            attackerStats.setHealth(health);

            MWBase::Environment::get().getSoundManager()->playSound3D(attacker, "Health Damage", 1.0f, 1.0f);
```

### 29.5, Allied spellcasting
- This captures both NPC and creature allies

Within `spellcasting.cpp`, within the `inflict` function

The same boolean logic was added to flag if the caster of a spell effect is allied to the player - this has been done within the `inflict` function

```
                // EncoreMP determine if spellcaster is allied to the player

                bool casterIsPlayerAlly = false;

                if (!caster.isEmpty() && caster.getClass().isActor())
                {
                    MWMechanics::CreatureStats& statsCaster = caster.getClass().getCreatureStats(caster);
                    for (const auto& lpackage : statsCaster.getAiSequence())
                    {
                        if (!lpackage) continue;
                        if (lpackage && lpackage->followTargetThroughDoors())
                        {
                            const MWWorld::Ptr& master = lpackage->getTarget();
                            if (master.isEmpty()) continue;
                            bool masterIsPlayer = (master == MWMechanics::getPlayer()) || mwmp::PlayerList::isDedicatedPlayer(master);
                            if (!masterIsPlayer) continue;
                            casterIsPlayerAlly = true;
                        }
                    }
                }

                // end of ally determination
```

Some variable names were changed to avoid conflicting with similar variables used elsewhere in the function

The Boolean was then used to fork the damage logic for spellcasting,

```
                if (mSourceType == SourceType::Spell && target != player && target != caster && (effectholder == 14 || effectholder == 15 || effectholder == 16 || effectholder == 18 || effectholder == 23 || effectholder == 27 || effectholder == 86))
                {
                    if (caster == player)
                    {
                        magnitude *= castenchantedDamagescale();
                    }
                    else if (casterIsPlayerAlly)
                    {
                        magnitude *= allyDamageDealt();
                    }
                }
```


### 29.6, Allied enchantments
- This captures both NPC and creature allies

Within `spellcasting.cpp`, within the `inflict` function

The boolean defined above was used to toggle damage scaling for on-strike via

```
                if (mEnchantmentType == ESM::Enchantment::WhenStrikes && target != player && (effectholder == 14 || effectholder == 15 || effectholder == 16 || effectholder == 18 || effectholder == 23 || effectholder == 27 || effectholder == 86))
                {
                    if (caster == player)
                    {
                        magnitude *= onstrikeDamageScale();
                    }
                    else if (casterIsPlayerAlly)
                    {
                        magnitude *= allyDamageDealt();
                    }

                }
```

and also toggle damage scaling for on-use and cast-once (scroll) damage scaling

```
                if ((mEnchantmentType == ESM::Enchantment::CastOnce || mEnchantmentType == ESM::Enchantment::WhenUsed) && target != player && target != caster && (effectholder == 14 || effectholder == 15 || effectholder == 16 || effectholder == 18 || effectholder == 23 || effectholder == 27 || effectholder == 86))
                {
                    if (caster == player)
                    {
                        magnitude *= castenchantedDamagescale();
                    }
                    else if (casterIsPlayerAlly)
                    {
                        magnitude *= allyDamageDealt();
                    }
                }
```

### 29.7, Note on reflected spells

The existing code already accounts for reflected damage, and treats it as normal spell damage for the purposes of difficulty scaling.

In other words, damage reflected by a player or their ally is stepped down by difficulty, all other reflection damage is handled normally (at 1x).

This is because the code stores (in the case of reflected damage) the original caster as `mCaster`, and the current source of the effect (so the actor who is reflecting) as `caster`. All of the ally damage scaling only reduces damage done if the `caster` is the player or their ally the damage of the effect is reduced, so the existing damage reduction code captures both direct and reflected damage coming from the player or their allies.



## 30, Spell buying menu substitution system
`spellbuyingwindow.cpp`    

The function `void SpellBuyingWindow::setPtr(const MWWorld::Ptr& actor, int startOffset)` was updated as shown below,    

```
    void SpellBuyingWindow::setPtr(const MWWorld::Ptr& actor, int startOffset)
    {
        center();
        mPtr = actor;
        clearSpells();

        MWMechanics::Spells& merchantSpells = actor.getClass().getCreatureStats (actor).getSpells();

        std::vector<const ESM::Spell*> spellsToSort;

        std::string prefix = "@";

        for (MWMechanics::Spells::TIterator iter = merchantSpells.begin(); iter!=merchantSpells.end(); ++iter)
        {
            const ESM::Spell* spell = iter->first;

            if (spell->mData.mType!=ESM::Spell::ST_Spell)
                continue; // don't try to sell diseases, curses or powers

            if (actor.getClass().isNpc())
            {
                const ESM::Race* race =
                        MWBase::Environment::get().getWorld()->getStore().get<ESM::Race>().find(
                        actor.get<ESM::NPC>()->mBase->mRace);
                if (race->mPowers.exists(spell->mId))
                    continue;
            }

            if (playerHasSpell(iter->first->mId))
                continue;

            spellsToSort.push_back(iter->first);
        }

        // EncoreMP spell replacement trial

        //get all spell records in the game
        const auto& allSpells = MWBase::Environment::get().getWorld()->getStore().get<ESM::Spell>();

        //make an empty vector to hold spells to be added to the merchant spell list
        std::vector<const ESM::Spell*> encoreSpellsToAdd;
        std::vector<std::string> spellsToDelete;

        //ranged based loop over merchant spells for sale, no modifying of original vector within this loop
        for (const ESM::Spell* s : spellsToSort)
        {
            if (!s) continue;

            std::string spellID = s->mId;
            std::string encoreID = prefix + spellID;
            const ESM::Spell* spellToInsert = nullptr;
            

            spellToInsert = allSpells.search(encoreID);

            
            if (spellToInsert && !spellToInsert->mId.empty() && spellToInsert->mData.mType == ESM::Spell::ST_Spell)
            {
                if (playerHasSpell(spellToInsert->mId))
                {
                    spellsToDelete.push_back(spellID);
                }
                else
                {
                    encoreSpellsToAdd.push_back(spellToInsert);
                    spellsToDelete.push_back(spellID);
                }
            }
        }

        //add all new spells, stored in the vector, to the merchant spell list for sale
        for (const ESM::Spell* s : encoreSpellsToAdd) 
        {
            spellsToSort.push_back(s);
        }

        //delete all the original spells in the merchant for sale list for which new IDs were found
        spellsToSort.erase(std::remove_if(spellsToSort.begin(), spellsToSort.end(),[&](const ESM::Spell* elem) 
            {
                if (!elem) return false;
                return std::find(spellsToDelete.begin(), spellsToDelete.end(), elem->mId)
                != spellsToDelete.end();
            }
            ),
            spellsToSort.end()
        );

        // EncoreMP spell replacement trial end

        std::stable_sort(spellsToSort.begin(), spellsToSort.end(), sortSpells);

        for (const ESM::Spell* spell : spellsToSort)
        {
            addSpell(*spell);
        }

        spellsToSort.clear();

        updateLabels();

        // Canvas size must be expressed with VScroll disabled, otherwise MyGUI would expand the scroll area when the scrollbar is hidden
        mSpellsView->setVisibleVScroll(false);
        mSpellsView->setCanvasSize (MyGUI::IntSize(mSpellsView->getWidth(), std::max(mSpellsView->getHeight(), mCurrentY)));
        mSpellsView->setVisibleVScroll(true);
        mSpellsView->setViewOffset(MyGUI::IntPoint(0, startOffset));
    }
```

**What this change does:**    
This function has been updated to look for spells with the @ prefix in the game files (ESPs, ESMs).    
If a spell with the prefix @ is found, e.g. a spell with the ID "@fireball", then the spell buying menu will now automatically hide the original spell, "fireball" in this case, and display the @ prefix variant instead.   

**Example:**    
A merchant sells the spells "fireball" and "levitate". In an ESP file you have made a custom spell with the ID "@fireball".   
When the player goes to buy spells from that merchant they will see in the merchants spell list the original "levitate" spell, but they will now no longer see the original "fireball" spell, that spell will be automatically removed and substituted for the spell with the ID "@fireball".    

**What problem is this trying to solve?**    
Updating the spell costs via an ESP file works for custom spellmaking (any potions, spell, or enchantments the player makes will use those custom values) but it does not affect already existing spells in the game files.

If you update the spell effect cost for poison damage to be lower, any spells the player makes will obey the new cost - but any pre-made spells the player buys will use the base game magicka costs for those spells.

This means that when custom spell costs are used, the spell buying menus will sell comparatively cheap or over costed spells, disrupting the game balance.

A potential solution to this would be just to update the costs of all existing spells, however just doing that introduces some problems... 

If you manually updated the cost of the spell "Poisonbloom", from 39 to 20 magicka, this would correctly update the magicka cost of the pre-made spell when the player buys it from a merchant, but it would have two significant undesirable effects on the game world,

- **[Issue one]** Every NPC/creature using the spell "Poisonbloom" will now be paying the reduced cost (20 magicka) and so have twice as many casts as the game designer intended, and find the spell much easier to cast (making effects that lower enemy spell success much less useful)    
	- The same is true in reverse, increasing the cost causes even more problems - creatures/NPCs can end up with spells they cannot possibly cast due to increased costs
	- In practise this is the most serious issue

- **[Issue two]** Most NPCs in the core game, and in many mods like tamriel rebuilt, do not have their spells assigned to them manually, and instead rely on a hidden system which selects spells for them based on their skills, magicka, and the cost of the spell
	- This is a core feature of Morrowind/the creation kit - developers/modders can make an NPC and select for them to auto-generate their spell list, which will result in a selection of level appropriate spells
- **[Issue two continued]** However this auto-generation logic means that another consequence of changing pre-made spell costs is that some NPCs will now spawn with different spell lists,
	- The core engine's auto spell selection logic will always try to find the most costly spells that the NPC can still comfortably cast (based on skill) and that they have enough magicka for a few casts of
	- So for example if an NPC would normally know the spell "Summon Ancestral Ghost" (costing 21 magicka) and you manually changed that spell cost to 40 magicka, that NPC may now no longer spawn with that spell at all (if the new cost is now higher than their maximum magicka, or if the engine determines that it is now too difficult for them to cast based on their conjuration skill)
	- But the spell list auto-selection logic would still look for spells to fill their spell list, so that NPC may instead spawn into the game with another conjuration spell that costs round 20 magicka, e.g. "Saintly Word" (23 magicka) - because the engine looks for a spell they can comfortable cast based on their skill
	- Now without meaning to, you've changed your ghost summoning NPC into a turn undead NPC!

Problem 2 is a bit more random in how it plays out. Some NPCs are locked, so they won't update spell lists (but they would still experience problem 1), some aren't, and it can also depend on whether you open the ESP files and click on the spells/NPCs after the costs have been changed (or whether you have another ESP file open at the same time that changes spell costs... etc etc).

In short, changing the core spell costs always results in problem 1, and will sporadically cause problem 2 (based on the settings the author chose for the NPC, and how the mod file has handled since it was downloaded)

**How does this solution help?**    
By looking for spells with the prefix "@" (an arbitrarily selected and unused character in Morrowinds spell IDs) and then substituting what the player sees on the spell buying menu with those spells, it is possible to leave the original spells completely unchanged and to still introduce custom costed pre-made spells for players.

An example:    
Take the spell "fireball": 5 magicka, 2-20 points in 5ft on target    
Now you make this spell in the creation kit    
"@fireball": 10 magicka, 2-20 points in 5ft on target    

When the player goes to buy spells from a merchant, if that merchant would have sold the player the fireball spell, they will now sell them instead the "@fireball" spell. So the player sees, buys, and uses the 10 magicka version of the spell, and every NPC/creature in the game still gets the original 5 magicka version of the spell!

This way you can introduce completely custom costed spells that appear in the spell buying menus without having any affect on the existing spells.

**Menu behaviour**
- When the player has either the normal spell ID in their spell book, or the @ prefix variant then the merchant will no longer offer to sell the player that spell
- It is okay if only some of the spells for sale in a list have @ variants, the engine will fall back to offering the default spells if any do not have variants

    
**Rules and limitations**    
There are a few things you have to be aware of when making or adjusting custom spells using the special @ prefix,
- Morrowind has a 31 character limit on spell IDs, so you cannot add an @ prefix to a spell whose ID is already 31 characters long. Thankfully this is a non-issue in all of the core game and tamriel rebuilt at the moment
- Any spells made like this must be set **not** to auto-calculate their costs in the creation kit. If you set them to auto-calculate, your custom @ spells ID variants will become available to NPCs and pollute their auto-generated spell lists
- The ID of the spell added to the players spell book this way will be an @ variant - if you want to add or remove such a spell with the ingame console you have to put the ID in quotation marks, as the console doesn't like strings that start with @
	- `player->removespell "@fireball"` will work
	- `player->removespell @fireball` will not
- Content that checks if the player has a specific spell in their spell book (e.g. the Telvanni quest "wizard spells") will not count the @ variants. Luckily at the moment this is not an issue in the base game (as the spells needed for that quest are not affected) and to my knowledge not an issue in tamriel rebuilt. If it is, you can manually add the correct spell IDs to your spell book, or as a mod patch update the spell ID checking script to also accept the @ variants 


## 31, Gameplay settings

**How they are implemented**    
- Settings are read from the user config file in openMW, however tes3mp changes this so that settings are pushed from the server `config.lua` file into the engine at launch, over-riding any user settings.    
- Default fallback values are added to the `defaults.bin` file.
- The engine looks for settings in the order: 
	- [1] User settings (via lua pushing the config file values into the engine)
	- [2] User settings that have been cached in the OpenMW `settings.cfg` file
	- [3] Defaults settings, acting as fallback values
	- [4] If none of these can be found, the engine throws a (fatal) error
- It is neccessary to add any setting to the `defaults.bin` file to prevent fatal errors, in the event that the server config file omits a setting
	- Settings are added to the `defaults.bin` file by editing the `settings-default.cfg` file in the source files, which is used to build the `defaults.bin` file during compiling
	- Where you add the settings in that file matters, as the section heading acts as part of the setting key when they are looked up. For EncoreMP all the settings have been placed in the [Game] section
- Since the user setting values are pushed from the `config.lua` in the server folder, all adding the user settings involves is adding a new row to the `config.gameSettings = {` section of that file
	- Be aware if you modify this further that the `config.lua` file is not part of the build when you compile, so you need to paste the most up to date `config.lua` file into the final version of any build you do 

**List of all settings**
- `two handed weapons receive an accuracy penalty` - Boolean
	- If true: 2 handed weapons take the -15% to hit penalty
	- If false: 2 handed weapons recieve no penalty to their hit chance 
- `staves receive accuracy bonus instead of two handed penalty` - Boolean
	- If true: Staves recieve the +20% to hit chance bonus
	- If false: Staves use whatever modifier applies to other 2h weapons (if 2h accuracy penalty is on, staves take the -15% hit chance penalty, if that setting is also false then staves take neither the +20% bonus nor the -15% penalty) 
- `global XP gain multiplier` - Float
    - This value is multiplied by the XP earned for all skills
    - 1.0 by default 
    - Examples
        - 1.0 = all XP gain is multiplied by 1 (no effect)
        - 0.2 = all XP gained is reduced to 20%
        - 1.5 = all XP gain is increased to 150%
    - Cannot be set to 0 or to negative values
        - If you do this, the engine will default back to normal (1.0) XP gain to prevent errors
    - If you want to effectively disable XP gain globally set it to something like 0.00001
    - Otherwise no upper or lower limits
- `skill books have level limit` - Boolean  
	- True: Skill books do not advance a players skill past 90
	- False: Base game behaviour, skill books work at any level
- `use new constant effect difficulty logic` - Boolean
	- True: Use the new Encore logic for constant effect enchantment difficulty, using player base skill
	- False: Use the base game difficulty logic for constant effect enchantments
