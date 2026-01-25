#pragma once
#include "glew/include/GL/glew.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>
#include "Camera.h"
#include "BitmapHandler.h"

 /**
  * @struct TripleBuffering
  * @brief Struktura przechowuj¹ca zasoby bufora.
  *
  * Zawiera identyfikatory obiektów OpenGL niezbêdnych do renderowania:
  * framebuffer object,
  * teksturê koloru,
  * renderbuffer g³êbokoœci.
  */

struct TripleBuffering
{
    GLuint fbo;
    GLuint texture;
    GLuint depth;
};


/**
 * @class Engine
 * @brief G³ówna klasa silnika 3D.
 *
 * Klasa Engine odpowiada za:
 * inicjalizacjê SDL, OpenGL oraz okna,
 * obs³ugê pêtli g³ównej aplikacji,
 * obs³ugê zdarzeñ klawiatury i myszy,
 * zarz¹dzanie buforowaniem,
 * renderowanie sceny 3D,
 * konfiguracjê kamery, projekcji oraz oœwietlenia.
 */
class Engine {
private:
    /** @brief WskaŸnik na okno SDL */
    SDL_Window* window = nullptr;
    /** @brief Kontekst OpenGL powi¹zany z oknem */
    SDL_GLContext glContext = nullptr;
    /** @brief Flaga trybu okna (pe³ny ekran / w oknie) */
    bool Fullscreen;
    /** @brief Flaga steruj¹ca dzia³aniem pêtli g³ównej */
    bool isRunning;
    /** @brief Szerokoœæ okna */
    int width;
    /** @brief Wysokoœæ okna */
    int height;
    /** @brief Flaga steruj¹ca obs³ug¹ myszy */
    bool mouseOn;
    /** @brief Flaga steruj¹ca obs³ug¹ klawiatury */
    bool keyboardOn;
    /** @brief Liczba klatek na sekundê */
    int targetFPS;
    /** @brief Flaga okreœlaj¹ca bufor Z */
    bool depthBufferOn;
    /** @brief OpóŸnienie jednej klatki */
    Uint32 frameDelay;
    /** @brief Czas rozpoczêcia klatki */
    Uint32 frameStart;
    /** @brief Czas klatki */
    Uint32 frameTime;
    /** @brief Znacznik czasu poprzedniej klatki */
    Uint32 lastTime;
    /**
     * @brief Tryb projekcji.
    * 0 – perspektywiczna
    * 1 – ortograficzna
    */
    int projectionMode; 
    /** @brief Obiekt kamery sceny */
    Camera camera;
    /**
     * @brief Tryb cieniowania.
     * 0 – FLAT
     * 1 – SMOOTH (Gouraud)
     */
    int shadingMode;
    /** @brief Liczba buforów w trybie triple buffering */
    static const int BufferCount=3;
    /** @brief Tablica buforów triple buffering */
    TripleBuffering buffers[BufferCount];
    /** @brief Indeks aktualnie rysowanego bufora */
    int drawIndex = 0;
    /** @brief Indeks bufora gotowego do wyœwietlenia */
    int readyIndex = 1;
    /** @brief Indeks bufora aktualnie wyœwietlanego */
    int displayIndex = 2;
    /**
     * @brief Tryb buforowania.
     * 2 – double buffering
     * 3 – triple buffering
     */
    int BufferingMode;
    /** @brief Identyfikator tekstury */
    GLuint myTextureID;


public:
    /**
    * @brief Inicjalizuje silnik, okno i kontekst OpenGL.
    *
    * @param windowtitle Tytu³ okna
    * @param x Pozycja X okna
    * @param y Pozycja Y okna
    * @param width Szerokoœæ okna
    * @param height Wysokoœæ okna
    * @param Fullscreen Tryb pe³noekranowy
    * @param mouseOn W³¹czenie obs³ugi myszy
    * @param keyboardOn W³¹czenie obs³ugi klawiatury
    * @param targetFPS FPS
    * @param depthBufferOn W³¹czenie bufora Z
    * @param BufferingMode Tryb buforowania
    *
    * @return true jeœli inicjalizacja siê powiod³a
    */
    bool init(const std::string& windowtitle, int x, int y, int width, int height, bool Fullscreen, bool mouseOn, bool keyboardOn, int targetFPS, bool depthBufferOn, int BufferingMode);
   
    /** @brief g³ówna pêtla silnika */
    void mainLoop();
    /** @brief Obs³uga klawiatury i myszy */
    void kbmEvents();
    /** @brief Renderowanie klatki */
    void renderFrame();

    /**
    * @brief Czyœci ekran zadanym kolorem.
    * @param r Red
    * @param g Green
    * @param b Blue
    * @param a Alpha
    */
    void clearScreen(float r, float g, float b, float a);

    /** @brief Ustawia projekcjê perspektywiczn¹ */
    void setPerspective(float fov, float nearZ, float farZ);
    /** @brief Ustawia projekcjê ortograficzn¹ */
    void setOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);
    /** @brief Konfiguruje oœwietlenie sceny */
    void setupLight();
    /** @brief Inicjalizuje zasoby triple buffering */
    bool initTripleBuffer();
    /** @brief Renderuje do back buffer */
    void renderToBackBuffer();
    /** @brief Renderuje do bufora triple buffering */
    void renderToTripleBuffer();
    /** @brief Prze³¹cza bufory w trybie triple buffering */
    void rotateTripleBuffers();
    /** @brief Prezentuje aktualny bufor na ekranie */
    void presentTripleBuffer();
    /** @brief Renderuje ca³¹ scenê */
    void renderScene();
    /** @brief Zwalnia zasoby i zamyka silnik */
    void clean();
   

};