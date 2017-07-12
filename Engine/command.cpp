#include <vector>
#include <random>
#include "command.h"
#include "grid.h"

namespace GoL
{
    namespace Engine
    {
        void TickCommand::Execute(Grid* grid)
        {
            unsigned int rows = grid->GetRows();
            unsigned int columns = grid->GetColumns();

            std::vector<Grid::CellState> cells(rows * columns);

            for (unsigned int row = 0; row < rows; ++row)
            {
                for (unsigned int column = 0; column < columns; ++column)
                {
                    unsigned int neighbors = CellNeighbors(grid, row, column);

                    Grid::CellState state = grid->GetCellState(row, column);

                    if (state == Grid::CellState::ALIVE && (neighbors > 3 || neighbors < 2))
                    {
                        state = Grid::CellState::DEAD;
                    }
                    else if (state == Grid::CellState::DEAD && neighbors == 3)
                    {
                        state = Grid::CellState::ALIVE;
                    }

                    cells[row * rows + column] = state;
                }
            }

            for (unsigned int row = 0; row < rows; ++row)
            {
                for (unsigned int column = 0; column < columns; ++column)
                {
                    grid->SetCellState(row, column, cells[row * rows + column]);
                }
            }
        }

        unsigned int TickCommand::CellNeighbors(Grid* grid, unsigned int row, unsigned int column) const
        {
            unsigned int count = 0;

            if (grid->IsCellAlive(row - 1, column - 1))
            {
                count++;
            }

            if (grid->IsCellAlive(row - 1, column))
            {
                count++;
            }

            if (grid->IsCellAlive(row - 1, column + 1))
            {
                count++;
            }

            if (grid->IsCellAlive(row, column - 1))
            {
                count++;
            }

            if (grid->IsCellAlive(row, column + 1))
            {
                count++;
            }

            if (grid->IsCellAlive(row + 1, column - 1))
            {
                count++;
            }

            if (grid->IsCellAlive(row + 1, column))
            {
                count++;
            }

            if (grid->IsCellAlive(row + 1, column + 1))
            {
                count++;
            }

            return count;
        }

        void ClearCommand::Execute(Grid* grid)
        {
            unsigned int rows = grid->GetRows();
            unsigned int columns = grid->GetColumns();

            for (unsigned int row = 0; row < rows; ++row)
            {
                for (unsigned int column = 0; column < columns; ++column)
                {
                    grid->SetCellState(row, column, Grid::CellState::DEAD);
                }
            }
        }

        void RandomizeCommand::Execute(Grid* grid)
        {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<unsigned int> distribution(1, 100);

            unsigned int rows = grid->GetRows();
            unsigned int columns = grid->GetColumns();

            for (unsigned int row = 0; row < rows; ++row)
            {
                for (unsigned int column = 0; column < columns; ++column)
                {
                    Grid::CellState state = distribution(mt) > 66 ? Grid::CellState::ALIVE : Grid::CellState::DEAD;
                    grid->SetCellState(row, column, state);
                }
            }
        }

        void WrapCommand::Execute(Grid* grid)
        {
            grid->SetWrapMode(grid->IsWrapModeOn() ? Grid::WrapMode::OFF : Grid::WrapMode::ON);
        }

        void ToggleCommand::Execute(Grid* grid)
        {
            Grid::CellState state;

            state = grid->IsCellAlive(m_row, m_column) ? Grid::CellState::DEAD : Grid::CellState::ALIVE;

            grid->SetCellState(m_row, m_column, state);
        }
    }
}
