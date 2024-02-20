#pragma once
#include <array>

#include <conways_game_of_life/util.hpp>

namespace conways_game_of_life
{
// KK - I think you always use `class`, especially since you're namespacing it anyways.
// This would prevent from accidentally coercing to int.
enum class CellState
{
  ON,
  OFF
};

template <unsigned int C, unsigned int R>
class ConwaysGameOfLife
{
public:
  //! \brief Initialize the Conway's Game of Life board.
  ConwaysGameOfLife() {
    // This used to be an init() function, but just defining values
    // at the declarations got us all the work.

    // Initialize all cells off.
    grid1_.fill(CellState::OFF);
    grid2_.fill(CellState::OFF);
  }

  // KK - Switched these out of a pair.
  // It was always being accessed by first and second.
  // Kept them as templates, but unsigned int templates.
  const unsigned int num_cols_ = C;
  const unsigned int num_rows_ = R;

  // KK - Public! And just initialized from the get.
  //! \brief Pause board updates.
  bool pause_ = true;

  //! \brief A grid to store the state of all the cells in the game.
  std::array<CellState, C*R> grid1_;
  //! \brief A grid to store the state of all the cells in the game.
  std::array<CellState, C*R> grid2_;

  //! \brief Update loop of the game.
  //! Update the game grid with the next generation of cells.
  void update()
  {
    if (pause_) { return; }
    // Loop through all cells of the grid
    for (unsigned int x = 0; x < C; x++)
    {
      for (unsigned int y = 0; y < R; y++)
      {
        // KK - const. This never changes and we know in the instant it's
        // not supposed to. Any time moving forward we know index is
        // supposed to be _exactly_ this.
        const unsigned int index = convert_indices(x, y, C);

        // KK - CONST
        // Count the number of neighbors that are alive
        const unsigned int alive = countAliveNeighbors(x, y);

        next_grid_[index] = current_grid_[index];

        // Birth rule
        if (current_grid_[index] == CellState::OFF
            && alive == 3)
          next_grid_[index] = CellState::ON;
        // Death rule
        else if (current_grid_[index] == CellState::ON
            && (alive <= 1 || alive >= 4))
          next_grid_[index] = CellState::OFF;
      }
    }

    // Swap which grid we're modifying
    current_grid_ =
      (current_grid_ == grid1_.data()) // if
        ? grid2_.data()  // then
        : grid1_.data(); // else

    next_grid_ =
      (current_grid_ == grid1_.data()) // if
        ? grid2_.data()  // then
        : grid1_.data(); // else
  }
  //! \brief A pointer to the current grid.
  CellState* current_grid_ = grid1_.data();

private:

  //! \brief A pointer to the grid used for the next generation.
  CellState *next_grid_ = grid2_.data();


  // KK - We're never having negative numbers of Alive neighbors, right?
  // Having done this once before, I think it might be easier to understand
  // just literally counting out the literal neighbors with wrapping instead
  // of doing the loops? Could be super wrong, though, since you're using 1D.
  //! \brief Count the number of alive cells adjacent to the current cell.
  //!
  //! \param [in] x The X coordinate of the cell to count the neighbors of.
  //! \param [in] y The Y coordinate of the cell to count the neighbors of.
  //! \return int The number of neighbors adjacent to the current cell.
  unsigned int countAliveNeighbors(int x, int y)
  {
    // Initialize counter
    unsigned int alive = 0;

    // KK - Modulo operator might help in this function to check bounds.
    // Loop over X offsets in the range [-1, 1]
    for (int x_off = -1; x_off <= 1; x_off++)
    {
      // Get the x coordinate of the neighbor cell using the x offset
      int neighbor_x = x + x_off;
      // Wrap the value if it is beyond the size of the grid
      if (x + x_off < 0) { neighbor_x = C - 1; }
      if (x + x_off >= C) { neighbor_x = 0; }

      // Loop over Y offsets in the range [-1, 1]
      for (int y_off = -1; y_off <= 1; y_off++)
      {
        // Get the y coordinate of the neighbor cell using the y offset
        int neighbor_y = y + y_off;
        // Wrap the value if it is beyond the size of the grid
        if (y + y_off < 0) { neighbor_y = R - 1; }
        if (y + y_off >= R) { neighbor_y = 0; }

        // Skip the cell if the offsets are both 0, this is the current cell
        if (x_off == 0 && y_off == 0) { continue; }

        // Convert (x, y) coords to 1D array index
        unsigned int neighbor_index = convert_indices(neighbor_x, neighbor_y, C);

        // Increment counter if neighbor cell is alive
        if (current_grid_[neighbor_index] == CellState::ON) { alive++; }
      }
    }

    return alive;
  }

};
} // namespace conways_game_of_life
