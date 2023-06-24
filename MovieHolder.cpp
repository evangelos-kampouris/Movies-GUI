#include "MovieHolder.h"
#include "graphics.h"
#include "Button.h"
#include <iostream>

void MovieHolder::update()
{

}
void MovieHolder::draw()
{
	br.texture = ASSET_PATH + movie->getDisplayImage();
	if (hide) {
		br.fill_opacity = 0.f;
		br.outline_opacity = 0.f;
	}
	else {
		br.fill_opacity = 1.f;
		br.outline_opacity = 1.f;
	}
	if (hovered) {
		scale = 0.9f;
		graphics::Brush brSecondHolder;
		SETCOLOR(brSecondHolder.fill_color, 0.f, 0.f, 0.f);
		brSecondHolder.fill_opacity = 1.f;
		brSecondHolder.outline_opacity = 1.f;
		graphics::drawRect(pos_x, pos_y, width, height, brSecondHolder);

		graphics::setScale(scale, scale);
		//br.outline_opacity = 0.f;
		graphics::drawRect(pos_x, pos_y, width, height, br); //actual movie
		graphics::resetPose();
	}
	else {
		graphics::drawRect(pos_x, pos_y, width, height, br); //actual movie
	}
	
}
void MovieHolder::init()
{

}
