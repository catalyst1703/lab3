#include "Circle.h"

Circle::Circle(float radius)
{
    circle.setRadius(radius);
    circle.setFillColor(color);
    circle.setPosition(100, 100);
}

void Circle::draw(sf::RenderWindow& window)
{
    if (visible) 
    {
        circle.setFillColor(color);
        window.draw(circle);
    }
}

void Circle::move(float dx, float dy)
{
    circle.move(dx, dy);
}

void Circle::setPosition(float dx, float dy)
{
    circle.setPosition(dx, dy);
}

void Circle::resize(float factor)
{
    float newRadius = circle.getRadius() * factor;
    circle.setRadius(newRadius);
}

std::shared_ptr<Figure> Circle::clone() const
{
    auto newCircle = std::make_shared<Circle>(*this);
    return newCircle;
}

sf::FloatRect Circle::getBounds()
{
    return circle.getGlobalBounds();
}

json Circle::toJson() const
{
    return {
            {"type", "Circle"},
            {"position", {circle.getPosition().x, circle.getPosition().y}},
            {"radius", circle.getRadius()},
            {"color", {circle.getFillColor().r, circle.getFillColor().g, circle.getFillColor().b, circle.getFillColor().a}},
            {"visible", isVisible()}
    };
}

void Circle::fromJson(const json& j)
{
    circle.setPosition(j.at("position")[0], j.at("position")[1]);
    circle.setRadius(j.at("radius"));
    setColor(sf::Color(
        j.at("color")[0], j.at("color")[1], j.at("color")[2], j.at("color")[3]
    ));
    visible = j.at("visible");
}
