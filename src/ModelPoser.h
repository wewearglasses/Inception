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
protected:
    map<string,aiMatrix4x4>bindPose;
};


#endif /* defined(__MODEL_POSER__) */
