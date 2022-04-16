project(XGui)


file(GLOB SRCS include/*.* source/*.*)

include_directories("${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/include")

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE
        ${SRCS}
        )

target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        include
        )
