#pragma once
#include "graphics.h"
#include "config.h"
#include "Button.h"
#include "Movie.h"
#include <string>
class MovieHolder : public Button {
private:
	const Movie* movie = nullptr;
	float scale = 1.f;
public:
	void update();
	void draw();
	void init();

	const Movie* getMovie() { return movie; }

	MovieHolder(float posx, float posy, float height, float width, graphics::Brush& _br, const Movie* movie_) :
		Button(posx, posy, height, width, _br), movie(movie_) {};

	MovieHolder(const MovieHolder& _MovieHolder, float posx, float posy, float _height, float _width)
	{
		pos_x = posx; pos_y = posy; height = _height; width = _width;
		radious = 0;
		graphics::Brush br = _MovieHolder.br;
		id = idGlobal++;
		hovered = false;
		hide = false;
		active = false;
		type = RECT;
		movie = _MovieHolder.movie;

	};
}; 
