include_directories("${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/include")


include_directories(testWin)
add_executable(test)

target_sources(test PRIVATE
        main.cpp
        )

target_link_libraries(test
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        XGui
        )