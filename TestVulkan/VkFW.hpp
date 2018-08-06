#pragma once

#pragma region header_parameter_list
/*
#define VKFW_DEBUG_MODE
#define VKFW_VERSION_MAJOR Number
#define VKFW_VERSION_MINOR Number
#define VKFW_KHR_surface
#define VKFW_KHR_win32_surface
#define VKFW_KHR_swapchain
*/
#pragma endregion

#pragma region include_std
#include <string>
#include <iostream>
#pragma endregion

#pragma region vulkan_header_argument_begin
#ifdef VKFW_KHR_surface
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
#pragma push_macro("WIN32_LEAN_AND_MEAN")
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma push_macro("VK_USE_PLATFORM_WIN32_KHR")
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#endif
#pragma endregion

#include <vulkan\vulkan.h>

#pragma region external_macro
#define VKFW_DEBUG(value) ::Vk::Debug(__LINE__, value)
#pragma endregion

#pragma region internal_macro_begin
#pragma push_macro("VKFW_ASSIGN")
#define VKFW_ASSIGN(Type, id)																			\
	template<typename = Type>																			\
	inline static void id(...) {}																		\
																										\
	template<typename T##Type = Type>																	\
	inline static void id(T##Type *t, decltype(T##Type::id) val) {										\
		t->id = val;																					\
	}																									\
																										\
	template<typename T##Type = Type, typename F##Type, typename Arg##Type>								\
	inline static void id(T##Type *t, F##Type f, Arg##Type arg, decltype(T##Type::id)* = nullptr) {		\
		f(arg, #id, reinterpret_cast<void**>(&t->id));													\
	}

#pragma push_macro("VKFW_STYPE")
#define VKFW_STYPE(Type, val)					\
	inline Type& SType(Type &ref) {				\
		ref.sType =  VK_STRUCTURE_TYPE_##val;	\
		return ref;								\
	}

#pragma push_macro("VKFW_HANDLE")
#define VKFW_HANDLE(Class, HandleType, varName)					\
	inline Class() = default;									\
	inline Class(const Class &rhs) : Class(rhs.varName) {}		\
	inline Class(Class &&rhs) : Class(rhs.varName) {}			\
	inline Class(HandleType handle) : varName(handle) {}		\
	inline Class(decltype(nullptr)) : varName(nullptr) {}		\
																\
	inline Class& operator=(const Class &rhs) {					\
		return operator=(rhs.varName);							\
	}															\
																\
	inline Class& operator=(Class &&rhs) {						\
		return operator=(rhs.varName);							\
	}															\
																\
	inline Class& operator=(HandleType rhs) {					\
		varName = rhs;											\
		return *this;											\
	}															\
																\
	inline Class& operator=(decltype(nullptr)) {				\
		varName = nullptr;										\
		return *this;											\
	}															\
																\
	inline HandleType* operator&() {							\
		return &varName;										\
	}															\
																\
	inline operator HandleType&() {								\
		return varName;											\
	}															\
																\
	inline operator const HandleType&() const {					\
		return varName;											\
	}
#pragma endregion

namespace Vk {
#pragma region util_type
	template<typename>
	class FnType;

	template<typename Return, typename... Args>
	class FnType<Return(VKAPI_PTR)(Args...)> {
	public:
		using Eval = Return(VKAPI_PTR*)(Args...);
	};
#pragma endregion

#pragma region util_function
	inline void ShowError(std::string head, std::string body) {
#ifdef _WINDOWS_
		MessageBoxA(nullptr, body.c_str(), head.c_str(), MB_OK | MB_ICONERROR);
#else
		std::cout << head << body << std::endl;
#endif
	}
#pragma endregion

#pragma region vulkan_function
	inline VkResult CreateInstance(const VkInstanceCreateInfo *pCreateInfo, VkInstance *pInstance, const VkAllocationCallbacks *pAllocator = nullptr) {
		return vkCreateInstance(pCreateInfo, pAllocator, pInstance);
	}

	template<typename Return, typename... Args>
	inline void GetInstanceProcAddr(VkInstance vjInstance, const char *pName, Return(VKAPI_PTR*&f)(Args...)) {
		f = reinterpret_cast<Return(VKAPI_PTR*)(Args...)>(vkGetInstanceProcAddr(vjInstance, pName));
	}

	template<typename Return, typename... Args>
	inline void GetInstanceProcAddr(const char *pName, Return(VKAPI_PTR*&f)(Args...)) {
		GetInstanceProcAddr(VK_NULL_HANDLE, pName, f);
	}

	template<typename Return, typename... Args>
	inline void GetDeviceProcAddr(VkDevice vkDevice, const char *pName, Return(VKAPI_PTR*&f)(Args...)) {
		f = reinterpret_cast<Return(VKAPI_PTR*)(Args...)>(vkGetDeviceProcAddr(vkDevice, pName));
	}

#if VKFW_VERSION_MAJOR > 1 || (VKFW_VERSION_MAJOR == 1  && VKFW_VERSION_MINOR >= 1)
	inline VkResult	EnumerateInstanceVersion(uint32_t *pApiVersion) {
		return vkEnumerateInstanceVersion(pApiVersion);
	}
#endif
#pragma endregion

#pragma region vulkan_sType
	VKFW_STYPE(VkApplicationInfo, APPLICATION_INFO);
	VKFW_STYPE(VkInstanceCreateInfo, INSTANCE_CREATE_INFO);
	VKFW_STYPE(VkDeviceQueueCreateInfo, DEVICE_QUEUE_CREATE_INFO);
	VKFW_STYPE(VkDeviceCreateInfo, DEVICE_CREATE_INFO);
	VKFW_STYPE(VkSubmitInfo, SUBMIT_INFO);
	VKFW_STYPE(VkMemoryAllocateInfo, MEMORY_ALLOCATE_INFO);
	VKFW_STYPE(VkMappedMemoryRange, MAPPED_MEMORY_RANGE);
	VKFW_STYPE(VkBindSparseInfo, BIND_SPARSE_INFO);
	VKFW_STYPE(VkFenceCreateInfo, FENCE_CREATE_INFO);
	VKFW_STYPE(VkSemaphoreCreateInfo, SEMAPHORE_CREATE_INFO);
	VKFW_STYPE(VkEventCreateInfo, EVENT_CREATE_INFO);
	VKFW_STYPE(VkQueryPoolCreateInfo, QUERY_POOL_CREATE_INFO);
	VKFW_STYPE(VkBufferCreateInfo, BUFFER_CREATE_INFO);
	VKFW_STYPE(VkBufferViewCreateInfo, BUFFER_VIEW_CREATE_INFO);
	VKFW_STYPE(VkImageCreateInfo, IMAGE_CREATE_INFO);
	VKFW_STYPE(VkImageViewCreateInfo, IMAGE_VIEW_CREATE_INFO);
	VKFW_STYPE(VkShaderModuleCreateInfo, SHADER_MODULE_CREATE_INFO);
	VKFW_STYPE(VkPipelineCacheCreateInfo, PIPELINE_CACHE_CREATE_INFO);
	VKFW_STYPE(VkPipelineShaderStageCreateInfo, PIPELINE_SHADER_STAGE_CREATE_INFO);
	VKFW_STYPE(VkPipelineVertexInputStateCreateInfo, PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO);
	VKFW_STYPE(VkPipelineInputAssemblyStateCreateInfo, PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO);
	VKFW_STYPE(VkPipelineTessellationStateCreateInfo, PIPELINE_TESSELLATION_STATE_CREATE_INFO);
	VKFW_STYPE(VkPipelineViewportStateCreateInfo, PIPELINE_VIEWPORT_STATE_CREATE_INFO);
	VKFW_STYPE(VkPipelineRasterizationStateCreateInfo, PIPELINE_RASTERIZATION_STATE_CREATE_INFO);
	VKFW_STYPE(VkPipelineMultisampleStateCreateInfo, PIPELINE_MULTISAMPLE_STATE_CREATE_INFO);
	VKFW_STYPE(VkPipelineDepthStencilStateCreateInfo, PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO);
	VKFW_STYPE(VkPipelineColorBlendStateCreateInfo, PIPELINE_COLOR_BLEND_STATE_CREATE_INFO);
	VKFW_STYPE(VkPipelineDynamicStateCreateInfo, PIPELINE_DYNAMIC_STATE_CREATE_INFO);
	VKFW_STYPE(VkGraphicsPipelineCreateInfo, GRAPHICS_PIPELINE_CREATE_INFO);
	VKFW_STYPE(VkComputePipelineCreateInfo, COMPUTE_PIPELINE_CREATE_INFO);
	VKFW_STYPE(VkPipelineLayoutCreateInfo, PIPELINE_LAYOUT_CREATE_INFO);
	VKFW_STYPE(VkSamplerCreateInfo, SAMPLER_CREATE_INFO);
	VKFW_STYPE(VkDescriptorSetLayoutCreateInfo, DESCRIPTOR_SET_LAYOUT_CREATE_INFO);
	VKFW_STYPE(VkDescriptorPoolCreateInfo, DESCRIPTOR_POOL_CREATE_INFO);
	VKFW_STYPE(VkDescriptorSetAllocateInfo, DESCRIPTOR_SET_ALLOCATE_INFO);
	VKFW_STYPE(VkWriteDescriptorSet, WRITE_DESCRIPTOR_SET);
	VKFW_STYPE(VkCopyDescriptorSet, COPY_DESCRIPTOR_SET);
	VKFW_STYPE(VkFramebufferCreateInfo, FRAMEBUFFER_CREATE_INFO);
	VKFW_STYPE(VkRenderPassCreateInfo, RENDER_PASS_CREATE_INFO);
	VKFW_STYPE(VkCommandPoolCreateInfo, COMMAND_POOL_CREATE_INFO);
	VKFW_STYPE(VkCommandBufferAllocateInfo, COMMAND_BUFFER_ALLOCATE_INFO);
	VKFW_STYPE(VkCommandBufferInheritanceInfo, COMMAND_BUFFER_INHERITANCE_INFO);
	VKFW_STYPE(VkCommandBufferBeginInfo, COMMAND_BUFFER_BEGIN_INFO);
	VKFW_STYPE(VkRenderPassBeginInfo, RENDER_PASS_BEGIN_INFO);
	VKFW_STYPE(VkBufferMemoryBarrier, BUFFER_MEMORY_BARRIER);
	VKFW_STYPE(VkImageMemoryBarrier, IMAGE_MEMORY_BARRIER);
	VKFW_STYPE(VkMemoryBarrier, MEMORY_BARRIER);
#ifdef VKFW_KHR_surface
#ifdef VKFW_KHR_swapchain
	VKFW_STYPE(VkSwapchainCreateInfoKHR, SWAPCHAIN_CREATE_INFO_KHR);
	VKFW_STYPE(VkPresentInfoKHR, PRESENT_INFO_KHR);
#endif
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
	VKFW_STYPE(VkWin32SurfaceCreateInfoKHR, WIN32_SURFACE_CREATE_INFO_KHR);
#endif
#endif
#pragma endregion

#pragma region vulkan_assign_procAddrs
	template<typename Type>
	class Assign {
	public:
		// Instance
		VKFW_ASSIGN(Type, vkCreateDevice);
		VKFW_ASSIGN(Type, vkDestroyInstance);
		VKFW_ASSIGN(Type, vkEnumerateDeviceExtensionProperties);
		VKFW_ASSIGN(Type, vkEnumerateDeviceLayerProperties);
		VKFW_ASSIGN(Type, vkEnumeratePhysicalDevices);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceFeatures);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceFormatProperties);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceImageFormatProperties);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceMemoryProperties);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceProperties);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceQueueFamilyProperties);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceSparseImageFormatProperties);
		// Device
		VKFW_ASSIGN(Type, vkAllocateCommandBuffers);
		VKFW_ASSIGN(Type, vkAllocateDescriptorSets);
		VKFW_ASSIGN(Type, vkAllocateMemory);
		VKFW_ASSIGN(Type, vkBeginCommandBuffer);
		VKFW_ASSIGN(Type, vkBindBufferMemory);
		VKFW_ASSIGN(Type, vkBindImageMemory);
		VKFW_ASSIGN(Type, vkCmdBeginQuery);
		VKFW_ASSIGN(Type, vkCmdBeginRenderPass);
		VKFW_ASSIGN(Type, vkCmdBindDescriptorSets);
		VKFW_ASSIGN(Type, vkCmdBindIndexBuffer);
		VKFW_ASSIGN(Type, vkCmdBindPipeline);
		VKFW_ASSIGN(Type, vkCmdBindVertexBuffers);
		VKFW_ASSIGN(Type, vkCmdBlitImage);
		VKFW_ASSIGN(Type, vkCmdClearAttachments);
		VKFW_ASSIGN(Type, vkCmdClearColorImage);
		VKFW_ASSIGN(Type, vkCmdClearDepthStencilImage);
		VKFW_ASSIGN(Type, vkCmdCopyBuffer);
		VKFW_ASSIGN(Type, vkCmdCopyBufferToImage);
		VKFW_ASSIGN(Type, vkCmdCopyImage);
		VKFW_ASSIGN(Type, vkCmdCopyImageToBuffer);
		VKFW_ASSIGN(Type, vkCmdCopyQueryPoolResults);
		VKFW_ASSIGN(Type, vkCmdDispatch);
		VKFW_ASSIGN(Type, vkCmdDispatchIndirect);
		VKFW_ASSIGN(Type, vkCmdDraw);
		VKFW_ASSIGN(Type, vkCmdDrawIndexed);
		VKFW_ASSIGN(Type, vkCmdDrawIndexedIndirect);
		VKFW_ASSIGN(Type, vkCmdDrawIndirect);
		VKFW_ASSIGN(Type, vkCmdEndQuery);
		VKFW_ASSIGN(Type, vkCmdEndRenderPass);
		VKFW_ASSIGN(Type, vkCmdExecuteCommands);
		VKFW_ASSIGN(Type, vkCmdFillBuffer);
		VKFW_ASSIGN(Type, vkCmdNextSubpass);
		VKFW_ASSIGN(Type, vkCmdPipelineBarrier);
		VKFW_ASSIGN(Type, vkCmdPushConstants);
		VKFW_ASSIGN(Type, vkCmdResetEvent);
		VKFW_ASSIGN(Type, vkCmdResetQueryPool);
		VKFW_ASSIGN(Type, vkCmdResolveImage);
		VKFW_ASSIGN(Type, vkCmdSetBlendConstants);
		VKFW_ASSIGN(Type, vkCmdSetDepthBias);
		VKFW_ASSIGN(Type, vkCmdSetDepthBounds);
		VKFW_ASSIGN(Type, vkCmdSetEvent);
		VKFW_ASSIGN(Type, vkCmdSetLineWidth);
		VKFW_ASSIGN(Type, vkCmdSetScissor);
		VKFW_ASSIGN(Type, vkCmdSetStencilCompareMask);
		VKFW_ASSIGN(Type, vkCmdSetStencilReference);
		VKFW_ASSIGN(Type, vkCmdSetStencilWriteMask);
		VKFW_ASSIGN(Type, vkCmdSetViewport);
		VKFW_ASSIGN(Type, vkCmdUpdateBuffer);
		VKFW_ASSIGN(Type, vkCmdWaitEvents);
		VKFW_ASSIGN(Type, vkCmdWriteTimestamp);
		VKFW_ASSIGN(Type, vkCreateBuffer);
		VKFW_ASSIGN(Type, vkCreateBufferView);
		VKFW_ASSIGN(Type, vkCreateCommandPool);
		VKFW_ASSIGN(Type, vkCreateComputePipelines);
		VKFW_ASSIGN(Type, vkCreateDescriptorPool);
		VKFW_ASSIGN(Type, vkCreateDescriptorSetLayout);
		VKFW_ASSIGN(Type, vkCreateEvent);
		VKFW_ASSIGN(Type, vkCreateFence);
		VKFW_ASSIGN(Type, vkCreateFramebuffer);
		VKFW_ASSIGN(Type, vkCreateGraphicsPipelines);
		VKFW_ASSIGN(Type, vkCreateImage);
		VKFW_ASSIGN(Type, vkCreateImageView);
		VKFW_ASSIGN(Type, vkCreatePipelineCache);
		VKFW_ASSIGN(Type, vkCreatePipelineLayout);
		VKFW_ASSIGN(Type, vkCreateQueryPool);
		VKFW_ASSIGN(Type, vkCreateRenderPass);
		VKFW_ASSIGN(Type, vkCreateSampler);
		VKFW_ASSIGN(Type, vkCreateSemaphore);
		VKFW_ASSIGN(Type, vkCreateShaderModule);
		VKFW_ASSIGN(Type, vkDestroyBuffer);
		VKFW_ASSIGN(Type, vkDestroyBufferView);
		VKFW_ASSIGN(Type, vkDestroyCommandPool);
		VKFW_ASSIGN(Type, vkDestroyDescriptorPool);
		VKFW_ASSIGN(Type, vkDestroyDescriptorSetLayout);
		VKFW_ASSIGN(Type, vkDestroyDevice);
		VKFW_ASSIGN(Type, vkDestroyEvent);
		VKFW_ASSIGN(Type, vkDestroyFence);
		VKFW_ASSIGN(Type, vkDestroyFramebuffer);
		VKFW_ASSIGN(Type, vkDestroyImage);
		VKFW_ASSIGN(Type, vkDestroyImageView);
		VKFW_ASSIGN(Type, vkDestroyPipeline);
		VKFW_ASSIGN(Type, vkDestroyPipelineCache);
		VKFW_ASSIGN(Type, vkDestroyPipelineLayout);
		VKFW_ASSIGN(Type, vkDestroyQueryPool);
		VKFW_ASSIGN(Type, vkDestroyRenderPass);
		VKFW_ASSIGN(Type, vkDestroySampler);
		VKFW_ASSIGN(Type, vkDestroySemaphore);
		VKFW_ASSIGN(Type, vkDestroyShaderModule);
		VKFW_ASSIGN(Type, vkDeviceWaitIdle);
		VKFW_ASSIGN(Type, vkEndCommandBuffer);
		VKFW_ASSIGN(Type, vkFlushMappedMemoryRanges);
		VKFW_ASSIGN(Type, vkFreeCommandBuffers);
		VKFW_ASSIGN(Type, vkFreeDescriptorSets);
		VKFW_ASSIGN(Type, vkFreeMemory);
		VKFW_ASSIGN(Type, vkGetBufferMemoryRequirements);
		VKFW_ASSIGN(Type, vkGetDeviceMemoryCommitment);
		VKFW_ASSIGN(Type, vkGetDeviceQueue);
		VKFW_ASSIGN(Type, vkGetEventStatus);
		VKFW_ASSIGN(Type, vkGetFenceStatus);
		VKFW_ASSIGN(Type, vkGetImageMemoryRequirements);
		VKFW_ASSIGN(Type, vkGetImageSparseMemoryRequirements);
		VKFW_ASSIGN(Type, vkGetImageSubresourceLayout);
		VKFW_ASSIGN(Type, vkGetPipelineCacheData);
		VKFW_ASSIGN(Type, vkGetQueryPoolResults);
		VKFW_ASSIGN(Type, vkGetRenderAreaGranularity);
		VKFW_ASSIGN(Type, vkInvalidateMappedMemoryRanges);
		VKFW_ASSIGN(Type, vkMapMemory);
		VKFW_ASSIGN(Type, vkMergePipelineCaches);
		VKFW_ASSIGN(Type, vkQueueBindSparse);
		VKFW_ASSIGN(Type, vkQueueSubmit);
		VKFW_ASSIGN(Type, vkQueueWaitIdle);
		VKFW_ASSIGN(Type, vkResetCommandBuffer);
		VKFW_ASSIGN(Type, vkResetCommandPool);
		VKFW_ASSIGN(Type, vkResetDescriptorPool);
		VKFW_ASSIGN(Type, vkResetEvent);
		VKFW_ASSIGN(Type, vkResetFences);
		VKFW_ASSIGN(Type, vkSetEvent);
		VKFW_ASSIGN(Type, vkUnmapMemory);
		VKFW_ASSIGN(Type, vkUpdateDescriptorSets);
		VKFW_ASSIGN(Type, vkWaitForFences);

