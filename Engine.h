#pragma once
#include "glew/include/GL/glew.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>
#include "Camera.h"
#include "BitmapHandler.h"

struct TripleBuffering
{
    GLuint fbo;
    GLuint texture;
    GLuint depth;
};

class Engine {
private:
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
    bool Fullscreen;
    bool isRunning;
    int width;
    int height;
    bool mouseOn;
    bool keyboardOn;
    int targetFPS;
    bool depthBufferOn;
    Uint32 frameDelay;
    Uint32 frameStart;
    Uint32 frameTime;
    Uint32 lastTime;
    int projectionMode; //0-perspektywiczne 1-ortograficzne
    Camera camera;
    int shadingMode;
    static const int BufferCount=3;
    TripleBuffering buffers[BufferCount];
    int drawIndex = 0;
    int readyIndex = 1;
    int displayIndex = 2;
    int BufferingMode=2;
    GLuint myTextureID;


public:
    bool init(const std::string& windowtitle, int x, int y, int width, int height, bool Fullscreen, bool mouseOn, bool keyboardOn, int targetFPS, bool depthBufferOn, int BufferingMode);

    void mainLoop();

    void kbmEvents();
    void renderFrame();


    void clearScreen(float r, float g, float b, float a);


    void setPerspective(float fov, float nearZ, float farZ);
    void setOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);

    void setupLight();
    bool initTripleBuffer();
    void renderToBackBuffer();
    void renderToTripleBuffer();
    void rotateTripleBuffers();
    void presentTripleBuffer();
    void renderScene();


    void clean();
   

};