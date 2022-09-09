set(APP_SOURCES
  main.cpp
  simplex_noise.cpp
)

add_executable(app_plotcraft ${APP_SOURCES})

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

