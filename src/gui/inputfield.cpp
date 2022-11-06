// #include "inputfield.h"

// #include <functional>

// namespace
// {
//   template <class T>
//   bool isMouseTouchingRect(const sf::Event::MouseButtonEvent &mouseButton,
//                            const sf::Rect<T> &bounds)
//   {
//     return (bounds.left <= mouseButton.x && mouseButton.x <= bounds.left + bounds.width &&
//             bounds.top <= mouseButton.y && mouseButton.y <= bounds.top + bounds.height);
//   }
// }

// InputField::InputField(const float &width, const sf::Font &font,
//                        bool clearOnFocus, unsigned int characterSize,
//                        float padding) : m_text("", font, characterSize),
//                                         m_clearOnFocus(clearOnFocus),
//                                         m_oldString(""),
//                                         m_padding(padding),
//                                         m_background({width + m_padding * 2, characterSize + m_padding * 2}),
//                                         m_cursor({1.f, static_cast<float>(characterSize)})
// {
//   m_background.setFillColor(DEFAULT_BACKGROUND_COLOR);
//   m_background.setOutlineColor(DEFAULT_BORDER_COLOR);
//   m_background.setOutlineThickness(DEFAULT_BORDER_THICKNESS);

//   m_text.setFillColor(DEFAULT_TEXT_COLOR);

//   setCursorPos(0);
// }

// void InputField::focus()
// {
//   m_focused = true;

//   if (m_clearOnFocus)
//     setString("");
// }

// void InputField::unfocus()
// {
//   m_focused = false;
//   if (m_submitStringCallback)
//   {
//     m_text.setString(m_submitStringCallback(m_oldString, getString()));
//     m_oldString = m_text.getString();
//   }
// }

// bool InputField::isFocused() const
// {
//   return m_focused;
// }

// void InputField::setCursorPos(std::size_t index)
// {
//   if (index > getTextLength())
//     throw std::out_of_range("Cannot put the cursor to a position bigger than the length of the string!");

//   m_cursorPos = index;
//   m_cursor.setPosition(m_text.findCharacterPos(index).x,
//                        m_background.getPosition().y + m_padding);
//   m_cursorClock.restart();

//   const sf::Vector2f &size = m_background.getSize();
//   if (m_cursor.getPosition().x > size.x - m_padding * 2)
//   {
//     // shift text to left (so the end of the text is viewed)
//     float diff = m_cursor.getPosition().x - size.x + m_padding * 2;
//     m_text.move(-diff, 0);
//     m_cursor.move(-diff, 0);
//   }
//   else if (m_cursor.getPosition().x < 0)
//   {
//     // shift text to right (so the start of the text is viewed)
//     float diff = -m_cursor.getPosition().x;
//     m_text.move(diff, 0);
//     m_cursor.move(diff, 0);
//   }

//   float text_width = m_text.getLocalBounds().width;
//   if (m_text.getPosition().x < 0 &&
//       m_text.getPosition().x + text_width < size.x - m_padding * 2)
//   {
//     float diff = size.x - m_padding * 2 - (m_text.getPosition().x + text_width);
//     m_text.move(diff, 0);
//     m_cursor.move(diff, 0);
//     // if text is smaller than the textbox, force align on left
//     if (text_width < (size.x - m_padding * 2))
//     {
//       diff = -m_text.getPosition().x;
//       m_text.move(diff, 0);
//       m_cursor.move(diff, 0);
//     }
//   }
// }

// std::size_t InputField::getCursorPos() const
// {
//   return m_cursorPos;
// }

// std::size_t InputField::getTextLength() const
// {
//   return getString().getSize();
// }

// bool InputField::clearsOnFocus() const
// {
//   return m_clearOnFocus;
// }

// void InputField::setClearOnFocus(bool clearOnFocus)
// {
//   m_clearOnFocus = clearOnFocus;
// }

// void InputField::setBackgroundTexture(const sf::Texture *texture, bool resetRect)
// {
//   m_background.setTexture(texture, resetRect);
// }

// void InputField::setBackgroundTextureRect(const sf::IntRect &rect)
// {
//   m_background.setTextureRect(rect);
// }

// void InputField::setBackgroundColor(const sf::Color &color)
// {
//   m_background.setFillColor(color);
// }

// void InputField::setOutlineColor(const sf::Color &color)
// {
//   m_background.setOutlineColor(color);
// }

// void InputField::setOutlineThickness(float thickness)
// {
//   m_background.setOutlineThickness(thickness);
// }

// const sf::RectangleShape &InputField::getBackground() const
// {
//   return m_background;
// }

// const sf::String &InputField::getString() const
// {
//   return m_text.getString();
// }

// void InputField::setString(const sf::String &text)
// {
//   m_text.setString(text);
// }

// void InputField::setFont(const sf::Font &font)
// {
//   m_text.setFont(font);
// }

// void InputField::setCharacterSize(unsigned int characterSize)
// {
//   m_text.setCharacterSize(characterSize);
//   m_cursor.setSize({ m_cursor.getSize().x, static_cast<float>(characterSize) });
//   m_background.setSize({m_background.getSize().x, static_cast<float>(characterSize) + m_padding * 2.f});
// }

// void InputField::setLetterSpacing(float spacingFactor)
// {
//   m_text.setLetterSpacing(spacingFactor);
// }

// void InputField::setTextStyle(sf::Uint32 style)
// {
//   m_text.setStyle(style);
// }

// void InputField::setTextFillColor(const sf::Color &color)
// {
//   m_text.setFillColor(color);
// }

// void InputField::setTextOutlineColor(const sf::Color &color)
// {
//   m_text.setOutlineColor(color);
// }

