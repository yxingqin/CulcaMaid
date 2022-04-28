project(source)

include_directories(Forms core Widget)
include_directories("${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/include")
file(GLOB_RECURSE   SRCS  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}  LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
LIST(APPEND  SRCS assets/res.qrc)




if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        add_executable(${PROJECT_NAME}   ${SRCS} )
    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
        add_executable(${PROJECT_NAME} WIN32 ${SRCS})
    endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_executable(${PROJECT_NAME}   ${SRCS} )
endif()

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        XGui
        )

