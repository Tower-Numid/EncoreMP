
```
EncoreMP V0.80 beta release - Forked from tes3mp V0.8.1
```

This project, EncoreMP, is a fork of tes3mp (V0.8.1), https://github.com/TES3MP

Asides from the mechanical changes listed below, and the code changes detailed in the "EncoreMP V0.80 compiling notes" file, all of the code used in this project is unchanged from tes3mp.

Information on the tes3mp project (V0.8.1) has been copied below verbatim from the tes3mp project readme, please support the original project if you enjoy this work:

---

TES3MP project information
======

Copyright (c) 2008-2015, OpenMW Team  
Copyright (c) 2016-2022, David Cernat & Stanislav Zhukov

TES3MP is a project adding multiplayer functionality to [OpenMW](https://github.com/OpenMW/openmw), an open-source game engine that supports playing "The Elder Scrolls III: Morrowind" by Bethesda Softworks.

* TES3MP version: 0.8.1
* OpenMW version: 0.47.0
* License: GPLv3 with additional allowed terms (see [LICENSE](https://github.com/TES3MP/TES3MP/blob/master/LICENSE) for more information)

Font Licenses:
* DejaVuLGCSansMono.ttf: custom (see [files/mygui/DejaVuFontLicense.txt](https://github.com/TES3MP/TES3MP/blob/master/files/mygui/DejaVuFontLicense.txt) for more information)

Project status
--------------

[Version changelog](https://github.com/TES3MP/TES3MP/blob/master/tes3mp-changelog.md)

As of version 0.8.1, TES3MP is fully playable, providing very extensive player, NPC, world and quest synchronization, as well as state saving and loading, all of which are highly customizable via [serverside Lua scripts](https://github.com/TES3MP/CoreScripts).

Remaining gameplay problems mostly relate to AI and the fact that clientside script variables need to be placed on a synchronization whitelist to avoid packet spam.

TES3MP now also has a [VR branch](https://github.com/TES3MP/TES3MP/tree/0.8.1-vr) that combines its code with that of Mads Buvik Sandvei's [OpenMW VR](https://gitlab.com/madsbuvi/openmw).

Donations
---------------

You can benefit the project by donating on Patreon to our two developers, [David Cernat](https://www.patreon.com/davidcernat) and [Koncord](https://www.patreon.com/Koncord), as well as by supporting [OpenMW](https://openmw.org).

Contributing
---------------

Helping us with documentation, bug hunting and video showcases is always greatly appreciated.

For code contributions, it's best to start out with modestly sized fixes and features and work your way up. There are so many different possible implementations of more major features – many of which would cause undesirable code or vision conflicts with OpenMW – that those should be talked over in advance with the existing developers before effort is spent on them.

Feel free to contact the [team members](https://github.com/TES3MP/TES3MP/blob/master/tes3mp-credits.md) for any questions you might have.

Getting started
---------------

* [Quickstart guide](https://github.com/TES3MP/TES3MP/wiki/Quickstart-guide)
* [Steam group](https://steamcommunity.com/groups/mwmulti) and its [detailed FAQ](https://steamcommunity.com/groups/mwmulti/discussions/1/353916184342480541/)
* [TES3MP section on OpenMW forums](https://forum.openmw.org/viewforum.php?f=45)
* [Discord server](https://discord.gg/ECJk293)
* [Subreddit](https://www.reddit.com/r/tes3mp)
* [Known issues and bug reports](https://github.com/TES3MP/TES3MP/issues)

# End of tes3mp project information

---

# EncoreMP Introduction

**What is EncoreMP?**

This is a gameplay modification to morrowind, with changes made at the engine level. It has been forked from tes3mp. As a branch of tes3mp, this is multiplayer compatible. 

It has been designed with maximum mod compatibility in mind, and most especially for full compatibility with the tamriel rebuilt project. It does this by changing as little as possible via the ESP file, and by making all the engine level changes as content agnostic as possible.

**How is this different to other gameplay overhauls?**

This project hosts almost all of it's changes in the games engine, not in an ESP file. So this should be compatible with almost all new content mods. It adds no new content, and makes no graphical changes.

**What is the tone of the overhaul?**

This tries as much as possible not to break from the sprit of the original game. 

There are some new mechanics, and a lot of balancing changes, but overall the aim is for this to feel like playing Morrowind did twenty something years ago when it came out.

As a Beta version it is in need of playtesting and feedback, and currently the economy aspect is likely the most punishing change - but it is not meant to be harder just for the sake of it.

**What does it change?**

This is a brief summary of the changes made, for more details see the mechanical changelog below, not everything is listed here:

(Unless stated, all mechanical changes affect the player only)

**Skills:**
- Enchanting and alchemy have been overhauled/balanced
- Acrobatics now lets you climb! Past a certain point your acrobatics skill lets you climb steeper and steeper slopes, up to an 89° angle at high skill
- Your weapon skills now contribute to your damage dealt, not just your hit chance, and weapon accuracy has been revised
- Ranged weapons are more accurate, and your ranged weapon skill helps you recover arrows more often as it increases
- Unarmoured is overall stronger, and scales with some attributes
- Armorer has had a massive rework, it is much more rewarding to level it up now
- Athletics increases your swim speed quite a bit more than it does in the base game
- Mercantile now gains XP from the value of items sold, rather than from haggling
- Bribing NPCs is harder and less rewarding (but 1000g bribes are the same, that big a bribe is still enough to make anyone happy)
- More expensive spells now reward you with more XP when you cast them
- Pickpocketing has been overhauled, and it is now possible for most reasonably priced items (provided you can hide successfully)
- Many magic effect costs revised
- Also see the ESP companion file for GMST changes

**General:**
- A revised difficulty system that affects player magic damage done and taken, as well as updating how it affects melee damage done and taken (**player summons are the only thing that does not currently scale with difficulty, that is being worked on**)
- XP gain slows down at higher skill levels
- Training skills becomes much more expensive at high levels
- Skill books stop granting skill increases at skill level 95 and above
- The player can't get above 60% magic resistance any more (much harder to exploit now!)
- The willpower attribute has been slightly buffed

**Quality of life:**
- The 'repairing equipment' sound has been turned down to 50% of it's original volume!
- Enchanted weapons no longer display the "out of charge" message when you attack with them whist they are out of charge

**Project version info**
This is the first public (beta) release of EncoreMP: V0.80

It requires the ESP file `TODO` to function as intended (this is for balance reasons, and due to some changes to how the GMSTs operate). See the ESP companion file for more details on these changes.

Hosted at: https://github.com/Tower-Numid/EncoreMP


# Mechanics changelog

1. Climbing
2. New difficulty system
3. Enchanting overhaul
4. XP gain changes
5. Training cost changes
6. Resist magicka cap
7. Melee combat changes
8. Hand to hand combat changes
9. Ranged combat changes
10. Armour rating changes (various)
11. Armorer overhaul
12. Mercantile overhaul
13. Alchemy overhaul
14. Pickpocketing overhaul
15. Swimming
16. Willpower buff
17. NPC spellcasting engine fixes
18. Misc changes

## 1, Climbing

**Acrobatics skill now lets you climb**
- The players acrobatics skill now lets them climb increasingly steep surfaces by attempting to walk up them
- This is not true Daggerfall style wall climbing, but everything that is not a vertical surface is now climbable with enough skill
- This feature is tied to the players **unmodified** acrobatics skill, so that even if your acrobatics skill is drained or buffed, you do not change your ability to climb. This was done intentionally to avoid unintended physics behaviour when the players acrobatics skill changes mid-climb

**Climbing angles**
- If your skill is 30 or below, then you have the base climbing angle of 47° (no change from the base game)
- If your skill is between 30-60 then you add `(skill-30)/3` degrees, so that you scale from 47 to 57° being climbable at 60 skill
- If your skill is above 60 then you start adding 1° per skill level (in addition to the 57° you will have reached so far by being 60), reaching the cap of 89° being climbable at 92 skill.

**What that means in practise**
Below are some examples of how these changes play out,
-  47° - Reached at skill 30, base game behaviour
-  57° - Reached at skill 60. This is a very noticeable improvement, many base game hills can now be climbed if you search around for a shallow enough incline. This angle increase has more of an effect than the small number change might suggest
- 67­° - Reached at skill 70. The majority of exterior obstacles are now scalable in the base game with a little effort finding a route. Not enough to climb buildings in urban areas (unless they have sloped sides) but more than enough for most wilderness trekking without having to rely on levitate
- 77° - Reached at skill 80. Practically any exterior obstacle is now scalable, although not necessarily in a straight line (some very sleep stopes may require some moving around to find a path still). A lot of spacious interiors (such as those using the cave interior pieces with sloping sides) are climbable as well
- 89° - Reached at skill 92. Anything non vertical is now climbable (technically you could encounter a slope with 89.9° and not be able to climb it)

## 2, The new difficulty system

The difficulty system has been completely reworked and re-balanced.

It now scales ALL player damage with difficulty, both dealt and taken (magic damage, fatigue from hand to hand, reflected damage, etc) with the exception of player summons and allies as of V0.80. Summons and allies will be added to the difficulty scaling system post release.

For ease of balancing during development, the game was also moved from a 'sliding bar' type difficulty, where any integer value can be used as a difficulty setting, to a a 'tiered' difficulty system like in later games.

This version (V0.80) has been tuned for co-op multiplayer, so it more heavily reduces damage done overall.

**The tier system**

| Tier           | Melee & other [1] dealt (%) | Melee taken (%) | Magic & other [2] dealt (%) | Magic & other [2] taken (%) |
| -------------- | --------------------------- | --------------- | --------------------------- | --------------------------- |
| 1: Apprentice  | 100                         | 100             | 100                         | 100                         |
| 2: Journeyman  | 75                          | 150             | 85                          | 125                         |
| 3: Master      | 50                          | 200             | 70                          | 150                         |
| 4: Grandmaster | 30                          | 300             | 50                          | 200                         |
| 5: Agent       | 20                          | 400             | 33                          | 250                         |
| 6: Nerevarine  | 15                          | 500             | 25                          | 300                         |
 
[1] Both melee and on-hit enchantments scale using these values

[2] Both magic damage and fatigue damage dealt from hand to hand scale using these values

Comments
- Magic damage taken only affects damage dealt by non-player actors, so drinking potions or using self damaging scrolls will not cause you to take any more damage. Nor will you take more magic damage from scripted effects or environmental sources such as traps
- For balance reasons, anything reflected onto the player deals 1x damage regardless of difficulty, but anything reflected onto non-players receives the magic damage step down
- Physical damage is reduced by your armour before difficulty modifiers apply, so you don't need more armour to reach the maximum damage reduction, but it becomes a lot more important when you are being hit for 5x damage! (the same is true in reverse for enemies, they apply armour first and then modify the damage by tier)


**Changing difficulty settings**
The new difficulty tiers are controlled by the global difficulty score in the server config file as follows,

| Server config value | Tier           |
| ------------------- | -------------- |
| 0 or less           | 1: Apprentice  |
| 1-50                | 2: Journeyman  |
| 51-100              | 3: Master      |
| 101-150             | 4: Grandmaster |
| 151-200             | 5: Agent       |
| 201+                | 6: Nerevarine  |

- There is no difference in difficulty within a given tier, e.g. setting it to either 201 or 999 will have the same effect (Nerevarine difficulty), and setting it to 52 or 96 would both give master difficulty
- The only reason number ranges were kept was so that it would be easier to go back to a sliding scale system later on if needed

## 3, Enchanting overhaul

**Every item now has a usable enchanting capacity**
- All items in the game with an enchantment capacity now have between roughly around 30-120 points of capacity (some still go over 120)
	- This was done by taking the actual item enchantment capacity from the game ESM/ESP file, and running through it an exponential function that converts it non-linearly to the new values.
	- Very high capacity items (such as the Daedric tower shield) end up nerfed a little compared to the core game, this could be changed in future versions though.
	- The break-even point in the new system is items with a base game enchanting capacity of 100-110. These are also 100-110 in the new system, and only above this point do the gains start to drop off.

**Your enchanting skill lowers the on-use costs less than before**
- Enchanting 'on-use' costs are still reduced by skill, but it's now a non-linear reduction. With some special rules for very cheap to cast items (to stop them ever costing less than 1 to cast)
	- Overall enchanting skill reduces the cost to cast enchanted items less than it does in the base game, which prevents a lot of enchanting exploits.
	- Depending on the initial cost of the effect, you can expect things to cost around 40-60% less to cast at 100 skill.
	- Beyond 100 skill there are only marginal gains, with a skill level of 200 only reducing on-use costs down to about 35% in most cases
	- Cheaper effect reach their minimum 'on-use' costs at lower skills, compared to more expensive ones

**On-strike enchantments are even cheaper to use**
- 'On-strike' enchantments follow the above logic, but are also further reduced by about 75%
	- This was done to pair with the limits put on weapon enchantment strength, and also as a QoL change so that you don't have to be as miserly with your charged weapons when cutting through weak enemies

**Not all spell effects use the same amount of an items enchanting capacity**
- How much of an items capacity that an enchantment uses up now also depends on the spell school, and on some specific spell effects, for balancing reasons
	- All destruction and restoration effects have doubled capacity costs
	- For scrolls only, all alteration conjuration effect costs have halved capacity costs
	- All instances of Dispel, Restore attribute, Absorb health, Absorb fatigue and Resist paralysis were doubled in capacity cost
	- All instances of fortify attribute were halved in capacity cost
	- For constant effects only: Shield, Chameleon, Sanctuary, Restore Fatigue, Fortify attribute, and Resist Paralysis have an additional x1.5 capacity cost multiplier added to them
		- All of these school and effect specific changes were done for balance reasons for the V0.80 beta release, they may change in future
- In addition on-hit effects were further tuned for balance reasons

**Enchanting success rates**
- Your enchanting success rate still follows the core game difficulty logic, but with these additional changes:
	- Enchantments with an equivalent magicka cost below 5 points get a flat +25% success chance
	- Enchanting scrolls gives a flat +25% success chance
	- All enchantments (except for constant effect, see below) get harder to make when they cost 20 or more points, and significantly harder to make beyond 25 points. 
	- At 100 skill you will struggle to make something 25 points and beyond, but you can still can with luck, and some buffs. This was done to prevent artefact quality items being made too easily.

**Making constant effect items**
- Constant effect follow a special rule, which was a bit of a stop-gap solution for the beta, to allow them to be possible but also more strictly gated to high skill levels.
	- All constant effect enchantments you attempt to make now require an **unmodified** enchanting skill of 75 or more
	- Between 75 and 100 skill you can make larger and larger capacity constant effect enchantments (exceeding the allowed capacity, based on skill, will drop your success chance to 0%)
	- At 100 skill you can enchant any capacity of constant effect

**Enchanting arrows**
- If the Openmw multiple ammunition enchanting setting is turned on (in the server config file), then you will automatically enchant ammunition in batches of up to 20
	- You will find it slightly harder to enchant 20 at once, but not prohibitively so
	- Due to how the Openmw logic works, with this setting on if you just enchant one arrow at a time you will actually get a boost to your enchanting success rate, but nothing game breaking
	- This was left in as a way of making special mega-arrows on demand
	- There is a visual bug where it can display an arrow as having 0 charge, but from testing the effects seem to trigger regardless
	- The value of the Openmw setting should not matter, as this new behaviour is partially hardcoded to stacks of 20. But just in case, set the value in the config file to `0.5`, as this was what was used during development and testing

**Cost of enchanting services**
- Enchanting service prices now scale non-linearly with the point cost of the enchantment. It is overall much more expensive to buy high cost effects, and some special rules were added to handle edge cases for the beta release
- Overall I am least happy with this section, it was one of the first changes made and was done very crudely to allow for balancing. This will certainly be revised in future releases. The service cost changes may be too punishing as is,
	- Enchantments costing more than 20 points begin to increase in price massively, and beyond 25 or 30 points depending on the enchantment type (on-hit, on-use, etc) it becomes "impossible" to afford
	- The "impossible" cost was crudely implemented by a flat 5 million gold cost to enchantment values that exceed these amounts. In theory if you have that much gold you can make these mega enchants. But this will never be a problem during normal play
	- Scrolls cost about 4k to make a single 20 point effect
	- On-hit costs about 100k to make an on-strike 20 point effect (this is roughly the strength of most artefact on-strike effects)
	- On-use costs about 75k to make an on-use 20 point effect
- Constant effect costs behave differently, and the price increases roughly mirror the allowable cost break points determined by player skill. 
	- There is a flat starting cost of 70k for any constant effect. The first 30 points will cost a total of about 100k, and then it ramps up non-linearly from there. A single 100 point CE will costa bout 400k, and beyond that point it becomes "impossible" with the flat 5 million gold cost increase being applied


## 4, Player XP gain adjustments

This was tuned to delay the point where your character reaches the 'power threshold', and most of the game becomes trivial. 

It is now slower to level very low level skills than in the base game (previously at skill level 5 you could often level up with only one or two actions), and skills require progressively more XP at higher levels.

**General**
- XP gain values have been adjusted for most skills as per skill the ESP changelog
- In the base game you needed XP equal to your skill level to level up
- Now skills require a minimum of 30xp to level, so all skills below 30 now advance slower. This was done to make your initial skill choices more meaningful, and also in general with the rest of the changes you should find it easier to level most skills from 5-30 without having to pay for training
- XP gain is reduced at high skill levels with the following step-down multipliers:
	- Below 50 = x1
	- 51-60 = x0.8
	- 61-70 = x0.65
	- 71-80 = x0.55
	- 81-90 = x0.4
	- 91-100 = x0.33

**Spellcasting**
Part of the reason magic skills feel slow to level in morrowind is that you do not gain any more XP from casting more powerful spells, but naturally as you level you tend towards using more expensive magic. The result is that by playing normally you actually earn less XP as you become more powerful.

As a partial fix you now gain more XP from spellcasting as the spells magicka cost increases.

- For spells that cost 5 or less magicka, gain normal XP
- For spell that cost more than 5 magicka you get a multiplier to your XP as per the equation below, where x is the spell cost and y is the XP multiplier:
	- `y = 0.089x + 0.56`
- Example XP multipliers by spell cost:
	- 10 magicka, x1.43
	- 15 magicka, x1.87
	- 20 magicka, x2.31
	- 30 magicka, x3.19
	- 40 magicka, x4.07
	- 50 magicka, x4.95
 
## 5, Training costs and skill book adjustments

- Skill books no longer grant a skill increase at skill level 95 or above
- Training skills is overall more expensive, and the price now increases non-linearly with your skill level
- Pricing behaves is a little more expensive up to skill level 20, but with a minimum gold cost now of around 100g (before mercantile discounts apply). 
- Beyond level 20 the cost of training a skill begins to increase noticeably
- All of these changes respect the GMST (`iTrainingMod`), which is left at 10 by default. To change the prices the GMST can be adjusted as normal, and the non-linear pricing system will adjust accordingly (for example if you want to half the below table, set that GMST to 5)

| Skill  level | Cost (aprox.) before mercantile reductions | Base game cost |
| ------------ | ------------------------------------------ | -------------- |
| 10           | 190                                        | 70             |
| 20           | 290                                        | 140            |
| 30           | 540                                        | 210            |
| 40           | 1000                                       | 280            |
| 50           | 1500                                       | 350            |
| 60           | 3000                                       | 420            |
| 70           | 4500                                       | 490            |
| 80           | 6500                                       | 560            |
| 90           | 9000                                       | 630            |
| 99           | 14500                                      | 697            |

## 6, Player 'resist magicka' cap

- Magic resistance now provides no benefit to the player beyond 60%. This is after accounting for weakness to magicka, which negates it 1:1 as in the base game, so there is still a reason to stack it above 60 if you have or expect to run into that effect. There is no changes to how it works for NPCs or creatures.
	- This was done purely as a design choice and for balancing reasons, as otherwise 100% MR trivially negates most negative effects in the game
	- The player will still see on their UI that they have magic resist values above 60%, but this is a display issue only and it no longer provides any mechanical benefit
	- Enemies will still behave as if the player has immunity to magicka once they reach 100% MR, even though that amount no longer gives the player immunity (in the base game, enemies will not even attempt to cast effects on you which you can fully resist)
	- It was decided to leave this behaviour in, as otherwise NPC/creature AI would have to have been modified, which could cause unexpected behaviour (especially when an AI is fighting another AI, like a summon or an ally). This may be resolvable in future.

## 7, Melee combat changes

These apply to all melee attacks, the accuracy also applies to hand to hand, but otherwise hand to hand has it's own damage logic detailed in it's section

**Weapon accuracy**
- Melee accuracy now starts higher at very low skill levels (the minimum in practise is about 15% against most low level enemies), and reaches an overall slightly lower value at 100 skill
	- At 100 skill, against the strongest enemies, your hit chance is about 90% with mid fatigue, 108% with max fatigue, and only 72% when your fatigue is empty
	- This was done to smooth the entire skill out, low levels are more playable now and high levels stop effectively auto-hitting beyond skill 60-70 (which made weapon skill past this point feel redundant)
- However, **all two handed weapons** (with some exceptions in the weapon type changes below) now have a -15% chance to hit
	- This was done to make the choice between 1h and 2h weapons more meaningful, and to make 2h weapons something that need a little more skill to use well

**Weapon damage**
- Your strength attribute now contributes half as much to weapon damage bonuses and penalties
	- For example 100 strength now adds +25% damage to weapon attacks, instead of 50%, and 1 strength is now -25% damage instead of -50% damage
- Your weapon skill now contributes to your damage done with weapons (it had no effect on weapon damage in the base game, only accuracy)
	- It follows the same logic as strength, at 100 weapon skill you get a +25% boost to damage which stacks with the strength bonus, at 1 skill you get a -25% damage penalty
	- For example in the new system, if you have 100 strength and 50 skill, you get +25% damage boost
	- If you have 100 strength and 100 skill you get the original +50% damage boost
	- With 50 skill and 1 strength, you now get a -25% damage modifier, and with 1 skill and 1 strength you get a original -50% damage modifier

**Weapon type benefits**
- All weapons now have an additional mechanical benefit, depending on what type they are
	- **Short blades** have a +10% accuracy boost (equivalent to about 15 skill levels)
	- **Spears** have a +10% accuracy boost and do not take the -15% to hit that all other 2h weapons now do
	- **Long blades** gain additional damage from your agility as well as your strength. This behaves like the strength/skill changes above, but there is no penalty for being below 50 agility. For example if you have 100 strength, 100 agility, and 100 skill you now get a +75% increase to damage with long blades
		- If you had 1 agility, 100 strength, and 100 skill, you still get the +50% damage increase from strength and skill
	- **Axes** are the same as long blades but they use your endurance above 50 instead of agility
	- **Maces** are the same as long blades but they use strength above 50 instead of agility (in addition to the normal benefit from strength that all melee weapons get)
		- So with a mace, at 100 strength and 100 skill you do +75% instead of +50% damage
	- **Staffs** (a sub-set of maces) have a +20% accuracy boost, and do not take the -15% accuracy penalty that other 2h weapons do
		- This was done by giving the bonus to all weapons classed as `BluntTwoWide` in the ESM/ESP. This could lead to minor balancing issues if modded content is adding powerful 2h maces to the `BluntTwoWide` category rather than the standard, but as of writing these notes this is not an issue in all of the core game and all of tamriel rebuilt


## 8, Hand to hand combat changes

**Health damage done**
- Health damage done by hand to hand attacks was increased by adjusting the GMST `fHandtoHandHealthPer`, up to 0.4, from 0.1
	- This GMST value is multiplied by the fatigue damage that your hand to hand attacks deal to determine the amount of health damage that enemies take when you are damaging health with hand to hand (e.g. when they have been knocked down, or are paralysed)

**Damage done - general**
- Damage done has been increased at the low end, reaches parity with normal behaviour at about 40 skill, and scales to the same final value at 100 skill
	- Beyond 100 skill you now gain slightly less damage per skill level
	- The formula change was from: `damage = skill` (before the attack strength multiplier), to: `damahe = (skill x 0.9) + 10`
	- This makes low levels slightly less pointless, they're still not good, but it is somewhat more reasonable to go punching mudcrabs now

**OpenMW strength scaling behaviour change**
- The OpenMW setting for scaling your hand to hand damage with your strength was revised to behave like strength does for weapon attacks in the base game. The new behaviour is:
	- 50 strength: no modifier
	- 100 strength: +50% damage modifier
	- 1 strength: -49% damage damage modifier
- It is recommended that this setting is toggled on in the server config file. Werewolves haven't been balance tested, so it is recommended to turn this on and set it to '2' which is strength scaling for hand to hand, excluding werewolf form
	- Also note that unlike all the other changes here, this one does affect NPCs, so toggling that setting on will still affect NPC hand to hand damage (as in core OpenMW)
- The reason for the change to OpenMW behaviour here is that it resulted in unusual behaviour at low strength values, and resulting in a very high scaling with strength if you kept buffing it past 100

**Comment on how hand to hand scales with difficulty**
- After some tested it was decided that fatigue was better balanced if it scaled like magic damage does with difficulty, going up to 3x fatigue damage taken and down to 0.25x fatigue damage dealt
	- This was because the player cannot resist fatigue damage with armour, unlike health damage taken, so on higher difficulties it became impossible at 5x fatigue damage taken to reasonably go toe-to-toe with an unarmed NPC
	- Damage dealt was also found to be too low when it was scaled at the same rate as melee, since the player has to overcome an enemies natural fatigue regeneration
	- See the difficulty scaling section for the table of difficulty values

## 9, Ranged combat changes

**Accuracy**
- Ranged weapons follow the same logic as the melee accuracy changes, but also get a flat +20% hit chance

**Damage**
- Bows and crossbows scale their damage using the same new logic as melee does, half the bonuses/penalties come from your skill and half from your attribute. However bows and crossbows use your agility not your strength to increase damage
- Throwing weapons scale in a similar fashion using your strength and skill, but they reach 200% of base weapon damage at 100 strength and 100 skill instead of 150%. This was to help them stay a little more competitive into the late game

**Ammunition recovery**
- Non-enchanted ammunition is now recovered more frequently from enemy corpses as you increase in skill:
	- From 0 to 25 skill you recover ammunition at 1x the GMST value `fProjectileThrownStoreChance` (which is 25% by default, as in the base game)
	- From 25 to 100 skill your chance of recovering ammunition linearly increases from 1x the GMST value at 25 skill to 4x the GMST value at 100 skill
	- So if you are using the default GMST setting, you reach a 100% recovery rate of unenchanted ammunition at 100 skill
- Enchanted ammunition can now be recovered occasionally past 50 skill (this is not possible at all in base game) 
	- From 0-50 skill you have no chance to recovery magical ammunition
	- From 50-100 skill you go linearly from a 0 to 2x the GMST value chance to recovery magical ammunition, e.g. at 75 skill you have a 1x GMST chance to recovery magical ammunition
	- For balance reasons, the function that controls this recovery rate caps the player skill at 100 for the purpose of calculating enchanted ammunition recovery rate. So even if you buff your skill into the hundreds, you will still be hard capped at an enchanted ammunition recovery rate of 2x the GMST value
- Both of these systems respect the GMST, changing it from the default value of 25 will cause all of the above to change as expected
	- e.g. changing the GMST to 10 would mean you end up with (at 100 skill) a 20% chance to recovery magical ammunition and a 40% chance to recover normal ammunition
- There are no issues with increasing the GMST value. If you end up with over a 100% chance to recover ammunition (e.g. by setting the GMST to 200), there are no bugs or unusual behaviour

## 10, Armour rating adjustments (player and creatures)

**Player equipment based armour ratings**
For the three armour skills (heavy, light, and medium) the equation used to determine player armour values below 30 skill was adjusted to be less punishing

* In the base game, your armour rating from equipment is equal to the base armour rating of the item multiplied by (your armour skill / 30)
* For example, previously at 5 skill in heavy armour wearing a full set of Dwemer heavy armour would give you 3 armour class instead of the 20 armour class you would get at 30 skill
* This was changed to be a little less punishing as a matter of taste, and also since low levels of skills now require more XP to advance
* The new logic is the items base armour rating multiplied by `(your skill + 5) / 35`, then once you reach 30 skill it behaves as in the base game
* Old vs new armour ratings (as a %) based on your skill:

| Skill | Old % rating | New % rating |
| ----- | ------------ | ------------ |
| 5     | 16           | 28           |
| 10    | 33           | 42           |
| 15    | 50           | 57           |
| 20    | 66           | 71           |
| 25    | 83           | 85           |
| 30    | 100          | 100          |

**Creatures armour ratings**
* All creature type entities (entities which are not classed as NPCs in the engine) in the base game had armour ratings of 0, except for any shield effects they might have had. A storm atronach and a mudcrab both had the same rating... of zero
* Now all creatures have 10AC as a baseline, which shield magnitudes are then applied additively to
* Creatures that are level 5 or above gain an additional +2 AC, for a total of 12
* Creatures that are level 10 or above gain an additional +5 AC, for a total of 15

This was done to make creatures a little more durable against physical attacks, but the numbers were kept low to maximise compatibility


**Player unarmoured skill**
- Unarmoured has been overall buffed a lot to help it be viable on high difficulties without having to rely on the base game trick of fortifying your skill past 100
- The buffs were also done to compensate for the fact that to use unarmoured you are giving up all the enchanted armour you find in the world that you could be wearing
- The previous logic was that unarmoured gave an armour rating equal to: `skill x skill x 0.0065`,
- The new logic gives higher ratings at lower levels, and allows your agility and speed attributes to both boost your unarmoured rating further
	- For skill levels 0 to 30, your unarmoured rating is `skill/3` (10 armour at 30 skill)
	- From skill levels 30 to 70, every level above 30 adds about 1.6 armour (75 armour at 70 skill)
	- From skill levels 70 and above, every level above 70 adds about 2.5 armour (150 armour at 100 skill)
- Your agility and speed modify this further if either are above 50, as a percentage modifier (there are no penalties for being below 50)
	- They each contribute the same % modifier above 50. For either attribute, every 2 points you have above 50 adds 1% to your unarmoured derived armour class
	- For example 100 speed and 50 agility gives you a 1.25x multiplier
	- 100 speed and 100 agility gives you a 1.5x multiplier
	- So at 100 skill, with 100 speed and 100 agility you end up with 225 armour rating from being completely unarmoured. It sounds good, but remember you are still giving up using all the enchanted armour pieces you will be finding in the world to get this
- The whole calculation for the player respects the GMST `fUnarmoredBase1` and assumes it has the default value of 0.1 to give the above armour scores

## 11, Armorer overhaul

This has been one of the most reworked skills so far. In the base game once you were able to reliably repair an iron sword, you could reliably repair anything and didn't benefit much from higher levels.

The following changes have been made,
- More expensive items are harder to repair now
- Your armorer skill now slows down the rate at which equipment loses durability in combat
- Better quality tools add to you repair success rate, as well as making you repair more per swing
- It costs a lot more to pay services to repair expensive items

**Skill slows the rate of equipment damage**
* All items worn by the player now degrade at only 25% of their normal rate once you reach 100 skill, and this is a hard cap of reduction which can be exceeded
* The formula is that your equipment takes (`skill x 0.075`)% less damage from combat
* This was done to to make it slightly easier to find and used equipment above your pay grade, and to make it less annoying to wear low durability items in the end game

**The value of an item determines how difficult it is to repair**
- The difficulty of repairing is not shown in game currently, but in future a UI element or message will be added in  to indicate when attempting to repair something is beyond your skill (like the 'lock too difficult' message in the base game)
- As in the base game, the amount you repair per swing is increases with your chance to succeed. So going from 20% to 50% success not only doubles your odds of repairing, but it also more than doubles how much you do repair when you succeed. Likewise sitting at a 5-10% success rate means you will be repairing very little even when you do succeed
- You can increase your odds by using better tools (see the section below) or by buffing your strength, luck, or skill
- Weapons are overall easier to repair until the very high end, as most characters can survive having their armour break, but not their weapon
- A 30-50% success rate is enough to maintain equipment reasonably, but you will need a lot of hammers at first

| Armour value   | Weapon value   | Minimum success rate | Skill for 30% success | Skill for 50% success |
| -------------- | -------------- | -------------------- | --------------------- | --------------------- |
| 0-100g         | 0-499g         | 20%                  | ~30                   | ~40                   |
| 101-499g       | 500-1999g      | 17%                  | ~35                   | ~45                   |
| 500-1999g      | 2000-4999g     | 15%                  | ~37                   | ~50                   |
| 2000-4999g     | Skipped        | 10%                  | ~45                   | ~55                   |
| 5000-19,999g   | 5000-19,999g   | 7%                   | ~60                   | ~70                   |
| 20,000-49,999g | 20,000-49,999g | 5%                   | ~70                   | ~80                   |
| 50,000g +      | 50,000g +      | 5%                   | ~80                   | ~90                   |

Comments:
- This system needs a lot of playtesting, I am wary of making armorer feel mandatory
- You should find that as a caster or someone using only light armour, you can get by without training the skill at all until the mid-game. Warrior types will need it a little more
- A big effect of all this is that finding an artefact at level 1 means you will have a very hard time maintaining it until you raise your skill

**Armorer tool quality modifies success rate**
- Since the new system requires you to have high armorer skill to maintain high end items, tools were buffed a little so that they could compensate for being at low skill levels
- Now, in addition to boosting the amount repaired per swing (as in the base game), the quality of an tool can also potentially raise or lower your effective skill when calculating your success rate
- The rule is: for every 0.1 quality above or below 1.0, add or subtract 1.5 skill levels to the attempt
- For example a grandmaster's armorer hammer (quality 1.7), adds an effective 10.5 skill levels to all repair attempts, and repair prongs (quality 0.5) remove an effective 7.5 levels (but you can never fall below the minimum success rates above)
- This should reward you for finding the best tools for the job, and let you maintain things above your level

**Repair costs are higher for more expensive items**
- This was technically already the case in the base game, but you would never be charged more than 1gp for point of item health, regardless of the items value
- Now that limit has been removed, and the new rule is (before mercantile discounts apply):
	- The cost to repair an item fully from 0% to 100% durability is 50% of the base cost of the item
	- So, each % of the items full durability you are repairing costs 0.5% of the items full value
- The repair cost is then multiplied by the GMST `fRepairMult` (which is 1.0) to determine the final price
- The repair costs may be set too high overall for the beta version (V0.80), if you find this to be the case try lowering the GMST to see how it feels (feedback is appreciated here, as with all the changes)
 

## 12, Mercantile overhaul

**The player now earns experience through the value of items sold, not by haggling**
- The player now earns mercantile XP not by haggling, but based on the value of items they sell (and how much they sell them for)
	- Earning XP through haggling was completely removed during development for ease of testing and balance, though it could be re-enabled in a future version
- You do not earn any XP from buying items, this was an intentional design decision as it opened up many ways to exploit the new system. This also could be enabled in a future version, but it is not top priority
- The player earns 1 experience for every 166gp they make in sales as of V0.80. So for example at skill 30 you need 30 experience to level, so you have to sell a total of around 5000g worth of item to level
- If this rate seems too low, or high, you can adjust it by changing the XP value for a successful bargain in the ESP file. This is at 0.3xp by default, as in the base game, and that gives you the gold to XP ratio described above
	- For example setting it to 0.9xp will triple the rate of XP gain and result in you only needing to sell about 1500g worth of items at level 30 to advance a level
- If you sell an item for less than the NPC offers you for it, you receive less XP proportional to how much you discounted the sale (as giving things away cheaply is not good merchant behaviour!)
- The value of items you receive in exchange for goods during a sale is also counted towards your 'sale value' for the purpose of XP gain. For example
	- If you have 1000g worth of gems, and the merchant makes an initial offer of 500gp - you stand to earn 3xp from the transaction (as the system uses the sale value of the items, not their base value)
	- If you decide to sell them cheaply, say if the merchant is nearly out of gold and you just want to get rid of them, for only 250gp, then you will still earn XP but only 50% of what you would have earned for selling them at full price (so 1.5xp)
	- However you could ask the merchant for 250gp, and 250gp worth of items in exchange for the gems. The engine will correctly add up the barter value (not base value) of everything you receive in return, and in this case award you full XP for the sale again (3xp)

**Disposition has less of an effect on mercantile interactions**
- The engine was changed so that an NPCs disposition being above or below 50 now only has one quarter of the effect it previously had on your mercantile bartering rate
- To go with this change, the GMST `fDispositionMod` was set to 0.25f, down from 1.0f in the base game. This GMST controls your ability to haggle based on disposition, lowering it to 0.25f makes it a 0.25x multiplier versus the base game as well

**Bartering and haggling rate caps (for balance and testing in the beta version)**
- Bartering rates (not haggling) are hard capped as follows:
	- You can never buy an item for less than 90% of it's base price, or be asked to pay more than 150% of its base price
	- You can never sell an item for more than 60% of it's base price, or be offered less than 20% of it's base price
	- These rates do not affect any services other than trading in a shop, so you can still get far better discounts on training, etc, as you level your mercantile
- Haggling rates have been hard capped at +- 10% the initial barter offer made
	- This was done to stop a potential exploit, where you otherwise can break even from buying/selling something by haggling, and endlessly circulate the item back and forth for free XP
	- This is not a very good solution, so this will likely be revised in future versions when this system is reviewed
 


## 13, Alchemy overhaul

This is a complete overhaul of the skill, changing nearly everything about it, but the end result is it still behaves and feels a lot like core alchemy.

**Potion strength overhaul**
This logic that determines potion strength was significantly changed to bring it in line with spellmaking costs. This helps balance potion making against other sources of magic, and prevent some unusual behaviour when effect costs are set very low or high in the ESP file

- Your alchemy factor is divided by 6 to determine an effects 'magicka budget'
- The engine then determines the effects strength, by calculating how strong a spell you could have made in the spell maker using that amount of magicka
- The system is designed to always produce effects which have a balance of duration and magnitude, with about half the budget being allocated to each
- The full magicka budget is given to each different effect in the potion, it is not spread out or shared between them. It is always an upside to have multiple positive effects on a single potion

**Ingredient value now affects potion strength**
The average value of the ingredients used to make a potion now affect the strength of the effects (by modifying your alchemy factor) as follows:
- If the average value of the ingredients is below 5g, then your alchemy factor is reduced by 30%
- From average ingredient values of 5g to 200g you receive a non-linear bonus to your alchemy factor.
	- For an average ingredient value of 5g, you get a +10 to your alchemy factor
	- For an average ingredient value of 10g, you get a +15 to your alchemy factor
	- For an average ingredient value of 25g, you get a +20 to your alchemy factor
	- For an average ingredient value of 100g, you get a +25 to your alchemy factor, and then an additional 1.1x multiplier
	- For an average ingredient value of 200g, you get a +30 to your alchemy factor, and then an additional 1.1x multiplier
- The logic interpolates between these values using a non-linear equation (so these are not hard break points, just examples), and past an average ingredient values of 200g the scaling speeds up and you get much larger bonuses (since there are very few, and often unique, ingredients worth more than 200g)

**The effect of mortar quality has been slightly reduced**
- The positive or negative multiplier you receive from mortar quality behaves as in the base game, but reduced by 50%
- For example, if you use a grandmasters mortar you would have received a 1.5x multiplier in the base game, whereas now you would receive a 1.25x multiplier
- The same is true for low quality tools. Using an apprentice's mortar would have given you a 0.5x multiplier in the base game, but now it gives you a 0.75x multiplier
- This was done to narrow the range of potential potion strengths for ease of balancing in the new system. It could be reverted in future

**The behaviour of other tools has been changed**
- The retort multiplies the duration and magnitude of positive effects by:
	- `(1 + (retortQuality/10))`
	- For example you would get +5% at 0.5 Quality, and +20% at 2.0 Quality
- The calcinator boosts both positive and negative effects, but negative effects are enhanced more so
	- Positive effects receive the same boost as with the retort (+5% at 0.5 Quality up to +20% at 2.0 Quality)
	- Negative effects receive three times that boost (+15% at 0.5 Quality up to +60% at 2.0 Quality)
- The alembic multiplies negative effects by:
	- `(1 - (alembicQuality*0.4))
	- For example you would reduce negative effects by 20% at 0.5 alembic quality, and you would reduce them by 80% at 1.5 alembic quality
	- There is a hard cap of a 90% reduction in negative effect strength which you reach at about 2.25 tool quality. This is only achievable if you use modded tools, and was only added to prevent unusual behaviour

Comments:
- Note that the modifiers from other tools are applied directly to both effect duration and magnitude, not your alchemy factor, so they have a larger impact than the numbers would otherwise suggest
- All of these modifiers from other tools stack with each other multiplicatively, not additively

**Order of operations for determining potion strength**
The order of operations in the new logic is:
1. Get the players alchemy factor as in the base game
2. Add or subtract from it depending on the quality (average gold value) of the ingredients being used
3. Apply the mortar tool strength modifier to the alchemy factor
4. Determine effect duration/magnitude using the new spellmaking costed system
5. Apply any other tools you are using as percentage multipliers directly to the effects duration and magnitude

**Potion value**
- The value of a potion you make can now never exceed the sum value of the ingredients used, otherwise it follows base game behaviour
	- This is an intentionally harsh cap for initial testing, as otherwise alchemy always has the potential to create infinite money via cheap ingredients

**Potion weight**
- Potions cannot weight more than 1.0, or less than 0.1, regardless of the ingredients used
- The new logic is to first calculate the base game weight (average of all ingredients used), then cap it 1.0 at the most, then reduce it by your `(alchemy factor / 100)` to a minimum of 0.1
- This way you will be able to make minimum weight potions very early on by using light ingredients, but you will need high skill to get heavy ingredient potions down to 0.1 (at 90 skill everything you make which will be 0.1 weight)

**Potions no longer stack**
- Drinking multiple of the same potion now refreshes the duration, instead of stacking multiple of the same potion on you - as spells behave in the base game
- This means if you drink 100 alcohol, you don't get absurd strength bonuses, or if you drink 10 healing potions with a hotkey, you don't become immortal due to all the stacking healing
- But you can still stack lots of different different potions if you want

**Cheap ingredients reward less XP**
- Potions whose average ingredient value is less than 5gp reward less XP. This was done to encourage using rarer and more expensive ingredients
- Otherwise potion XP remains flat as in the base game
- The reduction in XP becomes more severe as you level, and behaves as follows:
	- You earn 50% of the normal XP if your skill is 30 or below
	- You earn 25% of the normal XP if your skill is between 30 to 60
	- You earn 12.5% of the normal XP if your skill is between 60 to 90
	- You earn 5% of the normal XP if your skill is 90+

**Potion making success rate**
- The base success rate of potion making has been adjusted so that it is: 
	- `(30 + (2/3 of your alchemy factor))%`
- The result is that 
	- At 5 skill you have about a 40% success rate
	- At 30 skill you have about a 55% success rate
	- You reach 100% success rate at about 80 skill, depending on your attributes

**Ingredient value influences potion making success rate**
- The average value of ingredients used to make a potion now influence your chance of succeeding at making a potion
- Below 10 gold average value there is no change to your success odds
- Above 10 gold average ingredient value your success chance is increased by:
	- `8.4 + (avg value * 0.158)`
- In practise this translates to:

| Average ingredient value | Bonus to success rate |
| ------------------------ | --------------------- |
| 10g                      | +10%                  |
| 25g                      | +12%                  |
| 100g                     | +24%                  |
| 200g                     | +40%                  |

- The aim is to make it more rewarding to use expensive ingredients at low skill levels
- For example, if you make a potion using a gemstone worth 200g and some saltrice worth 1g, the average ingredient value would be 100.5g, and you would get flat +24% to your odds of making the potion


## 14, Pickpocketing overhaul

Pickpocketing has been reworked extensively, but stealth itself has not yet been addressed - so you will likely still have some difficulty with not being noticed. But if you can hide successfully, the value of what you can steal is a lot more reasonable now

**Pickpocketing difficulty overhaul**
- In the core game your chance of pickpocketing anything more than 100-200g was essentially zero, even at maximum skill, due to how heavily weighted item value was in the equations
- The difficulty check for pickpocketing no longer takes into account the victims attributes or skills (in the base game your chance of succeeding was lowered by both the items value, and by the NPCs own sneak, luck, and agility scores)
	- This was done to simplify the logic for testing, it could be added back in the future but it didn't feel like it added much to the game
- The logic has been adjusted so that you now have a roughly 50% chance to steal an item with a value of 5 times your pickpocketing term/skill
	- This is a 50% chance before the fatigue modifier applies, so at full fatigue (fatigue mod x1.25), you actually have a 62.5% chance to pickpocket something with 5x your skill/term in value
- Items which are above or below this value are harder or easier to steal according to this rule:
	- For every 5 gold the item is above or below the value which you have a 50% chance to steal, add or subtract 1.5% to your success chance
	- For example if you have a term of 40, you have a 50% base chance to steal an item worth 200 gold
	- If you tried to steal an item worth only 100 gold, you would have a base 80% chance to succeed. As you are trying to steal something 100g 'easier', the engine adds `(100 / 5) * 1.5` to your success rate
	- Trying to steal something that is worth 150g with a term of 40 would have a base success chance of 65% `+((50 / 5) * 1.5)`
- This may seem a little opaque at first, but see the table below for some guidelines, and see the change made to what can appear in the pickpocketing based on your skill - in short if you can see it, you can steal it,

| Player Skill | Player term [1] | Gold value at which you have a 50% chance to succeed (1x fatigue mod) | Gold value at which you have a 100% chance to succeed (1.25x fatigue mod) |
| ------------ | --------------- | --------------------------------------------------------------------- | ------------------------------------------------------------------------- |
| 10           | 17              | 85                                                                    | 0                                                                         |
| 20           | 28              | 140                                                                   | 15                                                                        |
| 30           | 39              | 195                                                                   | 70                                                                        |
| 40           | 50              | 250                                                                   | 125                                                                       |
| 50           | 62              | 310                                                                   | 185                                                                       |
| 60           | 76              | 380                                                                   | 255                                                                       |
| 70           | 90              | 450                                                                   | 325                                                                       |
| 80           | 104             | 520                                                                   | 395                                                                       |
| 90           | 118             | 590                                                                   | 465                                                                       |
| 100          | 130             | 650                                                                   | 525                                                                       |

[1] The players pickpocketing term is calculated as `(sneak skill) + (agility * 0.2) + (luck * 0.1)`. This table makes some assumptions about player attributes increasing along with their skills, and should be broadly correct if the player is trying to focus on the relevant stats as they play

**What appears in the pickpocket menu is determined by item value and the players skill**
- In the base game when you opened the pickpocketing menu of an NPC, what appeared was randomly determined by a dice roll regardless of it's value (your sneak skill made it more likely for any given item to appear, but the odds were completely independent of the items value)
- To represent NPCs guarding valuable items more closely, now you need a higher sneak skill to see more valuable items in the pickpocketing menu
- The rule is that: You can only see items in the pickpocketing menu if you have a base (before fatigue modifiers) 50% chance to steal that item
	- This way the player knows that if they can see something, they have a reasonable chance at stealing it without getting caught
- You can use the table above to see what value of items should appear at each skill/term level (the column which shows the amount you have a 50% chance to steal with a 1x fatigue modifier)

**Bug fix**
- The player no longer has to pass an extra detection check when closing the pickpocketing menu
	- This was a core game bug that meant when you stole something you had to pass the initial difficulty check, and then immediately another check just for closing the window
	- Fixing this (along with the GMST changes in the ESP file) means that the above table is your actual chance of stealing, no longer do you have to roll twice, nor is your success chance capped at 75%

**Note on GMST behaviour**
- The GMST `fPickPocketMod` has been set to 1.0 in the ESP file (versus 0.3 in the base game)
	- This value is what is multiplied by the gold value of what you are attempting to steal, to determine the difficulty of the attempt
	- Note that the engine now treats this GMST differently, and expects it to be 1.0 by default to produce the above example difficulties. 
- You can adjust the gold values the player can steal by adjusting the GMST, lowering it makes it easier to steal, for example setting it 0.1 in the new engine means you would be able to steal (and see) 10x the stated values above

## 15, Athletics and swimming

- In the base game, the player's swimming speed is a flat 50% of their running speed, which scales up to 60% of their running speed as you go from 1-100 skill. This was not very noticeable
- Now your swimming speed scales from 50-80% of you running speed as you go from 1-100 skill
- A hard cap has been added as to how much your skill can increase your % swim speed (in both the base and modified game going past 100 does give additional benefits). Above 500 athletics there is no further percentage boost to swim speed
	- This cap was only added as guarding, since technically in both systems your swimming speed is rising proportional to the square of your athletics, so there is a slim risk of reaching some truly absurd numbers and crashing the game (and it's Morrowind, so someone will try doing this)
  

## 16, The players willpower now has slightly more benefits

Willpower has been given a slight buff, and also now gives a small amount of resist magicka
- Willpower now contributes 1.5x as much as in the base game to your casting success rate (before factoring in your fatigue modifier)
- Your willpower, when it is above 50 points, now gives you a small amount of resist magicka. This is not displayed on the UI, but it is properly applied behind the scenes
	- Every 10 points of willpower above 50 adds 2% resist magicka, so 100 willpower gives 10% resist magicka
	- This stacks with normal resist magicka additively, but still obeys the hard cap of 60% for resist magicka

## 17, NPC spellcasting is now locked to base game spell effect costs

NPCs are now hard coded to use the base game spell effect costs regardless of the ESP values they are set to, so that the values can be changed in any way without affecting base game NPC behaviour. The player is unaffected by this hard-coding and will respond dynamically to spell effect cost changes

This was done to allow spell effect costs to be set to any value in the ESP file without affecting core game NPC behaviour. Without these changes when spell effect costs were adjusted, NPCs began to change their decision making in combat and in some cases found it unusually hard or easy to cast their spells. This was a core open morrowind (and likely base game morrowind) issue

A consequence of this is that the game now expects NPCs to only be using handcrafted spells, or auto-calculated spells that were made (auto-calculated) with the base game spell effect costs

## 18, Miscellaneous changes

- The sound played when repairing equipment with armorer's tools has been reduced to 50% the original volume
	- It was way too loud
- Enchanted weapons no longer display the "no-charge" message when their charge is depleted, and no longer play the "no-charge" sound effects either
- The server and client have been recompiled (a big thanks to Skooma-Breath for their help with the server) so that they have different checksums. EncoreMP clients and servers cannot connect to baseline versions of tes3mp


# Known issues & Comments

**General**
- [ ] Just about all of this needs playtesting, feedback is greatly appreciated!

**Base game spell costs**
- [ ] Pre-made spells for sale by merchants do not have updated magicka costs - instead of responding to the changes to magic effect costs in the ESP file, they keep the base game costs. 
- This appears to be a core feature of OpenMW and tes3mp - and changing the magicka costs of these spells would result in minor changes to AI combat behaviour and changes to AI auto-generated spell lists
- For these reasons they were left as is for the time being, although you could manually edit them to be in line with the new costs if you wished
- There is a plan to change this in a future version in a way that preserves the original costs for NPCs and creatures, whilst giving the player only the updated costed versions when buying pre-made spells (but this is not a simple fix so it was put on hold)
- The simple workaround during play is just to buy a spell with the effects you want, and then to make all of your spells as custom spells via spellmaking - anything made via the spell maker will use the new updated ESP costs
- A few effects are actually more expensive now, so the pre-made spells for those effects (levitate, open) are cheaper to cast than what you would be able to make via spellmaking. For the time being this will have to be on the honour system - just don't use the pre-made versions if you value balance

**Enchanting**
- [ ] Enchanting arrows using an enchanting service is too expensive in the current version, this is on the fix list
- [ ] The V0.80 code changes to enchanting are a little 'fragile' and depend on the spell effect costs not changing too much, this will be addressed when enchanting is reviewed (near the top of the priority list)

**Difficulty scaling**
- [ ] As of V0.80, player summons and player allies do not have their damage dealt decreased on high difficulty settings. This is being worked on as the next major change.

**Magic resistance**
- [ ] If the player has more than 60% magic resistance, NPC/creature AI will still act as if they the player had values above 60% when making decisions about what to do in combat
	- This was intentionally left like this to avoid re-working the AI, as it would have an impact on AI on AI combat as well. It might be possible to update the AI to treat only the player differently, but this a very minor issue
- [ ] The player UI still shows magic resistance values above 60%, but that is a UI issue only - the engine is working properly in this regard
	- Very likely this can be fixed, on the lower priority fix list

**Economy**
- [ ] Overall the changes to service costs and mercantile may be too punishing, but some of this can be addressed by adjusting the GMSTs

**Melee combat**
- [ ] An accuracy boost was given to all staff weapons as part of the melee overhaul. But this was actually done to all weapons in the class `BluntTwoWide`. In the base game this class is only used for staffs, and war hammers are in a separate category. Modded content may class some 2h blunt weapons as staffs, in which case they will be more accurate than intended in this overhaul (as of writing this however, this is not an issue for any tamriel rebuilt content)

**Experimental features**
- [ ] The acrobatics climbing overhaul is currently considered an experimental feature due to the risk of physics issues such as collision detection or clipping, although non have yet been found during playtesting

**NPC spellcasting**
- [ ] Several behind the scene changes were made to the engine to clean up some core game (or at least inherent to Openmw) bugs which affected NPC spellcasting when the effect costs were changed from their base game values. A consequence of all this is that the engine now expects NPCs to be using spells that were made with the base game effect costs. Essentially you can ignore this unless you are using modded content that: [1] Changes the spell effect costs notably, [2] Gives those spells to NPCs with auto-calculated values, and [3] expects the NPCs to cast those spells with the auto-calculated values
	- That scenario however would have caused unusual behaviour anyway in open morrowind, due to the behind the scenes stuff

**Server/Client visual checksum**
- [ ] The checksum has been correctly changed for the server/client (so that EncoreMP clients/servers cannot connect to baseline tes3mp servers), but EncoreMP servers still display as "V0.8.1" in the server browsing UI. 
- This was due to an issue with changing that user facing value - but it's a UI issue only

# Compiling partner file

- If you are curious about the new code or how it was developed, have a look at the partner file "V0.80 Beta release compiling changes"
- This is also a complete list of all changes made to the base tes3mp code, as requested in the original tes3mp license ammendments
- These are some rough notes that need a lot of tidying, but in their current state they will still walk you through all of the changes made and often explain why they were done a certain way
- Hopefully this can guide you through how to change the engine yourself if you are interested
- Keep in mind this is a Beta version, the code (and comments) are not tidy!
