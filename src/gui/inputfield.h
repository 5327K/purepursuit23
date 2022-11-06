// #ifndef INPUT_FIELD_H
// #define INPUT_FIELD_H

// #include <SFML/Graphics.hpp>
// #include <functional>

// class InputField : public sf::Drawable, public sf::Transformable
// {
// private:
//   const sf::Int32 BLINK_RATE = 530;
//   const sf::Color DEFAULT_BACKGROUND_COLOR = sf::Color::White;
//   const sf::Color DEFAULT_BORDER_COLOR = sf::Color::Blue;
//   const float DEFAULT_BORDER_THICKNESS = 0;
//   const sf::Color DEFAULT_TEXT_COLOR = sf::Color::Black;

//   std::function<bool(const sf::Uint32 &)> m_charValidator;
//   std::function<sf::String(const sf::String &, const sf::String &)> m_submitStringCallback;

//   sf::String m_oldString;
//   sf::Text m_text;

//   const float m_padding;
//   sf::RectangleShape m_background;

//   size_t m_cursorPos = 0;
//   sf::RectangleShape m_cursor;
//   sf::Clock m_cursorClock;

//   bool m_focused = false;

//   sf::Vector2f m_position;

//   bool m_clearOnFocus = false;

// public:
//   InputField(const float &width, const sf::Font &font,
//              bool clearOnFocus = false, unsigned int characterSize = 30u,
//              float padding = 8);

//   void focus();
//   void unfocus();
//   bool isFocused() const;

//   void setCursorPos(std::size_t index);
//   std::size_t getCursorPos() const;
//   std::size_t getTextLength() const;

//   bool clearsOnFocus() const;
//   void setClearOnFocus(bool clearOnFocus);

//   // background setters and getters

//   void setBackgroundTexture(const sf::Texture *texture, bool resetRect = false);
//   void setBackgroundTextureRect(const sf::IntRect &rect);
//   void setBackgroundColor(const sf::Color &color);
//   void setOutlineColor(const sf::Color &color);
//   void setOutlineThickness(float thickness);

//   const sf::RectangleShape &getBackground() const;

//   // text getters and setters

//   const sf::String &getString() const;
//   void setString(const sf::String &text);

//   void setFont(const sf::Font &font);
//   void setCharacterSize(unsigned int characterSize);
//   // TODO: add functionality for multiple lines
//   // void setLineSpacing(float spacingFactor);
//   void setLetterSpacing(float spacingFactor);
//   void setTextStyle(sf::Uint32 style);
//   void setTextFillColor(const sf::Color &color);
//   void setTextOutlineColor(const sf::Color &color);

//   const sf::Text &getText() const;

//   void setWidth(float width);

//   void setCharValidator(std::function<bool(const sf::Uint32 &)> charValidator);
//   void onSubmit(std::function<sf::String(const sf::String &, const sf::String &)> submitStringCallback);

//   void checkEvent(const sf::Event &event);
//   void draw(sf::RenderTarget &target, sf::RenderStates states) const;
// };

// #endif // INPUT_FIELD_H
