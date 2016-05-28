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
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "a22_m.h"

using namespace omnetpp;

class network22 : public cSimpleModule{
    private:
    simtime_t timer;  // timeout
    cMessage *timerEvent;  // holds pointer to the timeout self-message

    public:
        int master;
        network22();
        virtual ~network22();
    protected:
    virtual A22 *generateMessage();
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(network22);

network22::network22()
{
    timerEvent = nullptr;
}

network22::~network22()
{
    cancelAndDelete(timerEvent);
}

void network22::initialize()
{
    // Initialize variables
  //  numSent = 0;
   // numReceived = 0;
   // WATCH(numSent);
  //  WATCH(numReceived);

 //   hopCountStats.setName("hopCountStats");
//    hopCountStats.setRangeAutoUpper(0, 10, 1.5);
//    hopCountVector.setName("HopCount");

    timer = 0.08;
    timerEvent = new cMessage("timerEvent");

    // Master sends message
    master = par("master");
    if (master == 1) {
        // Boot the process scheduling the initial message as a self-message.
        A22 *msg = generateMessage();
        send(msg, "gate$o", 0);
        send(msg, "gate$o", 1);
    }
    scheduleAt(simTime()+timer, timerEvent);
}

void network22::handleMessage(cMessage *msg)
{
    if (msg == timerEvent) {
        // master sends new message
        if(master == 1)
        {
            EV << "Timer expired, sending new message and restarting timer\n";
            A22 *msg = generateMessage();
            send(msg, "gate$o", 0);
            send(msg, "gate$o", 1);
            scheduleAt(simTime()+timer, timerEvent);
        }
    }
    else
    {
        A22* ttmsg = check_and_cast<A22 *>(msg);
        simtime_t responsedelay = uniform(0,ttmsg->getPriority()) /1000;
        simtime_t procdelay = par("delayTime");
        responsedelay += procdelay;

        delete msg;

        A22* nmsg = generateMessage();
    }
}

A22* network22::generateMessage()
{
    int prio = intuniform(0,3);
    char msgname[20];
    sprintf(msgname, "Mastermsg-with-prio-%d", prio);
    A22* msg = new A22(msgname);

    msg->setPriority(prio);
    msg->setTimestamp(simTime());

    return msg;
}
