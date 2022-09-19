# Create the library 
set (PLOTCRAFT_SOURCES 
  plotcraft/plotcraft.cpp
  plotcraft/platforms/wxwidgets/wx_plotcraft_panel.cpp
)

add_library(plotcraft ${PLOTCRAFT_SOURCES})

# Add the include directories and make them known to other targets (PUBLIC)
target_include_directories(plotcraft PUBLIC ../include)

# Link extern libraries
target_link_libraries(plotcraft PUBLIC fmt)

target_link_libraries(plotcraft PUBLIC spdlog)

# Link GUI library
target_link_libraries(plotcraft PUBLIC nlohmann_json)

# Link GUI library
include(${wxWidgets_USE_FILE})
target_link_libraries(plotcraft PUBLIC ${wxWidgets_LIBRARIES})
