#ifndef SYSTEM_CAMERA_H_
#define SYSTEM_CAMERA_H_

// Global non-standard headers
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/Vulkan.hpp"

namespace System {
class Camera {
    public:
        Camera() {
            glm::vec3 cameraPos   = glm::vec3(100.0f, 50.0f, -150.0f);
            glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f,  0.0f);
            glm::vec3 cameraUp    = glm::vec3(0.0f, -1.0f,  0.0f);
            view_ = glm::lookAt(cameraPos, cameraFront, cameraUp);
            project_ = glm::perspective(fov_, aspect_, near_, far_);
            //project_[1][1] *= -1;
        };
        void SetViewPosition(glm::vec3 pos);
        //void SetFOV(float fov);
        void SetAspectRatio(float ratio) {
            aspect_ = ratio;
        };
        Core::Vulkan::UniformBufferObject GetMVP(glm::vec3 model) {
            Core::Vulkan::UniformBufferObject mvp;
            mvp.model = glm::translate(mvp.model, model);
            mvp.view = view_;
            mvp.proj = project_;
            return mvp;
        };

    private:
        glm::mat4 view_;
        glm::mat4 project_;
        float fov_ = glm::radians(45.0f);
        float aspect_ = 800.0f / 600.0f;
        float near_ = 0.1f;
        float far_ = 1000.0f;
};
};

#endif // SYSTEM_CAMERA_H_