# tinypixels

basic CPU renderer written in C with raylib. simulates the graphics processing pipeline but on the CPU. so it is very slow.

## Features

- load and display obj models
- simulates vertex shading, rasterization in CPU
- can perform projection, translation and rotation around axes
- depth buffer testing

## Built With

- uses raylib to create window and for vector operations
- vertex shading, rasterization and final drawing is done by us

## Limitations
- it does not use the GPU, so it is extremely slow
- obj file parsing breaks when face format is different
- only support for 3 order faces
- fixed buffers for storing vertices and triangles - it can break if the model is too large
