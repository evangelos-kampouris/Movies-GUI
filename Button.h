#pragma once
#include "config.h"
#include <functional>
#include "Widget.h"

class Button : public Widget{
protected:
	bool buttonPressed = false;
	std::function<void(int, void*)> callBackFunc;
public:
	virtual void update();
	virtual void draw();
	virtual void init();
	void IsPressed(float posx, float posy, graphics::MouseState& ms);


	void setButtonPressed(bool v) { buttonPressed = v; }
	bool getButtonPressed() { return buttonPressed; }

	void setCallBackFuction(std::function<void(int, void*)> cb) { callBackFunc = cb; }

	Button() {};

	Button(float posx, float posy, float height, float width, graphics::Brush& _br)
		: Widget(posx, posy, height, width, _br) {};

	Button(float posx, float posy, float _radious, graphics::Brush& _br)
		: Widget(posx, posy, _radious, _br) {}

};

class MenuButton : public Button {
private:
	//TO DO - REMOVE TEXTURE NAME
	std::string textureName = "";
	int menuState = 0;
	float hoveredColor[3] = {0.f, 0.f, 0.f};

public:
	void draw() override;

	void setTexture(const std::string& fileName) { textureName = fileName; }
	int getMenuState() { return menuState; }
	

	MenuButton(float posx, float posy, float height, float width, graphics::Brush& _br,  float _hoveredColor[3], int state = 0, const std::string& _textureName = "")
		: Button(posx, posy, height, width, _br), textureName(_textureName) {
		for (unsigned int i = 0; i <= 2; i++) {
			hoveredColor[i] = _hoveredColor[i];
		}
	}

	MenuButton(float posx, float posy, float _menuRadious, graphics::Brush& _br, float _hoveredColor[3], int state = 0, const std::string& _textureName = "")
		: Button(posx, posy, _menuRadious, _br),textureName(_textureName),menuState(state) {
		for (unsigned int i = 0; i <= 2; i++) {
			hoveredColor[i] = _hoveredColor[i];
		}
	};
};

class TextButton : public Button {
private:
	std::string text;
	graphics::Brush textBrush;

	float opacity = 0.f;
	float opacityTransition = 0.1f;
public:

	void draw() override;
	void setActive(bool v) override;

	void setText(const std::string& txt) { text = txt; }

	std::string getText() { return text; }

	TextButton(float posx, float posy, float height, float width, graphics::Brush& _br, graphics::Brush& txtBr)
		: Button(posx, posy, height, width, _br), textBrush(txtBr) {};

	TextButton(float posx, float posy, float _radious, graphics::Brush& _br, graphics::Brush& txtBr)
		: Button(posx, posy, _radious, _br), textBrush(txtBr) {}
};