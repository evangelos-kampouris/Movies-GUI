#pragma once
#include "graphics.h"
#include "DisplayField.h"
#include <vector>
#include "Button.h"


class Slider : public Widget {
private:
	Button* upperButton = nullptr;
	Button* downButton = nullptr;

	const int maxRows = 5;
	std::vector<IconDisplayField*> sliderDots;
	int rows = 0; //total rows
	int currentRow = 0;
	float startingPadding = 0;
	float padding;

	//textures
	const std::string firstDrawArrowFileName = ASSET_PATH + std::string ("slider-arrow-first.png");
	const std::string SecondDrawArrowFileName = ASSET_PATH + std::string("slider-arrow-second.png");
	const std::string fileNameActive = ASSET_PATH + std::string("slider-active.png");
	const std::string fileNameNonActive = ASSET_PATH + std::string("slider-noactive.png");

	/**
	* Creates row icons 
	* @param _rows : Number of icons to be created.
	*/
	void initSliderDots(int _rows);

public:
	void update() override;
	void draw() override;
	void init() override;

	//pressed methods

	/**
	* Checks if any slider button is pressed
	* 
	* @return bool
	*/
	bool sliderButtonIsPressed(float posx, float posy, graphics::MouseState& ms);
	/**
	* Checks if any upper button is pressed
	*
	* @return bool
	*/
	bool upperButtonIsPreesed(float posx, float posy, graphics::MouseState& ms);
	/**
	* Checks if any down button is pressed
	*
	* @return bool
	*/
	bool downButtonIsPreesed(float posx, float posy, graphics::MouseState& ms);
	/**
	* Sets next icon active if there is one next.
	*/
	void setNextActive();
	/**
	* Sets prev icon active if there is one next.
	*/
	void setPreviousActive();
	/**
	* Sets first icon active.
	*/
	void setFirstActive();
	
	//setters
	/**
	* Sets padding between icons.
	*/
	void setPadding(int rows);
	/**
	* Resets current icons padding.
	*/
	void setsliderDotsPadding();
	/**
	* Resets total rows and padding.
	*/
	void setRows(int _rows);

	void setCurrentRow(unsigned int n) { currentRow = n; }

	//getters
	int getRows() { return rows; }
	unsigned int  getCurrentRow() { return currentRow; }
	Button* getUpperButton() { return upperButton; }
	Button* getDownButton() { return downButton; }
	

	Slider(float posx, float posy, float height, float width, graphics::Brush& _br, int _rows)
		: Widget(posx, posy, height, width , _br),rows(_rows){
		this->setPadding(rows);
		this->init();
	};


	~Slider() {
		delete upperButton;
		delete downButton;
		upperButton = downButton = nullptr;

		for (auto icd : sliderDots) {
			if (icd) {
				delete icd;
				icd = nullptr;
			}
		}
	}
};