//
// Created by Shun Hang Lo on 5/7/26.
//

#ifndef LVIM_EDITOR_H
#define LVIM_EDITOR_H
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <ncurses.h>

namespace lvim {
    class Editor {
    public:
        explicit Editor(std::string &filePath);
        explicit Editor(const char* filePath);
        Editor(Editor &&editor) = delete;
        Editor &operator=(const Editor &editor) = delete;
        ~Editor() = default;
        int getInput();
        int getCommand();
        int handleInput();
        void insertChar(char c);
        void deleteChar();
        void newLine(int vPos);
        void deleteLine(int vPos);
        void moveVert(int offset);
        void moveHorz(int offset);
        void save();
        void display() const;
    private:
        std::filesystem::path filePath;
        std::vector<std::string> content;
        size_t vPointer;
        size_t hPointer;
        int mode; // idle = 0, insert = 1
        WINDOW* modeBar;
        WINDOW* editor;
    };
}


#endif //LVIM_EDITOR_H