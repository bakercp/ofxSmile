#pragma once

#include "ofMain.h"
#include "ofxSmile.h"

class ofApp: public ofBaseApp
{
public:
    
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased (int key);

    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased();
    
    ofImage img;
    computerVision vision;
    
    float smilePct;
    float lastTime;
    float smoothPct;
    
    ofTrueTypeFont ttf;
    ofTrueTypeFont ttfSmall;
		
};
