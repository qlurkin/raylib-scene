#include "Object.h"
#include <raymath.h>
#include <rlgl.h>

Object::Object() {
    position = {0.0f, 0.0f, 0.0f};
    rotation = {0.0f, 0.0f, 0.0f};
    size = {1.0f, 1.0f, 1.0f};
}

void Object::add(Object* obj) {
    children.push_back(obj);
}

void Object::render() {
    render(MatrixIdentity());
}

void Object::render(Matrix matModel) {
    //rlMatrixMode(RL_MODELVIEW);
    //rlPushMatrix();
    //rlTranslatef(position.x, position.y, position.z);
    //rlMultMatrixf(MatrixToFloatV(MatrixRotateXYZ(rotation)).v);
    //rlRotatef(rotation.x*180/PI, 1.0f, 0.0f, 0.0f);
    //rlRotatef(rotation.y*180/PI, 0.0f, 1.0f, 0.0f);
    //rlRotatef(rotation.z*180/PI, 0.0f, 0.0f, 1.0f);
    //rlScalef(size.x, size.y, size.z);
    matModel = MatrixMultiply(matModel, getTransform());
    draw(matModel);
    for(Object* obj : children) {
        obj->render(matModel);
    }
    //rlPopMatrix();
}

void Object::draw(Matrix matModel) {}

void Object::translate(float x, float y, float z) {
    position = Vector3Add(position, {x, y, z});
}

void Object::rotateX(float value) {
    rotation.x += value;
}

void Object::rotateY(float value) {
    rotation.y += value;
}

void Object::rotateZ(float value) {
    rotation.z += value;
}

void Object::scale(float value) {
    size = Vector3Multiply(size, {value, value, value});
}

Matrix Object::getTransform() {
    Matrix matScale = MatrixScale(size.x, size.y, size.z);
    Matrix matRotation = MatrixRotateXYZ(rotation);
    Matrix matTranslation = MatrixTranslate(position.x, position.y, position.z);

    Matrix matTransform = MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);

    return matTransform;
}

