/**
 * @file Engine.cpp
 * @brief Implementacja g³ównej klasy silnika 3D.
 *
 * Plik zawiera implementacjê inicjalizacji silnika,
 * obs³ugi pêtli g³ównej, renderowania sceny 3D,
 * oœwietlenia, buforowania (double/triple buffering)
 * oraz zarz¹dzania kamer¹ i projekcj¹.
 */


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
#include "BitmapHandler.h"
#include "TexturedCube.h"

 /**
  * @brief Inicjalizuje silnik 3D i kontekst OpenGL.
  *
  * Tworzy okno SDL, kontekst OpenGL, inicjalizuje GLEW,
  * ustawia tryb buforowania (double lub triple),
  * konfiguruje oœwietlenie, test g³êbi oraz ³aduje tekstury.
  *
  * @param windowtitle Tytu³ okna
  * @param x Pozycja okna X
  * @param y Pozycja okna Y
  * @param w Szerokoœæ okna
  * @param h Wysokoœæ okna
  * @param Fullscreen Tryb pe³noekranowy
  * @param mouseOn Obs³uga myszy
  * @param keyboardOn Obs³uga klawiatury
  * @param targetFPS Docelowa liczba FPS
  * @param depthBufferOn W³¹czenie bufora g³êbi
  * @param BufferingMode Tryb buforowania (2 – double, 3 – triple)
  * @return true jeœli inicjalizacja zakoñczy³a siê sukcesem
  */
bool Engine::init(const std::string& windowtitle, int x, int y, int w, int h, bool Fullscreen, bool mouseOn, bool keyboardOn, int targetFPS, bool depthBufferOn, int BufferingMode)
{
    this->width = w;
    this->height = h;
    this->Fullscreen = Fullscreen;
    this->mouseOn = mouseOn;
    this->keyboardOn = keyboardOn;
    this->targetFPS = targetFPS;
    this->frameDelay = 1000 / targetFPS;
    this->BufferingMode = (BufferingMode < 2) ? 2 : 3;

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

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW init failed\n";
        return false;
    }

    if (BufferingMode == 3)
    {
        if (!initTripleBuffer())
            return false;
    }

    SDL_GL_SetSwapInterval(1);

    if (depthBufferOn) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }

    glClearColor(0.1f, 0.15f, 0.2f, 1.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    shadingMode = 1;

    myTextureID = BitmapHandler::loadTexture("tekstura.jpg");

    isRunning = true;
    return true;

}

/**
 * @brief G³ówna pêtla programu.
 *
 * Obs³uguje zdarzenia, renderowanie
 * oraz synchronizacjê FPS.
 */
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

/**
 * @brief Obs³uguje zdarzenia klawiatury i myszy.
 *
 * Umo¿liwia zmianê rzutowania, trybu cieniowania,
 * poruszanie kamer¹ oraz obs³ugê zdarzeñ zamkniêcia okna.
 */
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
            case SDLK_UP:
                camera.move({ 0,0.5f,0 });
                    break;
            case SDLK_LEFT:
                camera.move({ -0.5f,0,0 });
                break;
            case SDLK_DOWN:
                camera.move({ 0,-0.5f,0 });
                break;
            case SDLK_RIGHT:
                camera.move({ 0.5f,0,0 });
                break;

            case SDLK_f:
                shadingMode = 0;
                glShadeModel(GL_FLAT);
                std::cout << "Cieniowanie: FLAT\n";
                break;

            case SDLK_g:
                shadingMode = 1;
                glShadeModel(GL_SMOOTH);
                std::cout << "Cieniowanie: SMOOTH (Gouraud)\n";
                break;
            }


        }

        if (mouseOn && e.type == SDL_MOUSEBUTTONDOWN) {
            std::cout << "Nacisnieto klawisz myszy w: (" << e.button.x << "," << e.button.y << ")" << std::endl;
        }
    }
}

