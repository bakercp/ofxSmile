#include "ofApp.h"


void ofApp::setup()
{
	ofBackground(30,30,30);

    vision.setupCamera(0, 320, 240);
	
	ttf.loadFont("MONACO.TTF", 48);
	ttfSmall.loadFont("MONACO.TTF", 14);

	img.allocate(320, 240, OF_IMAGE_GRAYSCALE);
	
	lastTime = ofGetElapsedTimef() - 10.0;
		
	smilePct = 0.0;
	smoothPct = 0.0;
}


void doSmily()
{

#if defined(TARGET_OSX)

	//from http://74.125.47.132/search?q=cache:OtbdKJ8MQToJ:www.realsoftware.com/listarchives/realbasic-nug/2001-11/msg01823.html+CGKeyCode+shift&cd=2&hl=en&ct=clnk&gl=us&client=safari
	//codes from - http://ritter.ist.psu.edu/projects/RUI/macosx/rui.c
	
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)49, true );		// - SPACE down
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)49, false );		// - SPACE down
	
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)56, true );		// - SHIFT down
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)41, true );		// - : key down
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)41, false );		// - : up down


	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)29, true );		// - ) key down  
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)29, false );		// - ) up down  
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)56, false );		// - SHIFT up

	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)49, true );		// - ENTER down
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)49, false );		// - ENTER down
	
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)52, true );		// - ENTER down
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)52, false );		// - ENTER up
	
		
	//also
	//- http://stackoverflow.com/questions/2379867/simulating-key-press-events-in-mac-osx
//	CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
//	CGEventRef saveCommandDown = CGEventCreateKeyboardEvent(source, (CGKeyCode)1, YES);
//	CGEventSetFlags(saveCommandDown, kCGEventFlagMaskCommand);
//	CGEventRef saveCommandUp = CGEventCreateKeyboardEvent(source, (CGKeyCode)1, NO);
//
//	CGEventPost(kCGAnnotatedSessionEventTap, saveCommandDown);
//	CGEventPost(kCGAnnotatedSessionEventTap, saveCommandUp);
//
//	CFRelease(saveCommandUp);
//	CFRelease(saveCommandDown);
//	CFRelease(source);

#endif

}


void ofApp::update()
{
    vision.update();
	
	img.setFromPixels(vision.gray.getPixels(),
                      vision.gray.width,
                      vision.gray.height,
                      OF_IMAGE_GRAYSCALE);
		
	ofxSmile::getSmile(img, smilePct);
	
	smoothPct *= 0.8;
	smoothPct += MAX(0, smilePct) * 0.2;
	
	if( ofGetElapsedTimef() - lastTime > 2.0 )
    {
		if( smoothPct > 0.50 ){
			doSmily();
			lastTime = ofGetElapsedTimef();
		}
	}
}


void ofApp::draw()
{
	ofSetColor(255);

    vision.color.draw(0,0);

    unsigned long long now = ofGetElapsedTimef();

	ofDrawBitmapString("smile        = " + ofToString(smilePct, 2), 20, 20);
	ofDrawBitmapString("smile smooth = " + ofToString(smoothPct, 2), 20, 36);
	
	if (now - lastTime < 1.0)
    {
		ofSetColor(255, 255, 255, 100);
		ttf.drawString(":)", -50 + img.width/2, 30 + img.height/2);
	}

	float alpha = ofMap(now - lastTime, 1.0, 1.3, 255, 0.0, true);
	
	ofSetColor(255, 255, 255, alpha);

	ttfSmall.drawString("-> sending smiley :)", 10, 270);

}


void ofApp::keyPressed(int key)
{
    if(key == ' ')
    {
        vision.togglePlayback();
    }

    // if you need to adjust the camera properties
    if(key == 's')
    {
        vision.camera.videoSettings();
    }
}
