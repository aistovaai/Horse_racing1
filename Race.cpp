#include <Graph_lib/Simple_window.h>
#include "Race.h"
#include <vector>
#include "string.h"
#include <iostream>
#include <string>

using namespace Graph_lib;

int moves = 24;

Vector_ref<Circle> circles_vec;
Vector_ref<Line> lines_vec;
Vector_ref<Mark> marks_vec;
Vector_ref<Knight> coordinates_knights_vec;
Vector_ref<Text> text_vec;

std::vector<int> steps_vec(4);
std::vector<std::string> string_vec = {"blue points:", "red points:", "yellow points:", "green points:"};

int Knight::x()
{
    return xy.x;
}

int Knight::y()
{
    return xy.y;
}

int Knight::x_standart()
{
    return xy_standart.x;
}

int Knight::y_standart()
{
    return xy_standart.y;
}

void Knight::move(int dx, int dy)
{
    Image::move(dx, dy);
    xy.x += dx;
    xy.y += dy;
}

void coordinates_knights(int win_w, int win_h)
{
    Point player_1(win_w / 2 - std::min(win_w, win_h) / 4, win_h / 2);
    Point player_2(win_w / 2 - std::min(win_w, win_h) * 4 / 12, win_h / 2);
    Point player_3(win_w / 2 - std::min(win_w, win_h) * 5 / 12, win_h / 2);
    Point player_4(win_w / 2 - std::min(win_w, win_h) / 2, win_h / 2);

    marks_vec.push_back(new Mark(player_1, '^'));
    marks_vec.push_back(new Mark(player_2, '^'));
    marks_vec.push_back(new Mark(player_3, '^'));
    marks_vec.push_back(new Mark(player_4, '^'));

    coordinates_knights_vec.push_back(new Knight(player_1, "Knight2.png"));
    coordinates_knights_vec.push_back(new Knight(player_2, "Knight3.png"));
    coordinates_knights_vec.push_back(new Knight(player_3, "Knight4.png"));
    coordinates_knights_vec.push_back(new Knight(player_4, "Knight5.png"));
}

void move_knights(int win_w, int win_h, int player, int steps)
{
    float up_radius = std::min(win_w, win_h) / 2;
    float down_radius = std::min(win_w, win_h) / 4; // неловко вышло
    float horse_step = 360 / moves;

    float radius_for_1 = std::min(win_w, win_h) / 4 + std::min(win_w, win_h) / 12;
    float radius_for_2 = std::min(win_w, win_h) / 4 + std::min(win_w, win_h) / 6;

    steps_vec[player] += steps;

    float cos_x_coef = (1 - cos(2 * pi * steps_vec[player] * horse_step / 360));
    float sin_y_coef = sin(2 * pi * steps_vec[player] * horse_step / 360);

    int x_standart = coordinates_knights_vec[player].x_standart();
    int y_standart = coordinates_knights_vec[player].y_standart();

    int x_now = coordinates_knights_vec[player].x();
    int y_now = coordinates_knights_vec[player].y();

    coordinates_knights_vec[player].move(x_standart - x_now, y_standart - y_now);
    marks_vec[player].move(x_standart - x_now, y_standart - y_now);

    switch (player)
    {
    case 0:

        coordinates_knights_vec[player].move(down_radius * cos_x_coef, -down_radius * sin_y_coef);
        marks_vec[player].move(down_radius * cos_x_coef, -down_radius * sin_y_coef);
        break;

    case 1:

        coordinates_knights_vec[player].move(radius_for_1 * cos_x_coef, -radius_for_1 * sin_y_coef);
        marks_vec[player].move(radius_for_1 * cos_x_coef, -radius_for_1 * sin_y_coef);
        break;

    case 2:

        coordinates_knights_vec[player].move(radius_for_2 * cos_x_coef, -radius_for_2 * sin_y_coef);
        marks_vec[player].move(radius_for_2 * cos_x_coef, -radius_for_2 * sin_y_coef);
        break;

    case 3:

        coordinates_knights_vec[player].move(up_radius * cos_x_coef, -up_radius * sin_y_coef);
        marks_vec[player].move(up_radius * cos_x_coef, -up_radius * sin_y_coef);
        break;

    default:
        break;
    }
}

