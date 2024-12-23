#pragma once
#include "AggregateFigure.h"
#include <cstdlib> 
#include <ctime>
#include "fstream"
#include <iostream>
#include <memory>
#include "FigureFabric.h"

class FigureManager {
private:
    std::vector<std::shared_ptr<Figure>> figures;
    int currentIndex = 0;
    std::vector<std::shared_ptr<Figure>> selectedFigures; // Список вибраних фігур для агрегації

public:
    void addFigure(const std::shared_ptr<Figure>& figure);
    

    void nextFigure();

   // void selectFigureForAggregation();
    

    void aggregateFigures();

    void drawFigures(sf::RenderWindow& window);

    void moveFigures(const sf::RenderWindow& window);

    std::shared_ptr<Figure> getActiveFigure();

    void toggleFigureForAggregation();

    void moveFigure(std::shared_ptr<Figure> figure, float dx, float dy, const sf::RenderWindow& window);

    bool checkCollision(const sf::FloatRect& a, const sf::FloatRect& b);

    void handleCollisions();

    json toJson() const;

    void fromJson(const json& j);

    void saveToFile(const std::string& filename) const;

    void loadFromFile(const std::string& filename);
};