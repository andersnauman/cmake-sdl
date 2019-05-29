#ifndef SYSTEM_RENDER_H_
#define SYSTEM_RENDER_H_

#include <vector>
#include <iostream>

// Global non-standard headers
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/Unique.hpp"
#include "Core/Vulkan.hpp"
#include "Component/Graphic.hpp"
#include "Component/Position.hpp"
#include "Manager/Component.hpp"

namespace System {
class Render {
    public:
        void Update();
        
    private:
};
};
#endif // SYSTEM_RENDER_H_