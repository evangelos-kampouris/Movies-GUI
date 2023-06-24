#include "FilmBrowser.h"
#include "graphics.h"
#include <cmath>
#include <list>
#include <iostream>
#include <algorithm>

void FilmBrowser::controlBrowser(int evt, void* data) 
{
	switch (evt)
	{
		case 1: //Menu Button State
		{
			MenuButton* tempMenu_b = static_cast<MenuButton*>(data);
			FilmBrowser::setState(tempMenu_b->getMenuState());
			tempMenu_b = nullptr;
		}
		break;
		case 2://sliderMainMenu Upper Button
		{
			Button* upperButton = static_cast<Button*>(data);
			FilmBrowser::moveMovieIcons(+MOVIES_ROW_DIFFERENCE);
		}
		break;
		case 3://sliderMainMenu Down Button
		{
			Button* downButton = static_cast<Button*>(data);
			FilmBrowser::moveMovieIcons(-MOVIES_ROW_DIFFERENCE);
		}
		break;
		case 4://TextButton Genres
		{
			TextButton* genreButton = static_cast<TextButton*>(data);
			//for Fading effect
			if (genreButton->getButtonPressed()) {
				if (!genreButton->getActive()) {
					genreButton->setButtonPressed(true);
					genreButton->setActive(true);
					genreSelectedCounter++;
				}
				else {
					genreButton->setButtonPressed(false);
					genreButton->setActive(false);
					genreSelectedCounter--;
				}
			}
		}
		break;
		case 5://TextButton Search
		{
			//delete previous elements in searchedMovies List.
			if (!searchedMovies.empty()) {
				
				for (auto mv : searchedMovies) {
					delete mv;
					mv = nullptr;
				}
				searchedMovies.clear();
			}
			//Search
			FilmBrowser::search();

			if (searchedMovies.size() < 3)
				sliderSearch->setRows(0);
			else 
				sliderSearch->setRows((int)searchedMovies.size() / 3 - 1); // minus one because we display the first two rows as one 
			
			if (searchedMovies.empty()) //break in case there is no match
				break;

			//if Elements exist give them cords Here.
			float x_PosSMovies = 650;
			float y_PosSMovies = MOVIES_INIT_POSY;

			float x_differenceSMovies = 260;
			float y_differenceSMovies = MOVIES_ROW_DIFFERENCE;

			int x_alignCounter = 0;

			for (auto it = searchedMovies.begin(); it != searchedMovies.end(); ++it) {

				(*it)->setPosX(x_PosSMovies);
				(*it)->setPosY(y_PosSMovies);

				if (x_alignCounter == 2) {
					x_alignCounter = 0;
					x_PosSMovies = 650;
					y_PosSMovies += y_differenceSMovies;
				}

				else {
					x_alignCounter++;
					x_PosSMovies += x_differenceSMovies;
				}
			}
		}
		break;
		case 6:
		{
			//delete previous elements in searchedMovies List.
			if (!searchedMovies.empty()) {

				for (auto mv : searchedMovies) {
					delete mv;
					mv = nullptr;
				}
				searchedMovies.clear();
			}
			sliderSearch->setRows(0);
			
			for (auto txtField : inputWidgets) {
				txtField->clearText();
			}
			for (auto gb : genreButtons) {
				gb->setActive(false);
			}
			genreSelectedCounter = 0;
		}
		break;
		case  7: //upper butt Search Slider
		{
			Button* upperButton = static_cast<Button*>(data);
			FilmBrowser::moveSearcedMoviesIcons(+MOVIES_ROW_DIFFERENCE);
		}
		break;
		case 8: //down butt Search Slider
		{
			Button* downButton = static_cast<Button*>(data);
			FilmBrowser::moveSearcedMoviesIcons(-MOVIES_ROW_DIFFERENCE);
		}
	default:
		break;
	}
}
void FilmBrowser::update()
{
	processEvents();

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
	float my = graphics::windowToCanvasY((float)ms.cur_pos_y);

	//menu Buttons
	for (MenuButton* menu_b : menuBottoms) {
		if (!menu_b->contains(mx, my))
			menu_b->setHovered(false);
		else {
			menu_b->setHovered(true);
			if (ms.button_left_released) {
				menu_b->setButtonPressed(true);
				menu_b->update();
			}
		}
	}
	//Slider
	if (state == MAIN_MENU) {
		
		//slider
		sliderUpdate(sliderMainMenu, mx, my, ms);

		//movie Buttons
		for (MovieHolder* mvHolder : movieButton) {

			//bounds
			float mvHolderPosy = mvHolder->getPosY();
			if (mvHolderPosy < upperMovieDrawBound - 30 || mvHolderPosy > downMovieDrawBound + 30) {// + | - 30 cause of delta time not always excact and may cause to set this condition to true
				mvHolder->setHide(true);
			}
			else
				mvHolder->setHide(false);

			//contains
			if (mvHolder->contains(mx, my)) {
				if (!mvHolder->getHide()) {
					mvHolder->setHovered(true);
					if (ms.button_left_released && state == MAIN_MENU) {
						state = DISPLAY_MOVIE;
						displayedMovie = mvHolder->getMovie();
					}
				}
			}
			else mvHolder->setHovered(false);
		}
	}

	if (state == SEARCH) {
		
		for (auto inputField : inputWidgets) {
			
			if (inputField->IsPressedR(mx, my, ms)) {
				
				if (!activeInputField) {
					activeInputField = inputField;
				
				}
				else {
					activeInputField->setActive(false);
					activeInputField = inputField;
				}
				activeInputField->setActive(true);
			}
			inputField->update();
		}

		for (auto tb : genreButtons) {
			tb->IsPressed(mx, my, ms);
			tb->update();

		}

		for (auto tb : textButtonFilters) {
			tb->IsPressed(mx, my, ms);
			tb->update();
		}

		//slider
		sliderUpdate(sliderSearch, mx, my, ms);

		// Searched Movie Buttons
		for (MovieHolder* mvHolder : searchedMovies) {

			//bounds
			float mvHolderPosy = mvHolder->getPosY();
			if (mvHolderPosy < upperMovieDrawBound - 30 || mvHolderPosy > downMovieDrawBound + 30) {// + /-30 cause of buggie event
				mvHolder->setHide(true);
			}
			else
				mvHolder->setHide(false);

			//contains
			if (mvHolder->contains(mx, my)) {
				if (!mvHolder->getHide()) {
					mvHolder->setHovered(true);
					if (ms.button_left_released && state == SEARCH) {
						state = DISPLAY_MOVIE;
						displayedMovie = mvHolder->getMovie();
					}
				}
			}
			else mvHolder->setHovered(false);
		}
	}
	if (state == DISPLAY_MOVIE) {
		
		//Description
		
		if (!(prevDisplayedMovie == displayedMovie)) { // if same movie to be diplsayed, skip, else enter if
			
			prevDisplayedMovie = displayedMovie;

			if (!tokens.empty()) {
				for (auto tok : tokens) {
					delete tok;
					tok = nullptr;
				}
				tokens.clear();
			}

			int buffer = 45;
			int bufferCounter = 0;

			bool lastChar = false; //used in case last char is passed in last else loop to insure that new line will created even for one letter

			std::string* tempString = new std::string("");

			for (auto str : displayedMovie->getDescription()) {
				if (bufferCounter < buffer) {
					*tempString += str;
					bufferCounter++;
					lastChar = false;
				}
				else {
					tokens.push_back(tempString);
					tempString = new std::string("");
					*tempString += str;
					bufferCounter = 1;
					lastChar = true;
				}
			}
			if (!lastChar)
				tokens.push_back(tempString);
		}
	}
}

