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


class node : public cSimpleModule{
    private:
    simtime_t timer;  // timeout
    cMessage *timerEvent;  // holds pointer to the timeout self-message
    cMessage *event;
    cMessage *finishSim;
    A22 *respToMaster;

    cOutVector latenzVector;
    int numPrio0;
    int numPrio1;
    int numPrio2;
    int numPrio3;

    public:
        int master;
        node();
        virtual ~node();
    protected:
    virtual A22 *generateMessage();
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

Define_Module(node);

node::node()
{
    timerEvent = nullptr;
    event = nullptr;
    finishSim = nullptr;
}

node::~node()
{
    cancelAndDelete(timerEvent);
    cancelAndDelete(event);
    cancelAndDelete(finishSim);
}

void node::initialize()
{
    // Initialize variables
      numPrio0 = 0;
    numPrio1 = 0;
    numPrio2 = 0;
    numPrio3 = 0;
    WATCH(numPrio0);
    WATCH(numPrio1);
    WATCH(numPrio2);
    WATCH(numPrio3);
    latenzVector.setName("Latenz");


    event = new cMessage("event");
    finishSim = new cMessage("finish");

    timer = 0.08;
    timerEvent = new cMessage("timerEvent");

    // Master sends message
    master = par("master");
    /*if (master == 1) {
        // Boot the process scheduling the initial message as a self-message.
        A22 *msg = generateMessage();
        send(msg, "gate$o", 0);
        cMessage *copy = (cMessage *) msg->dup();
        send(copy, "gate$o", 1);
    }*/
    scheduleAt(simTime()+timer, timerEvent);
    scheduleAt(simTime()+2.0, finishSim);
}

void node::handleMessage(cMessage *msg)
{
    if(msg == finishSim)
    {
       if(master == 1)
       {
           cancelEvent(timerEvent);
       }
       else
       {
           cancelEvent(event);
       }
    }
    else if (msg == timerEvent) {
        // master sends new message
        if(master == 1)
        {
            A22 *msg = generateMessage();
            send(msg, "gate$o", 0);
            A22 *copy = (A22 *) msg->dup();
            send(copy, "gate$o", 1);

            switch(msg->getPriority())
            {
                case 0: { numPrio0++; break; }
                case 1: { numPrio1++; break; }
                case 2: { numPrio2++; break; }
                case 3: { numPrio3++; break; }
            }

            EV << "Timer expired, sending new message with prio " << msg->getPriority();
            scheduleAt(simTime()+timer, timerEvent);
        }
    }
    else if(master == 0)
    {
        if(msg == event)
        {
            send(respToMaster, "gate$o", respToMaster->getGateIndex());
            respToMaster = nullptr;
        }
        else
        {
            A22* ttmsg = check_and_cast<A22 *>(msg);
            EV<< "priority " << ttmsg->getPriority();
            simtime_t responsedelay = uniform(0,ttmsg->getPriority()) /1000;
            simtime_t procdelay = par("delayTime");
           // responsedelay += procdelay;


            respToMaster = generateMessage();

            cGate *arrivalGate = msg->getArrivalGate();
            int index = arrivalGate->getIndex();
            EV << "Arrival Gate: " << index << "\n";
            EV << "Responsedelay: " << responsedelay;
            respToMaster->setGateIndex(index);
            delete msg;

            scheduleAt(simTime()+responsedelay, event);
        }
    }
    else
    {
        A22* ttmsg = check_and_cast<A22 *>(msg);

        simtime_t latenz = simTime() - ttmsg->getTimestamp();
        latenzVector.record(latenz);

        EV << "Received Response from Slave with latency " << latenz;
        delete msg;
    }
}

void node::finish()
{
    recordScalar("#Prio0", numPrio0);
    recordScalar("#Prio1", numPrio1);
    recordScalar("#Prio2", numPrio2);
    recordScalar("#Prio3", numPrio3);
}

A22* node::generateMessage()
{
    int prio = intuniform(0,3);
    EV << "generated prio: " << prio << "\n";
    char msgname[20];
    sprintf(msgname, "Mastermsg-with-prio-%d", prio);

    A22* msg = new A22(msgname);

    msg->setPriority(prio);
    if(master == 1)
    {
        msg->setTimestamp(-1);
    }
    else
    {
        msg->setTimestamp(simTime());
    }
    EV << "stored prio: " << msg->getPriority() << "\n";
    return msg;
}
