#pragma once
#include <vector>
#include <raylib.h>

using namespace std;

class Object {
    private:
        vector<Object*> children;

    public:
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;
        Object();
        void add(Object* obj);
        void render();
        virtual void draw();
};