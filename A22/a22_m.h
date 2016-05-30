//
// Generated file, do not edit! Created by nedtool 4.6 from a22.msg.
//

#ifndef _A22_M_H_
#define _A22_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>a22.msg:19</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * message A22
 * {
 *     int priority;
 *     simtime_t timestamp;
 *     int gateIndex;
 * }
 * </pre>
 */
class A22 : public ::cMessage
{
  protected:
    int priority_var;
    simtime_t timestamp_var;
    int gateIndex_var;

  private:
    void copy(const A22& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const A22&);

  public:
    A22(const char *name=NULL, int kind=0);
    A22(const A22& other);
    virtual ~A22();
    A22& operator=(const A22& other);
    virtual A22 *dup() const {return new A22(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getPriority() const;
    virtual void setPriority(int priority);
    virtual simtime_t getTimestamp() const;
    virtual void setTimestamp(simtime_t timestamp);
    virtual int getGateIndex() const;
    virtual void setGateIndex(int gateIndex);
};

inline void doPacking(cCommBuffer *b, A22& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, A22& obj) {obj.parsimUnpack(b);}


#endif // ifndef _A22_M_H_

