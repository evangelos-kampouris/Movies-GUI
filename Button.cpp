#include "Button.h"
#include "graphics.h"
#include "config.h"
#include <iostream>

void Button::update()
{
	if (buttonPressed)
		if (callBackFunc)
			callBackFunc(0, this); 
}

void Button::draw()
{
	if (type == RECT)
		graphics::drawRect(pos_x, pos_y, width, height, br);
	else
		graphics::drawDisk(pos_x, pos_y, radious, br);
}

void Button::init()
{

}

void Button::IsPressed(float posx, float posy, graphics::MouseState& ms)
{
	if (this->contains(posx, posy) && ms.button_left_released) 
		buttonPressed = true;
	else
		buttonPressed = false;
}


void MenuButton::draw()
{	
	if (hovered) {
		br.texture = "";
		SETCOLOR(br.fill_color, hoveredColor[0], hoveredColor[1], hoveredColor[2]);
		graphics::drawDisk(pos_x, pos_y, MENU_ITEM_RADIOUS * 1.5, br);
	}
	br.texture = ASSET_PATH + textureName;
	graphics::drawRect(pos_x, pos_y, width, height, br);
}


void TextButton::draw()
{
	float* brValues = br.outline_color;
	float* textBrushValues = textBrush.fill_color;
	if (active) {
		if (opacity >= 1)
			opacityTransition = -0.01f;
		else if (opacity <= 0.4f) 
			opacityTransition = 0.01f;
		opacity += opacityTransition;
		
		SETCOLOR(br.outline_color, 1.f, 0.5f, 0.f);
		SETCOLOR(textBrush.fill_color, 1.f, 0.5f, 0.f);
	}
	else {
		opacity = 1;
		SETCOLOR(br.outline_color, *brValues, *brValues + 1, *brValues + 2);
		SETCOLOR(textBrush.fill_color, *textBrushValues, *textBrushValues + 1, *textBrushValues + 2);
	}
	textBrush.fill_opacity = opacity;
	br.outline_opacity = opacity;
	graphics::drawRect(pos_x, pos_y, width, height, br);
	graphics::drawText(pos_x - 50, pos_y + 5, 20, text, textBrush);
}

void TextButton::setActive(bool v)
{
	if (v)
		active = true;
	else
		active = false;
	opacity = 1.f;

}
