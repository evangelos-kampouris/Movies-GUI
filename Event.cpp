#include "Event.h"
#include <iostream>

void Event::update()
{
    if (!active)
        return;

    if (waiting()) {
        elapsedDelay += graphics::getDeltaTime() / 1000.0f;
        return;
    }

    elapsedTime += graphics::getDeltaTime() / 1000.0f;
    if (elapsedTime > duration) {
        active = false;
    }
}

bool Event::waiting()
{
    return elapsedDelay < delay;
}

void WidgetMovementEvent::update()
{
    Event::update();
    if (!widget) {
        active = false;
        return;
    }

    if (waiting())
        return;

    float s = elapsedTime / duration;
    float x = startX * (1.f - s) + stopX * s;
    float y = startY * (1.f - s) + stopY * s;
   

    widget->setPosX(x);
    widget->setPosY(y);
}