#if VKFW_VERSION_MAJOR > 1 || (VKFW_VERSION_MAJOR == 1  && VKFW_VERSION_MINOR >= 1)
		// Instance
		VKFW_ASSIGN(Type, vkEnumeratePhysicalDeviceGroups);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceProperties2);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceQueueFamilyProperties2);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceSparseImageFormatProperties2);
		// Device
		VKFW_ASSIGN(Type, vkBindBufferMemory2);
		VKFW_ASSIGN(Type, vkBindImageMemory2);
		VKFW_ASSIGN(Type, vkCreateDescriptorUpdateTemplate);
		VKFW_ASSIGN(Type, vkCreateSamplerYcbcrConversion);
		VKFW_ASSIGN(Type, vkDestroyDescriptorUpdateTemplate);
		VKFW_ASSIGN(Type, vkDestroySamplerYcbcrConversion);
		VKFW_ASSIGN(Type, vkGetBufferMemoryRequirements2);
		VKFW_ASSIGN(Type, vkGetDescriptorSetLayoutSupport);
		VKFW_ASSIGN(Type, vkGetDeviceGroupPeerMemoryFeatures);
		VKFW_ASSIGN(Type, vkGetDeviceQueue2);
		VKFW_ASSIGN(Type, vkGetImageMemoryRequirements2);
		VKFW_ASSIGN(Type, vkGetImageSparseMemoryRequirements2);
		VKFW_ASSIGN(Type, vkTrimCommandPool);
		VKFW_ASSIGN(Type, vkUpdateDescriptorSetWithTemplate);

