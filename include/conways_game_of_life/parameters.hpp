#pragma once

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define CELL_SIZE_PX 10.0

#define COLUMNS (int)(WINDOW_WIDTH / CELL_SIZE_PX)
#define ROWS (int)(WINDOW_HEIGHT / CELL_SIZE_PX)

#define COLOR_MIN 0
#define COLOR_MAX 255

#define BG_RED 117
#define BG_GREEN 117
#define BG_BLUE 117

#define LINE_RED 0
#define LINE_GREEN 0
#define LINE_BLUE 0

#define CELL_ON_RED 100
#define CELL_ON_GREEN 10
#define CELL_ON_BLUE 255

#define CELL_OFF_RED 50
#define CELL_OFF_GREEN 50
#define CELL_OFF_BLUE 50

#define DEFAULT_FPS 10
#define MAX_FPS 170
#define MIN_FPS 1
#define FPS_STEP 10

#include <conways_game_of_life/util.hpp>

namespace conways_game_of_life
{
  //! \brief Window background color red component normalized to the range 0-1.
  const float bg_red = normalize(COLOR_MIN, COLOR_MAX, BG_RED);
  //! \brief Window background color green component normalized to the range 0-1.
  const float bg_green = normalize(COLOR_MIN, COLOR_MAX, BG_GREEN);
  //! \brief Window background color blue component normalized to the range 0-1.
  const float bg_blue = normalize(COLOR_MIN, COLOR_MAX, BG_BLUE);

  //! \brief Grid line color red component normalized to the range 0-1.
  const float line_red = normalize(COLOR_MIN, COLOR_MAX, LINE_RED);
  //! \brief Grid line color green component normalized to the range 0-1.
  const float line_green = normalize(COLOR_MIN, COLOR_MAX, LINE_GREEN);
  //! \brief Grid line color blue component normalized to the range 0-1.
  const float line_blue = normalize(COLOR_MIN, COLOR_MAX, LINE_BLUE);

  //! \brief Live cell color red component normalized to the range 0-1.
  const float cell_on_red = normalize(COLOR_MIN, COLOR_MAX, CELL_ON_RED);
  //! \brief Live cell color green component normalized to the range 0-1.
  const float cell_on_green = normalize(COLOR_MIN, COLOR_MAX, CELL_ON_GREEN);
  //! \brief Live cell color blue component normalized to the range 0-1.
  const float cell_on_blue = normalize(COLOR_MIN, COLOR_MAX, CELL_ON_BLUE);

  //! \brief Dead cell color red component normalized to the range 0-1.
  const float cell_off_red = normalize(COLOR_MIN, COLOR_MAX, CELL_OFF_RED);
  //! \brief Dead cell color green component normalized to the range 0-1.
  const float cell_off_green = normalize(COLOR_MIN, COLOR_MAX, CELL_OFF_GREEN);
  //! \brief Dead cell color blue component normalized to the range 0-1.
  const float cell_off_blue = normalize(COLOR_MIN, COLOR_MAX, CELL_OFF_BLUE);
} // namespace conways_game_of_life
