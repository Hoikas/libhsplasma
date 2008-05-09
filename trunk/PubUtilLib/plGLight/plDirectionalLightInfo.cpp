#include "plDirectionalLightInfo.h"

// plDirectionalLightInfo //
plDirectionalLightInfo::plDirectionalLightInfo() { }
plDirectionalLightInfo::~plDirectionalLightInfo() { }

IMPLEMENT_CREATABLE(plDirectionalLightInfo, kDirectionalLightInfo, plLightInfo)


// plLimitedDirLightInfo //
plLimitedDirLightInfo::plLimitedDirLightInfo() { }
plLimitedDirLightInfo::~plLimitedDirLightInfo() { }

IMPLEMENT_CREATABLE(plLimitedDirLightInfo, kLimitedDirLightInfo,
                    plDirectionalLightInfo)

void plLimitedDirLightInfo::read(hsStream* S, plResManager* mgr) {
    plLightInfo::read(S, mgr);
    fWidth = S->readFloat();
    fHeight = S->readFloat();
    fDepth = S->readFloat();
}

void plLimitedDirLightInfo::write(hsStream* S, plResManager* mgr) {
    plLightInfo::write(S, mgr);
    S->writeFloat(fWidth);
    S->writeFloat(fHeight);
    S->writeFloat(fDepth);
}

void plLimitedDirLightInfo::IPrcWrite(pfPrcHelper* prc) {
    plLightInfo::IPrcWrite(prc);
    prc->startTag("Limits");
    prc->writeParam("Width", fWidth);
    prc->writeParam("Height", fHeight);
    prc->writeParam("Depth", fDepth);
    prc->endTag(true);
}

void plLimitedDirLightInfo::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Limits") {
        fWidth = tag->getParam("Width", "0").toFloat();
        fHeight = tag->getParam("Height", "0").toFloat();
        fDepth = tag->getParam("Depth", "0").toFloat();
    } else {
        plLightInfo::IPrcParse(tag, mgr);
    }
}
