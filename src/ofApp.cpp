#include "ofApp.h"

bool first = false;
void ofApp::setup(){
    // initial setting
    ofSetFrameRate(60);
    ofSetBackgroundColor(ofFloatColor(bgColor.r,bgColor.g,bgColor.b,bgColor.a));
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    model.loadModel("bunny.obj", 10);
    model.setScale(0.9, 0.9, 0.9);

    // shader setings
    shader.load("shaders/flat");
    
    // camera setting
    cam.setNearClip(0);
    cam.setFarClip(1500);
    
    pos = ofVec3f(0.0, 0.0, 0.0);

    gui.setup();
    gui.add(lightDirSlider.setup("lightDir",lightDirection,glm::vec3(-1.0,-1.0,-1.0),glm::vec3(1.0,1.0,1.0)));
    
}

void ofApp::update(){
    lightDirection = lightDirSlider;
    // debug
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    if(rotating)
        time = ofGetElapsedTimef();
    
}

void ofApp::draw(){
    ofSetBackgroundColor(ofFloatColor(bgColor.r,bgColor.g,bgColor.b,bgColor.a));
    cam.begin();
    
    shader.begin();
    
    
    eyeDirection = cam.getLookAtDir();
    // model Matrix
    ofMatrix4x4 modelMatrix;
    if(mode == 0)
    modelMatrix.translate(-vboMesh.getCentroid());
    else
    modelMatrix.translate(0, 0, 0);
    modelMatrix.rotate(time*10, 0.3, 1.0, 0.0);
    icoSphere.setPosition(pos);
    icoSphere.setResolution(2);
    icoSphere.setRadius(50);
    //Box
    box.setResolution(8);
    //Cylinder
    cylinder.set(30,60);
    cylinder.setResolution(20, 13, 4);
    //Sphere
    sphere.setRadius(48);
    sphere.setResolution(32);

    // view Matrix
    ofMatrix4x4 viewMatrix;
    
    viewMatrix = ofGetCurrentViewMatrix();
    first = true;
    
    // projection Matrix
    ofMatrix4x4 projectionMatrix;
    projectionMatrix = cam.getProjectionMatrix();
    
    // mvp Matrix
    ofMatrix4x4 mvpMatrix;
    mvpMatrix = modelMatrix * viewMatrix * projectionMatrix;
    ofMatrix4x4 invMatrix;
    invMatrix = mvpMatrix.getInverse();
    shader.setUniformMatrix4f("model", modelMatrix);
    shader.setUniformMatrix4f("view", viewMatrix);
    shader.setUniformMatrix4f("projection", projectionMatrix);
    shader.setUniformMatrix4f("mvpMatrix", mvpMatrix);
    shader.setUniformMatrix4f("invMatrix", invMatrix);
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform3f("lightDirection",lightDirection);
    shader.setUniform3f("eyeDirection", eyeDirection);
    shader.setUniform4f("ambientColor", ambientColor);
    shader.setUniform4f("bgColor", bgColor);
    
    switch(mode){
        case 0:
            vboMesh = model.getMesh(0);
        break;
        case 1:
            vboMesh = sphere.getMesh();
        break;
        case 2:
            vboMesh = icoSphere.getMesh();
        break;
        case 3:
            vboMesh = cylinder.getMesh();
        break;
        case 4:
            vboMesh = box.getMesh();
        break;
        case 5:
            vboMesh = sphere.getMesh();
        break;
    };

    for(int j=0; j<vboMesh.getVertices().size(); j++){
        vboMesh.addColor(ofFloatColor(vertColor.r,vertColor.g,vertColor.b,vertColor.a));
    }
    //vboMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    vboMesh.draw();

    shader.end();
    // draw axis (x, y, z)
    ofSetLineWidth(0.1);
    ofSetColor(255, 0, 0);
    ofDrawLine(-500, 0, 0, 500, 0, 0);
    ofSetColor(0, 255, 0);
    ofDrawLine(0, -400, 0, 0, 400, 0);
    ofSetColor(0, 0, 255);
    ofDrawLine(0, 0, -400, 0, 0, 400);
    
    cam.end();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case '0':
            mode = 0;
        break;
        case '1':
            mode = 1;
        break;
        case '2':
            mode = 2;
        break;
        case '3':
            mode = 3;
        break;
        case '4':
            mode = 4;
        break;
        case '5':
            mode = 5;
        break;
        case 'a':
            shader.load("shaders/gouraud");
            bgColor = glm::vec4(64.0/255.0,64.0/255.0,64.0/255.0,1.0);
            vertColor = glm::vec4(200.0/255.0, 200.0/255.0, 200.0/255.0, 1.0);
        break;
        case 'b':
            shader.load("shaders/phong");
            bgColor = glm::vec4(64.0/255.0,64.0/255.0,64.0/255.0,1.0);
            vertColor = glm::vec4(200.0/255.0, 200.0/255.0, 200.0/255.0, 1.0);
        break;
        case 'c':
            shader.load("shaders/flat");
            bgColor = glm::vec4(64.0/255.0,64.0/255.0,64.0/255.0,1.0);
            vertColor = glm::vec4(200.0/255.0, 200.0/255.0, 200.0/255.0, 1.0);
        break;
        case 'd':
            shader.load("shaders/myShade");
            bgColor = glm::vec4(6.0/255.0,227.0/255.0,208.0/255.0,1.0);
            vertColor = glm::vec4(255.0/255.0, 48.0/255.0, 131.0/255.0, 1.0);
        break;
        case 'e':
            shader.load("shaders/myShadeFlat");
            bgColor = glm::vec4(6.0/255.0,227.0/255.0,208.0/255.0,1.0);
            vertColor = glm::vec4(255.0/255.0, 48.0/255.0, 131.0/255.0, 1.0);
        break;
        case ' ':
            if(rotating)
                rotating = false;
            else
                rotating = true;
        break;
    }
}