void FilmBrowser::draw()
{
	//---------------------background---------------------\\

	graphics::Brush brBackgorund;
	brBackgorund.outline_opacity = 0.0f;
	SETCOLOR(brBackgorund.fill_color, 1.0f, 1.0f, 1.0f);
	brBackgorund.texture = ASSET_PATH + std::string("background.png");
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_LEGHT / 2, CANVAS_WIDTH, CANVAS_LEGHT, brBackgorund);

	//set font
	graphics::setFont(std::string(ASSET_PATH) + "OpenSans-Regular.ttf");
	
	//title
	graphics::Brush appText;
	std::string appLabel = "FilmBrowser";
	graphics::drawText(CANVAS_WIDTH / 2-70, 120, 40, appLabel, appText);

	//---------------------draw menu icons---------------------\\

	for (auto menu_b : menuBottoms) {
		menu_b->draw();
	}

	if (state == MAIN_MENU) {
		for (auto mvHolder : movieButton) {
			mvHolder->draw();
		}
		//---------------------sliderMainMenu---------------------\\

		sliderMainMenu->draw();//check in here if rows big enough to be printed
	}
	
	if (state == DISPLAY_MOVIE) {
		if (!displayedMovie)
			return;

		//Movie Photo Draw
		graphics::Brush singleDisplayBrush;
		singleDisplayBrush.texture = ASSET_PATH + std::string(displayedMovie->getDisplayImage());
		singleDisplayBrush.outline_opacity = 1.f;
		graphics::drawRect(MOVIES_INIT_POSX, 425, 500, 500, singleDisplayBrush);

		//Movie Information Draw
		float initX = MOVIES_INIT_POSX + 250 + 30;
		float initY = 200;
		float adjustPosY = 40;
		graphics::Brush brTexts;

		//Title
		graphics::drawText(initX, initY, 35, displayedMovie->getTitile(), brTexts);
		initY += adjustPosY;

		//Director
		std::string directorTxt = "Director : " + displayedMovie->getDirector();
		graphics::drawText(initX, initY, 20, directorTxt, brTexts);
		initY += adjustPosY;

		//Actors
		std::string actorsString = "Actors : " + displayedMovie->getActorsToText();
		graphics::drawText(initX, initY, 20, actorsString, brTexts);
		initY += adjustPosY;

		//Genre
		std::string genreString = "Genre : " + displayedMovie->getGenreToText();
		graphics::drawText(initX, initY, 20, genreString, brTexts);
		initY += adjustPosY;

		//Year
		std::string yearTxt = "Year : " + std::to_string(displayedMovie->getYear());
		graphics::drawText(initX, initY, 20, yearTxt, brTexts);
		initY += adjustPosY;

		//Description

		graphics::drawText(initX, initY, 20, "Description : ", brTexts);
		initY += adjustPosY;

		for (string* str : tokens) {
			graphics::drawText(initX, initY, 20, *str, brTexts);
			initY += adjustPosY;
		}
	}//end of DISPLAY MOVIE

	if (state == SEARCH) {

		//Draw Search Widgets

		//draw inputFields
		for (auto fields : inputWidgets) {
			fields->draw();
		}
		
		//draw genre
		for (auto genreField : genreButtons) {
			if(genreField)
				genreField->draw();
		}

		//draw Descriptions
		for (auto descriptionWidget : descriptionWidgets) {
			if (descriptionWidget)
				descriptionWidget->draw();
		}
		for (auto textButtonFilter : textButtonFilters) {
			if (textButtonFilter)
				textButtonFilter->draw();
		}

		//---------------------Draw Selected Movie buttons---------------------\\
		//TO DO set update too. everytime search pressed clear list
		
		for (auto it = searchedMovies.begin(); it != searchedMovies.end(); ++it) {
			(*it)->draw();
		}
		//---------------------slider Search---------------------\\

		sliderSearch->draw();//check in here if rows big enough to be printed
	}
}
void FilmBrowser::init()
{
	//---------------------preload images---------------------\\

	graphics::preloadBitmaps(ASSET_PATH); 

	//---------------------Generate home Bar(MenuIcon) buttons---------------------\\
	
	float pos_x = MENU_ITEM_LEFT_MARGIN;
	float pos_y = MENU_ITEM_TOP_MARGIN;

	//deisgn
	graphics::Brush homeBarBrush;
	homeBarBrush.outline_opacity = 0.0f;
	float hovercolor[3] = { 0.505f, 0.52f, 0.505f };

	int j = 1;
	for (unsigned int i = 0; i < 2 ; i++) {
		MenuButton* menuB = new MenuButton(pos_x, pos_y, MENU_ITEM_RADIOUS, homeBarBrush, hovercolor, j, menuIcon[i]);
		menuB->setCallBackFuction(std::bind( &FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 1, placeholders::_2));

		menuBottoms[i] = menuB;
		pos_y -= MENU_ITEM_TOP_PADDING;
		j--;
	}
	//---------------------sliderMainMenu---------------------\\

	graphics::Brush sliderBr;

	sliderMainMenu = new Slider(CANVAS_WIDTH - 20, 285, 180, 20, sliderBr, rows - 1);

	sliderMainMenu->getUpperButton()->setCallBackFuction(std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 2, placeholders::_2));
	sliderMainMenu->getDownButton()->setCallBackFuction(std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 3, placeholders::_2));

	//---------------------sliderSearch---------------------\\

	sliderSearch = new Slider(CANVAS_WIDTH - 20, 285, 180, 20, sliderBr, 0);

	sliderSearch->getUpperButton()->setCallBackFuction(std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 7, placeholders::_2));
	sliderSearch->getDownButton()->setCallBackFuction(std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 8, placeholders::_2));

	//---------------------Generate Movies Data---------------------\\

	std::string actorsData[] = { "Brad Pitt", "Edward Norton", "Helena Bonham Carter" };
	std::string genreData[] = {"drama"};

	Movie* movie = new Movie("Fight Club", "David Fincher", actorsData, 3, genreData, 1,1999, "FightClub.png", "An insomniac office worker and a devil-may-care soap maker form an underground fight club that evolves into much more.");
	movies[0] = movie;

	//Second 

	std::string actorsData2[] = {"Marlon Brando","Al Pacino","James Caan"};
	std::string genreData2[] = { "drama","history" };

	movie = new Movie("The Godfather", "Francis Ford Coppola", actorsData2, 3, genreData2, 2, 1972, "Godfather.png", "The aging patriarch of an organized crime dynasty in postwar New York City transfers control of his clandestine empire to his reluctant youngest son.");
	movies[1] = movie;

	//Third

	std::string actorsData3[] = { "Liam Neeson","Ralph Fiennes","Ben Kingsley" };
	std::string genreData3[] = { "drama","history" };

	movie = new Movie("Schindler's List", "Steven Spielberg", actorsData3, 3, genreData3, 2, 1993, "SchindlersList.png", "In German-occupied Poland during World War II, industrialist Oskar Schindler gradually becomes concerned for his Jewish workforce after witnessing their persecution by the Nazis.");
	movies[2] = movie;

	//Forth

	std::string actorsData4[] = { "John Travolta", "Uma Thurman", "Samuel L. Jackson" };
	std::string genreData4[] = { "drama", "crime" };

	movie = new Movie("Pulp Fiction", "Quentin Tarantino", actorsData4, 3, genreData4, 2, 1994, "PulpFiction.png", "The lives of two mob hitmen, a boxer, a gangster and his wife, and a pair of diner bandits intertwine in four tales of violence and redemption.");
	movies[3] = movie;

	//Fifth

	std::string actorsData5[] = { "Harrison Ford","Karen Allen", "Paul Freeman" };
	std::string genreData5[] = { "action", "adventure" };

	movie = new Movie("Indiana Jones and the Raiders of the Lost Ark", "Steven Spielberg", actorsData5, 3, genreData5, 2, 1981, "RaidersOfTheLostArk.png", "Archaeology professor Indiana Jones ventures to seize a biblical artefact known as the Ark of the Covenant. While doing so, he puts up a fight against Renee and a troop of Nazis.");
	movies[4] = movie;

	//Sixth

	std::string actorsData6[] = { "Harrison Ford", "Kate Capshaw", "Ke Huy Quan" };
	std::string genreData6[] = { "action", "adventure" };

	movie = new Movie("Indiana Jones and the Temple of Doom", "Steven Spielberg", actorsData6, 3, genreData6, 2, 1984, "TempleOfDoom.png", "A skirmish in Shanghai puts archaeologist Indiana Jones, his partner Short Round and singer Willie Scott crossing paths with an Indian village desperate to reclaim a rock stolen by a secret cult beneath the catacombs of an ancient palace."  );
	movies[5] = movie;

	//Seventh

	std::string actorsData7[] = { "Mark Hamill", "Harrison Ford", "Carrie Fisher" };
	std::string genreData7[] = { "action", "adventure","fantasy" };

	movie = new Movie("Star Wars: Episode IV - A New Hope", "George Lucas", actorsData7, 3, genreData7, 3, 1977, "ANewHope.png", "Luke Skywalker joins forces with a Jedi Knight, a cocky pilot, a Wookiee and two droids to save the galaxy from the Empire's world-destroying battle station, while also attempting to rescue Princess Leia from the mysterious Darth Vader.");
	movies[6] = movie;

	//Eighth

	std::string actorsData8[] = { "Mark Hamill", "Harrison Ford", "Carrie Fisher" };
	std::string genreData8[] = { "action", "adventure","fantasy" };

	movie = new Movie("Star Wars : Episode V - The Empire Strikes Back", "Irvin Kershner", actorsData8, 3, genreData8, 3, 1980, "EmpireStrikesBack.png", "After the Rebels are brutally overpowered by the Empire on the ice planet Hoth, Luke Skywalker begins Jedi training with Yoda, while his friends are pursued across the galaxy by Darth Vaderand bounty hunter Boba Fett.");
	movies[7] = movie;

	//Nineth

	std::string actorsData9[] = { "Arnold Schwarzenegger","Linda Hamilton","Michael Biehn" };
	std::string genreData9[] = { "action","scifi" };

	movie = new Movie("The Terminator", "James Cameron", actorsData9, 3, genreData9, 2, 1984, "Terminator.png", "A human soldier is sent from 2029 to 1984 to stop an almost indestructible cyborg killing machine, sent from the same year, which has been programmed to execute a young woman whose unborn son is the key to humanity's future salvation.");
	movies[8] = movie;

	//---------------------Generate Movies Icon buttons---------------------\\

	//design
	graphics::Brush moviesBrush;

	moviesBrush.outline_opacity = 1.f;

	//position
	float x_initPos = MOVIES_INIT_POSX;
	float y_initPos = MOVIES_INIT_POSY;

	float x_difference = 425;
	float y_difference = MOVIES_ROW_DIFFERENCE;

	int x_alignCounter = 0;
	//movieIcon = new MovieHolder(360, CANVAS_LEGHT / 2 - 40 , MOVIES_HEIGHT, MOVIES_WIDTH, *movies[0]);
	for (int j = 0; j < TOTAL_MOVIES; j++) {

		MovieHolder* mvHolder = new MovieHolder(x_initPos + (x_alignCounter * x_difference), y_initPos, MOVIES_HEIGHT, MOVIES_WIDTH, moviesBrush, movies[j]);
		movieButton[j] = mvHolder;

		if (x_alignCounter == 2) {
			x_alignCounter = 0;
			y_initPos += y_difference;
		}
		else x_alignCounter++;
	}
	
	//---------------------Search---------------------\\

	float yPos = 200;
	float yPosPadding = 70;
	float xPos = 300;
	float textButtonPosx = 235;
	std::string text;

	//Search By TITLE

	//Desc
	graphics::Brush titleDescBrush;
	titleDescBrush.fill_opacity = 0.f;
	titleDescBrush.outline_opacity = 0.f;
	
	graphics::Brush titleDescTextBrush;
	SETCOLOR(titleDescTextBrush.fill_color, 0.f, 0.f, 0.f);
	text = "Search By Title:";

	TextField* titleDescText = new TextField(xPos-10, yPos - 30, 20, 250, titleDescBrush, titleDescTextBrush);
	titleDescText->setText(text);
	titleDescText->setTextSize(15);
	descriptionWidgets[0] = titleDescText;

	//field
	graphics::Brush inputSearchBrush;
	SETCOLOR(inputSearchBrush.fill_color, 0.3f, 0.3f, 0.3f);
	inputSearchBrush.outline_opacity = 1.f;

	graphics::Brush inputSearchTextBrush;
	SETCOLOR(inputSearchTextBrush.fill_color, 1.f, 1.f, 1.f);

	InputTextField* titleInputText = new InputTextField(xPos, yPos, 30, 250, inputSearchBrush, inputSearchTextBrush);
	inputWidgets[0] = titleInputText;
	
	yPos += yPosPadding;

	//Search By GENRE -TO DO when one selected transition from white to black outline
	
	//Desc
	graphics::Brush genreDescBrush;
	genreDescBrush.fill_opacity = 0.f;
	genreDescBrush.outline_opacity = 0.f;

	graphics::Brush genreDescTextBrush;
	SETCOLOR(genreDescTextBrush.fill_color, 0.f, 0.f, 0.f);
	text = "Search By Genre:";

	TextField* genreDescText = new TextField(xPos - 10, yPos - 30, 20, 250, genreDescBrush, genreDescTextBrush);
	genreDescText->setText(text);
	genreDescText->setTextSize(15);
	descriptionWidgets[1] = genreDescText;

	//field

	graphics::Brush genreBrush;

	SETCOLOR(genreBrush.fill_color, 0.8f, 0.8f, 0.8f);
	genreBrush.fill_opacity = 1.f;

	graphics::Brush genreTextBrush;

	SETCOLOR(genreTextBrush.fill_color, 1.f, 1.f, 1.f);

	TextButton* genreDrama = new TextButton(textButtonPosx, yPos, 30, 120, genreBrush, genreTextBrush);
	genreDrama->setText("Drama");
	genreDrama->setCallBackFuction((std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 4, placeholders::_2)));
	genreButtons[0] = genreDrama;

	TextButton* genreHistory = new TextButton(textButtonPosx + 120, yPos, 30, 120, genreBrush, genreTextBrush);
	genreHistory->setText("History");
	genreHistory->setCallBackFuction((std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 4, placeholders::_2)));
	genreButtons[1] = genreHistory;

	yPosPadding = 30;
	yPos += yPosPadding;

	TextButton* genreAdventure = new TextButton(textButtonPosx, yPos, 30, 120, genreBrush, genreTextBrush);
	genreAdventure->setText("Adventure");
	genreAdventure->setCallBackFuction((std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 4, placeholders::_2)));
	genreButtons[2] = genreAdventure;

	TextButton* genreAction = new TextButton(textButtonPosx + 120, yPos, 30, 120, genreBrush, genreTextBrush);
	genreAction->setText("Action");
	genreAction->setCallBackFuction((std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 4, placeholders::_2)));
	genreButtons[3] = genreAction;

	yPos += yPosPadding;

	TextButton* genreCrime = new TextButton(textButtonPosx, yPos, 30, 120, genreBrush, genreTextBrush);
	genreCrime->setText("Crime");
	genreCrime->setCallBackFuction((std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 4, placeholders::_2)));
	genreButtons[4] = genreCrime;

	TextButton* genreFantasy = new TextButton(textButtonPosx + 120, yPos, 30, 120, genreBrush, genreTextBrush);
	genreFantasy->setText("Fantasy");
	genreFantasy->setCallBackFuction((std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 4, placeholders::_2)));
	genreButtons[5] = genreFantasy;

	yPos += yPosPadding;

	TextButton* genreScifi = new TextButton(textButtonPosx, yPos, 30, 120, genreBrush, genreTextBrush);
	genreScifi->setText("Scifi");
	genreScifi->setCallBackFuction((std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 4, placeholders::_2)));
	genreButtons[6] = genreScifi;
	
	yPosPadding = 70;
	yPos += yPosPadding;

	//search by DIRECTOR

	//Desc
	graphics::Brush directortDescBrush;
	directortDescBrush.fill_opacity = 0.f;
	directortDescBrush.outline_opacity = 0.f;

	graphics::Brush directortDescTextBrush;
	SETCOLOR(directortDescTextBrush.fill_color, 0.f, 0.f, 0.f);
	text = "Search By Director:";

	TextField* directortDescText = new TextField(xPos - 10, yPos - 30, 20, 250, directortDescBrush, directortDescTextBrush);
	directortDescText->setText(text);
	directortDescText->setTextSize(15);
	descriptionWidgets[2] = directortDescText;

	//field
	InputTextField* directorInputText = new InputTextField(xPos, yPos, 30, 250, inputSearchBrush, inputSearchTextBrush);
	inputWidgets[1] = directorInputText;
	
	yPos += yPosPadding;

	//search by ACTOR

	//Desc
	graphics::Brush actorDescBrush;
	actorDescBrush.fill_opacity = 0.f;
	actorDescBrush.outline_opacity = 0.f;

	graphics::Brush actorDescTextBrush;
	SETCOLOR(actorDescTextBrush.fill_color, 0.f, 0.f, 0.f);
	text = "Search By Actor:";

	TextField* actorDescText = new TextField(xPos - 10, yPos - 30, 20, 250, actorDescBrush, actorDescTextBrush);
	actorDescText->setText(text);
	actorDescText->setTextSize(15);
	descriptionWidgets[3] = actorDescText;

	//field
	InputTextField* actorInputText = new InputTextField(xPos, yPos, 30, 250, inputSearchBrush, inputSearchTextBrush);
	inputWidgets[2] = actorInputText;

	yPos += yPosPadding;

	//search by Date

	//Desc
	graphics::Brush dateDescBrush;
	dateDescBrush.fill_opacity = 0.f;
	dateDescBrush.outline_opacity = 0.f;

	graphics::Brush dateDescTextBrush;
	SETCOLOR(dateDescTextBrush.fill_color, 0.f, 0.f, 0.f);
	text = "Search By date:";

	TextField* datetDescText = new TextField(xPos - 10, yPos - 30, 20, 250, dateDescBrush, dateDescTextBrush);
	datetDescText->setText(text);
	datetDescText->setTextSize(15);
	descriptionWidgets[4] = datetDescText;

	//field
	InputTextField* dateInputText = new InputTextField(xPos, yPos, 30, 250, inputSearchBrush, inputSearchTextBrush);
	inputWidgets[3] = dateInputText;

	yPos += yPosPadding;

	// search filters actions

	//clear
	TextButton* filterClear = new TextButton(textButtonPosx, yPos, 30, 120, genreBrush, genreTextBrush);
	filterClear->setText("Clear");
	filterClear->setCallBackFuction((std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 6, placeholders::_2)));
	textButtonFilters[0] = filterClear;

	//Search
	TextButton* filterSearch = new TextButton(textButtonPosx + 120, yPos, 30, 120, genreBrush, genreTextBrush);
	filterSearch->setText("Search");
	filterSearch->setCallBackFuction((std::bind(&FilmBrowser::controlBrowser, reinterpret_cast<FilmBrowser*>(graphics::getUserData()), 5, placeholders::_2)));
	textButtonFilters[1] = filterSearch;

}

