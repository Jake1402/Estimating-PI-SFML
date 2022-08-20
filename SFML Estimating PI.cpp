#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>

/*CREATING SOME A PIS ESTIMATE FUNCTION USING MACROS AND DEFINIG PI VALUE*/
#define PIESTIMATE(NUMIN, NUMOUT) 4*double(NUMIN/(double)(NUMIN + NUMOUT))
#define PI "3.141592653589793238"

/*TELLS ME IF POINTS LIE IN CIRLCE*/
bool inside(sf::Vector2f position, sf::Vector2f origin, double radius) {
    double x = sqrt(pow(position.x - origin.x, 2) + pow(position.y - origin.y, 2));
    if (x < radius) { return true; }
    return false;
}

int main()
{
    /*SETTING UP BOTH WINDOWS SETTING AND LOGIC SETTINGS*/
    srand(time(NULL));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(800, 900), PI, sf::Style::Default, settings);
    window.setFramerateLimit(120);

    /*SETTING UP RECTANGLE WHICH CIRCLE WILL LIE IN*/
    sf::RectangleShape piSquare(sf::Vector2f(780, 780));
    piSquare.setPosition(sf::Vector2f(10, 100));
    piSquare.setFillColor(sf::Color::Black);
    piSquare.setOutlineThickness(10.0f);
    piSquare.setOutlineColor(sf::Color::White);

    /*SETTING UP CIRCLE WHICH WILL LIE IN CIRCLE*/
    sf::CircleShape piCircle(390);
    piCircle.setPointCount(720);
    piCircle.setPosition(10, 100);
    piCircle.setOutlineThickness(10.0f);
    piCircle.setOutlineColor(sf::Color::White);
    piCircle.setFillColor(sf::Color::Black);
    const sf::Vector2f origin(400, 490);

    /*SETTING UP POINTS WHICH WILL HAVE RANDOM POSITION FOR MONTE CARLO METHOD*/
    sf::CircleShape point(5);
    point.setFillColor(sf::Color::Red);
    point.setPosition(sf::Vector2f((rand()%2)*780, 100+(rand()%2)*780));

    /*POSITION VECTOR THAT WILL HOLD THE POSITION OF POINTS*/
    std::vector<sf::Vector2f> pointPosition;
    pointPosition.push_back(sf::Vector2f(((double)(rand()) / (RAND_MAX)) * 780, 100 + (double)((rand()) / (RAND_MAX)) * 780));

    /*SETTING UP TEXT THAT WILL DISPLAY PI ESTIMATE*/
    sf::Text piString;
    sf::Font robotoMono;
    if (!robotoMono.loadFromFile("RobotoMono-Bold.ttf")) {}
    piString.setFont(robotoMono);
    piString.setCharacterSize(60);
    piString.setPosition(sf::Vector2f(10, 10));
    piString.setString("TEST STRING");

    /*MAIN WINDOW LOOP*/
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /*CLEAR AND DRAW SQUARE AND CIRCLE FIRST*/
        window.clear();
        window.draw(piSquare);
        window.draw(piCircle);

        /*LOOP THROUGH ALL POINTS DRAW THEM AND DETERMINE IF THEY'RE IN THE CIRCLE OR NOT*/
        int j = 0, numIn = 0, numOut = 0;
        for (auto i : pointPosition) {
            j++;
            point.setPosition(i);
            window.draw(point);
            if (inside(i, origin, 390)) {
                numIn++;
            }
            else {
                numOut++;
            }
        }
        /*CAP NUMBER OF POINTS TO SAVE FRAMES*/
        if (!(j > 30000)) {
            pointPosition.push_back(sf::Vector2f(
                10  + ((double)(rand()) / (RAND_MAX)) * 780,
                100 + ((double)(rand()) / (RAND_MAX)) * 780
            ));
        }

        /*CALCULATE PI ESTIMATE AND CONVERT IT TO STRING TO DRAW*/
        std::ostringstream ss;
        ss << PIESTIMATE(numIn, numOut);
        piString.setString(ss.str());
        window.draw(piString);
        window.display();
    }

    return 0;
}