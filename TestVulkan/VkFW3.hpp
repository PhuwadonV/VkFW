#pragma once

#ifdef VKFW_KHR_surface
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
#pragma push_macro("WIN32_LEAN_AND_MEAN")
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma push_macro("VK_USE_PLATFORM_WIN32_KHR")
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#endif

#include <vulkan\vulkan.h>

#pragma push_macro("VKFW_SET_STYPE")
#define VKFW_SET_STYPE(Type, val)				\
	inline Type& setSType(Type &ref) {			\
		ref.sType =  VK_STRUCTURE_TYPE_##val;	\
		return ref;								\
	}

#pragma push_macro("VKFW_HANDLE")
#define VKFW_HANDLE(Class, HandleType, varName)				\
	inline Class& operator=(const Class &rhs) {				\
		return operator=(rhs.varName);						\
	}														\
															\
	inline Class& operator=(Class &&rhs) {					\
		return operator=(rhs);								\
	}														\
															\
	inline Class& operator=(HandleType rhs) {				\
		varName = rhs;										\
		return *this;										\
	}														\
															\
	inline HandleType* operator&() {						\
		return &varName;									\
	}														\
															\
	inline operator HandleType&() {							\
		return varName;										\
	}														\
															\
	inline operator const HandleType&() const {				\
		return varName;										\
	}

#pragma push_macro("VKFW_SUIT")
#define VKFW_SUIT(Class, HandleType, varName)							\
	HandleType &varName;												\
	public:																\
		inline explicit Class(HandleType &handle) : varName(handle) {}	\
		inline Class(const Class &rhs) : Class(rhs.varName) {}			\
		inline Class(Class &&rhs) : Class(rhs) {}						\
		VKFW_HANDLE(Class, HandleType, varName)

#pragma push_macro("VKFW_SUIT_CHILD")
#define VKFW_SUIT_CHILD(ParentHandleType, parentVarName, Class, HandleType, varName)									\
	const ParentHandleType &parentVarName;																				\
	HandleType &varName;																								\
	public:																												\
		inline Class(const ParentHandleType &parent, HandleType &handle) : parentVarName(parent), varName(handle) {}	\
		inline Class(const Class &rhs) : Class(rhs.parentVarName, rhs.varName) {}										\
		inline Class(Class &&rhs) : Class(rhs) {}																		\
		VKFW_HANDLE(Class, HandleType, varName)

