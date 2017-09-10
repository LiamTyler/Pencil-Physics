#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <glm/glm.hpp>

namespace Config {

    const std::string shaderDir = "./";

    // Shaders
    const std::string shaderVert = shaderDir + "/constant2d.vert";
    const std::string shaderFrag = shaderDir + "/constant2d.frag";

}

#endif
