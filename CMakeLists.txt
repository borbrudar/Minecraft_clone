cmake_minimum_required(VERSION 3.16.0)
if(WIN32)
    #default install path, so no spaces
    set(CMAKE_INSTALL_PREFIX C:/ CACHE PATH "default path" FORCE)
endif()
set(PR_NAME Minecraft)
project(${PR_NAME} VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 17)
include(GNUInstallDirs)

include(CTest)
enable_testing()

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/GLFW/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#---------ADD SOURCE AND HEADER FILES ---------------
set(SOURCE_FILE_NAMES
    Birch_Biome
    Block_Heavy
    Block 
    Chunk 
    Crosshair 
    Desert_Biome 
    Forest_Biome 
    main
    Menu 
    Model 
    Snow_Biome 
    stb_image  
    Structure 
    Taiga_Biome 
    World
)

list(TRANSFORM SOURCE_FILE_NAMES APPEND ".cpp")
list(TRANSFORM SOURCE_FILE_NAMES PREPEND "Minecraft/")

if(UNIX)
set(CMAKE_INSTALL_RPATH $ORIGIN/../lib)
endif()
add_executable(${PROJECT_NAME} ${SOURCE_FILE_NAMES})

target_include_directories(${PR_NAME}
PRIVATE
"${CMAKE_CURRENT_SOURCE_DIR}/res/include/"
"${CMAKE_CURRENT_SOURCE_DIR}/res/include/glad/"
"${CMAKE_CURRENT_SOURCE_DIR}/res/include/assimp/"
"${CMAKE_CURRENT_SOURCE_DIR}/res/include/irk/"
"${CMAKE_CURRENT_SOURCE_DIR}/res/include/glm/"
"${CMAKE_CURRENT_SOURCE_DIR}/res/include/KHR/"
"${CMAKE_CURRENT_SOURCE_DIR}/external/GLFW/include/GLFW/"
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Minecraft/>
$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Minecraft/>
)


#-----------COPY RES DIR-------------------------
file(COPY res DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY audio DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY fonts DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY shaders DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY textures DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

#-----------ADD GLFW, GLAD and irk--------------------------------
add_subdirectory(external/GLFW)
add_subdirectory(res/include/glad)
target_link_directories(${PR_NAME} PUBLIC external/GLFW/src/ res/libs/)
target_link_libraries(${PR_NAME} PRIVATE glfw glad IrrKlang)

#--------INSTALL LINUX---------------------------------
install(TARGETS ${PR_NAME} 
RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY {CMAKE_CURRENT_SOURCE_DIR}/audio DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY {CMAKE_CURRENT_SOURCE_DIR}/fonts DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY {CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY {CMAKE_CURRENT_SOURCE_DIR}/textures DESTINATION ${CMAKE_INSTALL_BINDIR})

if(WIN32)
    #sfml
    install(FILES 
        "${CMAKE_CURRENT_BINARY_DIR}/ikpMP3.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/irrKlang.dll" 
        DESTINATION ${CMAKE_INSTALL_BINDIR})
elseif(UNIX)
    install(TARGETS ${PR_NAME} 
       LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

#-------PACKAGING------------------------------------
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack) 
