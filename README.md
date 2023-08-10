# VisionPluginLibrary
This plugin enables edge inferencing using a third-party AI SDK.

# Procedure

1. Complete the stub functions in Vision.cpp and update the CMakeLists.txt with the linked libs.
2. Compile your libacvisionplugin.so using the build.sh script.
3. Pack your libacvisionplugin.so with the AI model and compress the package (.tar).
4. Upload the compressed AI model package to the AnyConnect Dashboard and create an AI model entry.
5. Create an AI Container using the AI model entry and deploy it to the Smarter AI devices.


# What’s Included

- README		Instructions to complete the Vision.cpp stub functions and compile and use libacvisionplugin.so.
- Vision.h		Vision library header file.  This derived class overrides VisionPlugin base class member functions.
- Vision.cpp		Vision library source file.  You must complete the stub functions.
- VisionPluginTypes.h The data types class for the vision objects.
- VisionPlugin.h	These base class member functions are overridden by Vision derived class.
- CMakeLists.txt		Compiles libacvisionplugin.so.
- build.sh       Script to build all.
- test/Test.h		Test application header for libacvisionplugin.so.
- test/Test.cpp		Test application source for libacvisionplugin.so.
- test/Makefile		Compiles the test application.


# What’s Required

### Software packages:
- Linux
- cmake 3.1
- dl library
- pthreads library 
- gcc/g++ version 7.x or higher




# How to complete the Vision.cpp stub functions
- initPlugin() // Code to initialize the plugin library
- deInitPlugin() // Code to de-initialize the plugin library
- setNetworkModelsFilePath() // Set the AI model directory path
- feedMediaData() // Feed the media (audio, video) data from the device for inferencing and getting the results.
- feedSensoryApparatusData() // Feed the sensor data in JSON format.


# How to compile your VisionPlugin Library.

Compile your libacvisionplugin.so by typing “build.sh” from the VisionPlugin root directory.


# How to test your VisionPlugin Library.

Compile the test application by typing “cd test/ && make all”.  This will generate a test application called “visionplugintest”.  Copy the libacvisionplugin.so to the test/ directory and run the test application by typing “./visionplugintest”.  

If successful, the test application will print “Your AnyConnect Vision plugin loaded!”.  If not successful, the test application will print “Your AnyConnect Vision plugin is not loaded.”.
