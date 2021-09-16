#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(SimpleHE)

set(CMAKE_MODULE_PATH
	${Geant4_DIR}/Modules/
        ${CMAKE_MODULE_PATH})

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#include (FindROOT.cmake)
find_package(ROOT REQUIRED)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
#include(FindROOT.cmake) 
set(INCLUDE_DIRECTORIES                                                                      
	        ${ROOT_INCLUDE_DIRS}                                                                    
)                                                                                            
		                                                                                             
include_directories( ${INCLUDE_DIRECTORIES})                                                 
		                                                                                             
set(LINK_DIRECTORIES                                                                         
	        ${ROOT_LIBRARY_DIR}                                                                    ) 

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(simpleHE.exe simpleHE.cc ${sources} ${headers})
target_link_libraries(simpleHE.exe ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} 
"/cvmfs/sft.cern.ch/lcg/external/ROOT/5.34.23/x86_64-slc6-gcc49-opt/root/lib/libRIO.so" 
"/cvmfs/sft.cern.ch/lcg/external/ROOT/5.34.23/x86_64-slc6-gcc49-opt/root/lib/libHist.so"
)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(SIMPLEHE_SCRIPTS
  init.mac
  init_vis.mac
  vis.mac
  )

foreach(_script ${SIMPLEHE_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(SimpleHE DEPENDS simpleHE.exe)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS simpleHE.exe DESTINATION .)


