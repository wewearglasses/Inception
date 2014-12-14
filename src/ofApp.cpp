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
    
    model.randomPose();
//    model.disableTextures();
    model.disableMaterials();
//    model.setPosition(0, -200, 0);
    model.setScale(0.12, 0.12, 0.12);
    frame.allocate(4000, 4000);
}

//--------------------------------------------------------------
void ofApp::update(){    
}

//--------------------------------------------------------------
void ofApp::draw(){

//    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
//    
////    cam.rotate(1, 0, 0, 1);
//    cam.begin();
//    ofEnableLighting();
//    ofRotateY(180);
//    ofRotateZ(180);
//    pointLight.enable();
//    model.drawFaces();
//    cam.end();
    frame.draw(0,0);
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
            frame.draw(0,0);
            ofSaveFrame();
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
