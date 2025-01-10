 
#ifndef __WIDGET_H
#define __WIDGET_H

#include "include.common.types.h"
#include "include.common.graphicscontext.h"

    class Widget
    {
    protected:
        Widget* parent;

        int32_t x;
        int32_t y;
        int32_t w;
        int32_t h;

        uint8_t r;
        uint8_t g;
        uint8_t b;
        bool Focussable;

    public:
        Widget(
            Widget* parent,
            int32_t x,
            int32_t y,
            int32_t w,
            int32_t h,
            uint8_t r,
            uint8_t g,
            uint8_t b
            );
        ~Widget();
    
        virtual void GetFocus(Widget* widget);
        virtual void ModelToScreen(int32_t &x, int32_t& y);

        virtual void Draw(GraphicsContext* gc);
        virtual void OnMouseDown(int32_t x, int32_t y);
        virtual void OnMouseUp(int32_t x, int32_t y);
        virtual void OnMouseMove(int32_t oldx, int32_t oldy, int32_t newx, int32_t newy);

        virtual void OnKeyDown(int32_t x, int32_t y);
        virtual void OnKeyUp(int32_t x, int32_t y);
    };

    class CompositeWidget : public Widget
    {
    private: 
        Widget* children[100];
        int numChildren;
        Widget* focussedChild;

    public:
        CompositeWidget(Widget* parent,
            int32_t x, int32_t y, int32_t w, int32_t h,
            uint8_t r, uint8_t g, uint8_t b);
        ~CompositeWidget();

        virtual void GetFocus(Widget* widget);

        virtual void Draw(GraphicsContext* gc);
        virtual void OnMouseDown(int32_t x, int32_t y);
        virtual void OnMouseUp(int32_t x, int32_t y);
        virtual void OnMouseMove(int32_t oldx, int32_t oldy, int32_t newx, int32_t newy);

        virtual void OnKeyDown(int32_t x, int32_t y);
        virtual void OnKeyUp(int32_t x, int32_t y);

    };

#endif