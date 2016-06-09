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

#include "LinMaster.h"

Define_Module(LinMaster)

LinMaster::LinMaster() {
}

LinMaster::~LinMaster() {
    /*
     * todo: delete all cMessages
     */
    cancelAndDelete(timerEvent);
    cancelAndDelete(checkCollisionEvent);
}

void LinMaster::initialize() {


    needSporadic = false;
    changeSporadic = new cMessage("changeSporadic");
    scheduleAt(simTime() + 2 + dblrand() * 2, changeSporadic);

    timer = 0.01;
    timerEvent = new cMessage("timeout");
    checkCollisionEvent = new cMessage("checkCollisionEvent");
    counter = 0;
    eventAnswerCount = 0;

    latenzVector.setName("Latenz");
    eventTriggerVector.setName("Events");
    sporadicVector.setName("Sporadics");
    unconditionalVector.setName("Uncoditionals");
    collisionVector.setName("Collisions");
    sameSporadicAgain = false;


    scheduleAt(simTime() + timer, timerEvent);
    /*
     * todo: initialize all variables needed
     */

}

void LinMaster::finish() {
    /*
     * Record final statistics
     */
}

void LinMaster::handleSelfMessage(cMessage *msg) {

    if (msg == changeSporadic) {
        needSporadic = true;
        scheduleAt(simTime() + 2 + dblrand() * 2, changeSporadic);
    }

    if(msg == timerEvent)
    {
        eventAnswerCount = 0;
        counter++;
        if(counter % 5 == 0)
        {
            eventMessageID = intuniform(50, 59);

            eventTriggerVector.record(eventMessageID);
            EV << "Send EventMessag";
            sendLinRequest(eventMessageID);

            scheduleAt(simTime() + 0.001, checkCollisionEvent);
        }
        else if(counter % 3 == 0)
            {
                if(needSporadic || sameSporadicAgain)
                {
                    if(!sameSporadicAgain)
                    {
                        sporadicMessageID = intuniform(40, 49);
                        sendTime = simTime();
                    }

                    sporadicVector.record(sporadicMessageID);
                    EV << "Send SporadicMessage";
                    sendLinRequest(sporadicMessageID);
                }
            }
        else
            {
                int messageId = intuniform(0, 39);
                unconditionalVector.record(messageId);
                EV << "Send UnconditionalMessage";
                sendLinRequest(messageId);
            }

        scheduleAt(simTime() + timer, timerEvent);
    }

    if(msg == checkCollisionEvent)
    {

        if(eventAnswerCount > 1)
        {
            collisionVector.record(eventAnswerCount-1);
            std::vector<int> nodes = getEventTriggeredIds(eventMessageID);
            for(int messageID:nodes)
            {
                unconditionalVector.record(messageID);
                EV << "Send UnconditionalMessage";
                sendLinRequest(messageID);
            }
        }
        else
        {
            collisionVector.record(0);
        }
    }
    /*
     * todo: handle Self Messages in order to send next packet or check timeouts
     */

}

void LinMaster::receiveFrame(cMessage *msg) {

    LinResponseFrame* response = check_and_cast<LinResponseFrame *>(msg);
    FRAME_TYPE frameType = getFrameType(response->getMessageId());

    switch(frameType)
    {
        case EVENT_TRIGGERED_FRAME:
        {
            eventAnswerCount++;
            break;
        }
        case SPORADIC_FRAME:
        {
            int result = response->getResponse();
            if(result == 1)
            {
                simtime_t latenz = simTime() - sendTime;
                needSporadic = false;
                sameSporadicAgain = false;
                latenzVector.record(latenz);
            }
            else
            {
                sameSporadicAgain = true;
            }
            break;
        }

    }

    cancelAndDelete(msg);

    /*
     * todo: handle received Frames, check for collisions
     */
}

