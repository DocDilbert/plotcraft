# Create the library 
set (PLOTCRAFT_SOURCES 
  plotcraft/plotcraft.cpp
)

add_library(plotcraft ${PLOTCRAFT_SOURCES})

# Add the include directories and make them known to other targets (PUBLIC)
target_include_directories(plotcraft PUBLIC ../include)

# Link extern libraries
target_link_libraries(plotcraft PUBLIC fmt)

target_link_libraries(plotcraft PUBLIC spdlog)

# Link GUI library
target_link_libraries(plotcraft PUBLIC nlohmann_json)

