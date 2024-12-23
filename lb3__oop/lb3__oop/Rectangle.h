#pragma once
#include "Figure.h"
class Rectangle : public Figure {
private:
    sf::RectangleShape rectangle;
public:
    Rectangle(float width = 50.0f, float height = 50.0f);

    void draw(sf::RenderWindow& window) override;

    void move(float dx, float dy) override;

    void setPosition(float dx, float dy) override;

    void resize(float factor) override;

    std::shared_ptr<Figure> clone() const override;

    sf::FloatRect getBounds() override;

    json toJson() const;

    void fromJson(const json& j);
};

