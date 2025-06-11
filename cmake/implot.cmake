add_library(implot STATIC
        external/implot/implot.cpp
        external/implot/implot_demo.cpp
        external/implot/implot_items.cpp
)

# Include both ImPlot and ImGui headers
target_include_directories(implot PUBLIC
        ${CMAKE_SOURCE_DIR}/external/implot
        ${CMAKE_SOURCE_DIR}/external/imgui
)

# Link against imgui to resolve symbols and headers
target_link_libraries(implot PUBLIC imgui)
