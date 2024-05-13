#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "../../TList.h"
#include "../Utilities/Event.h"

enum KeyCode
{
    Unknown = -1, //!< Unhandled key
    A = 0,        //!< The A key
    B,            //!< The B key
    C,            //!< The C key
    D,            //!< The D key
    E,            //!< The E key
    F,            //!< The F key
    G,            //!< The G key
    H,            //!< The H key
    I,            //!< The I key
    J,            //!< The J key
    K,            //!< The K key
    L,            //!< The L key
    M,            //!< The M key
    N,            //!< The N key
    O,            //!< The O key
    P,            //!< The P key
    Q,            //!< The Q key
    R,            //!< The R key
    S,            //!< The S key
    T,            //!< The T key
    U,            //!< The U key
    V,            //!< The V key
    W,            //!< The W key
    X,            //!< The X key
    Y,            //!< The Y key
    Z,            //!< The Z key
    Num0,         //!< The 0 key
    Num1,         //!< The 1 key
    Num2,         //!< The 2 key
    Num3,         //!< The 3 key
    Num4,         //!< The 4 key
    Num5,         //!< The 5 key
    Num6,         //!< The 6 key
    Num7,         //!< The 7 key
    Num8,         //!< The 8 key
    Num9,         //!< The 9 key
    Escape,       //!< The Escape key
    LControl,     //!< The left Control key
    LShift,       //!< The left Shift key
    LAlt,         //!< The left Alt key
    LSystem,      //!< The left OS specific key: window (Windows and Linux), apple (macOS), ...
    RControl,     //!< The right Control key
    RShift,       //!< The right Shift key
    RAlt,         //!< The right Alt key
    RSystem,      //!< The right OS specific key: window (Windows and Linux), apple (macOS), ...
    Menu,         //!< The Menu key
    LBracket,     //!< The [ key
    RBracket,     //!< The ] key
    Semicolon,    //!< The ; key
    Comma,        //!< The , key
    Period,       //!< The . key
    Apostrophe,   //!< The ' key
    Slash,        //!< The / key
    Backslash,    //!< The \ key
    Grave,        //!< The ` key
    Equal,        //!< The = key
    Hyphen,       //!< The - key (hyphen)
    Space,        //!< The Space key
    Enter,        //!< The Enter/Return keys
    Backspace,    //!< The Backspace key
    Tab,          //!< The Tabulation key
    PageUp,       //!< The Page up key
    PageDown,     //!< The Page down key
    End,          //!< The End key
    Home,         //!< The Home key
    Insert,       //!< The Insert key
    Delete,       //!< The Delete key
    Add,          //!< The + key
    Subtract,     //!< The - key (minus, usually from numpad)
    Multiply,     //!< The * key
    Divide,       //!< The / key
    LeftArrow,    //!< Left arrow
    RightArrow,   //!< Right arrow
    Up,           //!< Up arrow
    Down,         //!< Down arrow
    Numpad0,      //!< The numpad 0 key
    Numpad1,      //!< The numpad 1 key
    Numpad2,      //!< The numpad 2 key
    Numpad3,      //!< The numpad 3 key
    Numpad4,      //!< The numpad 4 key
    Numpad5,      //!< The numpad 5 key
    Numpad6,      //!< The numpad 6 key
    Numpad7,      //!< The numpad 7 key
    Numpad8,      //!< The numpad 8 key
    Numpad9,      //!< The numpad 9 key
    F1,           //!< The F1 key
    F2,           //!< The F2 key
    F3,           //!< The F3 key
    F4,           //!< The F4 key
    F5,           //!< The F5 key
    F6,           //!< The F6 key
    F7,           //!< The F7 key
    F8,           //!< The F8 key
    F9,           //!< The F9 key
    F10,          //!< The F10 key
    F11,          //!< The F11 key
    F12,          //!< The F12 key
    F13,          //!< The F13 key
    F14,          //!< The F14 key
    F15,          //!< The F15 key
    Pause,        //!< The Pause key

    KeyCount,     //!< Keep last -- the total number of keyboard keys

    // Deprecated values:

