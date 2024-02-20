#pragma once

namespace conways_game_of_life
{
    inline float normalize(float min, float max, float val) { return (val - min) / (max - min); }
    // KK - These should never be negative, right?
    inline unsigned int convert_indices(unsigned int x, unsigned int y, unsigned int width) { return (y * width) + x; }
} // namespace conways_game_of_life
