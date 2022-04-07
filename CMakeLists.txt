cmake_minimum_required(VERSION 3.20)

project(CalcuMaid)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_PREFIX_PATH "D:/Software/SDK/Qt/5.15.2/mingw81_64")# yxqin
   # set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64")# xzl
endif()

#指定输出路径
if (NOT EXISTS ${CMAKE_PREFIX_PATH}/out)
    file(MAKE_DIRECTORY out)
endif ()
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        )
include_directories("${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/include")



add_subdirectory(XGui)
add_subdirectory(source)