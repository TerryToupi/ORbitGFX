#ifndef __RENDER_PASS_HPP__
#define __RENDER_PASS_HPP__

#include <utilities/span.hpp>
#include <utilities/handle.hpp>
#include <renderer/enums.hpp>
#include <renderer/resources/renderPassLayout.hpp>

namespace gfx
{
	class RenderPass;

	struct RenderPassDescriptor
    {
        struct ClearColor
        {
            double r = 0;
            double g = 0;
            double b = 0;
            double a = 0;
        };
        
        struct ColorTarget
        {
            LoadOperation loadOp = LoadOperation::CLEAR;
            StoreOperation storeOp = StoreOperation::STORE;
            ClearColor clearColor = { 0.2, 0.2, 0.2, 1 };
        };
        
        struct DepthTarget
        {
            LoadOperation loadOp = LoadOperation::CLEAR;
            StoreOperation storeOp = StoreOperation::STORE;
            LoadOperation stencilLoadOp = LoadOperation::CLEAR;
            StoreOperation stencilStoreOp = StoreOperation::STORE;
            float clearZ = 0.0f;
            uint32_t clearStencil = 0;
        };
        
        DepthTarget depthTarget;
        utils::Span<ColorTarget> colorTargets;
        utils::Handle<RenderPassLayout> layout;
    };
}

#endif // !__RENDER_PASS_HPP__
