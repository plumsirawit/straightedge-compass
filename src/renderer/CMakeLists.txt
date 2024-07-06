set(RENDERER_SOURCES 
    "change.cpp" "init.cpp" "load.cpp" "mainloop.cpp" "state.cpp")
set(RENDERER_HEADERS
    "renderer.hpp")

add_library(sc_renderer STATIC
    ${RENDERER_SOURCES}
    ${RENDERER_HEADERS}
)

target_link_libraries(sc_renderer ${ALL_LIBS} sc_base)

target_include_directories(sc_renderer PUBLIC "./")

target_compile_features(sc_renderer PRIVATE cxx_std_17)