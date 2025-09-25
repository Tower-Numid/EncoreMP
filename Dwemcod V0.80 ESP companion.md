This file details all the changes made in the required ESP file for the V0.80 dwemer coda beta release, `dwemcodV080.ESP`.

# GMSTs

**Shops and mercantile**
* `fBarterGoldResetDelay` set to 12 (from 24 in the base game)
	* This value is how many hours it takes for in-world shops to reset their gold. It was accelerated because time does not advance when resting in multiplayer. Though server commands can be used in the chat window to skip ahead if needed.
- `fDispositionMod` changed to 0.25 (from 1 in the base game)
	- This value is a multiplier for how much your disposition with an NPC affects your haggling (but not bartering) success rates. It was dropped to 1/4 of the base game value to pair up with the changes made in the engine to how much disposition affects shop prices (disposition now also now has 1/4 of the original effect on those as well).

**Bribery (Speechcraft)**
- `fBribe10Mod` set to 1 (from 35 in the base game)
	- This value is the number of effective skill levels that are added to your bribe attempt when bribing 10 gold (note that bribing any amount switches the player to using their mercantile skill, instead of their speechcraft skill, for the attempt. So in effect you are paying 10 gold to use your mercantile skill instead of your Speechcraft skill with this option.)
- `fBribe100Mod` changed to 15 (from 75 in the base game)
	- This value is the number of effective skill levels that are added to your bribe attempt when bribing 100 gold

**Security**
- `fPickLockMult` set to -1.3 (from -1.0 in the base game)
	- The level of a lock you are trying to pick is multiplied by this value, and then subtracted from your base success chance to get your actual success chance. This change makes lock level matter about 30% more than in the base game.

**Player Magicka**
- `fPCbaseMagickaMult` set to 1.2 (from 1.0 in the base game)
	- This value times your intelligence is your magicka pool. In the base game (without any fortify maximum magicka effects) you have 1 magicka for each point of intelligence. 
	- This change means that all player characters effectively start with fortify maximum magicka 0.2 points. This stacks additively with all other sources of fortify maximum magicka, and affects player characters only.

**Elemental shields**
- `fElementalShieldMult` set to 1.0 (from 0.1 in the base game)
	- This value is how many points of elemental damage each magnitude of an elemental shield effect does to the attacker (before factoring in resistances). 
	- Note that elemental shield effects are resisted unusually in the base game, something that has not been changed yet, so expect to still see them doing about 0.5 damage per point of magnitude against a lot of enemies.

**Spell prices**
- `fSpellValueMult` set to 20 (versus 10 in the base game)
	- This value is used as a multiplier when calculating the gold cost of buying a spell (based on its magicka cost). So increasing it to 20 roughly doubles the cost of buying a spell versus the base game.
- `fSpellMakingValueMult` set to 20 (versus 7 in the base game)
	- This value is used as a multiplier when calculating the gold cost of making a spell (based on its magicka cost). So increasing it to 20 roughly triples the cost of spellmaking versus the base game (and brings the cost in line with the change to spell buying).

**Hand to Hand**
- `fHandtoHandHealthPer` set to 0.4 (versus 0.1 in the base game)
	- This value multiplied by the fatigue damage that your hand to hand attacks deal is the amount of health damage that enemies take when you are damaging health with hand to hand (e.g. when they have been knocked down, or are paralysed).

**Alchemy**
- `fPotionStrengthMult` set to 1.0 (versus 0.5 in the base game)
	- This is a multiplier used when calculating the overall strength of potions made through alchemy. Due to extensive changes to the alchemy code this is now expected to be set to 1.0, which translates to a 1x multiplier. 
	- You can adjust it to taste, but all of the alchemy balancing in dwemcod was done assuming this is set to 1.0.
- `fPotionT1MagMult` and `fPotionT1DurMult` both set to 1.0
	- These two have had their functionality changed from the base game. They now both act as % multipliers to potion magnitude and potion duration respectively, with 1.0 being 100% of the base value, in the same way that `fPotionStrengthMult` behaves.

**Pickpocketing**
- `iPickMaxChance` set to 100 (versus 75 in the base game)
	- This determines the maximum success chance you can have when making any pickpocketing attempt, so at 100 you can have up to a 100% chance to succeed at pickpocketing if you have enough skill
- `iPickMinChance` was left at the default value of 5, but the functionality of the GMST was changed a little. This GMST is now the flat minimum success rate you have when attempting to pickpocket something. 
	- Beforehand it had a very similar effect, but it was a little more complicated as the engine also took into account your skill when calculating minimum success chance
- `fPickPocketMod` set to 1.0 (versus 0.3 in the base game)
	- This value is what is multiplied by the gold value of what you are attempting to steal, to determine the difficulty of the attempt
	- Note that due to changes to the pickpocketing logic in the engine, the new value of 1.0 is the expected default value which the skill has been balanced around

