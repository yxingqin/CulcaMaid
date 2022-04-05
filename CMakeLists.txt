cmake_minimum_required(VERSION 3.20)

project(CalculMaid)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)





if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64")# UOS 无需设置
endif()
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        )


include_directories("${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/include")
include_directories(src/Forms)# 需要单独引入头文件目录
include_directories(src/unit)
file(GLOB_RECURSE   SRCS  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}  LIST_DIRECTORIES false   src/*.cpp  src/*.ui)
#添加额外的 源文件 例如资源文件等
LIST(APPEND  SRCS res.qrc)



if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    # 针对window
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
    # 针对UOS
    add_executable(${PROJECT_NAME}   ${SRCS} )
    target_link_libraries(${PROJECT_NAME}
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            )
endif()





# 针对windows 平台复制 dll 到 build 目录下
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(QT_LIB_LIST Core Gui Widgets  Test)
    if (WIN32)
        set(DEBUG_SUFFIX)
        set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
                set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            endif ()
        endif ()
        #拷贝 style 文件
        if(EXISTS "${QT_INSTALL_PATH}/plugins/styles/qwindowsvistastyle.dll")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/styles/")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/plugins/styles/qwindowsvistastyle.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/styles/")
        endif()
        if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        endif ()
        foreach (QT_LIB ${QT_LIB_LIST})
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
        endforeach (QT_LIB)
    endif ()
endif()
