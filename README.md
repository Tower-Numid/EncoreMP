
```
They retreated behind math, behind colour, behind the active principle itself.

Baladas Demnevanni, 3E 427
```

The eight release version of Dwemer coda, requires `dwemercodaV1J` to function as intended (this version requires these ESP level changes for balance reasons - see the ESP companion file).

Unless stated, all mechanical changes affect the player only.

# 1, Balance + Unintended Behaviour
**Balance**
- [ ] Enchanting arrows using services is too expensive, they mirror the costs of on-strike effects are not worth paying for in V0.10. The price needs lowering if that is possible.
- [ ] Monster soul values have not been addressed. Although they may be suitable as is, but low value souls may be better off getting a slight increase in charge

**Unintended behaviour**
- [ ] If the player has more than 60% MR, enemies will still behave as if the player had that increased MR. For example in the core game at 100% MR the enemy AI detects this and will not attempt to cast any effects that can be resisted by magic. In this new system whilst the player can still be affected since there is no benefit beyond 60%, the AI will behave still as if they have immunity and choose not to cast those spells directly at the player
	- This was left in as 'unintended behaviour' as the alternative would be to change enemy AI, which whilst simple may cause problematic behaviour when AI fights other AI, including summons. So it was thought best to leave the original behaviour in
- [ ] The accuracy boost given to all staffs as part of the melee overhaul was actually done to all weapons of the class `BluntTwoWide` which in the base game is exclusively used for all staffs, whereas mauls are exclusively classed as `BluntTwoClose`. If modded content adds powerful 2h blunt weapons into the `BluntTwoWide` category they will receive the staff accuracy boost.

**Experimental features**
- [ ] The acrobatics climbing overhaul is currently considered an experimental feature due to the risk of physics issues such as collision detection or clipping, although non yet have been found during playtesting
# 2, Mechanics Changelog

- [ ] Enchanting completely overhauled as per 2.1 mechanics changelog, and 3.1 compiling changelog
- [ ] Spell effect costs adjusted per skill as per the ESP changelog
- [ ] XP gain per skill adjusted as per the ESP changelog
- [ ] XP gain reduced at high levels, and more is needed at levels below 30
- [ ] Training costs increase at high levels, and a floor value added
- [ ] Magic resistance now provides no benefit to the player beyond 60% (after accounting for weakness effects which negate it 1:1). No changes to how it works for NPCs or creatures.
- [ ] Skill books do not work at skill 95 and above anymore
- [ ] The sound played when repairing equipment with armorer's tools has been reduced to 50% the original volume
- [ ] When an enchanted weapon has run out of charge, there is no longer a sound effect of a spell failing or a text box pop-up telling you the weapon is out of charge
- [ ] Melee changes (extensive) to accuracy and damage, with the intention of overall making skill more important to a weapon user, and making weapons in general more usable at low skills whilst avoiding the auto-hit past about skill 50 which is currently the case
	- [ ] Accuracy starts higher and ends lower
	- [ ] Damage scales with skill
	- [ ] Each weapon type has a unique benefit (minor) to distinguish them
- [ ] Ranged changes,
	- [ ] +accuracy
	- [ ] launchers scale damage with agility and skill
	- [ ] throwing scales damage with strength, and reaches 200% damage rather than 150%
	- [ ] ammo recovery rates scale with level, as a % of GMST (unenchanted reaches 4x GMST or 100% at 100 skill, enchanted reaches 2x GMST at 100 skill or 50% by default)
- [ ] Acrobatics now actually allows climbing as you increase in skill, but not vertical walls in this version due to how they are handled in the Openmw physics engine. Benefits start at skill 30, but are gradual at first and probably start becoming noticeable at skill 45 and beyond. At skill 92 you should be able to climb anything that is not vertical.
	- [ ] This uses base skill, not modified, although it could in theory use the modified (design choice to use base)
	- [ ] This is not true Daggerfall style wall climbing, but will work on everything short of a vertical surface
- [ ] Difficulty scaling has been completely rebalanced and now operates off a tiered system, which more heavily reduces damage done and results in less extreme damage taken changes (compared to the default difficulty scaling)
	- [ ] Player magic damage dealt now scales to, specifically all of the direct damaging effects
		- [ ] Every type of player magic effects can be tracked separately, and some are, e.g. enchantments on-use, vs spells, vs on-strike enchantments
	- [ ] Player magic damage taken scales, but not from self inflicted effects, traps or scripts
	- [ ] Reflected damage has been accounted for as well
		- [ ] Player damage taken via a reflect is intentionally not increased for QoL and balance reasons
		- [ ] Monster damage taken via a reflect scales down by difficulty, using the same % changes that player magic damage done does (to stop reflect being a workaround for high difficulties)
	- [ ] Summons, scripted allies and commanded allies do not scale at all as of V0.80
- [ ] Armour ratings from equipment have been increased below skill level 30, but there are no changes from skill level 30 and beyond
- [ ] Unarmoured has been overhauled to scale much quicker, so that it can compete with medium armours most of the way through the game. It also now scales the armour rating you get from unarmoured with your agility and speed, if either are above 50, so that the skill becomes more useful to an agile and fast character (making it stand out from the other armour skills, but this benefit is not required to take advantage of the skill)
- [ ] Creatures now all have a base armour rating between 10 and 15 based on their level, these are provisional values for testing
- [ ] The armorer skill has been changed significantly, and has four major differences from the base game
	- The rate at which equipment degrades is now dependent on your armorer skill, with it degrading slower than in the base game as your skill increases
	- Your success chance when repairing an item now depends on the value of the item being repaired, with more expensive items being harder to repair
	- Armorer's tools (hammers, prongs) now increase or decrease your repair success rate dependent on their quality, anything with a quality below 1 decreases, and above 1 increases
	- Armour repair costs have been notably increased for high value items, and they are now based on a % of the item's full value - for low value items they are now slightly cheaper
- [ ] Athletics now significantly boosts your swim speed, in the base game going from 1-100 athletics took your swim speed from 50-60% of running. Coda V0.40 changes it from 50-80% running speed from skill 1-100
- [ ] Bribery has been nerfed heavily for 10g and 100g bribes, whilst 1000g bribes remain as in the base game. Now attempting to bribe with only 10g gives almost no boost to success chance, it only exists to let you switch to using mercantile skill instead of Speechcraft to calculate your success odds (as is the case in the base game)
- [ ] Mercantile has had several significant changes. These can be summarised as, (1) making it harder overall to get rich, and (2) switching mercantile XP gain from haggling to item sell value
	- [ ] XP is now earned through selling items, based on their gold value and the initial barter offer the merchant makes (but not XP for buying as of V0.50)
	- [ ] Disposition above and below 50 now only has 1/4 the effect it used to on prices
	- [ ] Haggling has been temporarily hard capped at a +- 10% price change, to avoid infinite money loopholes
	- [ ] Bartering rates (not haggling) are hard capped at 60% item value when selling and 90% item value when buying. Service charges are unaffected.
- [ ] Alchemy has has an almost complete mechanical overhaul, but hopefully doesn't feel different when playing, except for being balanced now
	- [ ] Potions no longer stack
	- [ ] Weight, value, XP gain adjusted
	- [ ] Strength of effects now tied to spellmaking costs
	- [ ] Tools now behave differently
	- [ ] See alchemy section, lots of changes
## 2.1, Enchanting

**Unchanged from earlier coda versions:**
- All items with enchantment capacity now range from 30-120 points capacity. This was achieved by modifying `TES3MP\apps\openmw\enchanting.cpp` to calculate item enchantment capacity using an exponential with a minimum of about 30 (at 1 capacity in base game) and a maximum of about 150 (practically, no core items will exceed this value).
	- Compatible with all items from all mods, as the change is to how capacity is calculated in the engine, and not a change to the items themselves. Providing the mod author has given them at least 1 capacity they will have around 30 now. At about 100 capacity there is no change. Beyond 100 there are diminishing returns, the Daedric tower shield (225 base game) has about 150 using this system. 400 capacity would become 200, 1000 would become 300.
	- This was done to allow all items to be practical for enchanting
- Enchanting on-use costs now operate on a curve, which caps out at reducing the cost to about 40-50% of the original value at 100 skill.
	- Added to avoid excessive cost reductions, which can trivialise the entire game otherwise with minimal effort (the normal behaviour would be considered an exploit in most other games)
	- Beyond 100 skill there are only marginal gains, with a skill level of 200 only reducing on-use costs down to about 35% in most cases
	- The minimum cost is 1, no items including 1 cost items can be reduced to costing 0 charge
	- Low values (those with original on-use costs of less than 5) will reach their maximum reduction sooner, at around 50-75 skill
	- All costs values remain integer, so there is some rounding at the low end
	- On-hit weapons have a further reduction applied which results in them having far lower on-use costs, but still following the above logic (typically around 1/4 the expected cost after the above modifiers). This was done to give them a niche as long lasting (and less powerful due to enchanting cost changes) items, it is also a QoL so that you don't have to be as miserly with your charged weapons when cutting through weak enemies
- The spell effect to enchantment capacity ratio now varies by spell, spell school and by enchantment type. The checks implemented for this mean that every spell effect could have a different cost for the purposes of enchanting, compared to as in player spellmaking and alchemy.
	- List of various changes implemented, unless otherwise stated the cost increases stack:
		- Keep in mind these are balanced around the V0.80 spell cost GMST changes in the associated ESP file
		- Also I do not like this system at all, it was one of the first things I coded and it is not of the same quality of what came later
	- All destruction and restoration point cost increases doubled
	- All alteration and conjuration point cost increases halved for scrolls only
	- All instances of Dispel, Restore attribute, Absorb health, Absorb fatigue and Resist paralysis doubled in point cost
	- All instances of fortify attribute halved in cost
	- For constant effects only; Shield, Chameleon, Sanctuary, Restore Fatigue, Fortify attribute, and Resist Paralysis are x1.5 cost (this stacks with the previous cost reduction for fortify attribute)
- Enchanting success chance is modified post-hoc, but the open morrowind success equation is still used to provide the base success chance with no changes being made to it.
	- All non constant effect enchantments get harder to make beyond 20 points, and significantly harder to make beyond 25 points. At 100 skill you will struggle to make something 25 points and beyond. This was designed to prevent artefact like items being made easily. If you buff your skill to absurd levels you can still do this however, but the change was balanced around the assumption that you are not exceeding 200 skill (as per core tes3mp server settings)
	- Scrolls get a flat +25% success rate
	- Enchantments with an equivalent magicka cost below 5 points get a flat +25% success rate
	- Constant effects now require a base (unmodified) enchanting skill of 75 to make, and the capacity you can now successfully enchant rises with your base enchanting skill (and at 100 skill becomes any amount with 100% success rate)
- If the Openmw multiple enchanting ammunition settings is turned on, then you will enchant ammo in batches of up to 20 (difficulty adjusted to account for this). If not ammo behaves normally (one per soul gem). Due to how multiple items are processed in open morrowind, this means that if the setting is on and you enchant less than 20 arrows at once (having less than 20 in your inventory) you will actually get a boost to enchanting success. It is not enough to allow any exploits, so it was left in as a way to make a handful of stronger arrows at a time if you need them.
	- There is a visual bug where it can display an arrow as having 0 charge, but from testing these seem to work normally anyway.
	- I don't believe the value of the Openmw setting matters anymore as to how many arrows you can make, as this new behaviour is partially hardcoded to 20. But just in case set the value in the config file to `0.5`, as this was what was used throughout development and testing.
- Enchanting service prices set to scale non-linearly with point cost, approaching much higher costs than in the base game for non constant effects, to reflect the fact that a 20 point enchantment would now require 100 skill to reliably make. Beyond 20 points the price ramps up massively, and beyond 25 or 30 points depending on the enchantment type (on-hit, on-use, etc) it becomes "impossible" to afford. This was done by adding a flat 5 million gold cost to values that exceed these amounts, in theory if you have that much you can then keep going. Will never be a problem during normal play.
	- Scrolls cost about 4k to make a single 20 point effect
	- On-hit costs about 100k to make an on-hit 20 point effect
	- On-use costs about 75k to make an on-use 20 point effect
	- Constant effect behaves differently and the price increases mirror the break points used in player skill. There is a flat starting cost of 70k for any constant effect. The first 30 points will cost a total of about 100k, and then it ramps up non-linearly from there. A single 100 point CE will costa bout 400k, and beyond that point it becomes "impossible" with the flat 5 million gold cost increase being applied
	- I also don't like how I handled this, but it will do the for the beta version

---

## 2.2, XP gain

- XP gain adjusted per skill as per the ESP changelog
- XP gain reduced at high skill levels with the following modifiers:
	- Below 50 = x1
	- 51-60 = x0.8
	- 61-70 = x0.65
	- 71-80 = x0.55
	- 81-90 = x0.4
	- 91-100 = x0.33
- Skills at level 30 and below now require 30xp to level, rather than the base game requirement of 1xp per current level. Done to make levelling for low level skills more difficult, and your initial skill choices more meaningful.

## 2.3, Training costs

- Base price at 1 skill is as previously but +100g to provide a floor
- Pricing behaves normally up to 20
- Beyond level 20 the cost of training a skill increases non-linearly. The price multiplier increases at levels 21, 31, 51, 71, 81 and 91
- Overall the price increases massively for the last 20 levels, with level 90 costing 9000 gold and level 95 costing 12,000
- All of these changes respect the GMST, which is left at 10 by default. To halve the prices the GMST can be adjusted as normal, and the non-linear pricing system will adjust down accordingly

## 2.4, MR cap

- [ ] Magic resistance now provides no benefit to the player beyond 60% (after accounting for weakness effects which negate it 1:1). No changes to how it works for NPCs or creatures.
	- Done for balancing reasons, otherwise 100% MR trivially negates most negative effects in the game
	- The player will still see on their UI that they have a magic resist with magnitudes above 60, but it no longer has any mechanical benefit
	- However if the player has weakness to magic, additional magic resistance can be used to first negate that penalty and then get them to the 60% cap. So for example a player with 30% weakness to magic will receive a mechanical benefit from up to 90 points of resist magic, which will first cancel the weakness and then get them to the 60% cap
	- Effects that magic resist applies to: all drain x, all damage x, all absorb x, all weakness effects, and burden, blind, sound, and silence
		- I left out weakness to magic, It seemed complicated to test, you will still be immune to that if you reach 100% MR
	- Enemies will still behave as if the player has immunity once they reach 100% MR even though that no longer gives the player immunity, decision made to leave this behaviour in for maximum compatibly with all mods and to avoid 'edge case' behaviour issues by AI in the core game (such as AI fighting AI)

## 2.5, Miscellaneous changes and fixes

- [ ] Skill books do not work at skill 95 and above anymore
	- Done to go alongside the greatly increased difficulty of training skill past 90, and the increased training costs when paying for levels
- [ ] The sound played when repairing equipment with armorer's tools has been reduced to 50% the original volume
	- It was way too loud

## 2.6, Melee changes
These apply to all melee attacks, the accuracy also applies to hand to hand, but otherwise hand to hand has it's own damage logic in it's section

