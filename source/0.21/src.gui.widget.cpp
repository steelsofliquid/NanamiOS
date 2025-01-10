 #include "include.gui.widget.h"


Widget::Widget(
    Widget* parent, int32_t x, int32_t y, int32_t w,
    int32_t h, uint8_t r, uint8_t g, uint8_t b)
{
    this->parent = parent;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->r = r;
    this->g = g;
    this->b = b;
    this->Focussable = true;
}
Widget::~Widget()
{
}
    
void Widget::GetFocus(Widget* widget)
{
    if(parent != 0)
        parent->GetFocus(widget);
}

void Widget::ModelToScreen(int32_t &x, int32_t& y)
{
    if(parent != 0)
        parent->ModelToScreen(x,y);
        x += this->x;
        y += this->y;
}

void Widget::Draw(GraphicsContext* gc)
{
    int X = 0;
    int Y = 0;
    ModelToScreen(X,Y);
    gc->FillRectangle(X, Y, w, h,  r, g, b);
}

void Widget::OnMouseDown(int32_t x, int32_t y)
{
    if(Focussable)
        GetFocus(this);
}

void Widget::OnMouseUp(int32_t x, int32_t y)
{
}

void Widget::OnMouseMove(int32_t oldx, int32_t oldy, int32_t newx, int32_t newy)
{
}


void Widget::OnKeyDown(int32_t x, int32_t y)
{
}

void Widget::OnKeyUp(int32_t x, int32_t y)
{
}



CompositeWidget::CompositeWidget(Widget* parent,
            int32_t x, int32_t y, int32_t w, int32_t h,
            uint8_t r, uint8_t g, uint8_t b)
{
}

CompositeWidget::~CompositeWidget()
{
}

void CompositeWidget::GetFocus(Widget* widget)
{
    this->focussedChild = widget;
}

void CompositeWidget::Draw(GraphicsContext* gc)
{
}
void CompositeWidget::OnMouseDown(int32_t x, int32_t y)
{
}
void CompositeWidget::OnMouseUp(int32_t x, int32_t y)
{
}
void CompositeWidget::OnMouseMove(int32_t oldx, int32_t oldy, int32_t newx, int32_t newy)
{
}

void CompositeWidget::OnKeyDown(int32_t x, int32_t y)
{
}
void CompositeWidget::OnKeyUp(int32_t x, int32_t y)
{
}