void FilmBrowser::moveMovieIcons(float y_difference)
{
	for (auto mv : movieButton) {
		float initPosy = mv->getPosY();
		float finalPosy = initPosy + y_difference;
		float posx = mv->getPosX();
		addEvent(new WidgetMovementEvent(posx, initPosy, posx, finalPosy, 0.3f, mv));
	}
}

void FilmBrowser::moveSearcedMoviesIcons(float y_difference)
{
	for (auto mv : searchedMovies) {
		float initPosy = mv->getPosY();
		float finalPosy = initPosy + y_difference;
		float posx = mv->getPosX();
		addEvent(new WidgetMovementEvent(posx, initPosy, posx, finalPosy, 0.3f, mv));
	}
}

void FilmBrowser::processEvents()
{
	for (auto e : events) {
		e->update();
	}
	events.remove_if([](Event* ev) {return !ev->isActive(); });
}

void FilmBrowser::search()
{
	std::vector<std::string> selectedGenres;
	std::string titleInput = ""; 
	std::string directorInput = "";
	std::string yearInput = "";
	std::string actorInput = "";

	// Check if any genre is selected
	if (genreSelectedCounter > 0) {

		// Loop through GenreArray to check which is enabled
		for (int i = 0; i < GENRE_CAT_INT; i++) {

			if (genreButtons[i]->getActive()) {

				std::string txt = genreButtons[i]->getText();
				transform(txt.begin(), txt.end(), txt.begin(), ::toupper);
				selectedGenres.push_back(txt);
			}
		}
	}
	//pernw ta inputs apo ta textfields
	//title
	titleInput = inputWidgets[0]->getText();
	if (inputWidgets[0] && titleInput != "") {
		transform(titleInput.begin(), titleInput.end(), titleInput.begin(), ::toupper);
	}
	//director
	directorInput = inputWidgets[1]->getText();
	if (inputWidgets[1] && directorInput != "") {
		transform(directorInput.begin(), directorInput.end(), directorInput.begin(), ::toupper);
	}
	//actor
	actorInput = inputWidgets[2]->getText();
	if (inputWidgets[2] && actorInput != "") {
		transform(actorInput.begin(), actorInput.end(), actorInput.begin(), ::toupper);
	}
	//year
	yearInput = inputWidgets[3]->getText();
	if (inputWidgets[3] && yearInput != "") {
		transform(yearInput.begin(), yearInput.end(), yearInput.begin(), ::toupper);
	}

	//SEARCH

	for (auto mv : movieButton) {

		if (titleInput != "") {
			std::string title = mv->getMovie()->getTitile();
			transform(title.begin(), title.end(), title.begin(), ::toupper);

			if (title.find(titleInput) == std::string::npos) //an den kanei match to substring
				continue;
		}
		if (directorInput != "") {

			std::string director = mv->getMovie()->getDirector();
			transform(director.begin(), director.end(), director.begin(), ::toupper);

			if (director.find(directorInput) == std::string::npos) //an den kanei match to substring
				continue;
		}
		if (actorInput != "") {

			std::vector<std::string> actor = mv->getMovie()->getActors();
			std::string actorName;

			for (auto& element : actor) {
				actorName = element;
				transform(actorName.begin(), actorName.end(), actorName.begin(), ::toupper);
			}

			if (actorName.find(actorInput) == std::string::npos) //an den kanei match to substring
				continue;
		}

		if (yearInput != "") {

			int year = mv->getMovie()->getYear();
			std::string yearStr = std::to_string(year);

			if (yearStr.find(yearInput) == std::string::npos)
				continue;
		}
		if (!selectedGenres.empty()) {

			//genres are the genre that the movie has
			std::vector <std::string> genres = mv->getMovie()->getGenre();

			for (auto& element : genres) {
				transform(element.begin(), element.end(), element.begin(), ::toupper);
			}
			//seleceted genres are the genre selected from the search .

			bool temp = std::all_of(selectedGenres.begin(), selectedGenres.end(),
				[&genres](const std::string& strSelected) { return std::any_of(genres.begin(), genres.end(),
					[&strSelected](const std::string& strMovieGenre) {return strMovieGenre == strSelected; }); });
			
			if (!temp)
			{
				continue;
			}
		}
		MovieHolder* searchedMv = new MovieHolder(*mv, 0.f, 0.f, MOVIES_HEIGHT, 220);
		searchedMovies.push_back(searchedMv);
	}//end of for
}

