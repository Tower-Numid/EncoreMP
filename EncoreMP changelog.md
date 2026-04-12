Current Version: 0.9.2

**Summary**

V0.9.2 - Alchemy balance review, major enchanting review (checksum 805)    
V0.9.1 - Adding new spell buying menu system, full spell effect cost review with many changes, minor XP gain adjustments, first wave of new server settings added for EncoreMP features (checksum to 804)    
V0.9.0 - Cached stealth checks, set all ally damage sources to obey difficulty scaling system (cheksum 803)    
V0.8.1 - Balancing (economy, enchanting, armorer, other misc changes) and optional content ESP release (checksum 802)    
V0.8.0 - First public beta release (checksum 801)    

**Changelog**

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

V0.9.0 - Added stealth check caching as per OpenMW 0.50. Set all sources of player ally damage to obey difficulty scaling, but no increase to player ally damage taken

V0.8.1 - Minimum XP required to level lowered to 20, Training costs reduced by 30%, Lockpicking made about 10% easier, Mercantile gold required to level reduced by 33%, Axes use strength now like maces, Enchanting compounding costs removed, Enchantment service costs reduced, Armorer service costs reduced, Armorer minimum success rate raised to 15% for all, Armorer tools made more impactful

V0.8.0 - Release
