#pragma once
#include "Figure.h"
class Triangle : public Figure {
private:
    sf::ConvexShape triangle;
    bool visible = true;

public:
    Triangle();

    void draw(sf::RenderWindow& window) override;

    void move(float dx, float dy) override;

    void setPosition(float dx, float dy) override;

    void resize(float factor) override;

    std::shared_ptr<Figure> clone() const override;

    sf::FloatRect getBounds() override;

    json toJson() const override;

    void fromJson(const json& j) override;
};
