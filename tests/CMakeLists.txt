enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET tiny-zip PROPERTY CXX_STANDARD 20)
endif()

include(GoogleTest)

add_executable (zip-file-tests "ZipFile-tests.cpp")
target_link_libraries(
  zip-file-tests
  GTest::gtest_main
  tiny-zip
)


gtest_add_tests(TARGET  zip-file-tests  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/tests/tests-data")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/tests-data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")

# TODO: Add tests and install targets if needed.
