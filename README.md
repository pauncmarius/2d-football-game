# 2d-football-game (dropped)
C++, Qt, OpenGL

This game is a simple 2D game on a single stage, using the Side View perspective. The game focuses more on the physics part because it is there that the core of the gameplay lies. Here, we can simulate various interactions with the ball and its movements to create a realistic experience. Although graphical effects can be added later, the primary goal is to make the game smooth and fair.

The game scene is based on an image:
![image](https://github.com/user-attachments/assets/5f0c6f91-94bb-404c-b2cc-a6dae3a0c85f)

As you can see, the scene already has the goals drawn. To enhance realism, I decided to make the player appear semi-transparent when they are in the goal area, ensuring they do not render over the goal. This transparency effect applies to both the ball and the player.

![image](https://github.com/user-attachments/assets/929cbb5c-8b43-4a12-b070-b5f2f90cccec)

Animations were created for the ball; for example, it rotates when in motion. Different states with corresponding animations were also made for the player to enhance realism. A small gravity simulation was implemented for the ball at the beginning of the game, causing it to draw upward and then simulate falling and bouncing until it comes to a stop, losing speed with each hit. Regarding the physics, we have managed to make the player carry the ball left and right upon contact.

I have documented the code extensively with comments in important areas. Below is a brief description of each class and its implementation.

### Texture Class
Used to load textures from files and use them in OpenGL. QImage was utilized to extract necessary information for the image to be used in shaders.

### Shader Class
Used to create the shader program for each game object using OpenGL. We utilized Qt classes such as:

#include QMatrix4x4,
#include QVector2D,
#include QVector3D,
#include QVector4D,
to correctly set the uniforms in the shader.

### Shadow Class
Simulates the shadow of the player and the ball. This shadow is a circle made of several triangles, flattened to appear as if it is under each object, becoming more transparent as the object moves away from the ground to simulate reality.

![image](https://github.com/user-attachments/assets/7d2066f0-bd78-4f5f-af9e-18584a903510)

### Player and Ball Classes
Contain all details about shaders, animations, physics, and other related functionalities.

### Background Class
Handles the rendering of the game background.

### DebugRectangle Class
Allows visualization of the physical boundaries for the goal, player, and ball during collisions and other interactions.

### glWindow Class
Responsible for creating and managing the OpenGL window within the application framework, deriving from QOpenGLWidget and QOpenGLFunctions_3_3_Core. It includes everything related to game creation and class usage for an optimal game loop. Qtimer is used for this, and QKeyEvent for managing keystrokes used in the game.

So far, this is the progress I have made. Although there is repeated code and room for optimization, I am pleased to have something functional. For now, the project is on hold, but I plan to return to it in the future. My goal is to complete the physics aspect to make the game as realistic as possible. Once that is achieved, I will add a timer and a scoring system to give the game a proper structure.
Thank you for your time!
