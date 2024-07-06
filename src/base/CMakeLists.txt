set(BASE_SOURCES 
    "object.cpp" "loadShader.cpp")
set(BASE_HEADERS
    "base.hpp" "loadShader.hpp")

add_library(sc_base STATIC
    ${BASE_SOURCES}
    ${BASE_HEADERS}
)

target_link_libraries(sc_base ${ALL_LIBS})

target_include_directories(sc_base PUBLIC "./")

target_compile_features(sc_base PRIVATE cxx_std_17)