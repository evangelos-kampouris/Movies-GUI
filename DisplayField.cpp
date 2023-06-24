#include "DisplayField.h"

void IconDisplayField::draw()
{
	if (active) 
		br.texture = activeIconTexture;
	else
		br.texture = nonActiveIconTexture;

	graphics::drawRect(pos_x, pos_y, height, width, br);
}


