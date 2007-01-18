#ifndef _PLBITMAP_H
#define _PLBITMAP_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../CoreLib/hsStream.h"

#define IMG_ARGB 0
#define IMG_DXT  1
#define IMG_JPEG 2

#define BITMAPVER (char)2

class plBitmap : public hsKeyedObject {
protected:
    char BPP, CPB;
    short flags;
    char imgType;
    char texelSize, texelType;
    int Unk1, Unk2;

public:
    plBitmap(PlasmaVer pv = pvUnknown);
    ~plBitmap();

    void read(hsStream * S);
    void write(hsStream * S);

    void readData(hsStream * S);
    void writeData(hsStream * S);
};

#endif
