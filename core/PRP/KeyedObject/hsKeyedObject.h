#ifndef _HSKEYEDOBJECT_H
#define _HSKEYEDOBJECT_H

#include "plReceiver.h"

DllClass hsKeyedObject : public plReceiver {
protected:
    plKey myKey;

public:
    hsKeyedObject();
    virtual ~hsKeyedObject();

    DECLARE_CREATABLE(hsKeyedObject)
    void init(const plString& name);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
    
public:
    plKey getKey() const;
    void setKey(plKey key);
};

DllClass hsKeyedObjectStub : public hsKeyedObject {
protected:
    plCreatableStub* fStub;

public:
    hsKeyedObjectStub();
    virtual ~hsKeyedObjectStub();

    virtual short ClassIndex() const;
    virtual const char* ClassName() const;

    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const plCreatableStub* getStub() const;
    void setStub(plCreatableStub* stub);
};

#endif
