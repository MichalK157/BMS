cmake_minimum_required(VERSION 3.25)
project(BMS_API LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

file(COPY   
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    DESTINATION    
    "${CMAKE_CURRENT_BINARY_DIR}"
)

set(UI_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/bms_api.ui
)

qt5_wrap_ui(UI_HEADERS ${UI_FILES})

include_directories(src)

set(HEADERS_API
    src/SerialPort.h
    src/q_main_window.h
    src/q_communication.h
)

set(FILES_API
    src/SerialPort.cpp
    src/q_main_window.cpp
    src/q_communication.cpp
)

add_executable(bms_api 
            main.cpp
            ${FILES_API}
            ${HEADERS_API}
            ${UI_HEADERS})

target_link_libraries(bms_api Qt5::Widgets)

find_package(Threads REQUIRED)
target_link_libraries(bms_api Qt5::Core Qt5::Gui Qt5::Widgets)

add_custom_command(TARGET bms_api
       	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:bms_api> ${CMAKE_CURRENT_SOURCE_DIR}
)


project(TEST)

set(HEADERS_TEST
    src/SerialPort.h
)

set(FILES_TEST
    src/test.cpp
    src/SerialPort.cpp
)

add_executable(test 
            ${FILES_TEST}
            ${HEADERS_TEST}
            )

add_custom_command(TARGET test
       	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:test> ${CMAKE_CURRENT_SOURCE_DIR}/src
)