// OLD GUI!

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "inputfield.h"

#include "../path/pathbuilder.h"
#include "../path/path.h"

sf::Color gradient(double val)
{
  return sf::Color(0, 0, (1 - val) * 255);
}

// 5 millimeters = 1 pixel
// NOTE: after changing this value, the image field.png
// MUST be resized from field-full.png to fieldSize * pixelsPerMM.
const double pixelsPerMM = 0.2;

float toPixels(long double mm)
{
  return mm * pixelsPerMM;
}

const double fieldSize = toPixels(Waypoint::maxCoord * 2),
             maxCoord = toPixels(Waypoint::maxCoord),
             minCoord = toPixels(Waypoint::minCoord);

const double windowSize = fieldSize;
const double sidebarSize = 200;
const double axisWidth = 4;

const sf::Color backColor{20, 20, 20};
const sf::Color accentColor{40, 40, 40};

std::string doubleToString(double value, int digits = -1)
{
  std::string str = std::to_string(value);
  std::size_t decimal = str.find('.');
  if (digits == -1)
    str.erase(std::max(str.find_last_not_of('0') + 1,
                       decimal == std::string::npos ? 0 : decimal + 3),
              std::string::npos);
  else
    str.erase(decimal + digits + 1, std::string::npos);
  return str;
}