    Tilde     = Grave,     //!< \deprecated Use Grave instead
    Dash      = Hyphen,    //!< \deprecated Use Hyphen instead
    BackSpace = Backspace, //!< \deprecated Use Backspace instead
    BackSlash = Backslash, //!< \deprecated Use Backslash instead
    SemiColon = Semicolon, //!< \deprecated Use Semicolon instead
    Return    = Enter,     //!< \deprecated Use Enter instead
    Quote     = Apostrophe,//!< \deprecated Use Apostrophe instead

    LeftMouse,       //!< The left mouse button
    RightMouse,      //!< The right mouse button
    MiddleMouse,     //!< The middle (wheel) mouse button
    XButton1Mouse,   //!< The first extra mouse button
    XButton2Mouse,   //!< The second extra mouse button
};


class Input
{
public:
    static void Init(sf::WindowBase* _window)
    {
        window = _window;
    }
    static bool GetKeyDown(KeyCode _key)
    {
        return keysDown.Contains(_key);
    }
    static bool GetKey(KeyCode _key)
    {
        return keys.Contains(_key);
    }
    static bool GetKeyUp(KeyCode _key)
    {
        return keysUp.Contains(_key);
    }

    static void AddKeyDown(KeyCode _key)
    {
        keysDown.push_back(_key);
        keyDownEvent.InvokeEvent(_key);
    }
    static void AddKey(KeyCode _key)
    {
        keys.push_back(_key);
    }
    static void AddKeyUp(KeyCode _key)
    {
        keysUp.push_back(_key);
        keyUpEvent.InvokeEvent(_key);
        RemoveKey(_key);
    }

    static void RemoveKeyDown(KeyCode _key)
    {
        keysDown.RemoveElement(_key);
    }
    static void RemoveKey(KeyCode _key)
    {
        keys.RemoveElement(_key);
    }
    static void RemoveKeyUp(KeyCode _key)
    {
        keysUp.RemoveElement(_key);
    }

    static bool GetTextEntered(char _char)
    {
        return textEntered.Contains(_char);
    }

    static void AddTextEntered(char _char)
    {
        textEntered.push_back(_char);
        textEnteredEvent.InvokeEvent(_char);
    }
    static void RemoveTextEntered(char _char)
    {
        textEntered.RemoveElement(_char);
    }

    static void Clear()
    {
        keysDown.clear();
        keysUp.clear();
        textEntered.clear();
    }

    static sf::Vector2f GetMousePosition()
    {
        return sf::Vector2f(sf::Mouse::getPosition(*window));
    }
    static sf::Vector2f GetMousePositionRaw()
    {
        return sf::Vector2f(sf::Mouse::getPosition());
    }
    static sf::Vector2f GetMousePositionRelativeTo(const sf::WindowBase* _window)
    {
        return sf::Vector2f(sf::Mouse::getPosition(*_window));
    }
    
    inline static Event<KeyCode> keyDownEvent;
    inline static Event<KeyCode> keyUpEvent;
    inline static Event<char> textEnteredEvent;

private:
    inline static TList<KeyCode> keysDown;
    inline static TList<KeyCode> keys;
    inline static TList<KeyCode> keysUp;

    inline static TList<char> textEntered;
    inline static sf::WindowBase* window;
    
public:
    

    static KeyCode FromSFKeyboard(const sf::Keyboard::Key& _other)
    {
        int otherValue = static_cast<int>(_other);
        KeyCode _key = static_cast<KeyCode>(otherValue);
        return _key;
    }

    static KeyCode FromSFMouse(const sf::Mouse::Button& _other)
    {
        KeyCode _key = KeyCode::Unknown;

        if (_other == sf::Mouse::Left)
        {
            _key = KeyCode::LeftMouse;
        }
        else if (_other == sf::Mouse::Right)
        {
            _key = KeyCode::RightMouse;
        }
        else if (_other == sf::Mouse::Middle)
        {
            _key = KeyCode::MiddleMouse;
        }
        else if (_other == sf::Mouse::XButton1)
        {
            _key = KeyCode::XButton1Mouse;
        }
        else if (_other == sf::Mouse::XButton2)
        {
            _key = KeyCode::XButton2Mouse;
        }
        return _key;
    }



};
