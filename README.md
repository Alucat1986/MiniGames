# MiniGames [C++]
Since I really want to get into game development, I want to start with cloning smaller games, and actually finishing them. I will use the SFML 3.0 Library for now as I am more used to it, but maybe I will dabble into other libraries as well at other points (or for other projects).

## Install
To build the repository follow the steps:

1) Open a console and navigate to the repository folder
2) Use `premake5` if you have it installed on your pc, otherwise `3rdParty/Binaries/Premake/YourOS/premake5`

For windows:
`premake5 vs2022` or `3rdParty/Binaries/Premake/Windows/premake5.exe vs2022`

For Linux:
`premake5 gmake` or `3rdParty/Binaries/Premake/Linux/premake5 gmake`

For Mac:
`premake5 xcode4` or `3rdParty/Binaries/Premake/macOS/premake5 xcode4`

## Pong [[SFML](#used-and-mentioned-libraries)]
A simple Pong clone made with C++20 and SFML 3.0.

The aim for using Pong as the first project was to get back into SFML as well as getting used to the new way of using it, quite a bit changed in their syntax. It will probably just stay as a pure pong clone without any new additions or twists.

## What is further planned?
I am planning on making a clone of "Snake" as well as "Space Invaders", perhaps a Tetris one too, but the last one depends on how confident I get with SFML 3.0 during "Snake" and "Space Invaders". Otherwise I can imagine going for a slightly bigger Project, be it something new or just giving one of these other projects a twist... idk like turn "Space Invaders" into a rogue-like where you can get upgrades because the enemies grow stronger and stronger.

### Further future considerations
I am not decided on this yet, but I could also try out other libraries instead of SFML 3.0 since SDL3.2 was released or Raylib 5.5 ([See Libs](#used-and-mentioned-libraries)). But that's something future me has to decide on :)

## Used and Mentioned Libraries
* SFML   3.0: [SFML Homepage](https://www.sfml-dev.org)
* SDL    3.2: [SDL Homepage](https://www.libsdl.org)
* Raylib 5.5: [Raylib Homepage](https://www.raylib.com)