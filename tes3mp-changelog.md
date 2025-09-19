0.8.1
-----

* Allow GameSettings packet to override clientside VR settings
* Include projectile origins in packets for attacking and casting, necessary for VR compatibility

0.8.0
-----

* Synchronization of custom records for interior cells, allowing for on-the-fly creation of entirely new interiors or ones based on existing interiors
* Synchronization of custom records for clientside scripts, allowing for on-the-fly creation or overriding of MWScripts
* Synchronization of custom records for containers, doors, activators, statics, ingredients, apparatuses, lockpicks, probes, repair tools, lights, body parts, sounds and record-based game settings
* Synchronization of clientside local variables based on which clientside scripts are set to be synchronized by the server
* Synchronization of clientside global variables based on rules defined for each one in the server scripts, with the possibility of also creating new clientside globals on-the-fly
* Synchronization of active spell effects for players and actors that no longer relies on players witnessing the spellcasting associated with the effects
* Synchronization of death animations for players and actors
* Synchronization of merchant inventories and gold pools
* Synchronization of environmental sounds made by players, e.g. when picking up or dropping items, when opening or closing chests and doors
* Synchronization of plant harvesting from herbalism mods
* Reworked attack synchronization with more precision, fixing skipped attacks for creatures with fast attack animations and making melee attack animations not depend on the direction a player or actor is moving in on the current client
* Reworked spellcasting synchronization, fixing improper failed spellcasting for actors with fast casting animations and reducing desyncs by not tying spellcasting for non-local actors and players to their animations on the current client
* Reworked equipment synchronization for players with less spammy packets
* Packet for resetting interior and exterior cells on-the-fly
* Packet for setting players as allies so they don't break each other's stealth and so their companions don't fight back when attacked by mistake
* Packet for overriding cell destinations, useful for moving players to instances of interiors instead of regular interiors
* Packet for tracking hits received by objects
* Packet for tracking dialogue choices selected by players
* Packet for tracking the cooldowns of powers used by players
* Allow GameSettings packet to override clientside game settings
* Allow custom records to override AI services for NPCs, alarm and flee values for NPCs and creatures, as well as scales, blood types, soul values and attack damage for creatures
* Fix freezes related to having too many players in a single interior cell
* Fix packet spam from some situations where actors start fights with players during dialogue
* Fix ObjectActivate packets not being sent when picking up items from inventory screen
* Fix ObjectDelete packets not being sent when non-container items are purchased from merchants who own them
* Fix PlayerItemUse packets not being sent when using quick keys
* Fix ConsoleCommand packets being ignored when sent by the server without a cell being associated with them
* Fix desyncs caused by late-arriving ActorAuthority packets by sending the packets to everyone on the server instead of only the players who have the associated cell loaded
* Fix indexes used when synchronizing the unassigning of quick keys
* Fix stealing being ignored when using Take All on owned containers
* Fix guards ignoring fights between players and other guards
* Prevent players from attacking while in persuasion dialogues with NPCs
* Prevent players from sending DoorState packets when not logged in
* Prevent NPCs from saying their dying words if they have been loaded up as dead from the server
* Prevent players and actors from playing their equipping sounds when they are first encountered
* Alleviate actor-related desyncs by not ignoring an entire packet when one of the actors referenced in it cannot be found
* Track kills caused through spell effects that do damage over time
* Track uses of the console by players
* Add serverside script functions for saving the identities of summoners
* Implement hashing for player passwords

0.7.0
-----

* Synchronization of custom records for spells, potions, enchantments, creatures, NPCs, armor, books, clothing, miscellaneous items and weapons
* Synchronization of weather
* Synchronization of world map exploration
* Synchronization of spells cast through items
* Synchronization of player reputations
* Reworked attack synchronization now accounts for "cast on strike" enchantments, knockdowns and projectile speeds
* Reworked container synchronization that relies on server approval of every container change
* Reworked object synchronization that relies on server approval of every action on objects and tracks whether actions originated from regular gameplay, the console or from ingame scripts
* Reworked time synchronization that preserves ingame date and does not allow for any unilateral clientside time changes
* Reworked summoning synchronization that prevents duplicate summons and retains summon durations
* Reworked inventory, equipment, attribute, skill and dynamic stat packets that are sent more often while containing minimal instead of maximal data
* Packet for activation of objects
* Packet for using items in inventory
* Packet for actor AI
* Packet for actor deaths, used to track their killers
* Packet for overriding collision on objects
* Packet for setting momentum of players
* Packet for saving and loading marked locations and selected spells
* Player scales and disguises as creatures are now included in shapeshift packets
* Soulgem souls are now included in item and object placement packets
* Physics framerate caps and enforced log levels are now included in game settings packets
* Journal entry timestamps are now included in journal packets
* The value of the OnPCDrop variable for player-placed objects is now preserved by being included in object placement packets
* Video play packets no longer have hardcoded synchronization
* Death packets now include clear information about the killers, and deaths through spells are no longer treated as suicides
* Inventory packets no longer include bound items, preventing them from becoming persistent upon quitting
* Fix broken check in equipment synchronization that was preventing throwing weapon synchronization from working
* Fix rare inability to start up game caused by use of potentially invalid pointer for storing cell unloads
* Death as a werewolf now removes status as known werewolf, to prevent infinite aggression from NPCs
* Death as a criminal now prevents witnesses to previous crimes from continuing combat
* Players are now kicked from the server when failing to reply to its handshake
* Players can no longer open up their rest menu before logging in
* NPC followers now follow players correctly from interiors to exteriors and vice versa, and are able to follow non-authority players
* NPCs can now start combat through dialogue with non-authority players
* The console window now displays the unique index of a selected object