/**
 * @brief Renderuje pojedyncz¹ klatkê.
 *
 * W zale¿noœci od wybranego trybu buforowania
 * renderuje scenê do bufora tylnego lub do
 * potrójnego bufora (FBO).
 */
void Engine::renderFrame()
{

    if (BufferingMode == 3)
    {
        renderToTripleBuffer();
    }
    else
    {
        renderToBackBuffer();
    }


}

/**
 * @brief Renderuje scenê bezpoœrednio do tylnego bufora.
 *
 * U¿ywany w trybie podwójnego buforowania (double buffering).
 */
void Engine::renderToBackBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderScene(); 
    SDL_GL_SwapWindow(window);
}

/**
 * @brief Renderuje scenê do aktualnego bufora FBO.
 *
 * Funkcja wykorzystywana w trybie potrójnego buforowania.
 */
void Engine::renderToTripleBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, buffers[drawIndex].fbo);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderScene();

    rotateTripleBuffers();
    presentTripleBuffer();
}

/**
 * @brief Rotuje indeksy buforów potrójnego buforowania.
 *
 * Bufor rysowania staje siê buforem gotowym,
 * gotowy staje siê wyœwietlanym itd.
 */
void Engine::rotateTripleBuffers()
{
    int oldDisplay = displayIndex;
    displayIndex = readyIndex;
    readyIndex = drawIndex;
    drawIndex = oldDisplay;
}


/**
 * @brief Wyœwietla aktualny bufor z potrójnego buforowania.
 *
 * Renderuje teksturê z FBO na pe³noekranowy quad.
 */
void Engine::presentTripleBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, buffers[displayIndex].texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(0, 0);
    glTexCoord2f(1, 0); glVertex2f(1, 0);
    glTexCoord2f(1, 1); glVertex2f(1, 1);
    glTexCoord2f(0, 1); glVertex2f(0, 1);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    SDL_GL_SwapWindow(window);
}

/**
 * @brief Renderuje ca³¹ scenê 3D.
 *
 * Ustawia projekcjê, kamerê, oœwietlenie,
 * tryb cieniowania oraz rysuje wszystkie obiekty
 * geometryczne i teksturowane.
 */
