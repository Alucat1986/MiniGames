# MiniGames [C++]
Since I really want to get into game development, I want to start with cloning smaller games, and actually finishing them. I will use the SFML 3.0 Library for now as I am more used to it, but maybe I will dabble into other libraries as well at other points (or for other projects).

## Install
To build the repository follow the steps:

1) Open a console and navigate to the repository folder
2) Make sure SFML is a submodule inside the folder `3rdParty`, I'm using the tag for `3.0.0` here. Have it build in debug or release as a static library, depending on if you want to compile my projects as debug or release configuration.  
-> These two libraries should be part of the submodule:  
    `freetype.lib`  
    `freetyped.lib`  
-> If you don't add it as a submodule, In the premake file `<Game>/Build-<Game>.lua` edit the `includedirs` and `libdirs` variables to let it know where your SFML includes and compiled libraries can be found.
3) The following 3 libraries are needed outside of SFML:  
    `opengl32.lib`  
    `winmm.lib`  
    `gdi32.lib`  

    I haven't found anything on this and I was able to just link to them, so I assume they are part of the OS?  
4) Use `premake5` if you have it installed on your pc, otherwise `3rdParty/Binaries/Premake/YourOS/premake5`

    For windows:
    `premake5 vs2022` or `3rdParty/Binaries/Premake/Windows/premake5.exe vs2022`

    For Linux:
    `premake5 gmake` or `3rdParty/Binaries/Premake/Linux/premake5 gmake`

    For Mac:
    `premake5 xcode4` or `3rdParty/Binaries/Premake/macOS/premake5 xcode4`

## Pong [[SFML](#used-and-mentioned-libraries)]
A simple Pong clone made with C++20 and SFML 3.0.

The aim for using Pong as the first project was to get back into SFML as well as getting used to the new way of using it, quite a bit changed in their syntax. It will probably just stay as a pure pong clone without any new additions or twists.

## Snake [[SFML](#used-and-mentioned-libraries)]
A clone of Snake made with C++20 and SFML 3.0.

In comparison to the Pong clone this one will use sprites and textures instead of just simple shapes to present the snake and the food. Plus this project will have "Managers" who overview and do stuff on the board, for example the food manager will make sure that there is at least one food always present on the board and of course the snake itself who manages itself as it can grow, move and die.

The game level will be a grid system for 'easier', I'm missing a proper word here, movement as well as food spawning. The cells of the grid will be squares, meaning that their $`WxH`$ will have $`W=H`$ with currently $`W=H=64`$. There is also a margin around each cell, mostly used to be able to draw an actual grid around the cells for debug purposes.

## What is further planned?
I am planning on making a clone of "Snake" as well as "Space Invaders", perhaps a Tetris one too, but the last one depends on how confident I get with SFML 3.0 during "Snake" and "Space Invaders". Otherwise I can imagine going for a slightly bigger Project, be it something new or just giving one of these other projects a twist... idk like turn "Space Invaders" into a rogue-like where you can get upgrades because the enemies grow stronger and stronger.

### Further future considerations
I am not decided on this yet, but I could also try out other libraries instead of SFML 3.0 since SDL3.2 was released or Raylib 5.5 ([See Libs](#used-and-mentioned-libraries)). But that's something future me has to decide on :)

## Used and Mentioned Libraries
| Library | Link |
| :--- | :--- |
| SFML 3.0: | [SFML Homepage](https://www.sfml-dev.org) |
| SDL 3.2: | [SDL Homepage](https://www.libsdl.org) |
| Raylib 5.5: | [Raylib Homepage](https://www.raylib.com) |