#endif
#ifdef VKFW_KHR_surface
		// Instance
		VKFW_ASSIGN(Type, vkDestroySurfaceKHR);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceSurfaceSupportKHR);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceSurfaceFormatsKHR);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceSurfacePresentModesKHR);
#ifdef VKFW_KHR_swapchain
		// Device
		VKFW_ASSIGN(Type, vkCreateSwapchainKHR);
		VKFW_ASSIGN(Type, vkDestroySwapchainKHR);
		VKFW_ASSIGN(Type, vkQueuePresentKHR);
		VKFW_ASSIGN(Type, vkAcquireNextImageKHR);
		VKFW_ASSIGN(Type, vkGetSwapchainImagesKHR);
#endif
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
		// Instance
		VKFW_ASSIGN(Type, vkCreateWin32SurfaceKHR);
		VKFW_ASSIGN(Type, vkGetPhysicalDeviceWin32PresentationSupportKHR);
#endif
#endif
	};

	void AssignInstanceProcAddrs(VkInstance vkInstance, const char *pName, void **pf) {
		*pf = vkGetInstanceProcAddr(vkInstance, pName);
	}

	void AssignDeviceProcAddrs(VkInstance vkInstance, const char *pName, void **pf) {
		*pf = vkGetInstanceProcAddr(vkInstance, pName);
	}

	template<typename Type>
	inline void GetInstanceProcAddrs(VkInstance vkInstance, Type *t) {
		Assign<Type>::vkCreateDevice<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkDestroyInstance<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkEnumerateDeviceExtensionProperties<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkEnumerateDeviceLayerProperties<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkEnumeratePhysicalDevices<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceFeatures<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceFormatProperties<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceImageFormatProperties<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceMemoryProperties<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceProperties<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceQueueFamilyProperties<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceSparseImageFormatProperties<>(t, AssignInstanceProcAddrs, vkInstance);
#if VKFW_VERSION_MAJOR > 1 || (VKFW_VERSION_MAJOR == 1  && VKFW_VERSION_MINOR >= 1)
		Assign<Type>::vkEnumeratePhysicalDeviceGroups<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceProperties2<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceQueueFamilyProperties2<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceSparseImageFormatProperties2<>(t, AssignInstanceProcAddrs, vkInstance);
#endif
#ifdef VKFW_KHR_surface
		Assign<Type>::vkDestroySurfaceKHR<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceSurfaceSupportKHR<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceSurfaceCapabilitiesKHR<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceSurfaceFormatsKHR<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceSurfacePresentModesKHR<>(t, AssignInstanceProcAddrs, vkInstance);
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
		Assign<Type>::vkCreateWin32SurfaceKHR<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetPhysicalDeviceWin32PresentationSupportKHR<>(t, AssignInstanceProcAddrs, vkInstance);
#endif
#endif
	}

	template<typename Type>
	inline void GetDeviceProcAddrs(VkDevice vkDevice, Type *t) {
		Assign<Type>::vkAllocateCommandBuffers<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkAllocateDescriptorSets<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkAllocateMemory<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkBeginCommandBuffer<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkBindBufferMemory<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkBindImageMemory<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdBeginQuery<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdBeginRenderPass<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdBindDescriptorSets<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdBindIndexBuffer<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdBindPipeline<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdBindVertexBuffers<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdBlitImage<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdClearAttachments<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdClearColorImage<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdClearDepthStencilImage<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdCopyBuffer<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdCopyBufferToImage<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdCopyImage<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdCopyImageToBuffer<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdCopyQueryPoolResults<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdDispatch<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdDispatchIndirect<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdDraw<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdDrawIndexed<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdDrawIndexedIndirect<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdDrawIndirect<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdEndQuery<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdEndRenderPass<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdExecuteCommands<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdFillBuffer<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdNextSubpass<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdPipelineBarrier<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdPushConstants<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdResetEvent<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdResetQueryPool<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdResolveImage<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdSetBlendConstants<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdSetDepthBias<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdSetDepthBounds<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdSetEvent<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdSetLineWidth<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdSetScissor<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdSetStencilCompareMask<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdSetStencilReference<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdSetStencilWriteMask<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdSetViewport<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdUpdateBuffer<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdWaitEvents<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCmdWriteTimestamp<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateBuffer<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateBufferView<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateCommandPool<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateComputePipelines<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateDescriptorPool<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateDescriptorSetLayout<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateEvent<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateFence<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateFramebuffer<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateGraphicsPipelines<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateImage<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateImageView<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreatePipelineCache<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreatePipelineLayout<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateQueryPool<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateRenderPass<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateSampler<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateSemaphore<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateShaderModule<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyBuffer<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyBufferView<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyCommandPool<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyDescriptorPool<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyDescriptorSetLayout<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyDevice<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyEvent<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyFence<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyFramebuffer<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyImage<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyImageView<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyPipeline<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyPipelineCache<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyPipelineLayout<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyQueryPool<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyRenderPass<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroySampler<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroySemaphore<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyShaderModule<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDeviceWaitIdle<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkEndCommandBuffer<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkFlushMappedMemoryRanges<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkFreeCommandBuffers<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkFreeDescriptorSets<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkFreeMemory<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetBufferMemoryRequirements<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetDeviceMemoryCommitment<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetDeviceQueue<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetEventStatus<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetFenceStatus<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetImageMemoryRequirements<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetImageSparseMemoryRequirements<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetImageSubresourceLayout<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetPipelineCacheData<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetQueryPoolResults<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetRenderAreaGranularity<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkInvalidateMappedMemoryRanges<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkMapMemory<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkMergePipelineCaches<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkQueueBindSparse<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkQueueSubmit<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkQueueWaitIdle<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkResetCommandBuffer<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkResetCommandPool<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkResetDescriptorPool<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkResetEvent<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkResetFences<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkSetEvent<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkUnmapMemory<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkUpdateDescriptorSets<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkWaitForFences<>(t, AssignDeviceProcAddrs, vkDevice);
#if VKFW_VERSION_MAJOR > 1 || (VKFW_VERSION_MAJOR == 1  && VKFW_VERSION_MINOR >= 1)
		Assign<Type>::vkBindBufferMemory2<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkBindImageMemory2<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateDescriptorUpdateTemplate<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkCreateSamplerYcbcrConversion<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroyDescriptorUpdateTemplate<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkDestroySamplerYcbcrConversion<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetBufferMemoryRequirements2<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetDescriptorSetLayoutSupport<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetDeviceGroupPeerMemoryFeatures<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetDeviceQueue2<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetImageMemoryRequirements2<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkGetImageSparseMemoryRequirements2<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkTrimCommandPool<>(t, AssignDeviceProcAddrs, vkDevice);
		Assign<Type>::vkUpdateDescriptorSetWithTemplate<>(t, AssignDeviceProcAddrs, vkDevice);
#endif
#ifdef VKFW_KHR_surface
#ifdef VKFW_KHR_swapchain
		Assign<Type>::vkCreateSwapchainKHR<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkDestroySwapchainKHR<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkQueuePresentKHR<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkAcquireNextImageKHR<>(t, AssignInstanceProcAddrs, vkInstance);
		Assign<Type>::vkGetSwapchainImagesKHR<>(t, AssignInstanceProcAddrs, vkInstance);
#endif
#endif
	}
