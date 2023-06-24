#include "TextField.h"
#include <iostream>

void TextField::update()
{
}

void TextField::draw()
{
	graphics::drawRect(pos_x, pos_y, width, height, br);
	graphics::drawText(pos_x-110, pos_y+5, textSize, text, textBrush);
}

void TextField::clearText()
{
	text = ""; 
}

void InputTextField::update()
{
	if (active) {
		
		elapsedDelay += graphics::getDeltaTime();
		
		int currentChar = graphics::SCANCODE_A;

		while(currentChar <= graphics::SCANCODE_SPACE){
			
			if (graphics::getKeyState((graphics::scancode_t)currentChar)) {

				if (elapsedDelay < inputDelay) {
					
					if (currentChar == graphics::SCANCODE_0)
						currentChar = graphics::SCANCODE_BACKSPACE;

					else if (currentChar == graphics::SCANCODE_BACKSPACE)
						currentChar = graphics::SCANCODE_SPACE;

					else
						currentChar++;

					continue;
				}
				else
					elapsedDelay = 0.f;
				
				//WRITING PART
				if (currentChar != graphics::SCANCODE_BACKSPACE && index < 100) {

					if (currentChar >= graphics::SCANCODE_1 && currentChar <= graphics::SCANCODE_9)
						InputedCharacter = (char)currentChar + 19;

					else if (currentChar == graphics::SCANCODE_0)
						InputedCharacter = (char)48;

					else if (currentChar == graphics::SCANCODE_SPACE) 
						InputedCharacter = (char)32;
					
					else if (graphics::getKeyState(graphics::SCANCODE_RSHIFT) || graphics::getKeyState(graphics::SCANCODE_LSHIFT))
						InputedCharacter = (char)(currentChar + 93 - 32);

					else
						InputedCharacter = (char)(currentChar + 93);

					prev = currentChar;
					textChar[index] = InputedCharacter;
					index++;
				}

				//REMOVING PART
				if (currentChar == graphics::SCANCODE_BACKSPACE && index > 0) 
					index--; //just substracting index by one. Index is to where we will transform the text variabe.
			}
			if (currentChar == graphics::SCANCODE_0)
				currentChar = graphics::SCANCODE_BACKSPACE;

			else if (currentChar == graphics::SCANCODE_BACKSPACE)
				currentChar = graphics::SCANCODE_SPACE;

			else
				currentChar++;
		}
		
	}
}

void InputTextField::draw()
{
	std::string str = toString();
	setText(str);
	graphics::drawRect(pos_x, pos_y, width, height, br);
	graphics::drawText(pos_x-110, pos_y+5, 15, getText(), textBrush);
}
void InputTextField::setText(std::string str, int _index)
{
	for (int i = 0; i < _index; i++)
		textChar[i] = str[i];
	index = _index;
};

std::string InputTextField::toString()
{
	std::string tempText = "";

	for (int i = 0; i < index; i++) {
		tempText += textChar[i];
	}

	return tempText;
}

void InputTextField::clearText()
{
	text = "";
	index = 0;
}

