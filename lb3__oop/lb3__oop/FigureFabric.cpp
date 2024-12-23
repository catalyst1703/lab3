#include "FigureFabric.h"
std::shared_ptr<Figure> FigureFabric::createFromJson(const json& j) 
{
    std::string type = j.at("type");
    if (type == "Circle") 
    {
        auto circle = std::make_shared<Circle>();
        circle->fromJson(j);
        return circle;
    }
    else if (type == "Rectangle") 
    {
        auto rectangle = std::make_shared<Rectangle>();
        rectangle->fromJson(j);
        return rectangle;
    }
    else if (type == "Triangle") 
    {
        auto triangle = std::make_shared<Triangle>();
        triangle->fromJson(j);
        return triangle;
    }
    else if (type == "AggregateFigure") 
    {
        auto aggregate = std::make_shared<AggregateFigure>();
        aggregate->fromJson(j);
        return aggregate;
    }
}
