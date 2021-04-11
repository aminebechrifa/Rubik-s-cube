# Rubik-s-cube
<h1>The First Menu :</h1>
<p>This is the very first interface of the game, also the first
impression one will have. This menu has the name of the game
and shows a Rubik's cube with an animation as well as 2
buttons offering the possibility to start a new game or resume
an old one.</p>
<br><br>
<h1>The Second Menu :</h1>
<p>This second menu offers the possibility to choose a theme for
the Rubik's cube one will be playing. The menu contains a title
as well as an explanation and 4 buttons containing the name
of the theme. All of these are loaded as a texture that have
been designed using PAINT 3D. Each button is put under a
small cube turning on itself to show the images on its faces.<br>
Again the cube is put on an angle that allows to see most of the faces. This particular cube is
not composed of the habituel 57 small cubes but is an individual one. The 4 themes available
are namely colors (The classic one), the planet Earth with all the continents, singers and
animals
<br><br>
To choose the theme, one can click on the button or directly on the Rubick’s cube using the
mouse. This is done in a similar manner to how the previous buttons are done, by delimiting
their area, storing it in variables and comparing it to the mouse position. To add realism to the
game, when one moves the mouse on one of the 4 cubes, they become bigger and allow to
show to the user that they are touching it. This is done by comparing the position of the cursor
and the one of the cube in the window and if they match, the cube is scaled up and then
rescaled down once the cursor is no longer there.
Once the cube or button clicked one has access to the game
<br><br>
<h1>THE GAME</h1>
<p>Once one has chosen the theme of the Rubik’s cube, the
user is directed to the final scene.<p><br>
<h3>The Decor of the Game :</h3>
<p>Half of the scene is made for the buttons and the timer as well
as the helper board containing the 6 images of the rubik's
cube. The rest of the scene contains a background in front of which the Rubik's cube is put
along with its arrows</p>