# XP values

If a skill or XP value is not mentioned then it has been left at the base game value


**Alchemy**
- Creation a potion: 2xp to 3xp
- Eating an ingredient: 0.5xp to 0.75xp

**Armorer**
- Successful repair: 0.4xp to 0.8xp

**Athletics**
- Running: 0.02xp to 0.04xp
- Swimming: 0.03xp to 0.07xp

**Enchant**
- Enchanting an item: 5xp to 15xp
- Recharging an item: 5xp to 7xp
- Using a magic item: 0.1xp to 0.5xp

**Security**
- Defeating a trap: 3xp to 4xp
- Picking a lock: 2xp to 4xp

**Speechcraft**
- Successful persuasion: 1xp to 2xp
- Failed persuasion: 0xp to 0.25xp

**All schools of magic**
- Successfully casting a spell: 1xp to 2xp
- Note that in addition to this XP change, all spellcasting schools now also reward more XP when you cast more expensive spells

**Long blade, Blunt weapons, Axe, and Spear**
- Successful attack: 1xp to 0.5xp (axe was originally 1.2xp actually in the base game)

**Short blade**
- Successful attack: 0.75xp to 0.4xp

**Hand to Hand**
- Successful attack: 1xp to 0.25xp

**Marksman**
- Successful attack: 1xp to 2xp

# Spell effect costs


==**Alteration**==  
Burden 1 -> 0.2  
Feather 1 -> 0.1  
Lock: unchanged (2)  
Shield 2 -> 0.6  
Swift swim 2 -> 0.2  
All three elemental shields 3 -> 1  
Jump: unchanged (3)  
Levitate 3 -> 6
Slowfall 3 -> 2  
Water breathing 3 -> 2  
Water walking 3 -> 2  
Open 6 -> 15

==**Conjuration**==  
Turn undead: unchanged (0.2)  
Bound weapons: unchanged (2)   
Bound armour: unchanged (2)   
Command creature 15 -> 7    
Command humanoid 15 -> 8  
Summons: unchanged  

==**Destruction**==  
Sun damage: unchanged (1)  
Fire/Frost damage: unchanged (5)    
Shock damage 7 -> 6   
Poison damage 9 -> 4   
Drain health 4 -> 3   
Damage health 8 -> 7   
Weakness to fire/frost/shock/poison 2 -> 0.7   
Weakness to magicka 2 -> 1   
Drain fatigue 4 -> 1   
Damage fatigue 4 -> 2   
Drain Magicka 4 -> 1   
Damage Magicka 8 -> 4   
Damage attribute 8 -> 15   
Drain attribute: unchanged (1)   
Drain skill: unchanged (1)   
Disintegrate weapon 6 -> 1   
Disintegrate armour 6 -> 2   

==**Illusion**==  
Night eye 0.2 -> 0.3    
Light: unchanged (0.2)  
Sanctuary: unchanged (1)  
Chameleon 1 (unchanged)  
Rally target: unchanged (0.2)  
Frenzy target 1 -> 3  
Demoralize target 1 -> 0.5 (Also demoralize humanoid was set to the illusion school, not mysticism as in the base game)  
Calm target 1 -> 0.5  
Blind 1 -> 0.6  
Sound 3 -> 0.70  
Charm 5 -> 1.5  
Invisibility 20 -> 10  
Silence 40 -> 30  
Paralyse 40 -> 60  


==**Mysticism**==  
Detect animal 0.75 -> 0.1  
Detect enchantment 1 -> 0.6  
Detect key 1 -> 0.2  
Telekinesis 1 -> 6  
Absorb health: unchanged (8)  
Absorb fatigue 4 -> 3    
Absorb attribute 2 -> 1.5  
Soul trap 2 -> 1.5    
Dispel 5 -> 2.5    
Reflect 10 -> 2  
Spell Absorb 10 -> 2  
Mark (unchanged)    
Recall (unchanged)    
Almisivi intervention (unchanged)    
Divine intervention (unchanged)  


==**Restoration**==  
Resist paralysis 0.2 -> 0.05    
Resist common disease 2 -> 0.1    
Resist fire/frost/shock/poison 2 -> 0.4    
Resist magicka 2 -> 0.5    
Resist blight disease 5 -> 0.2    
Resist corprus disease 5 (unchanged)  
Fortify attribute 1 -> 0.5    
Fortify skill 1 -> 1.5  
Restore attribute 1 -> 5   
Restore fatigue 1 -> 1.5    
Restore health 5 -> 6.5  
Cure Poison: unchanged (100)  
Cure Paralysis: unchanged (100)  
Cure common disease 300 -> 450  
Cure blight disease 2000 -> 700  
