add_library(grid
    grid.cpp
    point.cpp
    vec2.cpp
)

target_link_libraries(grid PRIVATE utils)

target_include_directories(grid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
