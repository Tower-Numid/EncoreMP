Current Version: 0.9.3

**Summary**

V0.9.3 - Feature balance and code review, around one third of the new features reviewed in this pass (checksum 806)   
V0.9.2 - Alchemy balance review, major enchanting review (checksum 805)    
V0.9.1 - Adding new spell buying menu system, full spell effect cost review with many changes, minor XP gain adjustments, first wave of new server settings added for EncoreMP features (checksum to 804)    
V0.9.0 - Cached stealth checks, set all ally damage sources to obey difficulty scaling system (cheksum 803)    
V0.8.1 - Balancing (economy, enchanting, armorer, other misc changes) and optional content ESP release (checksum 802)    
V0.8.0 - First public beta release (checksum 801)    

**Changelog**

V0.9.3  
- Spell XP gain multiplier based on magicka cost was rebalanced. The new XP multiplier cap is 4x XP at 50 magicka, past this additional spell cost provides no further benefits to XP gain
	- All spell base XP gain reverted back to base game (1xp per cast) from 2xp per cast in previous versions
- Melee combat reviewed and simplified
	- Accuracy bonus from spears removed, but they are still exempt from the two handed accuracy penalty 
	- Removed bonus damage scaling from strength or agility for long blades, axes, and maces simplified. Now all melee weapons scale their damage the same way, half from skill and half from strength, reaching +50% damage at 100 strength and 100 skill
	- Long blades no longer use agility for damage scaling, and the server setting that allows them to toggle between strength and agility has been temporarily disabled
- Swim speed derived from athletics has been hard capped at 100% of your land running speed at 166 athletics, otherwise the increased swim speed scaling remains unchanged from previous versions
- Climbing now operates off of your modified acrobatics skill, not your base acrobatics skill. So temporary buffs will allow you to climb up steeper angles
	- If your skill drops below the required level for the slope you are on mid climb you do not stay in place, you will begin to fall again
	- Likewise if your skill increases mid fall you will immediately stop in place on the slope, for the duration of the buff
- The GMST for player skill training costs has been set back to 10 (the default value), and the code has been adjusted to account for this and preserve the cost curve from previous versions
	- Plus a minor bug fix to the math which was present in previous versions and inflated high end training costs more than intended
- Refactored all of the resist magicka code, but no changes to gameplay or balance. The cap remains 60%, and the UI will still display magnitudes above 60
	- The UI behaviour is being treated as a feature not a bug, as resist magicka is negated 1:1 by weakness to magicka, so tracking magnitudes above 60 is meaningful information for the player
	- Fixed a bug where the AI was using the players willpower to add to it's magic resistance for constant effect items
- Encore's hand to hand strength scaling tested and working for werewolves, and a bug fixed where the AI was using the new hand to hand skill derived damage scaling (now it is player specific)
	- The new strength scaling logic is used by NPCs as well as the player, as was the case for the previous version of OpenMWs hand to hand strength scaling
- Ranged accuracy bonus lowered from +20 to +10 for all ranged weapons
	- Damage scaling remains as in previous versions, agility and skill for bows and crossbows, strength and skill for throwing
- Balanced some racials in the optional content ESP, nerfed "voice of the emperor", "sword singing", and "beast tongue"

V0.9.2  
- Alchemy balance overhauled, changes to overall potion strength and effect of ingredient values. Also added variable XP gain based on ingredient value used in the potion
- Major enchanting review
    - Variable XP gain added based on soul size used (larger souls give up to 4x XP)
	- Bonus to enchanting success rate based on soul size used (larger souls give up to +30 levels)
	- Review of on-use enchanting logic, closer to base game again with an overall slight increase in power
	- Scrolls now hold more enchantments and are easier to make at low costs
	- On-strike enchantments reviewed, they track the on-use enchantment logic but keep the double capacity usage for effects
	- Ammunition enchanting reviewed, arrows will always enchant in bundles of 20 (if enough items are provided), and the openMW setting "projectiles enchant multiplier" has been disabled (multiple enchanting ammunition is always on and set to 20)
		- Arrows receive the same bonus to success rate that scrolls do when their cost is below 10
		- Otherwise they follow on strike logic and capacity usage
	- Constant effect enchantments require a base skill of 60 or above, and the size of CE you can make it determined by your skill level. At 100 skill you can make any size CE enchantment
	- Previous changes to enchantment use costs tidied up and simplified
	- Previous changes to all enchanting services tidied up and simplified
    - Bugfix: Stacks of enchanted items (ammunition) now each reieve the full charge of the soul gem, and no longer display as having "0" charge when small soul gems are used

V0.9.1 
- The new spellbuying menu subsitution system was added, along wtih three new ESPs which contain pre-made lists of replacement spells for tamriel rebuilt and the core game
- All spell effect cost changes were reviewed, and after balance testing many were reverted back towards base game values
- XP gain for armorer was increased
- Cost of spellmaking/spellbuying was decreased
- Multiple new server settings were added which are customisable in the server config, and allow toggling of several EncoreMP features

V0.9.0 
- Added stealth check caching as per OpenMW 0.50. Set all sources of player ally damage to obey difficulty scaling, but no increase to player ally damage taken

V0.8.1 
- Minimum XP required to level lowered to 20, Training costs reduced by 30%, Lockpicking made about 10% easier, Mercantile gold required to level reduced by 33%, Axes use strength now like maces, Enchanting compounding costs removed, Enchantment service costs reduced, Armorer service costs reduced, Armorer minimum success rate raised to 15% for all, Armorer tools made more impactful

V0.8.0 
- First public release
