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
	find_package(Qt5 HINTS "$ENV{QT5_DIR}" COMPONENTS Core Quick REQUIRED)
	set(Qt5_DIR "C:/Qt/Qt5.3.2/5.3/msvc2013_64_opengl/")
	find_package(Qt5 COMPONENTS WinExtras REQUIRED)
	set(BUILD_SHARED_LIBS OFF)
	
elseif(Q_OS_LINUX)
	set(BUILD_SHARED_LIBS OFF)  # Maybe set to on in this one case?
endif()


include_directories(${PROJECT_SOURCE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/lib/qmenugen/")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


list(APPEND QJSONIFY_HEADERS
	mainwindow.h
	about.h
	lib/qmenugen/loadmenu.h
)

list(APPEND QJSONIFY_SOURCES
	mainwindow.cpp
	about.cpp
	lib/qmenugen/loadmenu.cpp
)

list(APPEND QJSONIFY_UIS
	mainwindow.ui
	about.ui
)

list(APPEND QJSONIFY_RES
	main.qrc
)

if (APPLE)
        include_directories("${PROJECT_SOURCE_DIR}/lib/cocoainitializer/")
	list(APPEND QJSONIFY_HEADERS lib/cocoainitializer/cocoainitializer.h)
	list(APPEND QJSONIFY_SOURCES lib/cocoainitializer/cocoainitializer.mm)
endif()


# QT5_WRAP_UI( UI_HEADERS ${QJSONIFY_UIS} )

if (APPLE)
	set(MACOSX_BUNDLE_ICON_FILE qjsonify.icns )
	set(APP_ICON "icons/${MACOSX_BUNDLE_ICON_FILE}")
	list(APPEND OTHER_TARGETS ${APP_ICON})
	list(APPEND QJSONIFY_SOURCES lib/cocoainitializer/cocoainitializer.mm)
	list(APPEND QJSONIFY_HEADERS lib/cocoainitializer/cocoainitializer.h)
	add_custom_target(OTHER_FILES SOURCES ${OTHER_TARGETS})
	set_property(SOURCE ${APP_ICON} PROPERTY MACOSX_PACKAGE_LOCATION
		${MACOSX_BUNDLE_ICON_FILE})
	file(COPY ${APP_ICON} DESTINATION
		 ${CMAKE_CURRENT_BINARY_DIR})
	add_executable(QJsonify MACOSX_BUNDLE
		${OTHER_FILES}
		main.cpp
		${QJSONIFY_HEADERS}
		${QJSONIFY_SOURCES}
		${QJSONIFY_UIS}
		${QJSONIFY_RES}

	)
	target_sources(QJsonify PRIVATE
		${OTHER_TARGETS}
	)
	set_source_files_properties(
		${OTHER_TARGETS}
		PROPERTIES
		MACOSX_PACKAGE_LOCATION Resources/
	)
	set_target_properties(QJsonify PROPERTIES
		BUNDLE TRUE
		MACOSX_BUNDLE_GUI_IDENTIFIER org.peondevelopments.QJsonify
		MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
		MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
		MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
	)

	target_link_libraries(QJsonify Qt5::MacExtras)
	set_target_properties(QJsonify PROPERTIES LINK_FLAGS
		 "-Wl,-F/Library/Frameworks")
	target_link_libraries(QJsonify stdc++
		"-framework Cocoa"
		objc
	)
else()
	if (MSVC)
		set(CMAKE_PREFIX_PATH "C:\\Qt\\5.3.1\\5.3\\msvc2013_opengl")
	endif()
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
if(MSVC)
	target_link_libraries(QJsonify Qt5::WinExtras)
	QT5_WRAP_UI( UI_HEADERS ${QJSONIFY_UIS} )
endif()

install(TARGETS QJsonify)

