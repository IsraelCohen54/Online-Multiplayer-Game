#include "colored_canvas.hpp"
#include "canvas_inl.hpp"
#include <iostream>

#define ANSI_ESCAPE_CHAR "\x1b"
#define RESET_SEQUENCE ANSI_ESCAPE_CHAR "[00m"
static const size_t COLOR_CODE_LEN = (sizeof(RESET_SEQUENCE) - sizeof('\0'));

#define NEUTRAL_CHAR_CONTROL_CODES RESET_SEQUENCE RESET_SEQUENCE 
static const size_t CHAR_CONTROL_CODES_LEN = (sizeof(NEUTRAL_CHAR_CONTROL_CODES) - sizeof('\0'));
#define CLEARED_CHAR_SEQUENCE NEUTRAL_CHAR_CONTROL_CODES " " 
static const size_t SINGLE_CHAR_WITH_CONTROL_CODES_LEN = (sizeof(CLEARED_CHAR_SEQUENCE) - sizeof('\0'));

static int ControlCodeStartX(int a_logicalX) {
    return a_logicalX * SINGLE_CHAR_WITH_CONTROL_CODES_LEN;
}

static int CharActualX(int a_logicalX) {
    return ControlCodeStartX(a_logicalX) + CHAR_CONTROL_CODES_LEN;
} 

const char *FG_COLOR_CODES[] = {
    RESET_SEQUENCE,
    ANSI_ESCAPE_CHAR "[30m",
    ANSI_ESCAPE_CHAR "[31m",
    ANSI_ESCAPE_CHAR "[32m",
    ANSI_ESCAPE_CHAR "[33m",
    ANSI_ESCAPE_CHAR "[34m",
    ANSI_ESCAPE_CHAR "[35m",
    ANSI_ESCAPE_CHAR "[36m",
    ANSI_ESCAPE_CHAR "[37m",
};

const char *BG_COLOR_CODES[] = {
    RESET_SEQUENCE,
    ANSI_ESCAPE_CHAR "[40m",
    ANSI_ESCAPE_CHAR "[41m",
    ANSI_ESCAPE_CHAR "[42m",
    ANSI_ESCAPE_CHAR "[43m",
    ANSI_ESCAPE_CHAR "[44m",
    ANSI_ESCAPE_CHAR "[45m",
    ANSI_ESCAPE_CHAR "[46m",
    ANSI_ESCAPE_CHAR "[47m",
};

