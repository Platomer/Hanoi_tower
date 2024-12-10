#include <iostream> 
#include <vector>
#include <string>
#include <ncurses.h>
#include <unistd.h>
//adding all towers
std::vector<int> A;
std::vector<int> B;
std::vector<int> C;
//function for printing state of towers
void print(const std::vector<int>& tower, int number)
{
    for (int i = tower.size(); i > 0; i--)
    {   std::string text((tower[i - 1] * 2) + 1, '8');
        mvprintw(21 - i, number - tower.size() + i, "%s", text.c_str());
    }
}
//function that will move donuts from one tower to another, only one move per tower is possible.
void move(std::vector<int>& one, std::vector<int>& two) {
    if (one.empty() && two.empty()) return;
    if (one.empty()) {
        one.push_back(two.back());
        two.pop_back();
    } else if (two.empty()) {
        two.push_back(one.back());
        one.pop_back();
    } else if (one.back() < two.back()) {
        two.push_back(one.back());
        one.pop_back();
    } else {
        one.push_back(two.back());
        two.pop_back();
    }
    clear();
    print(A, 10);
    print(B, 40);
    print(C, 70);
    refresh();
    usleep(50000);  //makes program stop after each move 
}
void hanoi_tower()
{   
    int height;
    std::cout << "How big you want your hanoi tower to be? :";
    std::cin >> height;
    std::cout << std::endl;
    initscr();
    //filling up first tower 
    for (int i = height; i > 0; i--)
    {
        A.push_back(i);
    }
    //checking if number of donuts is even
    bool even = false;
    if (height % 2 == 0) even = true;
    //moving algorythm, works differently based on height of tower
    while (C.size() != height) 
    {
        if (even) {
            move(A, B);
            if (C.size() == height) break;
            move(A, C);
            if (C.size() == height) break;
            move(B, C);
        } 
        else 
        {
            move(A, C);
            if (C.size() == height) break;
            move(A, B);
            if (C.size() == height) break;
            move(B, C);
        }
    }
    sleep(2);   
}
int main()
{
    hanoi_tower();
    endwin();
}