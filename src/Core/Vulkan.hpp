#ifndef CORE_VULKAN_H_
#define CORE_VULKAN_H_

#include <memory>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>

// Global non-standard headers
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>

//#include "Component/Graphic.hpp"
//#include "Manager/Resource/Texture.hpp"

namespace Core {
class Vulkan {
    public:
    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_LUNARG_standard_validation"
        };
        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
        // Structs
        struct UniformBufferObject {
            glm::mat4 model;
            glm::mat4 view;
            glm::mat4 proj;
        };
        struct Coords {
            glm::vec3 vertex;
            glm::vec2 texCoords;
        };
        struct Vertex {
            glm::vec3 pos;
            glm::vec3 color;

            static VkVertexInputBindingDescription getBindingDescription() {
                VkVertexInputBindingDescription bindingDescription = {};
                bindingDescription.binding = 0;
                bindingDescription.stride = sizeof(Vertex);
                bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

                return bindingDescription;
            }

            static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
                std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

                attributeDescriptions[0].binding = 0;
                attributeDescriptions[0].location = 0;
                attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
                attributeDescriptions[0].offset = offsetof(Vertex, pos);

                attributeDescriptions[1].binding = 0;
                attributeDescriptions[1].location = 1;
                attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
                attributeDescriptions[1].offset = offsetof(Vertex, color);

