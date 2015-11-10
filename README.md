# Conway Invaders

"The most awesome crappy space invaders knockoff evar. Fer serious."

## Build Instructions

Source code is in the src/ directory. There is a makefile there. Nothing should
be required besides OpenGL and GLUT. Once you've built the game, run the
`invader` binary.

### Linux

You need Freeglut3, including the headers. Your distro probably has a "dev"
package of some sort. One Debian just do `apt-get install freeglut3-dev`.

    $ cd src
    $ make

### Mac OS

You must have XCode installed for this to work.

    $ cd src
    $ make