#pragma endregion

#pragma region vulkan_handle
	class Instance {
		VkInstance m_handle;

		inline void debug_after_enumeratePhysicalDevices(uint32_t *pPhysicalDeviceCount, VkPhysicalDevice *pPhysicalDevices) const {
#ifdef VKFW_DEBUG_MODE
			bool isError = false;
			std::string body;
			if (pPhysicalDevices == nullptr && *pPhysicalDeviceCount == 0) {
				if (!isError) isError = true;
				body += "No physical device\n";
			}
			if (isError) ShowError("enumeratePhysicalDevices", body);
#endif
		}
	public:
		VKFW_HANDLE(Instance, VkInstance, m_handle);

		inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
			vkDestroyInstance(m_handle, pAllocator);
		}

		template<typename Type>
		inline void destroy(Type *t, const VkAllocationCallbacks *pAllocator = nullptr) {
			t->vkDestroyInstance(m_handle, pAllocator);
		}

		inline VkResult enumeratePhysicalDevices(uint32_t *pPhysicalDeviceCount, VkPhysicalDevice *pPhysicalDevices = nullptr) const {
			VkResult vkResult = vkEnumeratePhysicalDevices(m_handle, pPhysicalDeviceCount, pPhysicalDevices);
			debug_after_enumeratePhysicalDevices(pPhysicalDeviceCount, pPhysicalDevices);
			return vkResult;
		}

		template<typename Type>
		inline VkResult enumeratePhysicalDevices(Type *t, uint32_t *pPhysicalDeviceCount, VkPhysicalDevice *pPhysicalDevices = nullptr) const {
			VkResult vkResult = t->vkEnumeratePhysicalDevices(m_handle, pPhysicalDeviceCount, pPhysicalDevices);
			debug_after_enumeratePhysicalDevices(pPhysicalDeviceCount, pPhysicalDevices);
			return vkResult;
		}
