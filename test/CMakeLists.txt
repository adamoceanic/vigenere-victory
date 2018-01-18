
file(GLOB SOURCE_FILES *.h *.cpp Lib1/*.cpp)
add_executable(VigenereTests ${SOURCE_FILES})
target_link_libraries(VigenereTests Lib1)

target_include_directories(VigenereTests PUBLIC "../../")
target_include_directories(VigenereTests PUBLIC "catch/")

