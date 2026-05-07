//
// Created by Shun Hang Lo on 5/7/26.
//

#include <iostream>
#include <format>
#include "Editor.h"
using namespace lvim;

Editor::Editor(std::string &filePath)
    : filePath(std::move(filePath)), vPointer(0), hPointer(0), mode(0) {
    content.emplace_back("");
    int max_y = getmaxy(stdscr);
    int max_x = getmaxx(stdscr);

    editor = newwin(max_y - 1, max_x, 0, 0);
    modeBar = newwin(1, max_x, max_y - 1, 0);

    leaveok(modeBar, TRUE);
    leaveok(editor, FALSE);
    wrefresh(modeBar);
    wrefresh(editor);
}

Editor::Editor(const char* filePath)
    : filePath(filePath), vPointer(0), hPointer(0), mode(0) {
    content.emplace_back("");
    int max_y = getmaxy(stdscr);
    int max_x = getmaxx(stdscr);

    editor = newwin(max_y - 1, max_x, 0, 0);
    modeBar = newwin(1, max_x, max_y - 1, 0);

    leaveok(modeBar, TRUE);
    leaveok(editor, FALSE);
    wrefresh(modeBar);
    wrefresh(editor);
}

void Editor::moveHorz(const int offset) {
    hPointer = std::max(std::min(
        hPointer + offset,
        content[vPointer].size()
        ), static_cast<size_t>(0));
}

void Editor::moveVert(const int offset) {
    vPointer = std::max(std::min(
        vPointer + offset,
        content.size() - 1
        ), static_cast<size_t>(0));
}

void Editor::newLine(const int vPos) { content.insert(content.begin() + (vPos + 1), ""); }

void Editor::deleteLine(const int vPos) {
    if (vPos > content.size() - 1)
        return;

    content.erase(content.begin() + vPos);
}

void Editor::insertChar(const char c) {
    if (hPointer == content[vPointer].size()) {
        content[vPointer] += c;
    } else {
        content[vPointer].insert(
            content[vPointer].begin() + static_cast<int>(hPointer),
            c);
    }
    moveHorz(1);
}

void Editor::deleteChar() {
    if (!content[vPointer].empty()) {
        if (hPointer) {
            content[vPointer].erase(content[vPointer].begin() + (static_cast<int>(hPointer) - 1));
            moveHorz(-1);
        } else {
            if (vPointer != 0) {
                hPointer = content[vPointer - 1].size();
                content[vPointer - 1].append(content[vPointer]);
                content.erase(content.begin() + static_cast<int>(vPointer));
                moveVert(-1);
            }
        }
    } else if (vPointer) {
        content.erase(content.begin() + static_cast<int>(vPointer));
        moveVert(-1);
        hPointer = content[vPointer].size();
    }
}

char Editor::getInput() {
    int c = getch();
    if (c == KEY_ENTER || c == '\n') {
        if (content[vPointer].size() != hPointer) {
            std::string suffix = content[vPointer].substr(hPointer);
            if (const int nextPos = static_cast<int>(vPointer) + 1; nextPos == content.size()) {
                content.emplace_back(suffix);
            } else {
                content.insert(content.begin() + nextPos, suffix);
            }
        } else {
            newLine(static_cast<int>(vPointer));
        }
        moveVert(1);
        moveHorz(-static_cast<int>(hPointer));
        return c;
    }

    if (c == KEY_BACKSPACE || c == 127 || c == 8) {
        deleteChar();
        return c;
    }

    switch (c) {
        case KEY_UP:
            moveHorz(-1);
            break;
        case KEY_DOWN:
            if (content[vPointer].size() != vPointer + 1) newLine(static_cast<int>(vPointer));
            moveHorz(1);
            break;
        case KEY_LEFT:
            moveHorz(-1);
            break;
        case KEY_RIGHT:
            moveHorz(1);
            break;
        default:
            insertChar(static_cast<char>(c));
    }

    return c;
}

void Editor::save() {

}

void Editor::display() const {
    wclear(editor);
    box(editor, 0, 0);
    wclear(modeBar);
    const size_t lineCount = content.size();
    for (size_t i=0;i<lineCount;i++) {
        mvwprintw(editor, static_cast<int>(i) + 1, 1, "%s", content[i].c_str());
    }

    const int max_y = getmaxy(stdscr);
    mvwprintw(modeBar, 0, 0, "%s", std::format("mode: {}", mode ? "INSERT" : "IDLE").c_str());
    wmove(editor, static_cast<int>(vPointer) + 1, static_cast<int>(hPointer) + 1);
    wrefresh(modeBar);
    wrefresh(editor);
}

