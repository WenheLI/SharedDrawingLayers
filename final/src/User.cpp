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
    ofDrawCircle(this->pos, stroke);
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
