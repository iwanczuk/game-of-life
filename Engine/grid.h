#ifndef _GOL_ENGINE_GRID_H_
#define _GOL_ENGINE_GRID_H_

#include <vector>

namespace GoL
{
    namespace Engine
    {
        class Grid
        {
        public:
            enum class CellState
            {
                DEAD = false,
                ALIVE = true
            };

            enum class WrapMode
            {
                OFF = false,
                ON = true
            };

            explicit Grid(unsigned int rows, unsigned int columns, WrapMode wrapmode);
            Grid(const Grid&) = delete;
            Grid& operator=(const Grid&) = delete;

            unsigned int GetRows() const { return m_rows; };
            unsigned int GetColumns() const { return m_columns; };

            WrapMode GetWrapMode() const { return m_wrapmode; };
            void SetWrapMode(WrapMode wrapmode) { m_wrapmode = wrapmode; };
            bool IsWrapModeOff() const { return m_wrapmode == WrapMode::OFF; };
            bool IsWrapModeOn() const { return !IsWrapModeOff(); };

            CellState GetCellState(unsigned int row, unsigned int column) const;
            void SetCellState(unsigned int row, unsigned int column, CellState state);
            bool IsCellDead(unsigned int row, unsigned int column) const;
            bool IsCellAlive(unsigned int row, unsigned int column) const;

        private:
            unsigned int m_rows;
            unsigned int m_columns;

            std::vector<CellState> m_cells;
            WrapMode m_wrapmode;
        };
    }
}

#endif // !_GOL_ENGINE_GRID_H_
