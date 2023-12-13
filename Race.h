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

    bool can_move()
    {
        return can_move_bool;
    }

    void set_move()
    {
        can_move_bool = not(can_move_bool);
    }

private:
    Point xy{0, 0};
    Point xy_standart{0, 0};
    bool can_move_bool{true};
};

struct My_window : Graph_lib::Window
{
    My_window(Graph_lib::Point xy, int w, int h, const std::string &title)
        : Graph_lib::Window{xy, w, h, title},
          next_button{Graph_lib::Point{x_max() / 2 - 50, y_max() / 2 + 128}, 100, 20, "Throw the dice", cb_next},
          rules_button{Graph_lib::Point{x_max() - 70, 0}, 70, 20, "Rules", cb_rules}
    {
        attach(next_button);
        // attach(rules_button);
    }

    int Fl_wait()
    {
        return Fl::wait();
    }

    void wait_for_button()
    {
        while (!button_pushed && Fl::wait())
            ;
        button_pushed = false;
        Fl::redraw();
    }

    Graph_lib::Button next_button;
    Graph_lib::Button rules_button;

private:
    bool button_pushed{false};

    static void cb_next(Graph_lib::Address, Graph_lib::Address addr) // callback for next_button
    {
        auto *pb = static_cast<Graph_lib::Button *>(addr);
        static_cast<My_window &>(pb->window()).next();
    }

    static void cb_rules(Graph_lib::Address, Graph_lib::Address addr) // callback for next_button
    {
        auto *pb = static_cast<Graph_lib::Button *>(addr);
        static_cast<My_window &>(pb->window()).rules();
    }

    void next() { button_pushed = true; }
    void rules()
    {
        Simple_window win(Point(x_max() / 2, y_max() / 2), x_max() / 2, y_max() / 2, "Rules");
        Image rules(Point(x_max() / 4, y_max() / 4), "game_rules.png");
        win.attach(rules);

        win.show();
        Fl::run();
    }
};
struct Field
{
    Vector_ref<Knight> coordinates_knights_vec;

    Field(int win_w, int win_h)
    {
        this->win_h = win_h;
        this->win_w = win_w;
        draw_point_table(win_w, win_h);
    }

    void attach_pole(My_window &win);
    int current_steps(int player);

    void change_text(int player, int steps_now);
    void move_knights(int win_w, int win_h, int player, int steps);

    int win_h_value() { return win_h; }
    int win_w_value() { return win_w; }

private:
    int win_h = 0;
    int win_w = 0;

    void draw_point_table(int win_w, int win_h);
    void create_knights(int win_w, int win_h);
    void create_circles(int win_w, int win_h);
    void create_lines(int win_w, int win_h);

    Vector_ref<Circle> circles_vec;
    Vector_ref<Line> lines_vec;
    Vector_ref<Mark> marks_vec;
    Vector_ref<Text> text_vec;

    std::vector<int> steps_vec{0, 0, 0, 0};
    std::vector<std::string> string_vec{"blue points:", "red points:", "yellow points:", "green points:"};
};