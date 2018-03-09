cmake_minimum_required(VERSION 3.2)

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    message("TRAVIS_BUILD_NUMBER environment set to default")
    set(ENV{TRAVIS_BUILD_NUMBER} "1")
endif()

project(async VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Threads)

configure_file(version.h.in version.h)

add_library(async SHARED async.h async.cpp bulk.h bulk.cpp)

set_target_properties(async
        PROPERTIES
                CXX_STANDARD 14
                CXX_STANDARD_REQUIRED ON
                CMAKE_CXX_EXTENSIONS OFF
                COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(async PROPERTIES PUBLIC_HEADER async.h)

target_link_libraries(async
      ${CMAKE_THREAD_LIBS_INIT}
)

#add_executable(async_cli main.cpp)
#target_link_libraries(async_cli async)

include(GNUInstallDirs)

install(TARGETS async
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT edkolotilov@gmail.com)

include (CPack)
