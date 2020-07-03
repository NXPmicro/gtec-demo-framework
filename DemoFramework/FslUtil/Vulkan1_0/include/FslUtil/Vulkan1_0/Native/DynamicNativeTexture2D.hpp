#ifndef FSLUTIL_VULKAN1_0_NATIVE_DYNAMICNATIVETEXTURE2D_HPP
#define FSLUTIL_VULKAN1_0_NATIVE_DYNAMICNATIVETEXTURE2D_HPP
/****************************************************************************************************************************************************
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    * Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *
 *    * Neither the name of the NXP. nor the names of
 *      its contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************************************************************************************/

// Make sure Common.hpp is the first include file (to make the error message as helpful as possible when disabled)
#include <FslUtil/Vulkan1_0/Common.hpp>
#include <FslBase/Math/Pixel/PxExtent3D.hpp>
#include <FslGraphics/Render/Texture2DFilterHint.hpp>
#include <FslGraphics/Render/Adapter/IDynamicNativeTexture2D.hpp>
#include <FslUtil/Vulkan1_0/VUTexture.hpp>
#include <FslUtil/Vulkan1_0/Native/ANativeTexture2D.hpp>
#include <FslUtil/Vulkan1_0/Native/DynamicNativeTexture2DLink.hpp>
#include <FslUtil/Vulkan1_0/VUTextureUtil.hpp>
#include <memory>

namespace Fsl
{
  namespace Vulkan
  {
    class DynamicNativeTexture2D final
      : public ANativeTexture2D
      , public IDynamicNativeTexture2D
    {
      std::shared_ptr<DynamicNativeTexture2DLink> m_link;

    public:
      explicit DynamicNativeTexture2D(const PxExtent3D& extentPx, std::shared_ptr<DynamicNativeTexture2DLink> link)
        : ANativeTexture2D(extentPx)
        , m_link(std::move(link))
      {
      }
      ~DynamicNativeTexture2D() final = default;

      NativeTextureArea CalcNativeTextureArea(const PxRectangleU& imageRectanglePx) const final
      {
        return VUTextureUtil::CalcTextureArea(imageRectanglePx, GetPxExtent2D());
      }


      //! @brief Get the native texture handle
      VkDescriptorImageInfo Get() const final
      {
        return m_link->GetDescriptorImageInfo();
      }

      void SetData(const RawTexture& texture, const Texture2DFilterHint filterHint, const TextureFlags textureFlags) final
      {
        if (m_link)
        {
          m_link->SetData(texture, filterHint, textureFlags);
        }
      }
    };
  }
}

#endif
