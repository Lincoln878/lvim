//
// Created by Shun Hang Lo on 5/7/26.
//
#include <Editor.h>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Please enter a filename to enter lvim!\n";
        return 0;
    }

    std::string filePath = argv[1];

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(1);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    lvim::Editor editor(filePath);

    attron(COLOR_PAIR(1));

    do {
        editor.display();
    } while (editor.handleInput() != -1);

    attroff(COLOR_PAIR(1));
    endwin();
    return 0;
}
