#pragma once

#include "ofMain.h"
#include "ModelPoser.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void audioIn(float * input, int bufferSize, int nChannels); 
		
    ModelPoser model;
    ofEasyCam cam;
    ofLight pointLight;
    ofFbo frame;
    bool isNewFrame;
    ofSoundStream mic;
    ofShader shader;
    int bufferSize;
    float volume;
    float rotationY;
    vector<float> pastVolumes;
};
