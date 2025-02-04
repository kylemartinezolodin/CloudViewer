cmake_minimum_required(VERSION 3.5)

project(CloudViewer)

# init qt
set(CMAKE_AUTOMOC ON) # for meta object compiler
set(CMAKE_AUTORCC ON) # resource files
set(CMAKE_AUTOUIC ON) # UI files
set(DCMAKE_BUILD_TYPE "Debug")

# find package
find_package(Qt5 REQUIRED Widgets)
find_package(PCL 1.7.1 REQUIRED)
find_package(VTK REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/core/include) #3DRPCore
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# find source files, header files and ui files
# aux_source_directory(. DIR_SRCS)
file(GLOB_RECURSE DIR_SRCS    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE DIR_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE DIR_UIS     ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

# add resource
#set(RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/CloudViewer.qrc)
#qt5_add_resources(RESOURCE_ADDED ${RESOURCE})

add_executable(${PROJECT_NAME}
    ${DIR_SRCS}
    ${DIR_HEADERS}
    ${DIR_UIS}
#    ${RESOURCE_ADDED}
)

target_link_libraries(${PROJECT_NAME}
    3DRPCore #3DRPCore
    ${PCL_LIBRARIES}
    ${VTK_LIBRARIES}
    Qt5::Widgets
)
