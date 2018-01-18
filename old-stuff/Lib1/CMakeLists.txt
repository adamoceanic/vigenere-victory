#set(SOURCE_FILES inc/Vigenere.h inc/VigenereDecipherer.h src/Vigenere.cpp src/VigenereDecipherer.cpp api/Matlab.cpp inc/Input.cpp inc/Input.h)
file(GLOB SOURCE_FILES inc/*.h src/*.cpp api/*.cpp)
add_library(Lib1 ${SOURCE_FILES} src/Input_Impl.cpp src/Input_Impl.h)
set_target_properties(Lib1 PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(Lib1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})