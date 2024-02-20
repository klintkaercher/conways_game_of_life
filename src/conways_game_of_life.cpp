#include <GL/freeglut_std.h>
#include <cmath>

#include <GL/gl.h>
#include <GL/glut.h>

#include <conways_game_of_life/board.hpp>
#include <conways_game_of_life/conways_game_of_life.hpp>
#include <conways_game_of_life/parameters.hpp>

namespace cgl = conways_game_of_life;

unsigned int fps = DEFAULT_FPS;
cgl::ConwaysGameOfLife<COLUMNS, ROWS> game;

int main(int argc, char *argv[])
{
  // Window initialization
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Conway's Game of Life");

  // Register callbacks
  glutDisplayFunc(display_callback);
  glutReshapeFunc(reshape_callback);
  glutTimerFunc(0, timer_callback, 0);
  glutSpecialFunc(special_keys_callback);
  glutKeyboardFunc(keyboard_callback);
  glutMouseFunc(mouse_callback);

  // Initialize game
  init();

  // Run the main loop
  glutMainLoop();

  return 0;
}

void init()
{
  glClearColor(cgl::bg_red, cgl::bg_green, cgl::bg_blue, 1.0f);
}

void display_callback()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // KK - This used to be a function. We needed functions and getters and
  // private member variables for three lines of code!
  // We can tell from context that we're calculating some index.
  // KK - Def a nitpick, but I think I fell down a rabbit hole of looking
  // for more terse languages, but for C++, this totally works.
  // Draw the game board
  // Draw the grid of cells
  for (unsigned int x = 0; x < game.num_cols_; x++)
    for (unsigned int y = 0; y < game.num_rows_; y++)
    {
      drawCell(x, y, game.current_grid_[y * game.num_cols_ + x]);
      drawUnit(x, y);
    }

  glutSwapBuffers();
}

void reshape_callback(int width, int height)
{
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int value)
{
  // Re-run the display callback
  glutPostRedisplay();

  // Re-initialize this timer according to the fps
  glutTimerFunc(1000 / fps, timer_callback, value);

  // Update the game board
  game.update();
}

void special_keys_callback(int key, int mouseX, int mouseY)
{
  switch (key)
  {
    // Up arrow
    case GLUT_KEY_UP:
      // Increment the FPS
      fps += FPS_STEP;
      if (fps >= MAX_FPS) { fps = MAX_FPS; }
      break;

    // Down arrow
    case GLUT_KEY_DOWN:
      // KK - fps is now unsigned, so we can't let it go negative and wrap.
      // Decrement the FPS
      if (fps - FPS_STEP >= MIN_FPS)
        fps -= FPS_STEP;
      else
        fps = MIN_FPS;
      break;

    default:
      break;
  }
}

void keyboard_callback(unsigned char key, int mouseX, int mouseY)
{
  // KK - This switch case is a pretty small if-elseif as well.
  if (key == ' ')
    game.pause_ = !game.pause_;
  else if (key == 'c')
  {
    // This used to be a function call that someone would have to chase,
    // but now it's pretty obviously just clearing the boards.
    game.grid1_.fill(cgl::CellState::OFF);
    game.grid2_.fill(cgl::CellState::OFF);
  }
}

void mouse_callback(int button, int state, int mouseX, int mouseY)
{
  // KK - I appreciate the switch case before, but there were just not enough
  // options to justify it.
  if (state == GLUT_DOWN)
  {
    // KK - I'm actually not sure if these have to be int as opposed to unsigned.
    const int x = std::floor(mouseX / CELL_SIZE_PX);
    const int y = std::floor((WINDOW_HEIGHT - mouseY) / CELL_SIZE_PX);
    if (button == GLUT_LEFT_BUTTON)
      game.current_grid_[cgl::convert_indices(x, y, game.num_cols_)] = cgl::CellState::ON;
    else if (button == GLUT_RIGHT_BUTTON)
      game.current_grid_[cgl::convert_indices(x, y, game.num_cols_)] = cgl::CellState::OFF;
  }
}

void drawUnit(int x, int y)
{
  glLineWidth(1.0f);
  glColor3f(cgl::line_red, cgl::line_green, cgl::line_blue);

  glBegin(GL_LINE_LOOP);

  glVertex2f(x, y);
  glVertex2f(x + 1, y);
  glVertex2f(x + 1, y + 1);
  glVertex2f(x, y + 1);

  glEnd();
}

void drawCell(int x, int y, cgl::CellState state)
{
  // KK - At this point, I don't think your cells could be undetermined?
  // Set the drawing color based on the state of the cell
  if (state == cgl::CellState::ON)
    glColor3f(cgl::cell_on_red, cgl::cell_on_green, cgl::cell_on_blue);
  else
    glColor3f(cgl::cell_off_red, cgl::cell_off_green, cgl::cell_off_blue);

  // Draw a rectangle at the position of the cell
  glRectd(x, y, x+1, y+1);
}
