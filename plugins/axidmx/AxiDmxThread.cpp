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
 AxirtDmxThread.cpp
 * The DMX through AXI plugin for ola
 * Copyright (C) 2011 Rui Barreiros
 * Copyright (C) 2014 Richard Ash
 */

#include <math.h>
#include <unistd.h>
#include <string>
#include "ola/Clock.h"
#include "ola/Logging.h"
#include "ola/StringUtils.h"
#include "plugins/axidmx/AxiWidget.h"
#include "plugins/axidmx/AxiDmxThread.h"

namespace ola {
namespace plugin {
namespace axidmx {

AxiDmxThread::AxiDmxThread(AxiWidget *widget)
  :
    m_widget(widget),
    m_term(false) {
      OLA_WARN << "new AxiDmxThread()";
}

AxiDmxThread::~AxiDmxThread() {
  Stop();
}


/**
 * Stop this thread
 */
bool AxiDmxThread::Stop() {
  {
    ola::thread::MutexLocker locker(&m_term_mutex);
    m_term = true;
  }
  return Join();
}


/**
 * Copy a DMXBuffer to the output thread
 */
bool AxiDmxThread::WriteDMX(const DmxBuffer &buffer) {
  ola::thread::MutexLocker locker(&m_buffer_mutex);
  m_buffer.Set(buffer);
  return true;
}


/**
 * The method called by the thread
 */
void *AxiDmxThread::Run() {
  TimeStamp ts1, ts2;
  Clock clock;
  DmxBuffer buffer;

  // Setup the widget
  if (!m_widget->IsOpen())
    m_widget->SetupOutput();

  while (1) {
    {
      ola::thread::MutexLocker locker(&m_term_mutex);
      if (m_term)
        break;
    }

    {
      ola::thread::MutexLocker locker(&m_buffer_mutex);
      buffer.Set(m_buffer);
    }

    m_widget->Write(buffer);
    usleep(22000);

  }
  return NULL;
}


}  // namespace axidmx
}  // namespace plugin
}  // namespace ola