namespace VkFW::Vk {
	VKFW_SET_STYPE(VkApplicationInfo, APPLICATION_INFO)
	VKFW_SET_STYPE(VkInstanceCreateInfo, INSTANCE_CREATE_INFO)
	VKFW_SET_STYPE(VkDeviceQueueCreateInfo, DEVICE_QUEUE_CREATE_INFO)
	VKFW_SET_STYPE(VkDeviceCreateInfo, DEVICE_CREATE_INFO)
	VKFW_SET_STYPE(VkSubmitInfo, SUBMIT_INFO)
	VKFW_SET_STYPE(VkMemoryAllocateInfo, MEMORY_ALLOCATE_INFO)
	VKFW_SET_STYPE(VkMappedMemoryRange, MAPPED_MEMORY_RANGE)
	VKFW_SET_STYPE(VkBindSparseInfo, BIND_SPARSE_INFO)
	VKFW_SET_STYPE(VkFenceCreateInfo, FENCE_CREATE_INFO)
	VKFW_SET_STYPE(VkSemaphoreCreateInfo, SEMAPHORE_CREATE_INFO)
	VKFW_SET_STYPE(VkEventCreateInfo, EVENT_CREATE_INFO)
	VKFW_SET_STYPE(VkQueryPoolCreateInfo, QUERY_POOL_CREATE_INFO)
	VKFW_SET_STYPE(VkBufferCreateInfo, BUFFER_CREATE_INFO)
	VKFW_SET_STYPE(VkBufferViewCreateInfo, BUFFER_VIEW_CREATE_INFO)
	VKFW_SET_STYPE(VkImageCreateInfo, IMAGE_CREATE_INFO)
	VKFW_SET_STYPE(VkImageViewCreateInfo, IMAGE_VIEW_CREATE_INFO)
	VKFW_SET_STYPE(VkShaderModuleCreateInfo, SHADER_MODULE_CREATE_INFO)
	VKFW_SET_STYPE(VkPipelineCacheCreateInfo, PIPELINE_CACHE_CREATE_INFO)
	VKFW_SET_STYPE(VkPipelineShaderStageCreateInfo, PIPELINE_SHADER_STAGE_CREATE_INFO)
	VKFW_SET_STYPE(VkPipelineVertexInputStateCreateInfo, PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO)
	VKFW_SET_STYPE(VkPipelineInputAssemblyStateCreateInfo, PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO)
	VKFW_SET_STYPE(VkPipelineTessellationStateCreateInfo, PIPELINE_TESSELLATION_STATE_CREATE_INFO)
	VKFW_SET_STYPE(VkPipelineViewportStateCreateInfo, PIPELINE_VIEWPORT_STATE_CREATE_INFO)
	VKFW_SET_STYPE(VkPipelineRasterizationStateCreateInfo, PIPELINE_RASTERIZATION_STATE_CREATE_INFO)
	VKFW_SET_STYPE(VkPipelineMultisampleStateCreateInfo, PIPELINE_MULTISAMPLE_STATE_CREATE_INFO)
	VKFW_SET_STYPE(VkPipelineDepthStencilStateCreateInfo, PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO)
	VKFW_SET_STYPE(VkPipelineColorBlendStateCreateInfo, PIPELINE_COLOR_BLEND_STATE_CREATE_INFO)
	VKFW_SET_STYPE(VkPipelineDynamicStateCreateInfo, PIPELINE_DYNAMIC_STATE_CREATE_INFO)
	VKFW_SET_STYPE(VkGraphicsPipelineCreateInfo, GRAPHICS_PIPELINE_CREATE_INFO)
	VKFW_SET_STYPE(VkComputePipelineCreateInfo, COMPUTE_PIPELINE_CREATE_INFO)
	VKFW_SET_STYPE(VkPipelineLayoutCreateInfo, PIPELINE_LAYOUT_CREATE_INFO)
	VKFW_SET_STYPE(VkSamplerCreateInfo, SAMPLER_CREATE_INFO)
	VKFW_SET_STYPE(VkDescriptorSetLayoutCreateInfo, DESCRIPTOR_SET_LAYOUT_CREATE_INFO)
	VKFW_SET_STYPE(VkDescriptorPoolCreateInfo, DESCRIPTOR_POOL_CREATE_INFO)
	VKFW_SET_STYPE(VkDescriptorSetAllocateInfo, DESCRIPTOR_SET_ALLOCATE_INFO)
	VKFW_SET_STYPE(VkWriteDescriptorSet, WRITE_DESCRIPTOR_SET)
	VKFW_SET_STYPE(VkCopyDescriptorSet, COPY_DESCRIPTOR_SET)
	VKFW_SET_STYPE(VkFramebufferCreateInfo, FRAMEBUFFER_CREATE_INFO)
	VKFW_SET_STYPE(VkRenderPassCreateInfo, RENDER_PASS_CREATE_INFO)
	VKFW_SET_STYPE(VkCommandPoolCreateInfo, COMMAND_POOL_CREATE_INFO)
	VKFW_SET_STYPE(VkCommandBufferAllocateInfo, COMMAND_BUFFER_ALLOCATE_INFO)
	VKFW_SET_STYPE(VkCommandBufferInheritanceInfo, COMMAND_BUFFER_INHERITANCE_INFO)
	VKFW_SET_STYPE(VkCommandBufferBeginInfo, COMMAND_BUFFER_BEGIN_INFO)
	VKFW_SET_STYPE(VkRenderPassBeginInfo, RENDER_PASS_BEGIN_INFO)
	VKFW_SET_STYPE(VkBufferMemoryBarrier, BUFFER_MEMORY_BARRIER)
	VKFW_SET_STYPE(VkImageMemoryBarrier, IMAGE_MEMORY_BARRIER)
	VKFW_SET_STYPE(VkMemoryBarrier, MEMORY_BARRIER)

#ifdef VKFW_KHR_surface
#ifdef VKFW_KHR_swapchain
	VKFW_SET_STYPE(VkSwapchainCreateInfoKHR, SWAPCHAIN_CREATE_INFO_KHR)
	VKFW_SET_STYPE(VkPresentInfoKHR, PRESENT_INFO_KHR)
#endif

#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
	VKFW_SET_STYPE(VkWin32SurfaceCreateInfoKHR, WIN32_SURFACE_CREATE_INFO_KHR)
#endif
#endif

	namespace Hidden {
		template<typename Type>
		class Evalable {
		public:
			using Eval = Type;
		};

		template<typename Type>
		class RemoveRef : public Evalable<Type> {};

		template<typename Type> 
		class RemoveRef<Type&> : public Evalable<Type> {};

		template<typename HandleType, uint32_t>
		class Handle {
			using Type = typename RemoveRef<HandleType>::Eval;
		protected:
			HandleType m_handle;
		public:
			inline Handle() = default;
			inline explicit Handle(HandleType rhs) : m_handle(rhs) {}
			inline Handle(const Handle &rhs) : Handle(rhs.m_handle) {}
			inline Handle(Handle &&rhs) : Handle(rhs) {}
			VKFW_HANDLE(Handle,  , m_handle)
		};
	}

	using Buffer = Hidden::Handle<VkBuffer, 0>;
	using BufferView = Hidden::Handle<VkBufferView, 1>;
	using CommandBuffer = Hidden::Handle<VkCommandBuffer, 2>;
	using CommandPool = Hidden::Handle<VkCommandPool, 3>;
	using DescriptorPool = Hidden::Handle<VkDescriptorPool, 4>;
	using DescriptorSet = Hidden::Handle<VkDescriptorSet, 5>;
	using DescriptorSetLayout = Hidden::Handle<VkDescriptorSetLayout, 6>;
	using Device = Hidden::Handle<VkDevice, 7>;
	using DeviceMemory = Hidden::Handle<VkDeviceMemory, 8>;
	using Event = Hidden::Handle<VkEvent, 9>;
	using Fence = Hidden::Handle<VkFence, 10>;
	using Framebuffer = Hidden::Handle<VkFramebuffer, 11>;
	using Image = Hidden::Handle<VkImage, 12>;
	using ImageView = Hidden::Handle<VkImageView, 13>;
	using Instance = Hidden::Handle<VkInstance, 14>;
	using PhysicalDevice = Hidden::Handle<VkPhysicalDevice, 15>;
	using Pipeline = Hidden::Handle<VkPipeline, 16>;
	using PipelineCache = Hidden::Handle<VkPipelineCache, 17>;
	using PipelineLayout = Hidden::Handle<VkPipelineLayout, 18>;
	using QueryPool = Hidden::Handle<VkQueryPool, 19>;
	using Queue = Hidden::Handle<VkQueue, 20>;
	using RenderPass = Hidden::Handle<VkRenderPass, 21>;
	using Sampler = Hidden::Handle<VkSampler, 22>;
	using Semaphore = Hidden::Handle<VkSemaphore, 23>;
	using ShaderModule = Hidden::Handle<VkShaderModule, 24>;

#ifdef VKFW_KHR_surface
	using SurfaceKhr = Hidden::Handle<VkSurfaceKHR, 25>;

#ifdef VKFW_KHR_swapchain
	using SwapchainKhr = Hidden::Handle<VkSwapchainKHR, 26>;
#endif
#endif

