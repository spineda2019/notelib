# notelib
This is a pet project to make a nice note taking app. I have found notetaking
to be a very important but underappreciated and underutilized tool in the tech
world. I am a minimalist at heart, so while I do love tools like notion, it
just has too many moving parts to my liking.

This project will be built using Qt 6 and largely C++20 (if I get up to speed
on 23 in time, I may use features for that here too).

## Building
In proper Windows fashion, this project can be built, but not as easily as on
linux. To build from source on windows, you will need:

* Qt6
* CMake
* Visual Studio Build Tools
* Ninja

Then run:

```.ps
cmake -B build -G "Ninja" -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_CXX_FLAGS:STRING="-DQT_QML_DEBUG"
```

On Linux, this exact same command will work (and you can pick a different
generater like Make if you'd like). However (and I am unsure and still need to
check) just specifying your desired build directory with <code>-B build</code>
will work smoothly and default to make. Then you can build with:

```.ps
cmake --build build
```

or with:

```.ps
cmake --build build --config Release # Or Debug if you desire
```

If you did the simple generation with make.

