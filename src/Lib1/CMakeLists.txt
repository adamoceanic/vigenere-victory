file(GLOB SOURCE_FILES ../../include/Lib1/*.h *.cpp *h)
add_library(Lib1 ${SOURCE_FILES} matlab_api.h)
set_target_properties(Lib1 PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(Lib1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Lib1 PUBLIC "../../")
