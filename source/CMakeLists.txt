project(source)

include_directories(src/Forms)
include_directories(src/unit)
file(GLOB_RECURSE   SRCS  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}  LIST_DIRECTORIES false src/*.cpp src/*.ui)
LIST(APPEND  SRCS res.qrc)




if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        add_executable(${PROJECT_NAME}   ${SRCS} )
    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
        add_executable(${PROJECT_NAME} WIN32 ${SRCS})
    endif()
    target_link_libraries(${PROJECT_NAME}
            Qt::Core
            Qt::Gui
            Qt::Widgets
            )
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_executable(${PROJECT_NAME}   ${SRCS} )
    target_link_libraries(${PROJECT_NAME}
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            )
endif()

