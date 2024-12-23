#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Figure {
protected:
    sf::Color color;
    bool visible;
public:
    Figure() : color(sf::Color::White), visible(true) {}
    virtual ~Figure() = default;

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void move(float dx, float dy) = 0;
    virtual void setPosition(float dx, float dy) = 0;
    virtual void resize(float factor) = 0;
    virtual std::shared_ptr<Figure> clone() const = 0;
    virtual sf::FloatRect getBounds() = 0;
    virtual json toJson() const = 0;
    virtual void fromJson(const json& j) = 0;

    virtual void setColor(const sf::Color& newColor) { color = newColor; }
    virtual void setVisible(bool isVisible) { visible = isVisible; }
    bool isVisible() const { return visible; }
};
