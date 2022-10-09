# miniRT

<img width="1196" alt="Screen Shot 2022-09-20 at 2 30 27 PM" src="https://user-images.githubusercontent.com/68693691/194587193-9671ec6d-7bc8-4955-bbf3-352f2c8ceba9.png">


*A mini ray tracer using MLX42. Made with [Alfred Polycarpe](https://github.com/Alfredpoly).*

## Table of Contents
- [The Challenge](#the-challenge)
- [Implementation](#implementation)
- [Installation](#installation)

## The Challenge
The goal of miniRT is to create a basic ray tracer that can implement 3 simple geometric objects: **plane**, **sphere**, and a **cylinder**.  The intersections between each object has to be handled correctly, as well as the inside.  The objects as well as the camera and lights should be able to be transformed and rotated (with the exception of the sphere and light which cannot be rotated).  The ray tracer needs to incorporate light, with adjustable spot brightness, hard shadows, and ambiance lighting.  The ray tracer needs to be able to read a `.rt` file which contains information pertaining to the objects, lights, and camera.

## Implementation
This project was quite different from all the projects I had worked on previously as it was very math heavy, which was quite new to me.  So we started by following [this](https://raytracing.github.io/books/RayTracingInOneWeekend.html) tutorial which introduced us to the basic concepts such as the camera and spheres, and all the nitty gritty stuff like vectors, which I had never worked with before.

As vectors form a large part of the calculations in this project we decided to use [``__attribute__ ((vector_size (16)));``](https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html), a GNU library that includes basic math operations such as addition, subtraction, division, and multiplication.  This greatly simplified our code and made it much more readable.  It also meant we didn't have to make a whole library of vector math functions.

### Parsing
The first thing our program does is read from the `.rt` file it receives as argument.  Then using `get_next_line()` it reads through the file line by line. 

The map must follow the following rules:
- Each element is separated by one or more line break(s).
- The element's information is defined on one line and can be separated by one or more space.
- The elements can be defined in any order.
- Elements with a capital letter can only be declared once.

The elements are defined as follows:
##### Ambient:
```
A  0.2  255,255,255
```
- **A**: identifier
- **0.2**: Ambient lighting ratio in range [0.0,1.0]
- **255,255,255**: R,G,B colors in range [0-255]

##### Camera
```
C -50.0,0,20   0,0,1   70
```
- **C**: identifier
- **-50.0,0,20**: x,y,z view point coordinates
- **0,0,1**: 3d normalized orientation vector, in range [-1,1] for each x,y,z axis
- **70**: Horizontal field of view in degrees in range [0,180]
  
##### Light
```
L -40.0,50.0,0   0.6   10,0,255
```
- **L**: identifier
- **-40.0,50.0,0**: x,y,z light point coordinates
- **0.6**: light brightness ratio in range [0.0,1.0]
- **10,0,255**: R,G,B colors in range [0-255]

##### Sphere
```
sp   0.0,0.0,20.6   12.6    10,0,255
```
- **sp**: identifier
- **0.0,0.0,20.6**: x,y,z sphere center coordinates
- **12.6**: diameter
- **10,0,255**: R,G,B colors in range [0-255]

##### Plane
```
pl   0.0,0.0,-10.0   0.0,1.0,0.0   0,0,225
```
- **pl**: identifier
- **0.0,0.0,20.6**: x,y,z coordinates
- **0.0,1.0,0.0**: 3d normalized orientation vector, in range [-1,1] for each x,y,z axis
- **10,0,255**: R,G,B colors in range [0-255]

##### Cylinder
```
cy 50.0,0.0,20.6   0.0,0.0,1.0   14.2    21.42   10,0,255
```
- **cl**: identifier
- **50.0,0.0,20.6**: x,y,z bottom center coordinates
- **0.0,0.0,1.0**: 3d normalized orientation vector, in range [-1,1] for each x,y,z axis
- **14.6**: diameter
- **21.42**: height
- **10,0,255**: R,G,B colors in range [0-255]

The parser was quite simple to make, but it also had to account for a lot of edge cases and user error which was some what challenging to deal with.

Essentially as it reads through each line it checks what the first character is, and handles it appropriately.  As the objects and attributes are clearly defined, it makes it easy to read through the line and store the information in the correct variable using helper functions to convert the floats and vectors.  At this point, the diameter of the cylinder and sphere is converted to a radius as this is ultimately more useful later in the program.  The angle and axis of the cylinder is also calculated at the parser stage.

As the camera, light, and ambient light can only be declared once in the scene, the parser throws an error if multiple are declared.  Further if there is no camera, the program also sends an error and exits the program.  However the scene is missing an (ambient) light or objects, it sends a warning but still renders the scene.

### Setting up the Camera


![minirt 001](https://user-images.githubusercontent.com/68693691/194758372-dec2ea14-02f2-48d9-b485-7d79efbc43ee.png)
![minirt 002](https://user-images.githubusercontent.com/68693691/194758374-027f5848-a486-4b55-90e7-da7bb58dd3b8.png)

As each ray is calculated based upon the bottom left corner of the camera, this is an important coordinate vector that is determined during the parsing stage using the following formula:

$x = C - \frac{w\cdot\overrightarrow{|r|}}{2} - \frac{h\cdot \overrightarrow{|u|}}{2} + |o|$

Where:
- $x$ is the bottom left corner
- $C$ is the camera origin
- $w$ is the viewpoint width
- $|r|$ is a normalized orientation vector facing right
- $h$ is the viewpoint width
- $|u|$ is a normalized orientation vector facing up
- $|o|$ is the normalized orientation of the camera

The graphics above shows how we found this formula.

Other important information that is stored is the camera origin, a horizontal vector $w\cdot\overrightarrow{|r|}$, and a vertical vector $h\cdot \overrightarrow{|u|}$.  These four variables (including the bottom left corner) allows us to calculate a ray for each pixel in the scene.

A ray 

### Sphere
### Plane
### Cylinder
### Lighting

## Installation
### Clone the repository:
``` 
git clone https://github.com/maiadegraaf/minirt.git
cd minirt
make
```

### Run
You can run the program with any of the maps in the `/rt_maps` directory.

```
./minirt rt_maps/cake.rt
```

You can also make your own map.