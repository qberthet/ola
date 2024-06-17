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
 * AxiDmxPort.h
 * The DMX through AXI plugin for ola
 * Copyright (C) 2011 Rui Barreiros
 * Copyright (C) 2014 Richard Ash
 */

#ifndef PLUGINS_AXIDMX_AXIDMXPORT_H_
#define PLUGINS_AXIDMX_AXIDMXPORT_H_

#include <string>

#include "ola/DmxBuffer.h"
#include "olad/Port.h"
#include "olad/Preferences.h"
#include "plugins/axidmx/AxiDmxDevice.h"
#include "plugins/axidmx/AxiWidget.h"
#include "plugins/axidmx/AxiDmxThread.h"

namespace ola {
namespace plugin {
namespace axidmx {

class AxiDmxOutputPort : public ola::BasicOutputPort {
 public:
  AxiDmxOutputPort(AxiDmxDevice *parent,
                    unsigned int id,
                    AxiWidget *widget
                    //,unsigned int breakt,
                    //unsigned int malft
                    )
      : BasicOutputPort(parent, id),
        m_widget(widget),
        m_thread(widget
        //, breakt, malft
        ) {
    m_thread.Start();
  }
  ~AxiDmxOutputPort() { m_thread.Stop(); }

  bool WriteDMX(const ola::DmxBuffer &buffer, uint8_t) {
    OLA_WARN << "WriteDMX()";
    return m_thread.WriteDMX(buffer);
  }

  std::string Description() const { return m_widget->Description(); }

 private:
  AxiWidget *m_widget;
  AxiDmxThread m_thread;

  DISALLOW_COPY_AND_ASSIGN(AxiDmxOutputPort);
};
}  // namespace axidmx
}  // namespace plugin
}  // namespace ola
#endif  // PLUGINS_AXIDMX_AXIDMXPORT_H_
