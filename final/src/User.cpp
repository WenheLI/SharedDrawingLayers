//
//  User.cpp
//  final
//
//  Created by wenhe on 2019/4/29.
//

#include "User.hpp"

User::User(string _id) {
    this->id = _id;
    this->canvas = make_shared<ofFbo>(ofFbo());
    this->is_clear = false;
    this->c = ofColor(255, 0, 0);
    this->stroke = 6;
    this->pos = glm::vec2(-6,-6);
    
    this->is_clear = false;
    this->is_eraser = false;
    this->is_allocate = false;
    this->is_using = true;
    this->is_freed = false;
    
    float win_height = ofGetHeight();
    float win_width = ofGetWidth();
    
    this->trans_pos = glm::vec3(ofRandom(-win_width * .25, win_width*.25), ofRandom(-win_height * .25, win_height * .25), ofRandom(-50, 20));
    
    this->type = int(ofRandom(0, 5));
}

void User::set_color(int r, int g, int b) {
    this->c = ofColor(r, g, b);
}

void User::set_color(ofColor c) {
    this->c = c;
}

void User::update() {
    this->canvas->begin();
    ofFill();
    ofSetColor(this->is_eraser ? ofColor(255, 255, 255) : this->c);
    ofDrawCircle(this->pos, stroke*1.1);
    if (this->is_clear) {
        ofClear(0,0,0);
        is_clear = false;
        ofLog() << this->id << " cleared" << endl;
    }
    this->canvas->end();
    
    this->pos = glm::vec2(-this->stroke, -this->stroke);
    
}

void User::set_free() {
    this->canvas->begin();
        ofClear(0,0,0);
    this->canvas->end();
    this->is_freed = true;
}

void User::draw(int x, int y) {
    this->canvas->draw(x, y);
}

void User::init_primitive() {
    switch(this->type) {
        case 0: {
            this->cylinder.set(ofRandom(80, 150), ofRandom(80, 150));
            this->cylinder.mapTexCoordsFromTexture(this->canvas->getTexture());
            break;
        }
        case 1: {
            this->sphere.set(ofRandom(60,150), 32);
            this->sphere.mapTexCoordsFromTexture(this->canvas->getTexture());
            break;
        }
        case 2: {
            this->box.set(ofRandom(80, 200), ofRandom(80, 100), ofRandom(80, 150));
            this->box.mapTexCoordsFromTexture(this->canvas->getTexture());
            break;
        }
        case 3: {
            this->cone.set(ofRandom(60, 150), ofRandom(60, 150));
            this->cone.mapTexCoordsFromTexture(this->canvas->getTexture());
            break;
        }
        case 4: {
            this->plane.set(ofRandom(100, 200), ofRandom(100, 200));
            this->plane.mapTexCoordsFromTexture(this->canvas->getTexture());
            break;
        }
        default: break;
    }
}

void User::draw_primitive() {
    switch(this->type) {
        case 0: {
            this->cylinder.draw(ofPolyRenderMode::OF_MESH_FILL);
            break;
        }
        case 1: {
            this->sphere.draw(ofPolyRenderMode::OF_MESH_FILL);
            break;
        }
        case 2: {
            this->box.draw(ofPolyRenderMode::OF_MESH_FILL);
            break;
        }
        case 3: {
            this->cone.draw(ofPolyRenderMode::OF_MESH_FILL);
            break;
        }
        case 4: {
            this->plane.draw(ofPolyRenderMode::OF_MESH_FILL);
            break;
        }
        default: break;
    }
}
