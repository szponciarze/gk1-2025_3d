#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>


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


public:
    bool init(const std::string& windowtitle, int x, int y, int width, int height, bool Fullscreen, bool mouseOn, bool keyboardOn, int targetFPS, bool depthBufferOn);

    void mainLoop();

    void kbmEvents();
    void renderFrame();


    void clearScreen(float r, float g, float b, float a);


    void setPerspective(float fov, float nearZ, float farZ);
    void setOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);


    void clean();
};