## Wireframe 3D - Landscape modeling with X-Window
The program displays a given `.fdf` map using 3D wireframe representation.
It leverages 42's graphical library [minilibx](https://github.com/42Paris/minilibx-linux).


### Install and run
This program only runs on MacOS, due to the `minlibx` OS-specific dependency attached. To work correctly, it also requires OpenGL: if you don't have it yet, please install it.

```bash
brew install opengl
```

Once you've taken care of this, simply run `make` in the project folder to generate the executable. To launch the program, use the following command with a map of choice:

```bash
./fdf assets/maps/pyra.fdf
```
<br>

![pyra.png](https://github.com/richim96/42-fdf/blob/main/assets/screenshots/pyra.png)

<br>

-----
**Keep in mind, the bigger the map, the less details you will be able to see!**
<br><br>
![pylone.png](https://github.com/richim96/42-fdf/blob/main/assets/screenshots/pylone.png)

<br><br>
![france.png](https://github.com/richim96/42-fdf/blob/main/assets/screenshots/france.png)
