#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <functional>
#include <time.h>
#include <iostream>

using namespace std;

//**************** Types definitions **********************//
class Sandbox; class Base_Cell; class Sand_Cell; class Water_Cell; class Simulation; class Sandbox_Shape;
typedef vector<Base_Cell*> Cell_Array;
typedef vector<Cell_Array> Cell_Matrix;

//**************** Prototypes **********************//
std::string str(sf::VertexArray* cell_vertex, int w, int h);
std::string str(Cell_Matrix* cell_array);

class Base_Cell { public:
    int x = 0;
    int y = 0;
    Sandbox* sandbox = nullptr;
    bool checked = false;
    bool fluid = true;
    float viscosity = 0;
    float mass = 0;

    Base_Cell(Sandbox* sandbox = nullptr, sf::Vector2i pos = sf::Vector2i(0, 0));
    virtual sf::Color get_color();
    sf::Vector2i get_pos();
    virtual void update();
    void update_color(sf::VertexArray* cell_vertex, int);
    virtual bool sink_into(Base_Cell* cell);
    Base_Cell* get_cell(int i, int j);
    virtual std::string str();
};

class Sand_Cell : public Base_Cell{ public:
    Sand_Cell(Sandbox* sandbox = nullptr, sf::Vector2i pos = sf::Vector2i(0, 0));
    void update();
    sf::Color get_color();
    virtual std::string str();
};

class Water_Cell : public Base_Cell { public:
    Water_Cell(Sandbox* sandbox = nullptr, sf::Vector2i pos = sf::Vector2i(0, 0));
    void update();
    sf::Color get_color();
    virtual std::string str();

    
};

class Sandbox { public:
    int w = 10;
    int h = 10;
    Cell_Matrix* cell_array = new Cell_Matrix();
    sf::VertexArray* cell_vertex;
    sf::VertexArray* grid;

    Sandbox(int w, int h);
    void swap_cells(Base_Cell*, Base_Cell*);
    void insert_cell(Base_Cell*, sf::Vector2i pos);
    void sync_vertex();
    void update_cell(Base_Cell*);
    void update_cells();
    Base_Cell* get_cell_by_pixel(sf::Vector2i pos, float x_scale, float y_scale);
    void scale_to(int, int);
};

class Simulation { public :
    Sandbox* sandbox = nullptr;
    int screen_w = 10;
    int screen_h = 10;
    sf::RenderWindow* window;
    int max_fps = 60;
    int frames = 0;
    sf::Clock one_second_clock;
    sf::Clock next_frame_clock;
    bool pause = false;
    function<Base_Cell* (void)> cell_maker = []() {return new Sand_Cell(); };
    bool draw_grid = true;

    Simulation(Sandbox* sandbox, int screen_w = 420, int screen_h = 420, int max_fps = 60);
    void run();
    void update_window();
    void insert_new_cell();

};


//**************** Base_Cell method definition **********************//
Base_Cell::Base_Cell(Sandbox* sandbox, sf::Vector2i pos) :
    sandbox(sandbox), x(pos.x), y(pos.y){}

sf::Vector2i Base_Cell::get_pos() {
    return sf::Vector2i(x, y);
}

sf::Color Base_Cell::get_color() {
    return sf::Color(0, 0, 0);
}

void Base_Cell::update() {
    //do nothing
}

void Base_Cell::update_color(sf::VertexArray* cell_vertex, int h) {
    sf::Color color = this->get_color();
    int k = 4 * (x * h + y);
    (*cell_vertex)[k].color = color;
    (*cell_vertex)[k + 1].color = color;
    (*cell_vertex)[k + 2].color = color;
    (*cell_vertex)[k + 3].color = color;
}

bool Base_Cell::sink_into(Base_Cell* cell) {
    if (cell && cell->fluid && cell->mass < this->mass) {
        sandbox->swap_cells(this, cell);
        return true;
    }
    return false;
}

Base_Cell* Base_Cell::get_cell(int i, int j) {
    if (0 <= x+i && x+i < sandbox->w && 0 <= y+j && y+j < sandbox->h) 
        return (*sandbox->cell_array)[x + i][y + j];
    return nullptr;
}

std::string Base_Cell::str()
{
    return "0";
}

//**************** Sand_Cell method definition **********************//
Sand_Cell::Sand_Cell(Sandbox* sandbox, sf::Vector2i pos) :
    Base_Cell::Base_Cell(sandbox, pos) {
    mass = 0.8;
}

void Sand_Cell::update() {
    if (sink_into(get_cell(0, 1))) return;
    int x = 1;
    if (rand() % 100 < 50) x = 1;
    if (sink_into(get_cell(x, 1))) return;
    if (sink_into(get_cell(-x, 1))) return;
}

