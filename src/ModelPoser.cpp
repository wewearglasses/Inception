//
//  ModelPoser.cpp
//  Inception
//
//  Created by Shang Liang on 12/8/14.
//
//

#include "ModelPoser.h"

void ModelPoser::randomPose(){
    if (bindPose.size()==0) {
        
        for (int i=0; i<scene->mNumMeshes; i++) {
            aiMesh* mesh=scene->mMeshes[i];
            for (int j=0; j<mesh->mNumBones; j++) {
                aiBone* bone=mesh->mBones[j];
                aiNode* node=scene->mRootNode->FindNode(bone->mName);
                bindPose[bone->mName.data]=node->mTransformation;
                cout<<"bone found: "<<bone->mName.data<<endl;
            }
        }
    }
    for (pair<string, aiMatrix4x4> bone:bindPose) {
        if(bone.first=="spineCJT"||bone.first[0]=='F'||bone.first=="hipJT"){
            continue;
        }
        aiNode* node=scene->mRootNode->FindNode(bone.first);
        aiQuaternion rot=aiQuaternion(ofRandom(-PI/4, PI/4),ofRandom(-PI/4,PI/4),ofRandom(-PI/4,PI/4));
        node->mTransformation=bone.second*aiMatrix4x4(rot.GetMatrix());
    }
    updateBones();
    updateGLResources();
}