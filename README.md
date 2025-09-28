 
# :gear: EncoreMP :gear:

EncoreMP is a fork of tes3mp V0.8.1

The original tes3mp project can be found here: https://github.com/TES3MP

Asides from the mechanical changes listed in this file, and the code changes detailed in the "EncoreMP V0.80 compiling notes" file, all of the code used in this project is unchanged from tes3mp.

Just about all of this needs playtesting, so feedback is greatly appreciated! You can leave comments on the project discussion page on Github.

The tes3mp project information has been copied below from the V0.8.1 tes3mp project readme. If you enjoy this work, please support tes3mp and OpenMW.

**EncoreMP project information**  

This is the first public (beta) release of EncoreMP: V0.80

It requires the ESP file `EncoreMPV080` to function as intended (this is for balance reasons, and due to some changes to how the GMSTs operate). See the ESP companion file for more details on these changes.

Hosted at: https://github.com/Tower-Numid/EncoreMP

Live release (V0.80) download page: https://github.com/Tower-Numid/EncoreMP/releases/tag/0.80  

Discussion page: https://github.com/Tower-Numid/EncoreMP/discussions  

**Contents**
1. TES3MP project information
2. Introduction to EncoreMP
3. Mechanics changelog
   <ol type="1">
	 <li>Climbing</li>
	 <li>New difficulty system</li>
     <li>Enchanting overhaul</li>
     <li>Experience gain adjustments</li>
     <li>Training costs and skill book adjustments</li>
     <li>Player resist magicka cap</li>
     <li>Melee combat changes</li>
     <li>Hand to hand combat changes</li>
     <li>Ranged combat changes</li>
     <li>Armour rating adjustments</li>
     <li>Armorer overhaul</li>
     <li>Mercantile overhaul</li>
     <li>Alchemy overhaul</li>
     <li>Pickpocketing overhaul</li>
     <li>Athletics and swimming</li>
     <li>Willpower buff</li>
     <li>NPC spellcasting locked to base game effect costs</li>
     <li>Miscellaneous changes</li>
	</ol>
5. V0.80 known issues & comments
6. Partner files



# [1] TES3MP project information

Copyright (c) 2008-2015, OpenMW Team  
Copyright (c) 2016-2022, David Cernat & Stanislav Zhukov