#if VKFW_VERSION_MAJOR > 1 || (VKFW_VERSION_MAJOR == 1  && VKFW_VERSION_MINOR >= 1)
		inline VkResult enumeratePhysicalDeviceGroups(uint32_t *pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties *pPhysicalDeviceGroupProperties = nullptr) {
			return vkEnumeratePhysicalDeviceGroups(m_handle, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
		}

		template<typename Type>
		inline VkResult enumeratePhysicalDeviceGroups(Type *t, uint32_t *pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties *pPhysicalDeviceGroupProperties = nullptr) {
			return t->vkEnumeratePhysicalDeviceGroups(m_handle, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
		}
#endif
#ifdef VKFW_KHR_surface
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
		inline VkResult createWin32Surface(const VkWin32SurfaceCreateInfoKHR *pCreateInfo, VkSurfaceKHR *pSurface, const VkAllocationCallbacks *pAllocator = nullptr) {
			return vkCreateWin32SurfaceKHR(m_handle, pCreateInfo, pAllocator, pSurface);
		}

		template<typename Type>
		inline VkResult createWin32Surface(Type *t, const VkWin32SurfaceCreateInfoKHR *pCreateInfo, VkSurfaceKHR *pSurface, const VkAllocationCallbacks *pAllocator = nullptr) {
			return t->vkCreateWin32SurfaceKHR(m_handle, pCreateInfo, pAllocator, pSurface);
		}
#endif
#endif
	};

	class PhysicalDevice {
		VkPhysicalDevice m_handle;
	public:
		VKFW_HANDLE(PhysicalDevice, VkPhysicalDevice, m_handle);

		inline void getProperties(VkPhysicalDeviceProperties *properties) const {
			vkGetPhysicalDeviceProperties(m_handle, properties);
		}

		template<typename Type>
		inline void getProperties(Type *t, VkPhysicalDeviceProperties *properties) const {
			t->vkGetPhysicalDeviceProperties(m_handle, properties);
		}
	};
#pragma endregion

#pragma region vulkan_debug
#pragma region vulkan_debug_funtion_return
	inline VkResult Debug(int lineNum, VkResult vkResult) {
#ifdef VKFW_DEBUG_MODE
		if (vkResult < 0) {
			std::string head = std::string("VkResult : line ") + std::to_string(lineNum);
			switch (vkResult) {
			case -1: ShowError(head, "VK_ERROR_OUT_OF_HOST_MEMORY"); break;
			case -2: ShowError(head, "VK_ERROR_OUT_OF_DEVICE_MEMORY"); break;
			case -3: ShowError(head, "VK_ERROR_INITIALIZATION_FAILED"); break;
			case -4: ShowError(head, "VK_ERROR_DEVICE_LOST"); break;
			case -5: ShowError(head, "VK_ERROR_MEMORY_MAP_FAILED"); break;
			case -6: ShowError(head, "VK_ERROR_LAYER_NOT_PRESENT"); break;
			case -7: ShowError(head, "VK_ERROR_EXTENSION_NOT_PRESENT"); break;
			case -8: ShowError(head, "VK_ERROR_FEATURE_NOT_PRESENT"); break;
			case -9: ShowError(head, "VK_ERROR_INCOMPATIBLE_DRIVER"); break;
			case -10: ShowError(head, "VK_ERROR_TOO_MANY_OBJECTS"); break;
			case -11: ShowError(head, "VK_ERROR_FORMAT_NOT_SUPPORTED"); break;
			case -12: ShowError(head, "VK_ERROR_FRAGMENTED_POOL"); break;
			case -1000069000: ShowError(head, "VK_ERROR_OUT_OF_POOL_MEMORY"); break;
			case -1000072003: ShowError(head, "VK_ERROR_INVALID_EXTERNAL_HANDLE"); break;
			case -1000000000: ShowError(head, "VK_ERROR_SURFACE_LOST_KHR"); break;
			case -1000000001: ShowError(head, "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR"); break;
			case -1000001003: ShowError(head, "VK_SUBOPTIMAL_KHR"); break;
			case -1000001004: ShowError(head, "VK_ERROR_OUT_OF_DATE_KHR"); break;
			case -1000003001: ShowError(head, "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR"); break;
			default: ShowError(head, "Unknown Error"); break;
			}
		}
		return vkResult;
#else
		return vkResult;
#endif
	}
#pragma endregion

#pragma region vulkan_debug_structure
	inline void Debug(int lineNum, VkApplicationInfo *s) {
#ifdef VKFW_DEBUG_MODE
		bool isError = false;
		std::string body;
		if (s->sType != VK_STRUCTURE_TYPE_APPLICATION_INFO) {
			if (!isError) isError = true;
			body += "sType != VK_STRUCTURE_TYPE_APPLICATION_INFO\n";
		}
		if (isError) ShowError(std::string("VkApplicationInfo : line ") + std::to_string(lineNum), body);
#endif
	}
#pragma endregion
#pragma endregion
}

#pragma region internal_macro_begin
#pragma pop_macro("VKFW_HANDLE")
#pragma pop_macro("VKFW_STYPE")
#pragma pop_macro("VKFW_ASSIGN")
#pragma endregion

#pragma region vulkan_header_argument_end
#ifdef VKFW_KHR_surface
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
#pragma pop_macro("VK_USE_PLATFORM_WIN32_KHR")
#pragma pop_macro("WIN32_LEAN_AND_MEAN")
#endif
#endif
#pragma endregion