void FilmBrowser::sliderUpdate(Slider* slider, float mx, float my, graphics::MouseState& ms)
{
	if (slider->upperButtonIsPreesed(mx, my, ms) && slider->getCurrentRow() > 0) //action to move movie icons up
		slider->getUpperButton()->setButtonPressed(true);
	else
		slider->getUpperButton()->setButtonPressed(false);

	if (slider->downButtonIsPreesed(mx, my, ms) && slider->getCurrentRow() < rows - 2) //action to move movie icons down
		slider->getDownButton()->setButtonPressed(true);
	else
		slider->getDownButton()->setButtonPressed(false);

	slider->update();
}

void FilmBrowser::setState(int val) {
	if (val == 0)
		state = MAIN_MENU;
	else if (val == 1)
		state = SEARCH;
	else
		state = DISPLAY_MOVIE;
}

FilmBrowser::FilmBrowser()
{
	for (int i = 0; i < 2; i++) {
		menuBottoms[i] = nullptr;
	}
	for (int i = 0; i <= TOTAL_MOVIES - 1; i++) {
		movies[i] = nullptr;
	}
	for (int i = 0; i <= TOTAL_MOVIES - 1; i++) {
		movieButton[i] = nullptr;
	}
	for (int i = 0; i < 7; i++) {
		genreButtons[i] = nullptr;
	}
	for (int i = 0; i < 4; i++) {
		inputWidgets[i] = nullptr;
	}
	for (int i = 0; i < 5; i++) {
		descriptionWidgets[i] = nullptr;
	}
	for (int i = 0; i < 2; i++) {
		textButtonFilters[i] = nullptr;
	}
}

