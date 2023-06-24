#pragma once
#include "config.h"
#include "MovieHolder.h"
#include "Movie.h"
#include "Slider.h"
#include "Event.h"
#include "TextField.h"
#include <string>
#include <list>

class FilmBrowser {
	
private:
	std::string menuIcon[2] = { "icons-search-32.png","icons-home-32.png" };
	MenuButton *menuBottoms[2];

	Movie* movies[TOTAL_MOVIES];
	MovieHolder* movieButton[TOTAL_MOVIES];
	int itemInRow = 3;

	// Display Info
	list<std::string*> tokens;
	const Movie* displayedMovie = nullptr;
	const Movie* prevDisplayedMovie = nullptr;
	
	//SEARCH
	Slider* sliderSearch = nullptr;
	std::list<MovieHolder*> searchedMovies;
	InputTextField* inputWidgets[4];
	TextField* descriptionWidgets[5];
	InputTextField* activeInputField = nullptr;

	//GENRE
	enum GenreCategories { DRAMA, HISTORY, ADVENTURE, CRIME, ACTION, FANATSY, SCIFI };
	TextButton* genreButtons[GENRE_CAT_INT];
	int genreSelectedCounter = 0;

	// search filters actions
	TextButton* textButtonFilters[2];
	
	//STATE
	enum buttonMenuStates { MAIN_MENU = 0, SEARCH, DISPLAY_MOVIE };
	buttonMenuStates state = MAIN_MENU;

	//sliderMainMenu data
	unsigned int rows = TOTAL_MOVIES / 3; 
	Slider* sliderMainMenu = nullptr;

	//Bounds Info
	float upperMovieDrawBound = 335.f;
	float downMovieDrawBound = 610.f;
	
	//events
	std::list<Event*> events;

public:
	void update();
	void draw();
	void init();
	FilmBrowser();
	~FilmBrowser();

	/**
	* Sets the state of the application
	* @param val : 0 = Main Menu, 1 = Search, 2 = DisplayMovie.
	*/
	void setState(int val);

	/**
	* Moves MovieHolder Objects in movieButton Array through WidgetMovementEvent
	*  @param y_difference : Positive value for down movement. Negative for up movement.
	*/
	void moveMovieIcons(float y_difference);
	
	/**
	* Moves MovieHolder Objects in searchedMovies List through WidgetMovementEvent.
	*  @param y_difference : Positive value for down movement. Negative for up movement.
	*/
	void moveSearcedMoviesIcons(float y_difference); //takes the list searchedMovies
	
	/**
	*Processes All event that are in event list.
	*/
	void processEvents();

	/**
	*	Add event in events list back
	*/
	void addEvent(Event* e){events.push_back(e);}

	/**
	* Performs search and updates searchedMovies list based on selecetd Genres and inputWidgets text.
	*/
	void search();

	/**
	*	Checks if slider's buttons are pressed and updates the slider.
	*/
	void sliderUpdate(Slider* slider,float mx, float my, graphics::MouseState& ms);

	/**
	* Controls Actions Perfomred by Widgets that are used in filmBrowser Class.
	* 
	* evt Number 1 Assigned To : MenuButtons, setState().
	* evt Number 2 Assigned To : sliderMainMenu UpperButton.
	* evt Number 3 Assigned To : sliderMainMenu downButton.
	* evt Number 4 Assigned To : Genre Select On Seacrh Button. Fading effects and set as selected.
	* evt Number 5 Assigned To : Perform Search.
	* evt Number 6 Assigned To : Perform Clear.
	* evt Number 7 Assigned To : searchSlider UpperButton.
	* evt Number 8 Assigned To : searchSlider DownButton.
	*
	* @param evt : Event Number from One to N that corressponts to specific action
	* @param data : Pointer to Data that is needed to perfom the evt Event 
	*/
	void controlBrowser(int evt, void* data);
};
