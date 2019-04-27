#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxSocketIO.h"
#include "ofxSocketIOData.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    void gotEvent(std::string& name);
    void onServerEvent(ofxSocketIOData& data);
    void onColorEvent(ofxSocketIOData& data);
    void onPathEvent(ofxSocketIOData& data);
    void onStrokeEvent(ofxSocketIOData& data);
    void onClearEvent(ofxSocketIOData& data);


    
    ofxSocketIO socketIO;
    
    vector<shared_ptr<glm::vec2>> points;
    
    bool isConnected;
    void onConnection();
    void bindEvents();
    
    ofEvent<ofxSocketIOData&> serverEvent;
    ofEvent<ofxSocketIOData&> colorEvent;
    ofEvent<ofxSocketIOData&> pathEvent;
    ofEvent<ofxSocketIOData&> strokeEvent;
    ofEvent<ofxSocketIOData&> clearEvent;


    
    std::string address;
    std::string status;
    int stroke = 6;
    ofColor color = ofColor(255, 0, 0);
};