#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
   // mainOutputSyphonServer.setName("Screen Output");
    
    ofSetDataPathRoot("../Resources/data/");  // only for release
    
    ofSetVerticalSync(false);
    ofHideCursor();
    
    ofSetCircleResolution(64);
    
    isNewSec = true;
    ellapsedSec = 0;
    updateNy20 = false;
    
    localLon = -48.46;
    localLat = -27.59;
    localAlt = 0;
    
    local = "O Sitio";
    
    proximity = 300;
    
    zoom = 1.5;
    seconds = 2400;
    
    mapaLoad= false;
    
    urlWorld = "https://api.mapbox.com/styles/v1/mapbox/satellite-v9/static/0,0,1/1280x720?access_token=pk.eyJ1IjoiZmF6b2xpbiIsImEiOiJjazJkb2dnNGkwMHZ4M2RtZ3FtNDgxeTI0In0.ePDp6forjauhg6E5jcgFEg";
    
    apiKeyN2yo = "ULUYAD-342ESB-F2HPLE-47ZX";
    satId = {25544, 25338, 28654, 33591, 40019, 39444, 25994, 38771, 37849, 41183,
        40967, 27607, 41332, 39026, 40069, 20580, 27453, 40091, 39084, 40534,
        41789, 41788, 41783, 41607, 41466, 41463, 41460, 41459, 41458, 39440,
        40965, 40908, 40899, 40660, 40659, 40655, 40654, 24278, 40380, 40379,
        44530, 44419, 44427, 44426, 44420, 44412, 44406, 44394, 44392, 44352
    };
    urlN2yo.resize(satId.size());
    sateliteJason.resize(satId.size());
    
    // create url array
    for (size_t i = 0; i < satId.size(); i++){
        urlN2yo[i] = "https://www.n2yo.com/rest/v1/satellite/positions/"
        + ofToString(satId[i]) + "/"
        + ofToString(localLon) + "/"
        + ofToString(localLat) + "/"
        + ofToString(localAlt) + "/"
        + ofToString(seconds) + "/&apiKey="
        + apiKeyN2yo
        ;
    }
    
    //    for (size_t i = 0; i < satId.size(); i++){
    //        cout << urlN2yo[i] << endl;
    //    }
    
    ofRegisterURLNotification(this);
    // first url load async and world map
    ofLoadURLAsync(urlWorld, "world");
    for (size_t i = 0; i < satId.size(); i++){
        ofLoadURLAsync(urlN2yo[i], ofToString(satId[i]));
    }
    
    cicle.resize(satId.size());
    for (size_t i = 0; i < satId.size(); i++){
        cicle[i] = ofRandom(1000,1500);
    }
    // sound
    soundSatelite.resize(satId.size());
    
    ofDirectory sounds("sounds");
    sounds.listDir();

    for(int i = 0; i < sounds.size(); i++){
       // ofLogNotice(sounds.getPath(i));
        soundSatelite[i].load(sounds.getPath(i));
        soundSatelite[i].setLoop(true);
        soundSatelite[i].setVolume(0);
        soundSatelite[i].play();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    counter();
    updateJson();

 
    
}

