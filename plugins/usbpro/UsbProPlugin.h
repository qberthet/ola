/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * usbproplugin.h
 * Interface for the usbpro plugin class
 * Copyright (C) 2006  Simon Newton
 */

#ifndef USBPROPLUGIN_H
#define USBPROPLUGIN_H

#include <vector>
#include <llad/Plugin.h>
#include <lla/plugin_id.h>
#include <lla/select_server/Socket.h>

namespace lla {
namespace plugin {

using lla::select_server::SocketManager;
using lla::select_server::Socket;

class UsbProDevice;

class UsbProPlugin: public lla::Plugin, public SocketManager {
  public:
    UsbProPlugin(const PluginAdaptor *plugin_adaptor):
      Plugin(plugin_adaptor) {}

    string Name() const { return PLUGIN_NAME; }
    string Description() const;
    lla_plugin_id Id() const { return LLA_PLUGIN_USBPRO; }
    void SocketClosed(Socket *socket);

  protected:
    string PreferencesSuffix() const { return PLUGIN_PREFIX; }

  private:
    bool StartHook();
    bool StopHook();
    int SetDefaultPreferences();
    void DeleteDevice(UsbProDevice *device);

    vector<UsbProDevice*> m_devices; // list of our devices

    static const string USBPRO_DEVICE_PATH;
    static const string USBPRO_DEVICE_NAME;
    static const string PLUGIN_NAME;
    static const string PLUGIN_PREFIX;
};

} //plugins
} //lla
#endif
