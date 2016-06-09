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

#include "LinSlave.h"

Define_Module(LinSlave)

LinSlave::LinSlave()
{}

LinSlave::~LinSlave()
{}

void LinSlave::receiveFrame(cMessage *msg) {


    LinRequestFrame* response = check_and_cast<LinRequestFrame *>(msg);

    FRAME_TYPE frameType = getFrameType(response->getMessageId());

        switch(frameType)
        {
            case EVENT_TRIGGERED_FRAME:
            {
                if(isResponsibleForEventTriggered(response->getMessageId()))
                {
                    sendLinResponse(response->getMessageId(), 0);
                }

                break;
            }
            case SPORADIC_FRAME:
            {
                if(response->getMessageId() == getIndex())
                {
                    int result = intuniform(0,1);
                    sendLinResponse(response->getMessageId(), result);
                }

                break;
            }
            case UNCONDITIONAL_FRAME:
            {
                if(response->getMessageId() == getIndex())
                {
                    sendLinResponse(response->getMessageId(), 0);
                }
                break;
            }

        }

        delete(msg);


    /*
     * todo: handle received Frames, send responses
     */

}
