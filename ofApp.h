#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxSyphon.h"

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
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void urlResponse(ofHttpResponse &httpResponse);
    
    void updateJson();
    void counter();
    void drawLocal();
    void drawSatelites();
    void drawOsd();
    
    
    
    bool isNewSec;
    int ellapsedSec;
    bool updateNy20;
    
    float localLon, localLat, localAlt;
    int seconds;
    string local;
    
    string apiKeyN2yo;
    
    string urlWorld;
    vector <int> satId;
    vector <string> urlN2yo;
    
    
    vector <ofxJSONElement> sateliteJason;
    
    ofImage mapaMundi;
    bool mapaLoad;
    
    vector <int> cicle;
    
    
    //mercator
    float zoom;
    float mercX(float lon) {
        lon = ofDegToRad(lon);
        float a = (256 / PI) * pow(2, zoom);
        float b = lon + PI;
        return  a * b;
    }
    float mercY(float lat) {
        lat = ofDegToRad(lat);
        float a = (256 / PI) * pow(2, zoom);
        float b = tan(PI / 4 + lat / 2);
        float c = PI - log(b);
        return a * c;
    }
    // proximidade
    float proximity;
    float checkProximity(float x1, float y1, float x2, float y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        float  distance = sqrt(dx*dx + dy * dy);
        return distance;
    }
    
    // sound
    vector <ofSoundPlayer>  soundSatelite;

    // syphon
    ofxSyphonServer mainOutputSyphonServer;
    

};
