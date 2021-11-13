<h1 align="center">Cub3D - 21 school project</h1>

# Final grade 105/125

Mandatory part: 100/100 \
Bonus: 5/25

## About
This project is inspired by the game Wolfenstein 3D. World famous, Wolfenstein 3D is considered to be the first FPS (first person shooter) ever developed. \
The objective is to make a dynamic view in a labyrinth with a "realistic" 3D graphic representation.
This project allows to explore the technique of ray-casting using MLX library.

## Demonstrarion

<p align="center">

<img src="https://github.com/yaksaer/images-vault/blob/master/cubgif.gif?raw=true" width=700>
</p>

## Installation
Compatible MacOS with OpenGL
1. Clone this repo
`git clone git@github.com:yaksaer/cub3D.git`

2. `cd` into the directory and run `make` \
        `cd cub3d` \
        `make`\
3. After building run `make run` from the project root. 

For extended version of the project run `make bonus` and then `make runb` \
`make bonus` \
`make runb`

## Control

`WASD` - to go forward, left, back and right

`<-` `->` - to change point of view to the left or to the right

`ESC` or `red cross` - to close the porgramm

## Available options

There two "Map" files in map folder. You can change texutures for walls and sprites there. Also you can change map there but remember: `1` - is for wall,
`2` - is for sprites, `N` `W` `E` `S` - is for player.
