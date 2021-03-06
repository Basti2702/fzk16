//
// Generated file, do not edit! Created by nedtool 4.6 from LinRequestFrame.msg.
//

#ifndef _LINREQUESTFRAME_M_H_
#define _LINREQUESTFRAME_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>LinRequestFrame.msg:19</tt> by nedtool.
 * <pre>
 * //
 * // Generic LIN request frame
 * //
 * packet LinRequestFrame
 * {
 *     //LIN identifier, which encodes the expected
 *     //response message and the message type
 *     int messageId;
 * }
 * </pre>
 */
class LinRequestFrame : public ::cPacket
{
  protected:
    int messageId_var;

  private:
    void copy(const LinRequestFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LinRequestFrame&);

  public:
    LinRequestFrame(const char *name=NULL, int kind=0);
    LinRequestFrame(const LinRequestFrame& other);
    virtual ~LinRequestFrame();
    LinRequestFrame& operator=(const LinRequestFrame& other);
    virtual LinRequestFrame *dup() const {return new LinRequestFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getMessageId() const;
    virtual void setMessageId(int messageId);
};

inline void doPacking(cCommBuffer *b, LinRequestFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, LinRequestFrame& obj) {obj.parsimUnpack(b);}


#endif // ifndef _LINREQUESTFRAME_M_H_

