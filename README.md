# New Document 
# :gear: EncoreMP :gear:

Welcome to EncoreMP, an engine level overhaul of many of Morrowind's core gameplay mechanics. 

EncoreMP is a fork of tes3mp V0.8.1. The original tes3mp project is hosted here: https://github.com/TES3MP

Asides from the mechanical changes listed in this file, and the code changes detailed in the "EncoreMP compiling notes" file, all of the code used in this project is unchanged from tes3mp.

This project is in Beta. It's playable, bug-free (except for a few issues noted at the bottom of this file), but what it really needs is playtesting and feedback.  

 You can leave comments on the project discussion page on Github or get in touch with me via my reddit account,  
u/QuestionSure3480

If you enjoy this work please support tes3mp and OpenMW projects, without which this would not be possible!


### **EncoreMP project status**  

This is the sixth public beta release of EncoreMP: V0.93

**Hosted at**: https://github.com/Tower-Numid/EncoreMP

**Live release (V0.93) download page**: [add when setup]

#### Required and optional ESP files
- V0.93 requires the ESP `EncoreMPV093` to function as intended (this contains spell effect cost changes and minimal GMST changes)
- The optional content ESP `EncoreMPV093newcontent`  balances birth-signs and racial abilities
- The optional (but strongly recommended) spell buying ESPs update the magicka costs of spells for sale by NPCs (see the mechanics section for more details)
    - You should only load **one** of the three spell buying ESP files
    - These are a huge quality of life feature, but they are optional and can be left out if they conflict with other content


### **Contents**
1. An introduction to EncoreMP & Installation
2. Mechanical changes made by EncoreMP    
	2.1. Climbing    
	2.2. Difficulty system overhaul   
	2.3. Enchanting overhaul    
	2.4. XP gain changes    
	2.5. Training cost changes, and skill book toggle   
	2.6. Resist magicka cap    
	2.7. Melee combat changes    
	2.8. Hand to hand combat changes    
	2.9. Ranged combat changes    
	2.10. Armour rating changes (various)    
	2.11. Armorer overhaul    
	2.12. Mercantile overhaul    
	2.13. Alchemy overhaul    
	2.14. Pickpocketing overhaul    
	2.15. Swimming    
	2.16. Willpower buff    
	2.17. NPC spellcasting engine fixes    
	2.18. Misc changes    
	2.19. Sneak openMW fix    
	2.20. Updated spell magicka costs in spell-buying menus    
3. New gameplay settings
4. TES3MP project information
5. Known issues & comments
6. Partner files

# [1] An introduction to EncoreMP & Installation

### **What is EncoreMP?**

This is a mechanical overhaul of many of the core features of Morrowind, with the changes mainly hosted in the game's engine. It has been forked from tes3mp and so it is multiplayer compatible. 

EncoreMP has been designed with maximum mod compatibility in mind, and most especially for full compatibility with the Tamriel Rebuilt project. Every effort will be made in the future to keep this the case!

It achieves this by changing as little as possible in the ESP file, and by making all the engine level changes as 'content agnostic' as possible.

### **How is this different to other gameplay overhauls?**

EncoreMP hosts almost all of its changes in the games engine, not in an ESP file, and isn't hard-coded to work only with base game content. So it should be compatible with almost all ESP mods that add new features such as items, locations, followers, quests, graphics, etc    

EncoreMP itself adds no new content, and makes no graphical changes. The ESP file is limited to GMST setting changes only, and as few as possible.


### **What's the tone of EncoreMP?**

Encore tries as much as possible not to break from the spirit of the original game.

There are additions and balancing revision to many of the core mechanics, but ultimately the aim is for this to feel just like playing the original Morrowind did twenty something years ago when it came out.

The changes made seek to to breathe life into existing under-utilised systems, and to round out some of the rough edges of the balancing, without making anything feel 'gamified' or artificial.

I'd recommend EncoreMP for anyone who has already played the base game for a while, since you really need to see  why so many of us still love Morrowind after 20+ years!  

However if you really want to start with this, or if you are playing with a friend, you should have no problems starting out with Encore. It doesn't require you to know any of the behind the scenes mechanics.

This is still in beta and is in need of playtesting and feedback. Overall the game may feel a little harder at low levels, and the changes to the economy are likely the most punishing to the player, but nothing is meant to be harder just for the sake of it. 


### **What does EncoreMP change?**

These are some of the highlights of the changes made. For more information see the mechanics section below...     

Note: Unless stated, all changes made by EncoreMP affect only the player. NPCs and creature are intentionally unaffected, to ensure they behave and are balanced as per the base game

#### Skills
- Enchanting has been completely overhauled
	- Making scrolls is now worthwhile and viable
	- Every item will automatically update to have a reasonable enchantment capacity
	- When making enchantments, using larger souls will reward you with more XP and increase your success rates
- Alchemy has been heavily re-balanced
	- More expensive ingredients now create stronger potions, and increase your success rate
	- Potion strength logic has been adjusted so that you can make more reasonable potions at low and high skill levels
- The acrobatics skill now grants the ability to climb!
	- This does not involve any new mechanics or hotkeys, you will simply be able to walk up steeper and steeper slopes (up to 89° eventually) as your skill rises
- Weapon skills now also contribute to damage dealt, and weapon accuracy has been revised
- Ranged weapons are more accurate overall, and higher ranged weapon skill helps you recover arrows more often
- Unarmoured is much stronger at high levels, and your unarmoured rating now scales with your speed and agility attributes
- Armorer has been overhauled to be a more important skill (especially for warriors)
	- Expensive equipment is now more difficult to repair 
	- High armorer skill slows the rate at which your equipment degrades
- The athletics skill increases your swim speed much more than in the base game
- The Mercantile skill now gains experience from the value of the items sold, not from haggling
- Spellcasting now rewards more experience when you cast higher cost spells
- Pickpocketing has been completely overhauled
	- The value of items you can steal has been increased dramatically 
	- Various bugs have been fixed
	- Providing you can successfully hide, you will now find pickpocketing is a viable way of making money
- Most magic effects have had their costs adjusted via the ESP file, so that all spell effects are viable

#### General changes
- The difficulty scaling system has been completely overhauled
	- Magic damage, hand to hand, and summons now all scale with difficulty!
	- The scaling of melee damage has been adjusted
	- A new "difficulty tier" system has been introduced (as is used in Skyrim/Oblivion)
- Skills become much slower to advance as you approach skill level 100
- Skill training becomes are much higher than in the base game beyond the early levels
- The player no longer receives benefits from resist magicka values above 60%
	- This will be made optional via a toggle in future
- The willpower attribute has been slightly buffed, it now enhances spellcasting success rate a little more than previously, and grants small amounts of resist magicka when it is above 50

#### Quality of life
- The 'repairing equipment' sound has been turned down to 50% of it's original volume!
- Enchanted weapons no longer display the "out of charge" message or play the "no charge" sound effect when you attack whist they have no charge

#### Settings
- As of V0.93 several new server settings have been added which allow you to toggle off some of EncoreMPs features via the server config file 
- Almost all EncoreMP features will be tied to server settings in the upcoming releases

### Installation Guide

To play EncoreMP you need
- The steam install of Morrowind (other legal versions with unpacked data files will probably work too)
- That's it! Everything else is bundled in the release files

#### Installation

1. Download the release version of EncoreMP linked above    
2. Copy the required ESP file `EncoreMPV093` into Morrowind's 'data files' folder, as you would do with other ESP mods     
- `[2a]` (Optional but strongly recommended) Also copy over one of the spell list ESPs to enable updated spell magicka costs when buying from merchants (see below for more details on those)     
- `[2b]` (Optional) Copy over the optional content ESP as well if you want to try out the new racial abilities and birth signs
3. Unzip the rar file `EncoreMP.V0.93.beta.rar` anywhere on your computer that you are normally able to launch programs from    
4. Within the unzipped file, the folder called `EncoreMP V0.93 beta` contains the new engine and server
	- The .exe names are still `tes3mp` and `tesmp-server` but those are the new EncoreMP engine
5. Set up a server exactly as you would do for normal tes3mp
	- See here for general tes3mp server setup instructions https://github.com/TES3MP/TES3MP/wiki/Quickstart-guide
	- You do the same thing for EncoreMP, you just launch EncoreMP from the .exe files within the Encore server folder you downloaded
   - The default server `requiredDataFiles` for Encore lists Morrowind, Tribunal, Bloodmoon, and EncoreMPV093.ESP 
   - You can update this to include any other mods in the same way that you would do normally for tes3mp
   - If want to use one of the Encore spell list ESPs the optional content ESP add them to the server required data files
5. EncoreMP can then be played within the unzipped folder from anywhere on your computer  


#### A note on the spell list ESP files:
 - Using one of these ESPs is strongly recommended for quality of life. They will update the magicka costs of pre-made spells for sale at merchants for the content listed below:
 - Load only **one** of them!
    - Use `EncoreMPV093Spells1Base` for Morrowind, Bloodmoon, and Tribunal
    - Use `EncoreMPV093Spells2TRcore` for Morrowind, Bloodmoon, Tribunal, Tamriel Data, and Tamriel Mainland
    - Use `EncoreMPV093Spells3TRall` for Morrowind, Bloodmoon, Tribunal, Tamriel Data, Tamriel Mainland, Project Cyrodil, and Skyrim Home of The Nords
