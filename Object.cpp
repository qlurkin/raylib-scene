#include "Object.h"
#include <raymath.h>
#include <rlgl.h>

Object::Object() {
    position = {0.0f, 0.0f, 0.0f};
    rotation = {0.0f, 0.0f, 0.0f};
    scale = {1.0f, 1.0f, 1.0f};
}

void Object::add(Object* obj) {
    children.push_back(obj);
}

void Object::render() {
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    //rlMultMatrixf(MatrixToFloatV(MatrixRotateXYZ(rotation)).v);
    rlRotatef(rotation.x*180/PI, 1.0f, 0.0f, 0.0f);
    rlRotatef(rotation.y*180/PI, 0.0f, 1.0f, 0.0f);
    rlRotatef(rotation.z*180/PI, 0.0f, 0.0f, 1.0f);
    rlScalef(scale.x, scale.y, scale.z);
    draw();
    for(Object* obj : children) {
        obj->render();
    }
    rlPopMatrix();
}

void Object::draw() {}