#pragma once
#include <string>
#include <vector>
using namespace std;

class Movie {
private:
	 std::string title;
	 std::string director;
	 std::vector<std::string> actors;
	 std::vector<std::string> genre;
	 int year;
	 std::string displayImage;
	 std::string description;

public:
	Movie(const string& t, const string& dir, string *actorsAr, int sizeActors, string* genreAr, int sizeGenre, int y, const string& imageName, const string &desc) :
		 title(t),director(dir), year(y), displayImage(imageName), description(desc) {
		setActors(actorsAr, sizeActors);
		setGenre(genreAr, sizeGenre);
	}
	//setters
	void setTitle(const std::string& t) { title = t; }
	void setDisplayImage(const std::string& di){ displayImage = di; }
	void setDirector(const std::string& dir) { director = dir; }
	void setDiscription(const std::string& disc) { description = disc; }
	void setYear(int y) { year = y; }
	void setActors(const std::string *actorsAr, int size) {
		for (int i = 0; i < size; i++) {
			actors.push_back(actorsAr[i]);
		}
	}
	void setGenre(const std::string* genreAr, int size) {
		for (int i = 0; i < size; i++) {
			genre.push_back(genreAr[i]);
		}
	}
	//getters
	std::string getTitile() const { return title; }
	std::string getDirector() const { return director; }
	std::vector<std::string> getActors() const { return actors; }
	std::vector<std::string> getGenre() const {return genre;}
	std::string getDescription() const { return description; }
	int getYear() const { return year; }
	std::string getDisplayImage() const { return displayImage; }

	std::string getActorsToText() const{
		std::string text = "";
		for (std::string act : actors) 
			text += act + "  ";
		return text;
	}

	std::string getGenreToText() const {
		std::string text = "";
		for (std::string gen : genre)
			text += gen + "  ";
		return text;
	}

};
