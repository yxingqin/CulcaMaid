project(XGui)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
include_directories("${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/include")

add_library(${PROJECT_NAME} SHARED
        XWin/XWin.cpp
        )
target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/XWin
        )
