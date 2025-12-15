#include "Engine.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm/glm.hpp"
#include "glm/glm/gtx/transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "Primitive.h"
#include "Point.h"
#include "Line.h"
#include "Polylines.h"
#include "Triangle.h"
#include "TriangleStrip.h"
#include "TriangleFan.h"
#include "Quad.h"
#include "Cube.h"



bool Engine::init(const std::string& windowtitle, int x, int y, int w, int h, bool Fullscreen, bool mouseOn, bool keyboardOn, int targetFPS, bool depthBufferOn)
{
    this->width = w;
    this->height = h;
    this->Fullscreen = Fullscreen;
    this->mouseOn = mouseOn;
    this->keyboardOn = keyboardOn;
    this->targetFPS = targetFPS;
    this->frameDelay = 1000 / targetFPS;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
        std::cerr << "SDL Init error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    Uint32 flags = SDL_WINDOW_OPENGL;
    if (Fullscreen) flags |= SDL_WINDOW_FULLSCREEN;

    window = SDL_CreateWindow(windowtitle.c_str(), x, y, w, h, flags);
    if (!window) {
        std::cerr << "SDL Window error: " << SDL_GetError() << std::endl;
        return false;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "SDL_GL Context error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetSwapInterval(1); // vsync

    if (depthBufferOn) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }

    glClearColor(0.1f, 0.15f, 0.2f, 1.0f);

    isRunning = true;
    return true;

}

void Engine::mainLoop() {
    lastTime = SDL_GetTicks();
    while (isRunning) {
        frameStart = SDL_GetTicks();
        Uint32 currentTime = SDL_GetTicks();
        float dt = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        kbmEvents();
        renderFrame();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

}

void Engine::kbmEvents() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            isRunning = false;

        if (keyboardOn && e.type == SDL_KEYDOWN) {

            std::cout << "Nacisnieto klawisz: " << SDL_GetKeyName(e.key.keysym.sym) << std::endl;

            switch (e.key.keysym.sym) {
            case SDLK_1:
                projectionMode = 0;
                std::cout << "Rzutowanie perspektywiczne\n";
                break;

            case SDLK_2:
                projectionMode = 1;
                std::cout << "Rzutowanie ortograficzne\n";
                break;

            case SDLK_c:
                clearScreen(1.0f, 0.0f, 0.0f, 1.0f);
                break;
            }

        }

        if (mouseOn && e.type == SDL_MOUSEBUTTONDOWN) {
            std::cout << "Nacisnieto klawisz myszy w: (" << e.button.x << "," << e.button.y << ")" << std::endl;
        }
    }
}

void Engine::renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (projectionMode == 0)
        setPerspective(70.0f, 0.1f, 1000.0f);
    else
        setOrtho(-10, 10, -10, 10, -100, 100);

    //rysowanie
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -10);

    // Punkt
    glPushMatrix();
    glTranslatef(-6, 4, 0);
    Point p(Vertex({ 0,0,0 }, { 1,0,0 }));
    p.draw();
    glPopMatrix();

    // Linia 
    glPushMatrix();
    glTranslatef(5, 4, 0);
    Line l(Vertex({ -2,1,0 }, { 1,0,0 }), Vertex({ 2,0,0 }, { 1,0,0 }));
    l.draw();
    glPopMatrix();

    // Krzywa linia
    glPushMatrix();
    glTranslatef(-6, -4, 0);
    std::vector<Vertex> polyVerts = {
        Vertex({-2,-1,0},{0,1,0}),
        Vertex({0,2,0},{0,1,0}),
        Vertex({2,-1,0},{0,1,0})
    };
    Polylines pl(polyVerts);
    pl.draw();
    glPopMatrix();

    // Trójk¹t
    glPushMatrix();
    glTranslatef(-3, 4, 0);
    Triangle t(Vertex({ -1,-1,0 }, { 1,0,0 }), Vertex({ 1,2,0 }, { 1,0,0 }), Vertex({ 1,-1,0 }, { 1,0,0 }));
    t.draw();
    glPopMatrix();

    // Pasek trójk¹tów
    glPushMatrix();
    glTranslatef(2, 2, 0);
    std::vector<Vertex> stripVerts = {
        Vertex({-1,-1,0},{0,1,0}),
        Vertex({-0.5,2,0},{0,1,0}),
        Vertex({0,-1,0},{0,1,0}),
        Vertex({0.5,2,0},{0,1,0})
    };
    TriangleStrip ts(stripVerts);
    ts.draw();
    glPopMatrix();

    // Wachlarz trójk¹tów
    glPushMatrix();
    glTranslatef(6, -4, 0);
    std::vector<Vertex> fanVerts = {
        Vertex({0,0,0},{1,0,0}),
        Vertex({-1,0,0},{1,0,0}),
        Vertex({1,1,0},{1,0,0}),
        Vertex({1,-1,0},{1,0,0}),
        Vertex({-1,-1,0},{1,0,0})
    };
    TriangleFan tf(fanVerts);
    tf.draw();
    glPopMatrix();

    // Kwadrat
    glPushMatrix();
    glTranslatef(-3, 0, 0);
    Quad q(Vertex({ -1,-1,0 }, { 0,0,1 }), Vertex({ -1,1,0 }, { 0,0,1 }), Vertex({ 1,1,0 }, { 0,0,1 }), Vertex({ 1,-1,0 }, { 0,0,1 }));
    q.draw();
    glPopMatrix();

    // Kostka
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glRotatef(SDL_GetTicks() * 0.05f, 2, 1, 0);
    Cube cube(2.0f);
    cube.draw();
    glPopMatrix();

    SDL_GL_SwapWindow(window);
}


void Engine::setPerspective(float fov, float nearZ, float farZ) {
    glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)width / (float)height, 0.1f, 1000.0f);


    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));
}

void Engine::setOrtho(float left, float right, float bottom, float top, float nearZ, float farZ) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, nearZ, farZ);
}

void Engine::clearScreen(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Engine::clean() {
    if (glContext) {
        SDL_GL_DeleteContext(glContext);
        glContext = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}