void circles(int win_w, int win_h)
{
    Graph_lib::Circle down(Point(win_w / 2, win_h / 2), std::min(win_w, win_h) / 4);
    Graph_lib::Circle up(Point(win_w / 2, win_h / 2), std::min(win_w, win_h) / 2);

    circles_vec.push_back(new Circle(Point(win_w / 2, win_h / 2), std::min(win_w, win_h) / 4));
    circles_vec.push_back(new Circle(Point(win_w / 2, win_h / 2), std::min(win_w, win_h) / 2));
}

void lines(int win_w, int win_h)
{
    Point center = Point(win_w / 2, win_h / 2);
    float up_radius = std::min(win_w, win_h) / 2;
    float down_radius = std::min(win_w, win_h) / 4;

    Point start_1{center.x - up_radius, center.y}; // ну сужающее преоборазование и сужающее че поделать не злиться же
    Point start_2{center.x - down_radius, center.y};

    float horse_step = 360 / moves;

    lines_vec.push_back(new Line{start_1, start_2});

    for (int i = 1; i < moves; ++i)
    {
        Point start_new_1 = Point(start_1.x + up_radius * (1 - cos(2 * pi * i * horse_step / 360)),
                                  start_1.y - up_radius * sin(2 * pi * i * horse_step / 360));

        Point start_new_2 = Point(start_2.x + down_radius * (1 - cos(2 * pi * i * horse_step / 360)),
                                  start_2.y - down_radius * sin(2 * pi * i * horse_step / 360));

        lines_vec.push_back(new Line{start_new_1, start_new_2});
    }

    lines_vec[0].set_style(FL_DOT);
    lines_vec[12].set_style(FL_DOT);

    lines_vec[0].set_color(FL_RED);
    lines_vec[12].set_color(FL_RED);
}

void draw_point_table(int win_w, int win_h)
{
    Point player_1(win_w / 2 - std::min(win_w, win_h) * 8 / 11, win_h / 2 + win_h / 4);
    Point player_2(win_w / 2 - std::min(win_w, win_h) * 8 / 11, win_h / 2 + win_h / 3);
    Point player_3(win_w / 2 - std::min(win_w, win_h) * 8 / 11, win_h / 2 - win_h / 3);
    Point player_4(win_w / 2 - std::min(win_w, win_h) * 8 / 11, win_h / 2 - win_h / 4);

    text_vec.push_back(new Text(player_1, "blue points: 0"));   // blue
    text_vec.push_back(new Text(player_2, "red points: 0"));    // red
    text_vec.push_back(new Text(player_3, "yellow points: 0")); // yellow
    text_vec.push_back(new Text(player_4, "green points: 0"));  // green

    for (int i = 0; i < text_vec.size(); i++)
    {
        text_vec[i].set_font(FL_COURIER);
        text_vec[i].set_font_size(18);
    }
}

void change_text(int player, int steps_now)
{
    std::string x = string_vec[player] + " " + std::to_string(steps_vec[player] + steps_now);

    text_vec[player].set_font(FL_COURIER);
    text_vec[player].set_font_size(18);

    text_vec[player].set_label(x);
}

void draw_pole(My_window &win, int win_w, int win_h)
{
    lines(win_w, win_h);
    coordinates_knights(win_w, win_h);
    circles(win_w, win_h);
    draw_point_table(win_w, win_h);

    for (int i = 0; i < moves; ++i)
    {
        win.attach(lines_vec[i]); // отрисовали линии
    }

    for (int i = 0; i < text_vec.size(); ++i)
    {
        win.attach(text_vec[i]); // отрисовали линии
    }

    for (int i = 0; i < circles_vec.size(); ++i)
    {
        win.attach(circles_vec[i]); // отрисовали два кружочка
    }

    for (int i = 0; i < coordinates_knights_vec.size(); ++i)
    {
        win.attach(marks_vec[i]);
        win.attach(coordinates_knights_vec[i]);
    }
}

int steps_check(int player)
{
    return (steps_vec[player]);
}