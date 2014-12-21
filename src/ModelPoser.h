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

typedef map<string,aiVector3D> Pose;
class ModelPoser:public ofxAssimpModelLoader{
public:
    Pose randomPose();
    void loopPose(int index, int total);
    void getBindPose();
    void dance(float volume);
    void setPose(Pose p);
protected:
    bool excludeBone(string boneName);
    map<string,aiMatrix4x4>bindPose;
    Pose currDancePose;
    vector<Pose> loopPoses;

};


#endif /* defined(__MODEL_POSER__) */
