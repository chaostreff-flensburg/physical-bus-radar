#pragma once

#include <Arduino.h>

// Line -> RGB color table. Mirrors base.py:16-67 / .env.needtoedit.
struct LineColor {
    const char* line;
    uint32_t    rgb;  // 0xRRGGBB
};

constexpr LineColor LINE_COLORS[] = {
    {"1",  0x00ff00},
    {"2",  0xf2ee00},
    {"3",  0x97dc4d},
    {"4",  0xfe9ec9},
    {"5a", 0xf40033},
    {"5b", 0xf40033},
    {"7",  0x0000ff},
    {"8a", 0xf49f25},
    {"8b", 0xf49f25},
    {"10", 0x87d7f5},
    {"11", 0xaf1a82},
    {"12", 0x40f7bd},
    {"14", 0xad8f70},
};
constexpr size_t LINE_COLOR_COUNT = sizeof(LINE_COLORS) / sizeof(LINE_COLORS[0]);

// Whitelist: only these lines are drawn. Matches main.py:65.
constexpr const char* ACTIVE_LINES[] = {"1", "7"};
constexpr size_t ACTIVE_LINE_COUNT = sizeof(ACTIVE_LINES) / sizeof(ACTIVE_LINES[0]);

inline bool line_is_active(const char* line) {
    for (size_t i = 0; i < ACTIVE_LINE_COUNT; ++i) {
        if (strcmp(line, ACTIVE_LINES[i]) == 0) return true;
    }
    return false;
}

inline uint32_t color_for_line(const char* line) {
    for (size_t i = 0; i < LINE_COLOR_COUNT; ++i) {
        if (strcmp(line, LINE_COLORS[i].line) == 0) return LINE_COLORS[i].rgb;
    }
    return 0xffffff;
}
