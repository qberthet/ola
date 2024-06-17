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
 * AxiDmxPlugin.cpp
 * The DMX through AXI plugin for ola
 * Copyright (C) 2011 Rui Barreiros
 * Copyright (C) 2014 Richard Ash
 */

#include <fcntl.h>
#include <errno.h>

#include <memory>
#include <string>
#include <vector>

#include "ola/StringUtils.h"
#include "ola/io/IOUtils.h"
#include "olad/Preferences.h"
#include "olad/PluginAdaptor.h"
#include "plugins/axidmx/AxiDmxPlugin.h"
#include "plugins/axidmx/AxiDmxPluginDescription.h"
#include "plugins/axidmx/AxiDmxDevice.h"
#include "plugins/axidmx/AxiWidget.h"

namespace ola {
namespace plugin {
namespace axidmx {

using std::string;
using std::vector;

const char AxiDmxPlugin::PLUGIN_NAME[] = "AXI native DMX";
const char AxiDmxPlugin::PLUGIN_PREFIX[] = "axidmx";
const char AxiDmxPlugin::K_DEVICE[] = "device";
const char AxiDmxPlugin::DEFAULT_DEVICE[] = "/dev/dmx0";

/*
 * Start the plug-in, using only the configured device(s) (we cannot sensibly
 * scan for UARTs!). Stolen from the opendmx plugin.
 */
bool AxiDmxPlugin::StartHook() {
  vector<string> devices = m_preferences->GetMultipleValue(K_DEVICE);
  vector<string>::const_iterator iter;  // iterate over devices

  // start counting device ids from 0

  for (iter = devices.begin(); iter != devices.end(); ++iter) {
    // first check if device configured
    if (iter->empty()) {
      OLA_DEBUG << "No path configured for device, please set one in "
                << "ola-axidmx.conf";
      continue;
    }

    OLA_DEBUG << "Trying to open AxiDMX device " << *iter;
    int fd;
    if (!ola::io::Open(*iter, O_WRONLY, &fd)) {
      OLA_WARN << "Could not open " << *iter << " " << strerror(errno);
      continue;
    }

    // can open device, so shut the temporary file descriptor
    close(fd);
    std::auto_ptr<AxiDmxDevice> device(new AxiDmxDevice(this, m_preferences, PLUGIN_NAME, *iter));

    // got a device, now lets see if we can configure it before we announce
    // it to the world
    if (!device->GetWidget()->SetupOutput()) {
      OLA_WARN << "Unable to setup device for output, device ignored "
               << device->DeviceId();
      continue;
    }
    // OK, device is good to go
    if (!device->Start()) {
      OLA_WARN << "Failed to start AxiDmxDevice for " << *iter;
      continue;
    }

    OLA_DEBUG << "Started AxiDmxDevice " << *iter;
    m_plugin_adaptor->RegisterDevice(device.get());
    m_devices.push_back(device.release());
  }
  return true;
}

/**
 * Stop all the devices.
 */
bool AxiDmxPlugin::StopHook() {
  AxiDeviceVector::iterator iter;
  for (iter = m_devices.begin(); iter != m_devices.end(); ++iter) {
    m_plugin_adaptor->UnregisterDevice(*iter);
    (*iter)->Stop();
    delete *iter;
  }
  m_devices.clear();
  return true;
}


/**
 * Return a description for this plugin.
 */
string AxiDmxPlugin::Description() const {
  return plugin_description;
}


/**
 * Set the default preferences
 */
bool AxiDmxPlugin::SetDefaultPreferences() {
  if (!m_preferences) {
    return false;
  }

  // only insert default device name, no others at this stage
  bool save = m_preferences->SetDefaultValue(K_DEVICE, StringValidator(),
                                             DEFAULT_DEVICE);
  if (save) {
    m_preferences->Save();
  }

  // Just check key exists, as we've set it to ""
  if (!m_preferences->HasKey(K_DEVICE)) {
    return false;
  }
  return true;
}
}  // namespace axidmx
}  // namespace plugin
}  // namespace ola
