# PicturePerfect

1.Install CMake plugin in visual studio code.

2.Install vcpkg (https://vcpkg.io/en/getting-started.html)

3.View -> Command Palette -> Open User Settings (JSON)

4.Add


"cmake.configureOnOpen": true,

"cmake.configureSettings": {
  
  "CMAKE_TOOLCHAIN_FILE": "[Path to vcpkg]/scripts/buildsystems/vcpkg.cmake"

}


Final settings json file should look like something similar to

{
    
    "go.toolsManagement.autoUpdate": true,
    
    "cmake.configureOnOpen": true,
    
    "cmake.configureSettings": {
        
        "CMAKE_TOOLCHAIN_FILE": "D:/Workspace/vcpkg/scripts/buildsystems/vcpkg.cmake"
    
    },
    
    "redhat.telemetry.enabled": true

}


1.Build the project using CMake plugin (pick a kit when prompted)

2.Run filters project using CMake plugin

b) In order to build the project using command line:

https://vcpkg.io/en/getting-started.html







