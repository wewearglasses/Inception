//
//  ModelPoser.cpp
//  Inception
//
//  Created by Shang Liang on 12/8/14.
//
//

#include "ModelPoser.h"

void ModelPoser::randomPose(){
    getBindPose();
    for (pair<string, aiMatrix4x4> bone:bindPose) {
        aiNode* node=scene->mRootNode->FindNode(bone.first);
        aiQuaternion rot=aiQuaternion(ofRandom(-PI/4, PI/4),ofRandom(-PI/4,PI/4),ofRandom(-PI/4,PI/4));
        if(bone.first=="head"){
            rot=aiQuaternion(0,0,0);
        }
        node->mTransformation=bone.second*aiMatrix4x4(rot.GetMatrix());
    }
    updateBones();
    updateGLResources();
}

void ModelPoser::bigLoopPose(){
    
}

void ModelPoser::loopPose(){
    getBindPose();
    if (originRotations.size()==0) {
        p=0;
        for (pair<string, aiMatrix4x4> bone:bindPose) {
            aiNode* node=scene->mRootNode->FindNode(bone.first);
            
            originRotations[bone.first]=aiVector3D(ofRandom(-PI, PI),ofRandom(-PI,PI),ofRandom(-PI,PI));
            aiQuaternion rot=aiQuaternion(originRotations[bone.first].x,originRotations[bone.first].y,originRotations[bone.first].z);
            node->mTransformation=bone.second*aiMatrix4x4(rot.GetMatrix());
            phase1Rotations[bone.first]=(ofRandom(-PI, PI),ofRandom(-PI,PI),ofRandom(-PI,PI));
            phase2Rotations[bone.first]=(ofRandom(-PI, PI),ofRandom(-PI,PI),ofRandom(-PI,PI));
            phase3Rotations[bone.first]=(ofRandom(-PI, PI),ofRandom(-PI,PI),ofRandom(-PI,PI));
            phase4Rotations[bone.first]=(ofRandom(-PI, PI),ofRandom(-PI,PI),ofRandom(-PI,PI));
            phase5Rotations[bone.first]=(ofRandom(-PI, PI),ofRandom(-PI,PI),ofRandom(-PI,PI));
        }
    }else{
        p+=1.0/25;
        if (p>=6) {
            p=0;
        }
        for (pair<string, aiMatrix4x4> bone:bindPose) {
            aiNode* node=scene->mRootNode->FindNode(bone.first);
            aiVector3D orot;
            aiVector3D trot;
            if(p>5){
                orot=phase5Rotations[bone.first];
                trot=originRotations[bone.first];
            }
            else if(p>4){
                orot=phase4Rotations[bone.first];
                trot=phase5Rotations[bone.first];
            }
            else if(p>3){
                orot=phase3Rotations[bone.first];
                trot=phase4Rotations[bone.first];
            }
            else if(p>2){
                orot=phase2Rotations[bone.first];
                trot=phase3Rotations[bone.first];
            }else if(p>1){
                orot=phase1Rotations[bone.first];
                trot=phase2Rotations[bone.first];
            }else{
                orot=originRotations[bone.first];
                trot=phase1Rotations[bone.first];
            }
            aiVector3D rot=orot+(trot-orot)*(p-int(p));
            node->mTransformation=bone.second*aiMatrix4x4(aiQuaternion(rot.x,rot.y,rot.z).GetMatrix());
        }
        
    }
    
    updateBones();
    updateGLResources();
}

void ModelPoser::dance(float volume){
    if(!scene){
        return;
    }
    getBindPose();
    
    if(currRotations.size()==0){
        for (pair<string, aiMatrix4x4> bone:bindPose) {
            currRotations[bone.first]=aiVector3D();
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
            v=currRotations[bone.first]*0.95;
        }
        
        currRotations[bone.first]=v;
        aiQuaternion rot=aiQuaternion(currRotations[bone.first].x,currRotations[bone.first].y,currRotations[bone.first].z);
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
        for (int j=0; j<mesh->mNumBones; j++) {
            aiBone* bone=mesh->mBones[j];
            if(string(bone->mName.data)=="spine"){
                continue;
            }
            aiNode* node=scene->mRootNode->FindNode(bone->mName);
            bindPose[bone->mName.data]=node->mTransformation;
            cout<<"bone found: "<<bone->mName.data<<endl;
        }
    }
}