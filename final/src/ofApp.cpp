#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    isConnected = false;
    address = "http://127.0.0.1:3001";
    status = "not connected";
    
    socketIO.setup(address);
    /*
     * You can also pass a query parameter at connection if needed.
     */
    // std::map<std::string,std::string> query;
    // query["token"] = "hello";
    // socketIO.setup(address, query);
    
    ofAddListener(socketIO.notifyEvent, this, &ofApp::gotEvent);
    
    ofAddListener(socketIO.connectionEvent, this, &ofApp::onConnection);
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(255);
}

void ofApp::onConnection () {
    isConnected = true;
    bindEvents();
}

void ofApp::bindEvents () {
    std::string serverEventName = "news";
    socketIO.bindEvent(serverEvent, serverEventName);
    ofAddListener(serverEvent, this, &ofApp::onServerEvent);
    
    std::string colorEventName = "colorInput";
    socketIO.bindEvent(colorEvent, colorEventName);
    ofAddListener(colorEvent, this, &ofApp::onColorEvent);
    
    std::string pathEventName = "pathInput";
    socketIO.bindEvent(pathEvent, pathEventName);
    ofAddListener(pathEvent, this, &ofApp::onPathEvent);
    
    std::string strokeEventName = "strokeInput";
    socketIO.bindEvent(strokeEvent, strokeEventName);
    ofAddListener(strokeEvent, this, &ofApp::onStrokeEvent);
    
    std::string clearEventName = "clearInput";
    socketIO.bindEvent(clearEvent, clearEventName);
    ofAddListener(clearEvent, this, &ofApp::onClearEvent);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofNoFill();
//    ofBeginShape();
//    for (auto p : points) {
//        ofVertex(*p);
//    }
//    ofEndShape(false);
    if (points.size() > 1){
        ofPushStyle();
        ofFill();
        
        ofSetColor(color);
        ofDrawCircle(*points[points.size() - 1], stroke);
        ofPopStyle();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::gotEvent(string& name) {
    status = name;
}

//--------------------------------------------------------------
void ofApp::onServerEvent (ofxSocketIOData& data) {
    ofLogNotice("ofxSocketIO", data.getStringValue("hello"));
}

void ofApp::onColorEvent (ofxSocketIOData& data) {
    color = ofColor(data.getIntValue("r"),
                    data.getIntValue("g"),
                    data.getIntValue("b"));
}

void ofApp::onPathEvent (ofxSocketIOData& data) {

    float x = data.getFloatValue("mouseX");
    float y = data.getFloatValue("mouseY");
    
    auto p = make_shared<glm::vec2>(glm::vec2(x, y));
    points.push_back(p);

}

void ofApp::onStrokeEvent(ofxSocketIOData& data) {
    stroke = data.getIntValue("stroke");
}

void ofApp::onClearEvent(ofxSocketIOData& data) {
    ofLog() << "clear" << endl;
}


