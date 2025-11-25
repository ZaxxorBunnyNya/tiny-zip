
set(CMAKE_CXX_STANDARD 20)
include_directories(include)

add_library (tiny-zip  "src/ZipFile.cpp" "src/ZipEntry.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET tiny-zip PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(tiny-zip PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# TODO: Add tests and install targets if needed.