- If you have modded content not listed above you can still use it with or without these spell cost ESP files, the only consequence will be that any new pre-made spells added by the other modded content will not have their magicka costs automatically updated
    - You can make your own spell list ESPs to patch new content, see the notes on merchant spellbuying further down in this readme, and the compiling companion for how it works
	- Right now this is a manual process, but after the V1.0 release the hope is to automate this via an ESP creation program that will be included in the download
 




# [2] Mechanical changes

	2.1. Climbing    
	2.2. Difficulty system overhaul   
	2.3. Enchanting overhaul    
	2.4. XP gain changes    
	2.5. Training cost changes    
	2.6. Resist magicka cap    
	2.7. Melee combat changes    
	2.8. Hand to hand combat changes    
	2.9. Ranged combat changes    
	2.10. Armour rating changes (various)    
	2.11. Armorer overhaul    
	2.12. Mercantile overhaul    
	2.13. Alchemy overhaul    
	2.14. Pickpocketing overhaul    
	2.15. Swimming    
	2.16. Willpower buff    
	2.17. NPC spellcasting engine fixes    
	2.18. Misc changes    
	2.19. Sneak openMW fix    
	2.20. Updated spell magicka costs in spell-buying menus    

## [2.1] Mechanics: Climbing

#### The acrobatics skill now lets you climb
- The player's acrobatics skill now lets them climb increasingly steep surfaces by attempting to walk up them
- This is not true Daggerfall style wall climbing, but everything that is not a vertical surface is now climbable with enough skill
- This feature uses your modified acrobatics skill, so buffing it or draining it will change your climbing abilities mid-climb (be careful!)

#### Climbing angles
- If your skill is 30 or below, then you will have the base game slope climbing angle of 47° 
- Between skill levels 30-60 you add 1° of slope climbing angle per three skill levels, reaching 57° at 60 skill
- Above 60 skill you gain 1° of additional climbing angle per skill level with a cap hard limit of 89° reached at 92 skill

#### What that means in practice
-  47° - Reached at skill 30, base game behavior
-  57° - Reached at skill 60. This is a noticeable improvement, many base game hills can now be climbed if you search around for a shallow enough incline. This angle increase has more of an effect than the small increase in number might suggest
- 67­° - Reached at skill 70. The majority of exterior obstacles are now scalable in the base game with a little effort finding a route. This is not enough to climb buildings in urban areas (unless they have sloped sides) but more than enough for most wilderness trekking without having to rely on levitate
- 77° - Reached at skill 80. Practically any exterior obstacle is now scalable, although not necessarily in a straight line (some very sleep slopes may require some moving around to find a path still). A lot of spacious interiors (such as caves) are climbable now as well
- 89° - Reached at skill 92. Any surface with an angle of 89° or below can be climbed, this is essentially everything in the game apart from walls

## [2.2] Mechanics: Difficulty system overhaul

The difficulty system has been completely overhauled, and now affects all damage types

For ease of balancing during development, the game was also moved from a 'sliding bar' type difficulty, where any integer value could be used as the difficulty setting, to a a 'tiered' difficulty system like what appears in later games.   
The difficulty setting is still via the server config file as in core tes3mp.

The difficulty settings now scale ALL player damage dealt and taken including: Magic damage, fatigue damage from hand to hand, reflected spell damage, elemental shields, and summons/allies.  
Player allies (including summons) also obey the new difficulty scaling rules, but whilst they will deal less damage on higher difficulties they will not take increased damage like the player does (this is intended for balance reasons).

The difficulty tiers have been tuned for co-op multiplayer, so damage done is more heavily penalised than damage taken in this system.

#### New difficulty tiers

| Tier           | % Melee dealt [1] | % Melee taken | % Magic & other [2] dealt | % Magic & other [3] taken |
| :------------: | :---------------: | :-----------: | :-----------------------: | :-----------------------: |
| 1: Apprentice  | 100               | 100           | 100                       | 100                       |
| 2: Journeyman  | 75                | 150           | 85                        | 125                       |
| 3: Master      | 50                | 200           | 70                        | 150                       |
| 4: Grandmaster | 30                | 300           | 50                        | 200                       |
| 5: Agent       | 20                | 400           | 33                        | 250                       |
| 6: Nerevarine  | 15                | 500           | 25                        | 300                       |
 
[1] Both melee and on-hit enchantments scale using these values  
[2] Magic damage, hand to hand fatigue damage, and all types of damage dealt by player allies scale using these values  
[3] Magic damage and hand to hand fatigue damage taken by the player scale using these values
 
#### Notes on difficulty behaviour
- Magic damage taken only affects damage dealt to the player by other actors, so drinking potions or using self damaging scrolls will not cause you to take any more damage, nor will you take more magic damage from scripted effects or environmental sources such as traps (intended for balance reasons)
- Anything reflected onto the player deals 1x it's normal damage regardless of difficulty modifiers (so you won't die instantly if something is reflected at you on high difficulties)
	- But anything reflected by the player onto a non-player will receive the difficulty based magic damage reduction
- Physical damage taken by the player or enemies is first reduced by their armour rating, and only after that step do any difficulty modifiers apply
	- This is base game behaviour, and means that the % damage mitigation due to armour is constant across difficulty settings
- Player allies do not take any increased damage on higher difficulties, but deal less damage as described above. Any type of damage from an ally follows the above scaling: spells, melee, fatigue, etc, are all scaled the same way [2] for simplicity's sake

#### What counts as a player ally?
- The engine determines if something is a player's "ally" using the same reasoning that determines if something is a "friendly" summon in the base game:
    - If a creature/NPC will follow you through doors and it's not currently hostile to you, it's considered an ally
- Some examples of what is classed as an ally are:
    - All player summons (included any from modded content)
    - Commanded creatures/humanoids
    - Modded or base game companions
    - Quest companions who follow you through doors