TES3MP is a project adding multiplayer functionality to [OpenMW](https://github.com/OpenMW/openmw), an open-source game engine that supports playing "The Elder Scrolls III: Morrowind" by Bethesda Softworks.

* TES3MP version: 0.8.1
* OpenMW version: 0.47.0
* License: GPLv3 with additional allowed terms (see [LICENSE](https://github.com/TES3MP/TES3MP/blob/master/LICENSE) for more information)

Font Licenses:
* DejaVuLGCSansMono.ttf: custom (see [files/mygui/DejaVuFontLicense.txt](https://github.com/TES3MP/TES3MP/blob/master/files/mygui/DejaVuFontLicense.txt) for more information)

### Project status

[Version changelog](https://github.com/TES3MP/TES3MP/blob/master/tes3mp-changelog.md)

As of version 0.8.1, TES3MP is fully playable, providing very extensive player, NPC, world and quest synchronization, as well as state saving and loading, all of which are highly customizable via [serverside Lua scripts](https://github.com/TES3MP/CoreScripts).

Remaining gameplay problems mostly relate to AI and the fact that clientside script variables need to be placed on a synchronization whitelist to avoid packet spam.

TES3MP now also has a [VR branch](https://github.com/TES3MP/TES3MP/tree/0.8.1-vr) that combines its code with that of Mads Buvik Sandvei's [OpenMW VR](https://gitlab.com/madsbuvi/openmw).

### Donations

You can benefit the project by donating on Patreon to our two developers, [David Cernat](https://www.patreon.com/davidcernat) and [Koncord](https://www.patreon.com/Koncord), as well as by supporting [OpenMW](https://openmw.org).

### Contributing

Helping us with documentation, bug hunting and video showcases is always greatly appreciated.

For code contributions, it's best to start out with modestly sized fixes and features and work your way up. There are so many different possible implementations of more major features – many of which would cause undesirable code or vision conflicts with OpenMW – that those should be talked over in advance with the existing developers before effort is spent on them.

Feel free to contact the [team members](https://github.com/TES3MP/TES3MP/blob/master/tes3mp-credits.md) for any questions you might have.

### Getting started

* [Quickstart guide](https://github.com/TES3MP/TES3MP/wiki/Quickstart-guide)
* [Steam group](https://steamcommunity.com/groups/mwmulti) and its [detailed FAQ](https://steamcommunity.com/groups/mwmulti/discussions/1/353916184342480541/)
* [TES3MP section on OpenMW forums](https://forum.openmw.org/viewforum.php?f=45)
* [Discord server](https://discord.gg/ECJk293)
* [Subreddit](https://www.reddit.com/r/tes3mp)
* [Known issues and bug reports](https://github.com/TES3MP/TES3MP/issues)


# [2] Introduction to EncoreMP

**What is EncoreMP?**

EncoreMP is a mechanical overhaul of many of the core features of Morrowind, with the changes made in the game engine. It has been forked from tes3mp and as a branch of tes3mp it is multiplayer compatible. 

EncoreMP has been designed with maximum mod compatibility in mind, and most especially for full compatibility with the Tamriel Rebuilt project. 

It does this by changing as little as possible in the ESP file, and by making all the engine level changes as content agnostic as possible.

**How is this different to other gameplay overhauls?**

This project hosts almost all of its changes in the games engine, not in an ESP file. So this should be compatible with almost all mods that add new content. EncoreMP itself adds no new content, and makes no graphical changes.

**What is the tone of this overhaul?**

This tries as much as possible not to break from the spirit of the original game, whilst balancing and updating some of the older and neglected mechanics. 

There are some new mechanical additions, and a lot of balancing changes, but overall the aim is for this to feel like playing Morrowind did twenty something years ago when it came out.

EncoreMP is recommended for someone who has played the base game, and is already familiar with the core mechanics.

This is a beta version and is in need of playtesting and feedback. Currently the changes to the economy are likely the most punishing change - but they are not meant to be harder just for the sake of it.

**How do I play?**  

If you already have a working copy of tes3mp anywhere on your computer, you are able to play EncoreMP without any further setup required. If not, see the installation instructions from the tes3mp quickstart guide on Github: https://github.com/TES3MP/TES3MP/wiki/Quickstart-guide

First download the release version of the project from Github (V0.80).

Then move the ESP file `EncoreMPV080` from the release download into Morrowind's 'data files' install folder, as you do with other ESP mod files. 

Then unzip the rar file and set your modlist via the openmw-launcher within, to match that required by the server. By default the server `requiredDataFiles` lists Morrowind, Tribunal, Bloodmoon, and EncoreMPV080.ESP. Other mod files are added to the server in the same way they are for tes3mp.

EncoreMP can then be played within the unzipped folder from anywhere on your computer.


**What does it change?**

This is a brief summary of the changes made, for more details see the mechanical changelog below, not everything is listed here:

(Unless stated, all mechanical changes affect the player only)

**Skills:**
- Enchanting has been overhauled and re-balanced, making enchanted scrolls is now viable
- Alchemy has been overhauled and re-balanced
- Acrobatics now lets you climb! Past a certain point your acrobatics skill lets you climb steeper and steeper slopes, up to an 89° angle at high skill
- Your weapon skills now contribute to your damage dealt, not just your hit chance, and weapon accuracy has been revised
- Ranged weapons are more accurate, and higher ranged weapon skill helps you recover arrows more often
- Unarmoured is overall stronger, and scales with speed and agility
- Armorer has been overhauled to be a more important skill, expensive equipment is now more difficult to repair and equipment degrades slower as your armorer skill increases
- Athletics increases your swim speed more than it does in the base game, you can swim at up to 80% of your run speed at high skill
- Mercantile now gains experience from the value of items sold, rather than from haggling
- Spells now reward you with more experience proportional to their cost when cast
- Pickpocketing has been overhauled, the value of items you can steal has been increased and various bugs have been fixed
- The costs of most magic effects have been changed in the ESP file to make almost all spell effects viable, with the current exception of summoning effects

**General:**
- The difficulty system has been revised, melee scaling has been balanced and player magic damage is now included in difficulty scaling (currently player summons and allies are not included in difficulty scaling, this feature will be added in a future version)
- More experience is now required to advance at higher skill levels
- Paying for skill training is much more expensive at high skill levels
- Books that increase your skill when read stop granting skill increases at skill level 95 and above
- The player no longer benefits from resist magicka values above 60%
- The willpower attribute has been buffed, it now contributes more to spell casting success rates and grants small amounts of resist magicka when willpower is raised above 50

**Quality of life:**
- The 'repairing equipment' sound has been turned down to 50% of it's original volume!
- Enchanted weapons no longer display the "out of charge" message or play the "no charge" sound effect when you attack with them whist they have no charge



# [3] Mechanics changelog

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
- This feature is tied to the players **unmodified** acrobatics skill, so that even if your acrobatics skill is drained or buffed, you do not change your ability to climb. This was done intentionally to avoid unintended physics behavior when the players acrobatics skill changes mid-climb

**Climbing angles**
- If your skill is 30 or below, then you have the base climbing angle of 47° (no change from the base game)
- If your skill is between 30-60 then you add `(skill-30)/3` degrees, so that you scale from being able to climb a 47° angle at 30 skill to a 57° angle at 60 skill
- Above 60 skill you gain 1° of additional climbing angle per skill level with a cap hard limit of 89° reached at 92 skill

**What that means in practice**
Below are some examples of how these changes affect game play:
-  47° - Reached at skill 30, base game behavior
-  57° - Reached at skill 60. This is a noticeable improvement, many base game hills can now be climbed if you search around for a shallow enough incline. This angle increase has more of an effect than the small increase in number might suggest
- 67­° - Reached at skill 70. The majority of exterior obstacles are now scalable in the base game with a little effort finding a route. This is not enough to climb buildings in urban areas (unless they have sloped sides) but more than enough for most wilderness trekking without having to rely on levitate
- 77° - Reached at skill 80. Practically any exterior obstacle is now scalable, although not necessarily in a straight line (some very sleep slopes may require some moving around to find a path still). A lot of spacious interiors (such as caves) are climbable now as well
- 89° - Reached at skill 92. Any surface with an angle of 89° or below can be climbed, this is essentially everything in the game apart from walls

## 2, New difficulty system

The difficulty system has been completely reworked and re-balanced.

For ease of balancing during development, the game was also moved from a 'sliding bar' type difficulty, where any integer value can be used as a difficulty setting, to a a 'tiered' difficulty system like in later games. The difficulty setting is adjusted as with core tes3mp in the server config file. See below for a table of difficulty tiers.

Difficulty now scales ALL player damage dealt and taken, (including magic damage, fatigue from hand to hand, reflected damage, etc) with the exception of player summons and allies as of V0.80. Summons and allies will be added to the difficulty scaling system in a future version.

This version (V0.80) has been tuned for co-op multiplayer, so damage done is more heavily penalised than damage taken.

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
 
**Comments**
- Magic damage taken only affects damage dealt by non-player actors, so drinking potions or using self damaging scrolls will not cause you to take any more damage. Nor will you take more magic damage from scripted effects or environmental sources such as traps
- For balance reasons, anything reflected onto the player deals 1x damage regardless of difficulty, but anything reflected onto non-players receives the magic damage step down
- As in the base game physical damage taken by the player or enemies is first reduced by their armour rating, and then any difficulty modifiers apply. This means that you do not need higher armour values to achieve reasonable damage reduction on higher difficulty settings, but it becomes a lot more important when you are being hit for 5x damage!


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

- There is no difference in difficulty within a given tier, e.g. setting it to either 201 or 999 will have the same effect (Nerevarine difficulty), and setting it to 52 or 96 would both result in master difficulty
- The only reason number ranges were kept was so that it would be easier to go back to a sliding scale system later on if needed

## 3, Enchanting overhaul

**Every item now has a usable enchanting capacity**
- All items in the game that can be enchanted have increased enchanting capacities, with a capacity of 30 (approximately) being the new minimum. Very high capacity items in the base game are either unchanged or have been reduced in capacity slightly by the new logic.
	- This means that making enchanted scrolls is now viable, as all paper items have gone from an enchanting capacity of 1-3 to approximately 30
- This was achieved in the engine by taking the base game enchantment capacities from the game's ESM/ESP file and running them through an exponential function that converts them non-linearly to the new values.

**Your enchanting skill lowers the on-use costs less than it does in the base game**
- Enchanting 'on-use' costs are still reduced by skill, but the cost reduction now uses a non-linear equation. There are some additional rules for very cheap to cast items which stops them ever costing less than 1 to cast
- Overall the enchanting skill reduces the cost to use on-use enchanted items less than it does in the base game, with the aim of preventing exploits
	- Cheaper effects reach their minimum 'on-use' costs at lower skill levels
	- You can expect things to cost around 40-60% less to cast at 100 skill
	- Fortifying your skill past 100 does provide further 'on-use' cost reductions, but these are minimal

**On-strike enchantments have further reduced costs**
- The cost of using 'on-strike' enchantments is also reduced by your skill using the above logic, but in addition regardless of skill all `on-strike' effects have a final cost modifier of 0.25x after any skill reductions apply
	- This was done to pair with the limits put on weapon enchantment strength, and also as a QoL change so that you don't have to be as miserly with your charged weapons when cutting through weak enemies

**Not all spell effects use the same amount of an item's enchanting capacity**
- Different spell effects now use different amounts of enchanting capacity
	- All destruction and restoration effects have doubled capacity costs
	- For making scrolls only, all alteration and conjuration effects use half capacity
	- All instances of Dispel, Restore attribute, Absorb health, Absorb fatigue and Resist paralysis have been doubled in capacity cost
	- All variants of fortify attribute have been halved in capacity cost
	- For constant effects enchantments only the following effects have an additional x1.5 capacity cost multiplier added to them for balance reasons:
		-  Shield, Chameleon, Sanctuary, Restore Fatigue, Fortify attribute, and Resist Paralysis

**Enchanting success rates**
- Your enchanting success rate still follows the core game's logic, but with these additional changes:
	- If you make an enchantment with an equivalent magicka cost of 5 points or less you receive a flat +25% to your success chance to making the item
	- Enchanting scrolls is easier, making any enchanted scroll gives a flat +25% to your base success chance
	- All enchantments (except for constant effect, see below) become significantly harder to make when they reach equivalent magicka costs of 20 or more, and even harder again at costs of 25 or more
	- For example, without any buffs at 100 skill you would struggle to make an enchantments with a cost of 25 points or more (although it is still possible). This was done to prevent artefact quality items being made too easily

**Making constant effect items**
- Constant effect enchantments follow a special rule, which was implemented as a stop-gap solution for the first release of EncoreMP:
	- Attempting to make any constant effect enchantment now requires an **unmodified** enchanting skill of 75 or higher
	- Between 75 and 100 skill you are able to make increasingly larger capacity constant effect enchantments 
		- Exceeding the allowed capacity, based on your skill, will drop your success rate to 0%
		- At 100 skill you can enchant any capacity of constant effect with a 100% success rate

**Enchanting arrows**
- If you enable the OpenMW 'multiple ammunition enchanting setting' (which can be done in the server config file, and is toggled on by default in the EncoreMP release server), then you will automatically enchant ammunition in batches of up to 20
	- You will find it slightly harder to enchant 20 items at once compared to a single item of ammunition, but not prohibitively so
	- Due to how the OpenMW logic works, with this setting on if you choose to enchant one piece of ammunition at a time you will actually receive a boost to your enchanting success rate, but nothing game breaking
		- This was left in as a way of making special mega-arrows on demand
- There is a visual bug where it can display an enchanted arrow you make as having 0 charge, but testing has found that the enchantments work regardless of this UI issue
- The value of the OpenMW setting in the config file should not matter, but just in case leave the setting value at 0.5 if it is enabled, as this was what was confirmed to work during testing and development

**Cost of enchanting services**
- Enchanting service prices now scale non-linearly with the point cost of the enchantment. It is overall much more expensive to buy high cost effects, and some special rules were added to handle edge cases for the beta release. The balance of V0.80 may be too punishing due to high costs,
	- Making a 20 point capacity enchanted scroll costs around 4000 gold
	- Making a 20 point capacity on-strike enchantment costs around 100,000 gold (this capacity is roughly the strength of most artefact on-strike effects)
	- Making a 20 point capacity on-use effect costs around 75,000 gold
- Enchantments with capacities of 20 points or more begin to significantly increase in price, and beyond capacities of between 25 to 30 points (depending on the enchantment type, on-hit, on-use, etc) become effectively impossible to afford
	- The "impossible to afford" cost was crudely implemented by adding a flat 5 million gold cost to the enchantment for values that exceed these amounts. In theory if you enough gold you can make such a mega enchantment. But this will never be a problem during normal play
- Constant effect service costs behave differently,
	- Any constant effect enchantment has a baseline starting cost of 70,000 gold
	- A 30 point CE enchantment costs around 100,000 gold
	- Above 30 points the cost increases non-linearly
	- A 100 point CE enchantment costs around 400,000 gold (due to the revision to item enchanting capacity, very few items now have capacities above 100)
	- Beyond 100 points it becomes  "impossible" with the flat 5 million cost increase being applied


## 4, Experience gain adjustments

The rate of experience gain for all skills has been adjusted. Note that many of the experience gain values were also adjusted in the ESP file to complement these changes, see the ESP companion file for more information.

Overall experience gain has been reduced at high skill levels. This was done to delay the point at which many characters reach the 'power threshold' and begin to find most of the game's content too easy.

**General changes**
- Experience gain values have been adjusted for most skills as per the ESP companion file
- In the base game a skill required experience equal to its level to advance. This logic has been kept as a baseline, but there are now some additional rules that apply:
	- A skill can never require less than 30 experience to advance
		- This was done to make early skill choices more meaningful
	- Experience gain is reduced for all skills once they are above level 50:
		- Below skill level 50 there is no reduction to experience gain
		- From levels 51 to 60, all experience gained is multiplied by 0.8
		- From levels 61 to 70, all experience gained is multiplied by 0.65
		- From levels 71 to 80, all experience gained is multiplied by 0.55
		- From levels 81 to 90, all experience gained is multiplied by 0.4
		- From levels 91 to 100, all experience gained is multiplied by 0.33


**Experience gained from casting spells is now proportional to the spell's cost**

- For spells that cost 5 or less magicka, there is no increase to the experience gained from casting
- For spells that cost more 5 or more magicka you receive a multiplier to the experience earned, based on the spells cost, using the equation below:
	- `y = 0.089x + 0.56`
	-  Where x is the spell's magicka cost and y is the experience multiplier
- This results in the following multipliers to experience gain at these example spell costs:
	- 10 magicka, x1.43
	- 15 magicka, x1.87
	- 20 magicka, x2.31
	- 30 magicka, x3.19
	- 40 magicka, x4.07
	- 50 magicka, x4.95
 
## 5, Training costs and skill book adjustments

- Skill books no longer grant skill increases when the relevant skill is at level 95 or above
- Paying to train skills has been made more expensive, and the cost of training now increases non-linearly with skill level
- The change to training costs respects the GMST (`iTrainingMod`), which has been left at the default value of 10
- If you want to adjust the training costs shown below you can do so by altering the GMST. For example if you set the GMST to 5 the system will still scale the costs non-linearly by level but the result will be exactly half of the values shown in the table below
	- Note that these are the base costs to train a skill at the example levels, and that your mercantile skill will reduce the cost of training as in the base game

| Skill  level | EncoreMP gold cost for training | Base game gold cost for training |
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

## 6, Player resist magicka cap

- The resist magicka effect now provides no benefit to the player above 60%
	- This change was implemented for balance reasons. Reaching 100% resist magicka allowed the player to negate most of the downsides of unique items and to be immune to a wide range of dangerous spells in the late game
- The engine does not apply this cap until after all 'weakness to magicka' effects have been accounted for. In other words this is a net cap of 60% resist magicka
	- Weakness to magicka negates resist magicka at a 1:1 ratio, as in the base game
	- For example if a character had a permanent 20% weakness to magicka, and then cast a spell granting them 70% resistance to magicka for 30 seconds, the end result would be that the character has a 50% resistance to magicka for the spells duration
		- The engine does: (-20 + 70 = 50) and only then tries to apply the 60% cap
- Known issue: The spell effect UI still displays resist magicka values above 60%, but this is a display issue only and does not affect the mechanics
- Known issue: If the player does have a net resist magicka score of 100% or more, opponents in combat will still behave as if the player had immunity to the relevent effects (e.g. blind, burden, etc) despite this no longer being the case
	- As in the base game, enemies will not attempt to cast effects on the player that the player will fully resist
	- So if the player buffed themselves to a net 110% resist magicka, EncoreMP would properly cap the resistance to 60%, but as the combat AI has not been adjusted to account for this, all opponents will forego attempting to cast the relevent effects at the player whilst the net resist magicka value is in place
	- It was decided to leave this AI behavior mismatch unchanged, as otherwise the AI would have to have been adjusted which could have resulted in unintended behaviour (especially when an AI is fighting another AI, like a summon or a guard)
	- This may be resolvable in a future version

## 7, Melee combat changes

**Weapon accuracy**
- Melee accuracy is now higher at low skill levels (player accuracy at 5 skill is now around 15% versus most low level enemies, versus around 5% in the base game)
- Melee accuracy now scales slightly slower, and reaches a lower final value at 100 skill 
	- At 100 skill, against the strongest enemies, the player's hit chance will be around 90% with a 1x fatigue modifier, around 108% with a 1.25x fatigue modifier, and only around 72% with a 0.75x modifier
	- In the base game you reaches 100% accuracy at 80 skill with a 1.25x fatigue modifier, and 100% accuracy at 100 skill with a 1x fatigue modifier
- **Two handed weapons now give a flat -15% chance to hit**
	- This was added to make the choice between one and two handed weapons more meaningful, and to distinguish two handed weapons as items requiring more skill to use effectively
	-  There are some exceptions to this, see the weapon type changes below

**Weapon damage scaling**
- Your strength attribute now contributes half as much as in the base game to your melee weapon damage scaling (both positive and negative)
	- For example a strength score of 100 now adds +25% damage to weapon damage instead of +50%
	- A strength score of 1 now applies a -25% damage modifier instead of a -50% modifier
- The relevant melee weapon skill now contributes to damage done with melee weapons. In the base game your weapon skills only affected accuracy
- The contribution from skill follows the same logic as strength does in EncoreMP
	- At 100 weapon skill you get a +25% damage modifier to the relevant weapons
	- At a weapon skill of 1 you take a -25% damage penalty
	- For example in EncoreMP, if you have had a strength score of 100 and a weapon skill of 50, you would get a sum +25% increase to damage dealt
		- If you had 100 strength and 100 skill you would get a +50% damage modifier
		- If you had 50 skill and 1 strength, you would get a -25% damage modifier
		- If you had 1 skill and 1 strength you would get a -50% damage modifier

**Weapon type benefits**
- All weapons now have an additional mechanical benefit, depending on what type they are
	- **Short blades** receive a flat +10% to hit chance (equivalent to about 15 skill levels)
	- **Spears** receive a flat  +10% to hit chance and do not receive the -15% to hit that all other 2h weapons do
	- **Long blades** gain additional bonus damage from the characters agility score as well as their strength
		- For every 10 points of agility above 50, long blades gain +5% damage, reaching +25% damage at 100 agility
		- This stacks with the bonuses to damage that all weapons receive from strength and skill
		- There is no penalty to damage for being below 50 agility
		- For example if a character had 100 skill, strength and agility they would do 175% damage with long blades
		- If they had 30 agility, 50 strength and 50 skill they would do 100% weapon damage
	- **Axes** gain additional bonus damage from the characters endurance score when it is above 50, as well as from their strength and skill
		- This follows all of the same rules as described above for long blades
	- **Maces** gain additional bonus damage from the characters strength score when it is above 50, in addition to the normal bonuses the character receives from their strength and from their skill
		- This follows all of the same rules as described above for long blades
		- For example if a character had 50 skill and 100 strength, they gain a +50% damage bonus when using maces. This is because they first receive the baseline +25% damage boost that all weapons would get from 100 strength, and then the additional +25% boost from strength that maces receive using the same logic as described for long blades
		- In effect maces scale twice with strength
	- **Staves** (a sub-set of blunt weapons) receive a flat +20% to hit chance, and do not take the -15% to hit that other 2h weapons do
		- In the base game staves are classed as belonging to a different weapon group than all other blunt weapons. Staves are classified as `BluntTwoWide` weapons in the core game ESM files, and all staff like weapons added by the original developers have very low damage comapred to all other weapon types
		-  The +20% bonus to hit was given to everything in the `BluntTwoWide` weapon category. As a result if modded content adds powerful two handed blunt weapons to this category, they will wrongly recieve the accuracy bonus and may be overpowered
		- As of writing this, this is not an issue in any tamriel rebuilt content, however if required this change will be reverted in future


## 8, Hand to hand combat changes

**Health damage done**
- Health damage done by hand to hand attacks has been increased by adjusting the GMST in the ESP file,`fHandtoHandHealthPer`, which has been increased from 0.1 to 0.4
	- This GMST value is multiplied by the fatigue damage that your hand to hand attacks deal to determine the amount of health damage that they deal against vulnerable enemies (e.g. those that have been knocked down, or are paralysed)

**Damage done - general**
- Damage done has been increased at low skill levels and scales to the same final damage at 100 skill
	- Beyond 100 skill you now gain slightly less damage per skill level
	- The formula was changed from: `damage = skill`
	-  To: `damage = (skill x 0.9) + 10`
	- This makes low skill levels slightly more useful. They are still not good, but it is somewhat more reasonable now to go punching mudcrabs

**OpenMW strength scaling behaviour change**
- The OpenMW setting for scaling your hand to hand damage with your strength was revised to behave like strength does for weapon attacks in the base game. The new behaviour is:
	- 50 strength: no modifier
	- 100 strength: +50% damage modifier
	- 1 strength: -49% damage damage modifier
- It is recommended that this setting is toggled on in the server config file. Werewolves haven't been balance tested, so it is recommended to turn this on and set it to '2', which is the option for hand to hand strength scaling, excluding werewolf form
	- Note that unlike the other changes in EncoreMP, this does affect NPCs
- The reason the OpenMW behaviour was changed was that previously it resulted in unusual behaviour at low strength values, and gave very high scaling with strength past 100


## 9, Ranged combat changes

**Accuracy**
- Ranged weapons follow the same logic as the melee accuracy changes, but in addition all ranged attacks recieve a flat +20% to their hit chance

**Damage**
- Bows and crossbows scale their damage using the same updated logic that melee does (half of the modifier comes from skill and half from attributes) however bows and crossbows use your agility instead of your strength to scale damage
- Throwing weapons scale using your strength and your skill. Strength and skill have a greater effect on throwing weapon damage than on any other weapon type,
	- All throwing weapons reach 200% of their base damage at 100 strength and 100 skill instead of 150% as with other weapons
	- This was done to help them stay competitive into the late game

**Ammunition recovery**
- Non-enchanted ammunition is now recovered more frequently from enemy corpses as you increase your ranged weapon skill:
	- From skill levels 0 to 25 you will recover ammunition at the rate you do in the base game (1x the GMST value `fProjectileThrownStoreChance` - which is 25% by default)
	- Above skill level 25 your chance of recovering ammunition linearly increases with your ranged weapons skill from 1x the GMST value to 4x the GMST value at 100 skill
	- So if you are using the default GMST value of 25%, you reach a 100% recovery rate of unenchanted ammunition at 100 skill
- It is now possible to recover enchanted ammunition once your ranged weapon skill is above 50
	- From skill levels 0-50 you have no chance to recover magical ammunition
	- Above skill level 50 your chance of recovering magical ammunition scales linearly from 0, to 2x the GMST value (the same GMST used above for non magical ammunition recovery) 
		- For example, at 75 skill you have a 1x GMST chance to recover magical ammunition
		- At 100 skill you have a 2x GMST chance to recover magical ammunition
	- For balance reasons, the function that controls the magical ammunition recovery rate rate caps the player's ranged weapon skill at 100 for the purpose of calculating enchanted ammunition recovery rate. So that even if you buff your skill past 100, you will still be hard capped at an enchanted ammunition recovery rate of 2x the GMST value
- Both of these systems respect the GMST, changing it from the default value of 25 will cause all of the above to change as expected
	- e.g. changing the GMST to 10 would mean you end up with (at 100 skill) a 20% chance to recovery magical ammunition and a 40% chance to recover normal ammunition
	- There are no issues with increasing the GMST value. If you end up with over a 100% chance to recover ammunition (e.g. by setting the GMST to 200), there are no bugs or unusual behaviour

## 10, Armour rating adjustments (player and creatures)

**Player: equipment derived armour ratings**

For the three armour skills (heavy, light, and medium) the equation used to determine player armour values below skill level 30 has been adjusted to be less punishing

* In the base game your armour rating from equipment is equal to the base armour rating of the item multiplied by (your armour skill / 30)
	* For example, previously if you had 5 skill levels in heavy armour, wearing a full set of Dwemer armour would give you 3 armour class versus 20 armour class which you receive at 30 skill
* This was changed to be less punishing since low skill levels now require more experience to advance in EncoreMP
* The new logic used to determine armour rating from equipment below 30 is :
	*  `The item's base rating * ((your skill + 5) / 35)`, 
	* then once you reach 30 skill and above, the behaviour becomes the same as the base game
* A table of derived armour ratings (as a percentage) in the old and new system based on your skill:

| Skill | Old % rating | New % rating |
| ----- | ------------ | ------------ |
| 5     | 16           | 28           |
| 10    | 33           | 42           |
| 15    | 50           | 57           |
| 20    | 66           | 71           |
| 25    | 83           | 85           |
| 30    | 100          | 100          |

**Creatures: Innate armour ratings**
* All creature type entities in the base game  (entities which are not classed as NPCs in the engine) had armour ratings of 0, regardless of their level
* EncoreMP changes this so that all creatures have an armour rating of 10 as a baseline, in addition they recieve bonuses if they are level 5 or above, or level 10 or above,
	* Creatures that are level 5 or above gain an additional +2 AC, for a total of 12
	* Creatures that are level 10 or above gain an additional +5 AC, for a total of 15

This was done to make creatures a little more durable against physical attacks, but the numbers were kept low to maximise compatibility with modded content


**Player: unarmoured skill derived armour ratings**
- The unarmoured skill has been buffed to help it remain viable on high difficulties, without having to rely on the base game trick of fortifying your skill past 100
- The base game logic is that your unarmoured skill gives an armour rating equal to: `(your unarmoured skill)^2 x 0.0065`
- EncoreMP adjusts the unarmoured skill to give higher armour ratings at low skill levels, and makes it so that your agility and speed attributes can both boost your unarmoured rating further
	- For skill levels 0 to 30, your unarmoured rating is `unamoured skill/3` (reaching 10 armour at 30 skill)
	- From skill levels 30 to 70, every level above 30 adds approximately 1.6 armour rating (reaching 75 armour at 70 skill)
	- Above skill level 70, each skill level adds 2.5 armour (reaching 150 armour at 100 skill)
- Your agility and speed attributes can modify this further if either are above 50
	- There are no penalties to your unarmoured rating if either attribute is below 50
	- For either attribute, for every 2 points you have above 50, they add 1% to your unarmoured rating
	- For example at 100 speed and 50 agility you would recieve a 1.25x multiplier to your unarmoured rating
	- At 100 speed and 100 agility, you would recieve a 1.5x multiplier. This means at 100 skill, agility, and speed, you would have an unmaroured rating of 225 (comparable to some medium armour at full skill, but not quite as good as full heavy armour at 100 skill)
- The calculations above respect the GMST `fUnarmoredBase1` and they assume it has the default value of 0.1, which results in the above armour scores

## 11, Armorer overhaul

In the base game once you were able to reliably repair an iron sword, you could reliably repair anything, so ther was not much benefit to levelling the skill.  

The following changes have been made,
- More expensive items are now harder to repair
- Your armorer skill now passively slows down the rate at which equipment loses durability in combat
- Higher quality armorer's tools now add to you repair success rate, in addition to the base game behaviour of increasing the amount you repair per success
- It now costs significantly more to pay services to repair expensive items, proportional to their value

**The armorer skill now slows the rate of equipment durability loss**
* All items worn by the player now degrade at only 25% of their normal rate once you reach 100 armorer skill, and this is a hard cap of durabiltiy loss reduction which can be exceeded
* Your equipment now takes (`armorer skill x 0.075`)% less damage from combat

**The value of an item determines how difficult it is to repair**
- The base gold value of an item now influences how difficult it is to repair. More expensive items are harder to repair
- As in the base game, the amount of durability you restore per success is proportional to your chance to succeed at the repair attempt. So going from 20% to 50% success not only doubles your odds of repairing, but it also more than doubles how much you do repair when you succeed. Likewise sitting at a 5-10% success rate means you will be repairing very little even when you do succeed
- You can increase your repair success rate by using higher quality tools (see the section below) or by fortifying your strength, luck, or skill
- Weapons are overall easier to repair relative to armour until very high item costs, as most characters can survive having their armour break, but not their weapon
- Note: a 30-50% success rate is enough to maintain equipment reasonably, but you will need a lot of hammers at first
- Depending on the equipment value, EncoreMP enforces a minimum success rate you cannot fall below to avoid making the skill feel mandatory
- The table below shows the enforced minimum success rates, as well as typical skill levels required to reach 30% and 50% repair rates

| Armour value   | Weapon value   | Minimum success rate | Skill for 30% success | Skill for 50% success |
| -------------- | -------------- | -------------------- | --------------------- | --------------------- |
| 0-100g         | 0-499g         | 20%                  | ~30                   | ~40                   |
| 101-499g       | 500-1999g      | 17%                  | ~35                   | ~45                   |
| 500-1999g      | 2000-4999g     | 15%                  | ~37                   | ~50                   |
| 2000-4999g     | Skipped        | 10%                  | ~45                   | ~55                   |
| 5000-19,999g   | 5000-19,999g   | 7%                   | ~60                   | ~70                   |
| 20,000-49,999g | 20,000-49,999g | 5%                   | ~70                   | ~80                   |
| 50,000g +      | 50,000g +      | 5%                   | ~80                   | ~90                   |

  
**The quality of the armorer's tools you use now modifies your success rate when repairing**
- In addition to boosting the amount repaired per swing (as in the base game), the quality of an tool can also potentially raise or lower your effective skill when calculating your success rate
- The rule is: for every 0.1 quality above or below 1.0, add or subtract 1.5 skill levels to the attempt
- For example a grandmaster's armorer hammer (quality 1.7), adds an effective 10.5 skill levels to all repair attempts, and repair prongs (quality 0.5) remove an effective 7.5 levels (but you can never fall below the minimum success rates above)
- This should reward you for finding the best tools, and let you maintain things above your level

**Repair costs are increased for more expensive items**
- This was technically already the case in the base game, but you would never be charged more than 1gp for point of item health, regardless of the items value
- Now that limit has been removed, and the new rule is (before mercantile discounts apply):
	- The cost to repair an item fully from 0% to 100% durability is 50% of the base value of the item
	- So, each 1% of the item's durability you are repairing costs 0.5% of the item's full value
- The repair cost is then multiplied by the GMST `fRepairMult` (which is 1.0) to determine the final price
- The repair costs may be set too high overall for the beta version (V0.80), if you find this to be the case try lowering the GMST to see how it feels
 

## 12, Mercantile overhaul

**The player now earns experience through the value of items sold, not by haggling**
- The player now earns mercantile experience not by haggling, but based on the value of items they sell (and how much they sell them for)
	- Earning experience through haggling was completely removed during development for ease of testing and balance, though it could be re-enabled in a future version
- You do not earn any experience from buying items, this was an intentional design choice as it opened up many ways to exploit the new system
- The player earns 1 experience for every 166gp they make in sales as of V0.80. So for example at skill 30 you need 30 experience to level, so you would have to sell a total of around 5000g worth of item to level
- If this rate seems too low, or high, you can adjust it by changing the experience value for a successful bargain in the ESP file. This is set to 0.3xp by default, as in the base game, and that figure results in the gold to XP ratio described above
	- For example setting the experience value to 0.9xp in the ESP file will triple the rate of experience gain and result in you only needing to sell around 1660g worth of items to level up from 30 to 31
- If you sell an item for less than the offer made by the NPC you will receive less experience proportional to how much you discounted the sale (as giving things away cheaply is not good merchant behaviour)
- The value of any items you receive in exchange for a sale you make is also counted towards the 'sale value' for the purpose of awarding experience. For example,
	- If you have 1000g worth of gems, and the merchant makes an initial offer of 500gp - you stand to earn 3xp from the transaction (the system uses the sale value of the items, not their base value)
	- If you decide to sell them cheaply, say if the merchant is nearly out of gold and you just want to get rid of them, for only 250gp, then you will still earn experience but only 50% of what you would have earned for selling them at full price (1.5xp)
	- However you could ask the merchant for 250gp, and 250gp worth of items in exchange for the gems. The engine will correctly add up the barter value (not base value) of everything you receive in return, and in this case award you full XP for the sale again (3xp)

**Disposition has less of an effect on mercantile interactions**
- The engine was changed so that an NPC's disposition being above or below 50 now only has one quarter of the effect on mercantile bartering rates compared to the base game
- To pair with this change, the GMST `fDispositionMod` was set to 0.25f, down from 1.0f in the base game. This GMST acts a multiplier for how much NPC disposition benefits haggling, lowering it to 0.25f makes it a 0.25x multiplier versus the base game as well

**Bartering and haggling rate caps (for balance and testing in the beta version)**
- Bartering rates (not haggling) are hard capped as follows:
	- You can never buy an item for less than 90% of it's base price, or be asked to pay more than 150% of its base value
	- You can never sell an item for more than 60% of it's base price, or be offered less than 20% of it's base value
	- These rates do not affect any services other than trading in a shop, so you can still get far better discounts on training, etc, as you level your mercantile
- Haggling rates have been hard capped at +- 10% the initial barter offer made
	- This was done to stop a potential exploit, where you otherwise can break even from buying/selling something by haggling, and endlessly circulate the item back and forth for free experience


## 13, Alchemy overhaul

This is a complete overhaul of the skill, changing nearly everything about it, but the end result is it still behaves in practise a lot like core alchemy.

**Potion strength overhaul**

This logic that determines potion strength was significantly changed from the base game to bring it in line with spellmaking costs. This helps balance potion making against other sources of magic, and prevents some unusual behaviour when spell effect costs are set very low or high in the ESP file.

- Your alchemy factor is divided by 6 to determine an effect's 'magicka budget'
- The engine then determines the effect's strength, by calculating how strong a spell you could have made in the spell maker using that magicka budget
- The system is designed to always produce effects which have a balance of duration and magnitude, with about half the budget being allocated to each
- The full magicka budget is given to each distinct effect in a potion, it is not spread out or shared between multiple effects. It is always an upside to have multiple positive effects in a single potion

**Ingredient value now affects potion strength**

The average value of the ingredients used to make a potion now affects the strength of the potion (by modifying your alchemy factor) as follows:
- If the average value of the ingredients is below 5g, then your alchemy factor is reduced by 30%
- From average ingredient values of 5g to 200g you receive a non-linear bonus to your alchemy factor:
	- For an average ingredient value of 5g, you get a +10 to your alchemy factor
	- For an average ingredient value of 10g, you get a +15 to your alchemy factor
	- For an average ingredient value of 25g, you get a +20 to your alchemy factor
	- For an average ingredient value of 100g, you get a +25 to your alchemy factor, and then an additional 1.1x multiplier
	- For an average ingredient value of 200g, you get a +30 to your alchemy factor, and then an additional 1.1x multiplier
- The logic interpolates between those values using a non-linear equation (so these are not hard break points, just examples) 
- Above average ingredient values of 200g the scaling speeds up and you get much larger bonuses (since there are very few, and often unique, ingredients worth more than 200g)

**The effect of mortar quality has been slightly reduced**
- The positive or negative multiplier you receive from mortar quality behaves as in the base game, but the multiplier is reduced by 50%
- For example, if you use a grandmaster's mortar you would have received a 1.5x multiplier to potion strength in the base game, whereas in EncoreMP you would receive a 1.25x multiplier
- The same is true for low quality tools. Using an apprentice's mortar would have given you a 0.5x multiplier in the base game, whereas now it gives you a 0.75x multiplier
- This was done to narrow the range of potential potion strengths for ease of balancing in the new system. It could be reverted in future

**The behaviour of the other alchemy tools has been changed**
- The retort now multiplies the duration and magnitude of positive effects by:
	- `(1 + (retortQuality/10))`
	- For example you would get +5% at 0.5 Quality, and +20% at 2.0 Quality
- The calcinator boosts both positive and negative effects, and negative effects are more significantly increased
	- Positive effects receive the same boost as with the retort (+5% at 0.5 Quality up to +20% at 2.0 Quality)
	- Negative effects receive three times that boost (+15% at 0.5 Quality up to +60% at 2.0 Quality)
- The alembic multiplies negative effects by:
	- `(1 - (alembicQuality*0.4))`
	- For example you would reduce negative effects by 20% at 0.5 alembic quality, and you would reduce them by 80% at 1.5 alembic quality
	- There is a hard cap of a 90% reduction in negative effect strength which you reach at about 2.25 tool quality. This is only achievable if you use modded tools, and was only added to prevent unusual behaviour

Comments:
- Note that the modifiers from other tools are applied directly to both effect duration and magnitude, not your alchemy factor, so they have a larger impact than the numbers would otherwise suggest
- All of these modifiers from other tools stack with each other multiplicatively, not additively

**Order of operations for determining potion strength**
The order of operations in EncoreMP is:
1. Get the player's alchemy factor as in the base game
2. Add or subtract from it depending on the quality (average gold value) of the ingredients being used
3. Apply the mortar tool strength modifier to the alchemy factor
4. Determine effect duration/magnitude using the new spellmaking costed system
5. Apply any other tools you are using as percentage multipliers directly to the effect duration and magnitude

**Potion values**
- The value of any potions you make can now never be greater than the sum value of the ingredients used. Otherwise potion value is determined as in the base game
	- This is an intentionally harsh cap for initial testing, as otherwise alchemy always has the potential to create infinite money via cheap ingredients

**Potion weight**
- In EncoreMP potions cannot weigh more than 1.0, or less than 0.1, regardless of the ingredients used
- The new logic is to:
	- First calculate the potion weight as is done in the base game ( which is the average of all ingredients used)
	- Then cap it 1.0 at the most
	- Then reduce the weight by your `(alchemy factor / 100)`, to a minimum of 0.1
- This way you will be able to make minimum weight potions very early on by using light ingredients, but you will need high skill to get heavy ingredient potions down to 0.1 (at 90 skill everything you make will be 0.1 weight)

**Potions no longer stack**
- Drinking multiple of the same potion now refreshes the duration, instead of stacking multiple of the same potion on you - as spells behave in the base game
- For example if you drink 100 sujamma at once in EncoreMP you only recieve a +50 to your strength
- Or if you drink 10 healing potions at once via a hotkey, you no longer become practically immortal due to all the stacking healing
- But you can still stack lots of different different potions if you want

**Cheap ingredients reward less experience**
- Potions made with an average ingredient value of less than 5gp now reward less experience
- This was done to encourage using rarer and more expensive ingredients
- Otherwise potion experience gain is as in the base game
- The reduction in experience becomes more severe as your alchemy skill increases, and behaves as follows:
	- You earn 50% of the normal experience if your skill is 30 or below
	- You earn 25% of the normal experience if your skill is between 30 to 60
	- You earn 12.5% of the normal experience if your skill is between 60 to 90
	- You earn 5% of the normal experience if your skill is 90+

**Potion making success rate**
- The base success rate of making a potion has been adjusted so that it is now: 
	- `(30 + (2/3 of your alchemy factor))%`
- The result is that 
	- At 5 skill you have about a 40% success rate
	- At 30 skill you have about a 55% success rate
	- You reach 100% success rate at about 80 skill, depending on your attributes

**Ingredient value influences potion making success rate**
- The average value of the ingredients used to make a potion now influence your chance of succeeding at making a potion
- Below a 10 gold average value there is no change to your success rate
- Above a 10 gold average value your success chance is increased by:
	- `(8.4 + (avg value * 0.158))%`
- In practice this translates to:

| Average ingredient value | Bonus to success rate |
| ------------------------ | --------------------- |
| 10g                      | +10%                  |
| 25g                      | +12%                  |
| 100g                     | +24%                  |
| 200g                     | +40%                  |

- The aim is to make it more rewarding to use expensive ingredients at low skill levels
- For example, if you make a potion using a gemstone worth 200g and some saltrice worth 1g, the average ingredient value would be 100.5g, and you would receive a flat +24% to your odds of making the potion


## 14, Pickpocketing overhaul

Pickpocketing has been reworked extensively, but sneaking and remainig undetected has not yet been addressed - so you will likely still have difficulty with not being noticed at low skill levels. However, if you can hide successfully, the value of what you can steal is more reasonable now

**Pickpocketing difficulty overhaul**
- In the core game your chance of pickpocketing anything more than 100-200g was essentially zero, even at maximum skill, due to how heavily weighted item value was in the equations
- The difficulty check for pickpocketing no longer takes into account the victim's attributes or skills (in the base game your chance of succeeding was lowered by the item's value, and by the NPC's sneak, luck, and agility scores)
	- This was removed to simplify the logic for development purposes. It could be added back in the future, but it didn't feel like it added much to the game
- The logic has been adjusted so that you now have a roughly 50% chance to steal an item with a value of `5g x  your 'pickpocketing term'`
	- You have a 50% chance, before the fatigue modifier is applied, to steal an item of the above value. At full fatigue (resulting in a fatigue modifier of x1.25) you have a 62.5% chance to pickpocket something with the above value
- Items which are above or below this value are harder or easier to steal according to this rule:
	- For every 5 gold the item is above or below the value which you would have a 50% chance to steal, add or subtract 1.5% to your success chance
	- For example if you have a 'pickpocketing term' of 40, you would have a 50% base chance to steal an item worth 200 gold
	- If you tried to steal an item worth only 100 gold, you would have a base 80% chance to succeed. Because you are trying to steal something 100g 'easier', the engine adds `((100 / 5) * 1.5)%` to your success rate
- See the table below for some guidelines on what items values you can expect to be able to steal at each skill

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

[1] The players pickpocketing term is calculated via`(sneak skill) + (agility * 0.2) + (luck * 0.1)`. This table makes some assumptions about player's attributes increasing along with their skills, and should be broadly correct if the player is trying to focus on the relevant stats as they play

**What appears in the pickpocket menu is determined by item value and the player's skill**
- In the base game when you opened the pickpocketing menu of an NPC, what appeared was randomly determined by a dice roll regardless of its value (your sneak skill made it more likely for any given item to appear, but the odds were completely independent of the item's value)
- To represent NPCs guarding their more valuable items closely, you now need a higher sneak skill to see more valuable items in the pickpocketing menu
- The rule is that: You can only see items in the pickpocketing menu if you have a base (before fatigue modifiers) 50% chance to steal that item
	- This way the player knows that if they can see something, they have a reasonable chance at stealing it without getting caught
- You can use the table above to see what value of items should appear at each skill/term level (the column which shows the amount you have a 50% chance to steal with a 1x fatigue modifier is what values will appear at each skill level)

**Core game bug fix**
- The player no longer has to pass an additional detection check when closing the pickpocketing menu
	- This was a core game bug that meant when you stole something you had to pass the initial difficulty check, and then immediately another check just for closing the window
	- Fixing this (along with the GMST changes in the ESP file) means that the above table is your actual chance of stealing, no longer do you have to roll twice, nor is your success chance capped at 75% as in the base game (it now has no cap, see below)

**Note on GMST behaviour**
- The GMST `fPickPocketMod` has been set to 1.0 in the ESP file (versus 0.3 in the base game)
	- This value is what is multiplied by the gold value of the item you are attempting to steal to determine the difficulty of the attempt
	- Note that the engine now treats this GMST differently in EncoreMP due to code changes, and expects it to be 1.0 to produce the above example difficulties  
- You can adjust the gold values which the player can steal by adjusting the GMST. Lowering it makes it easier to steal, for example setting it 0.1 in the new engine means that you would be able to steal (and see) 10x the stated values above

## 15, Athletics and swimming

- In the base game, the player's swimming speed is set to 50% of their running speed before factoring in their athletics skill. Levelling your athletics skill from 1-100 scales this from 50% of your running speed up to 60%. This was not very noticeable.
- Now your swimming speed scales from 50-80% of you running speed as you go from 1-100 skill
- A hard cap has been added as to how much your skill can increase your % swim speed (in both the base and modified game going past 100 does give additional benefits). Above 500 athletics there is no further percentage boost to swim speed
	- This cap was only added as guarding, since technically in both systems your swimming speed is rising proportional to the square of your athletics, so there is a slim risk of reaching some truly absurd numbers and crashing the game
  

## 16, Willpower buff

Willpower has been given a slight buff, and also now gives a small amount of resist magicka.
- Your willpower now contributes 1.5x as much as it did in the base game to your spellcasting success rate (before factoring in the fatigue modifier)
- Your willpower, when it is above 50 points, now gives you a small amount of resist magicka. This is not displayed on the UI, but it is properly applied behind the scenes
	- Every 10 points of willpower above 50 adds 2% resist magicka, so 100 willpower gives 10% resist magicka
	- This stacks with normal resist magicka additively, but still obeys the hard cap of 60% for resist magicka

## 17, NPC spellcasting locked to base game effect costs

This is a purely 'behind the scenes' change to the engines behaviour. If you are not changing the spell effect costs in the ESP file you can ignore this section.

NPCs are now hard coded to use the base game spell effect costs regardless of the ESP values that they have been set to. This means that the spell effect costs can be changed to any values without affecting NPC behaviour. The player is unaffected by this hard-coding and player cast custom spells will respond dynamically to spell effect cost changes.

 Without these engine changes, when spell effect costs were adjusted it would cause NPCs to change their decision making in combat and in some cases resulted in them finding it unusually difficult or easy to cast their spells. This was a core openMW issue.

A consequence of this is that the game now expects NPCs to only use handcrafted spells, or auto-calculated spells that were made (auto-calculated) in the creation kit with the base game spell effect costs. Tamriel Rebuilt does not change the spell effect costs, so this has no impact on any Tamriel Rebuilt content.

## 18, Miscellaneous changes

- The sound played when repairing equipment with armorer's tools has been reduced to 50% of the original volume
	- It was way too loud
- Enchanted on-strike weapons no longer display the "no-charge" message when their charge is depleted, and no longer play the "no-charge" sound effects when attacking with insufficient charge
- The server and client have been recompiled (a big thanks to Skooma-Breath for their help with the server) so that they have different checksums. This prevents EncoreMP clients and servers from connecting to other versions of tes3mp


# [4] V0.80 known issues & comments

**Base game pre-made spells retain their original magicka costs**
- [ ] Pre-made spells sold by merchants do not reflect the updated ESP spell effect costs - Instead of responding to the changes made in the ESP file, these spells retain their original magicka costs as if the magic effects were still at their base game values 
- This appears to be a core feature of OpenMW and tes3mp - and forcibly updating the magicka costs of all spells would result in changes to AI combat behaviour and changes to AI auto-generated spell lists
- For these reasons the base game spells were left at their original values for V0.80
- There is the potential to address this in a future version in a way that should preserve the original costs for NPCs and creatures, whilst giving the player the updated costed versions when buying pre-made spells (but this will not be a simple fix so it has been put on hold)
- The workaround during play in V0.80 is to buy a spell with the effects you want, and then to re-make it via spellmaking as a custom spell - anything made via the spellmaking menu will use the updated ESP effect costs
- Since some spell effects have been made more expensive in EncoreMP, pre-made spells which use those effects (levitate, open, fortify skill, etc) are now cheaper to cast than what the player would otherwise have access to via spellmaking or enchanting. For the time being, you will have to either manually edit these spells or simply house-rule not to use them

**Enchanting**
- [ ] Paying to enchant arrows via an enchanting service is currently too expensive due to a bug in the code
- [ ] The V0.80 changes to the enchanting code are a little 'fragile' - Some of the balance depends on the spell effect costs being set to the values in the V0.80 ESP. This will be addressed when enchanting is reviewed in the future
	- For the time being you can change the spell effect costs in the ESP file but be wary of the effect on balance, particualrly when lowering the costs of destruction or restoration effects

**Difficulty scaling**
- [ ] As of V0.80, player summons and player allies do not have their damage dealt scaled by difficulty. If you want a challenge avoid using them on high difficulties for now

**Resist magicka**
- [ ] If the player has more than 60% resist magicka, NPC/creature AI will still act as if they the player had values above 60% when making decisions about what to do in combat
	- This was intentionally left like this to avoid re-working the AI, as it would have an impact on AI on AI combat as well. It might be possible to update the AI to treat only the player differently, but this a very minor issue
- [ ] The UI still shows resist magicka values above 60%, but this is a UI issue only - the engine is working properly in regards to the mechanics

**Economy**
- [ ] Overall the changes to service costs and mercantile may prove to be too punishing. Some of this can be addressed by adjusting the GMSTs as described in the relevent sections

**Melee combat**
- [ ] An accuracy boost was given to all staff weapons as part of the melee overhaul. But this was actually done to all weapons in the class `BluntTwoWide`. In the base game this class is only used for staffs, and all other 2h blunt weapons are in a separate category. Modded content may class some powerful 2h blunt weapons as staffs, in which case they will be more accurate than intended in V0.80 (as of writing this however, this is not an issue for any tamriel rebuilt content)

**Experimental features**
- [ ] The acrobatics climbing feature is currently considered an experimental feature due to the risk of physics issues such as collision detection failures or clipping, however no issues have been found during playtesting

**NPC spellcasting**
- [ ] Several behind the scenes changes were made to the engine to clean up some core game (or at least inherent to OpenMW) issues which affect NPC spellcasting when spell effect costs are changed from their base game values. A consequence of these engine changes is that the engine now expects NPCs to be using spells that were made with the base game spell effect costs  
-  You can ignore this unless you are using modded content that: 
	-  [1] Changes the spell effect costs notably, 
	-  [2] Gives spells to NPCs with auto-calculated values, and
	-  [3] expects the NPCs to cast those spells with the auto-calculated values
- This scenario would have been an issue anyway in core openMW, due to the behind the scenes issues that needed fixing

**Server/Client visual checksum**
- [ ] The checksum has been correctly updated for the EncoreMP server/client (so that EncoreMP cannot connect to baseline tes3mp servers), however EncoreMP servers still display as "V0.8.1" in the server browsing UI
	- This was due to an issue with compiling - it is a UI problem only that will be addressed in the future

# [5] Partner files

**ESP companion**
- This overhaul requires the ESP file `EncoreMPV080` to function as intended. This ESP adds no new content, it only changes magic effect costs, experience gain values, and some GMSTs
- See the partner file "EncoreMP V0.80 ESP companion" for a full list of changes


**Compiling companion**
- If you are curious about how the changes were made, or the finer details of the mechanics, have a look at the partner file "V0.80 Beta release compiling changes"
- This file contains a complete list of all of the changes made to the base tes3mp code, and some coments on why many of the changes were made


