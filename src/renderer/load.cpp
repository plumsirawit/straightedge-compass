#include "renderer.hpp"
#include <filesystem>

void Manager::load_shader() {
    std::filesystem::path srcdir(CMAKE_CURRENT_SOURCE_DIR);
    std::string vertexshaderpathstr =
        (srcdir / "main" / "SimpleVertexShader.glsl").string();
    std::string fragmentshaderpathstr =
        (srcdir / "main" / "SimpleFragmentShader.glsl").string();
    shader_program_id =
        LoadShaders(vertexshaderpathstr.c_str(), fragmentshaderpathstr.c_str());
}