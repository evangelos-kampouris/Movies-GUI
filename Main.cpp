#include "graphics.h"
#include "config.h"
#include "FilmBrowser.h"
#include <iostream>

// The custom callback function that the library calls 
// to check for and set the current application state.
void update(float ms)
{
    FilmBrowser* filmBrowser = reinterpret_cast<FilmBrowser *>
(graphics::getUserData());
    filmBrowser->update();
}

// The window content drawing function.
void draw()
{
    FilmBrowser* filmBrowser = reinterpret_cast<FilmBrowser*>(graphics::getUserData());
    filmBrowser->draw();
}

int main()
{
    FilmBrowser filmBrowser;
    graphics::createWindow(WINDOW_WIDTH, WINDOW_LEGTH, "MoviesGui!");
    
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setUserData(&filmBrowser);
    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_LEGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    filmBrowser.init();
    graphics::startMessageLoop();


    return 0;
}