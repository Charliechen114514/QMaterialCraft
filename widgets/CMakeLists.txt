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
  Commons/property_string.h
  helpers/commonwidgetsettingshelper.h helpers/commonwidgetsettingshelper.cpp
  helpers/widgetlayouthelper.h helpers/widgetlayouthelper.cpp
  CCWidgets_BuildDefine.h
  Commons/TextIndiator.h
)

set(CCSlider_SRC
  CCSlider/sliderpaintcontext.h CCSlider/sliderpaintcontext.cpp
  CCSlider/slider.h
  CCSlider/slider.cpp)

set(CCButton_SRC
  CCButton/buttonpaintcontext.h CCButton/buttonpaintcontext.cpp
  CCButton/button.h CCButton/button.cpp)

set(CCCard_SRC
  CCCards/cccard.h CCCards/cccard.cpp
  CCCards/privates/cccardactions.h CCCards/privates/cccardactions.cpp
  CCCards/privates/cccardcontent.h CCCards/privates/cccardcontent.cpp
  CCCards/privates/cccardheader.h CCCards/privates/cccardheader.cpp
  CCCards/privates/cccard_components_name.h
)

set(CCLabel_SRC
  CCLabel/cclabel.h CCLabel/cclabel.cpp
  CCLabel/labelpaintcontext.h CCLabel/labelpaintcontext.cpp
  CCLabel/ccbadgelabel.h CCLabel/ccbadgelabel.cpp
)

set(CCProgressBar_SRC
  CCProgressBar/progressbar.h CCProgressBar/progressbar.cpp
  CCProgressBar/progressbarpaintcontext.h CCProgressBar/progressbarpaintcontext.cpp
)

set(CCTextField_SRC
  CCTextField/cctextfield.h CCTextField/cctextfield.cpp
  CCTextField/cctextfieldpaintcontext.h CCTextField/cctextfieldpaintcontext.cpp
)

set(THEME_SUPPORT_SRC
  themes/material/slidermaterialpaintcontext.h themes/material/slidermaterialpaintcontext.cpp
  themes/material/material_color_helper.h themes/material/material_color_helper.cpp
  themes/material/MaterialThemeMarker.h
  themes/material/buttonmaterialpaintcontext.h
  themes/material/buttonmaterialpaintcontext.cpp
  themes/material/animation_wrapper/hoveranimationhelper.h themes/material/animation_wrapper/hoveranimationhelper.cpp
  themes/material/animation_wrapper/shadowoffsetsanimationhelper.h themes/material/animation_wrapper/shadowoffsetsanimationhelper.cpp
  themes/material/animation_wrapper/rippleanimation.h themes/material/animation_wrapper/rippleanimation.cpp
  themes/material/materialtextindicator.h themes/material/materialtextindicator.cpp
  themes/material/MaterialPropertyString.h
  themes/material/labelmaterialpaintcontext.h themes/material/labelmaterialpaintcontext.cpp
  themes/material/animation_wrapper/opacityanimation.h themes/material/animation_wrapper/opacityanimation.cpp
  themes/material/labelbadgematerialpaintcontext.h themes/material/labelbadgematerialpaintcontext.cpp
  themes/material/animation_wrapper/floativeanimation.h themes/material/animation_wrapper/floativeanimation.cpp
  themes/material/progressbarmaterialpaintcontext.h themes/material/progressbarmaterialpaintcontext.cpp
  themes/material/components/cardmaterialpaintcontext.h themes/material/components/cardmaterialpaintcontext.cpp
  themes/material/components/cctextfieldmaterialpaintcontext.h themes/material/components/cctextfieldmaterialpaintcontext.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(CCWidgets SHARED
  ${THEME_SUPPORT_SRC}
  ${COMMON_SRC}
  ${CCSlider_SRC}
  ${CCButton_SRC}
  ${CCCard_SRC}
  ${CCLabel_SRC}
  ${CCProgressBar_SRC}
  ${CCTextField_SRC}
)

target_link_libraries(CCWidgets PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(CCWidgets PUBLIC .
  Commons CCSlider CCButton CCCards CCLabel CCProgressBar)
target_compile_definitions(CCWidgets PRIVATE CCWIDGET_LIBRARY_BUILD)
