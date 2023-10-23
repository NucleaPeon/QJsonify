cmake_minimum_required(VERSION 3.3)

project(cocoainitializer
    VERSION 1.0.0
    LANGUAGES OBJCXX OBJC
)

set(COCOAINIT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/cocoainitializer/)
set(CMAKE_C_FLAGS "-x objective-c")

add_library(CocoaInitializer MODULE
	${COCOAINIT_SOURCE_DIR}/cocoainitializer.mm
	${COCOAINIT_SOURCE_DIR}/cocoainitializer.h
)

#target_link_libraries(CocoaInitializer
#    PRIVATE "-framework Cocoa"
#    PRIVATE "-framework Foundation"
#    PRIVATE "-framework AppKit"
#)

set_target_properties(CocoaInitializer PROPERTIES
    LINKER_LANGUAGE "CXX"
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
    XCODE_ATTRIBUTE_CLANG_ENABLE_MODULES YES
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_WEAK YES
)
