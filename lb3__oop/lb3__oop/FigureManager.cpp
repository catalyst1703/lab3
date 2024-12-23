#include "FigureManager.h"

void FigureManager::addFigure(const std::shared_ptr<Figure>& figure)
{
	figures.push_back(figure);
}

void FigureManager::nextFigure()
{
	if (figures.empty())
	{
		return;
	}
	currentIndex = (currentIndex + 1) % figures.size();
}

void FigureManager::aggregateFigures()
{
    if (selectedFigures.size() < 2) 
    {
        return;
    }

    auto aggregate = std::make_shared<AggregateFigure>();

    for (auto& figure : selectedFigures) 
    {
        aggregate->addFigure(figure->clone());
    }

    figures.push_back(aggregate);

    selectedFigures.clear();
}

void FigureManager::drawFigures(sf::RenderWindow& window)
{
    for (auto& figure : figures) 
    {
        if (figure->isVisible()) 
        {
            figure->draw(window);
        }
    }
}

void FigureManager::moveFigures(const sf::RenderWindow& window)
{
    srand(time(NULL));
    for (auto& figure : figures) 
    {
        moveFigure(figure, rand() % 10 - 5, rand() % 10 - 5, window);
    }
}

std::shared_ptr<Figure> FigureManager::getActiveFigure()
{
    if (!figures.empty()) {
        return figures[currentIndex];
    }
    return nullptr;
}

void FigureManager::toggleFigureForAggregation()
{
    auto activeFigure = getActiveFigure();
    if (!activeFigure)
    {
        return;
    }

    auto it = std::find(selectedFigures.begin(), selectedFigures.end(), activeFigure);
    if (it != selectedFigures.end()) 
    {
        selectedFigures.erase(it);
    }
    else 
    {
        selectedFigures.push_back(activeFigure);
    }
}

void FigureManager::moveFigure(std::shared_ptr<Figure> figure, float dx, float dy, const sf::RenderWindow& window)
{
    if (!figure)
    {
        return;
    }

    auto bounds = figure->getBounds();
    auto windowSize = window.getSize();

    float newLeft = bounds.left + dx;
    float newTop = bounds.top + dy;

    if (newLeft < 0)
    {
        dx = -bounds.left;
    }
    if (newTop < 0)
    {
        dy = -bounds.top;
    }
    if (newLeft + bounds.width > windowSize.x)
    {
        dx = windowSize.x - (bounds.left + bounds.width);
    }
    if (newTop + bounds.height > windowSize.y)
    {
        dy = windowSize.y - (bounds.top + bounds.height); 
    }

    figure->move(dx, dy);
}

bool FigureManager::checkCollision(const sf::FloatRect& a, const sf::FloatRect& b)
{
    return a.intersects(b);
}

void FigureManager::handleCollisions()
{
    for (size_t i = 0; i < figures.size(); ++i) 
    {
        for (size_t j = i + 1; j < figures.size(); ++j) 
        {
            if (figures[i]->isVisible() && figures[j]->isVisible() &&
                checkCollision(figures[i]->getBounds(), figures[j]->getBounds())) 
            {
                figures[i]->resize(0.99);
                figures[j]->resize(0.99);
            }
        }
    }
}

json FigureManager::toJson() const
{
    json figuresArray = json::array();
    for (const auto& figure : figures) 
    {
        figuresArray.push_back(figure->toJson());
    }
    return figuresArray;
}

void FigureManager::fromJson(const json& j)
{
    figures.clear();
    for (const auto& figureJson : j) 
    {
        figures.push_back(FigureFabric::createFromJson(figureJson));
    }
}

void FigureManager::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (file.is_open()) 
    {
        file << toJson().dump(4);
    }
}

void FigureManager::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        json j;
        file >> j;
        fromJson(j);
    }
   
}