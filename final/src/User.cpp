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
    ofSetColor(this->c);
    ofDrawCircle(this->pos, stroke);
    if (this->is_clear) {
        ofClear(255,255,255, 255);
        is_clear = false;
        ofLog() << this->id << " cleared" << endl;
    }
    this->canvas->end();
    
    this->pos = glm::vec2(-this->stroke, -this->stroke);
    
}

void User::draw(int x, int y) {
    this->canvas->draw(x, y);
}
