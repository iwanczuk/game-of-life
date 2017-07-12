#ifndef _GOL_ENGINE_COMMAND_H_
#define _GOL_ENGINE_COMMAND_H_

namespace GoL
{
    namespace Engine
    {
        class Grid;

        class Command
        {
        public:
            virtual void Execute(Grid* grid) = 0;
        };

        class ClearCommand : public Command
        {
        public:
            explicit ClearCommand() { };
            ClearCommand(const ClearCommand&) = delete;
            ClearCommand& operator=(const ClearCommand&) = delete;

            void Execute(Grid* grid) override;
        };

        class TickCommand : public Command
        {
        public:
            explicit TickCommand() { };
            TickCommand(const TickCommand&) = delete;
            TickCommand& operator=(const TickCommand&) = delete;

            void Execute(Grid* grid) override;

        private:
            unsigned int CellNeighbors(Grid* grid, unsigned int row, unsigned int column) const;
        };

        class RandomizeCommand : public Command
        {
        public:
            explicit RandomizeCommand() { };
            RandomizeCommand(const RandomizeCommand&) = delete;
            RandomizeCommand& operator=(const RandomizeCommand&) = delete;

            void Execute(Grid* grid) override;
        };

        class WrapCommand : public Command
        {
        public:
            explicit WrapCommand() { };
            WrapCommand(const WrapCommand&) = delete;
            WrapCommand& operator=(const WrapCommand&) = delete;

            void Execute(Grid* grid) override;
        };

        class ToggleCommand : public Command
        {
        public:
            explicit ToggleCommand(unsigned int row, unsigned int column) : m_row(row), m_column(column) { }
            ToggleCommand(const ToggleCommand&) = delete;
            ToggleCommand& operator=(const ToggleCommand&) = delete;

            void Execute(Grid* grid) override;

        private:
            unsigned int m_row;
            unsigned int m_column;
        };
    }
}

#endif // !_GOL_ENGINE_COMMAND_H_
