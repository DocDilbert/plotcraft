cmake_minimum_required (VERSION 3.2.0)

#include(cmake/print_target_properties.cmake)

# Project name and a few useful settings. Other commands can pick up the results
project(
  PlotCraft 
  VERSION 0.1.1
  DESCRIPTION "PlotCraft library"
  LANGUAGES CXX C)

set (CMAKE_CXX_STANDARD 20)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

  # Cxx extensions(aka -std=gnu++20) needed by wxWidgets compiling on mac
  set(CMAKE_CXX_EXTENSIONS ON)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app
  # Note this needs to be done in the main CMakeLists
  # since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)
  # Docs only available if this is the main app
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()


# ------------------------------------
# nlohmann json library
# ------------------------------------
add_subdirectory(extern/nlohmann_json EXCLUDE_FROM_ALL)

# ------------------------------------
# FMT
# ------------------------------------
add_subdirectory(extern/fmt EXCLUDE_FROM_ALL)

# ------------------------------------
# SPDLOG 
# ------------------------------------
set(SPDLOG_FMT_EXTERNAL ON) # Don't use internal fmt. Its provided directly!
add_subdirectory(extern/spdlog EXCLUDE_FROM_ALL)

# ------------------------------------
# CXXOPTS
# ------------------------------------
add_subdirectory(extern/cxxopts EXCLUDE_FROM_ALL)

# ------------------------------------
# wxWidgets
# ------------------------------------
find_package(wxWidgets REQUIRED gl core base)

# ------------------------------------
# Library: plotcraft 
# ------------------------------------
add_subdirectory(src)

# ------------------------------------
# Application: app_plotcraft 
# ------------------------------------
add_subdirectory(app_plotcraft)

# Testing only available if this is the main app
if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
  include(GoogleTest)
  add_subdirectory(tests)
endif()
