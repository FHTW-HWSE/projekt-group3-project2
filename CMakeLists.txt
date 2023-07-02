cmake_minimum_required(VERSION 3.10.0)

project(Table_Reservation_System VERSION 1.0)

find_package(Catch2 REQUIRED)

include(CTest)
include(Catch)

# Create the library containing the code of the project
add_library(program_library
  src/board_operations.cpp
  src/changes.cpp
  src/csv_operations.cpp
  src/main.cpp
  src/user_validation.cpp
  reservation/reservation.csv
)

target_include_directories(program_library PUBLIC include)

# Create test executable
add_executable(program_tests
  test/unit_tests.cpp
)

target_link_libraries(program_tests
  program_library
)

catch_discover_tests(program_tests)

# Create program executable
add_executable(program
  src/main.cpp
)

target_link_libraries(program
  program_library
)

# Add a target coverage that will run the tests and report the coverage of the 
# library in a folder coverage
if (CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage.cmake)
    append_coverage_compiler_flags_to_target(program_library)
    setup_target_for_coverage_lcov(
        NAME coverage
        EXECUTABLE program_tests
        EXCLUDE "/usr/include/*"
    )
endif()