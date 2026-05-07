//
// Created by Shun Hang Lo on 5/7/26.
//
#include <string>
#include <Editor.h>
#include <iostream>

int main(int argc, char** argv) {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(1);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    lvim::Editor editor("test.txt");

    attron(COLOR_PAIR(1));

    while (editor.getInput() != '|') {
        editor.display();
    }

    attroff(COLOR_PAIR(1));
    endwin();

    // for (auto& x : editor.content) {
    //     std::cout << "|" << x << "|" << std::endl;
    // }
    // int x = 1;
    // std::cin >> x;
    return 0;
}
