#include "canvas.hpp"
#include <algorithm>

namespace ascii {

template<class CanvasT>
void DrawLine(CanvasT &a_canvas, char a_brush, int a_startX, int a_startY, int a_endX, int a_endY) {
    unsigned int dx = abs(a_endX - a_startX);   // dx is the delta for x
    unsigned int dy = abs(a_endY - a_startY);   // dy is the delta for y
    unsigned int stepVal = 0;  // variable for figuring out when to the other axis 
    if(dx > dy) {   // The slope is less than 45 degres
        if (a_startX > a_endX) {
            std::swap(a_startX, a_endX);
            std::swap(a_startY, a_endY);
        }
        int yDirection = a_startY <= a_endY ? 1 : -1;
        for ( ; a_startX <= a_endX; ++a_startX) {
            stepVal += dy;
            if(stepVal >= dx) { // Increment y if enough x steps have been taken.
                stepVal -= dx;    // "Reset" StepVal by removing a dx amount
                a_startY += yDirection;
            }

            a_canvas(a_startX, a_startY) = a_brush; // DrawGroup a point
        }
    }
    else { // The slope is greater than 45 degrees, just like above, but with y instead of x.
        if (a_startY > a_endY) {
            std::swap(a_startX, a_endX);
            std::swap(a_startY, a_endY);
        }
        int xDirection = a_startX <= a_endX ? 1 : -1;
        for ( ; a_startY <= a_endY; ++a_startY) {
            stepVal += dx;
            if(stepVal >= dy) { // Increment y if enough x steps have been taken.
                stepVal -= dy;    // "Reset" StepVal by removing a dx amount
                a_startX += xDirection;
            }

            a_canvas(a_startX, a_startY) = a_brush; // DrawGroup a point
        }
    }        
}

// draw circle using mid-point circle algorithm 
template<class CanvasT>
void DrawCircle(CanvasT &a_canvas, char a_brush, int a_centerX, int a_centerY, double a_radius) {
    int dx = int(a_radius), dy = 0;
      
    // Printing the initial point on the axes after translation
    a_canvas(a_centerX + dx, a_centerY) = a_brush;
      
    // When radius is zero only a single point will be printed
    if (a_radius > 0.0) {
        a_canvas(a_centerX - dx, a_centerY) = a_brush;
        a_canvas(a_centerX, a_centerY + dx) = a_brush;
        a_canvas(a_centerX, a_centerY - dx) = a_brush;
    }
      
    // Initialising the value of P
    double P = 1 - a_radius;
    for (int dy = 1 ; dx > dy ; ++dy) { 
        // Mid-point is inside or on the perimeter
        if (P <= 0) {
            P = P + 2*dy + 1;
        }
        else { // Mid-point is outside the perimeter
            --dx;
            // All the perimeter points have already been printed
            if (dx < dy) {
                break;
            }

            P = P + 2*dy - 2*dx + 1;
        }
          
          
        a_canvas(a_centerX + dx, a_centerY + dy) = a_brush;
        a_canvas(a_centerX - dx, a_centerY + dy) = a_brush;
        a_canvas(a_centerX + dx, a_centerY - dy) = a_brush;
        a_canvas(a_centerX - dx, a_centerY - dy) = a_brush;
          
        // If the generated point is on the line x = y then 
        // the perimeter points have already been printed
        if (dx != dy) {
            a_canvas(a_centerX + dy, a_centerY + dx) = a_brush;
            a_canvas(a_centerX - dy, a_centerY + dx) = a_brush;
            a_canvas(a_centerX + dy, a_centerY - dx) = a_brush;
            a_canvas(a_centerX - dy, a_centerY - dx) = a_brush;
        }
    }
}

template<class CanvasT>
void DrawLine(CanvasT &a_canvas, char a_brush, const Point &a_start, const Point &a_end) {
    DrawLine(a_canvas, a_brush, a_start.GetX(), a_start.GetY(), a_end.GetX(), a_end.GetY());
}

template<class CanvasT>
void DrawCircle(CanvasT &a_canvas, char a_brush, const Point &a_center, size_t a_radius) {
    DrawCircle(a_canvas, a_brush, a_center.GetX(), a_center.GetY(), a_radius);
}

}
