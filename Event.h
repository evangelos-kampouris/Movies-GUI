#pragma once
#include "graphics.h"
#include "Widget.h"

class Event {
protected:

	float x_pos;
	float y_pos;
	float duration = 0.f;
	float delay = 0.f;
	float elapsedTime = 0.f;
	float elapsedDelay = 0.f;
	bool active = true;

public:
	virtual void draw() {};
	virtual void update();
	Event(float x = 0.f, float y = 0.f, float dur = 0.1f, float del = 0.0f)
		: x_pos(x), y_pos(y), duration(dur), delay(del) {};
	virtual ~Event() {}
	bool isActive() { return active; }
	bool disable() { active = false; }
	bool waiting();

};

class WidgetMovementEvent : public Event {
	Widget* widget = nullptr;
	float startX;
	float startY;
	float stopX;
	float stopY;

public:
	void update() override;
	
	WidgetMovementEvent(float start_x, float start_y, float stop_x, float stop_y, float _duration,
		Widget* wi) : Event(0.f, 0.f, _duration, 0.f), startX(start_x), startY(start_y),
		stopX(stop_x), stopY(stop_y), widget(wi) {};

	~WidgetMovementEvent() {
		widget = nullptr;
	}
};