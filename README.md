# miniRT

<img width="1196" alt="Screen Shot 2022-09-20 at 2 30 27 PM" src="https://user-images.githubusercontent.com/68693691/194587193-9671ec6d-7bc8-4955-bbf3-352f2c8ceba9.png">


*A mini ray tracer using MLX42. Made with [Alfred Polycarpe](https://github.com/Alfredpoly).*

## Table of Contents
- [The Challenge](#the-challenge)
- [Implementation](#implementation)
	- [Parsing](#parsing)
	- [Setting up the Camera](#setting-up-the-camera)
	- [Rays](#rays)
	- [Sphere](#sphere-1)
	- [Plane](#plane-1)
	- [Cylinder](#cylinder-1)
	- [Lighting](#lighting)
- [Examples](#examples)
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

### Rays
```C
typedef struct s_ray
{
	t_vec4	orig;
	t_vec4	dir;
}	t_ray;
```

A ray needs to have both an origin and a direction.  When calculating a ray from the camera, the origin is the camera origin.  The direction is calculated as follows:
```
r.dir = cam.btm_left_cnr + (u * cam.horiz) + (v * cam.vert) - cam.orig
```
Where `u` is the `x` coordinate of the pixel relative to the image width, and `v` is the `y` coordinate of the pixel relative to the image height.

### Sphere
```C
typedef struct s_sphere
{
	t_vec4		center;
	float		radius;
}	t_sphere;
```
Using the quadratic equation the program determines wether or not the camera ray hits the sphere.  If the discriminant is less than zero it means the sphere has not been hit, but if it is greater than zero, it has been hit.  As a ray can intersect a sphere twice, the program checks both roots of the quadratic equation and stores the closest one to the camera as `t`.  `t` is then used to evaluate the normal, which is a normalized vector from the center of the sphere to the point where the ray hits the sphere.  This vector will be used later to determine the color of the pixel.

### Plane
```C
typedef struct s_plane
{
	t_vec4	point;
	t_vec4	vector;
}	t_plane;
```
A ray-plane intersection can be calculated using the following formula:

$t = \frac{(p - r_o) \cdot |o|}{|o|\cdot r_d} = \frac{(r_o - p) \cdot |o|}{|o|\cdot r_d}$

Where $p$ is the `point` on the plane and $|o|$ is the planes normalized orientation `vector`.

Again, `t` is then used to evaluate the normal, which later is used to calculate the color of the pixel.

### Cylinder
```C
typedef struct s_cylinder
{
	t_vec4	center;
	t_vec4	n;
	float	radius;
	float	height;
	float	angle;
	t_vec4	axis;
}	t_cylinder;
```

By far the hardest part of this project rendering cylinders.  While rendering them on the y-axis is not that complicated, once you start rotating them it becomes quite difficult.  We solved this by always rendering them along the y-axis and rotating the ray (or the scene) accordingly.

We split the rendering into several steps.

First we determine if the sphere is hit, and if it is, what part.  

The top and bottom intersections are rendered through creating a plane that uses the height and center as points, and the cylinders orientation as orientation.  We then send it to the plane intersection function, which determines if the plane has been hit.

The cylinder is rendered by first rotating the ray so that the cylinder is oriented along the y-axis using [Rodrigues' rotation formula](https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula).

As cylinders are essentially a lot of circles stacked on top of each other, as seen in the diagram bellow, we can use the quadratic equation to determine wether a cylinder has been hit. If the discriminant is positive then solve for the two roots, using the closest root as `t`.

<p align="center">
  <a href="https://github.com/maiadegraaf">
    <picture>
    <img alt="cylinder" src="https://user-images.githubusercontent.com/68693691/194762980-77af0098-d442-4e15-b3e4-113cbec11fd6.png" width=400>
    </picture>
  </a>
</p>

Considering the cylinder has been oriented along the y-axis, this also allows us to easily check if the point that has been hit is within the height parameter.

Using the determined `t`, the normal is then calculated using the original ray, which again, affects the color of the pixel.

### Lighting
```C
typedef struct s_lighting
{
	t_vec4	diff;
	t_vec4	spec;
	bool	if_s;
	t_vec4	shadow;
}	t_lighting;
```
We implemented the [Blinn–Phong reflection model](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model) for our lighting.  The diffuse light is calculated using this equation:
```C
l.diff = obj->color * intensity * light.diff_color * light.diff_power / distance;
```
Where the intensity is the dot product between the direction of the light and the normal.

We also implemented Phong specular light which adds a nice reflection on the object.

### Final Thoughts
This was quite a challenging project for me as I hadn't worked with a lot of the mathematical concepts before.  While programming is something that is pretty logical to me, the mathematical part of this project took me a lot longer to understand.  However this is what made the project really fun too as I was really trying something very different than what I am used to.  I was happy I got to work with Alfred again on this project as where I am somewhat lacking in the maths department, Alfred is quite strong, although I do feel like I make up for it in terms of my coding ability.

This project has a lot of different aspects to it, as well as many things that can be added to it, and one of the challenges was actually knowing where to stop.  As making a ray tracer was super interesting to me, I was tempted to really tackle the bonuses and go above and beyond however I am also cognizant that C is not necessarily the best language to write a ray tracer in.  We also have an opportunity later in the curriculum to build a far more powerful and full bodied ray tracer in our language of choice so I think I'll wait for that instead.

## Examples
<img width="1022" alt="Screenshot 2022-10-08 at 16 00 49" src="https://user-images.githubusercontent.com/68693691/194775115-7ad64ac2-eb06-42ca-84c9-a131a64424e3.png">
<img width="614" alt="Screenshot 2022-10-08 at 16 20 50" src="https://user-images.githubusercontent.com/68693691/194775119-16b6d966-b931-442d-a6c2-38fe095e81bf.png">
<img width="614" alt="Screenshot 2022-10-08 at 16 20 50" src="https://user-images.githubusercontent.com/68693691/194775157-acc95a2a-86d0-461c-928b-6b9dc951f71d.jpg">

## Installation
### Clone the repository:
``` 
git clone https://github.com/maiadegraaf/minirt.git
cd minirt
make
```

### Antialiasing
We also implemented antialiasing which makes the rendered images a lot sharper.  To turn antialiasing on run:
```
make anti
```
Note: Images take a lot longer to render with antialiasing turned on.

### Run
You can run the program with any of the maps in the `/rt_maps` directory like so:

```
./minirt rt_maps/cake.rt
```

You can also make your own map using the information provided above.