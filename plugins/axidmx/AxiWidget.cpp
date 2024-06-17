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
 * AxiWidget.cpp
 * This class is based on QLCFTDI class from
 *
 * Q Light Controller
 * qlcftdi-libftdi.cpp
 *
 * Copyright (C) Heikki Junnila
 *
 * Only standard CPP conversion was changed and function name changed
 * to follow OLA coding standards.
 *
 * by Rui Barreiros
 * Copyright (C) 2014 Richard Ash
 */

#include <strings.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <string>
#include <algorithm>
#include <vector>

#include "ola/Constants.h"
#include "ola/io/IOUtils.h"
#include "ola/Logging.h"
#include "plugins/axidmx/AxiWidget.h"

namespace ola {
namespace plugin {
namespace axidmx {

using std::string;
using std::vector;

AxiWidget::AxiWidget(const string& path)
    : m_path(path),
      m_fd(NOT_OPEN) {
}

AxiWidget::~AxiWidget() {
  if (IsOpen()) {
    Close();
  }
}


bool AxiWidget::Open() {
  OLA_DEBUG << "Opening AXI port " << Name();
  if (!ola::io::Open(m_path, O_WRONLY, &m_fd)) {
    m_fd = FAILED_OPEN;
    OLA_WARN << Name() << " failed to open";
    return false;
  } else {
    OLA_DEBUG << "Opened AXI port " << Name();
    return true;
  }
}

bool AxiWidget::Close() {
  if (!IsOpen()) {
    return true;
  }

  if (close(m_fd) > 0) {
    OLA_WARN << Name() << " error closing";
    m_fd = NOT_OPEN;
    return false;
  } else {
    m_fd = NOT_OPEN;
    return true;
  }
}

bool AxiWidget::IsOpen() const {
  return m_fd >= 0;
}

bool AxiWidget::Write(const ola::DmxBuffer& data) {
  unsigned char buffer[DMX_UNIVERSE_SIZE];
  unsigned int length = DMX_UNIVERSE_SIZE;
  int ret = 0;
  //buffer[0] = DMX512_START_CODE; start code managed by hardware

  data.Get(buffer, &length);
  OLA_WARN << "AxiWidget::Write() called m_fd" << m_fd << " length" << length;
  ret =  write(m_fd, buffer, length );
  if (ret <= 0) {
    // TODO(richardash1981): handle errors better as per the test code,
    // especially if we alter the scheduling!
    OLA_WARN << Name() << " Short or failed write!: return code " << ret;
    return false;
  } else {
    return true;
  }
}

bool AxiWidget::Read(unsigned char *buff, int size) {
  int readb = read(m_fd, buff, size);
  if (readb <= 0) {
    OLA_WARN << Name() << " read error";
    return false;
  } else {
    return true;
  }
}

/**
 * Setup our device for DMX send
 * Also used to test if device is working correctly
 * before AddDevice()
 */
bool AxiWidget::SetupOutput() {

  if (Open() == false) {
    OLA_WARN << "Error Opening widget";
    return false;
  }

  // no specific action needed

  return true;
}

}  // namespace axidmx
}  // namespace plugin
}  // namespace ola