sf::Color Sand_Cell::get_color() {
    return sf::Color(76, 70, 50);
}

std::string Sand_Cell::str()
{
    return "1";
}

//**************** Water_Cell method definition **********************//
Water_Cell::Water_Cell(Sandbox* sandbox, sf::Vector2i pos) :
    Base_Cell::Base_Cell(sandbox, pos){
    mass = 0.2;
}

void Water_Cell::update()
{
    if (sink_into(get_cell(0, 1))) return;
    int x = 1;
    if (rand() % 100 < 50) x = -1;
    if (sink_into(get_cell(x, 1))) return;
    if (sink_into(get_cell(-x, 1))) return;
    if (sink_into(get_cell(x, 0))) return;
    if (sink_into(get_cell(-x, 0))) return;
}

sf::Color Water_Cell::get_color()
{
    return sf::Color(35, 137, 218);
}

std::string Water_Cell::str()
{
    return "2";
}
//**************** Sandbox method definition **********************//
Sandbox::Sandbox(int w, int h) : w(w), h(h)
{
    cell_array = new Cell_Matrix(w, Cell_Array(h, nullptr));
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++) 
            (*cell_array)[i][j] = new Base_Cell(this, sf::Vector2i(i, j));

    grid = new sf::VertexArray(sf::Lines, 2*w + 2*h);
    cell_vertex = new sf::VertexArray(sf::Quads, w * h * 4);
    int k = 0;
    scale_to(w, h);
}

void Sandbox::swap_cells(Base_Cell* cell1, Base_Cell* cell2) {
    Base_Cell* temp = cell1;
    (*cell_array)[cell1->x][cell1->y] = cell2;
    (*cell_array)[cell2->x][cell2->y] = temp;
    swap(cell1->x, cell2->x);
    swap(cell1->y, cell2->y);

    cell1->update_color(cell_vertex, this->h);
    cell2->update_color(cell_vertex, this->h);
}

void Sandbox::insert_cell(Base_Cell* cell, sf::Vector2i pos)
{
    cell->x = pos.x;
    cell->y = pos.y;
    cell->sandbox = this;
    (*cell_array)[pos.x][pos.y] = cell;
    cell->update_color(this->cell_vertex, this->h);
}

void Sandbox::sync_vertex()
{
    for (auto& cells : *cell_array)
        for (auto cell : cells)
            cell->update_color(cell_vertex, this->h);
}

void Sandbox::update_cell(Base_Cell* cell)
{
    if (!cell->checked) {
        cell->update();
        cell->checked = true;
    }
}

void Sandbox::update_cells()
{
    int rand = std::rand() % 101;
    if (rand > 75) {
        for (auto it = cell_array->begin(); it != cell_array->end(); it++)
            for (auto jt = it->begin(); jt != it->end(); jt++)
                update_cell((*jt));
    }
    else if (rand > 50) {
        for (auto it = cell_array->begin(); it != cell_array->end(); it++)
            for (auto jt = it->rbegin(); jt != it->rend(); jt++)
                update_cell((*jt));
    }
    else if (rand > 25) {
        for (auto it = cell_array->rbegin(); it != cell_array->rend(); it++)
            for (auto jt = it->begin(); jt != it->end(); jt++)
                update_cell((*jt));
    }
    else {
        for (auto it = cell_array->rbegin(); it != cell_array->rend(); it++)
            for (auto jt = it->rbegin(); jt != it->rend(); jt++)
                update_cell((*jt));
    }

    for (auto& cells : *cell_array)
        for (auto cell : cells)
            cell->checked = false;
}

Base_Cell* Sandbox::get_cell_by_pixel(sf::Vector2i pos, float x_scale, float y_scale)
{
    int x_cell = pos.x / x_scale;
    int y_cell = pos.y / y_scale;

    return (*cell_array)[x_cell][y_cell];
}

