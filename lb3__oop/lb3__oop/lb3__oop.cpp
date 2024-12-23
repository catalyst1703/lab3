#include <SFML/Graphics.hpp>
#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
#include "FigureManager.h"
#include <cstdlib> 
#include <ctime>
#include "Triangle.h"

void showHelp() {
    std::cout << "Commands:\n"
        << "F1 - Show this help\n"
        << "1 - Add Circle at mouse position\n"
        << "2 - Add Rectangle at mouse position\n"
        << "Tab - Switch active figure\n"
        << "Arrow Keys - Move active figure\n"
        << "+/- - Resize active figure\n"
        << "C - Change active figure color\n"
        << "V - Toggle visibility of active figure\n"
        << "S - Save configuration\n"
        << "L - Load configuration\n"
        << "B - (Un)Select figure for aggrigation\n"
        << "N - Make an aggrigate\n"
        << "Esc - Exit\n";
}

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Polymorphism Project");
    FigureManager manager;
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    showHelp();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
                

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code)
                {
                case sf::Keyboard::F1:
                {
                    showHelp();
                    break;
                }
                case sf::Keyboard::Num1:
                {
                    auto position = sf::Mouse::getPosition(window);
                    auto circle = std::make_shared<Circle>();
                    circle->setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
                    manager.addFigure(circle);
                    break;
                }
                case sf::Keyboard::Num2:
                {
                    auto position = sf::Mouse::getPosition(window);
                    auto rectangle = std::make_shared<Rectangle>();
                    rectangle->setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
                    manager.addFigure(rectangle);
                    break;
                }
                case sf::Keyboard::Num3:
                {
                    auto position = sf::Mouse::getPosition(window);
                    auto triangle = std::make_shared<Triangle>();
                    triangle->setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
                    manager.addFigure(triangle);
                    break;
                }
                case sf::Keyboard::Tab:
                {
                    manager.nextFigure();
                    break;
                }
                case sf::Keyboard::Up:
                {
                    auto figure = manager.getActiveFigure();
                    if (figure)
                    {
                        manager.moveFigure(figure, 0, -10, window);
                    }
                    break;
                }
                case sf::Keyboard::Down:
                {
                    auto figure = manager.getActiveFigure();
                    if (figure)
                    {
                        manager.moveFigure(figure, 0, 10, window);
                    }
                    break;
                }
                case sf::Keyboard::Left:
                {
                    auto figure = manager.getActiveFigure();
                    if (figure)
                    {
                        manager.moveFigure(figure, -10, 0, window);
                    }
                    break;
                }
                case sf::Keyboard::Right:
                {
                    auto figure = manager.getActiveFigure();
                    if (figure)
                    {
                        manager.moveFigure(figure, 10, 0, window);
                    }
                    break;
                }
                case sf::Keyboard::Add:
                {
                    auto figure = manager.getActiveFigure();
                    if (figure)
                    {
                        figure->resize(1.1f);
                    }
                    break;
                }
                case sf::Keyboard::Subtract:
                {
                    auto figure = manager.getActiveFigure();
                    if (figure)
                    {
                        figure->resize(0.9f);
                    }
                    break;
                }
                case sf::Keyboard::C:
                {
                    auto figure = manager.getActiveFigure();
                    if (figure)
                    {
                        figure->setColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
                    }
                    break;
                }
                case sf::Keyboard::V:
                {
                    auto figure = manager.getActiveFigure();
                    if (figure)
                    {
                        figure->setVisible(!figure->isVisible());
                    }
                    break;
                }
                case sf::Keyboard::S:
                {
                    std::cout << "Enter filename to save (e.g., config.json): ";
                    std::string filename;
                    std::cin >> filename;
                    manager.saveToFile(filename);
                    break;
                }
                case sf::Keyboard::B:
                {
                    manager.toggleFigureForAggregation();
                    break;
                }
                case sf::Keyboard::N:
                {
                    manager.aggregateFigures();
                    break;
                }
                case sf::Keyboard::L:
                {
                    std::cout << "Enter filename to load (e.g., config.json): ";
                    std::string filename;
                    std::cin >> filename;
                    manager.loadFromFile(filename); 
                    break;
                }
                case sf::Keyboard::Escape:
                {
                    window.close();
                    break;
                }
                }
               
               
            }
            //.moveFigures(window);
            manager.handleCollisions();
        }

        window.clear();
        manager.drawFigures(window);
        window.display();
    }

    return 0;
}