**Accuracy**
- [ ] Melee accuracy now starts higher at low skill levels (minimum in practise is about 15% against most low level enemies), and reaches a lower overall cap in practise (at 100 skill, against the strongest enemies, your hit chance is 90% with mid fatigue, 108% with max fatigue, and only 72% when your fatigue is empty)
	- This was done to smooth the entire skill out, low levels are more playable now and high levels stop effectively auto-hitting beyond skill 60-70 (which made weapon skill past this point feel redundant)
- [ ] However all two handed weapons (with some exceptions in the weapon type benefits below) now take a -15 to hit, to make the choice between 1h and 2h meaningful (and to make 2h weapons a better choice at higher skill). In theory being able to wear a shield is the sacrifice to use a 2h, but in practise it rarely felt worth it in the base game outside of roleplaying

**Damage**
- [ ] Strength now contributes half as much to damage bonuses or penalties, and your weapon skill now contributes half as much as strength did. In other words the game now checks if either your strength or weapon skill are above/below 50, and uses them both to compute the +-50% damage modifier.
	- For example now with 100 strength and 50 skill, you only get +25% damage, and you need 100 strength and 100 skill to get the original +50%. With 50 skill and 1 strength, you now get a -25% damage modifier, and with 1 skill and 1 strength you get the original -50% damage modifier.
	- This was done to add more value to levelling weapon skill
	- There are exceptions or adjustments to this rule in the weapon type benefits below

**Weapon type benefits**
- [ ] All weapon types have an additional bonus depending on what they are:
	- **Short blades** have a +10 accuracy boost (equivalent to about 15 skill levels)
	- **Long blades** now gain up to an additional +25% damage modifier at 100 agility (starting at no change at 50 agility, with no penalty for being below). e.g. at 50 agility the damage is normal, at 1 agility the damage is normal, at 75 agility the damage is +12.5%, at 100 agility the damage is +25%. This stacks with the damage changes above, and stacks with strength and skill, for a potential total maximum damage of 175%
	- **Axes** are the same as long blades but they use your endurance above 50 instead of agility
	- **Maces** are the same as long blades but they use strength above 50 instead of agility (in addition to the normal benefit from strength)
	- **Spears** have a +10 accuracy boost but no damage increase mechanic, and do not take the -15 to hit that all 2h weapons do in this system
	- **Staffs** (a sub-set of maces) have a +20 accuracy boost (as they have truly awful damage), but still receive the strength bonus from maces above. They also do not receive the -15 to that that all 2h weapons do in this system
		- `BluntTwoWide` is what specifically is being considered a staff, as this is how it is used in the base game. This could lead to minor balancing issues if modded content is adding powerful 2h maces to the `BluntTwoWide` category rather than the standard `BluntTwoClose` which is used for mauls. May be that the staff accuracy change is reverted if this seems to be an issue with major mod content

## 2.7, Ranged changes

- [ ] All ranged attacks get a +20 bonus to accuracy
- [ ] Bows and crossbows scale their damage with same logic as melee, half skill and half attribute, but they use agility instead of strength to determine damage
- [ ] Throwing weapons use strength and skill, but now scale to 200% stated damage rather than 150% for other weapons (so at 100 str and 100 skill a throwing weapon does 2x stated damage, rather than 1.5x). This is a linear 0-100 scaling and was done for balance reasons to keep them competitive
- [ ] Non-enchanted ammunition is now recovered at a rate of 1x GMST at 0-25 skill (never less than 1x GMST) up to 4x GMST at 100 skill (scaling linearly from 25-100 from 1x to 4x). At 100 skill you will recover ammo at 100% rate.
- [ ] Enchanted ammunition is now recovered (not possible at all in base game) at a rate of 0x GMST up to 50 skill, then scaling linearly up to 1x GMST at 75 and 2x GMST at 100 skill. With default GMST settings this means you will recover enchanted ammunition at 50% at 100 skill. For balance reasons, the function that controls this caps player skill at 100 when considering enchanted ammunition recovery rate. So even if you buff your skill into the 100s, you will be hard capped at an enchanted ammunition recovery rate of 2x GMST.

## 2.8, Acrobatics and climbing
Currently (V0.80) this feature is tied to your base climbing skill (not modified) so that even if your acrobatics is drained or buffed, you do not change your ability to climb.

This was done intentionally to avoid unintended physics behaviour when the players acrobatics skill changes mid-climb.

This does not allow true Daggerfall style wall climbing, but everything that is not a vertical surface is now climbable with enough skill.

**Mechanics**
- [ ] If skill is 30 or below, then you have the base climbing angle of 47° (no change from base game)
- [ ] If skill is 30-60 then you add (skill-30)/3 degrees, so that you scale from 47 to 57° being climbable at 60 skill
- [ ] If skill is above 60 then you start adding 1° per skill level (in addition to the 57° you will have reached so far by being 60)
- [ ] The benefit caps at 89° which is reached at 92 skill.

**Research**
How the change in degree of climbing plays in practise
- [ ] 47° - Base game, at skill 30 and below.
- [ ] 57° - Reached at skill 60. In practise a very noticeable improvement, most base game hills can now be climbed if you search around for a shallow enough incline. This angle increase has more of an effect than the small number increase would suggest
- [ ] 67­° - Reached at skill 70. The majority of exterior obstacles are now scalable in the base game with a little effort finding a route. Not enough to climb buildings in urban areas (unless they have sloped sides) but more than enough for most wilderness trekking without having to rely on levitate.
- [ ] 77° - 80 skill. Practically any exterior obstacle is now scalable, although not necessarily in a straight line (some very sleep stopes may require some moving around to find a path still). A lot of spacious interiors (such as those using the cave interior pieces with sloping sides) are climbable as well
- [ ] 89° - 92 skill. Anything non vertical is now climbable, technically you could encounter a slope with 89.9° and not be able to climb it. This could be fixed in future versions (if it something that needs fixing). It was decided to cap angle below 90° to avoid wall collision issues and sticking on non-wall but otherwise intended to be vertical surfaces (see compiling comments).


## 2.9, Difficulty Tiers and new difficulty scaling

The collective output of this section is to break from a slider scale difficulty system and to move to one with distinct tiers as in later games, there are now six tiers with fixed damage modifiers.

This new system also scales player magic damage done, via spells and enchantments, to enemies, and has checks in place to account for reflected damage.

This version (V0.80) has been tuned for co-op multiplayer, so it heavily reduces damage done. Single player versions will likely get a fix and revise the damage done up a little.

The following sources of player damage were not scaled in this implementation - these will still do full damage at all difficulties
- Player summons (due to how tes3mp handles non player actor vs non player actor combat), a workaround is planned for later versions
- Actors 'mind controlled' with the command spells - this was intentionally not attempted in this version, but would ultimately have the same problems as with summons
- Player allies from other sources, such as followers on quests or the pack rats you can buy in mournhold - these will always be intentionally excluded from these difficulty scaling changes, as I want to maintain maximum compatibility with ESP level modded content


The new difficulty tier system:

| Tier | % Melee/<br>on-hit ench<br>Dealt [1] | % Melee <br>taken | % Magic/ench<br>damage<br>Dealt [2] | % Magic<br>taken [3] | Fatigue dealt (H2H) [4] | Fatigue taken (H2H) [4] |
| ---- | ------------------------------------ | ----------------- | ----------------------------------- | -------------------- | ----------------------- | ----------------------- |
| 1    | 100                                  | 100               | 100                                 | 100                  | 100                     | 100                     |
| 2    | 75                                   | 150               | 85                                  | 125                  | 85                      | 125                     |
| 3    | 50                                   | 200               | 70                                  | 150                  | 70                      | 150                     |
| 4    | 30                                   | 300               | 50                                  | 200                  | 50                      | 200                     |
| 5    | 20                                   | 400               | 33                                  | 250                  | 33                      | 250                     |
| 6    | 15                                   | 500               | 25                                  | 300                  | 25                      | 300                     |
[1] The two (melee and on hit enchantments) are scaled by two separate functions, but I mirrored their values for this version (V0.80) for balance (to be play-tested)

[2] This includes all spells and enchantments, except for on-hit effects which for now mirror the reduction in magnitude given to melee for first pass balance reasons

