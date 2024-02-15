#include <iostream>
#include <thread>
#include <chrono>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "ascii/canvas.hpp"
#include "ascii/canvas_inl.hpp"
#include "ascii/colored_canvas.hpp"

#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"

#include "Group.h"
#include "Animation.h"
#include "AnimationStep.h"
#include "AnimationMoveTo.h"

#include "MoveRight.h"
#include "MoveUp.h"
#include "MoveLeft.h"
#include "MoveDown.h"

#include "ShapeFactory.h"

//#include "Reader.h"
//#include "Writer.h"

namespace experis
{
using ChoseClr = ascii::ColoredCanvas;

void operator++(Animation& a_animation)
{
    a_animation.ExecuteAnimation();
}

// ~~~~~~~~~~~~~~ Start Lord of the Rings Animations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void FillHobitHome(Group& a_group)
{
    a_group.Add<Line, Point, Point>(Point{0, 0}, Point{99, 0}, ChoseClr::BLUE, ChoseClr::BLUE, '|');    
    a_group.Add<Line, Point, Point>(Point{0, 1}, Point{99, 1}, ChoseClr::BLUE, ChoseClr::BLUE, '|');    
    a_group.Add<Line, Point, Point>(Point{0, 2}, Point{99, 2}, ChoseClr::BLUE, ChoseClr::BLUE, '|');    
    a_group.Add<Line, Point, Point>(Point{0, 3}, Point{99, 3}, ChoseClr::BLUE, ChoseClr::BLUE, '|');       
  
    //a_group.Add<Line, Point, Point>(Point{46, 0}, Point{99, 26}, ChoseClr::GREEN, ChoseClr::GREEN, '|');
    //a_group.Add<Line, Point, Point>(Point{5, 25}, Point{46, 2}, ChoseClr::CYAN, ChoseClr::CYAN, '/');    
    //a_group.Add<Line, Point, Point>(Point{46, 2}, Point{94, 25}, ChoseClr::CYAN, ChoseClr::CYAN, '\\');
    //a_group.Add<Circle, Point, double>(Point{40, 27}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    //a_group.Add<Circle, Point, double>(Point{40, 28}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    
    // home:
    a_group.Add<Circle, Point, double>(Point{40, 31}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    a_group.Add<Circle, Point, double>(Point{40, 32}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    a_group.Add<Circle, Point, double>(Point{40, 33}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    a_group.Add<Circle, Point, double>(Point{40, 34}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    a_group.Add<Circle, Point, double>(Point{40, 35}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    a_group.Add<Circle, Point, double>(Point{40, 36}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    a_group.Add<Circle, Point, double>(Point{40, 37}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    a_group.Add<Circle, Point, double>(Point{40, 38}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    a_group.Add<Circle, Point, double>(Point{40, 39}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    a_group.Add<Circle, Point, double>(Point{40, 40}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    a_group.Add<Circle, Point, double>(Point{40, 41}, 23, ChoseClr::GREEN, ChoseClr::GREEN, 'w');
    
    // door
    a_group.Add<Circle, Point, double>(Point{40, 32}, 15, ChoseClr::WHITE, ChoseClr::WHITE, 'w');
    a_group.Add<Circle, Point, double>(Point{41, 32}, 15, ChoseClr::WHITE, ChoseClr::WHITE, 'w');
    a_group.Add<Circle, Point, double>(Point{39, 32}, 15, ChoseClr::WHITE, ChoseClr::WHITE, 'w');
    a_group.Add<Circle, Point, double>(Point{40, 33}, 15, ChoseClr::WHITE, ChoseClr::WHITE, 'w');
    
    // ground
    a_group.Add<Line, Point, Point>(Point{0, 25}, Point{99, 25}, ChoseClr::BLACK, ChoseClr::GREEN, '|');    
    a_group.Add<Line, Point, Point>(Point{0, 26}, Point{99, 26}, ChoseClr::GREEN, ChoseClr::GREEN, '|');    
}

void FillGandalph(Group& a_group)
{
    //hat
    a_group.Add<Circle, Point, double>(Point{83, 19}, 1, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    a_group.Add<Circle, Point, double>(Point{83, 19}, 0, ChoseClr::WHITE, ChoseClr::WHITE, '|');    

    //man
    a_group.Add<Circle, Point, double>(Point{83, 20}, 0, ChoseClr::WHITE, ChoseClr::WHITE, 'w');
    a_group.Add<Line, Point, Point>(Point{83, 21}, Point{83, 25}, ChoseClr::WHITE, ChoseClr::WHITE, '|');
    //a_group.Add<Rectangle, Point, Point>(Point{82, 22}, Point{83, 23}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    a_group.Add<Line, Point, Point>(Point{82, 22}, Point{81, 22}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    //a_group.Add<Line, Point, Point>(Point{83, 20}, Point{81, 25}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    //a_group.Add<Line, Point, Point>(Point{83, 21}, Point{84, 25}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    //a_group.Add<Line, Point, Point>(Point{85, 21}, Point{84, 25}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
}

void FillGandalphToRight(Group& a_group)
{
    //man
    a_group.Add<Circle, Point, double>(Point{43, 20}, 0, ChoseClr::WHITE, ChoseClr::WHITE, 'w');
    a_group.Add<Line, Point, Point>(Point{43, 21}, Point{43, 25}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    //a_group.Add<Rectangle, Point, Point>(Point{82, 22}, Point{83, 23}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    a_group.Add<Line, Point, Point>(Point{43, 22}, Point{44, 22}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    //a_group.Add<Line, Point, Point>(Point{83, 20}, Point{81, 25}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    //a_group.Add<Line, Point, Point>(Point{83, 21}, Point{84, 25}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    //a_group.Add<Line, Point, Point>(Point{85, 21}, Point{84, 25}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    //hat
    a_group.Add<Circle, Point, double>(Point{43, 19}, 1, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    a_group.Add<Circle, Point, double>(Point{43, 19}, 0, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
}

void FillStaff(Group& a_group)
{
//stuff
    a_group.Add<Circle, Point, double>(Point{80, 20}, 1, ChoseClr::YELLOW, ChoseClr::YELLOW, 'O');
    a_group.Add<Line, Point, Point>(Point{80, 20}, Point{80, 25}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    a_group.Add<Circle, Point, double>(Point{80, 20}, 0, ChoseClr::WHITE, ChoseClr::YELLOW, 'O');
}

void FillHobit(Group& a_group)
{
    //hat
    a_group.Add<Circle, Point, double>(Point{40, 20}, 1, ChoseClr::CYAN, ChoseClr::GREEN, '_');    
    a_group.Add<Circle, Point, double>(Point{40, 20}, 0, ChoseClr::CYAN, ChoseClr::GREEN, '_');    

    //hobit
    a_group.Add<Circle, Point, double>(Point{40, 21}, 0, ChoseClr::WHITE, ChoseClr::WHITE, 'w');
    a_group.Add<Line, Point, Point>(Point{40, 21}, Point{40, 25}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    

}

void FillSpyder(Group& a_group)
{
    a_group.Add<Circle, Point, double>(Point{0, 65}, 45, ChoseClr::WHITE, ChoseClr::BLACK, '|');
    a_group.Add<Circle, Point, double>(Point{0, 55}, 35, ChoseClr::WHITE, ChoseClr::BLACK, '|');
    a_group.Add<Circle, Point, double>(Point{0, 45}, 25, ChoseClr::WHITE, ChoseClr::BLACK, '|');
}

void FillEye(Group& a_group)
{
    a_group.Add<Line, Point, Point>(Point{22, 0}, Point{8, 0}, ChoseClr::YELLOW, ChoseClr::RED, '#');    
    a_group.Add<Line, Point, Point>(Point{5, 27}, Point{25, 27}, ChoseClr::YELLOW, ChoseClr::RED, '#');
    a_group.Add<Line, Point, Point>(Point{6, 26}, Point{24, 26}, ChoseClr::YELLOW, ChoseClr::RED, '#');
    a_group.Add<Line, Point, Point>(Point{7, 25}, Point{23, 25}, ChoseClr::YELLOW, ChoseClr::RED, '#');
    a_group.Add<Line, Point, Point>(Point{8, 24}, Point{22, 24}, ChoseClr::YELLOW, ChoseClr::RED, '#');
    a_group.Add<Line, Point, Point>(Point{9, 23}, Point{21, 23}, ChoseClr::YELLOW, ChoseClr::RED, '#');
    a_group.Add<Line, Point, Point>(Point{10, 22}, Point{20, 22}, ChoseClr::YELLOW, ChoseClr::RED, '#');

    a_group.Add<Circle, Point, double>(Point{15,8}, 7, ChoseClr::YELLOW, ChoseClr::RED, 'w');
    a_group.Add<Circle, Point, double>(Point{15,14}, 7, ChoseClr::YELLOW, ChoseClr::RED, 'w');
    a_group.Add<Circle, Point, double>(Point{15,11}, 2, ChoseClr::RED, ChoseClr::YELLOW, 'O'); 
    a_group.Add<Rectangle, Point, Point>(Point{14, 10} ,Point{16, 12}, ChoseClr::RED, ChoseClr::YELLOW, '|');
}

void FillVolcano(Group& a_volcano)
{
    a_volcano.Add<Line> (Point{51, 25}, Point{89, 25}, ChoseClr::RED, ChoseClr::RED, '|');
    a_volcano.Add<Line> (Point{50, 26}, Point{90, 26}, ChoseClr::RED, ChoseClr::RED, '|');
    a_volcano.Add<Line> (Point{51, 25}, Point{50, 26}, ChoseClr::YELLOW, ChoseClr::YELLOW, '|');
    a_volcano.Add<Line> (Point{50, 25}, Point{49, 26}, ChoseClr::YELLOW, ChoseClr::YELLOW, '|');
    a_volcano.Add<Line> (Point{49, 25}, Point{48, 26}, ChoseClr::YELLOW, ChoseClr::YELLOW, '|');
    a_volcano.Add<Line> (Point{89, 25}, Point{90, 26}, ChoseClr::YELLOW, ChoseClr::YELLOW, '|');
    a_volcano.Add<Line> (Point{90, 25}, Point{91, 26}, ChoseClr::YELLOW, ChoseClr::YELLOW, '|');
    a_volcano.Add<Line> (Point{91, 25}, Point{92, 26}, ChoseClr::YELLOW, ChoseClr::YELLOW, '|');
}

void FillRuleThemAllRing(Group& a_ruleThemAllRing)
{
    using ChoseClr = ascii::ColoredCanvas;

    a_ruleThemAllRing.Add<Circle, Point, double>(Point{55,10}, 3, ChoseClr::YELLOW, ChoseClr::YELLOW, ' '); 
 
    a_ruleThemAllRing.Add<Line, Point, Point>(Point{53, 7}, Point{53, 7}, ChoseClr::YELLOW, ChoseClr::RED, 'O');
    a_ruleThemAllRing.Add<Line, Point, Point>(Point{54, 7}, Point{54, 7}, ChoseClr::YELLOW, ChoseClr::RED, 'N');
    a_ruleThemAllRing.Add<Line, Point, Point>(Point{55, 7}, Point{55, 7}, ChoseClr::YELLOW, ChoseClr::RED, 'E');

    a_ruleThemAllRing.Add<Line, Point, Point>(Point{57, 9}, Point{57, 9}, ChoseClr::YELLOW, ChoseClr::RED, 'T');
    a_ruleThemAllRing.Add<Line, Point, Point>(Point{57, 10}, Point{57, 10}, ChoseClr::YELLOW, ChoseClr::RED, 'O');

    a_ruleThemAllRing.Add<Line, Point, Point>(Point{53, 13}, Point{53, 13}, ChoseClr::YELLOW, ChoseClr::RED, 'R');
    a_ruleThemAllRing.Add<Line, Point, Point>(Point{54, 13}, Point{54, 13}, ChoseClr::YELLOW, ChoseClr::RED, 'U');
    a_ruleThemAllRing.Add<Line, Point, Point>(Point{55, 13}, Point{55, 13}, ChoseClr::YELLOW, ChoseClr::RED, 'L');
    a_ruleThemAllRing.Add<Line, Point, Point>(Point{56, 12}, Point{56, 12}, ChoseClr::YELLOW, ChoseClr::RED, 'E');

    a_ruleThemAllRing.Add<Line, Point, Point>(Point{51, 9}, Point{51, 9}, ChoseClr::YELLOW, ChoseClr::RED, 'A');
    a_ruleThemAllRing.Add<Line, Point, Point>(Point{51, 10}, Point{51, 10}, ChoseClr::YELLOW, ChoseClr::RED, 'L');
    a_ruleThemAllRing.Add<Line, Point, Point>(Point{51, 11}, Point{51, 11}, ChoseClr::YELLOW, ChoseClr::RED, 'L');
}

void FillSpyderHome(Group& a_spiderCave)
{
    a_spiderCave.Add<Line, Point, Point>(Point{0, 0}, Point{99, 27}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    a_spiderCave.Add<Line, Point, Point>(Point{-3, 81}, Point{11, 27}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    a_spiderCave.Add<Line, Point, Point>(Point{70, 27}, Point{99, -8}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
    a_spiderCave.Add<Line, Point, Point>(Point{-7, 20}, Point{15, -3}, ChoseClr::WHITE, ChoseClr::WHITE, '|');       
    a_spiderCave.Add<Line, Point, Point>(Point{5, 5},  Point{36,25}, ChoseClr::WHITE, ChoseClr::WHITE, '|');       
    a_spiderCave.Add<Line, Point, Point>(Point{28, 8},  Point{4, -3}, ChoseClr::WHITE, ChoseClr::WHITE, '|');       
    a_spiderCave.Add<Line, Point, Point>(Point{70, 20}, Point{23, 83}, ChoseClr::WHITE, ChoseClr::WHITE, '|');       
    a_spiderCave.Add<Line, Point, Point>(Point{4, 57},  Point{58, 14}, ChoseClr::WHITE, ChoseClr::WHITE, '|');       
    
    a_spiderCave.Add<Line, Point, Point>(Point{0, 25}, Point{99, 25}, ChoseClr::BLACK, ChoseClr::WHITE, '&');    
    a_spiderCave.Add<Line, Point, Point>(Point{0, 26}, Point{99, 26}, ChoseClr::WHITE, ChoseClr::WHITE, '|');    
}

//struct MoveRight { void operator()(Shape& a_shape) { a_shape.MoveBy(1, 0); } }; // NOTE: MoveRight/MoveDown do not inherit anything! They are function objects.
//struct MoveDown { void operator()(Shape& a_shape) { a_shape.MoveBy(0, 1); } };
//struct MoveLeft { void operator()(Shape& a_shape) { a_shape.MoveBy(-1, 0); } };
//struct MoveUp { void operator()(Shape& a_shape) { a_shape.MoveBy(0, -1); } };

// Todo Square init should be checked with assert,
//      instead of 'throw' inside ctor at runtime,
//      but before at compilation time using specific ctor for square

void PerformAnimation(ShapeFactory& a_shapeFactory)
{
    using namespace std::chrono_literals;

    Group hobitHome{};
    FillHobitHome(hobitHome);
    // ~~~
    SavePainting(std::string{"D:\\visual_studio_projs\\Experis_algo\\Shapes\\hobitHome.txt"}, hobitHome);
    Group newHobitHome = LoadPainting(std::string{"D:\\visual_studio_projs\\Experis_algo\\Shapes\\hobitHome.txt"}, a_shapeFactory);
    // ~~~

    Group gandalph{};
    FillGandalph(gandalph);

    Group staff1{};
    FillStaff(staff1);
    gandalph.Add(staff1);

    AnimationStep *gandalfComing = new AnimationMoveTo <MoveLeft> {gandalph, 40, MoveLeft{}};
    Animation anim1;
    anim1.Add(gandalfComing);

    while (anim1.HasAnimation())
	{
        ascii::ColoredCanvas canvasFirstThyme{99, 27};
        hobitHome.DrawGroup(canvasFirstThyme);
        gandalph.DrawGroup(canvasFirstThyme);
        canvasFirstThyme.Print(std::cout);
        std::this_thread::sleep_for(80ms);
		++anim1;
    } 
    std::cout << '\a';
    std::this_thread::sleep_for(2000ms);

    // Talk inside:
    ascii::ColoredCanvas canvasFirstThymeInside{99, 27};
    hobitHome.DrawGroup(canvasFirstThymeInside);
    canvasFirstThymeInside.Print(std::cout);
    std::this_thread::sleep_for(1700ms);
    
    Group gandlafGoesRight{};
    FillGandalphToRight(gandlafGoesRight);
    
    Group staff{};
    FillStaff(staff);
    staff.MoveBy(-35, 0);
    gandlafGoesRight.Add(staff);

    Group hobit{};
    FillHobit(hobit);
    AnimationStep *hobitAppearance = new AnimationMoveTo <MoveRight>{hobit, 30, MoveRight{}};
    anim1.Add(hobitAppearance);
    AnimationStep *gandalfRight = new AnimationMoveTo <MoveRight> {gandlafGoesRight, 20, MoveRight{}};
    
    Animation anime2;
    anime2.Add(gandalfRight);
    
    //going to talk out
    while (anim1.HasAnimation() || anime2.HasAnimation())
	{
        ascii::ColoredCanvas canvasFirstThyme{99, 27};
        hobitHome.DrawGroup(canvasFirstThyme);
        //hobit.MoveBy(1,0);
        hobit.DrawGroup(canvasFirstThyme);
        //gandalph.MoveBy(1,0);
        gandlafGoesRight.DrawGroup(canvasFirstThyme);
        canvasFirstThyme.Print(std::cout);
        std::this_thread::sleep_for(200ms);
		++anim1;
        ++anime2;
        std::this_thread::sleep_for(100ms);
    }

    // giving ring
    Circle ringThyme1{Point{65, 21}, 0,ascii::ColoredCanvas::BLACK,ascii::ColoredCanvas::YELLOW,'O'};
    AnimationStep *ringU1 = new AnimationMoveTo <MoveUp> {ringThyme1, 2, MoveUp{}};
    AnimationStep *ringL2 = new AnimationMoveTo <MoveRight>{ringThyme1, 2, MoveRight{}};
    AnimationStep *ringL3 = new AnimationMoveTo <MoveRight> {ringThyme1, 2, MoveRight{}};
    AnimationStep *ringD4 = new AnimationMoveTo <MoveDown> {ringThyme1, 2, MoveDown{}};
    AnimationStep *hobitContinue = new AnimationMoveTo <MoveRight> {hobit, 50, MoveRight{}};
    AnimationStep *gandalfContinue = new AnimationMoveTo <MoveRight> {gandlafGoesRight, 50, MoveRight{}};

    Animation ringAnim1;
    Animation ringAnim2;
    ringAnim1.Add(ringU1);
    ringAnim1.Add(ringL3);
    ringAnim1.Add(hobitContinue);
    ringAnim2.Add(ringL2);
    ringAnim2.Add(ringD4);
    ringAnim2.Add(gandalfContinue);
   
    Circle hobitHandThyme1{Point{69, 22}, 0,ascii::ColoredCanvas::WHITE,ascii::ColoredCanvas::WHITE,'O'};
    int counter = 0;
	while (ringAnim1.HasAnimation() || ringAnim2.HasAnimation())
	{
        ++counter;
		ascii::ColoredCanvas canvasFirstThyme{99, 27};
        hobitHome.DrawGroup(canvasFirstThyme);
        hobit.DrawGroup(canvasFirstThyme);
        gandlafGoesRight.DrawGroup(canvasFirstThyme);
        if (counter < 6)
        {
            ringThyme1.DrawGroup(canvasFirstThyme);
        }
        std::this_thread::sleep_for(150ms);
        if (counter == 4 || counter == 5)
        {
            hobitHandThyme1.DrawGroup(canvasFirstThyme);
        }
        canvasFirstThyme.Print(std::cout);
		++ringAnim1;
        ++ringAnim2;
	}
    std::this_thread::sleep_for(2000ms);

    Group spyderHome{};
    FillSpyderHome(spyderHome);

    Group spyder{};
    FillSpyder(spyder);
    AnimationStep *spderAnimeR = new AnimationMoveTo <MoveRight> {spyder, 150, MoveRight{}};
    Animation spyderThyme1;
    spyderThyme1.Add(spderAnimeR);

    hobit.MoveBy(-123, 0);
    AnimationStep *hobitRunR = new AnimationMoveTo <MoveRight> {hobit, 200, MoveRight{}};
    Animation spyderThyme2;
    spyderThyme2.Add(hobitRunR);

    counter = 0;
    while (spyderThyme1.HasAnimation() || spyderThyme2.HasAnimation())
	{
		ascii::ColoredCanvas canvasSecThyme{99, 27};
        
        ++counter;
        if (counter % 3 == 0 && counter > 38)
        {
            spyder.DrawGroup(canvasSecThyme);
            ++spyderThyme2;
        }

        hobit.DrawGroup(canvasSecThyme);
        
        if (counter >= 55)
        {
            spyder.DrawGroup(canvasSecThyme);
            ++spyderThyme1;
            ++spyderThyme1;
            ++spyderThyme2;
            ++spyderThyme1;
            ++spyderThyme1;
            ++spyderThyme2;
            spyderHome.DrawGroup(canvasSecThyme);
        }
        canvasSecThyme.Print(std::cout);
        ++spyderThyme2;
        std::this_thread::sleep_for(100ms);
	}

    Group eye{};
    FillEye(eye);

    Line seeLine{Point{15, 11}, Point{0, 27}, ChoseClr::YELLOW, ChoseClr::YELLOW, '|'};
    
    Group volcano{};
    FillVolcano(volcano);

    Group finishRing{};
    FillRuleThemAllRing(finishRing);

    AnimationStep *ringFinito = new AnimationMoveTo <MoveDown> {finishRing, 380, MoveDown{}};
    Animation lastThyme;
    lastThyme.Add(ringFinito);
    finishRing.MoveBy(0,-350);

    counter = 200;
    while (lastThyme.HasAnimation())
	{
        ++lastThyme;

        ascii::ColoredCanvas canvasThirdThyme{99, 27};
        eye.DrawGroup(canvasThirdThyme);
        volcano.DrawGroup(canvasThirdThyme);
        finishRing.DrawGroup(canvasThirdThyme);
        //if (counter % 8)
        //{
        seeLine.DrawGroup(canvasThirdThyme);
        //}
        --counter;
        canvasThirdThyme.Print(std::cout);
        if (counter > 0)
        {
            seeLine.MoveByRightPoint(3,0);
        }
        else
        {
            seeLine.MoveByRightPoint(-4,0);
        }
        if (counter == -150)
        {
            std::this_thread::sleep_for(4000ms);
        }
        std::this_thread::sleep_for(70ms);
    }
}
// ~~~~~~~~~~~~~~ End Lord of the Rings Animations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



} // namespace experis

int main()
{    
    using namespace experis;
    ShapeFactory shapeFactory{};

    PerformAnimation(shapeFactory);

    return 0;
}
    
    /*
    using namespace std::chrono_literals;
    
    ascii::ColoredCanvas gridNumbers{60, 17};
    for (size_t i = 0 ; i < gridNumbers.GetHeight() ; ++i) {
		if (i / 10)
		{
	        gridNumbers(gridNumbers.GetWidth() - 2, i) = '0' + (i / 10);
		}
		else
		{
			gridNumbers(gridNumbers.GetWidth() - 2, i) = '.';
		}
        gridNumbers(gridNumbers.GetWidth() - 1, i) = '0' + (i % 10);
    }
    for (size_t i = 0 ; i < gridNumbers.GetWidth() ; ++i) {
        gridNumbers(i, gridNumbers.GetHeight() - 2) = '0' + (i / 10);
        gridNumbers(i, gridNumbers.GetHeight() - 1) = '0' + (i % 10);
    }

    ascii::ColoredCanvas canvas{gridNumbers};
    ascii::DrawCircle(canvas, '*', ascii::ColoredCanvas::MAGENTA, ascii::ColoredCanvas::YELLOW, ascii::Point(7, 7), 7);
    ascii::DrawLine(canvas, '#', ascii::ColoredCanvas::TERMINAL_COLOR, ascii::ColoredCanvas::WHITE, ascii::Point(15, 7), ascii::Point(40, 7));
    ascii::DrawLine(canvas, '#', ascii::ColoredCanvas::TERMINAL_COLOR, ascii::ColoredCanvas::WHITE, ascii::Point(40, 7), ascii::Point(55, 0));
    ascii::DrawLine(canvas, '#', ascii::ColoredCanvas::TERMINAL_COLOR, ascii::ColoredCanvas::WHITE, ascii::Point(40, 7), ascii::Point(55, 14));
    ascii::DrawCircle(canvas, '#', ascii::ColoredCanvas::RED, ascii::ColoredCanvas::TERMINAL_COLOR, ascii::Point(4, 4), 1);
    ascii::DrawCircle(canvas, '#', ascii::ColoredCanvas::RED, ascii::ColoredCanvas::TERMINAL_COLOR, ascii::Point(5, 4), 1);
    ascii::DrawCircle(canvas, 'o', ascii::ColoredCanvas::BLUE, ascii::ColoredCanvas::TERMINAL_COLOR, ascii::Point(6, 4), 1);
    ascii::DrawCircle(canvas, '#', ascii::ColoredCanvas::RED, ascii::ColoredCanvas::TERMINAL_COLOR, ascii::Point(4, 9), 1);
    ascii::DrawCircle(canvas, '#', ascii::ColoredCanvas::RED, ascii::ColoredCanvas::TERMINAL_COLOR, ascii::Point(5, 9), 1);
    ascii::DrawCircle(canvas, 'o', ascii::ColoredCanvas::BLUE, ascii::ColoredCanvas::TERMINAL_COLOR, ascii::Point(6, 9), 1);
    ascii::DrawLine(canvas, '@', ascii::ColoredCanvas::BLACK, ascii::ColoredCanvas::WHITE, 20, 6, 27, 0);
    ascii::DrawLine(canvas, '@', ascii::ColoredCanvas::BLACK, ascii::ColoredCanvas::WHITE, 20, 8, 27, 14);
	canvas(0, 0) = '+';

    ascii::ColoredCanvas canvas2{gridNumbers};
    //canvas2 = canvas2orig;
    ascii::DrawCircle(canvas2, '*', ascii::ColoredCanvas::MAGENTA, ascii::ColoredCanvas::YELLOW, ascii::Point(7, 7), 7);
    ascii::DrawLine(canvas2, '#', ascii::ColoredCanvas::TERMINAL_COLOR, ascii::ColoredCanvas::WHITE, ascii::Point(15, 7), ascii::Point(40, 7));
    ascii::DrawLine(canvas2, '#', ascii::ColoredCanvas::TERMINAL_COLOR, ascii::ColoredCanvas::WHITE, ascii::Point(40, 7), ascii::Point(55, 0));
    ascii::DrawLine(canvas2, '#', ascii::ColoredCanvas::TERMINAL_COLOR, ascii::ColoredCanvas::WHITE, ascii::Point(40, 7), ascii::Point(55, 14));
    ascii::DrawCircle(canvas2, '#', ascii::ColoredCanvas::RED, ascii::ColoredCanvas::TERMINAL_COLOR, 3, 4, 1);
    ascii::DrawCircle(canvas2, 'O', ascii::ColoredCanvas::CYAN, ascii::ColoredCanvas::BLUE, 4, 4, 1);
    ascii::DrawCircle(canvas2, 'O', ascii::ColoredCanvas::CYAN, ascii::ColoredCanvas::BLUE, 5, 4, 1);
    ascii::DrawCircle(canvas2, '#', ascii::ColoredCanvas::RED, ascii::ColoredCanvas::TERMINAL_COLOR, 3, 9, 1);
    ascii::DrawCircle(canvas2, 'O', ascii::ColoredCanvas::CYAN, ascii::ColoredCanvas::BLUE, 4, 9, 1);
    ascii::DrawCircle(canvas2, 'O', ascii::ColoredCanvas::CYAN, ascii::ColoredCanvas::BLUE, 5, 9, 1);
    ascii::DrawLine(canvas2, '@', ascii::ColoredCanvas::BLACK, ascii::ColoredCanvas::WHITE, 20, 6, 13, 0);
    ascii::DrawLine(canvas2, '@', ascii::ColoredCanvas::BLACK, ascii::ColoredCanvas::WHITE, 20, 8, 13, 14);
	canvas2(0, 0) = 'x';

    while (true) {
        //for (int i = 0 ; i < 10 ; ++i) {
        //    std::cout << std::endl << std::endl;
        //}
        canvas.Print(std::cout);
        std::this_thread::sleep_for(2000ms);

        //for (int i = 0 ; i < 10 ; ++i) {
        //    std::cout << std::endl << std::endl;
        //}
        canvas2.Print(std::cout);
        std::this_thread::sleep_for(2000ms);
    }
    */    





    //_CrtDumpMemoryLeaks();
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /*
    Circle c1{Point{65, 21}, 0,ascii::ColoredCanvas::BLACK,ascii::ColoredCanvas::YELLOW,'O'};
	Animation anim;
	anim.Add(c1, 50, MoveRight{});
	anim.Add(c1, 20, MoveDown{});
	anim.Add(c1, 20, [](Shape& a_shape) { a_shape.MoveBy(1, 1); });
 
	while (anim.HasAnimation())
	{
		ascii::ColoredCanvas canvas{80, 25};
		c1.DrawGroup(canvas);
		
		canvas.Print(std::cout);
		++anim;
	}*/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~