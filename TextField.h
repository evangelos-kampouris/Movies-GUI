#pragma once
#include "DisplayField.h"
#include "scancodes.h"
#include <string>

class TextField : public DisplayField 
{
protected:
	graphics::Brush textBrush;
	float textSize = 20;
	std::string text;
public:
	virtual void update();
	virtual void draw();
	virtual void clearText();

	TextField(float posx, float posy, float height, float width, graphics::Brush& _br, graphics::Brush& _textBrush)
		: DisplayField(posx, posy, height, width, _br), textBrush(_textBrush) {};

	TextField(float posx, float posy, float _radious, graphics::Brush& _br, graphics::Brush& _textBrush)
		: DisplayField(posx, posy, _radious, _br), textBrush(_textBrush) {
		type = CIRLCE;
	};

	void setText(std::string txt) { text = txt; }
	void setTextSize(float size) { textSize = size; }

	virtual std::string getText() { return text; }
};

class InputTextField : public TextField
{
private:

	enum textType { NUM, CHAR };
	textType txtType = CHAR;

	float inputDelay = 130.f;
	float elapsedDelay = 0.f;

	char textChar[100] = {};
	int index = 0;
	int prev = 0;
	char InputedCharacter = 0;
	
public:

	void update() override;
	void draw() override;
	void clear() { index = 0; }
	void setText(std::string str) { text = str; }
	void setText(std::string str, int _index);
	void clearText() override;
	std::string toString();

	InputTextField(float posx, float posy, float height, float width, graphics::Brush& _br, graphics::Brush& _textBrush, textType _txtType = CHAR)
		: TextField(posx, posy, height, width, _br, _textBrush), txtType(_txtType) {
		for (int i = 0; i < 100; i++)//maybe to be removed
			textChar[i] = 0;
	};

	InputTextField(float posx, float posy, float _radious, graphics::Brush& _br, graphics::Brush& _textBrush, textType _txtType = CHAR)
		: TextField(posx, posy, _radious, _br, _textBrush), txtType(_txtType){
		type = CIRLCE;
		for (int i = 0; i < 100; i++) //maybe to be removed
			textChar[i] = 0;
	};
};