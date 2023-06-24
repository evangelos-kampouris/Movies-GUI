#include "Slider.h"
#include <iostream>

void Slider::update()
{
	upperButton->update();
	if (upperButton->getButtonPressed()) //Checking if getButtonPreesed only, because , it gets true only if current Row > 0 , through filmbrowser update
		setPreviousActive();

	downButton->update();
	if (downButton->getButtonPressed())
		setNextActive();
}

void Slider::draw()
{
	//Buttons
	if (rows == 0) // if no need to draw due to few elements return.
		return;
	
	upperButton->draw();
	downButton->draw();
	//slider
	//graphics::Brush silderBr;
	for (IconDisplayField* sliderIcons : sliderDots) {
		sliderIcons->draw();
	}
	
}

void Slider::init()
{
	graphics::Brush buttonBrush;

	buttonBrush.outline_opacity = 0.0f;
	buttonBrush.texture = firstDrawArrowFileName;

	upperButton = new Button(pos_x, pos_y , 20, width, buttonBrush);

	buttonBrush.texture = SecondDrawArrowFileName;
	downButton = new Button(pos_x, pos_y + height, 20, width, buttonBrush);

	initSliderDots(rows);
}

void Slider::initSliderDots(int _rows)
{
	graphics::Brush IconDisplayBr;
	SETCOLOR(IconDisplayBr.fill_color, 1.f, 1.f, 1.f);
	IconDisplayBr.outline_opacity = 0.0f;

	float posy = pos_y + padding;
	for (int i = 0; i < _rows && i < maxRows; i++) {
		IconDisplayField* icn = new IconDisplayField(pos_x, posy, 5.f, IconDisplayBr, fileNameActive, fileNameNonActive);
		if (i == 0)
			icn->setActive(true);
		sliderDots.push_back(icn);
		posy += padding;
	}
}

bool Slider::sliderButtonIsPressed(float posx, float posy, graphics::MouseState& ms)
{
	if(upperButtonIsPreesed(posx,posy,ms))
		return true;
	if (downButtonIsPreesed(posx, posy, ms))
		return true;
	return false;
}

bool Slider::upperButtonIsPreesed(float posx, float posy, graphics::MouseState& ms)
{
	if (upperButton->IsPressedR(posx, posy, ms))
		return true;
	return false;
}

bool Slider::downButtonIsPreesed(float posx, float posy, graphics::MouseState& ms)
{
	if (downButton->IsPressedR(posx, posy, ms))
		return true;
	return false;
}

void Slider::setNextActive()
{
	if (currentRow == sliderDots.size()-1)
		return;
	sliderDots[currentRow]->setActive(false);
	currentRow++;
	sliderDots[currentRow]->setActive(true);
}

void Slider::setPreviousActive()
{
	if (currentRow == 0)
		return;
	sliderDots[currentRow]->setActive(false);
	currentRow--;
	sliderDots[currentRow]->setActive(true);
}

void Slider::setFirstActive()
{
	if (sliderDots.empty())
		return;

	sliderDots[0]->setActive(true);
	for (int i = 1; i < sliderDots.size(); i++) {
		sliderDots[i]->setActive(false);
	}
}

void Slider::setPadding(int rows)
{
	switch (rows) {
	case 1:
		padding = 90.f;
		break;
	case 2:
		padding = 60.f;
		break;
	case 3:
		padding = 43.f;
		break;
	case 4:
		padding = 35.f;
		break;
	case 5:
		padding = 30.f;
		break;
	default:
		padding = 0;
		break;
	};
}

void Slider::setRows(int _rows)
{
	if (rows == _rows)
		return;

	setPadding(_rows);

	if (sliderDots.empty()) {
		initSliderDots(_rows);
	}
	else if (rows > _rows) { // if more old rows than new we have to delete the outstanding
		for (int i = rows - 1; i > _rows - 1; i-- ) {
			delete sliderDots[i];
			sliderDots.pop_back();
		}
		sliderDots.shrink_to_fit();
		setsliderDotsPadding();
		setFirstActive();
	}
	else {
		initSliderDots(_rows - rows);
		setFirstActive();
		setsliderDotsPadding();
	}
	rows = _rows;
}

void Slider::setsliderDotsPadding()
{
	float posy = pos_y + padding;
	for (auto dot : sliderDots) {
		dot->setPosY(posy);
	}
}