- Some examples of things that are not considered allies:
    - A neutral/passive NPC fighting nearby (e.g. a guard fighting a cliffracer)
    - Temporary allies from quests that do not follow the player
	- Currently as of V0.93, a slight loophole: Anything summoned by an ally of the player is not considered the players "ally" (this is a very niche problem, you won't run into it during normal play)


#### How to change the difficulty tier

- The new difficulty tiers are based on the difficulty setting in the server config file as below
	- There is no difference in difficulty within a given tier, e.g. setting it to either 201 or 999 will have the same effect (Nerevarine difficulty), and setting it to 52 or 96 would both result in Master difficulty
	- The only reason the number ranges were kept was so that it would be easier to go back to a sliding scale system later on if needed

| Server config value | Tier           |
| :---------------:   | :------------: |
| 0 or less           | 1: Apprentice  |
| 1-50                | 2: Journeyman  |
| 51-100              | 3: Master      |
| 101-150             | 4: Grandmaster |
| 151-200             | 5: Agent       |
| 201+                | 6: Nerevarine  |



## [2.3] Mechanics: Enchanting overhaul

### [2.3.1] All items are automatically updated to have usable enchanting capacities
- All items in the game that can be enchanted have increased enchanting capacities, with a capacity of 30 (approximately) being the new minimum
- Very high capacity items from the base game or modded content are either unchanged or have been reduced in capacity slightly by the new logic
	- Making enchanted scrolls is now viable, as all paper items have gone from an enchanting capacity of 1-3 to around 30
- This change is made in the engine automatically whilst the game is running, and doesn't change the properties of any items in the ESP/ESM file 
	- This is a change to how the engine interprets the "enchanting capacity" property of items. Those values remain unchanged for the item, but the engine now does some non-linear math to convert them to different player facing values
- This works automatically for all modded content as a result!  

### [2.3.2] More experience is gained when making enchanted items using larger souls
- Making enchanted items now grants an XP multiplier based on the soul size used
- The XP multiplier scales linearly between the values shown below

| Soul Size     | XP multiplier |
| :-----------: | :---------:   |
| 0 to 60       | 1x to 2x      |
| 60 to 180     | 2x to 3x      |
| 180-400       | 2x to 4x      |
| 400+          | 4x            |


### [2.3.3] Larger souls improve enchanting success rate
- Making items using larger souls now increases your success rate by boosting your enchanting skill
- The skill bonus scales linearly between the values shown below, e.g. a soul size 90 grants a +12.5 bonus

| Soul Size     | Skill Bonus |
| :-----------: | :---------: |
| 0 to 30       | +0 to +5    |
| 30 to 60      | +5 to +10   |
| 60 to 120     | +10 to +15  |
| 120 to 180    | +15 to +20  |
| 180-400       | +20 to +30  |
| 400+          | +30         |

### [2.3.4] Enchanting success rate: general changes
- Your enchanting success rate still follows the base game logic, but with these additional changes for on-use and use-once items
	- You get an invisible +5 to your skill level to smooth out low level success rates
	- Using larger souls make enchanting easier, as above
	- For balance reasons, enchantments that cost over 30 points are slightly (1.5x) harder to make
		- This only applies to the portion of the enchantment above 30, e.g. a 35 cost enchantment now has a difficulty of 37.5
- On-strike items follow the same rules, but all magical effects used in an-strike enchantment take up double the capacity (and so are twice as hard to make) for gameplay balance

### [2.3.5] Enchanting scrolls
- Enchantments placed on scrolls use half the capacity that the same enchantment would on an 'on-use' item, so you can make effects that are twice as strong at the same level
- Scrolls have a lower difficulty to enchant compared to on-use items, providing the enchantments total size is less than 10
	- This is to help out early game enchanters
	- The bonus drops off linearly as the enchantment size approaches 10

### [2.3.6] Enchanting ammunition 
- Ammunition will now always enchant in batches of 20 and the OpenMW setting "projectiles enchant multiplier" has been disabled
- Ammunition receives the same success rate boost that scrolls do when the total cost is below 10, and otherwise they obey the on-strike difficulty and capacity rules 

### [2.3.7] Constant effect enchantments
- Constant effect enchantments follow their own difficulty logic that scales off of the players base/unmodified enchanting skill
	- All constant effect enchantments check your base enchanting skill, and either have a 0% or 100% chance of succeeding, based on the size of the enchantment vs your enchanting skill
	- [`A server setting has been added which can toggle this feature off if you want to use the base game's constant effect logic`]
- Your skill level determines the size of the the constant effect enchantment you can make, as in the table below
- The logic linearly scales the size allowed between the values shown


| Base skill     | Constant effect size allowed |
| :------------: | :--------------------------: |
| Below 59       | 0                            |
| 60 to 70       | 5 to 15                      |
| 70 to 80       | 15 to 35                     |
| 80 to 90       | 35 to 65                     |
| 90 to 99       | 65 to 101                    |
| 100            | Any size                     |


### [2.3.8] Using multiple effects in an enchantment no longer increases the cost
- In the base game, making an item with multiple magic effects caused the cost to compound, so that the final enchantment was greater than the sum cost of the individual effects. This is no longer the case

### [2.3.9] How enchanting skill reduces the cost of using an enchanted item has been changed
- The cost of using an enchantment scales linearly down from 100% at 1 skill, to 20% at 100 skill
	- There is no further benefit beyond 100 skill. Using a magic item can never cost less than 20% of the original charge required
- In addition to the above, all on-strike enchantments have a flat 0.25x cost modifier, so your enchanted weapons will last a lot longer
	- e.g. if an on-strike enchantment costs 20 points to cast and you have 100 skill, your skill reduces the use cost to 4 points, and the on-strike modifier takes it down to 1 point per swing!

### [2.3.10] Destruction, restoration, and other damaging effects take up more enchantment capacity

- All spell effects from the destruction and restoration schools, as well as absorb health and fatigue have had their enchantment point costs doubled for enchantments
	- This was done purely for balance reasons, so no more 100 damage on strike weapon enchantments :<

### [2.3.11] The cost of using enchanting services has been adjusted
- Constant effect enchantments cost 2x the GMST value per point (the GMST is 1000 by default, so a 100 point CE will now cost 200k gold before mercantile discounts apply)
- On-use, on-strike, scrolls, and ammunition all retain the base game costs up until 30 points of enchantment capacity. After that point each additional point of capacity costs 1.5x the normal value
	- This mirrors the new enchanting difficulty for the player, which gets harder above 30 points
	- For example, a 30 point enchantment would cost 30,000 gold. A 40 point enchantment would cost 45,000 gold, because the 10 points above 30 cost 1,500 each (or whatever 1.5x the GMST is)
- Scrolls follow the same pricing rules but are then discounted to 1/25th of the GMST value per point, so a 20 point scroll costs 800gp before mercantile discounts apply
	- Note that scrolls use half the enchantment capacity compared to other items, so you are also getting a stronger effect for the same price
- Ammunition follows the above rules with two additional rules,
	- Enchanting ammunition is also heavily discounted, to 1/20th the GMST value per point (so 50 gold by default)
	- Enchanted ammo is made in up to stacks of 20 at no additional cost
	- For example, making 20 enchanted arrows with a 20 point enchantment each would only cost 1,000 gold before mercantile discounts apply, because you are getting a bundle of 20 arrows at 1/20th of the equivalent on-strike price
	- If you have less than 20 of that item, the cost is discounted accordingly, so you could just pay for a single arrow if you are really broke!

## [2.4] Mechanics: Experience gain adjustments

- The rate of experience gain for all skills has been modified, so that the player earns less experience at high skill levels
- Many XP values from using skills have been adjusted in the ESP file as well (see the ESP companion file)

### General changes
- In the base game a skill required experience equal to its level to advance. This logic has been kept as a baseline, but there are now some additional rules that apply:
- A skill can never require less than 20 experience to advance
	- This was done to make early skill choices more meaningful
- Experience gain is reduced for skills above level 50 as in the table below

| Skill level    | XP mutliplier  | Like levelling...  |
| :------------: | :------------: | :------------: |
| Below 50       | No change      | Normally |
| 51 to 60       | x0.8           | 20% slower |
| 61 to 70       | x0.65          | 50% slower |
| 71 to 80       | x0.55          | 80% slower |
| 81 to 90       | x0.4           | 150% slower |
| 91 to 100      | x0.33          | 300% slower |


### Experience gained from casting spells is now proportional to the spell's cost

- For spells that cost 5 or less magicka, there is no increase to the experience gained from casting
- For spells that cost more 5 or more magicka you receive a multiplier to the experience earned, based on the spells cost
- This scales linearly from 1x experience at 5 magicka to 4x experience at 50 magicka, there is no further increase in XP gain for spells costing more than 50 magicka
	- Each point of magicka above 5 adds 0.066 to the XP multiplier

### New server setting to globally increase/decrease XP gain 
- A new server setting has been added which acts as a global XP gain modifier
- This reduces or increases all XP gained by a percentage, which stacks with the new logic above
- This was added so that you can slow down XP gain globally to delay reaching the point where your character basically becomes a god
	- It's especially useful Tamriel Rebuilt characters, due to the volume of content there is
 
## [2.5] Mechanics: Training cost changes, and skill book toggle

- Skill books no longer grant skill increases when the relevant skill is level 90 or above
	- [`This feature can be disabled in the server settings`]
- Paying for skill training is more expensive across the board, and the cost now scales non-linearly with your level
- This new system respects the GMST (`iTrainingMod`), so you if you want to adjust the training costs shown below you can do so by adjusting the GMST
- Note that these are the base costs to train a skill prior to any discounts/penalties due to mercantile applying, in practise they will be cheaper


| Skill  level | Base game cost | EncoreMP cost |
| :------------: | :--------------: | :-------------: |
| 10           | 70             | 200           |
| 20           | 140            | 300           |
| 30           | 210            | 400           |
| 40           | 280            | 700           |
| 50           | 350            | 1,000         |
| 60           | 420            | 2,100         |
| 70           | 490            | 3,200         |
| 80           | 560            | 4,600         |
| 90           | 630            | 6,400         |
| 99           | 697            | 10,200        |


## [2.6] Mechanics: Player resist magicka cap

- The resist magicka effect has been capped at 60% effectiveness for the player, it is no longer possible to fully resist effects governed by resist magicka
- This was a balancing decision, as previously it was far too easy to temporarily reach 100% resist magicka and become immune to so many detrimental effects on unique items (such as boots of blinding speed)
- The engine does not apply this cap until after all 'weakness to magicka' effects have been accounted for, so this is a net cap of 60% resist magicka after all weakness modifiers have been applied
	- Weakness to magicka negates resist magicka at a 1:1 ratio
	- If a character had a 20% weakness to magicka effect and then cast a spell granting them 70% resistance to magicka, the net result would be that they have 50% resistance to magicka
	- The engine allows this example, because it is not blocking magnitudes above 60, just after all weaknesses and resistances have been balanced out, the final value cannot exceed 60
- Known issue: The UI still displays resist magicka values above 60%, but this is a display issue only and does not affect the mechanics
	- This is being treated as a 'feature not a bug', as due to the way resist magicka negates weakness 1:1 it is useful for the player to know their actual resist magicka effect magnitudes
- Known issue: If the player does achieve a net resist magicka score of 100% or more, opponents in combat will still behave as if the player had immunity to the relevent effects (e.g. blind, burden, etc) despite this no longer being the case
	- As in the base game, enemies will avoid targeting the player with effects that they are immune to  
	- So if the player buffed themselves to a net 110% resist magicka, Encore would properly cap the resistance to 60%, but as the combat AI has not been adjusted to account for this, all opponents will forego attempting to cast the relevant effects at the player whilst the net resist magicka value is in place
	- It was decided to leave this AI behavior mismatch unchanged, as otherwise the AI would have to have been adjusted which could have resulted in unintended behaviour (especially when an AI is fighting another AI, like a summon or a guard)
	- This may be changed in a future version, but it's not a top priority

## [2.7] Mechanics: Melee combat changes

### Weapon accuracy
- Melee accuracy has been increased at low skill levels, and scales slightly slower with skill than before
- The player now receives an invisible +10 to hit, and skill now adds 0.8 to hit per skill level instead of 1 per skill level
	- Equation: (10 + (weapon skill x 0.8))
- In practise this means against most enemies your base hit chance at 5 skill is around 15%, not 5% as previously
- However due to the slower scaling, you end up with only around a 90% hit chance at a 1x fatigue modifier at 100 skill
- This was done to make levelling your weapon skills all the way to 100 more important (see also the damage scaling changes below that also rely on skill)

### Two handed weapons now give a flat -15% chance to hit 
- This was added to make the choice between one and two handed weapons more meaningful, and to distinguish two handed weapons as items requiring more skill to use effectively
 -  There are some exceptions to this, see the weapon type changes below
	- The 2h accuracy penalty can be disabled in the `server settings`
	- Spears are exempt from this penalty as they are the only weapon type with no one-handed variants, so it felt too punishing to include them (and it gives them a niche as a slightly lower damage 2h weapon, but with more range and accuracy)

### Weapon damage scaling
- Your weapon damage is now modified by both your weapon skill and your strength attribute
- Your skill adds +25% damage at 100 skill, and inflicts a -25% damage penalty at 1 skill
- Your strength add +25% damage at 100 strength, and inflicts a -25% damage penalty at 1 strength
- These stack, so to reach the +50% damage modifier you got at 100 strength in the base game, you now need 100 strength and 100 in the relevant weapon skill

### Weapon type specific changes
- **Short blades** receive a flat +10% to hit (equivalent to about 15 skill levels)
- **Spears** receive are exempt from the 2h hit penalty as noted above
- **Staves** (a sub-set of blunt weapons) receive a flat +20% to hit, and ignore the -15% hit penalty that applies to other 2h weapons
	- Staves are classified as anything in the category `BluntTwoWide`
	- All staff weapons in the base game and in Tamriel Rebuilt have very low damage
	- If a mod adds a powerful two handed blunt weapon and classifies it as `BluntTwoWide` in the ESP file, it will also receive this accuray boost and may be overpowered
	- In this case, the staves accuracy bonus can be disabled in the `server settings`, and if it is then staves will take the 2h accuracy penalty unless that setting is also disabled in the `server settings`


## [2.8] Mechanics: Hand to hand combat changes

### Accuracy
- Hand to hand combat scales it's accuracy using the same updated logic as other melee weapons 
	- Equation: (10 + (weapon skill x 0.8))

### Health damage done
- The health damage done by hand to hand attacks has been increased by changing the GMST in the ESP file,`fHandtoHandHealthPer`, from 0.1 to 0.4
	- This GMST value is multiplied by the fatigue damage that your hand to hand attacks deal to determine the amount of health damage that they deal against vulnerable targets 
	- So this is in practise a 4x increase in the health damage done by hand to hand attacks, but does not affect  the fatigue damage done

### Damage done - general
- Damage done has been increased at low skill levels, and it now scales slightly slower, reaching the same final damage at 100 skill
	- The previous formula was `damage = skill`
	- The new formula is `damage = (skill x 0.9) + 10`
    - As a result, buffing the skill past 100 is slightly less effective than before, but only slightly
	- This makes low skill levels slightly more useful. They are still not good, but it is somewhat more reasonable now to go punching mudcrabs

### OpenMW strength scaling change
- The OpenMW setting for scaling your hand to hand damage with your strength was adjusted so that it behaves like strength scaling does for weapon attacks in the base game. 
- The new behaviour is:
	- For every point of strength above or below 50, plus or minus 1% damage
	- So at 100 strength, do +50% damage, and if drained to 1 strength, do -49% damage
- It is recommended that the hand to hand strength scaling setting is left on in the `server settings` (it is on by default in the release files)
- This change also works for players in werewolf form
- The old OpenMW behaviour for this setting was:
	- Add +100% damage for every 40 strength levels above 40, so at 100 strength you did +150% unarmed damage (which resultd in some very wonky balance)
- Note that unlike other EncoreMP changes, the strength scaling affects NPCs too 
	- This was the case with the old OpenMW strength scaling setting, so I have left it that way for now


## [2.9] Mechanics: Ranged combat changes

### Accuracy
- Ranged weapons follow the same logic as the melee accuracy changes, but in addition all ranged attacks receive a flat +10% to their hit chance

### Damage
- Bows and crossbows scale their damage using the same updated logic that melee does (half of the modifier comes from skill and half from attributes) however bows and crossbows use your agility instead of your strength to scale damage
- Throwing weapons scale using your strength and your skill instead of agility and skill
- Strength and skill have a greater effect on throwing weapons than on any other weapon type,
	- All throwing weapons reach 200% of their base damage at 100 strength and 100 skill instead of 150% as with other weapons
	- This was done to help them stay competitive into the late game

### Ammunition recovery
- Non-enchanted ammunition is now recovered more frequently from enemy corpses as you increase your ranged weapon skill
- From skill levels 0 to 25 you will recover ammunition at the rate you do in the base game 
    - 1x the GMST value `fProjectileThrownStoreChance` - which is 25% by default
- Above skill level 25 your chance of recovering ammunition linearly increases with your ranged weapons skill from 1x the GMST value to 4x the GMST value at 100 skill
- So if you are using the default GMST value of 25%, you reach a 100% recovery rate of unenchanted ammunition at 100 skill
	- At this value, your recovery rate is equal to your skill, with a floor of 25%
- This respects the GMST, and will scale accordingly as you adjust the GMST

### Enchanted ammunition recovery
- It is now possible to recover enchanted ammunition once your ranged weapon skill is above 50
- Below skill level 50 you cannot recover magical ammunition
- Above 50 your chance of recovering magical ammunition scales linearly from 0% at 50, to 2x the GMST value at 100
	- For example, at 75 skill you have a 1x GMST chance to recover magical ammunition (25% by default)
	- At 100 skill you have a 2x GMST chance to recover magical ammunition (50% by default)
- For balance reasons, you cannot exceed a 2x GMST enchanted ammunition recovery rate (reached at 100 skill), buffing your ranged skill past 100 will have no effect on your enchanted ammunition recovery rate
- This also respects the GMST, and will scale accordingly as you adjust the GMST
	- For example setting `fProjectileThrownStoreChance` to 10 would result in a 20% chance to recovery magical ammunition at 100 skill

## [2.10] Mechanics: Armour rating adjustments (player and creatures)

### Player: Equipment derived armour ratings

- For the three armour skills (heavy, light, and medium) the equation used to determine armour rating when you are below skill level 30  has been adjusted to be less punishing
- In the base game your armour rating from equipment is equal to:
	-  `Armour rating * (your armour skill / 30)`
- This meant that at 5 skill you only got 16% of the AR of a piece of equipment
- This was changed to be less punishing since low skill levels now require more experience to advance in Encore
- The new logic used to determine armour rating below skill 30:
	-  `Armour rating * ((your armour skill + 5) / 35)` 
- Then once you reach 30 skill level 30 it goes back to base game  behaviour
- See the table below for how this practically works out at low skill levels

| Skill | Base game % armour rating | EncoreMP % armour rating |
| :-----: | :------------: | :------------: |
| 5     | 16           | 28           |
| 10    | 33           | 42           |
| 15    | 50           | 57           |
| 20    | 66           | 71           |
| 25    | 83           | 85           |
| 30    | 100          | 100          |


### Creatures: Innate armour ratings
- Previously all creatures (anything that wasn't a player or an NPC) had armour ratings of 0, regardless of their level
- This has been changed so that creatures have a passive armour rating determined by their level, as in the table below

| Creature level | Armour rating |
| :------------: | :-----------: | 
| 0-4            | 10            |
| 5-9            | 12            |
| 10+            | 15            | 


- This was done to make creatures a little more durable overall, but the values were kept small to maximise balance compatibility with modded content


### Player: Unarmoured armour ratings
- The unarmoured skill has been buffed (a lot) to help it remain viable on high difficulties (without having to rely on fortifying it past 100)
- The base game logic was:
	- Unarmoued rating is equal to `(your unarmoured skill)^2 x 0.0065`
	- This is quadratic scaling, so it was very weak unless you buffed your skill a lot, then it got too good
- The new system adjusts the scaling so that you can achieve viable armour ratings at lower skill levels
	- It also makes it so that your unarmoured score receives a % multiplier for having your agility or speed above 50
- See the table below for the new armour ratings the player will receive, the logic linearly scales between the values shown

| Unarmoured skill | Unarmoured rating |
| :--------------: | :---------------: | 
| 0-30             | 0-10 AR           |
| 31-70            | 10-75 AR          |
| 71-100           | 75-150 AR         | 

- Your agility and speed attributes then modify this further, if either of them are above 50
	- For both attributes, for every 2 points they are above 50, add 1% to your unarmoured rating
	- For example at 100 speed and 50 agility you would receive a 1.25x multiplier to your AR
	- At 100 speed and 100 agility you would receive a 1.5x multiplier
- There are no penalties to your unarmoured rating if either attribute is below 50
- The calculations above respect the GMST `fUnarmoredBase1`

| Unarmoured skill | Unarmoured rating | +50% from 100 speed/agi |
| :--------------: | :---------------: | :---------------: | 
| 0-30             | 0-10 AR           |   0-15 AR         |
| 31-70            | 10-75 AR          |   15-112 AR        |
| 71-100           | 75-150 AR         |   112-225 AR       |


## [2.11] Mechanics: Armorer overhaul
In the base game once you were able to reliably repair an iron sword, you could reliably repair anything, so there was not much benefit to levelling the skill beyond a certain point.  

The following changes have been made to increase the value of the skill
- More expensive items are now harder to repair
- Your armorer skill now passively slows down the rate at which equipment loses durability in combat
- Higher quality armorer's tools now add to you repair success rate, in addition to the base game behaviour of increasing the amount you repair per success
- It now costs significantly more to pay services to repair expensive items, proportional to their value

### The armorer skill now slows the rate at which items degrade
- Your equipment now takes (`armorer skill x 0.075`)% less damage from combat
	- Equal to 0.75% less equipment damage per skill level
- There is a hard cap of 75% less equipment damage reached at 100 skill

### More expensive items are harder to repair
- The base gold value of an item now determines how difficult it is to repair, with more expensive items being more difficult
- Your success rate improves with your skill, strength and luck, and it is improved by tool quality (see below)
- The new logic enforces a minimum success rate of at least 15% regardless of your skill level, to stop the skill becoming mandatory
	- But you will need a lot of hammers if you are trying to repair ebony with only a 15% chance per swing!
- The table below shows the enforced minimum success rates, as well as typical skill levels required to reach 30% and 50% repair rates
	- The logic used here is a little opaque, but basically aim to have enough skill to repair an item 30% of the time if you plan to constantly use it
	- Since your strength, luck, and tools also boost success rate, these are approximate values, you will find strong or lucky characters need a little less skill

| Armour value (g) | Weapon value (g) | Aprox. skill to achieve 30% success | Aprox. skill to achieve 50% success |
| :--------------: | :--------------: | :---------------------: | :---------------------: |
| 0-100            | 0-500            | 30                   | 40                   |
| 100-500          | 500-2000         | 35                   | 45                   |
| 500-2000         | 2000-5000        | 37                   | 50                   |
| 2000-5000        | N/A              | 45                   | 55                   |
| 5000-20,000      | 5000-20,000      | 60                   | 70                   |
| 20,000-50,000    | 20,000-50,000    | 70                   | 80                   |
| 50,000 +         | 50,000 +         | 80                   | 90                   |

- Around a 30-50% success rate is enough to maintain equipment reliably (the amount you repair per swing scales with your success rate as in the base game)
- Weapons are overall easier to repair than armour, as having your weapon break can be devastating and I didn't want to make the skill be mandatory
- The balance of this will likely be adjusted in future versions
  
### Tool quality affects success rate when repairing
- Tools now modify your repair success rate based on their quality, in addition to the base game effect of boosting the amount you repair per swing
- The new success rate logic is:
	- For every 0.1 quality above or below 1, add or subtract 2 skill levels to the attempt
- For example using a grandmaster's hammer (quality 1.7), effectively adds 14 skill levels
- Whereas repair prongs (quality 0.5) effectively remove 10 levels (but you can still never fall below the minimum success rates above)
- This should reward you for finding the best tools, and let you maintain things above your level

### Paying to repair items is more expensive
- Items now cost more to repair based on the base value of the item
- This was technically already the case in the base game, but you could never be charged more than 1gp for each point of item health you were repairing
- This cap has been raised, and the new rule is:
	- The cost to repair an item fully is 1/3 of it's base value (before mercantile discounts apply)
	- The repair cost is then multiplied by the GMST `fRepairMult` (which is 1.0) to determine the final price
- During testing an issue was found, some items in the base game have very high values and very low health, e.g. a Fiend Helm only has 50 item health, but is worth 6000 gold
- To stop the repair costs for items like this being absurd, a cap of around 3gp per item health has been enforced, you will never be asked to pay more than this
	- So with the example of a Fiend Helm, to pay to have it fully repaired will only cost around 150gp, not 2000 gold!
 

## [2.12] Mechanics: Mercantile overhaul

### The player now earns experience from the value of items sold, not from haggling
- The player now earns mercantile experience not from haggling, but from how much gold they make selling items
	- Experience from haggling has been completely disabled at present, though it may be enabled again in future
	- But as it is gold you earn from selling items, not from the base value of the items, haggling will still help a little, but now you should only need to use it if you are short on cash, not to earn XP
- You only earn XP from selling things, not from buying them
	- This was intentional, as otherwise the skill proved far too easy to level during testing
- The player earns around 1 experience for every 100 gold they make from selling things
	- For example at skill 30 you need 30 experience to level up (less if mercantile is one your major/minor or specialisation skills), so you would have to make around 3000 gold selling things to advance a level
- This rate of XP gain governed by the XP value for a "successful bargain" in the ESP file, which is 0.45 by default
	- If you want to halve the amount of gold needed to earn experience, double the amount of XP earned from a bargain to 0.90, etc
- Selling items for less than what the merchant offers you will award you less experience, proportional to how much you discounted the sale (as giving things away cheaply is not good merchant behaviour)
	- So if a  merchant only has 100 gold left and they offer to buy an item for 1000g, if you discount that item down to 100g just to get rid of it, the XP gain for that sale is reduced to 1/10th
	- This was partly a balance thing, but also realism - you aren't going to become a great merchant if you keep giving things away
- You will also earn XP from the value of any items received in return for an item you are selling, up to a limit
	- For example if you wanted to sell that 1000 gold item above, and the merchant only had 100g, you could ask for 900g of items in return (to get the net sale value to zero without you having to discount it), and then you would earn full XP from the sale
	- You can't earn more XP this way than you would have earned from just selling your item for gold
	- For example if you had an item worth 1000g, and you traded it for items worth 2000g (making up the difference with some gold of your own), you would only earn XP for the 1000g worth of items you sold in that transaction
- All of this is using the actual sale value of the items as you see it in the trade window, not their base value, so a higher mercantile skill will make it easier to earn XP (and trading with very skilled merchants will make it harder)

### Disposition has less of an effect on mercantile interactions
- The engine was changed so that an NPC's disposition being above or below 50 now only has one quarter of the effect on mercantile bartering rates than it did in the base game
	- Bartering rates are determined by disposition, attributes, and skill - in the old system the discounts from disposition were so large they tended to overshadow changes in your skill and personality, which made them feel less relevant past a certain point
- To pair with this change, the GMST `fDispositionMod` has been set to 0.25, down from 1.0 in the base game
	- This GMST controls how much disposition affects your ability to haggle, lowering it to 0.25 makes it 1/4th as effective at helping you haggle and brings haggling in line with the reduced effect disposition has on item sale values

### Bartering and haggling rate caps
- Bartering rates are what a merchant will offer your for an item initially, haggling is when you adjust the price via the + - buttons to try and get a better deal
- Bartering rates have been hard capped to:
	- You can never sell an item for more than 60% of it's base value, and you can never buy an item for less than 90% of it's base value
	- You can never be asked to pay more than 150% of an item's value (if you have very sow skill), and you will always be able to sell an item for 20% of it's base value regardless of your skill
- Haggling rates have been hard to:
	- You can never haggle an item to sell for more than 110% of the initial offer made
	- You can never haggle an item be sold for less than 90% of the initial offer made
- Together these caps were needed, as several exploits existed in the base game (and this system), where with the right buffs you could buy an item and sell it right back to the same merchant for more than you paid via haggling
	- Collectively these caps mean that even with perfect haggling, you can never sell an item for more than 70% of it's base value, and you can never buy an item for less than 80% of it's base value  
- **Important note**: These caps do not apply to services like training, repairing, enchanting, etc, there is no limit to the discount you can achieve for these services (other than the natural limits that exist in the base game)

## [2.13] Mechanics: Alchemy overhaul

This is a complete overhaul of the skill, changing nearly all of the equations used, but the end result is it still behaves in practise a lot like core alchemy. There are no changes to the principles of potion making or effect behaviour, just the equations that govern the results

### Summary
- The strength of a potion effects is now calculated using spellmaking logic
	- In the base game potions, and only potions, used their own bespoke spellmaking logic that didn't even slightly match up with normal spellmaking, so the balance was extremely wonky at the high and low ends
- Potions of the same type no longer stack
	- If you drink five of the same healing potion, you no longer heal 5 times as fast
- Potion values are now capped to be no more than the sum value of the ingredients used to make the potion
	- To stop many of the infinite money exploits that alchemy is known for
- Potions made by the player can never weigh more than 1, and by high skill levels most will weight around 0.1
- The average value of the ingredients used to make a potion now affects the strength of the potion, the success rate, and the XP you earn
- All alchemy tools have had the equations governing them changes, but they retain the same functions they do as in the base game


### [2.13.1] Potion strength part 1, spellmaking logic

This logic that determines potion strength has been significantly changed from the base game to bring it in line with the logic used in enchanting and spellmaking. This was done to balance potion strengths with other sources of magic, and to prevent some unusual behaviour when spell effect costs are changed to be very low or very high in the ESP.

To calculate potion strength, the new system does the following:
- Work out your alchemy factor as in the base game (this is determined by your skill, luck, and intelligence)
- Divide the alchemy factor by 4 to calculate the effects 'magicka budget'
- Using the magicka budget for the effect, calculate the duration/magnitude of the effect as if it were a spell being cast by the player that cost that much magicka
	-  The engine allocates about half the magicka to duration, and half to magnitude
- For potions with multiple effects, the full magicka budget is given to each separate effect in a potion, it is not split between the effects
	- So it is always an upside to have multiple positive effects in a single potion
- For example, if the player had an alchemy factor of 20, any effects they make on a potion will last as long as and be as strong as an equivalent 5 magicka spell with around half its cost spent on duration and half on magnitude

### [2.13.2] Potion strength part 2, valuable ingredients make stronger potions

- The average value of the ingredients used to make a potion now affects the strength of the potion (by modifying your alchemy factor) as in the table below
- The engine adds the flat value shown to your alchemy factor, and then also applies the % multiplier shown to the final value (so that at high skill levels where the flat bonus becomes less relevant you are still incentivized to use expensive ingredients for the % bonus )
	- `(Alchemy factor + Flat skill bonus) * Final factor multiplier`


| Average ingredient value (g) | Flat skill bonus  | Final factor multipler |
| :--------------------------: | :---------------: | :--------------------: | 
| Less than 5                  | 0                 |   0.7                  |
| 5-10                         | 10-15             |   1.0-1.05             |
| 10-25                        | 15-25             |   1.05-1.10            |
| 25-100                       | 25-35             |   1.10-1.15            |
| 100-200                      | 35-45             |   1.15-1.20            |
| Above 200                    | 45+ (special)     |   1.25                 |

- The logic interpolates between both of these sets of values using non-linear equations, so these are not break points, just examples
- There are two special cases
	- The multiplier is hard capped at 1.25x no matter the ingredient values
	- The flat bonus continues to increase based on ingredients value beyond +45 at 200g, and this has no cap
	- The scaling beyond +45 at 200g is very generous, to reward you for using the truly rare and exceptional ingredients in the world

### [2.13.3] Potion strength part 3, the effect of mortar quality on potion strength has been halved
- The potion strength multiplier you receive from the quality of mortar and pestle you are using is calculated as in the base game, but the strength of the final multiplier is halved
	- For example if you are using a grandmaster's mortar and pestle you would have previously gained a 150% multiplier to potion strength, whereas now you would receive a 125% strength modifier
	- The same is true for low quality tools, previously an apprentice's mortar and pestle gave you a 50% multiplier, whereas now it gives you a 75% multiplier
- This was done to narrow the range of potion strengths for balancing purposes, and also to make the other alchemy tools more important

### [2.13.4] Potion strength part 4, the equations governing the other alchemy tools have been changed
- The retort now multiplies the duration and magnitude of all positive effects by:
	- `1 + (retortQuality / 10)`
	- For example with a 0.5 quality retort, you get a 1.05x multiplier (+5%) to both duration and magnitude
	- A 2.0 quality retort gives a 1.20x multiplier (+20% to both duration and magnitude)
- The calcinator still boosts both positive and negative effects, but negative effects are more significantly increased now
	- Positive effects use the same logic as the retort (+5% at 0.5 Quality, +20% at 2.0 Quality)
	- Negative effects receive three times that modifier (+15% at 0.5 Quality, +60% at 2.0 Quality)
	- Now whether to use a calcinator will be a real choice sometimes 
- The alembic still weakens negative effects by multiplying them by:
	- `1 - (alembicQuality * 0.4)`
	- For example, a 0.5 quality alembic now multiplies negative effect duration/magnitude by 0.8 (20% reduction)
	- A 1.5 quality alembic multiplies them by 0.2 (80% reduction)
	- There is a hard cap of 90% reduction (a 0.1 multiplier) reached at a tool quality of 2.25
	- This was added to account for any modded tools that go this high, there are none in the base game
- Note all of these modifiers apply directly to the duration and magnitude values, not the effect budget, so they have a larger impact than the numbers might otherwise suggest
	- This was how they worked in the base game, so I've kept it that way
- All of the modifiers from tools stack multiplicatively, not additively

### [2.13.5] Potion strength summary, order of operations for determining potion strength

To help understand how the engine works out final potion strength, the order it calculates things in is:

1. Calculate your alchemy factor as in the base game
2. Modify the alchemy factor based on ingredient value
3. Apply the effect of mortar quality to the alchemy factor
4. Calculate the effect duration/magnitude using normal spellmaking logic
5. Apply the effect of other tools to the duration/magnitude of any effects


### [2.13.6] Potion values
- The value of any potions made by the player can never exceed the sum value of the ingredients used
- This is a harsh cap, you no longer make money with alchemy, but it was necessary to close many of the infinite money exploits
- It may be relaxed in future

### [2.13.7] Potion weight
- Previously potion weight was the average weight of the ingredients used, which resulted in potions made from things like ebony or scrap metal being too heavy to be practical
- Now potion weight is hard capped to 1.0, and based on your skill the final weight can be as low as 0.1 per potion
	- First potion weight is calculate as in the base game
	- Then it is hard capped to 1.0
	- Then it is reduced by `(alchemy factor / 100)` to a minimum of 0.1
- Now by around skill 90 every potion you make will weigh 0.1 regardless of ingredient weight
	- For example using two ingredients that each weight 0.5 would normally give you a 0.5 weight potion, but now at around skill 40 that potion would be reduced to 0.1 weight
	- The idea is that you need to be more skilled to be able to distill down very heavy ingredients

### [2.13.8] Potions no longer stack
- Drinking multiple of the same potion now refreshes the duration of the effects instead of applying multiple copies of the effects
	- This is how spells work in the base game
- This closes lots of combat exploits like drinking 100 sujamma or 10 of the same health potion at once, in both these cases the effects don't get any stronger the more you drink
- But effects from different potions are still allowed to stack, so if you drank a potion that granted +10 to strength and then drank some sujamma, the two strength boosting effects would stack because they come from different sources

### [2.13.9] The average value of the ingredients used modifies the XP gained

- The amount of XP earned from making a potion is multiplied by the value in the table below, based on average ingredient value
- The multiplier scales linearly between the values shown
- There is a hard cap of a 3x multiplier reached at 200g average value

| Average ingredient value (g) | XP multiplier              |
| :--------------------------: | :------------------------: | 
| 0-5                          | 0.5 to 1.0   (special)     |  
| 5-100                        | 1.0 to 2.0                 | 
| 100-200                      | 2.0 to 3.0                 |   
| 200+                         | 3.0                        | 


- A special rule exists for potions made with average ingredient values of less than 5
	- In addition to the reduced XP noted in the table above, once you reach skill 30 the final XP earned from these potions is halved
	- It's halved again at 60 to one quarter, and again at 90 to on eighth
- This is to discourage levelling alchemy by spamming cheap ingredients bought from shops. You can still can, but you might actually prefer to find rare ingredients now at high levels


### [2.13.10] Potion making success rate
- The success for making potions has been adjusted to:
	- `30 + (Alchemy factor * 2/3)`
- The results in higher success rates at low levels, and the player reaching 100% success around 80-90 skill
	- At 5 skill you have about a 40% success rate, previously it was as low as 10-15% depending on attributes
	- At 30 skill you have about a 50% success rate
- You can receive a bonus to your potion making success rate if you use expensive ingredients, see below

### [2.13.11] Ingredient value increases the success rate of making a potion
- The average value of the ingredients used in a potion can now improve your success rate
	- Below 10 gold average value, there is no change to your success rate
	- Above 10 gold average value your success chance is increased by
	- `8.4 + (avg value * 0.158)`
- In practise this works out to around:

| Average ingredient value (g) | Success rate bonus |
| :------------------------: | :---------------------: |
| 10                         | 10%                  |
| 25                         | 12%                  |
| 100                        | 24%                  |
| 200                        | 40%                  |

- This was added to further incentivize using expensive ingredients for levelling


## [2.14] Mechanics: Pickpocketing overhaul

- In the core game your chance of pickpocketing anything more than 100-200g was essentially zero, even at maximum skill, due to how heavily weighted item value was in the equations
- Several changes have been made to make pickpocketing more viable

### Pickpocketing overhaul, general changes

- The difficulty check for pickpocketing no longer takes into account the victim's attributes or skills (in the base game your chance of succeeding was lowered by the item's value, and by the NPC's sneak, luck, and agility scores)
	- This was removed to simplify the logic for development and balancing. It could be added back in later on, but it didn't feel like it added much to the game
- The base logic has been extensively changed so that you now have around a 50% chance to steal an item worth: 
	- `5 x  Pickpocketing term`
	- This is before the fatigue modifier is applied, so at full fatigue your odds are often even better
- The pickpocketing term is calculated as in the base game via,
	- `pickpocketing term = (sneak) + (agility * 0.2) + (luck * 0.1)`
- So your term is usually something like
	- `your sneak skill + (10 to 25 depending on attributes)`
- See the table below for what value items you can now reliably steal at some example skill/term values
	- I've made some assumptions about what a players stats are at each skill level, if you are levelling your luck/agility expect to hit these values, and expect to be able to steal a little less if you neglect them 


| Skill  | Assumed pickpocketing term  | Value (g) with 50% success rate (1x fatigue) | Value (g) with 100% success rate (1x fatigue) |
| :----: | :-------------------------: | :------------------------------------------: | :-------: |
| 10     | 17                          |   85                                         | 0
| 30     | 39                          |   195                                        | 35
| 50     | 62                          |   310                                        | 150
| 70     | 90                          |   450                                        | 290
| 90     | 118                         |   590                                        | 430
| 100    | 130                         |   650                                        | 490

- For every 5g an item is below or above your 50% success rate, add or subtract 1.5% chance to succeed
	- For example at skill 50 in the table above i have assumed based on your attributes you have a 50% chance to steal something worth 310 gold
	- If you tried to take something worth 210g, you are taking something 100g easier and so add 30% to your success rate
	- `Success rate modifier = (Item value above or below 50% odds / 5) * 1.5 `
- A rule of thumb is, for every 100g under your 50% success rate, you will have about a 30% higher chance to succeed
- This is all before factoring in fatigue, so at high fatigue you will find all of this easier
- Annoyingly in the base game, the pickpocketing UI doesn't show a % success rate, so to help you with all of this another change was made...

### You can only see items in an NPCs inventory if you have at least a 50% chance to steal them
- The engine reverse engineers all the above and the end result is that if you open an NPCs inventory whilst sneaking and you can see something, you have at least a 50% chance to steal it (providing your fatigue modifier isn't below 1)
- This is meant to represent NPCs guarding their more valuable items closely
- Items you have less than a base 50% chance to steal won't appear at all, and the only way to see them is to raise your sneak or your attributes
- In the base game this was handled completely differently,
	- Whenever you opened an NPCs inventory via sneaking, what appeared was determined completely independently of the items value
	- Instead for every item they had there was a % chance for it to appear based on your skill
	- This is why in the old system you sometimes had to close and open the NPCs inventory repeatedly to get something to appear


### Core game bug fixes
- The player no longer has to pass an additional detection check when closing the pickpocketing menu
- This was a core game bug (feature?) that meant whenever you succeeded at stealing something you had to pass the pickpocketing difficulty check twice in a row to actually succeed
- That is no longer the case
- This change, along with GMST adjustments (see the ESP companion) mean that your maximum success chance is now 100%, in the base game you could never have more than a 75% chance to succeed

### A note on GMST behaviour
- The GMST `fPickPocketMod` has been set to 1.0 (versus 0.3 in the base game)
- This is what determines the value of items you can steal, and 1.0 produces the values in the table above
- If you want to adjust the amount the player can steal, lowering the value increases the amount you can steal
	- Changing it to 0.5 would double all the values shown in the table above
	- Changing it to 2.0 would halve all the values shown in the table above


## [2.15] Mechanics: Athletics and swimming

- In the base game the players swimming speed started at 50% of their running speed, and every athletics level added 0.1% of their run speed to their swim speed
	- This wasn't a very big increase, you only went from 50% to 60% run speed going from 1 to 100 athletics
- Now the players swim speed is increased by 0.3% per level
	- So at 100 athletics the players swimming speed is 80% of their run speed
- There is a hard cap of being able to swim at 100% of your run speed, which you will reach at 166 athletics 
- Further raising your athletics will help, since athletics is what determines your run speed, as would adding swift swim effects
- This change just makes it so that raising your athletics will have a noticeable effect on swim speed (turning it into a pseudo swimming skill)

## [2.16] Mechanics: Willpower buff

- Willpower was buffed slightly, this was done purely for balancing reasons (it felt a little lackluster in core)
	- Your willpower now contributes 1.5x as much to your spellcasting success rate than previously
	- Otherwise the base game spell success equations are still used
- In addition, willpower was modified to add small amounts of resist magicka passively when above 50
	- This was added purely for fun, because of a longstanding rumour that it did this
	- But also it does make the stat a litle less one note
- Your willpower now grants 2% resist magicka per 10 points above 50
	- So at 100 willpower you have a passive 10% resist magicka effect
- There is no cap to this bonus
- The resist magicka granted this way is affected by the hard cap of 60% resist magicka in the current version
- This doesn't appear on the UI as an active spell effect, but it has been tested and is all working behind the scenes

## [2.17] Mechanics: NPC spellcasting locked to base game effect costs

This is a purely 'behind the scenes' change to the engines behaviour. If you are not a modder yourself or planning to change the spell effect costs in the ESP file then you can ignore this section

- NPCs are now hard coded to use the base game spell effect costs regardless of their current values in the ESP
- This means that spell effect costs can be changed without affecting NPC behaviour
- The player is unaffected by this, and always uses the current ESP spell cost values

This was done to allow the spell effect costs to be changed without affecting NPC behaviour, as in the base engine/game if you changed the effects costs via an ESP mod, it would also affect NPC spellcasting difficulty and spell lists
- For example, previously if you made an ESP mod that set the fire damage effect to cost 10x it's current value, all NPCs with fire spells would find them 10x harder to cast (so you would probably find lots of mage enemies resort to meleeing you and become much weaker than intended by the developers)
- This change was made purely to allow the spell effect costs to be set to any value without affecting NPC or creature behaviour
- In effect this makes changes to the spell cost values in ESP files 'player only'

However there is one consequence of this to be aware of:

- The Encore engine now forces NPCs to use the base values for spell effect costs at all times
- So if you install modded content that:
	- Changes the spell effect costs
	- Creates new NPCs with modded spells using those new spell effect costs
	- Balances the difficulty around the NPCs casting those spells with the new spell effect costs
- Then the engine will force them back to base game values and mess with the balance for that modded content
- But this is at worse a balancing issue, not one that will cause bugs or crashes, and one can that be fixed with a compatibility patch if needed
- It is very rare for modded content to touch these values, typically only total overhauls do, so don't worry about this if you are just playing a vanilla+ game with tamriel rebuilt and other location/content mods



## [2.18] Mechanics: Miscellaneous changes

- The hammer sound that plays when the player repairs equipment been reduced to 50% of it's original volume
	- It was way too loud
- Enchanted on-strike weapons no longer display the "no-charge" message when their charge is depleted, and no longer play the "no-charge" sound effect when attacking with insufficient charge
- The server and client have been recompiled (a big thanks to Skooma-Breath for their help with the server) so that they have different checksums. This prevents EncoreMP clients and servers from connecting to other versions of tes3mp (and vice versa)

## [2.19] Mechanics: OpenMW fix to sneaking behaviour 

EncoreMP now includes the fix added to OpenMW in V0.50: https://gitlab.com/OpenMW/openmw/-/issues/6029 which makes it so that out of combat you only have to pass sneak checks periodically.

Changed sneaking behaviour:
- Out of combat enemies will only roll to spot you every 5 seconds, and they will keep that roll result for that interval
- In combat they will still check every frame, so it is very hard to stay hidden once in a fight

Context:

OpenMW V0.50 introduced cached stealth checks, fixing a longstanding bug in OpenMW that caused it to diverge from core game behaviour.

In the Bethesda version of Morrowind you only had to pass a stealth check every few seconds, whereas up until OpenMW V0.50 you had to pass a stealth check potentially up to every frame. 

This meant that the sneak icon was not a reliable indicator of whether you were actually sneaking, and it was extremely hard to do anything illegal with NPCs around. As EncoreMP is based on OpenMW 0.47 it inherited this issue.


Now out of combat, once you are hidden you should have a reliable 5 second window to do things in - but be aware that any changes to your stats, the enemy's stats, or either of your positions, can potentially still cause you to be seen (this is intentional behaviour and mirrors the original version of the game)


## [2.20] Mechanics: Updated spell magicka costs in spell-buying menus    

A behind the scenes change has been made to how the spell buying menu works, this affects all spells for sale by NPCs.   
This is another section which is probably only of interest to modders.

### Summary for non-modders
- All base game and tamriel rebuilt spells for sale will have their magicka costs updated to reflect the spell effect cost changes made in EncoreMP providing you load one of the spell ESPs
- You do not have to include them if you don't want to, as all they do is update the costs of spells for sale at merchants, but they are recommended for balance reasons
	- There will be no bugs/issues if you skip them
- Any modded content not captured in one of these ESPs is fine to use, it will just not have it's spells auto-updated to match the new EncoreMP effect values

### The pre-made spell ESPS  
- There are three spell ESPs bundled in the release files that contain manually updated lists of spells
- You should only load **one** of these ESPs depending on the content you are using:
	- `EncoreMPV093Spells1Base` for Morrowind, Bloodmoon, and Tribunal
	- `EncoreMPV093Spells2TRcore` for Morrowind, Bloodmoon, Tribunal, Tamriel data, and Tamriel mainland
	- `EncoreMPV093Spells3TRall` for Morrowind, Bloodmoon, Tribunal, Tamriel data, Tamriel mainland, Project Cyrodil, and Skyrim Home of The Nords
- As mentioned above, it does not matter too much if you don't load any of them, the only consequence is that pre-made spells for sale will still have their original magicka costs (a balance issue at most)
- These are all up to date with the most recent main releases for these projects as of July 2026 (as of writing this poison song update has not yet been released)
	- You can use them with older or newer releases of this content, the only consequence will be that some spells aren't captured and balanced

### For modders: How the engine change works and why it exists

- EncoreMP updates many spell effect costs, however these changes only affect custom spells, enchantments, and potions made by the player
- All pre-made spells for sale by NPCs are unaffected by this and would normally retain their original magicka costs
- This could be addressed by updating the magicka costs of all pre-made spells in the game manually via an ESP file   
- However since pre-made spells are used by every NPC in the game, doing this would change NPC behaviour in several ways:
	- Auto-generated spell lists (a feature used a lot by the original developers for NPCs) would update themselves to reflect the new costs, potentially changing what spells NPCs spawn with
	- Spell cost changes would change the difficulty of casting those spells for NPCs (they do have to pass a spellcasting check, it's not an auto succeed for them!)
	- So in extreme cases hand made NPCs may find themselves unable to cast their own spells if you have changed the costs dramatically

So to stop these things from happening, a workaround solution was developed that avoids all of the issues listed above
- The spell merchant UI code was extensively updated to include some new behind the scenes behaviour
- Now when the player opens the spell buying UI, the engine will first check for "variant spell IDs", and display those if possible, falling back to the normal spell IDs if no variants are available
- Exactly how this works...
	- For every spell for sale by an NPC, the engine now looks for a 'variant' of that spell ID in the ESP files
	- If it can find a 'variant spell ID' it shows that to the player instead in the UI, and if not it falls back to showing them the original spell for sale
	- A 'variant' has been defined to the engine as the original spell ID, concatenated with the prefix '@'
    - '@' was chosen as it is never used in the base game or Tamriel Rebuilt spell lists, and is very unlikely to be used in other modded content
	- For example, if you open the menu to buy the spell fireball, the engine will take that spells ID, `fireball`, and concatenate it with the prefix @ to produce the variant spell ID `@fireball`
	- Now the engine looks in all the ESP files to see if there is an `@fireball` spell ID, and if there is it shows that to the player **instead** of the original fireball spell
	- It not it falls back to showing them the normal `fireball` spell
- Now it is possible to manually make a spell in an ESP file called `@fireball` with an updated cost to reflect whatever spell effect cost values you are using, and whenever the player would have been offered `fireball` they will instead see your modded cost spell `@fireball`, and the NPCs copy of the spell is completely unaffected!
- The player will not see a change in spell name on the spell list, this is an ID change only (providing you keep the spell name the same in your duplicate record)
- The spell buying UI accounts for this when checking what spells the player already knows, if they a spell that would be offered for sale, or they know it's @ ID variant, then the list hides the spell (as if they owned the base spell)


### For modders: Making your own spell list ESPs for modded content
- Since this is an engine change it doesn't rely on a hard-coded list of spells, if you add new modded content to your game and want to update the pre-made spells for sale, you can do so by making your own ESP and adding new spell ID variants that start with @ as described above
- I'm sorry, but right now this has to be done by hand (it took a very long time to make the TR spell companions included in the release)
- See the compiling notes companion bundled in the release if you want to understand more about the engine changes made
- There is one limitation to this, since the @ symbol takes up a character, and spell IDs are limited to being 31 characters in length, you can't do this for spells that are already 31 characters long
	- A niche problem though, and an unfortunate limitation of this solution

### For modders: Planned long term solution

- I am not yet sure if this is feasible, but in the long term the hope is to bundle in some ESP extraction tools and a simple program that can extract all the spells in your ESP files, and then make a new list of spells with the variant IDs and updated costs
- Consider this a stretch goal though, for now I will be updating all the spells ESPs for each new TR release by hand

# [3] New gameplay settings

- There are several new gameplay settings which can be configured via the server `config.lua` file    
- These are server wide, to prevent desync in behaviour, and so configured by the server owner prior to launch   
- I have noticed a core issue with tes3mp, where the server settings do not override your local openMW settings straight away when you connect, if you find this is happening, just sit in game for a minute and then close and re-open the client, this forces the player to sync all their settings with the servers

### New server settings 

`"two handed weapons receive an accuracy penalty"` - Boolean
- True: two-handed weapons take the -15% to hit penalty
- False: two-handed weapons receive no penalty to their hit chance 

`staves receive accuracy bonus instead of two handed penalty` - Boolean    
- True: Staves receive the +20% to hit chance bonus
- False: Staves use whatever modifier applies to other 2h weapons (if 2h accuracy penalty is on, staves take the -15% hit chance penalty, if that setting is also false then staves take neither the +20% bonus nor the -15% penalty) 

`skill books have level limit` - Boolean  
- True: Skill books do not advance a players skill past 90
- False: Base game behaviour, skill books work at any level

`global XP gain multiplier` - Float
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

`use new constant effect difficulty logic`  - Boolean 
- True: Use the new Encore logic for constant effect enchantment difficulty, using player base skill
- False: Use the base game difficulty logic for constant effect enchantments

# [4] TES3MP project information

This section has been copied verbatim from the tes3mp project information as requested by the original authors of that work - see this section for details about tes3mp, OpenMW, the authors, and how you can support those projects.

---

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



# [5] Known issues & comments

### Resist magicka
- If the player has more than 60% resist magicka, the combat AI of enemies will still behave as if the player had MR values above 60% when making decisions about what to do in combat
	- This was intentionally as is to avoid changing the combat AI, as doing so would have knock on effects on NPC behaviour in fights. It may be possible to update the AI to accommodate this in the future, but this a very minor issue in practise
- The UI still shows resist magicka values above 60%, but this is a UI issue only - the engine is working properly in regards to the mechanics

### Melee combat
- An accuracy boost was given to all 'staff' type weapons as part of the melee overhaul. However this achieved by increasing the accuracy of all weapons belonging to the class `BluntTwoWide`  
- In the base game this category is only used for staff weapons which do very low damage. All other two handed blunt weapons are grouped in a separate category
- However if modded content adds high damage 2h blunt weapons and classes them as `BluntTwoWide` they will receive the accuracy boost intended for staffs and be more powerful than intended (as of writing this however, this is not an issue for any tamriel rebuilt content)
	- In this case the staff accuracy boost can be disabling it via the new server settings

### NPC spellcasting
- Several behind the scenes changes were made to the engine to clean up some core game (or at least inherent to OpenMW) issues which affected NPC spellcasting when spell effect costs were changed from their base game values  
- A consequence of these engine changes is that the EncoreMP engine now expects NPCs to be casting spells that were made using the base game spell effect costs  
-  You will not be affected by this issue unless you are using modded content that: 
	-  [1] Changes base game spell effect costs notably, 
	-  [2] Gives spells to NPCs made with the new spell effect cost values, and
	-  [3] expects the NPCs to cast those spells with the auto-calculated values
- This scenario would have been an issue anyway in core openMW, due to the behind the scenes issues that needed fixing

### Server/client visual checksum
- The server/client checksum has been correctly updated for each EncoreMP release (so that EncoreMP cannot connect to baseline tes3mp servers or earlier Encore versions), however EncoreMP servers still display their checksum as being "V0.8.1" in the server browsing UI
- This was due to an issue with compiling - it is a UI problem only that will be addressed in the future, but right now I have no idea why the compiler refuses to let me change the UI string but it's okay with me changing the actual checksum

### Console commands to adds/remove modded spells
- The effect of the engine change made to spellbuying means that when a player buys a variant spell they actually have the @ variant added to their spellbook instead of the original spell ID
- e.g. if the player buys `Poisonbloom` they would actually have the ID `@poisonbloom` behind the scenes
- So if using console commands to add or remove spells you may need to use the @ variant if the original ID isn't what's in your spellbook
- Due to how the morrowind console works, you **have to** put quotation marks around spells with an @ prefix in them
    - `player->addspell @poisonbloom` will not work
    - `player->addspell "@poisonbloom"` will

### Content that checks the content of the player's spellbook

- Quests or scripts that check for the player owning specific spells will not work if the player owns the variant instead
    - Luckily in the base game this is not an issue, as it only happens in one quest ("Wizard Spells") and the spells involved do not have @ variants as their spell effect costs have not been changed
    - I am also not aware of any Tamriel Rebuilt content that checks for spell IDs, but I have not checked everything
- In any case, if this happens the solution is just to add the correct spell ID via the in-game console
	- e.g. `player->addspell poisonbloom`
    - The spell ESPs do not affect the original spell records, so you can do this to get the original version of any spell if you need to


# [6] Partner files

**ESP companion**
- This overhaul requires the ESP file `EncoreMPV093` to function as intended. This ESP adds no new content, it only changes magic effect costs, experience gain values, and some GMSTs
- See the partner file "EncoreMP V0.93 ESP companion" for a full list of changes made by the ESP

**ESP optional new content companion**
- There is an optional ESP file which overhauls some content in the original game. This is not required, and EncoreMP is not balanced around it. As of V0.93 it includes racial ability changes, birth sign changes, and a change to the (tribunal) assassin spawn script that stops them appearing before level 10
- See the partner file "EncoreMP V0.93 new content ESP companion" for a full list of changes

**Compiling companion**
- If you are curious about how the changes were made, or the finer details of the mechanics, have a look at the partner file "EncoreMP V0.93 compiling notes"
- This file contains a complete list of all of the changes made to the base tes3mp code, and some comments on why many of the changes were made

