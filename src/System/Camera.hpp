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
        struct Resolution {
            float Width;
            float Height;
        };
        Camera() {
            Update();
        };
        void SetViewPosition(glm::vec3 pos);
        glm::vec3 GetViewPosition() {
            return viewPos_;
        };
        glm::vec3 GetLookPosition() {
            return lookPos_;
        };
        Resolution GetResolution() {
            return resolution_;
        };
        glm::vec3 MousePos3D(glm::vec2 pos) {
/*
            glm::mat4 invMat = glm::inverse(project_ * view_);
            glm::vec4 near = glm::vec4((pos.x - resolution_.Width/2) / resolution_.Width/2, -1*(pos.y - resolution_.Height/2) / resolution_.Height/2, -1, 1.0);
            glm::vec4 far = glm::vec4((pos.x - resolution_.Width/2) / resolution_.Width/2, -1*(pos.y - resolution_.Height/2) / resolution_.Height/2, 1, 1.0);
            glm::vec4 nearResult = invMat*near;
            glm::vec4 farResult = invMat*far;
            nearResult /= nearResult.w;
            farResult /= farResult.w;
            glm::vec3 dir = glm::vec3(farResult - nearResult );
            //return glm::normalize(dir);
            return dir;
*/
//            int w = resolution_.Width;
//            int h = resolution_.Height;
//            glm::vec4 viewport = glm::vec4( 0, 0, w, h );

            //return glm::unProject( glm::vec3( pos, 0 ), view_, project_, viewport );

            glm::vec4 const viewport = glm::vec4(0.0f, 0.0f, resolution_.Width, resolution_.Height);

            glm::vec3 wincoord = glm::vec3(pos.x, pos.y, 0.0f);
            glm::vec3 objcoord = glm::unProject(wincoord, view_, project_, viewport);
            printf("Coordinates in object space: %f, %f, %f\n", objcoord.x, objcoord.y, objcoord.z);
            wincoord = glm::vec3(pos.x, pos.y, 1.0f);
            objcoord = glm::unProject(wincoord, view_, project_, viewport);
            printf("Coordinates in object space: %f, %f, %f\n", objcoord.x, objcoord.y, objcoord.z);            
            return objcoord;
        };
        //void SetFOV(float fov);
        void SetResolution(uint32_t height, uint32_t width) {
            resolution_.Height = (float)height;
            resolution_.Width = (float)width;
            aspect_ = resolution_.Height / resolution_.Width;
            Update();
        };
        void Update() {
            glm::vec3 cameraPos   = viewPos_;
            glm::vec3 cameraFront = lookPos_;
            glm::vec3 cameraUp    = glm::vec3(0.0f, -1.0f,  0.0f);
            view_ = glm::lookAt(cameraPos, cameraFront, cameraUp);
            project_ = glm::perspective(fov_, aspect_, near_, far_);
        };
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
        //glm::vec3 viewPos_ = glm::vec3(100.0f, 50.0f, -150.0f);
        glm::vec3 viewPos_ = glm::vec3(0.0f, 0.0f, -50.0f);
        glm::vec3 lookPos_ = glm::vec3(0.0f, 0.0f,  0.0f);
        glm::mat4 view_;
        glm::mat4 project_;
        Resolution resolution_ = {800.0f, 600.0f};
        float fov_ = glm::radians(45.0f);
        float aspect_ = resolution_.Width / resolution_.Height;
        float near_ = 0.1f;
        float far_ = 1000.0f;
};
};

#endif // SYSTEM_CAMERA_H_