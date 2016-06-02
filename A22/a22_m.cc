//
// Generated file, do not edit! Created by nedtool 4.6 from a22.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "a22_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(A22);

A22::A22(const char *name, int kind) : ::cMessage(name,kind)
{
    this->priority_var = 0;
    this->timestamp_var = 0;
    this->gateIndex_var = 0;
}

A22::A22(const A22& other) : ::cMessage(other)
{
    copy(other);
}

A22::~A22()
{
}

A22& A22::operator=(const A22& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void A22::copy(const A22& other)
{
    this->priority_var = other.priority_var;
    this->timestamp_var = other.timestamp_var;
    this->gateIndex_var = other.gateIndex_var;
}

void A22::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->priority_var);
    doPacking(b,this->timestamp_var);
    doPacking(b,this->gateIndex_var);
}

void A22::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->priority_var);
    doUnpacking(b,this->timestamp_var);
    doUnpacking(b,this->gateIndex_var);
}

int A22::getPriority() const
{
    return priority_var;
}

void A22::setPriority(int priority)
{
    this->priority_var = priority;
}

simtime_t A22::getTimestamp() const
{
    return timestamp_var;
}

void A22::setTimestamp(simtime_t timestamp)
{
    this->timestamp_var = timestamp;
}

int A22::getGateIndex() const
{
    return gateIndex_var;
}

void A22::setGateIndex(int gateIndex)
{
    this->gateIndex_var = gateIndex;
}

class A22Descriptor : public cClassDescriptor
{
  public:
    A22Descriptor();
    virtual ~A22Descriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(A22Descriptor);

A22Descriptor::A22Descriptor() : cClassDescriptor("A22", "cMessage")
{
}

A22Descriptor::~A22Descriptor()
{
}

bool A22Descriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<A22 *>(obj)!=NULL;
}

const char *A22Descriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int A22Descriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int A22Descriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *A22Descriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "priority",
        "timestamp",
        "gateIndex",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int A22Descriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "timestamp")==0) return base+1;
    if (fieldName[0]=='g' && strcmp(fieldName, "gateIndex")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *A22Descriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "simtime_t",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *A22Descriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int A22Descriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    A22 *pp = (A22 *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string A22Descriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    A22 *pp = (A22 *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPriority());
        case 1: return double2string(pp->getTimestamp());
        case 2: return long2string(pp->getGateIndex());
        default: return "";
    }
}

bool A22Descriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    A22 *pp = (A22 *)object; (void)pp;
    switch (field) {
        case 0: pp->setPriority(string2long(value)); return true;
        case 1: pp->setTimestamp(string2double(value)); return true;
        case 2: pp->setGateIndex(string2long(value)); return true;
        default: return false;
    }
}

const char *A22Descriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *A22Descriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    A22 *pp = (A22 *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


