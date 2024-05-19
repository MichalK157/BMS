cmake_minimum_required(VERSION 3.25)
project(BMS_API)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(COPY   
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    DESTINATION    
    "${CMAKE_CURRENT_BINARY_DIR}"
)

set(UI_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/bms_api.ui
)

qt5_wrap_ui(UI_HEADERS ${UI_FILES})


add_executable(bms_api main.cpp ${UI_HEADERS})

target_link_libraries(bms_api Qt5::Widgets)

add_custom_command(TARGET bms_api
       	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:bms_api> ${CMAKE_CURRENT_SOURCE_DIR}
)
