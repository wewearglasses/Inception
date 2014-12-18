//
//  ModelPoser.h
//  Inception
//
//  Created by Shang Liang on 12/8/14.
//
//

#ifndef __MODEL_POSER__
#define __MODEL_POSER__

#include <stdio.h>
#include "ofxAssimpModelLoader.h"
#include <map>

class ModelPoser:public ofxAssimpModelLoader{
public:
    void randomPose();
    void loopPose();
    void getBindPose();
protected:
    map<string,aiMatrix4x4>bindPose;
    map<string,aiVector3D>originRotations;
    map<string,aiVector3D>phase1Rotations;
    map<string,aiVector3D>phase2Rotations;
    map<string,aiVector3D>phase3Rotations;
    map<string,aiVector3D>phase4Rotations;
    map<string,aiVector3D>phase5Rotations;
    float p;
};


#endif /* defined(__MODEL_POSER__) */
