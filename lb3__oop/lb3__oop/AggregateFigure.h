
#pragma once
#include <vector>
#include <memory>
#include "Figure.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "FigureFabric.h"


class AggregateFigure : public Figure {
private:
    std::vector<std::shared_ptr<Figure>> figures;
    sf::FloatRect unionRect(const sf::FloatRect& a, const sf::FloatRect& b);

public:
    void addFigure(const std::shared_ptr<Figure>& figure);

    void draw(sf::RenderWindow& window) override;

    void setPosition(float x, float y) override;

    void resize(float factor) override;

    void move(float dx, float dy) override;

    void setVisible(bool isVisible) override;

    void setColor(const sf::Color& newColor) override;

    std::shared_ptr<Figure> clone() const override;

    sf::FloatRect getBounds()  override;

    json toJson() const;

    void fromJson(const json& j);
   
};