// void InputField::setWidth(float width)
// {
//   m_background.setSize({width + m_padding * 2, m_background.getSize().y});
// }

// void InputField::setCharValidator(std::function<bool(const sf::Uint32 &)> charValidator)
// {
//   m_charValidator = charValidator;
// }

// void InputField::onSubmit(std::function<sf::String(const sf::String &, const sf::String &)> submitStringCallback)
// {
//   m_submitStringCallback = submitStringCallback;
// }

// void InputField::checkEvent(const sf::Event &event)
// {
//   if (event.type == sf::Event::MouseButtonPressed &&
//       event.mouseButton.button == sf::Mouse::Left)
//   {
//     sf::FloatRect bounds = m_background.getGlobalBounds();
//     bounds.left += getPosition().x;
//     bounds.top += getPosition().y;
//     bool touching = isMouseTouchingRect(event.mouseButton, bounds);

//     if (!isFocused() && touching)
//       focus();
//     else if (isFocused() && !touching)
//       unfocus();

//     if (isFocused() && touching)
//     {
//       // put cursor directly before the mouse click
//       for (int i = getTextLength(); i >= 0; --i)
//       {
//         if (m_text.findCharacterPos(i).x <= event.mouseButton.x)
//         {
//           setCursorPos(i);
//           break;
//         }
//       }
//     }
//   }
//   else if (event.type == sf::Event::TextEntered && isFocused())
//   {
//     // ascii characters 32 - 127 are printable
//     // TODO: allow extended ASCII support
//     if (event.text.unicode > 31 && event.text.unicode < 127 &&
//         (m_charValidator && m_charValidator(event.text.unicode)))
//     {
//       sf::String string = getString();
//       string.insert(getCursorPos(), event.text.unicode);
//       setString(string);
//       setCursorPos(getCursorPos() + 1);
//     }
//   }
//   else if (event.type == sf::Event::KeyPressed && isFocused())
//   {
//     switch (event.key.code)
//     {
//     // move the cursor left
//     case sf::Keyboard::Left:
//       if (getCursorPos() > 0)
//         setCursorPos(getCursorPos() - 1);
//       break;

//     // move the cursor right
//     case sf::Keyboard::Right:
//       if (getCursorPos() < getTextLength())
//         setCursorPos(getCursorPos() + 1);
//       break;

//     // delete the character before the cursor
//     case sf::Keyboard::BackSpace:
//       if (getCursorPos() > 0)
//       {
//         sf::String string = getString();
//         string.erase(getCursorPos() - 1);
//         setString(string);

//         setCursorPos(getCursorPos() - 1);
//       }
//       break;

//     // delete the character after the cursor
//     case sf::Keyboard::Delete:
//       if (getCursorPos() < getTextLength())
//       {
//         sf::String string = getString();
//         string.erase(getCursorPos());
//         setString(string);

//         setCursorPos(getCursorPos());
//       }
//       break;

//     // go to the first character
//     case sf::Keyboard::Home:
//       setCursorPos(0);
//       break;

//     // go to the last character
//     case sf::Keyboard::End:
//       setCursorPos(getTextLength());
//       break;

//     // unfocus
//     case sf::Keyboard::Return:
//       unfocus();
//       break;

//     // TODO: implement this after implementing highlighting text
//     // copy highlighted text
//     case sf::Keyboard::C:
//       if (event.key.control)
//       {
//       }
//       break;

//     // TODO: implement this after implementing highlighting text (CTRL+A, select all)
//     // select all text
//     case sf::Keyboard::A:
//       if (event.key.control)
//       {
//       }
//       break;

//     // paste from clipboard after cursor
//     case sf::Keyboard::V:
//       if (event.key.control)
//       {
//         sf::String string = getString();
//         sf::String clipboardString = sf::Clipboard::getString();

//         int valid = 0;
//         if (m_charValidator)
//           for (const char &c : clipboardString)
//             if (!m_charValidator(c))
//             {
//               string.insert(getCursorPos(), c);
//               ++valid;
//             }

//         setString(string);
//         setCursorPos(getCursorPos() + valid);
//       }
//       break;

//     default:
//       break;
//     }
//   }
// }

// void InputField::draw(sf::RenderTarget &target, sf::RenderStates states) const
// {
//   // draw background box
//   states.transform *= getTransform();
//   target.draw(m_background, states);

//   sf::RenderTexture textRender;
//   // add another character of space and allow characters to overflow on the bottom
//   textRender.create(m_background.getSize().x - m_padding * 2 +
//                         m_text.getCharacterSize(),
//                     m_text.getCharacterSize() + m_padding);

//   // not sure why this is needed, but it seems there is a bug where text objs
//   // dont work with sf::Transformable properly
//   sf::Text textCopy(m_text);
//   textCopy.move(-getPosition());

//   textRender.draw(textCopy, states);
//   textRender.display();

//   sf::Sprite textSprite(textRender.getTexture());
//   textSprite.setPosition(m_padding, m_padding);
//   target.draw(textSprite, states);

//   // only show cursor if currently focused
//   if (isFocused())
//   {
//     // time since last blink
//     const sf::Int32 &time = m_cursorClock.getElapsedTime()
//                                 .asMilliseconds() %
//                             (BLINK_RATE * 2);

//     sf::Color color = m_text.getFillColor();
//     color.a = 255 * static_cast<int8_t>(time <= BLINK_RATE);
//     sf::RectangleShape cursorCopy(m_cursor);
//     cursorCopy.move(m_padding, 0);
//     cursorCopy.setFillColor(color);

//     target.draw(cursorCopy, states);
//   }
// }
