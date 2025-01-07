This engine uses Composition and Inheritance.

Everything in the game scene is a node (Technically the game scene is also a node, just a root singleton node!).

Node Types:
* Node has a parent, enum type, list of children, and override-able Update method (in the future I would like to have a simple "scripting" system where nodes instead store a reference to a user defined function).

* Node3D inherits Node but has transform data and methods.

* Mesh3D inherits Node3D but with reference to MeshData and a Draw method.

* Camera3D inherits Node3D but with camera values like FOV, Aspect, and near and far planes. It also has the function to update the projection matrix.

* Timer inherits Node (doesn't need transform info). This is a pretty standard timer. It has autostart, oneshot, wait time, along with a timeout function pointer.

* Animator inherits Timer but has a Node3D to animate along with AnimationData.

Of note, libnds does not allow dynamic_cast, therefore a decent chunk of polymorphism doesn't work as intended. This could be fixed by creating a custom RTTI.

Data Types:
* AnimationData
* MeshData
* TextureData
These are pretty self-explanatory, nothing crazy here. But the AnimationData is pretty fun! It uses Keyframe structs to store transform data and interpolates between said keyframes.

There are a couple Engine singletons (and static classes, just for fun really. I might want to go back and change them all to be singletons. I just like not having to call GetInstance() for every single method that doesn't need it.)
Singletons / Static Classes:
* Debug: Not fully complete, line rendering is WIP, but the quad renderer works!
* Input: I'm quite proud of this little system! You can bind and unbind and add delegates to keycodes and names.
* Renderer: Handles all the rendering.
* Time: Uses hardware timers to calculate deltaTime. Mostly used for the Timer node.

The main gameloop uses a sort of hook system, very little code in the main function is Engine code, mostly that should just be user code.


Given more time, these are the things I'd like to work on:
* Fixing Rendering to be more performant (including cullings)
* Add in a simple way to switch scenes (+ add in scenes)
* Update all OpenGL calls to use the proper NDS calls.
* Clean up all the data types to be more consistent and performant (including packing values together).
* Fix naming conventions over all the code.
* Fix const correctness.
* Make the inheritance between Nodes more clear on the code side (virutal keywords, abstract, override keywords)
* Fix the folder structure so it isn't all just one folder (perhaps a Node folder, user folder for custom scripts, engine folder)
* Add in the lighting and not fixed vertex color system.
* Add in the audio system
* Update the input system to support touch screen.
* If I was to update the polymorphism system, I would consider using a bitmask to represent parent classes.
* Optimize Vertex data.