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
  Commons/containercommondelegate.h Commons/containercommondelegate.cpp
  setups/paintcontextregisters.h setups/material/materialpaintcontextregisters.cpp
  Commons/property_string.h
  helpers/commonwidgetsettingshelper.h helpers/commonwidgetsettingshelper.cpp
  helpers/widgetlayouthelper.h helpers/widgetlayouthelper.cpp
  helpers/animations/hoveranimationhelper.h helpers/animations/hoveranimationhelper.cpp
  helpers/animations/shadowoffsetsanimationhelper.h helpers/animations/shadowoffsetsanimationhelper.cpp
  helpers/animations/rippleanimation.h helpers/animations/rippleanimation.cpp
  helpers/animations/opacityanimation.h helpers/animations/opacityanimation.cpp
  helpers/animations/floativeanimation.h helpers/animations/floativeanimation.cpp
  CCWidgets_BuildDefine.h
  Commons/TextIndiator.h
  helpers/animations/appearanimation.h
  helpers/animations/appearanimation.cpp
  helpers/animations/commons.h
  helpers/animations/commons.cpp
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
  themes/material/materialtextindicator.h themes/material/materialtextindicator.cpp
  themes/material/MaterialPropertyString.h
  themes/material/labelmaterialpaintcontext.h themes/material/labelmaterialpaintcontext.cpp
  themes/material/labelbadgematerialpaintcontext.h themes/material/labelbadgematerialpaintcontext.cpp
  themes/material/progressbarmaterialpaintcontext.h themes/material/progressbarmaterialpaintcontext.cpp
  themes/material/components/cardmaterialpaintcontext.h themes/material/components/cardmaterialpaintcontext.cpp
  themes/material/components/cctextfieldmaterialpaintcontext.h themes/material/components/cctextfieldmaterialpaintcontext.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
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
  CCImageWidget/ccimagewidget.h CCImageWidget/ccimagewidget.cpp
  CCImageWidget/imagewidgetpaintcontext.h CCImageWidget/imagewidgetpaintcontext.cpp
  themes/material/imagewidgetmaterialpaintcontext.h themes/material/imagewidgetmaterialpaintcontext.cpp
  Composers/CCTreeWidget/cctreewidget.h Composers/CCTreeWidget/cctreewidget.cpp
  Composers/CCTreeWidget/treewidgetpaintcontext.h Composers/CCTreeWidget/treewidgetpaintcontext.cpp
  Composers/privates/containerpaintcontext.h Composers/privates/containerpaintcontext.cpp
  themes/material/delegates/materialcontainercommondelegate.h themes/material/delegates/materialcontainercommondelegate.cpp
  setups/material/materialpaintcontextregisters.h
  setups/paintcontextregisters.cpp
  Composers/privates/container_delegates_keys.h
  Commons/context_request_headers.h
  themes/material/materialtreewidgetpaintcontext.h themes/material/materialtreewidgetpaintcontext.cpp
  themes/material/commons/materialcontainerdefaultpaintcontext.h themes/material/commons/materialcontainerdefaultpaintcontext.cpp
  themes/material/materiallistviewpaintcontext.cpp themes/material/materiallistviewpaintcontext.h themes/material/materiallistwidgetpaintcontext.cpp themes/material/materiallistwidgetpaintcontext.h themes/material/materialtableviewpaintcontext.cpp themes/material/materialtableviewpaintcontext.h themes/material/materialtablewidgetpaintcontext.cpp themes/material/materialtablewidgetpaintcontext.h themes/material/materialtreeviewpaintcontext.cpp themes/material/materialtreeviewpaintcontext.h
  Composers/CCTreeView/cctreeview.h Composers/CCTreeView/cctreeview.cpp
  Composers/CCTableWidget/cctablewidget.h Composers/CCTableWidget/cctablewidget.cpp
  Composers/CCTableView/cctableview.h Composers/CCTableView/cctableview.cpp
  Composers/CCListView/cclistview.h Composers/CCListView/cclistview.cpp
  Composers/CCListWidget/cclistwidget.h Composers/CCListWidget/cclistwidget.cpp
  Composers/CCTreeView/treeviewpaintcontext.h Composers/CCTreeView/treeviewpaintcontext.cpp
  Composers/CCTableWidget/tablewidgetpaintcontext.h Composers/CCTableWidget/tablewidgetpaintcontext.cpp
  Composers/CCTableView/tableviewpaintcontext.h Composers/CCTableView/tableviewpaintcontext.cpp
  Composers/CCListWidget/listwidgetpaintcontext.h Composers/CCListWidget/listwidgetpaintcontext.cpp
  Composers/CCListView/listviewpaintcontext.h Composers/CCListView/listviewpaintcontext.cpp
  CCToolButton/cctoolbutton.h CCToolButton/cctoolbutton.cpp
  CCToolButton/toolbuttonpaintcontext.h CCToolButton/toolbuttonpaintcontext.cpp
  themes/material/toolbuttonmaterialpaintcontext.h themes/material/toolbuttonmaterialpaintcontext.cpp
  CCToolBox/cctoolbox.h CCToolBox/cctoolbox.cpp
  CCToolBox/toolboxpaintcontext.h CCToolBox/toolboxpaintcontext.cpp
  themes/material/toolbox/materialtoolboxpaintcontext.h themes/material/toolbox/materialtoolboxpaintcontext.cpp
  themes/material/toolbox/materialheaderbar.h themes/material/toolbox/materialheaderbar.cpp
  CCCalendarWidget/cccalendarwidget.h CCCalendarWidget/cccalendarwidget.cpp
  CCCalendarWidget/calendarwidgetpaintcontext.h CCCalendarWidget/calendarwidgetpaintcontext.cpp
  themes/material/calendar/calendarwidgetmaterialpaintcontext.h themes/material/calendar/calendarwidgetmaterialpaintcontext.cpp

  CCMarkdownWidget/privates/markdownhighlighter.h CCMarkdownWidget/privates/markdownhighlighter.cpp
  CCMarkdownWidget/cmarkdowncardwidget.h CCMarkdownWidget/cmarkdowncardwidget.cpp
  CCMarkdownWidget/ccmarkdownbrowserwidget.h CCMarkdownWidget/ccmarkdownbrowserwidget.cpp
)

target_link_libraries(CCWidgets PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(CCWidgets PRIVATE Qt6::Widgets)
target_link_libraries(CCWidgets PRIVATE Qt6::Core)
target_link_libraries(CCWidgets PRIVATE Qt6::Widgets)
target_link_libraries(CCWidgets PRIVATE Qt6::Widgets)
target_link_libraries(CCWidgets PRIVATE Qt6::Widgets)
target_link_libraries(CCWidgets PRIVATE Qt6::Widgets)

target_include_directories(CCWidgets PUBLIC .
  Commons CCSlider CCButton CCCards CCLabel CCProgressBar)
target_compile_definitions(CCWidgets PRIVATE CCWIDGET_LIBRARY_BUILD)
