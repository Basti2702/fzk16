//
// Copyright (C) 2006-2011 Christoph Sommer <christoph.sommer@uibk.ac.at>
//
// Documentation for these modules is at http://veins.car2x.org/
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

#include "veins/modules/application/ieee80211p/SimpleWaveApp.h"

using Veins::AnnotationManagerAccess;

Define_Module(SimpleWaveApp);


void SimpleWaveApp::initialize(int stage) {
	BaseWaveApplLayer::initialize(stage);
	if (stage == 0) {
		mobi = dynamic_cast<TraCIMobility*> (getParentModule()->getSubmodule("veinsmobility"));
		ASSERT(mobi);
	}
}

//function will be called when beacon packet has been received
void SimpleWaveApp::onBeacon(WaveShortMessage* wsm) {
    //todo nachbarschaftsliste aufbauen und auf anfragen antworten
    /*WaveShortMessage* wsmNew = prepareWSM("data", dataLengthBits, type_CCH, dataPriority, wsm->getSenderAddress(), -1);
    wsmNew->setTimestamp(wsm->getTimestamp());
    double off = dblrand() * par("maxOffset").doubleValue();
    sendDelayedDown(wsm,off);*/
    int id = wsm->getSenderAddress();
    std::list<struct neighbour>::iterator it;
    bool alreadyInList = false;
    for (it=neighbourlist.begin(); it!=neighbourlist.end(); ++it)
    {
        if((*it).ID == id)
        {
            (*it).position = wsm->getSenderPos();
            (*it).speed = wsm->getSenderSpeed();
            (*it).lastUpdate = simTime();
            alreadyInList = true;
            break;
        }
    }

    if(!alreadyInList)
    {
        struct neighbour newNeighbour;
        newNeighbour.position = wsm->getSenderPos();
        newNeighbour.speed = wsm->getSenderSpeed();
        newNeighbour.lastUpdate = simTime();
        newNeighbour.ID = id;
        neighbourlist.push_front(newNeighbour);
    }
    receivedMessages++;
  //  std::cerr << "Received Beacon" << std::endl;
}

//function will be called when data packet has been received
void SimpleWaveApp::onData(WaveShortMessage* wsm) {
	findHost()->getDisplayString().updateWith("r=16,green");
/*	if(wsm->getRecipientAddress() == myId)
	{
	   simtime_t latenz = simTime() - wsm->getTimestamp();
	   latenzVector.record(latenz);
	}*/
	if(map.find(wsm->getPsid()) != map.end())
	{
	    //add id to map
	    map.insert(std::pair<wsm->getPsid(), NULL>);
	}

}

//function will be called when node has been moved. see parent class how to access a node's position
void SimpleWaveApp::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);
    //todo (get position and speed)

}

void SimpleWaveApp::sendMessage(std::string blockedRoadId) {
	t_channel channel = dataOnSch ? type_SCH : type_CCH;
	WaveShortMessage* wsm = prepareWSM("data", dataLengthBits, channel, dataPriority, -1,2);
	wsm->setWsmData(blockedRoadId.c_str());
	sendWSM(wsm);
}
void SimpleWaveApp::sendWSM(WaveShortMessage* wsm) {
	sendDelayedDown(wsm,individualOffset);
}
