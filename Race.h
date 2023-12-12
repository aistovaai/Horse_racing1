#include <Graph_lib/Simple_window.h>
using namespace Graph_lib;
#include <iostream>

struct Knight : Image
{
    Knight(Point xy, const std::string &s, Suffix::Encoding e = Suffix::none) : Image(xy, s, e)
    {
        this->xy += xy;
        this->xy_standart += xy;
    }

    int x();

    int y();

    int x_standart();

    int y_standart();

    void move(int dx, int dy) override;

private:
    Point xy{0, 0};
    Point xy_standart{0, 0};
};

void coordinates_knights(int win_w, int win_h);

void move_knights(int win_w, int win_h, int player, int steps);

void circles(int win_w, int win_h);

void lines(int win_w, int win_h);

struct My_window : Simple_window
{
    My_window(Point xy, int w, int h, const std::string &title)
        : Simple_window{xy, w, h, title}, quit_button{Point{x_max() - 70, 20}, 70, 20, "Quit", cb_quit}
    {
        attach(quit_button);
    }

    Graph_lib::Button quit_button;

private:
    static void cb_quit(Address, Address widget)
    {
        auto &btn = Graph_lib::reference_to<Graph_lib::Button>(widget);
        dynamic_cast<My_window &>(btn.window()).quit();
    }
    void quit() { hide(); }
};

void change_text(int player, int steps_now);

void draw_pole(My_window &win, int win_w, int win_h);

int steps_check(int player);