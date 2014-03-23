#pragma once


#include "ofMain.h"
#include "ofxSmile.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    ofImage img;
    SimpleCV vision;
    
    float smilePct;
    float lastTime;
    float smoothPct;
    
    ofTrueTypeFont ttf;
    ofTrueTypeFont ttfSmall;
		
};
