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
 * URLEntry.h
 * Copyright (C) 2012 Simon Newton
 */

#ifndef TOOLS_SLP_URLENTRY_H_
#define TOOLS_SLP_URLENTRY_H_

#include <ola/io/BigEndianStream.h>

#include <sstream>
#include <string>
#include <vector>

using ola::io::BigEndianOutputStreamInterface;
using std::ostream;
using std::string;

namespace ola {
namespace slp {

/**
 * Represents an SLP URLEntry.
 */
class URLEntry {
  public:
    URLEntry() : m_lifetime(0) {}

    URLEntry(uint16_t lifetime, const string &url)
        : m_lifetime(lifetime),
          m_url(url) {
    }
    ~URLEntry() {}

    // getters and setters
    uint16_t Lifetime() const { return m_lifetime; }
    void Lifetime(uint16_t lifetime) { m_lifetime = lifetime; }
    string URL() const { return m_url; }
    void URL(const string &url) { m_url = url; }

    // Return the total size of this URL entry
    unsigned int Size() const { return 6 + m_url.size(); }

    // Write this URLEntry to an IOQueue
    void Write(ola::io::BigEndianOutputStreamInterface *output) const;

    bool operator==(const URLEntry &other) const {
      return (m_lifetime == other.m_lifetime && m_url == other.m_url);
    }

    friend ostream& operator<<(ostream &out, const URLEntry &entry) {
      return out << entry.URL() << "(" << entry.Lifetime() << ")";
    }

  private:
    uint16_t m_lifetime;
    string m_url;
};

// typedef for convenience
typedef std::vector<URLEntry> URLEntries;
}  // slp
}  // ola
#endif  // TOOLS_SLP_URLENTRY_H_
