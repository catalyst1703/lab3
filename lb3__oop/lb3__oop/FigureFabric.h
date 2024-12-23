#pragma once
#include "Figure.h"
#include <memory>
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "AggregateFigure.h"

class FigureFabric
{
public:
    static std::shared_ptr<Figure> createFromJson(const json& j);
};



