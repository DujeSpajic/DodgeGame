#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include <fstream>
using namespace sf;
using namespace std;

class Utils // singleton global class
{
    sf::Clock deltaClock;
public:
    sf::RenderWindow* window;
    Font* font;

    float deltaTime;
    bool gameOver = false;
    Screen* currentGame;

    void init() {

        srand(time(NULL));
        window->setFramerateLimit(60);
        font = new sf::Font();
        if (!font->loadFromFile("assets/font.ttf"))
        {
            printf("error\n");
        }
    }
    //izracun delta vremena
    void tickClock() {
        sf::Time dt = deltaClock.restart();
        deltaTime = dt.asSeconds();
    }

    //izgled texta,boja itd...

    void showText(string str, int x, int y, int size, Color color = { 233,233,233 }) {
        sf::Text text;
        text.setFont(*font);
        text.setFillColor(color);
        text.setCharacterSize(size);
        text.setString(str);
        text.setPosition(Vector2f(x, y));
        window->draw(text);
    }
    //dodaje score u datoteku
    void saveScore(int score) {
        std::ofstream outfile;

        outfile.open("score.txt", std::ios_base::app);
        outfile << score << "\n";
        outfile.close();
    }
    //ucitavanje rezultata iz datoteke
    vector<int> readScores() {
        vector<int>scores;
        std::ifstream file("score.txt");
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                //atoi pretvara linije iz datoteke u int i dodaje u vektor
                scores.push_back(atoi(line.c_str()));
            }
            file.close();
        }
        return scores;
    }
    //racuna distancu izmedu dvije tocku , pitag poucak
    float distance(float x1, float y1, float x2, float y2) {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
    }
    //random float generator
    static float randomFloat(float a, float b) {
        float random = ((float)rand()) / (float)RAND_MAX;
        float diff = b - a;
        float r = random * diff;
        return a + r;
    }
    //random int generator
    static int randomInt(int a, int b) {
        return a + (std::rand() % (b - a + 1));
    }
    //osiigurava da je samo jedna instanca klase utils
    static Utils& get() {
        static Utils INSTANCE;
        return INSTANCE;
    }
};


