//
//  User.hpp
//  final
//
//  Created by wenhe on 2019/4/29.
//

#ifndef User_hpp
#define User_hpp

#include <ofMain.h>

class User {
public:
    string id;
    shared_ptr<ofFbo> canvas;
    ofColor c;
    glm::vec2 pos;
    int stroke;
    bool is_clear;
    bool is_eraser;
    bool is_allocate;
    bool is_using;
    bool is_freed;
    
    User(string _id);
    
    void set_color(int r, int g, int b);
    void set_color(ofColor c);
    void set_free();
    void update();
    void draw(int x, int y);
    
    inline bool operator == (const string& _id){
        return _id.compare(this->id) == 0;
    }
};

#endif /* User_hpp */
