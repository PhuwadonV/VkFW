#pragma once

#include <vector>
#include <string>

#define USE_MAIN
#include <WinFW.hpp>

#define VKFW_DEBUG_MODE
#define VKFW_VERSION_MAJOR 1
#define VKFW_VERSION_MINOR 1
#define VKFW_KHR_surface
#define VKFW_KHR_swapchain
#include "VkFW.hpp"

#pragma comment(lib, "WinFW.lib")
#pragma comment(lib, "vulkan-1.lib")

using WinFW::EventLoop;
using WinFW::IPtr;
using WinFW::Window;
using WinFW::WindowConfig;
using WinFW::WinClass;
using WinFW::WinClassConfig;
using WinFW::Keyboard;
using WinFW::Mouse;

IPtr<Window> window;
IPtr<Keyboard> keyboard;
IPtr<Mouse> mouse;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;