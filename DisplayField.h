#pragma once
#include "Widget.h"

class DisplayField : public Widget {

protected:
	enum diplayFieldDrawType { RECT = 0, CIRLCE };
	diplayFieldDrawType type = RECT;

public:
	virtual void update() {};
	virtual void draw() {};
	virtual void init() {};

	//consrtuctor for rect
	DisplayField(float posx, float posy, float height, float width, graphics::Brush& _br)
		: Widget(posx, posy, height, width, _br) {};

	//consrtuctor for circle
	DisplayField(float posx, float posy, float _radious, graphics::Brush& _br)
		: Widget(posx, posy, _radious, _br) {
		type = CIRLCE;
	};
};

class IconDisplayField : public DisplayField {

private:
	const std::string activeIconTexture;
	const std::string nonActiveIconTexture;

public:
	//consrtuctor for rect
	IconDisplayField(float posx, float posy, float height, float width, graphics::Brush& _br, const std::string& _activeIconTexture,
		const std::string& _nonActiveIconTexture = "")
		: DisplayField(posx, posy, height, width, _br),activeIconTexture(_activeIconTexture), nonActiveIconTexture(_nonActiveIconTexture){};

	//consrtuctor for circle
	IconDisplayField(float posx, float posy, float _radious, graphics::Brush& _br,const std::string &_activeIconTexture,
		const std::string& _nonActiveIconTexture = "")
		: DisplayField(posx, posy, _radious, _br), activeIconTexture(_activeIconTexture), nonActiveIconTexture(_nonActiveIconTexture) {
	};

	void draw() override;
};