<h3>The Timer:</h3>
<p>One important element of the decor is the timer. This timer counts the seconds while the user is
playing. 4 buttons are available to control this timer. These buttons can be clicked using the
mouse. The user can then choose when to start the game by clicking on the START button.The
START button also reset the cube at its initial position. The user can also stop the counter by
clicking on the STOP button. After clicking Stop one will need to resume the timer to continue
playing. This is offered by the button RESUME. One can also restart the timer from the
beginning by clicking RESTART.<br>
The timer on itself is made out of 9 images containing the numbers from 0 to 9 . These images
are mapped to 4 squares put inside the decor . Depending on the count of the second and
minutes, the right texture is then mapped and rendered. A function was then created to do this
more conveniently . This function takes the path of the texture and loads it and binds it. For
simplicity the images were also named from 0 to 9 .<br>
<h3>The Helper Board with the Audio feature and Color Light Change:</h3>
<p>The part of the decor is a kind of a board that contains the 6 pictures of the faces that one is
trying to assemble. This then helps in the resolution of the game
In addition to its function of helping the user in resolving the game, this picture offers in certain
of the themes some extra funny features. In fact, when one chooses the theme of the singers ,
by clicking on the picture of one of the singers, he will launch a song of that singer.
Similarly if one chooses the animal's theme, by clicking on the animal one will get the sound
that that animal does (after waiting very few seconds). By choosing the theme of the colors,
when one clicks on one of the colors , the light of the scene will change and become the same
color.</p>
<br>
<h3>The Buttons Related to the Game [Shuffle, solve, home]:</h3>
<p> Buttons available are related to the solving of the game:<p>
<h4>The Shuffle Button:</h4>
<p>This button can be clicked using the mouse and allow the user to randomly scramble the
Rubik's cube at any time during the game while seeing the animation . This is done by
rearranging the positions of the small cube that constitute the rubik's cube randomly . To do this
we randomly generate numbers that will correspond to an axe a direction and a level , these
parameter will then be used to activate a function that will twist a random part of the cube .While
rearranging the position of the cubes , the animation of the turning face in different direction is
also done to add realism to the game.</p>
<h4>Solving the Game Button :</h4>
<p>This button allows the user to click on it using the mouse and allows them to see the Rubiks
cube being resolved starting from the position of the cubes that the user let them in . An
animation is created to see the cube being arranged starting from the configuration put by the
user . The solving is done by going through an array where movement the cubes are subjected
to are stored . The function goes through the array in reverse and execute each movement in
the opposite direction stored thus sorting the cube</p>
<h4>The Exit button :</h4>
<p>This button is to be clicked using the mouse, it redirects the user to the second menu where he
can choose another theme.</p>
<h4>The Rubik's Cube :</h4>
<p>The cube itself is created by 57 small cubes .
A class has been created for the Rubik’s cube as a whole and a second for the small cube
composing it.
Each small cube holds its own information about its direction as well as his 3d position. This
help us control the moves.
All the small cubes have been organised in an array. Their indexes are known and help control
them.</p>
<h3>Mapping the faces of the rubik's cube :</h3>
<p>The images to be loaded have been chosen to be square so that they fit perfectly. They next
have been cropped into 9 pictures so that each one will be mapped on one of the small cubes.
The cropping has been made using Paint 3d. The mapping is done thanks to the indexes of the
small cube in their array.</p>
<h3>The Movement and its animation :</h3>
<p>Moving the mouse while clicking the right button only moves the rubik's cube around its center.
The right button is needed to click on the buttons.</p>
<h3>The Arrows :</h3>
<p>Two arrows have been modeled to facilitate visualising and controlling the movements of the
cube. These arrows have been modeled using cubes. They follow the direction of the cube and
each one is able to move in a particular axis using the keyboard. The left/right arrow control the
arrow on the top of the cube and the WASD control the arrow on the left of the cube. While
pointing to a location, an arrow allows to show in which direction the next move is possible. The
actual movement of the face will be possible according to the arrow position using the G, H to
rotate along the y axis (positive and negative). Also J and K keys rotate along the Z axis and N
and M to rotate along the X axis. These arrows also allow one of the very first things that have
been learnt in the course that is the modelisation of the models.</p>
<h3>Loading the textures and binding it :</h3>
<p>The project requires loading a huge amount of images . In fact , each time it is required to write
a text, an image has been loaded. In addition, while we have 4 possible cubes , each cube
requires 54 images to load. To facilitate the loading of the images, a convention has been
created to name the images . In fact the name contained the position of the image compared to
the whole cube so that it can be mapped easily. Also for these reasons a function has been
created that takes the ID of the texture as an input and it creates the texture and binds it . Each
time it is needed to bind a texture, the simple function is then called.</p>
<h3>Adding realism:</h3>

<p>A small imperfection in the movement of the cubes have been added to add realism to the cube.
In fact, while playing Rubik's cube in real life, one spent a long time trying to put all the cubes in
a perfect line . This has been taken here and simulated to add realism to the game. This is done
as follow: instead of rotating by 90 degrees making a perfect twist, we increment the rotation
value only about 88.5 degrees. In the next rotation we are doing, we add the 1.5 degrees left.</p>

<h3>The Camera :</h3>
<p>The camera has been locked and the cube has been made big so that one doesn t need to tilt
and pan. The mouse is instead used to rotate the cube around its center.</p>

<h3>The Light and Shadows :</h3>
<p>The fong model have been followed and everything was rendered in 2 a pass rendering to
create the shadow</p>
<h3>Finishing the game And some Additional Features :</h3>
<p>When one finishes the Rubik's cube, there are some cases where there is something that
happens. For instance, when one is playing with the rubik’s cube with the animals one can see
the model of that animal appearing. These animals are in reality 3d object that have been
loaded and textured.<br>
Also finishing the world rubik's cube, one can see the planet earth
appearing and taking the place of the rubik's cube

