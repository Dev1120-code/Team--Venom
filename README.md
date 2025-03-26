
# Tetris Game in C++

A  Tetris Game implementation in C++ using console graphics.

## Table Of Contents
- [Features](#Features)
- [Requirements](#Requirements)
- [Installation](#Installation)
- [Controls](#Controls)
- [Game Mechanics](#Game-Mechanics)
- [Scoring System](#Scoring-System)
- [Sample Photo](#Sample-Photo)


## Features

- Tetris gameplay with 7 different tetromino shapes
- Score system with high score tracking
- Colorful console interface
- Keyboard controls for movement and rotation
- Game speed increases as you play

## Requirements

- Windows OS
- C++ compiler (tested with g++ and MSVC)
- `<conio.h>` library for keyboard input

## Installation

1. Clone this repository or download the source files
2. Compile the code using your preferred C++ compiler: g++ tetris.cpp -o tetris
3. Run the executable: ./tetris


## Controls

| Key          | Action               |
|--------------|----------------------|
| Left Arrow   | Move piece left      |
| Right Arrow  | Move piece right     |
| Down Arrow   | Soft drop (move down)|
| Up Arrow     | Rotate piece         |
| Spacebar     | Instant drop         |
| ESC          | Quit game            |

## Game Mechanics

- Pieces spawn at the top center of the playfield
- Complete lines to score points and clear space
- Game ends when new pieces can't spawn
- Score increases based on number of lines cleared at once

## Scoring System

- 1 line: 10 points

## Sample Photo 

![Screenshot 2025-03-27 015843](https://github.com/user-attachments/assets/a0492671-22b2-42e7-8d8a-5b4cf2031504)


