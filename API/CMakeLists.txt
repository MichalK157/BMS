cmake_minimum_required(VERSION 3.25)
project(BMS_API)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(UI_FILES
    bms_api.ui
)

# Wygeneruj kod C++ na podstawie pliku .ui
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

# Dodaj wygenerowany plik do celu wykonywalnego lub biblioteki
add_executable(bms_api main.cpp ${UI_HEADERS})

# Linkowanie z Qt5
target_link_libraries(bms_api Qt5::Widgets)

