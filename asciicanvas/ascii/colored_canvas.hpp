#ifndef __ASCII_COLORED_CANVAS__
#define __ASCII_COLORED_CANVAS__

#include "canvas.hpp"

namespace ascii {

class ColoredCanvas {
public:
    enum Color { TERMINAL_COLOR, BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };

private:
    class CharProxy {
    public:
        CharProxy(ColoredCanvas &a_canvas, int a_logicalX, int a_y);
        CharProxy(const CharProxy &a_other) = default;
        CharProxy &operator=(const CharProxy &a_other);
        ~CharProxy() = default;

        operator char() const;
        //operator Color() const;

        CharProxy &operator=(const char a_newVal);
        //CharProxy &operator=(const Color a_newVal);
        CharProxy &operator()(Color a_fg, Color a_bg, char a_newVal);

    private:
        ColoredCanvas &m_colored;
        int m_logicalX;
        int m_y;
    };

public:
    ColoredCanvas(size_t a_width, size_t a_height);
    ColoredCanvas(const ColoredCanvas &a_other) = default;
    ColoredCanvas &operator=(const ColoredCanvas &a_other) = default;
    ~ColoredCanvas() = default;

    void Clear();
    CharProxy operator[](const Point &a_point);
    char operator[](const Point &a_point) const;
    CharProxy operator()(int a_x, int a_y);
    char operator()(int a_x, int a_y) const;

    size_t GetWidth() const;
    size_t GetHeight() const;
    bool IsLegalPosition(const Point &a_point) const;
    bool IsLegalPosition(int a_x, int a_y) const;

    void SetDefaultFg(Color a_color);
    void SetDefaultBg(Color a_color);
    Color GetDefaultFg() const;
    Color GetDefaultBg() const;

	enum class OutputPosition
	{
		TOP_LEFT,
		CURRENT_LINE
	};
    void Print(::std::ostream &a_out, OutputPosition a_outPos = OutputPosition::TOP_LEFT) const;

private:
    Canvas m_canvas;
    size_t m_logicalWidth;
    Color m_defaultFg;
    Color m_defaultBg;
};

void DrawLine(ColoredCanvas &a_canvas, char a_brush, ColoredCanvas::Color a_fgColor, ColoredCanvas::Color a_bgColor, int a_startX, int a_startY, int a_endX, int a_endY);
void DrawLine(ColoredCanvas &a_canvas, char a_brush, ColoredCanvas::Color a_fgColor, ColoredCanvas::Color a_bgColor, const Point &a_start, const Point &a_end);
void DrawCircle(ColoredCanvas &a_canvas, char a_brush, ColoredCanvas::Color a_fgColor, ColoredCanvas::Color a_bgColor, int a_centerX, int a_centerY, double a_radius);
void DrawCircle(ColoredCanvas &a_canvas, char a_brush, ColoredCanvas::Color a_fgColor, ColoredCanvas::Color a_bgColor, const Point &a_center, size_t a_radius);

} // ascii

#endif