#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    isConnected = false;
    address = "http://127.0.0.1:3001";
    status = "not connected";
    
    socketIO.setup(address);
    
    ofAddListener(socketIO.notifyEvent, this, &ofApp::gotEvent);
    
    ofAddListener(socketIO.connectionEvent, this, &ofApp::onConnection);
//    ofSetBackgroundAuto(false);
//    ofSetBackgroundColor(255);
    
//    plane.set(640, 480);
//    plane.setPosition(0, 0, 0);
//    plane.setResolution(4, 4);
    mShader.load("shader");
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
    
    string disconnEventName = "disconnectInput";
    socketIO.bindEvent(disconnEvent, disconnEventName);
    ofAddListener(disconnEvent, this, &ofApp::onDisconnEvent);
    
    string eraserEventName = "eraserInput";
    socketIO.bindEvent(eraserEvent, eraserEventName);
    ofAddListener(eraserEvent, this, &ofApp::onEraserEvent);
    
    string rotateEventName = "rotateInput";
    socketIO.bindEvent(rotateEvent, rotateEventName);
    ofAddListener(rotateEvent, this, &ofApp::onRotateEvent);
}

//--------------------------------------------------------------
void ofApp::update(){
//
    for (auto& user : users) {
        if (!user->is_allocate) {
            user->is_allocate = true;
            user->canvas->allocate(640, 480, GL_RGBA);
            user->init_primitive();
        }
        user->update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    mCam.begin();

    glm::vec3 trans = glm::vec3(0, 0, -1);
    mShader.begin();
    for (size_t i = 1 ; i < users.size(); i++) {
        if (users[i]->is_using && users[i]->is_drawed) {
            ofPushMatrix();
            ofRotateXDeg(users[i]->rotation_vec.x);
            ofRotateYDeg(users[i]->rotation_vec.y);
            ofRotateZDeg(users[i]->rotation_vec.z);
            ofTranslate(users[i]->trans_pos);
            mShader.setUniformTexture("tex0", users[i]->canvas->getTexture(), int(i));
            users[i]->draw_primitive();
            ofPopMatrix();
        } else if(users[i]->is_freed) {
            users[i]->set_free();
        }
    }
    mShader.end();
    
    for (size_t i = 1 ; i < users.size(); i++) {
        if (users[i]->is_using && !users[i]->is_drawed) {
            users[i]->draw_wireframe();
            
        }
           
    }

    mCam.end();
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
    string id = data.getStringValue("id");
    ofLogNotice("ID", id);
    auto user = User(id);
    ofLog() << "id:" << user.type << endl;
    users.push_back(make_shared<User>(user));
}

void ofApp::onColorEvent (ofxSocketIOData& data) {
    ofColor color = ofColor(data.getIntValue("r"),
                    data.getIntValue("g"),
                    data.getIntValue("b"));
    string id = data.getStringValue("id");
    for (auto& user : users) {
        if (user->id.compare(id) == 0) {
            user->c = color;
            break;
        }
    }
}

// int*
// (*user).id ==> 
void ofApp::onPathEvent (ofxSocketIOData& data) {

    float x = data.getFloatValue("mouseX");
    float y = data.getFloatValue("mouseY");
    string id = data.getStringValue("id");
    auto p = make_shared<glm::vec2>(glm::vec2(x, y));
    
    for (auto& user : users) {
        if (*user == id) {
            if (!user->is_drawed) user->is_drawed = true;
            user->pos = *p;
        }

    }
}

void ofApp::onStrokeEvent(ofxSocketIOData& data) {
    int stroke = data.getIntValue("stroke");
    string id = data.getStringValue("id");
    
    for (auto& user : users) {
        if (user->is_using && *user == id) {
            user->stroke = stroke;
            break;
        }
    }
}

void ofApp::onClearEvent(ofxSocketIOData& data) {
    string id = data.getStringValue("id");
    for (auto& user : users) {
        if (user->is_using && *user == id) {
            user->is_clear = true;
            break;
        }
    }
    
    
}

void ofApp::onDisconnEvent(ofxSocketIOData& data) {
    string id = data.getStringValue("id");
    for (auto i = 0; i < users.size(); i++) {
        if (users[i]->is_using && *users[i] == id) {
            users[i]->is_using = false;
        }
    }
    ofLog() << users.size() << endl;
}

void ofApp::onEraserEvent(ofxSocketIOData& data) {
    string id = data.getStringValue("id");
    for (auto& user : users) {
        if (user->is_using && *user == id) {
            user->is_eraser = data.getBoolValue("eraser");
            ofLog() << user->is_eraser;
            break;
        }
    }
}

void ofApp::onRotateEvent(ofxSocketIOData &data) {
    string id = data.getStringValue("id");
    for (auto& user : users) {
        if (user->is_using && *user == id) {
            auto alpha = user->is_eraser = data.getFloatValue("alpha");
            auto beta = user->is_eraser = data.getFloatValue("beta");
            auto gamma = user->is_eraser = data.getFloatValue("gamma");
            user->rotation_vec = glm::vec3(alpha, beta, gamma);
            break;
        }
    }
}

