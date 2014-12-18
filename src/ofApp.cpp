#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofSetSmoothLighting(true);
    ofBackground(0, 0, 0);
    
    pointLight.setDiffuseColor( ofColor(100.f, 100.f, 100.f));
    pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    pointLight.setAmbientColor(ofColor(100.f, 100.f, 100.f));
    pointLight.setPointLight();
    pointLight.setPosition(0, 0, 800);

    cam.setDistance(500);
    model.loadModel("man.dae");
    
    model.disableMaterials();
    model.setPosition(0, 200, 0);
//    model.setScale(0.7,0.7,0.7);
    frame.allocate(4000, 4000);
    ofSetFrameRate(25);
}

//--------------------------------------------------------------
void ofApp::update(){
    model.loopPose();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    frame.draw(0,0);
    ofEnableLighting();
    pointLight.enable();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    ofRotateX(ofGetFrameNum()*360/25/6);
    ofRotateY(ofGetFrameNum()*360/25/6);
    model.drawFaces();
    ofSaveFrame();
    
    if(ofGetFrameNum()>=25*6){
        ofExit();
    }
    if (isNewFrame) {
        ofSaveFrame();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            model.randomPose();
            frame.begin();
            ofClear(0, 0, 0);
            ofEnableLighting();
            pointLight.enable();
            float ang=ofRandom(TWO_PI);
            for (int i=0; i<800; i++) {
                float r=i*10/log(i)+80;
                ang+=5;
                ofPushMatrix();
                ofTranslate(ofGetWidth()/3+r*cosf(ang), ofGetHeight()/3+r*sin(ang));
//                ofRotateY(180);
                ofRotateZ(-90-ang*RAD_TO_DEG);
                model.randomPose();
                model.drawFaces();
                ofPopMatrix();
            }
            frame.end();
            isNewFrame=true;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
