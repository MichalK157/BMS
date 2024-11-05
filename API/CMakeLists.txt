cmake_minimum_required(VERSION 3.25)
project(BMS_API LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
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

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
qt5_wrap_cpp(MOC_SOURCES q_main_window.h q_communication.h)
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

include_directories(src proto)

set(HEADERS_API
    src/SerialPort.h
    src/q_main_window.h
    src/q_communication.h
    src/q_tools.h
    proto/protocol.h
    src/serialization.h
)

set(FILES_API
    src/SerialPort.cpp
    src/q_main_window.cpp
    src/q_communication.cpp
    src/q_tools.cpp
    src/serialization.cpp
)

set(BQ_TYPE "" CACHE STRING "Specify the BQ version (BQ76920, BQ76930, or BQ76940)")

add_executable(bms_api 
            main.cpp
            ${FILES_API}
            ${HEADERS_API}
            ${UI_HEADERS})

target_link_libraries(bms_api Qt5::Widgets)

find_package(Threads REQUIRED)
target_link_libraries(bms_api Qt5::Core Qt5::Gui Qt5::Widgets)

if (BQ_TYPE STREQUAL "BQ76920")
    target_compile_definitions(bms_api PRIVATE BQ76920)
elseif (BQ_TYPE STREQUAL "BQ76930")
    target_compile_definitions(bms_api PRIVATE BQ76930)
elseif (BQ_TYPE STREQUAL "BQ76940")
    target_compile_definitions(bms_api PRIVATE BQ76940)
else()
    message(FATAL_ERROR "Unknown BQ_TYPE: ${BQ_VERSION}")
endif()

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