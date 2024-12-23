#include "AggregateFigure.h"
#include "FigureFabric.h"

void AggregateFigure::addFigure(const std::shared_ptr<Figure>& figure)
{
    figures.push_back(figure);
}

void AggregateFigure::draw(sf::RenderWindow& window)
{
    if (visible)
    {
        for (auto& figure : figures)
        {
            figure->draw(window);
        }
    }
}

void AggregateFigure::setPosition(float x, float y)
{
    for (auto& figure : figures)
    {
        figure->setPosition(x, y);
    }
}

void AggregateFigure::resize(float factor)
{
    for (auto& figure : figures) 
    {
        figure->resize(factor);
    }
}

void AggregateFigure::move(float dx, float dy)
{
    for (auto& figure : figures) 
    {
        figure->move(dx, dy);
    }
}

void AggregateFigure::setVisible(bool isVisible)
{
    for (auto& figure : figures) 
    {
        figure->setVisible(isVisible);
    }
}

void AggregateFigure::setColor(const sf::Color& newColor)
{
    for (auto& figure : figures) 
    {
        figure->setColor(newColor);
    }
}

std::shared_ptr<Figure> AggregateFigure::clone() const
{
    auto newAggregate = std::make_shared<AggregateFigure>();

    for (const auto& figure : figures)
    {
        newAggregate->addFigure(figure->clone());
    }

    return newAggregate;
}

sf::FloatRect AggregateFigure::getBounds()
{
    if (figures.empty())
    {
        return sf::FloatRect(0, 0, 0, 0);
    }

    sf::FloatRect bounds = figures.front()->getBounds();

    for (size_t i = 1; i < figures.size(); ++i) 
    {
        bounds = unionRect(bounds, figures[i]->getBounds());
    }

    return bounds;
}

json AggregateFigure::toJson() const
{
    json figuresArray = json::array();
    for (const auto& figure : figures) {
        figuresArray.push_back(figure->toJson());
    }

    return {
        {"type", "AggregateFigure"},
        {"figures", figuresArray},
        {"visible", isVisible()}
    };
}

sf::FloatRect AggregateFigure::unionRect(const sf::FloatRect& a, const sf::FloatRect& b)
{
    float left = std::min(a.left, b.left);
    float top = std::min(a.top, b.top);
    float right = std::max(a.left + a.width, b.left + b.width);
    float bottom = std::max(a.top + a.height, b.top + b.height);

    return sf::FloatRect(left, top, right - left, bottom - top);
}

void AggregateFigure::fromJson(const json& j) {
    visible = j.at("visible");
    for (const auto& figureJson : j.at("figures")) 
    {
        auto figure = FigureFabric::createFromJson(figureJson);
        addFigure(figure);
    }
}
