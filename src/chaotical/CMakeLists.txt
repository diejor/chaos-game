add_library(chaotical
    experiments.cpp
    ppm_stream.cpp
    rgb_mapping.cpp
)

target_link_libraries(chaotical PRIVATE 
    utils
    grid
)

target_include_directories(chaotical PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

