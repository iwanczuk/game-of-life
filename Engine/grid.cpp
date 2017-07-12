#include "grid.h"

namespace GoL
{
    namespace Engine
    {
        Grid::Grid(unsigned int rows, unsigned int columns, Grid::WrapMode wrapmode) : m_rows(rows), m_columns(columns), m_cells(rows * columns, CellState::DEAD), m_wrapmode(wrapmode)
        {

        }

        Grid::CellState Grid::GetCellState(unsigned int row, unsigned int column) const
        {
            if (IsWrapModeOn())
            {
                row = (row + m_rows) % m_rows;
                column = (column + m_columns) % m_columns;
            }
            else if (row < 0 || row >= m_rows || column < 0 || column >= m_columns)
            {
                return CellState::DEAD;
            }

            return m_cells[row * m_columns + column];
        }

        void Grid::SetCellState(unsigned int row, unsigned int column, Grid::CellState state)
        {
            m_cells[row * m_columns + column] = state;
        }

        bool Grid::IsCellDead(unsigned int row, unsigned int column) const
        {
            return GetCellState(row, column) == CellState::DEAD;
        }

        bool Grid::IsCellAlive(unsigned int row, unsigned int column) const
        {
            return !IsCellDead(row, column);
        }
    }
}