[3] This is only magic damage inflicted by actors other than the player, so any self cast effects (potions, spells, ingredients), or any effects that come from the world (traps, scripted effects) are not scaled by this system. Traps were intentionally excluded from scaling in this version, but could be re-introduced later if appropriate (I didn't want to make players turn down the difficulty when lock picking to avoid getting one-shot)

In V0.80 only spell effects which directly deal damage have the step-down applied to them. These are: [14] Fire damage, [15] Shock damage, [16] Frost damage, [18] Drain health, [23] Damage health, [27] Poison, [86] Absorb health. In theory any spell magnitude can be modified, and with proper logic guarding I think in practise they can be - but for now I want to just playtest the direct damage effects to get a feel for balance.

[4] The hand to hand changes were added in V0.70, where it was determined that tying fatigue dealt/taken to normal melee scaling was too punishing for the player in both directions. As of V0.70, it seems to work well operating off the same scaling that magic does.

The new tiers are controlled by the global difficulty score as defined in the server config file, in the following way:

| Server value | Tier | Comments                          | Tier name [1] |
| ------------ | ---- | --------------------------------- | ------------- |
| Less than 0  | 1    | 1 = normal, unchanged, difficulty | Apprentice    |
| 1-50         | 2    |                                   | Journeyman    |
| 51-100       | 3    |                                   | Master        |
| 101-150      | 4    |                                   | Grandmaster   |
| 151-200      | 5    |                                   | Agent         |
| 201+         | 6    | 6 = absurdly difficult            | Nerevarine    |
[1] Note: These names are not implemented anywhere in game or code, they are just the documentation names for these tiers

So if in the server config you set difficulty to 132, the engine will now convert it to "tier 4" and apply all processing as per the tier 4 modifiers. There is no difference between numbers within a bracketed range, difficulty 132 and 149 now both equate to tier 4.

**How reflect is handled**
Anything reflected onto the player is at 1x it's default magnitude, for balance reasons
Anything reflected by the player onto a non-player actor is stepped down by difficulty tier.

**Tes3mp gameplay issue found during testing**
- When two players are attacking the same target with melee, everything works fine
- But whoever is the cell owner appears to be the only one who can inflict magical effects on the target - so direct offensive spell-casting does not work if you are not the cell-owner
	- Even being in a group does not fix this
	- This seems to be a core tes3mp issue which is not to do with my magic magnitude changes - found it occurred equally on default tes3mp I had not modified at all, so I haven't made it any worse it seems

**Points for clarity**
- As in the base game, the difficulty scaling for physical damage comes after armour based damage reduction. This is a good thing, as otherwise absurd and unachievable armour ratings would be required on high difficulties.
	- So you still need the same armour ratings on Nerevarine difficulty as you do on Apprentice, but since armour has a damage reduction cap of 75%, you still take massive damage on the highest difficulties!

## 2.10, Equipment derived armour ratings

For the three armour skills (heavy, light, medium) the equation used to determine player armour value below 30 skill was adjusted to be less punishing.

In the base game, your armour rating is your skill/30 as a %, so 100% at skill 30, 200% at skill 60, etc. However this meant for relatively untrained skills you got negligible armour values which made wearing off-skill armour pointless without training.

For example, previously at 5 skill in heavy armour wearing a full set of Dwemer heavy armour would give you 3 armour class instead of 20 AC at 30 skill.

The only change made is to soften that initial 1-30 curve, so now for skill levels below 30 only (and for the player only, NPCs are not affected), the equation is now:
`(skill + 5) / 35`,
then once you reach skill 30 it resumed behaving normally via skill / 30.

The effect of this change is that at the skill levels shown below you now get the % of the armours base value listed, compared to what you got in the old system shown in brackets.

5 skill, 28% (versus 16%)
10 skill, 42% (versus 33%)
15 skill, 57% (versus 50%)
20 skill, 71% (versus 66%)
25 skill, 85% (versus 83%)
30 skill, 100% (versus 100%)

This is really only impactful at skill values below 20, and serves to make armour switching mid-game less reliant on training.

In addition this change complements the revision to XP required to level skills, as previously a skill required XP equal to it's level to advance (so if you had heavy armour 5, it would reach level 6 within only 5 hits, and so on) - but now as of V0.20 a skill never requires less than 30xp to level, so this early game is intentionally slowed down (to prolong the time you spend playing before the power threshold), so I felt armour needed a slight tweak for this reason also

The current implementation of this logic change for skills below 30 does not respect the GMST particularly well by design, but overall changing the GMST still has a very minimal and non game-balance disrupting impact
	- The game controls how armour rating scales by skill using a GMST. It is not necessarily skill / 30 in the base game, it is in fact skill / `iBaseArmorSkill`, which is set to 30 in the base game
	- So if someone changes that GMST it slightly disrupts how my logic behaves below skill 30, but the change is robust to all reasonable GMST changes (from values of 10 up to infinity, problems only occur when the GMST is set to very small numbers like 10 or less, but in reality no one will ever be doing that and expecting balance compatibility with anything - a GMST of 10 means you would have 10x the stated armour value for a piece of armour once you reached skill 100, full Daedric would now grant 800 armour rating in that theoretical system!)


## 2.11, Unarmoured derived armour ratings

Unarmoured has been overall buffed massively, so that it is viable without having to rely on the old system of boosting your skill far past 100. 

In my opinion (in the base game) it was enough of a downside to go without wearing enchantable items, without unarmoured also being practically useless for most the game.

However despite that I have balanced unarmoured still as weaker than fully heavy armour. Morrowind is a roleplaying game, unarmoured doesn't need to be the best, just viable.
- I still think is too generous, I have some ideas to adjust the whole system where attributes above 50 start giving flat bonuses to unarmoured. I am worried I 'gamified' the changes too much in this version

Instead of the old logic, which was `skill x skill x 0.0065`,
a new three tiered system has been added to get a smooth curve at the start, which can then keep up with high end armour towards maximum skill

**The new logic is:**

For skill levels below 30, `AC = Skill/3`
For skill levels 30 to 70,`AC = 10 + ( (Skill - 30) * 1.625 )`
For skill levels above 70`AC = 75 + ( (Skill - 70) * 2.5 )`

In addition the players armour class for unarmoured gets a % bonus based on their agility and speed if either are above 50. 
- They each contribute the same % modifier above 50. For each attribute, for every 2 points it is above 50, you add 1% to your unarmoured derived armour class
	- So 100 speed and 50 agility results in 1.25x multiplier
	- 100 speed and 100 agility results in a 1.5x multiplier
	- There are no penalties for being below 50 in either attribute

The whole calculation for the player respects the GMST `fUnarmoredBase1` and relies on it being 0.1 (the default base game setting for this GMST).

Adjusting that GMST up or down will linearly scale all armour values obtained from unarmoured, as the end step of processing is the armour rating to far x 10 x `fUnarmoredBase1`

## 2.12, Creature armour ratings

All creature type entities (entities which are not classed as NPCs in the engine) did not previously have any armour rating. Even a storm Atronach had an armour rating of 0.

Now all creatures have 10AC as a baseline, which shield magnitudes are then applied to.
Creatures level 5+ gain 2AC, for a sum total of 12AC
Creatures level 10+ gain 5AC, for a sum total of 15AC

The idea is just to make all creatures a little more durable at low levels, with a very slight scaling up to medium tier creatures (which could be far more aggressive, or specific, but I want to keep this mod friendly so I am capping and flooring the contribution quite narrowly so even in strange ESP mod situations with atypical creature level to creature combat power the balance is not significantly affected).

The values provided by this are likely to be revisited in future versions.

## 2.13, Armorer

### 2.13.1 Equipment degradation rates

As part of a push to increase the value of the armorer skill, the rate at which all player worn equipment (weapons, shields and armour) degrades is reduced as your armorer skill increases.

All items now degrade at only 25% of their normal rate once you reach 100 skill, and this is a hard cap of reduction which can be achieved.

The formula is just ( skill x 0.075 ) as a % reduction to equipment degradation rates. This does take effect from level 1 in this version, meaning a character with 5 armorer already had a slightly reduced equipment degradation rate (96.25%).

### 2.13.2, Your armorer repair success rate now depends on item value

This is a massive overhaul to default armorer behaviour.
In the base game, your success rate is determined solely by
`float x = (0.1f * pcStrength + 0.1f * pcLuck + armorerSkill) * fatigueTerm;`

In this overhaul, items are divided into 'tiers' within the code block, and the difficulty of repairing an item at a given skill level varies by the tier that item belongs to.  Higher tiers are harder to repair.

The tiers are as follows,

| ARMOUR          |          |                                                                   |
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


Weapons were lowered one difficulty tier up until tier 5, which is where you start approaching the 'power threshold'. This was done so that armorer remained an optional skill for anyone using any common weapon - weapons break quickly, and unlike a single piece of armour breaking, if your good weapon breaks you are at a massive disadvantage. For that reason, they are easier to repair overall up until you start using powerful weapons - then they equalise in difficulty with repairing armour.

This graph shows success rate in repairing for each item tier, by player skill. It assumes you are getting a +7 from your attributes, which is the minimum possible boost (due to the lowest starting strength and luck being 30 and 40 respectively). In practise, your success rates will be higher than this at higher levels if you are investing in those attributes as you play.

Also note that every repair attempt now has at least a 5% chance to succeed. For tiers 1-3 this is between 20-15%, to allow for reasonable training and repairing without picking the skill.


![[Pasted image 20250615192911.png]]

Broadly, since the amount repaired is proportional to your success rate, not your level, the sweet spot at which maintaining your gear becomes viable is around the 50% success rate mark.

In summary:
- Artefacts and other items with values of 50,000+ are not practically repairable until about skill 80-90 without boosts to armorer
- Everything less than 2000g is reasonable repairable from the start if you have 30 armorer
	- With only 5 armorer you will instead have about a 15-20% success rate floor for a while, so even then you can train and top up important items when away from repair services
- Items above 5000g are where it starts to become much harder to repair things,
	- T5, 5000-20,000g needs about 50 skill with some attribute or item boosts to maintain reliably away from services
	- T6/7 need much higher skills, approaching 100 without good attribute/item support, to maintain


### 2.13.3, Armorer's tools now modify success rate

Since the new system requires you to have high armorer skill to maintain high end items, I wanted to add another way to work around an otherwise hard skill requirement.

Now in addition to boosting the amount repaired, the quality of an armorer's tool also potentially boosts your effective skill level when repairing something.

`(tool quality - 1) x 10 x 1.5`

is added to your skill.

So a tool with 0.8 quality results in you effectively losing
0.2 x 10 x 1.5 = 3 skill levels
when repairing something

A tool with quality 1.7 (grandmaster's armorer hammer), adds an effective 10.5 skill levels to all repair attempts. Meaning if you can source the best tools, you will be able to repair items at least a tier ahead of what you would otherwise be able to.


### 2.13.4, Armour repair costs

In the original game, items could never cost more than 1gp per item health being repaired.

This was changed so that now to fully repair an item costs 50% of the item's full value, and anything less than a full repair costs proportionally less.

Due to the effects of mercantile, you will never pay this full 50% in game. Expect closer to 40-30% depending on the haggling factors.

For example,
- You want to repair a weapon which costs 5,000 gold, and has lost 100% of it's durability
- The new repair cost is now 2,500 gold to fully repair that item, pre-haggling, versus 1 gold per health point lost in the old system

This is not a perfect system as it means some items which have low durability's but high prices become very hard to maintain by paying.

I am also wary that overall this may be too expensive, but this is a first implementation version to test, and since this does respect the GMST, this is something that can be changed by anyone at an ESP level whilst playing.


## 2.14, Athletics derived swim speed

In the core game, the player's swim speed is set to a % of their run speed, and increasing athletics increases your swim speed % (of run speed) from 50% to 60% as you go from 1-100 skill.

As of V0.40 coda the player's swim speed scales from 50 to 80% of their base run speed as they go from 1-100 skill.

There is a hard cap to how much athletics can contribute to swim speed of level 500 athletics (which works out to +150% run to swim speed, on top of the 50% you get at skill 1. For a total of 200% base swim speed at 500 skill).

This was done because in both cases, your swim speed rises proportional to the square of your athletics, so there is a risk of reaching some truly absurd numbers and crashing the game (and it's morrowind, buffs like this will happen).

## 2.15, Speechcraft review

No engine level changes, but the following ESP level changes were reviewed and kept as final pending testing.

**Speechcraft**
`fBribe10Mod` = 1
`fBribe100Mod` = 15
`fBribe1000Mod` = 150

These were changed to these values, down from 35/75/150.
The number value is the effective skill level boosts you get from making such a bribe attempt. Keep in mind bribery attempts use the mercantile skill to calculate success rate, so in the new system the 10 gold bribe is effectively you paying to use the mercantile skill instead of Speechcraft.

## 2.16, Mercantile

### 2.16.1, ESP level changes

- `iBarterFailDisposition` reverted back to -1 (the base game value), from 0 (modified value) in at least the 1F version of the ESP file.
	- This now means NPCs will properly lose disposition when you are haggling with them and fail.
- `fDispositionMod` changed to 0.25f
	- This means that mercantile haggling (but not not bargaining) is affected by disposition to 1/4 the degree it previously was in the base game
- Set mercantile XP from bartering back to 0.3xp, as it is in the base game, from the previous modded value up to this coda version of 0.9xp.

### 2.16.2, Summary of mercantile changes

- Disposition above or below 50 now only has 1/4 the effect it previously had on your mercantile bartering and haggling rates
- Haggling also now has the same reduction in the effect disposition has, so that haggling is 1/4 affected by disposition. This was done as an ESP level change by changing `fDispositionMod` from 1.0f to 0.25f
- Reverted a previous ESP change to core game behaviour, merchants now lose 1 disposition as they did in the base game when you fail to haggle with them
- Bartering rates (not haggling) are hard capped as follows:
	- You can never buy an item for less than 90% of it's base price, or be asked for more than 150% of its base price
	- You can never sell an item for more than 60% of it's base price, or be offered less than 20% of it's base price
	- These rates do not affect any services other than trading in a shop, so you can still get far better discounts on training, etc, as you level mercantile
- Haggling rates have been capped at +- 10%, this is a hard cap, to stop a potential exploit where you break even from buying/selling with haggling and endlessly circulate items back and forth for free XP
	- It being a hard cap is not very elegant, so this will likely be revised in future versions
- You now earn mercantile XP not through haggling (XP gain that way has been removed completely), but by selling items
	- This is based on what you sell those items for
		- It intentionally does not award XP for buying things
	- You earn 1XP for every 166gp you receive for sales in V0.80
		- This is controlled by the XP value in the creation kit, as the 0.30xp from haggling has been preserved and transferred to this XP gain system, so you can modulate the XP gain rates by adjusting that value in the creation kit at an ESP level
	- If you undersell an item, that is you sell it for les than it is worth (based on what the NPC offers you) then you will receive proportionally less XP from that transaction (as giving things away cheaply is not good merchant behaviour!)
	- Items you receive in return are counted towards the gold you receive from selling items. For example:
		- If you have 1000g worth of gems, and the merchant makes an initial offer of 500gp - you stand to earn 3xp from the transaction (as the system uses the sale value of the items, not their base value)
		- If you decide to sell them cheaply, say if the merchant is nearly out of gold and you just want to get rid of them, and sell them for only 250gp, then you will still earn XP but only 50% of what you would have earned for selling them at full price (so 1.5xp)
		- In that circumstance however, if the merchant is nearly out of gold you could ask for 250gp and 250g worth of items in return. The engine will correctly add up the barter value (not base value) of everything you receive in return, and in this case award you fill XP for the sale again (3xp)
- You no longer get any XP from haggling
	- This was a matter of taste, and ease of balance for the testing versions, you can still haggle and the reward is the gold you save, but beyond that I do not think it added anything to the skill to min/max the haggle offer for every sale - but I am likely to add this back in to some degree in later versions if the playtesting feels lacking without it

**Potential issues with this versions implementation**
- [ ] The GP/XP ratio is constant across all levels, so the first few levels from 5-30 are especially hard to achieve (about 4500gp of sales per level is needed)
	- You can either just pay for training to get around this, or I may put in a fix later on which steps down the gold needed at low levels - although right now I am reluctant to do that as it will make this new system even more opaque
- [ ] Haggling no longer awards any extra XP for going over
	- I could fix this, I will eventually, but it's a bit messy to do with how complicated the logic ended up being for this one in the first draft

## 2.17, NPC spellcasting locked to base game spell effect costs

NPCs are now hard coded to use the base game spell effect costs regardless of the ESP values they are set to, so that the values can be changed in any way without affecting base game NPC behaviour. The player is unaffected by this hard-coding and will respond dynamically to spell effect cost changes.

Overall this change was done with TR in mind. It does limit compatibility with mods that already change these values, but also it opens up those values to be adjusted to anything without affecting the world in TR and other base game magic effect modded content.

## 2.18, Alchemy overhaul

A complete overhaul of the skill, changing nearly everything about it, but the end result is it still behaves a lot like core alchemy.
This needs a lot of playtesting, but as with all previous changes, an effort has been made not to break from the spirit of morrowind, so overall it should still feel and play like the core skill - but with a lot of the exploits fixed or made much less viable.

**Potion value**
- The value of a potion you produce can never exceed the sum value of the ingredients used, otherwise it follows base game behaviour
	- This is an intentionally harsh cap for playtesting, as I really want to shutdown the infinite money from alchemy exploit that you can do
	- This goes in tandem with the mercantile changes, so it was also done harshly to make cross system interaction simpler for the time being

**Potion weight**
- Potions cannot weight more than 1.0, or less than 0.1
- Your alchemy factor, the base game equation which uses your alchemy skill, intelligence, and luck, is used to reduce potion weight
- By 90 skill, every potion you make will weight 0.1, regardless of the original weight
- But potions that would have been light in the base game remain so, this change just makes it so that you can actually use heavy ingredients in potions without the resulting potion weighing too much to be practical

**Potions no longer stack**
- Drinking multiple of the same potion now refreshes the duration, instead of stacking multiple of the same potion on you - as spells behave in the base game
- This means if you drink 100 alcohol, you don't get absurd strength bonuses, or if you drink 10 healing potions with a hotkey, you don't become immortal due to all the stacking healing
- But you can still stack lots of different distinct potions if you want

**Potion XP**
- The only change here is to potions whose average ingredient value is less than 5gp, the sort of logic below could be expanded to all potions, but for now it's just to stop spamming 1g ingredient potions being as good as it currently is (it still doesn't fix that entirely)
- If a potions average ingredient value is less than 5gp,
	- You earn 50% of the normal XP if skill 30 or below
	- You earn 25% of the normal XP if skill 30 to 60
	- You earn 12.5% of the normal XP if skill 60 to 90
	- You earn 5% of the normal XP if skill 90+
- Otherwise, if value is 5 or above, you earn XP normally

**GMSTs**
The new system is balanced around these GMSTs being the following, also note the change in behaviour for `fPotionT1MagMult` and `fPotionT1DurMult`

`fPotionStrengthMult` set to 1.0. 
- This still acts as in the base game as a % potion strength multiplier, but the new system is balanced around this being 1.0.

`fPotionT1MagMult` and `fPotionT1DurMult` were both set to 1.0.
- These two have had their function changed from the base game, they both act as % modifiers, with 1.0 being 100%, as `fPotionStrengthMult` behaves

**Potion success rate**
The baseline success rate has been adjusted so that it is,
`30 + 2/3 of your alchemy factor` as a %
The result is that 
- At 5 skill you have about a 40% success rate
- At 30 skill you have about a 55% success rate
- You reach 100% success rate at about 80 skill, depending on your attributes

Versus the base game, where you had almost no chance of making potions at low skill.

However the above success logic is further adjusted by the average quality (gold value) of ingredients you use in the potion,
- If the average gold value of the ingredients being used is 10 or above,
- The average gold value of the items being used in the potion adds a flat value to your potion making success rate (as a %) based on what the value is:

| Avg item value | +Success % |
| -------------- | ---------- |
| 10             | +10        |
| 25             | +12        |
| 100            | +24        |
| 200            | +40        |
This was done with a straight line equation, which is
- 8.4 + ((Average item value) multiplied by 0.158)

The idea here is to make it more rewarding to use expensive ingredients at low skill levels.
For example, if the potion had a gemstone worth 200g in it and some common salt rice worth 1g, it's average value would be 100.5g, and you would get a flat +24% to your success rate. In this case, you would get to 100% success rate at about 50-60 or so skill (depending on your stats).

**Potion strength, duration and magnitude**
This was significantly overhauled, with multiple changes to the logic which brings it more in line with spell maker costing logic (and hence effect strengths more like you would achieve with spellcasting or enchanting).

For context, the base game alchemy logic involves at one point `x / spell effect cost`, where x is the alchemy factor after being modified by mortar quality.
This was an issue as it did not conform to anything like normal spell effect strengths. Effects with costs below 1 ended up with absurdly high magnitudes/durations, and effects significantly above 1 tended to have very low strength.

Part of the reason for this change was also to bring potions in line with the other two magic systems (spellcasting and enchanting), so that when adjusting effect costs at an ESP level all three systems stayed roughly in sync in terms of balance.

The order of operations for these changes (in more detail below) is,
- Get the alchemy factor as in the base game
- Add or subtract from it depending on the quality (average gold value) of the ingredients being used
- Apply the mortar strength to modify it up or down (but mortars have a less dramatic effect than in the base game, for balancing reasons)
- Then work out the potion duration/magnitude using the new spellmaking like costing system
- Then finally apply all the other tools you are using (or not) to modify the resulting duration and magnitude

1: Modifying your alchemy factor depending on the quality (average gold value) of the ingredients being used
- If average value of ingredients is below 5, take a -30% penalty
- From 5 to 200 average value, the bonus follows a non-linear straight line equation
	- Average value 5g, gain a +10 to skill
	- Average value 10g, gain a +15 to skill
	- Average value 25g, gain a +20 to skill
	- Average value 100g, gain a +25 to skill, and a +10% modifier
	- Average value 200g, gain a +30 to skill, and a +10% modifier
- Beyond 200 it moves to a simplified linear bonus
	- Gain a skill bonus of +30, and the 10% modifier, and in addition for every extra 100g of average value, add another +10 to the skill modifier
	- This extra logic past 200g is very niche, at the time of making this there are only a handful of ingredients in all of TR with this value, and they are either officially not used or quest items. Nonetheless, morrowind is about freedom, so now you can make one really good potion with them if you want. It's still probably not a good idea.

2: Apply mortar strength
- This works just like in the base game, but the positive or negative multiplier from the mortar is reduced by 50%
- For example, if you use a grandmasters mortar you would have got a 150% modifier in the base game. Now you get a 125% modifier. If you used an apprentice's mortar you would have got a 50% modifier, now you get a 75% modifier
- This was done to tighten the range of potion strengths the new system produces, for balancing reasons (so that the other factors can have more of an impact, without tipping back into silly potion strengths like in the base game)
- It may not be necessary in the long run, but until the system has been play tested it has been left in as a precaution

3: Use a new magicka costed system to determine potion strength
- The alchemy factor generated so far is divided by 6, to get a magicka budget
- In the base game the alchemy factor ranges from 12 to 120, not taking into account the effect of the mortar and pestle, which results in a magicka budget of between 2 and 20
- In this new system, with the potential boost from items and the reduced boost from the mortar, you can end up at around 200, which is a magicka budget of 33
	- You can get much higher than this by boosting your skill, but at that point you kind of want the outcome to be unbalanced
- Then using the maths documented in the compiling changelog, the engine now 'spends' that budget 50/50 on magnitude and duration, as if you were making a spell using the spellmaking logic
- So the idea is that now potions will be balanced around what the equivalent magicka cost of casting that effect would be
- This magicka budget is per effect, if you stack two effects on a single potion you will get the entire magicka budget given to each
- For effects like water walking, which have no magnitude (it is always treated as 1 in the engine) the logic accounts for that and adjusts, properly spending the whole budget on duration (and the same for no duration effects, like dispel)

4: Then apply all other tools, which modify magnitude/duration using simplified logic
- Note that these modifiers below are modifiers applied to the duration and magnitude, not the alchemy factor, so they actually result in larger bonuses to potion magicka budget that the raw % values shown imply. e.g. a flat 20% boost to both duration and magnitude is more than a 20% boost to potion magicka budget, due to how the base game spellmaking logic counts magnitude twice
- All of these boosts stack with each other multiplicatively, not additively
	- The retort multiplies the duration and magnitude of positive effects by `1+(retortQuality/10)
		- So in practise, +5% at 0.5 Quality up to +20% at 2.0 Quality
	- The calcinator boosts positive effects and negative effects, but negative effects more strongly (as a trade-off, hopefully making negative effects matter sometimes)
		- Same positive boost as Retort, +5% at 0.5 Quality up to +20% at 2.0 Quality
		- Three times that boost to negative effects, +15% at 0.5 Quality up to +60% at 2.0 Quality
	- The alembic reduces negative effects via `effect * (1.0f-(alembicQuality*0.4))`
		- -20% at 0.5 quality, up to -80% at 1.5 quality
		- Hard cap of a 90% reduction at about 2.25 quality, only achievable if you have modded tools (the hard cap is to stop negative values occurring)

## 2.19, Bound weapons

All bound weapon items were modified in the ESP to drain 10 fatigue per second when wielded. In addition their normal effects of fortifying skills have been removed.

This is to balance them somewhat, with them now reducing your hit chance (unless you can manage the fatigue loss).

## 2.20, Bound armour

The armour rating you gain from bound items is good, it's significant early game and drops off late game, an ideal balance.

But the enchantments are very flat, they don't do much mechanically, and aren't interesting in the first place (all of them being flat static boosts to attributes or skills)

New enchantments have been added to each of the bound armour pieces in an attempt to make them more exciting and situationally useful.

**Bound helm**
- Detect animals (75)
- Night eye (20)
- Fortify attack (10)
`dwemcod_bound_helm`

**Bound shield**
- Reflect (15)
`dwemcod_bound_shield`

**Bound boots**
- Fortify speed (20)
- Sanctuary (10)
`dwemcod_bound_boots`

**Bound cuirass**
- Resist fire (20)
- Resist frost (20)
- Resist shock (20)
`dwemcod_bound_cuirass`

**Bound left gauntlet**
- Fortify strength (15)
`dwemcod_bound_gauntlet_left`

**Bound right gauntlet**
- Fortify agility (15)
`dwemcod_bound_gauntlet_right`

## 2.21, More XP from casting expensive spells

Part of the reason magic skills feel slow to level in morrowind is that you do not gain any more XP from casting more powerful spells, but naturally as you level you tend towards using more powerful spells that exhaust your magicka pool in fewer casts.

So in most cases you actually level slower as a result of this alone, despite throwing a lot more magicka into casting.

To address this partially, you now gain slightly more XP as the spell cost rises. It is intentionally a weak increase at the moment, so as not to overturn how it feels to play a mage.

Below 5 magicka, gain normal XP
Above 5 magicka, use,
`y = 0.0888888888889x + 0.555555555556`,
where y is the XP multiplier and x is the spell cost

This results in,

| Spell cost | % multiplier to XP |
| ---------- | ------------------ |
| 5          | 1                  |
| 10         | 1.43               |
| 15         | 1.87               |
| 20         | 2.31               |
| 30         | 3.19               |
| 40         | 4.07               |
| 50         | 4.95               |


## 2.22, Summons rebalance

- I don't love this, it will change or come out entirely once summon damage balancing is done

A total review of summoned creatures, some dramatic changes, but again overall trying to stick to tone. Not happy with scamp having a blind, think that's the most tone breaking, and a lot need testing to see if they are too weak/strong (that will also be something that cannot be properly resolved until the difficulty not affecting summons issue is resolved with a server rebuild)

In addition to the changes below, all summons changed have had their soul values set to 0, so you can no longer fill soul gems with your own summons.

For now, the sphere centurion, bloodmoon summons, and the verminous fabricant have not been balanced.
- The sphere centurion and fabricant already have no souls
- I have left the other three (bloodmoon, wolf, bear, bone wolf) completely unchanged, including keeping their original soul values. They will be returned to in the future.

### 2.22.1, List of changed summons

**Ancestral Ghost (7)**
- +5 health, from 23 to 28
- Added 10 points of passive sanctuary via `dwemcod_summon_ghost_sanctuary`
- Updated spell (unique ID, `dwemcod_Ghost_Curse`) to do 5-15 points damage health, drain endurance 5 points for 30 seconds, and 2 points damage fatigue for 30 seconds
	- Vs original of 1-10 points damage health, drain endurance 5 points for 30 seconds, and drain fatigue 10 points for 30 seconds

Summon niche: Early game evasive summon, weak melee, okay spell damage, damages fatigue a little as well.

Comments on changes: A little more health, and 10 point sanctuary, add to it's survivability. The passive 'ghost effect' gives it 50 chameleon, which comes out to a passive equivalent of 10 points sanctuary already in the base game. These changes position it as an evasive early game summon. The spell was updated to hit a little harder, and the useless 'drain fatigue' effect was changed to a weak damage fatigue for the same duration, making it feel more like a curse (now your opponents will actually hit a little less often after being cursed).

**Scamp (12)**
- Added spell `dwemcod_summon_scamp_blind`
	- Name: Oblivion's Caliginy
	- 10 magicka
	- blind 25 points on touch for 10 seconds
- Lowered magicka (spell points) to 50, so that the scamp can only cast this five times at most

Summon niche: Early game melee 'rogue-like'  summon, with a short duration blinding spell with limited casts. Retains all base game resists, so immune to normal weapons and quite resistant to a lot of magic types.

Comments on changes: I wanted to give the scamp a niche that was distinct from the other early game melee summon, the skeletal minion. The scamp has been positioned as more of a trickster, with a blinding effect. The blinding isn't canonical though, so I don't love it, but it's a coda for a reason.

**Skeletal minion (13)**
- +7 health, from 38 to 45
- Changed iron shield to steel shield, primarily for visuals, practically no mechanical difference
- Random iron weapon changed to `dwemcod_random_silver_weapon`
	- So now they can hit targets immune to normal weapons
	- This new table also has a 1/3 chance of giving the skeleton a silver weapon enchanted with 1-4 frost damage (a steel mace with this enchantment is also on the table, though there is no equivalent silver unenchanted mace)

Summon niche: Melee fighter with blocking and a semi-randomised weapon. Average higher melee output than the scamp as a result.

Comments on changes: They were originally strictly worse than the scamp, this gives them a semi-random weapon which adds more punch. Health was increased to bring them in line with scamp, and the shield was changed for visuals (very little effect mechanically).

**Bonewalker (13)**
- Replaced two drain spells with higher magnitude variants, but kept the same manually defined costs
	- Drain strength 2-4 for 60s becomes drain strength 10-20 for 60s `dwemcod grave curse: strength`
	- Drain endurance 2-4 for 60s becomes drain endurance 10-20 for 60s `dwemcod grave curse: endurance`
- Lowered melee damage slightly from 4-12 to 3-11, making it an average of 7, versus scamp average of 10, so overall 30% less melee damage output
- Kept the very low movement speed (12 speed) and the high health (60)

Summon niche: Slow moving, high health, relatively weak, debuff specialist

Comments on changes: Tried to keep it in niche, just amplified it's ability to drain attributes to something meaningful.

**Greater bonewalker (19)**
- Has a good niche as the damage strength summon, it might be too good at that - but that's a base game issue I haven't addressed for now
- The only change, and problem with the base game spell, was that it's original spell effect cost was (IMO) too low, at 15, so it has been increased to 19
	- For comparison, lesser bonewalker is/was 13, so there was no reason not to use greater bonewalker as soon as you got it. I think it needed to have a jump in cost, given the fact it is a complete shutdown against some enemies with the damage attribute spells.

**Clannfear (22)**
- Speed increased from 14 to 30, it goes fast now due to the model and animation
- Melee increased slightly from 6-18, to 10-20
- Otherwise left as is, no resists, good health (113)

Summon niche: Fast melee hunter, like being torn to pieces by an angry daedra

Comments on changes: Made it fast, and bought the damage up a little (since it has nothing else going for it) to make it's niche a charging murder machine, good versus casters, rangers, and just a little more viable overall as a melee. Still might be too weak overall, but not everything has to be balanced, it's just a good fighter style summon in the midgame.

**Flame atronach (23)**
- Has a good niche as a fire magical dps already
- Lowered AOE from 10ft from 5ft, to make them less likely to hit allies/player, but kept cost the same
	- A new unique spell ID, left core fire bloom as is, `dwemcod_summon_firebloom`

Summon niche: fire magic dps

**Bone lord (25)**
- Replaced the second barrier spell (20pts shield for 30s on self) with a passive ability, shield 20pts. No stronger, but now it doesn't waste time buffing itself when summoned
	- `dwemcod_summon_second_barrier`
- Replaced the useless drain speed 2-4 pts for 60s curse with `dwemcod_grave_curse_bonelord`
	- Drain speed and agility, 10-20 points, for 60s on touch

Summon niche: Undead melee backed up with defensive spells and another potent curse variant

**Frost atronach (27)**
- Has a good niche as a frost magical dps already
- Lowered AOE from 10ft from 5ft, to make them less likely to hit allies/player, but kept cost the same
	- A new unique spell ID, left core frost bloom as is, `dwemcod_summon_frostbloom`

Summon niche: frost magic dps

**Dremora (28)**
- Has a good niche as a melee heavy hitter, has reflect, random weapon table scales with level up to daedric (which gives it very strong dps), also high health
- No changes

**Hunger (29)**
- Removed disintegrate weapons and armour on target
- Added, disintegrate armour 20 points for 30s on touch (cost 30)
	- `dwemcod_summon_hunger_disint`
- Left paralysis as is
- Lowered total magicka to 110 points, to limit paralysis spam potential

Summon niche: Disintegrate and paralysis 'special effect' melee caster

Comments: Base game behaviour is, if enemy has armour/weapons: almost exclusively spam disintegrate, if not: almost exclusively spam paralysis. The change means even against an armoured target, it chooses not to spam disintegrate armour (as it can recognise the effect is still applied and there is no benefit to recasting it), and will prioritise paralysis. The magicka cap of 110 (down from~250) is an initial attempt to stop it being infinite paralysis casts. If it misses disintegrate it will recast that at 30 magicka, hence the still high cap (given paralysis only costs it 10 magicka to cast)

**Daedroth (32)**
- Replaced third barrier (30pts shield for 30s) with a passive 30 point shield ability
	- `dwemcod_summon_third_barrier`
	- Same reason for change as with bonelord, means it gets right into fighting instead of spending time buffing when summoned
- Reduced the AOE on the shock bloom from 10ft to 5ft with new unique ID spell (same as is used for storm atronach)
	- `dwemcod_summon_shockbloom`
- Did the same thing for the poison bloom, new ID, also buffed slightly from 1-20 for 5s to 1-25 for 5s. Why does poison need to always be worse than shock? Poor poison.
	- `dwemcod_summon_poisonbloom`
- Retains the healing, but in practise they rarely cast it as they have normally run out of mana by time they get that injured
	- Something for a future version after some more testing

Niche: Tanky (shield), caster like atronach are, retains the healing spell. Not a huge niche really compared to the other caster summons, but I'm trying not to gamify this too much, it's okay for it just to be a variant mechanically IMO


**Storm Atronach (38)**
- Overall the strongest caster summon, lots of health and a terrifying melee attack
- Lowered AOE from 10ft from 5ft, to make them less likely to hit allies/player, but kept cost the same
	- A new unique spell ID, left core shock bloom as is, `dwemcod_summon_shockbloom`
- Buffed the lightning shield slightly
	- A new unique spell ID, left core shock shield as is, `dwemcod_summon_shock_shield`

**Winged twilight (52)**
- Had no spells or abilities in core, moved to a mysticism/absorption themed anti-magic summon
- Given:
- `dwemcod_summon_spellabsorb`
	- Passive ability, absorb spell 30pts
- `dwemcod_summon_greater_absorb`
	- Spell, absorb health 1-25pts for 5s on target 5ft AOE (40 magicka)


**Golden saint (55)**
- The ultimate summon
- Strength increased from 50 to 100, making it do 150% damage
	- The UESP claims that it should be doing weapon + base damage (base damage average of 40), but testing and the code show it is doing just weapon damage in this version of open morrowind
	- Regardless of if it should, it certainly needed a damage boost in this version, as the average weapon damage was only about 30, making it no better at damage than the storm atronach, and not that much ahead the Dremora
	- Now it does an average of 45 a swing, across all it's possible weapons
- Lightning shield (3pts for 30s) replaced with a new variant, 10pts for 30s
- Otherwise left as is, with dispel and the same weapon/shield table


**Special, not balanced/changed, including no soul changes for the time being**
Bone wolf (BM)
Grizzly bear (BM)
Wolf (BM)
Sphere centurion (Morrowind)
Verminous Fabricant (TR)

## 2.23, Willpower attribute change (buff)

Overall I felt that willpower was a relatively weak stat.

A 100 willpower character gets a +20 to their casting success rate, which is equal to +10 skill. When you account for the fact that everyone starts at 30 willpower at least, this is already a +6 to casting success. The end result is that for levelling your willpower from 30 to 100, all you get mechanically is a +14 to your casting success. Not bad, but really not worth that much investment (given that in practise you rarely need to cast spells beyond a certain cost threshold).

Other than that, willpower also gave a slight resistance to paralysis and silence, and increased your fatigue.

So two changes have been made,
1. Willpower now contributes 1.5x as much to casting success (before factoring in the fatigue modifier, which is the same order of operations as in the base game)
	- So now 100 willpower is equal to +15 to your casting skill in all schools, not a world better, but a nudge in the right direction
2. Your willpower points above 50 now give you a small amount of passive resist magicka. This doesn't appear as a buff, it is just calculated behind the scenes. Every 10 points above 50 adds 2% resist magicka, with no cap.
	- So 100 willpower now also gives +10% passive resist magicka
	- This stacks with normal resist magicka effects, but still obeys the hard cap to resist magicka that was added earlier (of 60% total)

## 2.24, Adjusted previous change to spellcasting XP gain

As per ESP changelog,

Base conjuration and destruction XP reverted back to 2.0 from 3.0.

The change to 3.0 was originally done during testing where it was found even going to 2.0 was too slow, and the two skills didn't level much due to most normal usage being single casts of very high cost spells.

With the casting XP revision, this is no longer needed as preliminary testing shows the schools do gain XP well now (due to them tending to prefer higher costed spells naturally in combat).

## 2.25, Hand to Hand changes

- Note that hand to hand accuracy obeys the same modified logic that weapons do now, which is (skill x 0.7) +20. No changes here in that regard, but a reminder that the previous changes capture hand to hand too.
	- Unlike some weapon types, hand to hand has no special accuracy modifiers beyond the above.
- Health damage done increased by adjusting the GMST `fHandtoHandHealthPer`, up to 0.4, from 0.1
	- This GMST is the amount of health damage you do with hand to hand, as a % of the fatigue damage. So in the base game at 0.1 you do 10%, with this change you do 40%. It might be a little strong, but it really needed some kind of buff, for context:
	- At 100 skill you do 50 fatigue damage, hence with the GMST of 0.1 you do 5 damage per swing, before armour, at 100 skill. After armour that can be reduced down to as little as 1.25 per swing
	- With the changes, you now do 20 damage per swing at 100 skill, more in line with top end daggers and some other short blades
- Damage done has been increased at the low end, reaches parity with normal behaviour at about 40 skill, and scales to the same final value at 100 skill
	- Beyond 100 skill you now gain slightly less damage per skill level
	- The formula change was from damage = skill (before the attack strength multiplier), to: 10 + (skill x 0.9)
	- This just makes low levels slightly less pointless, they're still not good, but it is slightly more reasonable to go punching mudcrabs now
- Fatigue damage done now scales with difficulty, but less aggressively than with melee, due to fatigue damage not being resisted by armour, and due to the player having to overcome natural creature/NPC fatigue regeneration when attacking
	- See table at the end of this section for values
- The open morrowind setting for scaling your hand to hand damage with strength was revised to behave like strength does for weapon attacks in the base game.
	- 50 strength, no modifier
	- 100 strength, +50% damage
	- 1 strength, -49% damage
- As such it is recommended that this setting is toggled on by default in the server config, although werewolves haven't been balance tested (and they are an edge case), so I recommend setting 2 (normal hand to hand scales with strength, but not werewolves)
	- Also note that unlike all the other changes here, this one does affect NPCs, so toggling that setting on will still affect NPC hand to hand damage (as in core open morrowind)

| Tier | % Melee/<br>on-hit dealt | % Melee <br>taken | % Magic/ench<br>damage dealt | % Magic<br>taken | Fatigue dealt | Fatigue taken |
| ---- | ------------------------ | ----------------- | ---------------------------- | ---------------- | ------------- | ------------- |
| 1    | 100                      | 100               | 100                          | 100              | 100           | 100           |
| 2    | 75                       | 150               | 85                           | 125              | 85            | 125           |
| 3    | 50                       | 200               | 70                           | 150              | 70            | 150           |
| 4    | 30                       | 300               | 50                           | 200              | 50            | 200           |
| 5    | 20                       | 400               | 33                           | 250              | 33            | 250           |
| 6    | 15                       | 500               | 25                           | 300              | 25            | 300           |

**Footnote on unusual core engine behaviour:**
I noticed during testing that NPCs did a much bigger range of fatigue damage than expected, up to 2x the expected values at a given skill level.

This is definitely base game/engine behaviour (for open morrowind at least), as it was the case before I began making any changes.

It's not a huge issue for me, so not something I decided to fix - especially as it is 'core' behaviour, and whilst I didn't find the reason, it appears to be something to do with how NPCs generate a value for `attackStrength`, it looks like they don't quite follow the same rules the player does. Maybe it's randomising a value between 0 and 2? I can't see why, but definitely the core game behaviour I observed is NPCs doing up to 2x damage with hand to hand fatigue than expected (but no more).


**In future**
 - I wanted to make hand to hand do a mix of health and fatigue damage against standing targets, but that was put on hold pending server packet work

## 2.26, Pickpocketing overhaul

- The player no longer has to pass a detection check when closing the pickpocketing window
	- This was happening even if you stole nothing, and just exited the window, now you auto-pass the check (impossible to fail, the code just returns a success for that check every time now). This also stops the core game bug/balance issue where the player has to pass effectively two difficulty checks to steal something
- Item value is now handled in the code as 1x the items value in gold, providing the GMST is 1.0, this is a change from core behaviour where it was item value x10, x GMST (which was 0.3 in the core game)
- Pickpocketing difficulty logic completely overhauled
	- You now have a 50% chance to steal items equal to your pickpocketing term x5
		- This is a base 50% chance, before the fatigue modifier applies, so at full fatigue (fatigue mod x1.25), you actually have a 62.5% chance to pickpocket the values below
	- Your pickpocketing term is your sneak skill + (agility x 0.2) + (luck x 0.1), so it ranges from 10-130 in practise
	- When you look in an NPCs inventory, you will now only see items which you have a base 50% chance, or higher, to pickpocket
	- There is no longer a victim term, meaning that the logic no longer takes into account NPC agility, luck, or sneak
		- This was to simplify the logic for the first implementation, but I don't feel the game has lost anything in having this simplified away
	- For every skill/term value which you exceed, or are under, the equivalent value you can pickpocket at a base 50% success chance, you gain or lose 1.5% success chance
		- For example, if your pickpocket term was 50, you have a 50% chance to take a 250g item
		- When trying to take a 50g item, your are 200g 'over' the 50% threshold, to the check becomes proportionally easier, and you have a 90% chance to succeed
		- The reverse is also true, although due to the change in menu behaviour this will rarely matter
			- So if you try to steal a 250g item with only a term of 10 (50% chance to steal 50g), you would only have a 10% chance to succeed
			- The reason this rarely matters is now you would not be able to see that 250g item until you had a 50% base chance to succeed. However this code was added to account for the player buffing their skill/attributes, opening an NPCs inventory, and still having it open and trying to steal by time the buffs have worn off
	- Since the above is a base 50% chance to succeed, at full fatigue you will always have a 62.5% chance to succeed pickpocketing something you can see
	- This means with the +1.5% success chance per skill/term level you are above, to reach 100% success rate (at full fatigue) you need to be 25 skill/term levels above the 50% success rate threshold

Final values for getting caught:

| Skill | Skill + attribute term | Gold value you have a 50% chance to succeed at, at a 1x fatigue modifier | Gold value you have a 100% chance to succeed at, at a 1.25x fatigue modifier |
| ----- | ---------------------- | ------------------------------------------------------------------------ | ---------------------------------------------------------------------------- |
| 10    | 17                     | 85                                                                       | 0                                                                            |
| 20    | 28                     | 140                                                                      | 15                                                                           |
| 30    | 39                     | 195                                                                      | 70                                                                           |
| 40    | 50                     | 250                                                                      | 125                                                                          |
| 50    | 62                     | 310                                                                      | 185                                                                          |
| 60    | 76                     | 380                                                                      | 255                                                                          |
| 70    | 90                     | 450                                                                      | 325                                                                          |
| 80    | 104                    | 520                                                                      | 395                                                                          |
| 90    | 118                    | 590                                                                      | 465                                                                          |
| 100   | 130                    | 650                                                                      | 525                                                                          |
- The skill and attribute term is making assumptions about the players attributes, but will broadly be correct if the player is trying to focus on the relevant stats

All of this still relies on you not being seen however!

# 3, Compiling Changelog
All files changed:
`openmw\enchanting.cpp`
`openmw\spellutil.cpp`
`npcstats.cpp`
`trainingwindow.cpp`
`spellcasting.cpp` - headers added
`inventorystore.cpp`
`repair.cpp`
`npc.cpp` - header additions
`combat.cpp` - header additions
`movementsolver.hpp` - header additions
`difficultyscaling.hpp`
`difficultyscaling.cpp`

## 3.1, Enchanting
`openmw\enchanting.cpp`
`openmw\spellutil.cpp`

- Changed the enchanting capacity of items by altering the equation to generate on a curve by introducing a SQRT to the equation. No other changes involved, all relevant code is within the `int Enchanting::getMaxEnchantValue() const` function.
	- Enchanting.cpp now requires `cmath` in the header to use the SQRT function.
		- Relies on `cmath`
	- There is a check to ensure that that SQRT equation will be skipped and instead 0 is returned, if the game detects an item has (somehow) got a capacity of -5 or less. The use of the SQRT would return unexpected behaviour in these situations otherwise. Should never be a problem if the game is being modded as intended (with values of 0 and above).
- Added a 0.25x multiplier to on-hit item charge costs before they go into the on-use equation in `spellutil.cpp`, this function is hosted in `enchanting.cpp` as `int Enchanting::getEffectiveCastCost() const`
	- Interaction with `spellutil.cpp`
- Added various enchantment point cost modifiers to spell effects and spell schools, to allow independent balancing of spell effects from player spellmaking and alchemy
	- Majority (all?) hosted in `float Enchanting::getEnchantPoints(bool precise) const`
	- `const auto magicEffect = MWBase::Environment::get().getWorld()->getStore().get<ESM::MagicEffect>().find(effect.mEffectID);` required to function
	- If check for cast when strikes, which doubles the enchantment point cost. Done for balancing reasons to position on-hit enchantments as having many more uses than in core, with lower potential damage. With other balancing implemented this caps enchantable damage at about 10-30 or 15-35, which rivals artefact damage output (such as Goldbrand, which does 10-30 fire damage per hit)
	- If check for destruction and restoration schools, doubling their enchantment point cost for all items. Done for balancing reasons, to limit the players ability to spam healing or on touch damaging items with otherwise can trivialise the game
		- Gets spell effect school via `int school = magicEffect->mData.mSchool;` and then checks for `if (school == 2 || school == 5)` which are destruction and restoration respectively. If either are found it doubles the point cost. This stacks with all other multipliers such as the cost increase for on-hit weapons
	- If checks for specific spell effects implemented in the same way, in the format ` if (effenumid == 57 || effenumid == 74...` See mechanics changelog for which spells were adjusted in this way
		- `int effenumid = effect.mEffectID;` in code block required to function
		- These modifiers stack with the school and on-hit modifiers above. All modifiers stack unless otherwise noted. All implemented for balancing reasons.
- Enchanting difficulty (success chance) modified for each enchanting type, with the aim of broadly restricting enchantments beyond 20 points by making them disproportionately difficult
	- See the entire `int Enchanting::getEnchantChance() const`. Extensively modified success rates by making difficulty increase in intervals at around 20 and beyond, and by making success rates higher when making low end enchantments (below 5 points)
	- Otherwise however the actual core success rate equation is unchanged, it is still the one listed for open morrowind. All of the difficulty adjustments made are post-hoc, to the success rate generated by that equation
	- `const float enchantpointsforpenalty = getEnchantPoints();` defined in block for point value checks
	- `fEnchantmentConstantChanceMult` no longer used at all
	- Code block on lines 547-549 is required to get the base skill of the players enchanting (ignoring buffs or drain/damage effects), which is used to determine constant effect success rate
	- `"mechanicsmanagerimp.hpp"`, `"../mwclass/creature.hpp"`, and `"../mwworld/player.hpp"` now required in header to get the base skill value (actually I don't think they all are, I got lazy and pasted in all three instead of checking)
	- Constant effects now require a base (unmodified) enchanting skill of 75 to be made, any skill value below this has a 0% success chance. At 75 you can make up to 30 points of CE with guaranteed success rate, and above 30 the chance drops to 0% again. The amount you can make increased in 15 point increments for every 5 skill levels, reaching 90 CE points at 95 skill. At 100 skill all constant effect enchantments succeed regardless of point cost.
	- On-use and on-strike effects are easier to make below 5 points, and become significantly harder beyond 20 and 25 points. 30 is a practical hard cap if you stay within the 200 max skill level allowed by the tes3mp server setup. You can get higher otherwise with buffs, but it was balanced around the assumption you won't.
	- Cast-once (scrolls) use the same logic, but with an additional flat +25% success rate to position them as low level enchanting items (and to provide a practical way to train the skill when starting at very low skill levels)
- Ammunition will now enchant in batches of 20 if the Openmw setting is turned on (set it to `0.5` just in case, but the behaviour should now be value independent as long as it is turned on at all, i.e. greater than 0 in the config file)
	- Within `int Enchanting::getEnchantItemsCount() const`;
		- `count = std::min(itemsInInventoryCount, std::max(1, 20));` replaces the previous check for the enchantment cost and the multiplier settings, fixing the number it will attempt at up to 20 if you are holding them
	- Within `float Enchanting::getTypeMultiplier() const`
		- Fixed to `return 0.05f;`, reducing difficulty by x20
- Enchanting costs modified within `int Enchanting::getEnchantPrice() const` as described in the mechanics section. Very different behaviour to core.

---
	`TES3MP\apps\openmw\spellutil.cpp`
- Changed the on-use cost of enchanted items to involve a logarithm. Intentionally designed the equation to cap cost reduction to 1/3 (more for on-hit effects), and for there to be no penalty at 0 skill.
	- Achieved by making changes to the `int getEffectiveEnchantmentCastCost` function
	- An if check first caps skill player skill at 200, and floors it at 1, to stop unexpected behaviour with the log equation
	- Then a log equation performs the new cost reduction
	- This relies on the `std::log` function so `cmath` is now called in the header
		- Relies on `cmath`
	- Then a flat +1, and a flat +33% original cost are added to this value, providing absolute floors to the cost reduction
	- The value is returned as INT, so some rounding will occur
	- For gameplay reasons, on-hit effects are further reduced to about 25% of the value generated this way. This is handled in the `int Enchanting::getEffectiveCastCost() const` function in the `enchanting.cpp` file, which applies a 0.25 multiplier to the base cost value before it goes into the above equation.
		- Interaction with `enchanting.cpp`

---


## 3.1a, Fixing the enchanted item on-use bug I introduced

`spellcasting.cpp`

 introduced a bug - the way I removed the "out of charge" message for on-hit effects resulted in it being removed from everything, but more than removing the message I appear to have removed the entire "stop" bit of the code - so as a result the game let's you cast enchanted items with 0 charge but they do nothing - however the entire animation plays, a bolt is generated, etc. So that's a problem that needs fixing, they need to register as out of charge still, go back and fix that

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



## 3.2, XP gain
`npcstats.cpp`
- [ ] XP gain changes
- Changed the `useSkill` function to add a non-linear curve insertion of code block. Simply checks for players base skill level and reduces the XP gained by the multipliers shown in the mechanics changelog depending on level
- Also changed the `getSkillProgressRequirement` function in `npcstats.cpp` to have a floor value of 30, so skills below 30 will still require 30xp to advance. Done by adding a `std:: max 30` pre-check function to the existing calculation

## 3.3, Training costs
`trainingwindow.cpp`
- [ ] Training costs
- `trainingwindow.cpp` modified in two locations as in section 1.1 work area 2, using the values on google sheets, in such a way as to produce a non-linear increase in training costs for all skills whilst respecting the GMST. So the GMST setting of 10 can be doubled to 20, for example, and the non-linear price increases will also double uniformly.
- Note that two edits were required (with duplicate code) as this file calculates the cost mechanically and the cost in the UI (training window) independently

## 3.4, MR cap
`spellcasting.cpp`
`inventorystore.cpp`

 - [ ] Magic resistance now has no mechanical effect beyond 60% (after accounting for weakness effects which negate it 1:1)
 - Added a clause each to each of `spellcasting.cpp` and `inventorystore.cpp`. It was necessary for it to be formatted differently in each location, but the function is the same
 - Had to manually define the list of effects which were to have their resistances capped
	 - The reason was because I wanted not to cap the magnitude of resist magicka effects to avoid complicated changes to the UI and spell behaviour
 - TGM is unaffected, it still gets full immunity due to the location this code change was positioned
 - In `spellcasting.cpp` the `inflict` function was modified with a conditional check that caps magic resist for a pre-defined list of effects
 - In `inventorystore.cpp` the `updateMagicEffects` function was modified with the same logic but formatted slightly differently as this file required
 - The two changes were necessary as `inflict` in `spellcasting.cpp` covers all possible sources of negative effects except for constant effect enchantments, which are handled via the `inventorystore.cpp` code

## 3.5, Miscellaneous changes and fixes
`npcstats.cpp`
`repair.cpp`

- [ ] Skill books do not work at skill 95 and above anymore
- Added a single conditional clause that returns the function if the skill-up gain is from a book and the base skill is 95 or above. The relevant function is `increaseSkill` in `npcstats.cpp` under the `if (readBook)` check

- [ ] Reduced the armorer sounds by changing the `repair` function within `repair.cpp` to play the sound at 0.5 instead of 1.0. This has to be done twice, as the tes3mp also sends a pakcet with the same information for others to hear. Also whilst the original values (from openmw) are written as "1.0" (which makes them doubles), I had to manually define them as floats when changing this otherwise a type conversion error was called. No effect on gameplay or code behaviour, just worth noting as an implicit conversion that has been made explicit
## 3.6, Melee changes
`npc.cpp`
`combat.cpp`

**Accuracy**
- [ ] The change to base hit chance calculations are implemented in the function `getHitChance` within `combat.cpp`. Something like (skill x 0.7) + 20, instead of (skill x1). Agility, luck, fatigue and enemy evasion are all handled normally
- [ ] 2h accuracy penalties are implemented in the same function `hit` within `npc.cpp`

**Damage**
- [ ] The change to how base damage is calculated (using skill as well as an attribute, with the same sum benefit of +50%) is implemented in the function `adjustWeaponDamage` within `combat.cpp`

**Weapon type benefits**
- [ ] Weapon type accuracy variations are implemented in `npc.cpp` within the function `hit`
- [ ] The changes to what contributes to damage for each weapon are implemented in the function `adjustWeaponDamage` within `combat.cpp`

## 3.7, Ranged changes
`combat.cpp`
**Accuracy**
- [ ] Ranged attacks follow the same accuracy change logic as implemented for melee, as determined in the `getHitChance` function within `combat.cpp`
	- In addition within the `projectileHit` function in `combat.cpp` ranged attacks are there given a flat +20 to hit, for balancing reasons (they are intended to be more accurate to make up for missed shots due to poor aim)

**Damage**
- [ ] Bows and crossbows have their damage modified to function similar to melee, increasing with skill and attribute, but they use agility as their damage attribute instead of strength. This is done in the `adjustWeaponDamage` function within `combat.cpp`
- [ ] Throwing scales differently, and uses strength and skill to determine damage. These are weighted equally as with melee, but the damage scaling for throwing progresses linearly from 0-100 to a higher cap of 200% weapon damage instead of 150% at 100 strength and 100 skill. Given that throwing weapons do 2x the stated damage, this means at max strength and skill throwing weapons do 4x the stated damage. This is also done in the `adjustWeaponDamage` function within `combat.cpp`

**Ammunition Recovery**
- [ ] Both enchanted and non-enchanted ammo recovery are handled via the `projectileHit` function within `combat.cpp` which has been modified
	- The function now checks player skill and uses it to multiply the GMST ammo recovery value. For non-enchanted the recovery rate cannot be less than 1x GMST, at from 25 to 100 it scales linearly up to 4x GMST (every 25 skill is another 1x GMST, it increments at each skill level as this is processed as a float)
	- The same function also allows for enchanted ammo recovery, but this only becomes possible at 50 skill and above. You start at 0 recovery rate at 50 skill, and each level beyond 50 adds 1/25th of the GMST recovery rate, so every 25 levels adds another 1x GMST up to 2x GMST total at 100 skill. This function hard caps the players skill it checks at 100 before processing, so there is no way to achieve beyond 2x GMST recovery rate.


## 3.8, Acrobatics and climbing
`movementsolver.hpp`
Headers added (to call base player skill)

The `static bool isWalkableSlope` logic within `movementsolver.hpp` was updated to check if it is the player (only the player is affected by this change), and to get the players base acrobatics skill and scale the climbing angle allowed based on skill as described in mechanics (2.8).

The climbing angle is hard capped at 89° to minimise the risk of unusual behaviour (this will all potentially interact with stepping upwards on stairs, and hitting steep surfaces when walking).

 - [ ] This change adjust the criteria for the engine to determine the boolean `iswalkableslope` and restricts it to the player
 - [ ] There is not effect on the default value (47°) at 30 skill or below, and no benefit beyond 92 base skill (the angle you can climb to is hard capped to 89° for compatibility reasons)
 - [ ] Increasing the angle to 90° (or beyond) does not allow true wall climbing, due to separate logic checks in the openmw engine that exist  to prevent wall collision/sticking
	 - [ ] I did not attempt to resolve this, as this would require a more extensive rework of the physics engine which would further risk compatibility with new content.
	 - [ ] In short, whilst wall climbing is technically possible with some changes it meant (in the version I trialled) that you "stuck" to every wall you touched, which meant your speed slowed down to a crawl as you attempted to being moving vertically up it at greatly reduced speed, which was a huge problem in many urban areas and most interiors
- [ ] The `sMaxSlope` variable is seemingly hard coded and not accessible to the compiler (47°) but it can be worked around in the way I have done without issues.
- [ ] There remain risks of floor detection failing when climbing, or clipping through ceilings, this will be investigated as playtesting continues.
- [ ] Several functions within `movementsolver.cpp` call the Boolean `iswalkableslope`, these have been checked for unintended knock-on effects, and of the functions within the `cpp` file there are only two are of potential concern (although no issues have been seen yet during playtesting)
	- `osg::Vec3f MovementSolver::traceDown` beginning on line 80, but the bool starts getting called around line 106
		- I have no idea what the ray tracing logic does here, but it seems only to be involved in whether you can walk or not on a slope (so probably the actual post-hoc function that is implementing this change)
		- But since it involves ray tracing and ground offset there could be some object detection/collision issues that result in clipping(?)
	- Also called twice between lines 367 to 392, to determine actor collision and determining if on slope. Again no idea what the impact of this is, but playtesting has not yet found an issue
	- Other areas of code checked and certainly of no concern for unintended behaviour, these two I couldn't pick apart in the time I spent on this (I am way out of my depth with the physics engine stuff)


## 3.9, Difficulty Tiers and new difficulty scaling
Modified files:
`difficultyscaling.hpp`
`difficultyscaling.cpp`
`spellcasting.cpp` - headers added

[Note that in addition to these changes, further functions were added in V0.70, see 3.25, hand to hand, which also affects the difficulty scaling files.]
### 3.9.1, Tier function
In `difficultyscaling.hpp`
- `int difficultyTier();` function defined

In `difficultyscaling.cpp`:
- The function `int difficultyTier()` has been added 
	- This gets the difficulty and converts it to a tier
	- It gets the server config file difficulty setting (or player specific if overridden by server admins in tes3mp, the player specific values have not been play tested - as with base tes3mp it is not looking at the openmw difficulty setting)

The actual server config to difficulty tier conversion table as shown below:

| Server value | Tier | Comments                          | Tier name [1] |
| ------------ | ---- | --------------------------------- | ------------- |
| Less than 0  | 1    | 1 = normal, unchanged, difficulty | Apprentice    |
| 1-50         | 2    |                                   | Journeyman    |
| 51-100       | 3    |                                   | Master        |
| 101-150      | 4    |                                   | Grandmaster   |
| 151-200      | 5    |                                   | Agent         |
| 201+         | 6    | 6 = absurdly difficult            | Nerevarine    |
[1] Note: These names are not implemented anywhere in game or code, they are just the documentation names for these tiers

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

### 3.9.2, Moving melee damage to tiers

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


### 3.9.3, Scaling on-strike and adding enchantment type detection

Via the following changes, on-strike enchantments specifically are tied to their own damage scaling table, which also operates off of difficulty tier - for now it is identical to melee damage dealt, but it is coded separately for ease of balancing

Tested and working for all effects, all sources of effect and also confirmed that absorb health correctly halves the magnitude of damage done and haling received (it should do automatically, and it did, just checking)

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


[Base function without enchantment type]
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

        /// dwemer coda gets the enchantment type
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


### 3.9.4, Castonce enchantment damage scaling

I scaled down the damage less aggressively than with melee, as unlike melee you can run out of mana/charge when casting, so it is a more premium resource

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

### 3.9.5, On-use enchantment damage scaling

Done via updating the start of the above function in 4.2, to allow for either `castonce` or `whenused`. No other changes needed, working, they both use the same damage scaling function as a result (intended)

```
if ((mEnchantmentType == ESM::Enchantment::CastOnce || mEnchantmentType == ESM::Enchantment::WhenUsed)
```

### 3.9.6, Spell damage dealt

One change was left unfinished as it is not yet required, but will be:
- The actual scaling function that processes the spell magnitude in `difficultyscaling.cpp` is the same one that does enchanted items, etc, as for now I decided the scaling for each could match, but in the next revision it would be better to separate them so that they can be scaled separately 

**Summary**
`spellcasting.hpp`
[1] `spellcasting.hpp` updated with new `enum class SourceType`, for use in tracking spell effect source/origin
[2] `spellcasting.hpp` also updated to initialise `SourceType` via the line
`SourceType mSourceType{ SourceType::None };` 
which was inserted at the bottom of the public space starting with
`bool mStack{false};`
[3] at some point in the `spellcasting.hpp` file I think I changed the order things are declared in that same public namespace, from what was default, I remember this was not necessary and was only to avoid potential compiling errors on other systems - in the end I can't see that I kept this change, but just keep it in mind in case there is an apparent different in line order in my version compared to the original, it was for this reason if so
`spellcasting.cpp`
[4] See the working out section below, it became a little involved and whilst it is all documented i need to summarise it for this section

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
        SourceType mSourceType{ SourceType::None }; // dwemercoda addition
```
so just the last line was added

There were also some changed the order that lines were in that public space, I can't remember if I kept all that and whether it really mattered, but just be aware there may be differences in the line order in my version compared to original, and in theory it could matter for some vague compiling error reason I failed to document at the time (I don't think it does)

With all that done it was then used in `spellcastin.cpp` in the following way,
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

**The bug fixes**
Two issues with the above,
1. `bool CastSpell::cast(const MWWorld::Ptr &item, bool launchProjectile)` actually handles both items and spells saved in the game BSA/ESP files (so ever spell you can learn which you do not make yourself), so they would otherwise bypass the cast as a spell function and be left with the enchanted item tag

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

### 3.9.7, Magic damage taken

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

### 3.9.8, Accounting for reflected damage

By default all of the changes so far did not account for reflected effects (although some of the code above this may have been documented after reflect corrections were made to it).

The consequence of this in game-play was that:
- Magic effects being reflected onto monsters were not being properly stepped down by tier, and were applying at a flat 1x damage. This would have allowed by-passing the difficulty tier magic damage stepdown if left unchanged
- The player was also taking a flat 1x damage regardless of difficulty tier

I decided not to fix the second point (damage reflected onto the player), and the first point was fixed with the below changes...

**Damage reflected onto the player**
I did not fix this on purpose for balance reasons, but it could be in the same way as the inverse problem was fixed below.

The reasoning was that already in the base game, getting a spell reflected onto you is potentially lethal if you are not prepared for it - spellcasters will typically have lower health (if they are not min-maxing their attributes as they level), and are less likely to pick high endurance starts if they are roleplaying.

That and the base game has an unusual health scaling curve (which I may be going to fix later) which in effect means that until mid to high levels, and especially without good endurance, the player has much less health than monsters and relies more on healing, armour and positioning - which is great until you cast a 50 point shock spell and it's reflected onto your 80 health pool at level 10 (if you had 40 endurance from level 1 to 10). 
In other words the base game requires player spell damage output be disproportionally high compared to their own health pools due to the health it gives to monsters beyond the early game.

So for those reasons I intentionally did not correct player damage taken for now, for balance reasons, and it remains a flat 1x when reflected regardless of difficulty tier.

The reason it behaves this way is because of this bit of the if logic for player magic damage taken...

```
target == player && mCaster != player
```

It checks the target is the player (which it is when reflected) and the `mCaster` (essentially the original caster for the purpose of the current, base, overload implementation) is not the player - however in the case of a monster reflection, the `mCaster` is still the player (although the game does update the `caster` variable, which is tracked separately, to the monster as the new local `caster` within the overload loop)

**Damage reflected on monsters**
This I did fix, as without these fixes it allowed the player to cheese all high difficulty settings but just reflecting monster spells back to them at 1x damage (for the same if statement logic reasons as above), by-passing the intended player magic damage done step-down of up to x0.15

The monster magic damage taken was checking (via the three separate functions that track spells, on-hit spells, and on-use together with cast-once sources),
`&& target != player && mCaster == player`
So it checks the target is not the player via `target != player` (which is fine),
but it was also originally checking,
`mCaster == player`,
so it was also requiring the original source of the spell effect to be the player, hence it was implicitly excluding all monster originating effects that were being reflected onto monsters - thus escaping out out of the effect magnitude reduction that should otherwise have applied

the fix was to change it to
`target != player && caster == player`
so that instead it looks for effects locally originating from the player, regardless of the original source, and so now it includes all reflected effects and properly steps them down on high difficulties


## 3.9a Elemental shield damage scaling bug

Elemental shield was, up until V0.40, still operating off of the base game damage scaling function, and so was being scaled as if it were melee damage.

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


## 3.10, Equipment derived armour ratings

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


## 3.11, Unarmoured derived armour ratings
`npc.cpp`

Within `npc.cpp` the function `getArmorRating` calculates player armour rating locally

The function has a fork in it's logic for if the armour class is being calculated for the player. The below logic fork was inserted into the original function, immediately after it calculates the unarmoured score normally via `ratings[i] = (fUnarmoredBase1 * unarmoredSkill) * (fUnarmoredBase2 * unarmoredSkill);.`

It was done this way so that for all entities the engine still generates an original armour score, and then the if pointer is player fork simply overwrites that score with the new one.

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
	                
	                /// this x10 mod goes in just so that the GMST holds
                    playerunarmoured *= 10.0f;

                    playerunarmoured *= fUnarmoredBase1;

                    ratings[i] = playerunarmoured;
                }
            }
```


## 3.12, Creature armour ratings

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

## 3.13, Armorer

### 3.13.1, Equipment degradation rates
Changes made to
`npc.cpp`
`combat.cpp`
`difficultyscaling.cpp`
`difficultyscaling.hpp`
#### 3.13.1.1, Shields
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


#### 3.13.1.2, Armour
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

#### 3.13.1.3, Weapons
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

#### 3.13.1.4, Accounting for difficulty

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


### 3.13.2, Your armorer repair success rate now depends on item value
Header additions to `repair.cpp` and `merchantrepair.cpp`
`repair.cpp`
`merchantrepair.cpp`
#### 3.13.2.1, General changes
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


#### 3.13.2.2, Assigning item tiers

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

#### 3.13.2.3, Success rate equations
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
            if (x < 14.0f)
            {
                x = 14.0f;
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
        if (x < 10.0f)
        {
            x = 10.0f;
        }
    }

    if (tier == 5)
    {
        x = ((0.0114f * basepercent * basepercent) + (0.23f * basepercent) - 27.64f);
        if (x < 7.0f)
        {
            x = 7.0f;
        }
    }

    if (tier == 6)
    {
        x = ((0.0072f * basepercent * basepercent) + (0.51f * basepercent) - 41.4f);
        if (x < 5.0f)
        {
            x = 5.0f;
        }
    }

    if (tier == 7)
    {
        x = ((0.014f * basepercent * basepercent) - (0.552f * basepercent) - 14.63f);
        if (x < 5.0f)
        {
            x = 5.0f;
        }
    }
```

### 3.13.3, Armorer's tools now modify success rate
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
        qualitymod *= 1.50f;
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



### 3.13.4, Armour repair costs
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

            int x = static_cast<int>((maxDurability - durability) / r);
            x = static_cast<int>(fRepairMult * x * 0.5f);
            x = std::max(1, x);

            int price = MWBase::Environment::get().getMechanicsManager()->getBarterOffer(mActor, x, true);
```

The difference from the original code is that r is no longer set to 1 via `std::max`

Since the line for r was originally

```
float r = static_cast<float>(std::max(1, static_cast<int>(maxDurability / p)));
```

The effect was that r would never be less than 1, due to the `std::max` operation, and only r values less than 1 increase the price past 1gp per item health, since the cost is later calculated as health restored / r.

This preserves the base game functionality of item's costing less than 1gp per item health to repair,

By making this change, items now cost a % of their value equal to the % of their health being restored.

In addition the line
`x = static_cast<int>(fRepairMult * x * 0.5f);`
had the 0.5f multiplier added, so that final cost to repair an item fully is 50% of the item's full value

This was done to make the prices more reasonable for testing, and for the first version, but the player can adjust `fRepairMult` at an ESP level, so further in game changes can be made on the fly, to taste.



## 3.14, Athletics derived swim speed
`npc.cpp`

This change boosts the contribution to swim speed (as a % of base run speed) by the player's athletics from 1% a level to 3% a level. Resulting in the player going from 50-80% swim speed, vs 50-60% in the base game, when they go from 1-100 athletics.

This is restricted to the player only via an if player is ptr check, and replacing a hardcoded value with a local variable in the function.

There is a hard cap to how much athletics can contribute to swim speed of level 500 athletics (which works out to +150% run to swim speed, on top of the 50% you get at skill 1. For a total of 200% base swim speed at 500 skill).

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

was updated as follows

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
            if (athleticsholder > 500.0f)
            {
                athleticsholder = 500.0f;
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
- Toggles variable value for player and non-players (which are preserved with base game behaviour)

## 3.16, Mercantile
`mechanicsmanagerimp.cpp`
`tradewindow.cpp`
`trading.cpp`

To facilitate the changes listed in 2.16.2, the following changes were made at an engine level

### 3.16.2.1, Mercantile disposition has reduced effect on bartering
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


### 3.16.2.2, Mercantile disposition has reduced effect on haggling

Not actually a compiling level change, but listed here as it complements the engine level change made above. At an ESP level the GMST `fDispositionMod` governs the extent to which disposition affects haggling, it is 1.0 by default and was adjusted to 0.25 so that 4 points of disposition above or below 50 add or remove 1 effective mercantile level. Now as with bartering, the maximum benefit you can get from 100 disposition is +12.5 effective mercantile levels.


### 3.16.2.3, Adjustments to min and max buy/sell rates
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

### 3.16.2.4, Setting a hard limit on haggling of 10%
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

This is a very aggressive and crude fix, and will likely be replaced with something more nuanced in a later version, but for now it serves it's purpose without introduces any bugs.

### 3.16.2.5, XP gain overhaul

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
8. Calculate the amount of XP you will be awarded, in increments of 0.3xp, based on the amount of barter value you sold. In the version for V0.50 this is 50gp per 0.3xp, or about 166.7gp per XP
9. Apply a potential step down multiplier to that XP amount used the ratio calculated in step 7. This means that if you intentionally undersell items to get rid of them, you will get proportionally less XP (as that is not something that a good merchant would do!)
10. Award XP, using the value calculated in step 9 as the extra factor

The end result is that
- You get XP based on the value of items you sell
- You get less XP if you intentionally undersell
- Items received in kind are accounted for, and count towards you receiving full payment
- Buying things intentionally does not give XP


## 3.17, NPC spellcasting locked to base game spell effect costs

`spellutil.cpp`
`spellutil.hpp`
`autocalcspell.cpp`
`autocalcspell.hpp`
`spellpriority.cpp`

An exhaustive search was done in the engine for all direct and indirect references to spell effect costs made by NPCs. Three areas were found and adjusted so that NPCs used new hard-coded base game spell effect cost values.

### 3.17.1, Locking `calcSpellBaseSuccessChance()`
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

### 3.17.2, New hardcoded function, `getBaseGameEffectCost`
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


### 3.17.3, Locking `calcWeakestSchool()`
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

### 3.17.4, Locking `calcEffectCost()`
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

## 3.18 Alchemy overhaul
`alchemy.cpp`
`spellcasting.cpp`

### 3.18.1, Potion weight change

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


### 3.18.2, Potions no longer stack
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

changed to
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

The line
```
mStack = false;
```

means that the same potion will no longer stack.

So now if you drink 10 of the same healing potion using hotkeys, it does nothing except refresh the potion.
You can still drink 10 different potions to stack the effects, if you really want.


### 3.18.3, Potion making success rate
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
    successChance = std::max(successChance, 30.0f);

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

It's not perfect, but I went with a straight line instead of another polynomial to save time, and to make it more understandable.

This function can be summarised as,
- Average item value multiplied by 0.158, + 8.4

### 3.18.4, Modifying alchemy factor based on ingredient quality
`alchemy.cpp`

This system gets the average value of all ingredients used in a potion, and increases or decreases the players alchemy factor based on what it gets

**Get the average gold value of the ingredients being used**
```
    //dwemer coda, ingredient value logic
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

    //dwemer coda end

```

**Use the average value to modify the alchemy factor**
```
    // general alchemy factor
    float x = getAlchemyFactor();

    float averageIngredientValue = 0.0f;
    float priceMod = 0.0f;
    float multMod = 1.0f;
    
    //average the ingredient values with guarding against 0s
    //then work out benefit from tiers and apply
    if ((sumIngredientValue > 0) && (numberIngredients > 0))
    {
        averageIngredientValue = (sumIngredientValue / numberIngredients);

        if (averageIngredientValue < 5.0f)
        {
            multMod = 0.7f;
        }
        else if ((averageIngredientValue >= 5.0f) && (averageIngredientValue < 200.0f))
        {
            // y = 64.46238 + (-293895.7 - 64.46238)/(1 + (x/3.767532e-32)^0.116272)
            // where y is skill boost, and x is ingredient value

            float yf = 64.5f + (-293960.0f / (1.0f + std::powf(averageIngredientValue / 3.76e-32f, 0.11627f)));
            priceMod += yf;
        }
        else if (averageIngredientValue >= 200.0f)
        {
            priceMod = 30.0f;
            float highValueHolder = (averageIngredientValue - 200.0f);
            highValueHolder /= 10.0f;
            priceMod += highValueHolder;
        }

        if (averageIngredientValue >= 100.0f)
        {
            multMod = 1.1f;
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
- If the average value of alchemy ingredients used is less than 5g, take a -30% penalty to your alchemy factor
- If the average value is,
- 5-10g, gain between a +10 and a +15 bonus to your effective alchemy skill
- 10-25g, gain between a +15 and a +20 bonus
- 25-100g, gain between a +20 and a +25 bonus
- 100-200g, gain between a +25 and a +30 bonus, along with an additional 10% bonus to alchemy factor after the addition
- 200g+, gain a +30 up to a (average value of items - 200) / 10 bonus to your alchemy skill, so e.g. at 200 you gain +30, at 300 you gain +40, etc (there are very few ingredients even in TR that exceed 200, so this is an edge case and a reward if you decide to use something really valuable for a one shot potion. Still probably not worth it though!)
	- In addition, as with the 100-200g range, gain an additional 10% bonus to alchemy factor after the addition

Up to 200, this is governed by a non-linear line equation, which is simplified in the above code from
```
y = 64.46238 + (-293895.7 - 64.46238)/(1 + (x/3.767532e-32)^0.116272)
```

The overall effect is that
- Using cheap (sub 5g value) ingredients results in weaker potions at all skill levels
- Using more expensive in ingredients results in stronger potions, which is most notable at low levels
- The highest values of ingredients, an average of 100g+, adds a flat +10% modifier in addition at a flat skill boost, so that even at very high skill/factor they have an effect

### 3.18.5, Reduce the impact of the mortar
`alchemy.cpp`

Aim: Make mortar quality above or below 1.0 have 50% less of an effect, to stop stacking equipment and ingredients resulting in way too strong potions at the high end

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

    // begin step down mortar effectiveness, dwemer coda
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

    // end step down mortar effectiveness, dwemer coda
```

### 3.18.6, Switch potion making to a magicka costed system
`alchemy.cpp`

**Part one, converting alchemy factor into a magicka budget**
Magicka budget = alchemy factor / 6

Reasoning: you cannot reasonably have an alchemy factor of less than 12 (skill 5, intelligence 30, luck 40), so you will always start with a minimum potion spell cost equivalent of 2.

So at 100 alchemy, luck, and intelligence, you will be making 20 magicka costed potions (assuming you don't have fancy tools by then, which you will)

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
float potionMagickaBudget = (x / 6.0f);

float vHolderOne = (potionMagickaBudget / magicEffect->mData.mBaseCost);
vHolderOne *= 40.0f;
float durHolder = sqrtf(vHolderOne);
float magHolder = (durHolder / 2.0f);

// dwemer coda budget to effect converter end

float magnitude = (magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude) ?
            1.0f : magHolder;
float duration = (magicEf
```
- Divides alchemy factor by 6 to get a magicka budget
- Uses the above equation to 'spend' the magicka budget of the alchemy result equally on duration and magnitude, as if you were casting an equivalent spell made with the spellmaking system

**If the potion effect is missing either it's magnitude or duration**

Some effects like water walking have a fixed magnitude of 1, so to properly mirror the spellmaking logic a fork in the above calculations has been added to account for this.

Went back to the original magnitude/duration budgeting code and did this,
```
        // dwemer coda budget to effect converter start

        float vHolderOne = (potionMagickaBudget / magicEffect->mData.mBaseCost);
        vHolderOne *= 40.0f;
        float durHolder = sqrtf(vHolderOne);
        float magHolder = (durHolder / 2.0f);

        //override duration to budget over two, if the effect has no magnitude
        if (magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude)
        {
            durHolder = (vHolderOne / 2.0f);
        }

        //override magnitude to budget over two, if the effect has no duration
        if (magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration)
        {
            magHolder = (vHolderOne / 4.0f);
        }

        // dwemer coda budget to effect converter end

        float magnitude = (magicEffect->mData.mFlags & ESM::MagicEffect::NoMagnitude) ?
            1.0f : magHolder;
        float duration = (magicEffect->mData.mFlags & ESM::MagicEffect::NoDuration) ?
            1.0f : durHolder;
```

### 3.18.7, Adjusted behaviour for all other tools
`alchemy.cpp`

The full original function
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

**New version and changed**
The logic has overall been simplified,
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

### 3.18.8, Capping potion values at sum cost of ingredients
`alchemy.cpp`

Aim: Cap the value of a potion the player makes by the sum value of the ingredients used in the potion

Just did this
```
    // potion value, with dwemer coda cap added
    mValue = static_cast<int> (
        x * MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find ("iAlchemyMod")->mValue.getFloat());
    mValue = std::min(mValue, sumIngredientValue);
```

Only the `std::min` addition was new by me. It uses the sum ingredient value variable that was established above as part of the item value logic

**Comments:**
- This is a harsh cap, and means that you can never make money from alchemy by mass buying and processing ingredients. But this was intentional, to stop any exploitative gameplay loops.
	- The only problem with this first version, is that it is not realistic. You should be able to make money selling powerful healing potions, people would be willing to pay more than the base ingredients are worth. So this is something to revisit after some playtesting.

### 3.18.9, Reducing XP gained from cheap ingredient potions
`alchemy.cpp`

Aim: XP gain from making a potion scales with either average item value, or sum item value, or there is just a penalty below a certain value and skill. In essence, I want to make spamming 1g potions non-viable past a certain point, and I want to reward using high value ingredients in potions with more XP.

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
    //even this might be too generous
    if (averageIngredientValue < 5.0f)
    {
        alchXpMod = 0.5f;

        if (alchemySkill > 30.0f)
        {
            alchXpMod = 0.25f;
        }

        if (alchemySkill > 60.0f)
        {
            alchXpMod = 0.125f;
        }

        if (alchemySkill > 90.0f)
        {
            alchXpMod = 0.05f;
        }
    }

    mAlchemist.getClass().skillUsageSucceeded(mAlchemist, ESM::Skill::Alchemy, 0, alchXpMod);
    //increaseSkill();
```

The end result is that,
If average potion ingredient value is less than 5gp,
- You earn 50% of the normal XP if skill 30 or below
- You earn 25% of the normal XP if skill 30 to 60
- You earn 12.5% of the normal XP if skill 60 to 90
- You earn 5% of the normal XP if skill 90+

### 3.18.10, GMST value and behaviour changes
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

## 3.21, More XP from casting expensive spells
`spellcasting.cpp`


Original code, within `bool CastSpell::cast(const ESM::Spell* spell)`

```
if (!mManualSpell && mCaster == getPlayer() && spellIncreasesSkill(spell))
	mCaster.getClass().skillUsageSucceeded(mCaster, spellSchoolToSkill(school), 0);
```

New code

```
        //dwemer coda, more XP from high costed spells

        float xpMult = 1.0f;
        float spellCost = spell->mData.mCost;

        if (spellCost > 5.0f)
        {
            xpMult = (spellCost * 0.0889f);
            xpMult += 0.556f;
        }

        if (!mManualSpell && mCaster == getPlayer() && spellIncreasesSkill(spell))
            mCaster.getClass().skillUsageSucceeded(mCaster, spellSchoolToSkill(school), 0, xpMult);

        //end of dwemer coda, more XP from high costed spells
```

## 3.23, Willpower change (buff)
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

Within `spellcasting.cpp`, the magic resist capping system was modified to include a conversion of willpower to magic resist.

For every 5 points of willpower above 50, add 1% magic resistance.
- So at 100 willpower, your character has an invisible +10% resist magicka

modification to function

```
            // Start of dwemercoda resistance caps

            if (target == getPlayer())
            {
                int effectholder = 1;
                effectholder = effectIt->mEffectID;

                float magcap = 0.4f;

                //sub system to add 10% of willpower to magic resist
                MWWorld::Ptr player = getPlayer();
                const MWMechanics::CreatureStats &playerStats = player.getClass().getCreatureStats(player);
                float playerWill = playerStats.getAttribute(ESM::Attribute::Willpower).getModified();
                float willMagicResist = 0.0f;

                if (playerWill > 50.0f)
                {
                    playerWill -= 50.0f;
                    willMagicResist = (playerWill / 500.0f);
                }

                //check for drain effects
                if (effectholder == 17 || effectholder == 18 || effectholder == 19 || effectholder == 20 || effectholder == 21)
                {
                    magnitudeMult -= willMagicResist;
                    if (magnitudeMult < magcap)
                    {
                        magnitudeMult = magcap;
                    }
                }
```

and it just repeats the

```
                {
                    magnitudeMult -= willMagicResist;
                    if (magnitudeMult < magcap)
                    {
                        magnitudeMult = magcap;
                    }
                }
```

logic for every group of MR effect checks

The same was done in `inventorystore.cpp`, as had to be done with the original willpower capping, as magic items with constant effects are handled separately here.

Within `void MWWorld::InventoryStore::updateMagicEffects(const Ptr& actor)`

```
 if (!existed)
            {
                params.resize(enchantment.mEffects.mList.size());

                int i=0;
                for (const ESM::ENAMstruct& effect : enchantment.mEffects.mList)
                {
                    int delta = effect.mMagnMax - effect.mMagnMin;
                    // Roll some dice, one for each effect
                    if (delta)
                        params[i].mRandom = Misc::Rng::rollDice(delta + 1) / static_cast<float>(delta);
                    // Try resisting each effect
                    params[i].mMultiplier = MWMechanics::getEffectMultiplier(effect.mEffectID, actor, actor);

                    // Start of dwemercoda resistance caps

                    float magcap = 0.4f;

                    //sub system to add 10% of willpower to magic resist
                    MWWorld::Ptr player = MWMechanics::getPlayer();
                    const MWMechanics::CreatureStats &playerStats = player.getClass().getCreatureStats(player);
                    float playerWill = playerStats.getAttribute(ESM::Attribute::Willpower).getModified();
                    float willMagicResist = 0.0f;

                    if (playerWill > 50.0f)
                    {
                        playerWill -= 50.0f;
                        willMagicResist = (playerWill / 500.0f);
                    }

                    // Check for drain effects
                    if (effect.mEffectID == 17 || effect.mEffectID == 18 || effect.mEffectID == 19 || effect.mEffectID == 20 || effect.mEffectID == 21)
                    {
                        params[i].mMultiplier -= willMagicResist;
                        params[i].mMultiplier = std::max(magcap, params[i].mMultiplier);
                    }

```

and the same for all the other sequential groups of magical effect checks.

## 3.25, Hand to Hand changes
`combat.cpp`
`npc.cpp`
`creature.cpp`
`difficultyscaling.cpp`
`difficultyscaling.hpp`

### 3.25.1, Accuracy

This change has not been made here, it was done during the original melee accuracy pass, but I have included it as a reminder of what was done there.

**Hand to hand accuracy**
Tested and confirmed that hand to hand accuracy is also captured in the new weapon accuracy logic, so hand to hand combat accuracy is,
```
Accuracy = (Hand to hand skill*0.7)+(Agility/5)+(Luck/10)
Accuracy *= fatigue mod
Accuracy += fortify attack
Accuracy -= blind
Accuracy += 20
```
So it has a higher floor, and scales slower. This is the same code used for weapon accuracy.

### 3.25.2, Damage done at low skill levels
`combat.cpp`

Since in core the damage done by hand to hand is derived from your skill multiplied by your attack draw strength, you do trivial amounts of damage at low skill.

For example, given that a fully drawn attack caps out at a 0.5x multiplier,
- Skill 5 = 2.5 fatigue damage
- Skill 10 = 5
- Skill 20 = 10
- Skill 30 = 15
The logic was changed as below to be 10 + (your skill x 0.9),
which is then modified by the draw strength as in core, resulting in
- Skill 5 = 7.25 fatigue damage
- Skill 10 = 9.5
- Skill 20 = 14
- Skill 30 = 18.5
- It then becomes roughly equivalent to core behaviour from skill 40 onwards, scaling a little slower overall and reaching the same final damage value at 100 skill.
- Beyond 100 skill this does result in a reduction in damage gained from skill, but that is probably desirable due to the linear scaling already resulting in potentially absurd figures with some fortify skill effects

Within `combat.cpp`
Within the function `void getHandToHandDamage`

The first few lines were changed to
```
    void getHandToHandDamage(const MWWorld::Ptr &attacker, const MWWorld::Ptr &victim, float &damage, bool &healthdmg, float attackStrength)
    {
        const MWWorld::ESMStore& store = MWBase::Environment::get().getWorld()->getStore();
        float minstrike = store.get<ESM::GameSetting>().find("fMinHandToHandMult")->mValue.getFloat();
        float maxstrike = store.get<ESM::GameSetting>().find("fMaxHandToHandMult")->mValue.getFloat();
        damage  = (0.9f * (static_cast<float>(attacker.getClass().getSkill(attacker, ESM::Skill::HandToHand))));
        damage += 10.0f;
        damage *= minstrike + ((maxstrike-minstrike)*attackStrength);
```

Whereas before damage was just equal to your skill

### 3.25.3, Fatigue damage difficulty based scaling
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

This results in,

| Tier | % Melee/<br>on-hit dealt | % Melee <br>taken | % Magic/ench<br>damage dealt | % Magic<br>taken | Fatigue dealt | Fatigue taken |
| ---- | ------------------------ | ----------------- | ---------------------------- | ---------------- | ------------- | ------------- |
| 1    | 100                      | 100               | 100                          | 100              | 100           | 100           |
| 2    | 75                       | 150               | 85                           | 125              | 85            | 125           |
| 3    | 50                       | 200               | 70                           | 150              | 70            | 150           |
| 4    | 30                       | 300               | 50                           | 200              | 50            | 200           |
| 5    | 20                       | 400               | 33                           | 250              | 33            | 250           |
| 6    | 15                       | 500               | 25                           | 300              | 25            | 300           |
The numbers are the result of some initial playtesting, and may need refining. Also note for now they are just a duplicate of the magic damage scaling values (which have seemed to be okay from some initial testing).

Within `npc.cpp`,
Within the else fork (else covers if `isHealth` if false) of `onHit`
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
before my custom player/NPC fork, and regardless of it, the damage is now scaled as per the hand to hand function. The check for damage greater than 0 may be strictly necessary, but there are a few calls in the engine to the `onHit` function from non-attack sources which pass `isHealth = false` and damage = 0. So I added the check for, is damage greater than 0, as guarding against strange behaviour versus those calls. Not strictly needed I think, but good futureproofing.

Within `creature.cpp`,
Within the else fork (else covers if `isHealth` if false) of `onHit`
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

### 3.25.4, Changing Openmw strength scaling behaviour
`combat.cpp`

Openmw adds an optional strength scaling for hand to hand combat. I would like to keep this, and suggest it be toggled on by default, however the way it is implemented is slightly buggy and not in line with how attributes affect other skills.

If the toggle is on, it does
```
damage *= attacker.getClass().getCreatureStats(attacker).getAttribute(ESM::Attribute::Strength).getModified() / 40.0f;
```

Which is multiplying your hand to hand damage by your strength over 40, this causes two problems (one likely unintentional)
- At 100 strength you are doing 2.5x hand to hand damage, this seems excessive, and certainly will be as I revise this system
- At damaged strength values below 40, you do massively reduced damage (I assume this is unintentional), e.g. if you are damaged to strength 10, you do 10/40 = 25% of your normal damage
	- Whereas with all weapons in the base game, a strength of 10 would only reduce weapon damage to 60% of the bae value, since that logic is counting values above and below 50

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
            //dwemcod, change str scaling to behave like weapon scaling does in core
            float attackerStrength = attacker.getClass().getCreatureStats(attacker).getAttribute(ESM::Attribute::Strength).getModified();
            float strengthMult = 1.0f;
            float strengthHolder = 50.0f;

            //some zero guarding, I don't know If I need it, but better safe than sorry
            attackerStrength = std::max(1.0f, attackerStrength);

            //this doesn't need to be two if statements, the logic is identical, collapse it down when I tidy the code

            if (attackerStrength > 50.0f)
            {
                strengthHolder = (attackerStrength - 50.0f);
                strengthHolder /= 100.0f;
                strengthMult += strengthHolder;
            }

            if (attackerStrength < 50.0f)
            {
                strengthHolder = (attackerStrength - 50.0f);
                strengthHolder /= 100.0f;
                strengthMult += strengthHolder;
            }

            damage *= strengthMult;

            //damage *= attacker.getClass().getCreatureStats(attacker).getAttribute(ESM::Attribute::Strength).getModified() / 40.0f;
        }
```

As stated in the comments, the guarding might not be strictly necessary, and the way the code is written is redundant, there's no need for the if forks as the logic works the same above and below 50. I just decided to leave it in for now until I start cleaning things.

## 3.26, Pickpocketing overhaul
`pickpocket.cpp`
`pickpocketitemmodel.cpp`

### 3.26.1, You can no longer get caught when closing the pickpocketing UI
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

### 3.26.2, Item difficulty is value x1, providing GMST is 1.0. Change to expected GMST value
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

### 3.26.3, Updating what items can appear to the player in the NPC inventory window when sneaking
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
                    continue; // don't know if I needed to do this, but it's a robust guarding, I think technically
                              // some NPCs can carry light sources as psuedo items

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

### 3.26.4, Change to pickpocketing difficulty logic
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

# 4, ESP Changelog

See the V0.70 ESP companion file for a complete list of ESP changes.
Since V0.50 the ESP has been 'cleaned', meaning all development items have been removed, as have all non essential gameplay changes (e.g. race and birth sign changes)

New additions in V0.70 are detailed in the companion, but they are also summarised below:

## 4.22, Summons rebalance

See mechanics changelog for list of exact changes. 

All player summons modified, excluding the centurion sphere, the three bloodmoon summons, and the verminous fabricant summon.

The following spells added and used to change the abilities and spells of the summons:

```
|dwemcod_summon_ghost_sanctuary|
|dwemcod_Ghost_Curse|
|dwemcod_summon_scamp_blind|
|dwemcod grave curse: endurance|
|dwemcod grave curse: strength|
|dwemcod_summon_firebloom|
|dwemcod_summon_frostbloom|
|dwemcod_summon_shockbloom|
|dwemcod_summon_shock_shield|
|dwemcod_summon_second_barrier|
|dwemcod_grave_curse_bonelord|
|dwemcod_summon_hunger_disint|
|dwemcod_summon_third_barrier|
|dwemcod_summon_poisonbloom|
|dwemcod_summon_shock_shield_10|
|dwemcod_summon_spellabsorb|
|dwemcod_summon_greater_absorb|
```

Summon souls set to 0
Spells generally buffed, where they had little impact
Weak summons buffed a little

Also the effect cost of summon greater bonewalker was increased, as it was unusually low for it's power level.

* Greater bonewalker effect cost, 15 -> 19

## 4.24, Adjusted previous change to spellcasting XP gain

Base conjuration and destruction XP reverted back to 2.0 from 3.0.

The change to 3.0 was originally done during testing where it was found even going to 2.0 was too slow, and the two skills didn't level much due to most normal usage being single casts of very high cost spells.

With the casting XP revision, this is no longer needed as preliminary testing shows the schools do gain XP well now (due to them tending to prefer higher costed spells naturally in combat).

## 4.25, Hand to Hand changes

`fHandtoHandHealthPer` increased to 0.4, from 0.1 in the base game, which results in your hand to hand attacks doing 40% of the fatigue damage they would have dealt, as health damage (when striking a knocked down or paralysed opponent)

## 4.26 Pickpocketing overhaul

- GMST: `iPickMaxChance` does determine your max pickpocket chance, so if it's 50, your maximum pickpocket chance is 50%
	- Set to 100, up from 75 in the base game, so you can reach 100% success chance with enough skill
- GMST: `iPickMinChance` is claimed to raise your minimum pickpocket chance, and whilst it does do that, it seems to be a little more complicated than just setting the floor to it's value
	- Left at the floor value of 5 (which is practically irrelevant in the new V0.70 logic)
	- But, functionality of the GMST changed so that it is a simple and true flat minimum success chance. You can never have lower than this GMST in success chance
- GMST: `fPickPocketMod` to 1.0 (up from 0.3 in the base game)
	- Functionality broadly the same, but the system assumes a GMST value of 1.0, which is 1x gold value
	- Higher values make it harder to pickpocket, by weighting the value of items more in the new difficulty system, e.g. setting the GMST to 10 means it is 10x harder to pickpocket, by item value. The same is true for sub 1 values

Note functionality changes to `iPickMinChance` and `fPickPocketMod`!# dwemercoda
dwemcod beta version, private