FilmBrowser::~FilmBrowser()
{
	for (auto mb : menuBottoms) {
		if (mb) {
			delete mb;
			mb = nullptr;
		}
	}
	for (auto mv : movies) {
		if (mv) {
			delete mv;
			mv = nullptr;
		}
	}
	for (auto mv : movieButton) {
		if (mv) {
			delete mv;
			mv = nullptr;
		}
	}
	if (sliderMainMenu) {
		delete sliderMainMenu;
		sliderMainMenu = nullptr;
	}
	if (sliderSearch) {
		delete sliderSearch;
		sliderSearch = nullptr;
	}
	for (auto txt : genreButtons) {
		if (txt) {
			delete txt;
			txt = nullptr;
		}
	}
	for (auto inputfield : inputWidgets) {
		if (inputfield) {
			delete inputfield;
			inputfield = nullptr;
		}
	}
	for (auto descriptionWidget : descriptionWidgets) {
		if (descriptionWidget) {
			delete descriptionWidget;
			descriptionWidget = nullptr;
		}
	}
	for (auto textButtonFilter : textButtonFilters) {
		if (textButtonFilter) {
			delete textButtonFilter;
			textButtonFilter = nullptr;
		}
	}
	for (auto sMovie : searchedMovies) {
		if (sMovie) {
			delete sMovie;
			sMovie = nullptr;
		}
	}
	
	for (auto tok : tokens) {
		if (tok) {
			delete tok;
			tok = nullptr;
		}
	}
	tokens.clear();

	if (activeInputField) {
		activeInputField = nullptr; //only nullptr because its getting destroyed from its category array/list
	}

	if (displayedMovie) {
		displayedMovie = nullptr; //only nullptr because its getting destroyed from its category array/list
	}

	if (prevDisplayedMovie) {
		prevDisplayedMovie = nullptr; //only nullptr because its getting destroyed from its category array/list
	}

	for (auto ev : events) {
		if (ev) {
			delete ev;
			ev = nullptr;
		}
	}
	events.clear();
}