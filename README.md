
# Table of Contents

1.  [Description](#org5faae63)
    1.  [What is a raytracer ?](#org860fb6e)
2.  [How to use it ?](#org5da5da8)
    1.  [Compilation](#org64ba708)
    2.  [What is a .rt file ?](#org892e464)
    3.  [What is the syntax of a .rt file ?](#orgb63c26e)



<a id="org5faae63"></a>

# Description


<a id="org860fb6e"></a>

## What is a raytracer ?

In computer graphics, raytracing is a rendering technique for generating an image by tracing the path of light as pixels in an image plane and simulating the effects of its encounters with virtual objects.


<a id="org5da5da8"></a>

# How to use it ?


<a id="org64ba708"></a>

## Compilation

1.  make
2.  ./miniRT <file.rt>
3.  You can also choose to save the image by adding &#x2013;save after the .rt file like : ./miniRT ./scenes/simple<sub>scene.rt</sub>. &#x2013;save


<a id="org892e464"></a>

## What is a .rt file ?

A .rt file is where all the informations about the scene you want to render are.


<a id="orgb63c26e"></a>

## What is the syntax of a .rt file ?

The first letters of each lines indicate what it is :
	R = Resolution of the screen
	A = Ambient light
	c = camera
	l = light
	sp = sphere
	sq = square
	pl = plan
	cy = cylinder
	tr = triangle

In order to work correctly, there must be at least a Resolution, an Ambient light and a camera in the file, and only one Resolution and one Ambient light

After the letters there are numbers.

R : number of x pixels of the window - number of y pixels of the window

A : intensity of the light [0.0, 1.0] - RGB colors [0, 255]

c : coordinates x,y,z - view direction [-1, 1] - field of view [0,180]

l : coordinates x,y,z - intensity of the light [0.0, 1.0] - RGB colors [0, 255]

sp : coordinates x,y,z - diameter - RGB colors [0, 255]

sq : coordinates x,y,z - orientation [-1, 1] - height - RGB colors [0, 255]

pl : coordinates x,y,z - orientation [-1, 1] - RGB colors [0, 255]

cy : coordinates x,y,z - orientation [-1, 1] - diameter - height - RGB colors [0, 255]

tr : coordinates x,y,z of the 1st point - coordinates x,y,z of the 2nd point - coordinates x,y,z of the 3rd point - RGB colors [0, 255]

