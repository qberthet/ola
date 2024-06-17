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
 * AxiDmxDevice.cpp
 * The DMX through AXI plugin for ola
 * Copyright (C) 2011 Rui Barreiros
 * Copyright (C) 2014 Richard Ash
 */

#include <string>
#include <memory>
#include "ola/Logging.h"
#include "ola/StringUtils.h"
#include "plugins/axidmx/AxiDmxDevice.h"
#include "plugins/axidmx/AxiDmxPort.h"

namespace ola {
namespace plugin {
namespace axidmx {

using std::string;

AxiDmxDevice::AxiDmxDevice(AbstractPlugin *owner,
                             class Preferences *preferences,
                             const string &name,
                             const string &path)
    : Device(owner, name),
      m_preferences(preferences),
      m_name(name),
      m_path(path) {
  // set up some per-device default configuration if not already set
  SetDefaults();
  // now read per-device configuration

  // none yet

  m_widget.reset(new AxiWidget(path));
}

AxiDmxDevice::~AxiDmxDevice() {
  if (m_widget->IsOpen()) {
    m_widget->Close();
  }
}

bool AxiDmxDevice::StartHook() {
  AddPort(new AxiDmxOutputPort(this, 0, m_widget.get()));

  return true;
}

/**
 * Set the default preferences for this one Device
 */
void AxiDmxDevice::SetDefaults() {
  if (!m_preferences) {
    return;
  }

  bool save = false;

  // no specific config yet

  if (save) {
    m_preferences->Save();
  }
}
}  // namespace axidmx
}  // namespace plugin
}  // namespace ola
