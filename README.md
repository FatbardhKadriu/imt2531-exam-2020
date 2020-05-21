# IMT2531-Exam
Repository for the exam deliverables to IMT2531 - Graphics Programming

![picture](resources/textures/photo2.png)

## How to setup

Make sure you have [cmake](https://cmake.org/) version 3.14 or later installed.
Navigate to the root folder of the project and execute the following commands

On linux:
```
mkdir build
cd build
cmake ..
make
./Pacman3D
```

On windows:
```
mkdir build
cd build
cmake ..
cmake --build .
cd ..
cd out/build/x64-Debug
Pacman3D.exe
```

## Controls

W - Move player forward

A - Move player left

S - Move player backwards

D - Move player right

T - Switch between first-person, third-person and top down view(bird view)

LShift - Sprint

Esc - Exit the game

Arrow keys - Navigate the menu

Space - Make a selection in the menu

