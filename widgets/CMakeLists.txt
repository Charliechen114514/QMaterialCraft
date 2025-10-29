cmake_minimum_required(VERSION 3.16)

project(CCWidgets LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(COMMON_SRC
  Commons/paintcontext.h Commons/paintcontext.cpp
  Commons/paintcontextallocator.h Commons/paintcontextallocator.cpp
  Commons/ThemeMarker.h
  Commons/colorhelper.h Commons/colorhelper.cpp
  Commons/context_request_macros.h
  Commons/animation_helpers.h Commons/animation_helpers.cpp
  setups/paintcontextregisters.h setups/paintcontextregisters.cpp
  CCWidgets_BuildDefine.h
)

set(CCSlider_SRC
  CCSlider/sliderpaintcontext.h CCSlider/sliderpaintcontext.cpp
  CCSlider/slider.h
  CCSlider/slider.cpp)

set(CCButton_SRC CCButton/button.h CCButton/button.cpp)

set(THEME_SUPPORT_SRC
  themes/material/slidermaterialpaintcontext.h themes/material/slidermaterialpaintcontext.cpp
  themes/material/material_color_helper.h themes/material/material_color_helper.cpp
  themes/material/MaterialThemeMarker.h
  themes/material/buttonmaterialpaintcontext.h
  themes/material/buttonmaterialpaintcontext.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(CCWidgets SHARED
  ${THEME_SUPPORT_SRC}
  ${COMMON_SRC}
  ${CCSlider_SRC}
  ${CCButton_SRC}
  themes/material/animation_wrapper/hoveranimationhelper.h themes/material/animation_wrapper/hoveranimationhelper.cpp
  themes/material/animation_wrapper/shadowoffsetsanimationhelper.h themes/material/animation_wrapper/shadowoffsetsanimationhelper.cpp
  themes/material/animation_wrapper/rippleanimation.h themes/material/animation_wrapper/rippleanimation.cpp
  themes/material/materialtextindicator.h themes/material/materialtextindicator.cpp
  Commons/TextIndiator.h
)

target_link_libraries(CCWidgets PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(CCWidgets PRIVATE Qt6::Core)
target_link_libraries(CCWidgets PRIVATE Qt6::Core)
target_link_libraries(CCWidgets PRIVATE Qt6::Core)
target_include_directories(CCWidgets PUBLIC . Commons CCSlider CCButton)
target_compile_definitions(CCWidgets PRIVATE CCWIDGET_LIBRARY_BUILD)
