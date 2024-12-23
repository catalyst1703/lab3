#include "Triangle.h"

Triangle::Triangle()
{
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.f, -25.f));
    triangle.setPoint(1, sf::Vector2f(-25.f, 25.f));
    triangle.setPoint(2, sf::Vector2f(25.f, 25.f));
    triangle.setFillColor(sf::Color::White);
    triangle.setPosition(400.f, 300.f);
}

void Triangle::draw(sf::RenderWindow& window)
{
    if (visible) {
        triangle.setFillColor(color);
        window.draw(triangle);
    }
}

void Triangle::move(float dx, float dy)
{
    triangle.move(dx, dy);
}

void Triangle::setPosition(float dx, float dy)
{
    triangle.setPosition(dx, dy);
}

void Triangle::resize(float factor)
{
    triangle.scale(factor, factor);
}

std::shared_ptr<Figure> Triangle::clone() const
{
    auto newTriangle = std::make_shared<Triangle>(*this);
    return newTriangle;
}

sf::FloatRect Triangle::getBounds()
{
    return triangle.getGlobalBounds();
}

json Triangle::toJson() const
{
    return {
            {"type", "Triangle"},
            {"position", {triangle.getPosition().x, triangle.getPosition().y}},
            {"points", {
                {triangle.getPoint(0).x, triangle.getPoint(0).y},
                {triangle.getPoint(1).x, triangle.getPoint(1).y},
                {triangle.getPoint(2).x, triangle.getPoint(2).y}
            }},
            {"color", {triangle.getFillColor().r, triangle.getFillColor().g, triangle.getFillColor().b, triangle.getFillColor().a}},
            {"visible", isVisible()}
    };
}

void Triangle::fromJson(const json& j)
{
    triangle.setPosition(j.at("position")[0], j.at("position")[1]);

    triangle.setPoint(0, sf::Vector2f(j.at("points")[0][0], j.at("points")[0][1]));
    triangle.setPoint(1, sf::Vector2f(j.at("points")[1][0], j.at("points")[1][1]));
    triangle.setPoint(2, sf::Vector2f(j.at("points")[2][0], j.at("points")[2][1]));

    setColor(sf::Color(
        j.at("color")[0], j.at("color")[1], j.at("color")[2], j.at("color")[3]
    ));

    visible = j.at("visible");
}