//--------------------------------------------------------------
void ofApp::draw(){
 
    
    ofBackground(0);
    // draw the fft resutls:
     //ofSetColor(255,255,255,255);
     
//     float width = (float)(5*128) / nBandsToGet;
//     for (int i = 0;i < nBandsToGet; i++){
//         // (we use negative height here, because we want to flip them
//         // because the top corner is 0,0)
//         ofDrawRectangle(100+i*width,ofGetHeight()-100,width,-(fftSmoothed[i] * 200));
//     }
    
    if(mapaLoad){
        ofFill();
        ofSetColor(30);
        mapaMundi.draw(0, 0, ofGetWidth(), ofGetHeight());
    }

    drawOsd();
    
    ofTranslate(ofGetWidth()/2 -mercX(0), ofGetHeight()/2 - mercY(0));
    drawLocal();
    drawSatelites();
    

    
    //mainOutputSyphonServer.publishScreen();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
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
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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
void loadUrl(){
    
}
void ofApp::urlResponse(ofHttpResponse &httpResponse) {
    if (httpResponse.status == 200 && httpResponse.request.name == "world") {
        mapaMundi.load(httpResponse);
        mapaLoad = true;
    }
    for (size_t i = 0; i < satId.size(); i++){
        if (httpResponse.status == 200 && httpResponse.request.name == ofToString(satId[i])) {
            sateliteJason[i] = (httpResponse.data.getText());
            //cout << sateliteJason[i] << endl;
//            cout << sateliteJason[i]["info"]["transactionscount"].asString() << endl;
//            cout << sateliteJason[i]["info"]["satname"].asString() << endl;
//            cout << sateliteJason[i]["info"]["satid"].asString() << endl;
//            cout << sateliteJason[i]["positions"][1]["timestamp"].asString() << endl;
            
        }
    }
}
void ofApp::updateJson(){
    if (updateNy20){
        //cout << "ok"<< endl;
        for (size_t i = 0; i < satId.size(); i++){
            ofLoadURLAsync(urlN2yo[i], ofToString(satId[i]));
        }
        updateNy20 = false;
    }
    
}

void ofApp::counter(){
  
    if (ofGetSeconds() % 2 == 1  && isNewSec){
        ellapsedSec++;

//        cout << ellapsedSec << endl;
        isNewSec = false;
    }
    if (ofGetSeconds() % 2 == 0  && !isNewSec){
        ellapsedSec++;

//        cout << ellapsedSec << endl;
        isNewSec = true;
    }
    if (ellapsedSec == seconds){
        updateNy20 = true;
        ellapsedSec = 0;
    }
}

void ofApp::drawOsd(){
    ofSetColor(255);
//    std::stringstream scr;
//    for (size_t i = 0; i < satId.size(); i++){
//        scr << sateliteJason[i]["info"]["satname"].asString() << std::endl;
//    }
//    ofDrawBitmapString(scr.str(), 10, 14);
    std::stringstream fps;
    fps << "FPS  : " << ofGetFrameRate() << std::endl;
    ofDrawBitmapString(fps.str(),ofGetWidth()-120, ofGetHeight()-10);

    
    std::stringstream date;
    date << ofGetTimestampString()<< std::endl;
    ofDrawBitmapString(date.str(),20, 24);
    ofNoFill();
    
    std::stringstream invisivel;
    invisivel<<"O invisivel das coisas | Caio Fazolin | 2019 "<< std::endl;
    ofDrawBitmapString(invisivel.str(),20, ofGetHeight()-10);
    ofNoFill();

    ofNoFill();
    ofDrawRectangle(10, 10, ofGetWidth()-10, ofGetHeight()-10);
    
}

void ofApp::drawLocal(){
    
    float x = mercX(localLon);
    float y = mercY(localLat);
    
    ofFill();
    ofSetColor(255);
    ofSetColor(255,10);
    ofDrawCircle(x, y, proximity);
    ofSetColor(255);
    ofDrawCircle(x, y, 3);
    ofNoFill();
    for (int i = 0; i < proximity; i = i + 20) {
        ofSetColor(255,127 - ofMap(i,proximity,0,100,0));
        ofDrawCircle(x, y, i);
    }
    
    ofFill();
    ofSetColor(255);
    std::stringstream localStr;
    localStr <<  local << std::endl;
    ofDrawBitmapString(localStr.str(),mercX(localLon)+10, mercY(localLat));
    
}

void ofApp::drawSatelites(){
    
        for (size_t i = 0; i < satId.size(); i++){
            std::stringstream sat;
            
             if (!sateliteJason[i]["info"]["satname"].empty()){
            //sat << "ID        = " << sateliteJason[i]["info"]["satid"].asString() << std::endl;
            sat << "NAME      = " << sateliteJason[i]["info"]["satname"].asString() << std::endl;
            //sat << "AZIMUTH   = " << sateliteJason[i]["positions"][1]["azimuth"].asFloat() << std::endl;
            //sat << "ELEVATION = " << sateliteJason[i]["positions"][ellapsedSec]["elevation"].asFloat() << std::endl;
            sat << "ALTITUDE  = " << sateliteJason[i]["positions"][ellapsedSec]["sataltitude"].asFloat() << std::endl;
            sat << "LATITUDE  = " << sateliteJason[i]["positions"][ellapsedSec]["satlatitude"].asFloat() << std::endl;
            sat << "LONGITUDE = " << sateliteJason[i]["positions"][ellapsedSec]["satlongitude"].asFloat() << std::endl;
            
            float x = mercX(ofToFloat(sateliteJason[i]["positions"][ellapsedSec]["satlongitude"].asString()));
            float y = mercY(ofToFloat(sateliteJason[i]["positions"][ellapsedSec]["satlatitude"].asString()));
            float xL = mercX(localLon);
            float yL = mercY(localLat);
            
            float pulse = ofGetElapsedTimeMillis() % cicle[i];
            
            for (int j = 0; j <seconds; j=j+60){
                float xP = mercX(ofToFloat(sateliteJason[i]["positions"][j]["satlongitude"].asString()));
                float yP= mercY(ofToFloat(sateliteJason[i]["positions"][j]["satlatitude"].asString()));
                ofSetColor(255,ofMap(j,0,seconds,127,255));
                ofFill();
                ofDrawCircle(xP, yP, 1);
            
            }
            int xOffset = 10;
            int yOffset = -50;
            int xOffsetLine = 200;
            if (x < xL){
                xOffset = -200;
                xOffsetLine = -200;
            }
            //        if (y < ofGetHeight()/2){
            //            yOffset = -50;
            //        }
            
            ofFill();
            ofSetColor(255);
            ofDrawCircle(x, y, 3);
            
            if (checkProximity(x, y, xL, yL) < proximity){
                ofSetColor(255);
                ofDrawLine(xL, yL, x, y);
                soundSatelite[i].setVolume(1 -(checkProximity(x, y, xL, yL) /proximity));
                soundSatelite[i].setSpeed(ofMap((checkProximity(x, y, xL, yL) /proximity),1,0,.2,1.2));
                soundSatelite[i].setPan(ofMap(x,0,ofGetWidth(),0,1));
            }else{
                ofSetColor(255,100);
            }
            
            ofDrawBitmapString(sat.str(), x +xOffset, y +yOffset);
            ofDrawLine(x, y, x + xOffsetLine, y );
            
            
            ofNoFill();
            ofSetColor(255,255 - pulse);
            ofDrawCircle(x, y, 10 + pulse / 50);
            
        }
    }
}



