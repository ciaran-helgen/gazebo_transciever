## Build
CD into the cloned build folder and run cmake ../ && make

Make sure to add the built library to your plugin path, e.g.

export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:~/gazebo_transciever/build


Run demo with gazebo <path/to/wireless.world
or gazebo --verbose <path/to/wireless.world
