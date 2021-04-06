	This is a simple raytracer.

	What is a raytracer ? 
In computer graphics, ray tracing is a rendering technique for generating an image by tracing the path of light as pixels in an image plane and simulating the effects of its encounters with virtual objects.

	How to use it ?

First of all, compil the programm by using the command make.
Then use the executable miniRT and choose a .rt file in the scenes folder like : ./miniRT ./scenes/simple_scene.rt.
You can also choose to save the image by adding --save after the .rt file like : ./miniRT ./scenes/simple_scene.rt. --save

	What is a .rt file ?
A .rt file is where all the informations about the scene you want to render are.

	What is the syntax of a .rt file ?

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

	Features :

You can moove the camera with the arrows and zoom with the mouse scroll.
You can switch to the next camera with the key A and reset with Z.