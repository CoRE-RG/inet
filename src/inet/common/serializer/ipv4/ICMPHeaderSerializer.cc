//
// Copyright (C) 2005 Christian Dankbar, Irene Ruengeler, Michael Tuexen, Andras Varga
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

#include "inet/common/packet/serializer/ChunkSerializerRegistry.h"
#include "inet/common/serializer/ipv4/ICMPHeaderSerializer.h"
#include "inet/networklayer/ipv4/IcmpHeader_m.h"

namespace inet {

namespace serializer {

Register_Serializer(IcmpHeader, ICMPHeaderSerializer);
Register_Serializer(ICMPEchoRequest, ICMPHeaderSerializer);
Register_Serializer(ICMPEchoReply, ICMPHeaderSerializer);

void ICMPHeaderSerializer::serialize(MemoryOutputStream& stream, const Ptr<const Chunk>& chunk) const
{
    const auto& icmpHeader = std::static_pointer_cast<const IcmpHeader>(chunk);
    stream.writeByte(icmpHeader->getType());
    stream.writeByte(icmpHeader->getCode());
    stream.writeUint16Be(icmpHeader->getChksum());
    switch (icmpHeader->getType()) {
        case ICMP_ECHO_REQUEST: {
            const auto& icmpEchoRq = CHK(std::dynamic_pointer_cast<const ICMPEchoRequest>(chunk));
            stream.writeUint16Be(icmpEchoRq->getIdentifier());
            stream.writeUint16Be(icmpEchoRq->getSeqNumber());
            break;
        }
        case ICMP_ECHO_REPLY: {
            const auto& icmpEchoReply = CHK(std::dynamic_pointer_cast<const ICMPEchoReply>(chunk));
            stream.writeUint16Be(icmpEchoReply->getIdentifier());
            stream.writeUint16Be(icmpEchoReply->getSeqNumber());
            break;
        }
        case ICMP_DESTINATION_UNREACHABLE:
            stream.writeUint16Be(0);   // unused
            stream.writeUint16Be(0);   // next hop MTU
            break;
        case ICMP_TIME_EXCEEDED:
            stream.writeUint32Be(0);   // unused
            break;
        default:
            throw cRuntimeError("Can not serialize ICMP packet: type %d  not supported.", icmpHeader->getType());
    }
}

const Ptr<Chunk> ICMPHeaderSerializer::deserialize(MemoryInputStream& stream) const
{
    auto icmpHeader = std::make_shared<IcmpHeader>();
    uint8_t type = stream.readByte();
    icmpHeader->setType(type);
    icmpHeader->setCode(stream.readByte());
    icmpHeader->setChksum(stream.readUint16Be());
    switch (type) {
        case ICMP_ECHO_REQUEST: {
            auto echoRq = std::make_shared<ICMPEchoRequest>();
            echoRq->setType(type);
            echoRq->setCode(icmpHeader->getCode());
            echoRq->setChksum(icmpHeader->getChksum());
            echoRq->setIdentifier(stream.readUint16Be());
            echoRq->setSeqNumber(stream.readUint16Be());
            icmpHeader = echoRq;
            break;
        }
        case ICMP_ECHO_REPLY: {
            auto echoReply = std::make_shared<ICMPEchoReply>();
            echoReply->setType(type);
            echoReply->setCode(icmpHeader->getCode());
            echoReply->setChksum(icmpHeader->getChksum());
            echoReply->setIdentifier(stream.readUint16Be());
            echoReply->setSeqNumber(stream.readUint16Be());
            icmpHeader = echoReply;
            break;
        }
        case ICMP_DESTINATION_UNREACHABLE:
            stream.readUint16Be();   // unused
            stream.readUint16Be();   // next hop MTU
            break;
        case ICMP_TIME_EXCEEDED:
            stream.readUint32Be();   // unused
            break;
        default:
            EV_ERROR << "Can not parse ICMP packet: type " << type << " not supported.";
            icmpHeader->markImproperlyRepresented();
            break;
    }
    return icmpHeader;
}

} // namespace serializer

} // namespace inet

