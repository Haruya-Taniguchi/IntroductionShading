#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
    public:
        void setup();
        void update();
        void draw();
        void keyPressed(int key);
    
    ofEasyCam cam;
    ofShader shader;
    ofVboMesh vboMesh;
    ofIcoSpherePrimitive icoSphere;
    ofSpherePrimitive sphere;
    ofBoxPrimitive box = ofBoxPrimitive(60, 60, 60);
    ofCylinderPrimitive cylinder;
    ofxAssimpModelLoader model;
    
    int mode = 0;
    ofVec3f pos;
    float time;
    bool rotating = false;

    glm::vec3 lightDirection = glm::vec3(1.0,1.0,-0.01);
    glm::vec4 ambientColor = glm::vec4(0.1,0.1,0.1,1.0);
    glm::vec3 eyeDirection = glm::vec3(0.0, 0.0, 10.0);
    //glm::vec4 bgColor = glm::vec4(6.0/255.0,227.0/255.0,208.0/255.0,1.0);
    //glm::vec4 vertColor = glm::vec4(255.0/255.0, 48.0/255.0, 131.0/255.0, 1.0);
    glm::vec4 bgColor = glm::vec4(64.0/255.0,64.0/255.0,64.0/255.0,1.0);
    glm::vec4 vertColor = glm::vec4(200.0/255.0, 200.0/255.0, 200.0/255.0, 1.0);

    ofxPanel gui;
    ofxVec3Slider lightDirSlider;
};