void Engine::renderScene()
{
    glShadeModel(shadingMode == 0 ? GL_FLAT : GL_SMOOTH);

    if (projectionMode == 0)
        setPerspective(70.0f, 0.1f, 1000.0f);
    else
        setOrtho(-10, 10, -10, 10, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    camera.setPostion({ 0, 2, 15 });
    glm::mat4 view = camera.getViewMatrix();
    glLoadMatrixf(glm::value_ptr(view));

    setupLight();

    TexturedCube texCube(5.0f, myTextureID);
    texCube.rotate(SDL_GetTicks() * 0.05f, { 1, 1, 0 });
    texCube.draw();
  

    Cube c2(2.0f);
    c2.translate({ 10, 0, 0 });
    c2.rotate(SDL_GetTicks() * 0.05f, { 0,1,0 });
    c2.draw();

    Cube c3(1.0f);
    c3.translate({ -10, 0, 0 });
    c3.rotate(SDL_GetTicks() * 0.1f, { 0,1,0 });
    c3.draw();

    Vertex q1({ -2.0f, -2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f });
    Vertex q2({ 2.0f, -2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f });
    Vertex q3({ 2.0f,  2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f });
    Vertex q4({ -2.0f,  2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f });

    Quad quad(q1, q2, q3, q4);
    quad.translate({ 10, 5, 0 });
    quad.rotate(SDL_GetTicks() * 0.05f, { 1, 0, 0 });
    quad.draw();

    Vertex t1({ -2.0f, -2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
    Vertex t2({ 2.0f, -2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });
    Vertex t3({ 0.0f,  2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });

    Triangle tri(t1, t2, t3);
    tri.translate({ -10, 5, 0 });
    tri.rotate(SDL_GetTicks() * 0.05f, { 0, 1, 0 });
    tri.draw();

    Vertex f1({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f });
    Vertex f2({ 3.0f,  0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f });
    Vertex f3({ 2.0f,  2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f });
    Vertex f4({ -2.0f,  2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f });

    TriangleFan fan({f1, f2, f3, f4});
    fan.translate({ 0, 5, 0 });
    fan.rotate(SDL_GetTicks() * 0.05f, { 0, 0, 1 });
    fan.draw();

    Vertex s1({ -2.0f, -2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f });
    Vertex s2({ -2.0f,  2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f });
    Vertex s3({ 0.0f, -2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f });
    Vertex s4({ 0.0f,  2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f });

    TriangleStrip strip({ s1, s2, s3, s4});
    strip.translate({ 0, -5, 0 });
	strip.scale({ 0.5f, 0.5f, 0.5f });
    strip.draw();

    Vertex p1({ -2.0f,  0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 1.0f });
    Vertex p2({ 0.0f,  2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 1.0f });
    Vertex p3({ 2.0f,  0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 1.0f });

    Polylines polylines({ p1, p2, p3 });
    polylines.translate({ 10, -5, 0 });
    polylines.draw();

    Vertex l1({ -2.0f, -2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f });
    Vertex l2({ 2.0f,  2.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f });

    Line line(l1, l2);
    line.translate({ -10, -5, 0 });
    line.draw();



}

/**
 * @brief Inicjalizuje potrójne buforowanie (Triple Buffering).
 *
 * Tworzy trzy bufory ramki (FBO) wraz z teksturami
 * kolorów oraz buforami g³êbi.
 *
 * @return true jeœli inicjalizacja siê powiod³a
 */
bool Engine::initTripleBuffer() 
{
    for (int i = 0; i < BufferCount; i++)
    {
        glGenFramebuffers(1, &buffers[i].fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, buffers[i].fbo);

        glGenTextures(1, &buffers[i].texture);
        glBindTexture(GL_TEXTURE_2D, buffers[i].texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffers[i].texture, 0);

        glGenRenderbuffers(1, &buffers[i].depth);
        glBindRenderbuffer(GL_RENDERBUFFER, buffers[i].depth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, buffers[i].depth);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cerr << "FBO error\n";
            return false;
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

/**
 * @brief Ustawia rzutowanie perspektywiczne.
 *
 * @param fov K¹t widzenia
 * @param nearZ P³aszczyzna bliska
 * @param farZ P³aszczyzna daleka
 */
void Engine::setPerspective(float fov, float nearZ, float farZ) {
    glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)width / (float)height, 0.1f, 1000.0f);


    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));
}


/**
 * @brief Ustawia rzutowanie ortograficzne.
 *
 * @param left Lewa granica
 * @param right Prawa granica
 * @param bottom Dolna granica
 * @param top Górna granica
 * @param nearZ P³aszczyzna bliska
 * @param farZ P³aszczyzna daleka
 */
void Engine::setOrtho(float left, float right, float bottom, float top, float nearZ, float farZ) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, nearZ, farZ);
}

/**
 * @brief Konfiguruje Ÿród³o œwiat³a w scenie.
 *
 * Ustawia pozycjê œwiat³a, sk³adowe ambient,
 * diffuse, specular oraz parametry t³umienia.
 */
void Engine::setupLight()
{
    GLfloat lightPos[] = {0.0f, -5.0f, 10.0f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.02f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.001f);
}

/**
 * @brief Ustawia kolor czyszczenia ekranu.
 *
 * @param r Sk³adowa czerwona
 * @param g Sk³adowa zielona
 * @param b Sk³adowa niebieska
 * @param a Kana³ alfa
 */
void Engine::clearScreen(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}


/**
 * @brief Zwalnia zasoby silnika.
 *
 * Usuwa kontekst OpenGL, niszczy okno SDL
 * i koñczy dzia³anie biblioteki SDL.
 */
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