                return attributeDescriptions;
            }
        };
        struct Object {
            std::vector<Vertex> vertices_ = {
                {{+1.0f, +1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
                {{-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}},
                {{+1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
                {{-1.0f, +1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
                {{+1.0f, +0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}},
                {{+0.0f, +1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
                {{+0.0f, +0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            };
            std::vector<uint16_t> indices_ = {{
                0, 6, 4, 6, 0, 5
            }};
            VkBuffer vertex;
            VkDeviceMemory vertexMemory;
            VkBuffer index;
            VkDeviceMemory indexMemory;
            VkImage image;
            VkDeviceMemory imageMemory;
            VkImageView imageView;
            VkSampler imageSampler;
            std::vector<VkBuffer> mvp;
            std::vector<VkDeviceMemory> mvpMemory;
            std::vector<VkDescriptorSet> descriptorSets;
            struct {
                int h, w;
                std::shared_ptr<void> pixels;
                VkDeviceSize size;
            } data;
        };   
        Vulkan() {
            printf("Created vulkan\n");
        };
        // Vulkan.cpp
        void Initialize();
        void Destroy();
        void CreateVertexBuffer(std::vector<Coords> vertices, VkBuffer& vb, VkDeviceMemory& vbm);
        void CreateIndexBuffer(std::vector<uint16_t> indices, VkBuffer& ib, VkDeviceMemory& ibm);
        /*void CreateUniformBuffers(std::vector<VkBuffer>& ub, std::vector<VkDeviceMemory>& ubm);
        void CreateTextureImage(std::shared_ptr<Manager::Resource::Texture::Object>& texture);
        void CreateTextureSampler(VkSampler& s);
        void CreateDescriptorSets(std::shared_ptr<Manager::Resource::Texture::Object>& texture);
        void CreateCommandBuffers(std::shared_ptr<Manager::Resource::Texture::Object> obj); // temp */
        //void CreateVertexBuffer();
        //void CreateIndexBuffer();
        void CreateUniformBuffers(std::vector<VkBuffer>& mvp, std::vector<VkDeviceMemory>& mvpMemory);
        void UpdateUniformBuffer(UniformBufferObject mvp, std::vector<VkDeviceMemory>& mvpBufferMemory);
        void CreateDescriptorPool();
        //void CreateDescriptorSets(std::shared_ptr<Object>& obj);
        void CreateDescriptorSets(std::vector<VkDescriptorSet>& ds, std::vector<VkBuffer>& mvpBuffer, VkImageView& imageView, VkSampler& imageSampler);
        //void CreateTextureImage(std::shared_ptr<Object>& texture);
        void CreateTextureImage(VkImage& image, VkDeviceMemory& imageMemory, std::shared_ptr<void> pixels, VkDeviceSize size, int height, int width);
        void CreateTextureImageView(VkImage& image, VkImageView& imageView);
        void CreateTextureSampler(VkSampler& imageSampler);
        void CreateCommandBuffers(bool init); // temp
        void StartSecondaryCommandBuffer(uint32_t size);
        //void AddToSecondaryCommandBuffer(std::shared_ptr<Object>& obj, unsigned int i);
        void AddToSecondaryCommandBuffer(VkBuffer vb, VkBuffer ib, uint32_t iSize, std::vector<VkDescriptorSet>& ds, unsigned int objCount);
        void EndSecondaryCommandBuffer();
        //void CreateSecondaryCommandBuffer(std::vector<Component::Graphic> obj);

        VkCommandPool commandPool;

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;

        void DrawFrame(); // Temp

        uint32_t StartFrame();
        void EndFrame();

        // Vulkan_utils.cpp
        void SetInstanceExtensions(std::vector<const char*> extensions);
        void SetWindowSize(uint32_t width, uint32_t height);
        void DestroyBuffer(VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void DestroyBufferArray(std::vector<VkBuffer>& buffer, std::vector<VkDeviceMemory>& bufferMemory);
        //void DestroyTexture(std::shared_ptr<Object>& texture);
        void DestroyTexture(VkImage& image, VkDeviceMemory& imageMemory, VkImageView& imageView, VkSampler& imageSampler);

    private:
        // Structs
        struct QueueFamilyIndices {
            uint32_t graphicsFamily = UINT32_MAX;
            uint32_t presentFamily = UINT32_MAX;

            bool isComplete() {
                if (graphicsFamily == UINT32_MAX || presentFamily == UINT32_MAX) {
                    return false;
                }
                return true;
            }
        };    
        struct SwapChainSupportDetails {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;

            bool isComplete() {
                return !formats.empty() && !presentModes.empty();
            }
        };
        struct WindowSize {
            uint32_t width;
            uint32_t height;
        };
        // Vulkan.cpp
        void DestroySwapChain();
        void RecreateSwapChain();
        void CreateInstance();
        void SetupDebugMessenger();
        void CreateSurface();
        void ChooseDevice();
        void CreateLogicalDevice();
        void CreateSwapChain();
        void CreateImageViews();
        void CreateRenderPass();
        void CreateDescriptorSetLayout();
        void CreateGraphicsPipeline();
        void CreateColorResources();
        void CreateDepthResources();
        void CreateFramebuffers();
        void CreateSyncObjects();
        void CreateCommandPool();
        
        std::vector<VkCommandBuffer>& GetCommandBuffer();
//        void CreateCommandBuffers();

        // Vulkan_utils.cpp
        bool CheckValidationLayerSupport();
        bool IsDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
        bool CheckDeviceFeatureSupport(VkPhysicalDevice device);
        VkSampleCountFlagBits GetMaxUsableSampleCount(); 
        SwapChainSupportDetails FindSwapChainSupport(VkPhysicalDevice device);
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
        VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkFormat FindDepthFormat();
        VkShaderModule CreateShaderModule(const std::vector<char>& code);
        std::vector<char> ReadFile(const std::string& filename);
        uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        void CreateImage(uint32_t width, uint32_t height, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        bool HasStencilComponent(VkFormat format);
        VkCommandBuffer BeginSingleTimeCommands();
        void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
        void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
        void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

        // Variables
        VkInstance instance_;
        std::vector<const char*> instanceExtensions_;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkSurfaceKHR surface_;
        VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;
        VkDevice device_;
        const std::vector<const char*> deviceExtensions_ = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };
        VkSampleCountFlagBits msaaSamples_ = VK_SAMPLE_COUNT_1_BIT;
        VkQueue graphicsQueue_;
        VkQueue presentQueue_;
        // Swapchain
        VkSwapchainKHR swapChain_;
        std::vector<VkImage> swapChainImages_;
        VkFormat swapChainImageFormat_;
        VkExtent2D swapChainExtent_;
        std::vector<VkImageView> swapChainImageViews_;
        std::vector<VkFramebuffer> swapChainFramebuffers_;
        // Render Pass
        VkRenderPass renderPass_;
        // Commands
        VkCommandPool commandPool_;
        std::vector<VkCommandBuffer> primaryCommandBuffers_;
        std::vector<std::vector<VkCommandBuffer>> secondaryCommandBuffers_;

        // DescriptorSetLayout
        VkDescriptorSetLayout descriptorSetLayout;
        // Pipeline
        VkPipelineLayout pipelineLayout_;
        VkPipeline graphicsPipeline_;
        // Depth
        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;
        // MSAA
        VkImage colorImage_;
        VkDeviceMemory colorImageMemory_;
        VkImageView colorImageView_;
        // Sync
        std::vector<VkSemaphore> imageAvailableSemaphores_;
        std::vector<VkSemaphore> renderFinishedSemaphores_;
        std::vector<VkFence> inFlightFences_;
        size_t MAX_FRAMES_IN_FLIGHT = 2;
        size_t currentFrame_ = 0;
        uint32_t currentImageIndex_ = 0;

        WindowSize windowSize_;
        bool windowResized_ = false;  
};
};

#endif // CORE_VULKAN_H_