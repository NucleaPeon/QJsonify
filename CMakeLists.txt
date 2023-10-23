cmake_minimum_required(VERSION 3.3)
project(QJsonify
        VERSION 1.1.0
        LANGUAGES CXX)

find_package(Qt5 REQUIRED
    PrintSupport
    Widgets
)

if(APPLE)
	find_package(Qt5 REQUIRED MacExtras)
	set(BUILD_SHARED_LIBS OFF)
elseif(MSVC)
	find_package(Qt5 REQUIRED WinExtras)
	set(BUILD_SHARED_LIBS OFF)
elseif(Q_OS_LINUX)
	set(BUILD_SHARED_LIBS OFF)  # Maybe set to on in this one case?
endif()


include_directories(${PROJECT_SOURCE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/lib/qmenugen/")
include_directories("${PROJECT_SOURCE_DIR}/lib/cocoainitializer/")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


list(APPEND QJSONIFY_HEADERS
	mainwindow.h
	about.h
	lib/cocoainitializer/cocoainitializer.h
	lib/qmenugen/loadmenu.h
)

list(APPEND QJSONIFY_SOURCES
	mainwindow.cpp
	about.cpp
	lib/cocoainitializer/cocoainitializer.mm
	lib/qmenugen/loadmenu.cpp
)

list(APPEND QJSONIFY_UIS
	mainwindow.ui
	about.ui
)

list(APPEND QJSONIFY_RES
	main.qrc
)

QT5_WRAP_UI( UI_HEADERS ${QJSONIFY_UIS} )
list(APPEND OTHER_TARGETS
	menu_defs.json
)
if (APPLE)

	set(MACOSX_BUNDLE_ICON_FILE qjsonify.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
	set(APP_ICON "icons/${MACOSX_BUNDLE_ICON_FILE}")
	list(APPEND OTHER_TARGETS ${APP_ICON})
	add_custom_target(OTHER_FILES ALL SOURCES ${OTHER_TARGETS})
	file(COPY ${APP_ICON} DESTINATION
		 ${CMAKE_CURRENT_BINARY_DIR})
	set_source_files_properties(
		${MACOSX_BUNDLE_ICON_FILE} PROPERTIES
       	MACOSX_PACKAGE_LOCATION Resources
	)



	add_executable(QJsonify MACOSX_BUNDLE
		${OTHER_FILES}
		main.cpp
		${QJSONIFY_HEADERS}
		${QJSONIFY_SOURCES}
		${QJSONIFY_UIS}
		${QJSONIFY_RES}

	)
	set_target_properties(QJsonify PROPERTIES
		MACOSX_BUNDLE TRUE
		MACOSX_FRAMEWORK_IDENTIFIER org.peondevelopments.QJsonify
		RESOURCE ${MACOSX_BUNDLE_ICON_FILE})
else()
	add_executable(QJsonify
		main.cpp
		${QJSONIFY_HEADERS}
		${QJSONIFY_SOURCES}
		${QJSONIFY_UIS}
		${QJSONIFY_RES}
		${OTHER_FILES}
	)
endif()
target_link_libraries(QJsonify Qt5::Widgets Qt5::PrintSupport )

if (APPLE)
	target_link_libraries(QJsonify Qt5::MacExtras)
	set_target_properties(QJsonify PROPERTIES LINK_FLAGS "-Wl,-F/Library/Frameworks")
	target_link_libraries(QJsonify stdc++ "-framework Foundation" "-framework Cocoa" "-framework AppKit" objc)
elseif(MSVC)
	target_link_libraries(QJsonify Qt5::WinExtras)
endif()
