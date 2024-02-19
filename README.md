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