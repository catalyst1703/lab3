#include "Rectangle.h"

Rectangle::Rectangle(float width, float height)
{
    rectangle.setSize({ width, height });
    rectangle.setFillColor(color);
    rectangle.setPosition(200, 200);
}

void Rectangle::draw(sf::RenderWindow& window)
{
    if (visible) 
    {
        rectangle.setFillColor(color);
        window.draw(rectangle);
    }
}

void Rectangle::move(float dx, float dy)
{
    rectangle.move(dx, dy);
}

void Rectangle::setPosition(float dx, float dy)
{
    rectangle.setPosition(dx, dy);
}

void Rectangle::resize(float factor)
{
    auto size = rectangle.getSize();
    rectangle.setSize({ size.x * factor, size.y * factor });
}

std::shared_ptr<Figure> Rectangle::clone() const
{
    auto newRectangle = std::make_shared<Rectangle>(*this);
    return newRectangle;
}

sf::FloatRect Rectangle::getBounds()
{
    return rectangle.getGlobalBounds();
}

json Rectangle::toJson() const
{
    return {
            {"type", "Rectangle"},
            {"position", {rectangle.getPosition().x, rectangle.getPosition().y}},
            {"size", {rectangle.getSize().x, rectangle.getSize().y}},
            {"color", {rectangle.getFillColor().r, rectangle.getFillColor().g, rectangle.getFillColor().b, rectangle.getFillColor().a}},
            {"visible", isVisible()}
    };
}

void Rectangle::fromJson(const json& j)
{
    rectangle.setPosition(j.at("position")[0], j.at("position")[1]);
    rectangle.setSize({ j.at("size")[0], j.at("size")[1] });
    setColor(sf::Color(
        j.at("color")[0], j.at("color")[1], j.at("color")[2], j.at("color")[3]
    ));
    visible = j.at("visible");
}
