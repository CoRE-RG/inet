//
// Copyright (C) OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package inet.routing.contract;

//
// Interface for routing protocol modules connected to IP Layer.
//
moduleinterface IEigrp
{
    parameters:
        bool enableIPv4;
        bool enableIPv6;
        @display("i=block/network");
    gates:
        input ipIn @labels(Ipv4ControlInfo/up,Ipv6ControlInfo/up);
        output ipOut @labels(Ipv4ControlInfo/down,Ipv6ControlInfo/down);
}

