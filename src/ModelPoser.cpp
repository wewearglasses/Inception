//
//  ModelPoser.cpp
//  Inception
//
//  Created by Shang Liang on 12/8/14.
//
//

#include "ModelPoser.h"

void ModelPoser::setPose(Pose p){
    for (pair<string, aiVector3D> bone:p) {
        aiNode* node=scene->mRootNode->FindNode(bone.first);
        aiQuaternion rot=aiQuaternion(bone.second.x,bone.second.y,bone.second.z);
        node->mTransformation=bindPose[bone.first]*aiMatrix4x4(rot.GetMatrix());
    }
    updateBones();
    updateGLResources();
}

Pose ModelPoser::randomPose(){
    getBindPose();
    Pose p;
    for (pair<string, aiMatrix4x4> bone:bindPose) {
        aiNode* node=scene->mRootNode->FindNode(bone.first);
        p[bone.first]=aiVector3D(ofRandom(-PI/4, PI/4),ofRandom(-PI/4, PI/4),ofRandom(-PI/4, PI/4));
    }
    return p;
}

void ModelPoser::loopPose(int index, int total){
    getBindPose();
    if (loopPoses.size()==0) {
        for (int i=0; i<total; i++) {
            loopPoses.push_back(randomPose());
        }
    }
    setPose(loopPoses[index]);
}


void ModelPoser::dance(float volume){
    if(!scene){
        return;
    }
    getBindPose();
    
    if(currDancePose.size()==0){
        for (pair<string, aiMatrix4x4> bone:bindPose) {
            currDancePose[bone.first]=aiVector3D();
        }
    }
    
    int counter=0;
    for (pair<string, aiMatrix4x4> bone:bindPose) {
        aiNode* node=scene->mRootNode->FindNode(bone.first);
        aiVector3D v;
        if(volume>0.5){
            float seed=(ofGetFrameNum()+counter*100)*0.01;
            float dx=ofNoise(seed, 0, 0)*PI/4-PI/8;
            float dy=ofNoise(0,seed, 0)*PI/4-PI/8;
            float dz=ofNoise(0,0,seed)*PI/4-PI/8;
            v=aiVector3D(dx,dy,dz)*volume*5;
        }else{
            v=currDancePose[bone.first]*0.95;
        }
        
        currDancePose[bone.first]=v;
        aiQuaternion rot=aiQuaternion(currDancePose[bone.first].x,currDancePose[bone.first].y,currDancePose[bone.first].z);
        node->mTransformation=bone.second*aiMatrix4x4(rot.GetMatrix());
        counter++;
    }
    updateBones();
    updateGLResources();
    
}

void ModelPoser::getBindPose(){
    if (bindPose.size()>0) {
        return;
    }
    
    for (int i=0; i<scene->mNumMeshes; i++) {
        
        aiMesh* mesh=scene->mMeshes[i];
        cout<<"Bones: ";
        for (int j=0; j<mesh->mNumBones; j++) {
            aiBone* bone=mesh->mBones[j];
            cout<<bone->mName.data<<"\t";
            if(excludeBone(string(bone->mName.data))){
                continue;
            }
            aiNode* node=scene->mRootNode->FindNode(bone->mName);
            bindPose[bone->mName.data]=node->mTransformation;
        }
        cout<<endl;
    }
}

bool ModelPoser::excludeBone(string boneName){
    string exludingBones[]={"head","jaw"};
    for(string b:exludingBones){
        if(b==boneName){
            return true;
        }
    }
    return false;
}
