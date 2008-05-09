#include "plDynaRippleMgr.h"

// plDynaRippleMgr //
plDynaRippleMgr::plDynaRippleMgr() { }
plDynaRippleMgr::~plDynaRippleMgr() { }

IMPLEMENT_CREATABLE(plDynaRippleMgr, kDynaRippleMgr, plDynaDecalMgr)

void plDynaRippleMgr::read(hsStream* S, plResManager* mgr) {
    plDynaDecalMgr::read(S, mgr);
    fInitUVW.read(S);
    fFinalUVW.read(S);
}

void plDynaRippleMgr::write(hsStream* S, plResManager* mgr) {
    plDynaDecalMgr::write(S, mgr);
    fInitUVW.write(S);
    fFinalUVW.write(S);
}

void plDynaRippleMgr::IPrcWrite(pfPrcHelper* prc) {
    plDynaDecalMgr::IPrcWrite(prc);

    prc->writeSimpleTag("InitUVW");
    fInitUVW.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("FinalUVW");
    fFinalUVW.prcWrite(prc);
    prc->closeTag();
}

void plDynaRippleMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "InitUVW") {
        if (tag->hasChildren())
            fInitUVW.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "FinalUVW") {
        if (tag->hasChildren())
            fFinalUVW.prcParse(tag->getFirstChild());
    } else {
        plDynaDecalMgr::IPrcParse(tag, mgr);
    }
}


// plDynaRippleVSMgr //
plDynaRippleVSMgr::plDynaRippleVSMgr() { }
plDynaRippleVSMgr::~plDynaRippleVSMgr() { }

IMPLEMENT_CREATABLE(plDynaRippleVSMgr, kDynaRippleVSMgr, plDynaRippleMgr)

void plDynaRippleVSMgr::read(hsStream* S, plResManager* mgr) {
    plDynaRippleMgr::read(S, mgr);
    fWaveSetBase = mgr->readKey(S);
}

void plDynaRippleVSMgr::write(hsStream* S, plResManager* mgr) {
    plDynaRippleMgr::write(S, mgr);
    mgr->writeKey(S, fWaveSetBase);
}

void plDynaRippleVSMgr::IPrcWrite(pfPrcHelper* prc) {
    plDynaRippleMgr::IPrcWrite(prc);

    prc->writeSimpleTag("WaveSet");
    fWaveSetBase->prcWrite(prc);
    prc->closeTag();
}

void plDynaRippleVSMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "WaveSet") {
        if (tag->hasChildren())
            fWaveSetBase = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plDynaRippleMgr::IPrcParse(tag, mgr);
    }
}


// plDynaTorpedoMgr //
plDynaTorpedoMgr::plDynaTorpedoMgr() { }
plDynaTorpedoMgr::~plDynaTorpedoMgr() { }

IMPLEMENT_CREATABLE(plDynaTorpedoMgr, kDynaTorpedoMgr, plDynaRippleMgr)


// plDynaTorpedoVSMgr //
plDynaTorpedoVSMgr::plDynaTorpedoVSMgr() { }
plDynaTorpedoVSMgr::~plDynaTorpedoVSMgr() { }

IMPLEMENT_CREATABLE(plDynaTorpedoVSMgr, kDynaTorpedoVSMgr, plDynaTorpedoMgr)

void plDynaTorpedoVSMgr::read(hsStream* S, plResManager* mgr) {
    plDynaTorpedoMgr::read(S, mgr);
    fWaveSetBase = mgr->readKey(S);
}

void plDynaTorpedoVSMgr::write(hsStream* S, plResManager* mgr) {
    plDynaTorpedoMgr::write(S, mgr);
    mgr->writeKey(S, fWaveSetBase);
}

void plDynaTorpedoVSMgr::IPrcWrite(pfPrcHelper* prc) {
    plDynaTorpedoMgr::IPrcWrite(prc);

    prc->writeSimpleTag("WaveSet");
    fWaveSetBase->prcWrite(prc);
    prc->closeTag();
}

void plDynaTorpedoVSMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "WaveSet") {
        if (tag->hasChildren())
            fWaveSetBase = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plDynaRippleMgr::IPrcParse(tag, mgr);
    }
}


// plDynaPuddleMgr //
plDynaPuddleMgr::plDynaPuddleMgr() { }
plDynaPuddleMgr::~plDynaPuddleMgr() { }

IMPLEMENT_CREATABLE(plDynaPuddleMgr, kDynaPuddleMgr, plDynaRippleMgr)


// plDynaWakeMgr //
plDynaWakeMgr::plDynaWakeMgr() { }
plDynaWakeMgr::~plDynaWakeMgr() { }

IMPLEMENT_CREATABLE(plDynaWakeMgr, kDynaWakeMgr, plDynaRippleMgr)

void plDynaWakeMgr::read(hsStream* S, plResManager* mgr) {
    plDynaRippleMgr::read(S, mgr);

    fDefaultDir.read(S);
    fAnimPath = plAnimPath::Convert(mgr->ReadCreatable(S));
    fAnimWgt = S->readFloat();
    fVelWgt = S->readFloat();
}

void plDynaWakeMgr::write(hsStream* S, plResManager* mgr) {
    plDynaRippleMgr::write(S, mgr);

    fDefaultDir.write(S);
    mgr->WriteCreatable(S, fAnimPath);
    S->writeFloat(fAnimWgt);
    S->writeFloat(fVelWgt);
}

void plDynaWakeMgr::IPrcWrite(pfPrcHelper* prc) {
    plDynaRippleMgr::IPrcWrite(prc);

    prc->writeSimpleTag("DefaultDir");
    fDefaultDir.prcWrite(prc);
    prc->closeTag();

    prc->startTag("DynaWakeMgrParams");
    prc->writeParam("AnimWeight", fAnimWgt);
    prc->writeParam("VelWeight", fVelWgt);
    prc->endTag(true);

    if (fAnimPath != NULL) {
        fAnimPath->prcWrite(prc);
    } else {
        prc->startTag("plAnimPath");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plDynaWakeMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "DefaultDir") {
        if (tag->hasChildren())
            fDefaultDir.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "DynaWakeMgrParams") {
        fAnimWgt = tag->getParam("AnimWeight", "0").toFloat();
        fVelWgt = tag->getParam("VelWeight", "0").toFloat();
    } else if (tag->getName() == "plAnimPath") {
        if (tag->getParam("NULL", "false").toBool()) {
            fAnimPath = NULL;
        } else {
            if (tag->hasChildren())
                fAnimPath = plAnimPath::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
        }
    } else {
        plDynaRippleMgr::IPrcParse(tag, mgr);
    }
}
