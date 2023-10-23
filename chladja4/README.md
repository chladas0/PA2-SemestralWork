# Ant game

## Introduction

This project is a card-based RPG engine inspired by the Czech card game Ants. The game can be played either against another player or against AI. Each player has their own base and cards that they can play. Each card costs a certain number of one or more resources. Cards have one or more effects that can damage the enemy or help the player. The game ends when one player's base reaches 100 or drops to 0. These values can be changed in the configuration file. This game can be modified to create a completely different game using the configuration file.


### Game controls

At the beginning, the player is given the option to start a new game against another player or against AI, or to load a game from a file. If they choose to load a game from a file, they can do so by selecting the corresponding option and entering the name of the file. If they choose to create a new game, they will be asked to enter a name if they want to play against another player. The game will then load, and each turn the player can use one card by selecting the number listed to the left of the card.

During the game, the player can also use commands. The "help" command displays the known commands, and the "save" command saves the game to a file. If the player decides to quit the game, they can use the "quit" command to surrender.

If the player decides to save the game to a file, it will be saved in the "examples" directory. If they attempt to overwrite an existing file, they will be asked if they really want to do so. The games are saved in a slightly modified CSV format. When loading a game from a file, all files in CSV format are highlighted in green.

Whenever the player enters invalid input, they will be notified, and the game will prompt them for new input. If the player presses CTRL + D during the game, the game will end correctly, and the player will be informed that the end of input (EOF) has been reached.


### Gameplay sample
Main menu:

```
Welcome to the Ant game

(0) New game -> player vs player
(1) New game -> player vs AI 
(2) Saved game -> Load from a file
Choose the type of game: 
```

One round of the game:

``` C++
================================== UltimateAI ==================================
Base: 40 (lose=0, win=100)
Builders: 4 Magicians: 4 Soldiers: 4 
Bricks: 50 Crystals: 50 Weapons: 50 

==================================== Karel =====================================
Castle: 40 (lose=0, win=100)
Builders: 4 Magicians: 4 Soldiers: 4 
Bricks: 50 Crystals: 50 Weapons: 50 

Card(0) ResourceMine
Effects: {Bricks +10, Crystals +10, Weapons +10} Costs: {Crystals -> 20}

Card(1) Fortress
Effects: {Base +20} Costs: {Bricks -> 20}

Card(2) ResourceMine
Effects: {Bricks +10, Crystals +10, Weapons +10} Costs: {Crystals -> 20}

Card(3) BrickGenerator
Effects: {Bricks +20} Costs: {Crystals -> 5}

Card(4) Refiller
Effects: {2x resource refill} Costs: {Crystals -> 10}

================================================================================
Player on turn: Karel

Enter the number of the card you want to play or "help" for instructions : 
```
