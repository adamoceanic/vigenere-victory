set(SOURCE_FILES src/MyClass.cpp src/MyOtherClass.cpp inc/MyClass.h inc/MyOtherClass.h)
add_library(Lib1 ${SOURCE_FILES})
set_target_properties(Lib1 PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(Lib1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})