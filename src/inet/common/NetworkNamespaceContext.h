//
// Copyright (C) OpenSimLtd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_NETWORKNAMESPACECONTEXT_H
#define __INET_NETWORKNAMESPACECONTEXT_H

#include "inet/common/INETDefs.h"

namespace inet {

class INET_API NetworkNamespaceContext
{
  protected:
    int oldNs = -1;
    int newNs = -1;

  public:
    NetworkNamespaceContext(const char *networkNamespace);
    ~NetworkNamespaceContext();
};

} // namespace inet

#endif

