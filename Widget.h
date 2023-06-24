#pragma once
#include "config.h"
#include "graphics.h"

class Widget {
protected:
	float pos_x = 0, pos_y = 0, radious = 0, height = 0, width = 0;
	int static idGlobal;
	int id = -1;
	bool hovered = false;
	bool hide = false;
	bool active = false;
	
	graphics::Brush br;
	enum containType { RECT = 0, CIRCLE };
	containType type = RECT;
	
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;

	Widget() {};

	Widget(float posx, float posy, float height, float width, graphics::Brush& _br)
		: pos_x(posx), pos_y(posy), height(height), width(width), br(_br) {
		id = idGlobal++;
	}

	Widget(float posx, float posy, float _radious, graphics::Brush& _br)
		: pos_x(posx), pos_y(posy), radious(_radious), br(_br) {
		type = CIRCLE;
		height = width = radious * 2;
		id = idGlobal++;
	};

	virtual bool contains(float posx, float posy) {
		if (type == RECT)
			return containsRect(posx, posy);
		return containsCircle(posx, posy, radious);
	};
	
	bool containsRect(float posx, float posy) {
		if (posx >= (pos_x - width / 2.f) && posx <= (pos_x + width / 2.f) &&
			posy >= (pos_y - height / 2.f) && posy <= (pos_y + height / 2.f))
			return true;
		else return false;
	};

	bool containsCircle(float posx, float posy,float radious) {
		if (distance(pos_x, pos_y, posx, posy) <= radious)
			return true;
		else return false;
	};

	virtual bool IsPressedR(float posx, float posy, graphics::MouseState& ms) {
		if (this->contains(posx, posy) && ms.button_left_released)
			return true;
		return false;
	}

	void setPosX(float pos) { pos_x = pos; }
	void setPosY(float pos) { pos_y = pos; }
	void setheight(float h) { height = h; }
	void setWidth(float d) { width = d; }
	void setHovered(bool b) { hovered = b; }
	void setHide(bool v) { hide = v; }
	virtual void setActive(bool v) { active = v; }

	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	float getHeight() { return height; }
	float getWidth() { return width; }
	int getId() { return id; }
	bool getHide() { return hide; }
	bool getHovered() { return hovered; }
	bool getActive() { return active; }
};



