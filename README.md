# QtSingleInstance
## Description
This is a short example on how to create a qt based single instance application cross-platform.
It works by creating a TCP Server on a predetermined port. If this port is already taken, we
assume that an instance of the application is already running.

Please note that this is just meant as a short example to show how such a problem could be solved;
you could use this if you quickly want to prototype something, but in production you should
utilize Mutexes, pid files or whatever else is suited for your platform.

## Depdencies
* Qt5, modules core and network
* cmake (or use qmake)

## Compiling
    mkdir ../build
    cd ../build
    cmake ../QtSingleInstance
    make

## Running the example
Run the application once. It should create the server and wait for messages:

    $ ./qttest
    This is the only instance.
    Waiting for messages...

Now, while this instance is running, switch to another terminal and run it again:

    $ ./qttest
    Other instance reacted nicely.

The first terminal's output should now look like:

    $ ./qttest
    This is the only instance.
    Waiting for messages...
    Got a message:  "RESTORE"

(The RESTORE message is just an example; it could be used to ask the main instance
 to restore a minimized window, if it is a gui application).