0.6.2
-----

* Packet for quick keys
* Packet for player sounds
* Packet for player animations
* Packet for console commands
* Enchantment charge values are now included in item and object placement packets
* Settings packet can now be used to separately enable or disable resting in beds, resting in the wilderness and waiting
* Changes in attribute and skill modifiers now send their respective packets
* Attribute and skill packets using 0 as a modifier can now remove all attribute or skill fortification effects from a player
* Completion of vendor trades and skill training now sends inventory packets
* Item drag and dropping is now finished when arrested or when moved to another cell by the server
* Window minimization no longer pauses the game
* Actor speech captions are now searched for in dialogues instead of being sent in packets

0.6.1
-----

* Record player positions before their last cell change
* Remove inertia from players who are teleported via a packet
* Fix data loss caused by server packets attempting to add invalid items, spells and quests
* Fix client crashes caused by items with state disabling scripts, as well as their side effects of making players disappear to others
* Fix server crashes caused by improper interior initialization when exterior 0, 0 is loaded
* Fix server freezes caused by infinite topic packet spam from local scripts
* Fix spell casting probability synchronization
* Prevent players from using excessively long names

0.6.0
-----

* Synchronization of NPC & creature positions, stats, equipment, speech, attacks, spells & animations
* Reworked server browser with major stability fixes and additional information about servers
* Synchronization of client & server plugins (non-automated)
* Synchronization of leveled & summoned creature spawns
* Synchronization of rotation animations
* Synchronization of journal entries
* Synchronization of faction ranks, reputation and expulsion states
* Synchronization of dialogue topics
* Synchronization of kill counts checked in quest progression
* Synchronization of trap states
* Synchronization of object states (i.e. whether they are enabled or disabled)
* Synchronization of player werewolf states
* Synchronization of time of day
* Packet for saving and loading of read skill books
* Fix to messagebox buttons for client scripts
* Fix to synchronization of object locking/unlocking
* Packet for jailing players
* Packet for setting the difficulty for each player
* Bandwidth optimization for all packet types
* Various fixes to client & server crashes

0.5.2
-----

* Fix to server crash caused by not deleting empty cells upon players disconnecting
* Fix to client freezes caused by invalid spells and races
* Fix to players not being spawned when using other base master files
* Fix to visual glitch where flying players bounced up and down continuously

0.5.1
-----

* Fix to server crash caused by incorrect cell comparison added by bandwidth optimization changes
* Fix to server browser freeze caused by connection failures and incomplete data received from master server

0.5.0
-----

* Server browser
* Synchronization of containers
* Reworked world packets allowing for the saving and loading of world state, including container state
* Bandwidth optimization by forwarding the most frequent player packets only to other players in the same loaded cells

0.4.1
-----

* Packet for saving and loading spellbooks

0.4.0
-----

* Synchronization of spells
* Packet for saving and loading inventories
* Being in a menu no longer prevents you from sending packets about your client
* Fixes to freezes and problems caused by players moving around in cells from expansions/plugins that are not loaded by others

0.3.0
-----

* Synchronization of world object removal, placement, scaling, locking and unlocking
* Synchronization of local, global and member script variables for specific scripts
* Synchronization for the setdelete, placeat, setscale, lock and unlock console commands
* Player markers on minimap
* Death reasons in chat
* Fix to client freeze related to players logging in at the same time
* Fix to server crash related to sending information about invalid players

0.2.0
-----

* Packets for saving and loading classes, birthsigns, dynamic stats, levels, level progress, attribute bonuses from skill increases and progress towards skill increases
* Version checking to prevent mismatches between clients and servers

0.0.1b
------

* Synchronization of attributes and skills
* Fix to memory leaks related to player initialization on Windows servers
* Fix to various graphical glitches
* Main menu buttons for starting, saving and loading games are now disabled

0.0.1a
------

* Combat animation
* Synchronization of melee and ranged (bow, crossbow, throwable weapons) combat
* Synchronization of health, magicka, fatigue and death
* Synchronization of cell changes
* Server-side Lua scripting
* Chat

0.0.1
-----

* Initial networking and packet architecture
* Synchronization of player character generation
* Synchronization of player position
* Synchronization of player attack states (unarmed, armed with a weapon, using a spell)
* Synchronization of movement and jump animations
