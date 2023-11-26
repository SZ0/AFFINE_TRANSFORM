I use CMake to support building on different platforms, but did not test it on Windows.
Tested on:
- DEBIAN 9.4

(NOTE: If you will try different ways to build, I recommend deleting the 'build' folder betwen them.)


################## TO BUILD WITH VISUAL STUDIO ON WINDOWS: ##################
LAZY WAY:
- Have Visual Studio 2017 installed,
- double click the file: 'MakeScriptVisualStudio2017.bat' and 
- press 'F5' (after Visual Studio loads).
If it worked, this happened: bat ran CMake creating a Visual Studio 2017 solution and opened.
(NOTE: I only had access to Visual Studio 2017, but I added (DISCLAMER: and did NOT test) 'MakeScriptVisualStudio2012.bat' and 'WindowsMakeScript.bat' to see if you can avoid installing Visual Studio 2017.)

THE WAY INTENDED:
- Download latest graphical CMake from here: https://cmake.org/download/
- Run CMake.
- Point the 'Where is the source code' to the folder containing the top level CMakeLists.txt (the 'SOURCE' folder).
- Point to 'Where to build the binaries' to some empty folder (eg. 'SOURCE/build') folder.
- Press configure. A window will pop up.
- In the new window for 'Specify the generator for this project' pick a 32 bit Visual Studio version (tested working on Visual Studio 15 2017).
- Leave the 'Use default native compilers' radio button clicked and press the Finish button.
- Wait until 'Configuring done' is prompted in the output panel below the Configure button.
- Repeat pressing Configure after 'Configuring done' is prompted until there are no more red options in the central panel. (Only one more time should do.)
- Press Generate and wait for 'Generating done' to be prompted below.
- Press the Open Project button (or you can find the generated Visual Studio solution in the build folder you specified).
- The Visual Studio solution will contain three projects, build the 'AffineTransform' project and run it. This should start the program.


################## TO BUILD WITH MAKE ON LINUX MINT 18.3 or DEBIAN 9.4: ##################
LAZY WAY:
- Make sure you have graphics card drivers installed and up to date.
- Open a command-line interface and 'cd' to inside the 'SOURCE' directory.
- Run './linuxMakeScript.sh' (without quotation marks). (If you can not run this file, run 'chmod +x ./linuxMakeScript.sh' first.)
- Type in your password and press ENTER to allow the script installing cmake, g++, various libraries and their dependencies.

INFORMED WAY:
- 'cd' to 'SOURCE' directory.
- Run: 'cmake . -Bbuild'
- Run: 'make -C build'
- Run the program with: './build/AffineTransform'
(NOTE: You can also use the graphical cmake: cmake-gui, if not installed yet, use: "sudo apt-get install cmake-gui", then follow the same steps as for Windows, but use the default generator instead of picking Visual Studio 2017 and run make in the build directory.)
