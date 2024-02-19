# Conway's Game of Life
## Prerequisites
- cmake
- freeglut3-dev
- opengl

## Building
### Debug
From the root of the project, run the following command:
```bash
cmake --build build --config Debug --target all --
```

### Release
From the root of the project, run the following command:
```bash
cmake --build build --config Release --target all --
```

## Installing
### Debug
From the root of the project, run the following command:
```bash
cmake --build build --config Debug --target install --
```

### Release
From the root of the project, run the following command:
```bash
cmake --build build --config Release --target install --
```

## Running
From the root of the project, run the following command:
```bash
./install/bin/conways_game_of_life
```

The initial state of the board is paused. This allows the user to select cells to start as "alive".  
Mark cells as "alive" using the left mouse button and mark cells as "dead" using the right mouse button.  
Once the board is in a good starting state, press the spacebar to toggle animation.  
You may press space bar at any time to start/stop animation and modify the board state.  

Pressing "c" on the keyboard will clear the board and reset all cells to "dead".  
This can be done either while the animation is running or while it is paused.  

Using the up and down arrow keys, you can increase and decrease the animation speed respectively.  
The starting framerate is 10 FPS and the min and max frame rates are 1 and 170 FPS respectively.  
The frame rate will increase/decrease in steps of 10 FPS.  

There is a known bug that I didn't feel like fixing where if you lower the FPS all the way to 1 FPS, once you start increasing the FPS again  
it will continue in increments of 10. With the min framerate being 1, this will make subsequent framerates of 11, 21, 31, etc.  
In other words, this adds an off-by-one error to the FPS. With the difference between 10 and 11 FPS being so small and with the actual framerate not  
exactly matching the set framerate, I didn't see a need to fix this issue. Additionally, if the framerate is increased to the maximum, the off-by-one error  
is removed again until the framerate is dropped to the minimum again.