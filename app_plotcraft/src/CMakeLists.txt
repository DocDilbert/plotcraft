set(APP_SOURCES
  main.cpp
  my_frame.cpp
  simplex_noise.cpp
)

add_executable(app_plotcraft ${APP_SOURCES})

# Add the include directories and make them known to other targets (PUBLIC)
target_include_directories(app_plotcraft PUBLIC ../include)

# Link local libraries
target_link_libraries(app_plotcraft PUBLIC plotcraft)

# Link string format library
target_link_libraries(app_plotcraft PUBLIC fmt)

# Link logging library
target_link_libraries(app_plotcraft PUBLIC spdlog)

# Link command line option library
target_link_libraries(app_plotcraft PUBLIC cxxopts)

# Link GUI library
include(${wxWidgets_USE_FILE})
target_link_libraries(app_plotcraft PUBLIC ${wxWidgets_LIBRARIES})

# Link GUI library
target_link_libraries(app_plotcraft PUBLIC nlohmann_json)

