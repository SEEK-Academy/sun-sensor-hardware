

set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/src/application)
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/src/application/test)

set(TEST_SOURCES ${TESTS_DIR}/main.cc
                 ${TESTS_DIR}/lightEstimatorTest.cc
                 ${TESTS_DIR}/mathTest.cc
                 )

if(TEST)
    add_executable(run_tests ${TEST_SOURCES})
    target_link_libraries(run_tests PUBLIC GTest::gtest_main Eigen3::Eigen)
    target_include_directories(run_tests PUBLIC ${SOURCES_DIR}/inc)
endif()

