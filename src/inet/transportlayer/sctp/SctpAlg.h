//
// Copyright (C) 2008 Irene Ruengeler
// Copyright (C) 2010-2012 Thomas Dreibholz
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef __INET_SCTPALG_H
#define __INET_SCTPALG_H

#include "inet/transportlayer/sctp/SctpAlgorithm.h"

namespace inet {
namespace sctp {

/**
 * State variables for SctpAlg.
 */
class INET_API SctpAlgStateVariables : public SctpStateVariables
{
  public:
    // ...
};

class INET_API SctpAlg : public SctpAlgorithm
{
  protected:
    SctpAlgStateVariables *state;

  public:
    /**
     * Ctor.
     */
    SctpAlg();

    /**
     * Virtual dtor.
     */
    virtual ~SctpAlg();

    /**
     * Creates and returns a SctpStateVariables object.
     */
    virtual SctpStateVariables *createStateVariables() override;

    virtual void established(bool active) override;

    virtual void connectionClosed() override;

    virtual void processTimer(cMessage *timer, SctpEventCode& event) override;

    virtual void sendCommandInvoked(SctpPathVariables *path) override;

    virtual void receivedDataAck(uint32_t firstSeqAcked) override;

    virtual void receivedDuplicateAck() override;

    virtual void receivedAckForDataNotYetSent(uint32_t seq) override;

    virtual void sackSent() override;

    virtual void dataSent(uint32_t fromseq) override;
};

} // namespace sctp
} // namespace inet

#endif

