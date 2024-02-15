#include "TreasureBox.h"
#include "Line.h"
#include "Rectangle.h"
#include "ascii/colored_canvas.hpp"

namespace experis
{

// Adding treasure box in the middle
Group TreasureBoxCreation()
{
    using ChoseColor = ascii::ColoredCanvas;

    Group treasure;
    treasure.Add<Rectangle, Point, Point>(Point{9, 11}, Point{12, 13}
    , ChoseColor::YELLOW, ChoseColor::BLACK, '?');
    treasure.Add<Line, Point, Point>(Point{10, 12}, Point{11, 12}
    , ChoseColor::GREEN, ChoseColor::WHITE, ' ');
    return treasure;
}

TreasureBox::TreasureBox(const Health a_health, const Attack a_attack, const TreasureMessage& a_message)
:m_health{a_health}
,m_attack{a_attack}
,m_message{a_message}
,m_Paint{TreasureBoxCreation()}
{
}


} // experis namespace