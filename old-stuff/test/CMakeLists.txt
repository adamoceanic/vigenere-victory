#set(SOURCE_FILES main.cpp inc/MyClass.h inc/MyOtherClass.h)
file(GLOB SOURCE_FILES ../Lib1/inc/*.h *.cpp)
add_executable(VigenereTests ${SOURCE_FILES} Input_test.cpp)
target_link_libraries(VigenereTests Lib1)