void Sandbox::scale_to(int _w, int _h)
{
    int k = 0;
    float scale_x = _w / float(w);
    float scale_y = _h / float(h);

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            float x_step = i * scale_x;
            float y_step = j * scale_y;
            (*cell_vertex)[k].position = sf::Vector2f(x_step, y_step); k++;
            (*cell_vertex)[k].position = sf::Vector2f(x_step, y_step + scale_y); k++;
            (*cell_vertex)[k].position = sf::Vector2f(x_step + scale_x, y_step + scale_y); k++;
            (*cell_vertex)[k].position = sf::Vector2f(x_step + scale_x, y_step); k++;
        }
    }
    for (int i = 0; i < w*2; i+=2) {
        (*grid)[i].position = sf::Vector2f(i/2 * scale_x, 0);
        (*grid)[i+1].position = sf::Vector2f(i/2 * scale_x, h * scale_y);
    }
         
    for (int i = 0; i < h*2; i+=2) {
        (*grid)[i + w*2].position = sf::Vector2f(0, i/2 * scale_y);
        (*grid)[i + w*2 + 1].position = sf::Vector2f(w * scale_y, i/2 * scale_y);
    }
    
}
//**************** Simulation method definition **********************//
Simulation::Simulation(Sandbox* sandbox, int screen_w, int screen_h, int max_fps):
    sandbox(sandbox), screen_w(screen_w), screen_h(screen_h), max_fps(max_fps){
    window = new sf::RenderWindow(sf::VideoMode(screen_w, screen_h), "SFML works!");
    
    sandbox->scale_to(screen_w, screen_h);
    sandbox->sync_vertex();
    cout << str(sandbox->cell_vertex, sandbox->w, sandbox->h) << endl << endl;
    cout << str(sandbox->cell_array) << endl << endl;
    
     
}

void Simulation::run()
{
    bool running = true;
    bool mouse_pressed = false;
    pause = false;
    sf::Vector2i mouse_pos;
    draw_grid = false;

    update_window();

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {

            switch (event.type) {
            case sf::Event::Closed:
                running = false;
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                mouse_pressed = true;
                mouse_pos = sf::Mouse::getPosition(*window);
                std::cout << "(" << mouse_pos.x << ", " << mouse_pos.y << ")" <<endl;
                break;
            case sf::Event::MouseButtonReleased:
                mouse_pressed = false;
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::P:
                    pause = !pause;
                    break;
                case sf::Keyboard::G:
                    draw_grid = !draw_grid;

                case sf::Keyboard::Numpad1:
                    cell_maker = []() {return new Sand_Cell(); };
                    break;
                case sf::Keyboard::Numpad2:
                    cell_maker = []() {return new Water_Cell(); };
                    break;
                case sf::Keyboard::Numpad3:
                    sandbox->update_cells();
                    //update_window();
                    cout << str(sandbox->cell_array) << endl;
                    sandbox->sync_vertex();
                    cout << str(sandbox->cell_vertex, sandbox->w, sandbox->h) << endl;
                    break;
                }

            }

        }

        if (mouse_pressed)
            insert_new_cell();
        update_window();
        if (!pause && one_second_clock.getElapsedTime().asMilliseconds() >= 1000) {
            cout << frames << endl;
            frames = 0;
            one_second_clock.restart();
        }
        if (!pause && next_frame_clock.getElapsedTime().asMilliseconds() >= 1 / max_fps * 1000) {
            sandbox->update_cells();
            //update_window();
            frames++;
            next_frame_clock.restart();
        }

            
    }
}

void Simulation::update_window()
{
    window->clear();
    window->draw(*sandbox->cell_vertex);
    if (draw_grid)
        window->draw(*sandbox->grid);
    window->display();
        
    
}

void Simulation::insert_new_cell()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
    //cout << window->getSize().x << "," << window->getSize().y << endl;
    float scale_x = window->getSize().x / float(sandbox->w);
    float scale_y = window->getSize().y / float(sandbox->h);
    sf::Vector2i cell = sandbox->get_cell_by_pixel(mouse_pos, scale_x, scale_y)->get_pos();
    sandbox->insert_cell(cell_maker(), cell);
}

int main()
{
    Sandbox* sandbox = new Sandbox(100, 50);
    sandbox->insert_cell(new Sand_Cell(), sf::Vector2i(1, 2));
    Simulation* simulation = new Simulation(sandbox, 1600, 800, 1000);
    simulation->run();

    return 0;
}



//**************** Str func **********************//
std::string str(Cell_Matrix* cell_array) {
    std::string res = "";
    std::string line = "";
    for (auto i = 0; i < cell_array->size(); i++) {
        line = "";
        for (auto j = 0; j < (*cell_array)[i].size(); j++) 
            line += (*cell_array)[i][j]->str() + "|";
        res += line + "\n";
    }
    return res;
}

std::string str(sf::VertexArray* cell_vertex, int w, int h) {
    std::string res = "";
    std::string line = "";
    sf::Vertex vertex;
    int k = 0;
    for (auto i = 0; i < w; i++) {
        line = "";
        for (auto j = 0; j < h; j++) {
            line += "[";
            for (auto l = 0; l < 4; l++){
                vertex = (*cell_vertex)[k++];
                line += "(" + std::to_string(vertex.position.x).substr(0, 1) + "," + std::to_string(vertex.position.y).substr(0, 1) + ")" + std::to_string(vertex.color.r) + " ";
            }
            line += "]\n";

        }
        res += line + "\n";
    }
    return res;
}
