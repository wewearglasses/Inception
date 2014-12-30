#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofSetSmoothLighting(true);
    ofBackground(0, 0, 0);
    
    pointLight.setDiffuseColor( ofColor(100.f, 100.f, 100.f));
    pointLight.setSpecularColor( ofColor(255.f, 100.f, 100.f));
    pointLight.setAmbientColor(ofColor(100.f, 100.f, 100.f));
    pointLight.setPointLight();
    pointLight.setPosition(0, 0, 800);
    
    cam.setDistance(500);
    model.loadModel("man.dae");
    model.disableMaterials();
    float scale=model.getNormalizedScale();
    ofPoint center=model.getSceneCenter();
    model.setPosition(center.x*scale, center.y*scale, center.z*scale);
    //    frame.allocate(4000, 4000);
        ofSetFrameRate(25);
    
    shader.load("shaders/noise");
    mic.listDevices();
    mic.setDeviceID(4);
    bufferSize=256;
    mic.setup(this, 0, 2, 44100, bufferSize, 4);
    
    ofSeedRandom();
    
    rotationY=0;
    pastVolumes.assign(100, 0);
    
    model.randomPose();
    
    gif.setup(ofGetWidth(), ofGetHeight(), 0.08, 256);
    //    gif.setFrameDuration(1/25.0);
}

//--------------------------------------------------------------
void ofApp::update(){
    //    model.loopPose();
    //    model.dance(volume);
}

//--------------------------------------------------------------
void ofApp::draw(){
    //    frame.draw(0,0);
    ofEnableLighting();
    pointLight.enable();
    //    ofTranslate(0,ofGetHeight()/2);
    rotationY-=3;
    
    //    ofRotateY(rotationY);
    //    ofRotateZ(-rotationY/2);
    
    //        shader.begin();
    //we want to pass in some varrying values to animate our type / color
    //    shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.01/(volume+1) );
    //    shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.018/(volume+1) );
    int total=50;
    int layers=13;
    ofTranslate(ofGetWidth()/3, ofGetHeight()/3);
    ofRotateZ(-rotationY);
    for (int j=0;j<layers;j++){
        model.loopPose(j, total);
        for (int i=0; i<total; i++) {
            float n=i+1;
            float ang=PI/20*n+TWO_PI/layers*j;
            float r=(n-1)*20;
            ofPushMatrix();
            ofTranslate(r*cos(ang),r*sin(ang));
            ofRotateZ(-(rotationY*6+i*60));
            ofScale((n+1.0)/total/4,(n+1.0)/total/4,(n+1.0)/total/4);
            
            model.drawFaces();
            ofPopMatrix();
        }
    }
    
    //    model.drawFaces();
    
    //    shader.end();
    ofImage img;
    img.grabScreen(0, 0, ofGetWidth(),ofGetHeight());
    if(rotationY>-370){
//                ofSaveFrame();
        //        gif.addFrame(img);
    }else if(!isSaving){
        isSaving=true;
        //        gif.save("mess.gif");
    }
    if (isNewFrame) {
        ofSaveFrame();
    }
    
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    float curVol = 0.0;
    for(int i=0;i<bufferSize*2;i++){
        curVol+=input[i]*input[i];
    }
    curVol/=bufferSize*2;
    
    pastVolumes.erase(pastVolumes.begin());
    pastVolumes.push_back(curVol);
    float min=99999;
    float max=-99999;
    for (float v:pastVolumes) {
        min=std::min(v,min);
        max=std::max(v,max);
    }
    
    if(max==min){
        return;
    }
    
    volume=curVol/(max-min);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'r':
            model.randomPose();
            break;
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
