/*
 * Copyright 2017 - 2018 The WizTK Authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "display/private.hpp"
#include "surface/private.hpp"
#include "abstract-rendering-api_proxy.hpp"

#include "wiztk/gui/vulkan-api.hpp"
#include "wiztk/gui/application.hpp"

namespace wiztk {
namespace gui {

VulkanAPI::VulkanAPI()
    : AbstractRenderingAPI() {

}

VulkanAPI::~VulkanAPI() = default;

void VulkanAPI::OnSetup() {
  Display *display = Application::GetInstance()->GetDisplay();

  vk::WaylandSurfaceCreateInfoKHR info = {
      vk::WaylandSurfaceCreateFlagsKHR(),
      Display::Private::Get(*display).wl_display,
//      Proxy::GetWaylandSurface(GetSurface())
  };

  vk_surface_ = Display::Private::Get(*display).vk_instance.createWaylandSurfaceKHR(info);
}

} // namespace gui
} // namespace wiztk
