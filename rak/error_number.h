// rak - Rakshasa's toolbox
// Copyright (C) 2005-2007, Jari Sundell
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// In addition, as a special exception, the copyright holders give
// permission to link the code of portions of this program with the
// OpenSSL library under certain conditions as described in each
// individual source file, and distribute linked combinations
// including the two.
//
// You must obey the GNU General Public License in all respects for
// all of the code used other than OpenSSL.  If you modify file(s)
// with this exception, you may extend this exception to your version
// of the file(s), but you are not obligated to do so.  If you do not
// wish to do so, delete this exception statement from your version.
// If you delete this exception statement from all source files in the
// program, then also delete it here.
//
// Contact:  Jari Sundell <jaris@ifi.uio.no>
//
//           Skomakerveien 33
//           3185 Skoppum, NORWAY

#ifndef RAK_ERROR_NUMBER_H
#define RAK_ERROR_NUMBER_H

#include <cerrno>
#include <cstring>

namespace rak {

class error_number {
public:
  static const int e_access      = EACCES;
  static const int e_again       = EAGAIN;
  static const int e_connreset   = ECONNRESET;
  static const int e_connaborted = ECONNABORTED;
  static const int e_deadlk      = EDEADLK;

  static const int e_noent       = ENOENT;
  static const int e_nodev       = ENODEV;
  static const int e_nomem       = ENOMEM;
  static const int e_notdir      = ENOTDIR;
  static const int e_isdir       = EISDIR;
  
  static const int e_intr        = EINTR;

  error_number() = default;
  error_number(int e) : m_errno(e) {}

  bool                is_valid() const             { return m_errno != 0; }

  int                 value() const                { return m_errno; }
  const char*         c_str() const                { return std::strerror(m_errno); }

  bool                is_blocked_momentary() const { return m_errno == e_again || m_errno == e_intr; }
  bool                is_blocked_prolonged() const { return m_errno == e_deadlk; }

  bool                is_closed() const            { return m_errno == e_connreset || m_errno == e_connaborted; }

  bool                is_bad_path() const          { return m_errno == e_noent || m_errno == e_notdir || m_errno == e_access; }

  static error_number current()                    { return errno; }
  static void         clear_global()               { errno = 0; }
  static void         set_global(error_number err) { errno = err.m_errno; }

  bool operator == (const error_number& e) const   { return m_errno == e.m_errno; }

private:
  int                 m_errno{};
};

}

#endif
