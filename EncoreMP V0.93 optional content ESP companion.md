This file details all the changes made in the optional new content ESP file for the V0.93 EncoreMP beta release, `EncoreMPV093newcontent.ESP`

**Sections**
1. Racial ability changes
2. Star sign changes
3. Script changes
4. Item table changes

# 1, Racial abilities

**Argonian**
- Immunity to poison (base game)
- Resist common disease 75% (base game)
- Sanctuary 10 points
- Spell, 0 magicka, always succeeds, water breathing 300 seconds, swift swim 30 points for 300 seconds, night-eye 30 points for 300 seconds

**Breton**
- 35% magicka resistance
- 0.5x magicka multiplier
- Dragon skin daily power, 30 points spell absorption for 60 seconds

**Dark Elf**
- 0.3x magicka multiplier
- 75% fire resistance
- Ancestor guardian daily power has been updated to: 5 points attack, 50 points sanctuary, 25 points chameleon, for 60 seconds

**High Elf**
- 25% weakness to fire
- 25% weakness to magicka
- 25% weakness to frost
- 25% weakness to shock
- 1.2x magicka multiplier
- 75% common disease resistance

**Imperial**
- Voice of the emperor, power, calm humanoid 100 points for 60 seconds on target and charm 50-100 points for 120 seconds on target
- Star of the west, power, absorb fatigue 15 points for 10 seconds on target

**Khajit**
- Fortify luck 10 points
- Eye of Night, spell, 0 magicka, always succeeds, Night eye 50 points on self for 300 seconds, Detect enchantment 20 points on self for 300 seconds
- Powerful leaps, spell, Jump 4 points for 60 seconds on self, 10 magicka, always succeeds

**Nord**
- Resist shock 50%
- Resist frost 75%
- Restore fatigue 1 point per second, permanent passive effect
- The voice, power, Sound 50-75 points for 30 seconds in 5ft on target

**Orc**
- Resist magicka 50%
- Resist paralysis 100%
- Berserk, power, For 60s on self: restore health 3 points, fortify strength 50pts, fortify speed 50pts, fortify attack 75pts, drain agility 100 pts
	- Note that because orcs have 50% magic resistance as a racial, this will only lower your agility by 50 points when used

**Redguard**
- Resist disease 75%
- Resist poison 75%
- Sword singing, power, Reflect 30 points on self for 60 seconds, Restore Magicka 1-2 points for 60 seconds on self
- Adrenaline rush, power, Fortify agility 50 points on self for 60 seconds, Fortify strength 50 points on self for 60 seconds, Fortify speed 50 points on self for 60 seconds, Fortify endurance 50 points on self for 60 seconds, Fortify health 25 points on self for 60 seconds

**Wood elf**
- Resist disease 75%
- Beast tongue, power, Command creature 10 points for 300 seconds on target in a 5ft AOE
- Beast kin, spell, 10 magicka, always succeeds, calm creature 10 points for 60 seconds

# 2, Star sign changes

**The Warrior**
- Attack 10 points
- Strength 10 points

**The Mage**
- Fortify magicka x0.5
- Willpower 10 points

**The Thief**
- Sanctuary 10 points
- Agility 10 points

**The Serpent**
- Luck 20 points
- Weakness to poison 100 points

**The Lady**
- 25 points personality
- 25 points resist magicka

**The Steed**
- 25 points speed
- Spell, 5 mana, always succeeds, feather 100 points for 300s on self

**The Lord**
- Spell, Restore health 1-5 points for 30 seconds (10 mana, always succeeds)
- Resist frost 25 points
- Resist common disease 25 points
- Resist blight disease 25 points
- Fortify Light, Medium, and Heavy armour 10 points
- Fortify Unarmoured 10 points

**The Lover**
- 25 points Agility
- Lover's kiss, Power, paralyse 30 seconds on touch, drain agility 30 points for 60 seconds, on touch

**The Tower**
- Spell, detect key/enchantment/animal 200 points for 60 seconds (5 mana, always succeeds)
- Power, Open 50-100 points
- Power, Open 50 points
- Power, Open 40 points

**The Shadow**
- Power, fortify sneak 50 points for 120 seconds

**The Ritual**
- Intelligence 10 points
- Power, Fortify alchemy, armorer, and enchanting 10-30 points for 120 seconds
- Spell, 10 mana, always succeeds, restore all attributes 10 points

**The Apprentice**
- Fortify maximum magicka x1.5
- Weakness to magicka 50 points

**The Atronach**
- Spell absorb 50 points
- Fortify maximum magicka x2.0
- Stunted magicka

# 3, Script changes

**Assassin spawn level changed (tribunal)**
The dark brotherhood assassins that spawn to start the tribunal main quest can no longer spawn until you reach level 10. The script changed was `dbattackScript`