	template<typename>
	class FnType;

	template<typename Return, typename... Args>
	class FnType<Return(VKAPI_PTR)(Args...)> : public Hidden::Evalable<Return(VKAPI_PTR*)(Args...)> {};

	template<typename Return, typename... Args>
	inline void getInstanceProcAddr(VkInstance instance, const char *pName, Return(VKAPI_PTR*&f)(Args...)) {
		f = reinterpret_cast<Return(VKAPI_PTR*)(Args...)>(vkGetInstanceProcAddr(instance, pName));
	}

	template<typename Return, typename... Args>
	inline void getInstanceProcAddr(const char *pName, Return(VKAPI_PTR*&f)(Args...)) {
		getInstanceProcAddr(VK_NULL_HANDLE, pName, f);
	}

	template<typename Return, typename... Args>
	inline void getDeviceProcAddr(VkDevice device, const char *pName, Return(VKAPI_PTR*&f)(Args...)) {
		f = reinterpret_cast<Return(VKAPI_PTR*)(Args...)>(vkGetDeviceProcAddr(device, pName));
	}

	inline VkResult createInstance(VkInstance *pInstance, const VkInstanceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) {
		return vkCreateInstance(pCreateInfo, pAllocator, pInstance);
	}

	inline VkResult enumerateInstanceExtensionProperties(const char *pLayerName, uint32_t *pPropertyCount, VkExtensionProperties *pProperties = nullptr) {
		return vkEnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties);
	}

	inline VkResult enumerateInstanceLayerProperties(uint32_t *pPropertyCount, VkLayerProperties *pProperties = nullptr) {
		return vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties);
	}

	namespace Suit {
		class Buffer  {
			VKFW_SUIT_CHILD(VkDevice, m_parent, Buffer, VkBuffer, m_handle)

			inline VkResult bindMemory(VkDeviceMemory memory, VkDeviceSize memoryOffset) {
				return vkBindBufferMemory(m_parent, m_handle, memory, memoryOffset);
			}

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyBuffer(m_parent, m_handle, pAllocator);
			}

			inline void getMemoryRequirements(VkMemoryRequirements *pMemoryRequirements) {
				vkGetBufferMemoryRequirements(m_parent, m_handle, pMemoryRequirements);
			}
		};

		class BufferView {
			VKFW_SUIT_CHILD(VkDevice, m_parent, BufferView, VkBufferView, m_handle)

			void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyBufferView(m_parent, m_handle, pAllocator);
			}
		};

		class CommandBuffer {
			VKFW_SUIT(CommandBuffer, VkCommandBuffer, m_handle)

			inline VkResult begin(const VkCommandBufferBeginInfo *pBeginInfo) {
				return vkBeginCommandBuffer(m_handle, pBeginInfo);
			}

			inline void cmdBeginQuery(VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) {
				vkCmdBeginQuery(m_handle, queryPool, query, flags);
			}

			inline void cmdBeginRenderPass(const VkRenderPassBeginInfo *pRenderPassBegin, VkSubpassContents contents) {
				vkCmdBeginRenderPass(m_handle, pRenderPassBegin, contents);
			}

			inline void cmdBindDescriptorSets(VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout,
				uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet *pDescriptorSets,
				uint32_t dynamicOffsetCount, const uint32_t *pDynamicOffsets) {
				vkCmdBindDescriptorSets(m_handle, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
			}

			inline void cmdBindIndexBuffer(VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) {
				vkCmdBindIndexBuffer(m_handle, buffer, offset, indexType);
			}

			inline void cmdBindPipeline(VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) {
				vkCmdBindPipeline(m_handle, pipelineBindPoint, pipeline);
			}

			inline void cmdBindVertexBuffers(uint32_t firstBinding, uint32_t bindingCount, const VkBuffer *pBuffers, const VkDeviceSize *pOffsets) {
				vkCmdBindVertexBuffers(m_handle, firstBinding, bindingCount, pBuffers, pOffsets);
			}

			inline void cmdBlitImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout,
				uint32_t regionCount, const VkImageBlit *pRegions, VkFilter filter) {
				vkCmdBlitImage(m_handle, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
			}

			inline void cmdClearAttachments(uint32_t attachmentCount, const VkClearAttachment *pAttachments, uint32_t rectCount, const VkClearRect *pRects) {
				vkCmdClearAttachments(m_handle, attachmentCount, pAttachments, rectCount, pRects);
			}

			inline void cmdClearColorImage(VkImage image, VkImageLayout imageLayout, const VkClearColorValue *pColor, uint32_t rangeCount, const VkImageSubresourceRange *pRanges) {
				vkCmdClearColorImage(m_handle, image, imageLayout, pColor, rangeCount, pRanges);
			}

			inline void cmdClearDepthStencilImage(VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue *pDepthStencil,
				uint32_t rangeCount, const VkImageSubresourceRange *pRanges) {
				vkCmdClearDepthStencilImage(m_handle, image, imageLayout, pDepthStencil, rangeCount, pRanges);
			}

			inline void cmdCopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy *pRegions) {
				vkCmdCopyBuffer(m_handle, srcBuffer, dstBuffer, regionCount, pRegions);
			}

			inline void cmdCopyBufferToImage(VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy *pRegions) {
				vkCmdCopyBufferToImage(m_handle, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
			}

			inline void cmdCopyImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy *pRegions) {
				vkCmdCopyImage(m_handle, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
			}

			inline void cmdCopyImageToBuffer(VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy *pRegions) {
				vkCmdCopyImageToBuffer(m_handle, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
			}

			inline void cmdCopyQueryPoolResults(VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset,
				VkDeviceSize stride, VkQueryResultFlags flags) {
				vkCmdCopyQueryPoolResults(m_handle, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
			}

			inline void cmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
				vkCmdDispatch(m_handle, groupCountX, groupCountY, groupCountZ);
			}

			inline void cmdDispatchIndirect(VkBuffer buffer, VkDeviceSize offset) {
				vkCmdDispatchIndirect(m_handle, buffer, offset);
			}

			inline void cmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
				vkCmdDraw(m_handle, vertexCount, instanceCount, firstVertex, firstInstance);
			}

			inline void cmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) {
				vkCmdDrawIndexed(m_handle, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
			}

			inline void cmdDrawIndexedIndirect(VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
				vkCmdDrawIndexedIndirect(m_handle, buffer, offset, drawCount, stride);
			}

			inline void cmdDrawIndirect(VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
				vkCmdDrawIndirect(m_handle, buffer, offset, drawCount, stride);
			}

			inline void cmdEndQuery(VkQueryPool queryPool, uint32_t query) {
				vkCmdEndQuery(m_handle, queryPool, query);
			}

			inline void cmdEndRenderPass() {
				vkCmdEndRenderPass(m_handle);
			}

			inline void cmdExecuteCommands(uint32_t commandBufferCount, const VkCommandBuffer *pCommandBuffers) {
				vkCmdExecuteCommands(m_handle, commandBufferCount, pCommandBuffers);
			}

			inline void cmdFillBuffer(VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) {
				vkCmdFillBuffer(m_handle, dstBuffer, dstOffset, size, data);
			}

			inline void cmdNextSubpass(VkSubpassContents contents) {
				vkCmdNextSubpass(m_handle, contents);
			}

			inline void cmdPipelineBarrier(VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
				uint32_t memoryBarrierCount, const VkMemoryBarrier *pMemoryBarriers, uint32_t bufferMemoryBarrierCount,
				const VkBufferMemoryBarrier *pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier *pImageMemoryBarriers) {
				vkCmdPipelineBarrier(m_handle, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount,
					pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
			}

			inline void cmdPushConstants(VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void *pValues) {
				vkCmdPushConstants(m_handle, layout, stageFlags, offset, size, pValues);
			}

			inline void cmdResetEvent(VkEvent event, VkPipelineStageFlags stageMask) {
				vkCmdResetEvent(m_handle, event, stageMask);
			}

			inline void cmdResetQueryPool(VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
				vkCmdResetQueryPool(m_handle, queryPool, firstQuery, queryCount);
			}

			inline void cmdResolveImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve *pRegions) {
				vkCmdResolveImage(m_handle, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
			}

			inline void cmdSetBlendConstants(const float blendConstants[4]) {
				vkCmdSetBlendConstants(m_handle, blendConstants);
			}

			inline void cmdSetDepthBias(float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) {
				vkCmdSetDepthBias(m_handle, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
			}

			inline void cmdSetDepthBounds(float minDepthBounds, float maxDepthBounds) {
				vkCmdSetDepthBounds(m_handle, minDepthBounds, maxDepthBounds);
			}

			inline void cmdSetEvent(VkEvent event, VkPipelineStageFlags stageMask) {
				vkCmdSetEvent(m_handle, event, stageMask);
			}

			inline void cmdSetLineWidth(float lineWidth) {
				vkCmdSetLineWidth(m_handle, lineWidth);
			}

			inline void cmdSetScissor(uint32_t firstScissor, uint32_t scissorCount, const VkRect2D *pScissors) {
				vkCmdSetScissor(m_handle, firstScissor, scissorCount, pScissors);
			}

			inline void cmdSetStencilCompareMask(VkStencilFaceFlags faceMask, uint32_t compareMask) {
				vkCmdSetStencilCompareMask(m_handle, faceMask, compareMask);
			}

			inline void cmdSetStencilReference(VkStencilFaceFlags faceMask, uint32_t reference) {
				vkCmdSetStencilReference(m_handle, faceMask, reference);
			}

			inline void cmdSetStencilWriteMask(VkStencilFaceFlags faceMask, uint32_t writeMask) {
				vkCmdSetStencilWriteMask(m_handle, faceMask, writeMask);
			}

			inline void cmdSetViewport(uint32_t firstViewport, uint32_t viewportCount, const VkViewport *pViewports) {
				vkCmdSetViewport(m_handle, firstViewport, viewportCount, pViewports);
			}

			inline void cmdUpdateBuffer(VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void *pData) {
				vkCmdUpdateBuffer(m_handle, dstBuffer, dstOffset, dataSize, pData);
			}

			inline void cmdWaitEvents(uint32_t eventCount, const VkEvent *pEvents, VkPipelineStageFlags srcStageMask,
				VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier *pMemoryBarriers,
				uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier *pBufferMemoryBarriers,
				uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier *pImageMemoryBarriers) {
				vkCmdWaitEvents(m_handle, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers,
					bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
			}

			inline void cmdWriteTimestamp(VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) {
				vkCmdWriteTimestamp(m_handle, pipelineStage, queryPool, query);
			}

			inline VkResult end() {
				return vkEndCommandBuffer(m_handle);
			}

			inline VkResult reset(VkCommandBufferResetFlags flags = 0) {
				return vkResetCommandBuffer(m_handle, flags);
			}
		};

		class CommandPool {
			VKFW_SUIT_CHILD(VkDevice, m_parent, CommandPool, VkCommandPool, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyCommandPool(m_parent, m_handle, pAllocator);
			}

			inline void freeCommandBuffers(uint32_t commandBufferCount, const VkCommandBuffer *pCommandBuffers) {
				vkFreeCommandBuffers(m_parent, m_handle, commandBufferCount, pCommandBuffers);
			}

			inline VkResult reset(VkCommandPoolResetFlags flags = 0) {
				return vkResetCommandPool(m_parent, m_handle, flags);
			}
		};

		class DescriptorPool {
			VKFW_SUIT_CHILD(VkDevice, m_parent, DescriptorPool, VkDescriptorPool, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				return vkDestroyDescriptorPool(m_parent, m_handle, pAllocator);
			}

			inline VkResult free(uint32_t descriptorSetCount, const VkDescriptorSet *pDescriptorSets) {
				return vkFreeDescriptorSets(m_parent, m_handle, descriptorSetCount, pDescriptorSets);
			}

			inline VkResult reset(VkDescriptorPoolResetFlags flags = 0) {
				return vkResetDescriptorPool(m_parent, m_handle, flags);
			}
		};

		class DescriptorSetLayout {
			VKFW_SUIT_CHILD(VkDevice, m_parent, DescriptorSetLayout, VkDescriptorSetLayout, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyDescriptorSetLayout(m_parent, m_handle, pAllocator);
			}
		};

		class Device {
			VKFW_SUIT(Device, VkDevice, m_handle)

			inline VkResult allocateCommandBuffers(VkCommandBuffer *pCommandBuffers, const VkCommandBufferAllocateInfo *pAllocateInfo = nullptr) const {
				return vkAllocateCommandBuffers(m_handle, pAllocateInfo, pCommandBuffers);
			}

			inline VkResult allocateDescriptorSets(VkDescriptorSet *pDescriptorSets, const VkDescriptorSetAllocateInfo *pAllocateInfo = nullptr) const {
				return vkAllocateDescriptorSets(m_handle, pAllocateInfo, pDescriptorSets);
			}

			inline VkResult allocateMemory(VkDeviceMemory *pMemory, const VkMemoryAllocateInfo *pAllocateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkAllocateMemory(m_handle, pAllocateInfo, pAllocator, pMemory);
			}

			inline VkResult bindBufferMemory(VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) const {
				return vkBindBufferMemory(m_handle, buffer, memory, memoryOffset);
			}

			inline VkResult bindImageMemory(VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) const {
				return vkBindImageMemory(m_handle, image, memory, memoryOffset);
			}

			inline VkResult createBuffer(VkBuffer *pBuffer, const VkBufferCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateBuffer(m_handle, pCreateInfo, pAllocator, pBuffer);
			}

			inline VkResult createBufferView(VkBufferView *pView, const VkBufferViewCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateBufferView(m_handle, pCreateInfo, pAllocator, pView);
			}

			inline VkResult createCommandPool(VkCommandPool *pCommandPool, const VkCommandPoolCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateCommandPool(m_handle, pCreateInfo, pAllocator, pCommandPool);
			}

			inline VkResult createComputePipelines(VkPipeline *pPipelines, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo *pCreateInfos,
				const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateComputePipelines(m_handle, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
			}

			inline VkResult createDescriptorPool(VkDescriptorPool *pDescriptorPool, const VkDescriptorPoolCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateDescriptorPool(m_handle, pCreateInfo, pAllocator, pDescriptorPool);
			}

			inline VkResult createDescriptorSetLayout(VkDescriptorSetLayout *pSetLayout, const VkDescriptorSetLayoutCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateDescriptorSetLayout(m_handle, pCreateInfo, pAllocator, pSetLayout);
			}

			inline VkResult createEvent(VkEvent *pEvent, const VkEventCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateEvent(m_handle, pCreateInfo, pAllocator, pEvent);
			}

			inline VkResult createFence(VkFence *pFence, const VkFenceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateFence(m_handle, pCreateInfo, pAllocator, pFence);
			}

			inline VkResult createFramebuffer(VkFramebuffer *pFramebuffer, const VkFramebufferCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateFramebuffer(m_handle, pCreateInfo, pAllocator, pFramebuffer);
			}

			inline VkResult createGraphicsPipelines(VkPipeline *pPipelines, VkPipelineCache pipelineCache, uint32_t createInfoCount,
				const VkGraphicsPipelineCreateInfo *pCreateInfos, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateGraphicsPipelines(m_handle, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
			}

			inline VkResult createImage(VkImage *pImage, const VkImageCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateImage(m_handle, pCreateInfo, pAllocator, pImage);
			}

			inline VkResult createImageView(VkImageView *pView, const VkImageViewCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateImageView(m_handle, pCreateInfo, pAllocator, pView);
			}

			inline VkResult createPipelineCache(VkPipelineCache *pPipelineCache, const VkPipelineCacheCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreatePipelineCache(m_handle, pCreateInfo, pAllocator, pPipelineCache);
			}

			inline VkResult createPipelineLayout(VkPipelineLayout *pPipelineLayout, const VkPipelineLayoutCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreatePipelineLayout(m_handle, pCreateInfo, pAllocator, pPipelineLayout);
			}

			inline VkResult createQueryPool(VkQueryPool *pQueryPool, const VkQueryPoolCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateQueryPool(m_handle, pCreateInfo, pAllocator, pQueryPool);
			}

			inline VkResult createRenderPass(VkRenderPass *pRenderPass, const VkRenderPassCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateRenderPass(m_handle, pCreateInfo, pAllocator, pRenderPass);
			}

			inline VkResult createSampler(VkSampler *pSampler, const VkSamplerCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateSampler(m_handle, pCreateInfo, pAllocator, pSampler);
			}

			inline VkResult createSemaphore(VkSemaphore *pSemaphore, const VkSemaphoreCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateSemaphore(m_handle, pCreateInfo, pAllocator, pSemaphore);
			}


			inline VkResult createShaderModule(VkShaderModule *pShaderModule, const VkShaderModuleCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateShaderModule(m_handle, pCreateInfo, pAllocator, pShaderModule);
			}

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyDevice(m_handle, pAllocator);
			}

			inline VkResult waitIdel() const {
				return vkDeviceWaitIdle(m_handle);
			}

			inline VkResult flushMappedMemoryRanges(uint32_t memoryRangeCount, const VkMappedMemoryRange *pMemoryRanges) {
				return vkFlushMappedMemoryRanges(m_handle, memoryRangeCount, pMemoryRanges);
			}

			inline void getQueue(VkQueue *pQueue, uint32_t queueFamilyIndex, uint32_t queueIndex) const {
				vkGetDeviceQueue(m_handle, queueFamilyIndex, queueIndex, pQueue);
			}

			inline VkResult invalidateMappedMemoryRanges(uint32_t memoryRangeCount, const VkMappedMemoryRange *pMemoryRanges) {
				return vkInvalidateMappedMemoryRanges(m_handle, memoryRangeCount, pMemoryRanges);
			}

			inline VkResult resetFences(uint32_t fenceCount, const VkFence *pFences) {
				return vkResetFences(m_handle, fenceCount, pFences);
			}

			inline void updateDescriptorSets(uint32_t descriptorWriteCount, const VkWriteDescriptorSet *pDescriptorWrites,
				uint32_t descriptorCopyCount, const VkCopyDescriptorSet *pDescriptorCopies) {
				vkUpdateDescriptorSets(m_handle, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
			}

			inline VkResult waitForFences(uint32_t fenceCount, const VkFence *pFences, VkBool32 waitAll, uint64_t timeout) {
				return vkWaitForFences(m_handle, fenceCount, pFences, waitAll, timeout);
			}
#ifdef VKFW_KHR_swapchain
			inline VkResult createSwapchain(VkSwapchainKHR *pSwapchain, const VkSwapchainCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateSwapchainKHR(m_handle, pCreateInfo, pAllocator, pSwapchain);
			}
#endif
		};

		class DeviceMemory {
			VKFW_SUIT_CHILD(VkDevice, m_parent, DeviceMemory, VkDeviceMemory, m_handle)

			inline void free(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkFreeMemory(m_parent, m_handle, pAllocator);
			}

			inline void getCommitment(VkDeviceSize *pCommittedMemoryInBytes) {
				vkGetDeviceMemoryCommitment(m_parent, m_handle, pCommittedMemoryInBytes);
			}

			inline VkResult map(void **ppData, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags = 0) {
				return vkMapMemory(m_parent, m_handle, offset, size, flags, ppData);
			}

			inline void unmap() {
				vkUnmapMemory(m_parent, m_handle);
			}
		};

		class Event {
			VKFW_SUIT_CHILD(VkDevice, m_parent, Event, VkEvent, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyEvent(m_parent, m_handle, pAllocator);
			}

			inline VkResult getStatus() {
				return vkGetEventStatus(m_parent, m_handle);
			}

			inline VkResult reset() {
				return vkResetEvent(m_parent, m_handle);
			}

			inline VkResult set() {
				return vkSetEvent(m_parent, m_handle);
			}
		};

		class Fence {
			VKFW_SUIT_CHILD(VkDevice, m_parent, Fence, VkFence, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyFence(m_parent, m_handle, pAllocator);
			}

			inline VkResult getStatus() {
				return vkGetFenceStatus(m_parent, m_handle);
			}
		};

		class Framebuffer {
			VKFW_SUIT_CHILD(VkDevice, m_parent, Framebuffer, VkFramebuffer, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyFramebuffer(m_parent, m_handle, pAllocator);
			}
		};

		class Image {
			VKFW_SUIT_CHILD(VkDevice, m_parent, Image, VkImage, m_handle)

			inline VkResult bindMemory(VkDeviceMemory memory, VkDeviceSize memoryOffset) {
				return vkBindImageMemory(m_parent, m_handle, memory, memoryOffset);
			}

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyImage(m_parent, m_handle, pAllocator);
			}

			inline void getMemoryRequirements(VkMemoryRequirements *pMemoryRequirements) {
				vkGetImageMemoryRequirements(m_parent, m_handle, pMemoryRequirements);
			}

			inline void getSparseMemoryRequirements(uint32_t *pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements *pSparseMemoryRequirements) {
				vkGetImageSparseMemoryRequirements(m_parent, m_handle, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
			}

			inline void getSubresourceLayout(const VkImageSubresource *pSubresource, VkSubresourceLayout *pLayout) {
				vkGetImageSubresourceLayout(m_parent, m_handle, pSubresource, pLayout);
			}
		};

		class ImageView {
			VKFW_SUIT_CHILD(VkDevice, m_parent, ImageView, VkImageView, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyImageView(m_parent, m_handle, pAllocator);
			}
		};

		class Instance {
			VKFW_SUIT(Instance, VkInstance, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyInstance(m_handle, pAllocator);
			}

			inline VkResult enumeratePhysicalDevices(uint32_t *pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices = nullptr) const {
				return vkEnumeratePhysicalDevices(m_handle, pPhysicalDeviceCount, pPhysicalDevices);
			}

#ifdef VKFW_KHR_surface
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
			inline VkResult createWin32Surface(VkSurfaceKHR *pSurface, const VkWin32SurfaceCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateWin32SurfaceKHR(m_handle, pCreateInfo, pAllocator, pSurface);
			}
#endif
#endif
		};

		class PhysicalDevice {
			VKFW_SUIT(PhysicalDevice, VkPhysicalDevice, m_handle)

			inline VkResult createDevice(VkDevice *pDevice, const VkDeviceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator = nullptr) const {
				return vkCreateDevice(m_handle, pCreateInfo, pAllocator, pDevice);
			}

			inline VkResult enumerateDeviceExtensionProperties(const char *pLayerName, uint32_t *pPropertyCount, VkExtensionProperties *pProperties) const {
				return vkEnumerateDeviceExtensionProperties(m_handle, pLayerName, pPropertyCount, pProperties);
			}

			inline VkResult enumerateDeviceLayerProperties(uint32_t *pPropertyCount, VkLayerProperties *pProperties) const {
				return vkEnumerateDeviceLayerProperties(m_handle, pPropertyCount, pProperties);
			}

			inline void getProperties(VkPhysicalDeviceProperties *properties) const {
				vkGetPhysicalDeviceProperties(m_handle, properties);
			}

			inline void getQueueFamilyProperties(uint32_t *pQueueFamilyPropertyCount, VkQueueFamilyProperties *pQueueFamilyProperties = nullptr) const {
				vkGetPhysicalDeviceQueueFamilyProperties(m_handle, pQueueFamilyPropertyCount, pQueueFamilyProperties);
			}

			inline void getFeatures(VkPhysicalDeviceFeatures *pFeatures) const {
				vkGetPhysicalDeviceFeatures(m_handle, pFeatures);
			}

			inline void getFormatProperties(VkFormat format, VkFormatProperties *pFormatProperties) const {
				vkGetPhysicalDeviceFormatProperties(m_handle, format, pFormatProperties);
			}

			inline VkResult getImageFormatProperties(VkFormat format, VkImageType type, VkImageTiling tiling,
				VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties *pImageFormatProperties) const {
				return vkGetPhysicalDeviceImageFormatProperties(m_handle, format, type, tiling, usage, flags, pImageFormatProperties);
			}

			inline void getMemoryProperties(VkPhysicalDeviceMemoryProperties *pMemoryProperties) const {
				vkGetPhysicalDeviceMemoryProperties(m_handle, pMemoryProperties);
			}

			inline void getSparseImageFormatProperties(VkFormat format, VkImageType type, VkSampleCountFlagBits samples,
				VkImageUsageFlags usage, VkImageTiling tiling, uint32_t *pPropertyCount, VkSparseImageFormatProperties *pProperties) const {
				vkGetPhysicalDeviceSparseImageFormatProperties(m_handle, format, type, samples, usage, tiling, pPropertyCount, pProperties);
			}

#ifdef VKFW_KHR_surface
			inline VkResult getSurfaceSupport(VkBool32 *pSupported, uint32_t queueFamilyIndex, VkSurfaceKHR surface) const {
				return vkGetPhysicalDeviceSurfaceSupportKHR(m_handle, queueFamilyIndex, surface, pSupported);
			}

			inline VkResult getSurfaceCapabilities(VkSurfaceCapabilitiesKHR *pSurfaceCapabilities, VkSurfaceKHR surface) const {
				return vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_handle, surface, pSurfaceCapabilities);
			}

			inline VkResult getSurfaceFormats(VkSurfaceKHR surface, uint32_t *pSurfaceFormatCount, VkSurfaceFormatKHR *pSurfaceFormats = nullptr) const {
				return vkGetPhysicalDeviceSurfaceFormatsKHR(m_handle, surface, pSurfaceFormatCount, pSurfaceFormats);
			}

			inline VkResult getSurfacePresentModes(VkSurfaceKHR surface, uint32_t *pPresentModeCount, VkPresentModeKHR *pPresentModes = nullptr) const {
				return vkGetPhysicalDeviceSurfacePresentModesKHR(m_handle, surface, pPresentModeCount, pPresentModes);
			}

#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
			inline VkBool32 getWin32PresentationSupportKHR(uint32_t queueFamilyIndex) {
				return vkGetPhysicalDeviceWin32PresentationSupportKHR(m_handle, queueFamilyIndex);
			}
#endif
#endif
		};

		class Pipeline {
			VKFW_SUIT_CHILD(VkDevice, m_parent, Pipeline, VkPipeline, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyPipeline(m_parent, m_handle, pAllocator);
			}
		};

		class PipelineCache {
			VKFW_SUIT_CHILD(VkDevice, m_parent, PipelineCache, VkPipelineCache, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyPipelineCache(m_parent, m_handle, pAllocator);
			}

			inline VkResult getData(size_t *pDataSize, void *pData) {
				vkGetPipelineCacheData(m_parent, m_handle, pDataSize, pData);
			}

			inline VkResult merge(uint32_t srcCacheCount, const VkPipelineCache *pSrcCaches) {
				vkMergePipelineCaches(m_parent, m_handle, srcCacheCount, pSrcCaches);
			}
		};

		class PipelineLayout  {
			VKFW_SUIT_CHILD(VkDevice, m_parent, PipelineLayout, VkPipelineLayout, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyPipelineLayout(m_parent, m_handle, pAllocator);
			}
		};

		class QueryPool {
			VKFW_SUIT_CHILD(VkDevice, m_parent, QueryPool, VkQueryPool, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyQueryPool(m_parent, m_handle, pAllocator);
			}

			inline VkResult getResults(uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void *pData, VkDeviceSize stride, VkQueryResultFlags flags) {
				vkGetQueryPoolResults(m_parent, m_handle, firstQuery, queryCount, dataSize, pData, stride, flags);
			}
		};

		class Queue {
			VKFW_SUIT(Queue, VkQueue, m_handle)

			inline VkResult bindSparse(uint32_t bindInfoCount, const VkBindSparseInfo *pBindInfo, VkFence fence) {
				return vkQueueBindSparse(m_handle, bindInfoCount, pBindInfo, fence);
			}

			inline VkResult submit(uint32_t submitCount, const VkSubmitInfo *pSubmits, VkFence fence) {
				return vkQueueSubmit(m_handle, submitCount, pSubmits, fence);
			}

			inline VkResult waitIdle() {
				return vkQueueWaitIdle(m_handle);
			}

#ifdef VKFW_KHR_surface
#ifdef VKFW_KHR_swapchain
			inline VkResult present(const VkPresentInfoKHR *pPresentInfo) const {
				return vkQueuePresentKHR(m_handle, pPresentInfo);
			}
#endif
#endif
		};

		class RenderPass {
			VKFW_SUIT_CHILD(VkDevice, m_parent, RenderPass, VkRenderPass, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyRenderPass(m_parent, m_handle, pAllocator);
			}

			inline void getGranularity(VkExtent2D *pGranularity) {
				vkGetRenderAreaGranularity(m_parent, m_handle, pGranularity);
			}
		};

		class Sampler {
			VKFW_SUIT_CHILD(VkDevice, m_parent, Sampler, VkSampler, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroySampler(m_parent, m_handle, pAllocator);
			}
		};

		class Semaphore {
			VKFW_SUIT_CHILD(VkDevice, m_parent, Semaphore, VkSemaphore, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroySemaphore(m_parent, m_handle, pAllocator);
			}
		};

		class ShaderModule {
			VKFW_SUIT_CHILD(VkDevice, m_parent, ShaderModule, VkShaderModule, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroyShaderModule(m_parent, m_handle, pAllocator);
			}
		};

#ifdef VKFW_KHR_surface
		class SurfaceKhr {
			VKFW_SUIT_CHILD(VkInstance, m_parent, SurfaceKhr, VkSurfaceKHR, m_handle)

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroySurfaceKHR(m_parent, m_handle, pAllocator);
			}
		};

#ifdef VKFW_KHR_swapchain
		class SwapchainKhr {
			VKFW_SUIT_CHILD(VkDevice, m_parent, SwapchainKhr, VkSwapchainKHR, m_handle)

			inline VkResult acquireNextImage(uint32_t *pImageIndex, uint64_t timeout, VkSemaphore semaphore, VkFence fence) const {
				return vkAcquireNextImageKHR(m_parent, m_handle, timeout, semaphore, fence, pImageIndex);
			}

			inline VkResult acquireNextImageWithSemaphore(uint32_t *pImageIndex, VkSemaphore semaphore, uint64_t timeout = 0) const {
				return vkAcquireNextImageKHR(m_parent, m_handle, timeout, semaphore, VK_NULL_HANDLE, pImageIndex);
			}

			inline VkResult acquireNextImageWithFence(uint32_t *pImageIndex, VkFence fence, uint64_t timeout = 0) const {
				return vkAcquireNextImageKHR(m_parent, m_handle, timeout, VK_NULL_HANDLE, fence, pImageIndex);
			}

			inline void destroy(const VkAllocationCallbacks *pAllocator = nullptr) {
				vkDestroySwapchainKHR(m_parent, m_handle, pAllocator);
			}

			inline VkResult getImages(uint32_t *pSwapchainImageCount, VkImage *pSwapchainImages = nullptr) const {
				return vkGetSwapchainImagesKHR(m_parent, m_handle, pSwapchainImageCount, pSwapchainImages);
			}
		};
#endif
#endif
	}
}

#pragma pop_macro("VKFW_SUIT_CHILD")
#pragma pop_macro("VKFW_SUIT")
#pragma pop_macro("VKFW_HANDLE")
#pragma pop_macro("VKFW_SET_STYPE")

#ifdef VKFW_KHR_surface
#if defined(VKFW_KHR_win32_surface) || defined(_WIN32) || defined(_WIN64)
#pragma pop_macro("VK_USE_PLATFORM_WIN32_KHR")
#pragma pop_macro("WIN32_LEAN_AND_MEAN")
#endif
#endif