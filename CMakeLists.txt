

# ⭐ این خط را برای تنظیم مسیر Qt اضافه کنید
set(CMAKE_PREFIX_PATH "C:/Qt/6.11.1/mingw_64")


include(FetchContent)



cmake_minimum_required(VERSION 3.20)

project(CircuitSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ⭐ این خطوط را اضافه کنید (برای Qt MOC)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(FetchContent)

# JSON library.
FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

# ⭐ اصلاح: تمام کامپوننت‌های مورد نیاز Qt را اضافه کنید
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

add_executable(CircuitSimulator
        main.cpp
        types.cpp
        pin.cpp
        component.cpp
        node.cpp
        circuit.cpp
        resistor.cpp
        circuit_widget.cpp
)

target_include_directories(CircuitSimulator PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# ⭐ اصلاح: همه کتابخانه‌های Qt را لینک کنید
target_link_libraries(CircuitSimulator PRIVATE
        nlohmann_json::nlohmann_json
        Qt6::Widgets
        Qt6::Core
        Qt6::Gui
)

if(WIN32)
    set_target_properties(CircuitSimulator PROPERTIES
            WIN32_EXECUTABLE TRUE
    )
endif()

# ⭐ اضافه کنید: برای پیدا کردن فایل‌های هدر Qt
target_compile_definitions(CircuitSimulator PRIVATE
        QT_WIDGETS_LIB
        QT_GUI_LIB
        QT_CORE_LIB
)