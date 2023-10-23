cmake_minimum_required(VERSION 3.3)

find_package(Qt5 REQUIRED
    PrintSupport
    Widgets
)

set(MENUGEN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/qmenugen/)

if(Q_OS_MAC)
	find_package(Qt5 REQUIRED MacExtras)
elseif(Q_OS_WIN)
	find_package(Qt5 REQUIRED WinExtras)
endif()

add_library(libqmenugen STATIC
	${MENUGEN_SOURCE_DIR}/loadmenu.h
	${MENUGEN_SOURCE_DIR}/loadmenu.cpp
)

target_include_directories(libqmenugen PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries( libqmenugen Qt5::Widgets Qt5::PrintSupport )
if (Q_OS_MAC)
	target_link_libraries( libqmenugen Qt5::MacExtras)
elseif(Q_OS_WIN)
	target_link_libraries( libqmenugen Qt5::WinExtras)
endif()

message(STATUS "libqmenugen library built")
