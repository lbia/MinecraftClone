# MinecraftClone

#### Minecraft clone created with C and OpenGL

## Build

```
git clone https://github.com/Cubik22/MinecraftClone.git
cd MinecraftClone
mkdir build
cmake -S . -B build
# or if you are using a languge server
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B build
cd build
make
./Minecraft
```

## Instructions

Wait for the program to load the world

Use 'w', 's', 'a', 'd' keys to move, 'space' to jump

Hold 'ctrl' to run

Hold 'shift' to shift (not falling from blocks)

Hold left mouse button to remove block

Press right mouse button to place block

Scroll the mouse wheel to change block to be placed

Press 'p' and then right mouse button to plant tree

Press 'c' to enter flying mode, 'v' to return to normal mode

When in flying mode press 'space' to go up, 'alt' to go down

To close the window press 'esc'
