//
// Generated file, do not edit! Created by nedtool 4.6 from veins/modules/messages/WaveShortMessage.msg.
//

#ifndef _WAVESHORTMESSAGE_M_H_
#define _WAVESHORTMESSAGE_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "veins/base/utils/Coord.h"
// }}

/**
 * Class generated from <tt>veins/modules/messages/WaveShortMessage.msg:27</tt> by nedtool.
 * <pre>
 * packet WaveShortMessage
 * {
 *     //Version of the Wave Short Message
 *     int wsmVersion = 0;
 *     //Determine which security mechanism was used
 *     int securityType = 0;
 *     //Channel Number on which this packet was sent
 *     int channelNumber;
 *     //Data rate with which this packet was sent
 *     int dataRate = 1;
 *     //Power Level with which this packet was sent
 *     int priority = 3;
 *     //Unique number to identify the service
 *     int psid = 0;
 *     //Provider Service Context
 *     string psc = "Service with some Data";
 *     //Length of Wave Short Message
 *     int wsmLength;
 *     //Data of Wave Short Message
 *     string wsmData = "Some Data";
 * 
 *     int senderAddress = 0;
 *     int recipientAddress = -1;
 *     int serial = 0;
 *     Coord senderPos;
 *     Coord senderSpeed;
 *     simtime_t timestamp = 0;
 * }
 * </pre>
 */
class WaveShortMessage : public ::cPacket
{
  protected:
    int wsmVersion_var;
    int securityType_var;
    int channelNumber_var;
    int dataRate_var;
    int priority_var;
    int psid_var;
    opp_string psc_var;
    int wsmLength_var;
    opp_string wsmData_var;
    int senderAddress_var;
    int recipientAddress_var;
    int serial_var;
    Coord senderPos_var;
    Coord senderSpeed_var;
    simtime_t timestamp_var;

  private:
    void copy(const WaveShortMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const WaveShortMessage&);

  public:
    WaveShortMessage(const char *name=NULL, int kind=0);
    WaveShortMessage(const WaveShortMessage& other);
    virtual ~WaveShortMessage();
    WaveShortMessage& operator=(const WaveShortMessage& other);
    virtual WaveShortMessage *dup() const {return new WaveShortMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getWsmVersion() const;
    virtual void setWsmVersion(int wsmVersion);
    virtual int getSecurityType() const;
    virtual void setSecurityType(int securityType);
    virtual int getChannelNumber() const;
    virtual void setChannelNumber(int channelNumber);
    virtual int getDataRate() const;
    virtual void setDataRate(int dataRate);
    virtual int getPriority() const;
    virtual void setPriority(int priority);
    virtual int getPsid() const;
    virtual void setPsid(int psid);
    virtual const char * getPsc() const;
    virtual void setPsc(const char * psc);
    virtual int getWsmLength() const;
    virtual void setWsmLength(int wsmLength);
    virtual const char * getWsmData() const;
    virtual void setWsmData(const char * wsmData);
    virtual int getSenderAddress() const;
    virtual void setSenderAddress(int senderAddress);
    virtual int getRecipientAddress() const;
    virtual void setRecipientAddress(int recipientAddress);
    virtual int getSerial() const;
    virtual void setSerial(int serial);
    virtual Coord& getSenderPos();
    virtual const Coord& getSenderPos() const {return const_cast<WaveShortMessage*>(this)->getSenderPos();}
    virtual void setSenderPos(const Coord& senderPos);
    virtual Coord& getSenderSpeed();
    virtual const Coord& getSenderSpeed() const {return const_cast<WaveShortMessage*>(this)->getSenderSpeed();}
    virtual void setSenderSpeed(const Coord& senderSpeed);
    virtual simtime_t getTimestamp() const;
    virtual void setTimestamp(simtime_t timestamp);
};

inline void doPacking(cCommBuffer *b, WaveShortMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, WaveShortMessage& obj) {obj.parsimUnpack(b);}


#endif // ifndef _WAVESHORTMESSAGE_M_H_