//int main()
int run()
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(windowSize + sidebarSize, windowSize),
                          "VRC Team 5327K's Path Planner",
                          sf::Style::Titlebar | sf::Style::Close,
                          settings);

  window.setVerticalSyncEnabled(true);

  const sf::Vector2f center{windowSize / 2, windowSize / 2};

  sf::RectangleShape xAxis({fieldSize, axisWidth});
  xAxis.setOrigin(Waypoint::maxCoord, axisWidth / 2);
  xAxis.setPosition(center);
  xAxis.setFillColor(accentColor);

  sf::RectangleShape yAxis({axisWidth, fieldSize});
  yAxis.setOrigin(axisWidth / 2, maxCoord);
  yAxis.setPosition(center);
  yAxis.setFillColor(accentColor);

  sf::Texture fieldTex;
  if (!fieldTex.loadFromFile("src/gui/assets/field.png"))
    throw "Could not load field PNG file!";
  fieldTex.setSmooth(true);

  sf::RenderTexture fieldRenderTex;
  fieldRenderTex.create(fieldTex.getSize().x, fieldTex.getSize().y);
  fieldRenderTex.clear({0, 0, 0});

  sf::Sprite fieldSprite;
  fieldSprite.setOrigin(maxCoord, maxCoord);
  fieldSprite.setPosition({maxCoord, maxCoord});
  fieldSprite.setTexture(fieldTex);
  fieldSprite.setColor({255, 255, 255, 150});
  fieldRenderTex.draw(fieldSprite);

  fieldRenderTex.display();
  sf::Sprite field(fieldRenderTex.getTexture());
  field.setOrigin({maxCoord, maxCoord});
  field.setPosition(center);

  sf::RectangleShape sidebar({sidebarSize, windowSize});
  sidebar.setOrigin({sidebarSize / 2, windowSize / 2});
  sidebar.setPosition({windowSize + sidebarSize / 2, windowSize / 2});
  sidebar.setFillColor(accentColor);

  // TODO
  std::vector<Waypoint> points = {{1030, 1505}, {-195, 465}, {1570, -770}, {1550, 1005}};

  sf::CircleShape pointShape;
  pointShape.setOrigin({2.5, 2.5});
  pointShape.setFillColor({255, 0, 0});
  pointShape.setOutlineColor({255, 255, 255});

  sf::CircleShape pathPointShape(3);
  pathPointShape.setOrigin({1.5, 1.5});
  pathPointShape.setFillColor({0, 0, 255});

  sf::Font font;
  if (!font.loadFromFile("src/gui/assets/OpenSans-Regular.ttf"))
    throw "Could not open font file!";

  bool inputFieldYFocus = false;

  int selected = 0;
  bool dragging = false;

  sf::Text xText("X: ", font);
  xText.setFillColor(sf::Color::White);
  xText.setPosition({fieldSize + 10, 8});

  InputField inputFieldX(125, font);
  inputFieldX.setString(doubleToString(points[selected].x));
  inputFieldX.setPosition({fieldSize + 35, 0});
  inputFieldX.setBackgroundColor(accentColor);
  inputFieldX.setTextFillColor(sf::Color::White);
  // numbers are ascii codes 48 - 57, minus is 45, decimal is 46
  inputFieldX.setCharValidator([](sf::Uint32 ch)
                               { return (ch == 45) || (ch == 46) || (48 <= ch && ch <= 57); });

  inputFieldX.onSubmit([&](const sf::String &oldStr, const sf::String &newStr)
                       {
    try
    {
      // make sure the coordinates are valid; if they aren't, clamp them
      points[selected].x = std::clamp(std::stod(newStr.toAnsiString()), Waypoint::minCoord, Waypoint::maxCoord);
    }
    catch(const std::invalid_argument &e)
    { return oldStr; }
    catch (const std::out_of_range &e)
    { return oldStr; }
  
    return sf::String(doubleToString(points[selected].x)); });

  sf::Text yText("Y: ", font);
  yText.setFillColor(sf::Color::White);
  yText.setPosition({fieldSize + 10, 48});

  InputField inputFieldY(125, font);
  inputFieldY.setString(doubleToString(points[selected].y));
  inputFieldY.setPosition({fieldSize + 35, 40});
  inputFieldY.setBackgroundColor(accentColor);
  inputFieldY.setTextFillColor(sf::Color::White);
  // numbers are ascii codes 48 - 57, minus is 45, decimal is 46
  inputFieldY.setCharValidator([](sf::Uint32 ch)
                               { return (ch == 45) || (ch == 46) || (48 <= ch && ch <= 57); });

  inputFieldY.onSubmit([&](const sf::String &oldStr, const sf::String &newStr)
                       {
    try
    {
      // make sure the coordinates are valid; if they aren't, clamp them
      points[selected].x = std::clamp(std::stod(newStr.toAnsiString()), Waypoint::minCoord, Waypoint::maxCoord);
    }
    catch(const std::invalid_argument &e)
    { return oldStr; }
    catch (const std::out_of_range &e)
    { return oldStr; }
  
    return sf::String(doubleToString(points[selected].y)); });

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
        break;
      }

      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left)
      {
        for (int i = 0; i < points.size(); ++i)
        {
          const double locX = points[i].x * pixelsPerMM + windowSize / 2,
                       locY = points[i].y * pixelsPerMM + windowSize / 2;

          if (locX - 7 <= event.mouseButton.x && event.mouseButton.x <= locX + 7 &&
              locY - 7 <= event.mouseButton.y && event.mouseButton.y <= locY + 7)
          {
            selected = i;
            dragging = true;
            inputFieldX.setString(doubleToString(points[selected].x));
            inputFieldY.setString(doubleToString(points[selected].y));
            break;
          }
        }
      }

      if (event.type == sf::Event::MouseMoved && dragging)
      {
        points[selected].x = std::clamp((static_cast<double>(event.mouseMove.x) - windowSize / 2) / pixelsPerMM, Waypoint::minCoord, Waypoint::maxCoord);
        inputFieldX.setString(doubleToString(points[selected].x));
        points[selected].y = std::clamp((static_cast<double>(event.mouseMove.y) - windowSize / 2) / pixelsPerMM, Waypoint::minCoord, Waypoint::maxCoord);
        inputFieldY.setString(doubleToString(points[selected].y));
      }

      if (event.type == sf::Event::MouseButtonReleased &&
          event.mouseButton.button == sf::Mouse::Left)
      {
        if (dragging)
          dragging = false;
      }

      inputFieldX.checkEvent(event);
      inputFieldY.checkEvent(event);
    }

    window.clear(backColor);

    window.draw(field);
    window.draw(xAxis);
    window.draw(yAxis);

    window.draw(sidebar);

    const double maxV = 150;

    const Path path = PathBuilder(true, maxV, 1, 3)
                          .addPoints(points)
                          .build();

    for (const auto &point : path.path)
    {
      pathPointShape.setPosition({static_cast<float>(round(point.x * pixelsPerMM + windowSize / 2)),
                                  static_cast<float>(round(point.y * pixelsPerMM + windowSize / 2))});
      pathPointShape.setFillColor(gradient(point.targetV / maxV));
      window.draw(pathPointShape);
    }

    for (int i = 0; i < points.size(); ++i)
    {
      pointShape.setPosition({static_cast<float>(round(points[i].x * pixelsPerMM + windowSize / 2)),
                              static_cast<float>(round(points[i].y * pixelsPerMM + windowSize / 2))});

      if (i == 0)
      {
        pointShape.setFillColor({0, 255, 0});
        pointShape.setRadius(5);
      }
      else if (i == points.size() - 1)
      {
        pointShape.setFillColor({255, 0, 0});
        pointShape.setRadius(5);
      }
      else
      {
        pointShape.setFillColor({255, 255, 0});
        pointShape.setRadius(4);
      }

      if (i == selected)
        pointShape.setOutlineThickness(2);
      else
        pointShape.setOutlineThickness(0);

      window.draw(pointShape);
    }

    window.draw(xText);
    window.draw(inputFieldX);

    window.draw(yText);
    window.draw(inputFieldY);

    window.display();
  }

  return 0;
}