namespace ascii {

ColoredCanvas::CharProxy::CharProxy(ColoredCanvas &a_canvas, int a_logicalX, int a_y)
: m_colored(a_canvas)
, m_logicalX(a_logicalX)
, m_y(a_y) {
}

ColoredCanvas::CharProxy &ColoredCanvas::CharProxy::operator=(const CharProxy &a_other) {
    int actualX = ControlCodeStartX(m_logicalX);
    for (size_t sequenceIdx = 0  ; sequenceIdx < SINGLE_CHAR_WITH_CONTROL_CODES_LEN ; ++sequenceIdx) {
        m_colored.m_canvas(actualX + sequenceIdx, m_y) = a_other.m_colored.m_canvas(actualX + sequenceIdx, m_y);
    }
    return *this;
}

ColoredCanvas::CharProxy::operator char() const {
    return m_colored.m_canvas(CharActualX(m_logicalX), m_y);
}

/*ColoredCanvas::CharProxy::operator Color() const {
    size_t colorSequenceStart = ControlCodeStartX(m_logicalX); 
    
}*/

ColoredCanvas::CharProxy &ColoredCanvas::CharProxy::operator=(const char a_newVal) {
    return operator()(m_colored.m_defaultFg, m_colored.m_defaultBg, a_newVal);
}

/*ColoredCanvas::CharProxy &ColoredCanvas::CharProxy::operator=(const Color a_newVal) {

}*/

ColoredCanvas::CharProxy &ColoredCanvas::CharProxy::operator()(Color a_fg, Color a_bg, char a_newVal) {
    int actualX = ControlCodeStartX(m_logicalX);
    const char *firstColor, *secondColor;
    if (ColoredCanvas::TERMINAL_COLOR == a_fg) {
        firstColor = FG_COLOR_CODES[a_fg];
        secondColor = BG_COLOR_CODES[a_bg];
    }
    else {
        firstColor = BG_COLOR_CODES[a_bg];
        secondColor = FG_COLOR_CODES[a_fg];
    }

    for (size_t sequenceIdx = 0  ; sequenceIdx < COLOR_CODE_LEN ; ++sequenceIdx) {
        m_colored.m_canvas(actualX, m_y) = firstColor[sequenceIdx];
        ++actualX;
    }
    for (size_t sequenceIdx = 0  ; sequenceIdx < COLOR_CODE_LEN ; ++sequenceIdx) {
        m_colored.m_canvas(actualX, m_y) = secondColor[sequenceIdx];
        ++actualX;
    }
    m_colored.m_canvas(actualX, m_y) = a_newVal;

    return *this;
}

ColoredCanvas::ColoredCanvas(size_t a_width, size_t a_height)
: m_canvas(ControlCodeStartX(a_width) + COLOR_CODE_LEN, a_height)
, m_logicalWidth(a_width)
, m_defaultFg(TERMINAL_COLOR)
, m_defaultBg(TERMINAL_COLOR) {
    Clear();
}

void ColoredCanvas::SetDefaultFg(Color a_color) {
    m_defaultFg = a_color;
}

void ColoredCanvas::SetDefaultBg(Color a_color) {
    m_defaultBg = a_color;
}

ColoredCanvas::Color ColoredCanvas::GetDefaultFg() const {
     return m_defaultFg;
}

ColoredCanvas::Color ColoredCanvas::GetDefaultBg() const {
    return m_defaultBg;
}

void ColoredCanvas::Clear() {
    for (size_t y = 0 ; y < m_canvas.GetHeight() ; ++y) {
        for (size_t logicalX = 0 ; logicalX < m_logicalWidth ; ++logicalX) {
            for (size_t sequenceIdx = 0 ; sequenceIdx < SINGLE_CHAR_WITH_CONTROL_CODES_LEN ; ++sequenceIdx) {
                m_canvas(ControlCodeStartX(logicalX) + sequenceIdx, y) = (CLEARED_CHAR_SEQUENCE)[sequenceIdx];
            }
        }
        for (size_t sequenceIdx = 0 ; sequenceIdx < COLOR_CODE_LEN ; ++sequenceIdx) {
            m_canvas(ControlCodeStartX(m_logicalWidth) + sequenceIdx, y) = (RESET_SEQUENCE)[sequenceIdx];
        }
    }
}

ColoredCanvas::CharProxy ColoredCanvas::operator[](const Point &a_point) {
    return operator()(a_point.GetX(), a_point.GetY());
}

char ColoredCanvas::operator[](const Point &a_point) const {
    return operator()(a_point.GetX(), a_point.GetY());
}

ColoredCanvas::CharProxy ColoredCanvas::operator()(int a_x, int a_y) {
    return CharProxy(*this, a_x, a_y);
}

char ColoredCanvas::operator()(int a_x, int a_y) const {
    return m_canvas(CharActualX(a_x), a_y);
}

size_t ColoredCanvas::GetWidth() const {
    return m_logicalWidth;
}

size_t ColoredCanvas::GetHeight() const {
    return m_canvas.GetHeight();
}

bool ColoredCanvas::IsLegalPosition(const Point &a_point) const {
    return m_canvas.IsLegalPosition(a_point);
}

bool ColoredCanvas::IsLegalPosition(int a_x, int a_y) const {
    return m_canvas.IsLegalPosition(a_x, a_y);
}

void ColoredCanvas::Print(::std::ostream &a_out, OutputPosition a_outPos) const {
	if (a_outPos == OutputPosition::TOP_LEFT)
	{
		a_out << ANSI_ESCAPE_CHAR << "[H";
	}
    m_canvas.Print(a_out);
}

void DrawLine(ColoredCanvas &a_canvas, char a_brush, ColoredCanvas::Color a_fgColor, ColoredCanvas::Color a_bgColor, int a_startX, int a_startY, int a_endX, int a_endY) {
    ColoredCanvas::Color oldFg = a_canvas.GetDefaultFg();
    ColoredCanvas::Color oldBg = a_canvas.GetDefaultBg();

    a_canvas.SetDefaultFg(a_fgColor);
    a_canvas.SetDefaultBg(a_bgColor);
    DrawLine(a_canvas, a_brush, a_startX, a_startY, a_endX, a_endY);

    a_canvas.SetDefaultFg(oldFg);
    a_canvas.SetDefaultBg(oldBg);
}

void DrawLine(ColoredCanvas &a_canvas, char a_brush, ColoredCanvas::Color a_fgColor, ColoredCanvas::Color a_bgColor, const Point &a_start, const Point &a_end) {
    DrawLine(a_canvas, a_brush, a_fgColor, a_bgColor, a_start.GetX(), a_start.GetY(), a_end.GetX(), a_end.GetY());
}

void DrawCircle(ColoredCanvas &a_canvas, char a_brush, ColoredCanvas::Color a_fgColor, ColoredCanvas::Color a_bgColor, int a_centerX, int a_centerY, double a_radius) {
    ColoredCanvas::Color oldFg = a_canvas.GetDefaultFg();
    ColoredCanvas::Color oldBg = a_canvas.GetDefaultBg();

    a_canvas.SetDefaultFg(a_fgColor);
    a_canvas.SetDefaultBg(a_bgColor);
    DrawCircle(a_canvas, a_brush, a_centerX, a_centerY, a_radius);
    
    a_canvas.SetDefaultFg(oldFg);
    a_canvas.SetDefaultBg(oldBg);
}

void DrawCircle(ColoredCanvas &a_canvas, char a_brush, ColoredCanvas::Color a_fgColor, ColoredCanvas::Color a_bgColor, const Point &a_center, size_t a_radius) {
    DrawCircle(a_canvas, a_brush, a_fgColor, a_bgColor, a_center.GetX(), a_center.GetY(), a_radius);
}

} // ascii
