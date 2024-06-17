/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * AxiDmxPlugin.h
 * The DMX through AXI plugin for ola
 * Copyright (C) 2011 Rui Barreiros
 * Copyright (C) 2014 Richard Ash
 */

#ifndef PLUGINS_AXIDMX_AXIDMXPLUGIN_H_
#define PLUGINS_AXIDMX_AXIDMXPLUGIN_H_

#include <set>
#include <string>
#include <vector>

#include "olad/Plugin.h"
#include "ola/plugin_id.h"

#include "plugins/axidmx/AxiDmxDevice.h"

namespace ola {
namespace plugin {
namespace axidmx {

class AxiDmxPlugin : public Plugin {
 public:
  explicit AxiDmxPlugin(ola::PluginAdaptor *plugin_adaptor)
      : Plugin(plugin_adaptor) {
  }

  ola_plugin_id Id() const { return OLA_PLUGIN_AXI; }
  std::string Name() const { return PLUGIN_NAME; }
  std::string PluginPrefix() const { return PLUGIN_PREFIX; }
  // This plugin is enabled unless explicitly disabled by a user.
  bool DefaultMode() const { return true; }

  std::string Description() const;

 private:
  typedef std::vector<AxiDmxDevice*> AxiDeviceVector;
  AxiDeviceVector m_devices;

  void AddDevice(AxiDmxDevice *device);
  bool StartHook();
  bool StopHook();
  bool SetDefaultPreferences();
  //unsigned int GetBreak();
  //unsigned int GetMalf();

  static const char PLUGIN_NAME[];
  static const char PLUGIN_PREFIX[];
  static const char K_DEVICE[];
  static const char DEFAULT_DEVICE[];

  DISALLOW_COPY_AND_ASSIGN(AxiDmxPlugin);
};
}  // namespace axidmx
}  // namespace plugin
}  // namespace ola
#endif  // PLUGINS_AXIDMX_AXIDMXPLUGIN_H_
