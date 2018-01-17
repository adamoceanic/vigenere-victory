#set(SOURCE_FILES main.cpp inc/MyClass.h inc/MyOtherClass.h)
file(GLOB SOURCE_FILES *.cpp)
add_executable(VigenereTests ${SOURCE_FILES})
target_link_libraries(VigenereTests Lib1)
