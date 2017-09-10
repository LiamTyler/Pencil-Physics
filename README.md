# Pencil Physics

## Description
The goal of this assignment was to learn how to create an interface between a graphics toolkit and other libraries, like a physics engine. This program allows the user to interactively manipulate objects on the screen that translate into force / constraints handled by the box2D engine. You can create circels, boxes, and lines. You can then drag your objects around and watch how they interact

## Tools Used
- Modern OpenGL 3 for drawing
- SDL2 for the windowing and user input
- Box2D for the physics engine

## Features
- Interactive objects
- Movement and collision handled by physics engine

## Controls
- Mouse: Click and move to create pencil line while in draw mode
- 'B': Adds a box
- 'C': Adds a circle
- Tab: Switches from drawing mode to moving mode
- Backspace: Reset the scene


## Installing
On Linux:
```sh
g++ main.cpp -lGL -lGLU -lSDL2 -lGLEW -lBox2D
```
