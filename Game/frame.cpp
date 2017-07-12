#include <wx/dcbuffer.h>
#include "frame.h"
#include "command.h"
#include "grid.h"

namespace GoL
{
    namespace Game
    {
        using namespace GoL::Engine;

        Frame::Frame() : wxFrame(NULL, wxID_ANY, wxT("Game of Life"), wxDefaultPosition, wxDefaultSize, wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION)
        {
            SetBackgroundStyle(wxBG_STYLE_PAINT);
            SetClientSize(400, 400);
            SetIcon(wxIcon(wxT("GOL")));

            Bind(wxEVT_PAINT, &Frame::OnPaint, this);
            Bind(wxEVT_LEFT_UP, &Frame::OnClick, this);
            Bind(wxEVT_TIMER, &Frame::OnTimer, this);
            Bind(wxEVT_MENU, &Frame::OnPlay, this, wxID_EXECUTE);
            Bind(wxEVT_MENU, &Frame::OnQuit, this, wxID_EXIT);
            Bind(wxEVT_MENU, &Frame::OnWrap, this, wxID_APPLY);
            Bind(wxEVT_MENU, &Frame::OnClear, this, wxID_CLEAR);
            Bind(wxEVT_MENU, &Frame::OnRandomize, this, wxID_RESET);

            m_timer = new wxTimer(this);
            m_grid = new Grid(10, 10, Grid::WrapMode::OFF);

            RandomizeCommand command;
            command.Execute(m_grid);

            wxMenuBar* menubar = new wxMenuBar();
            wxMenu* gamemenu = new wxMenu();

            gamemenu->AppendCheckItem(wxID_EXECUTE, wxT("&Play"));
            gamemenu->Append(wxID_EXIT, wxT("&Quit"));
            menubar->Append(gamemenu, wxT("&Game"));

            wxMenu* gridmenu = new wxMenu();

            gridmenu->AppendCheckItem(wxID_APPLY, wxT("&Wrap"));
            gridmenu->Append(wxID_CLEAR, wxT("&Clear"));
            gridmenu->Append(wxID_RESET, wxT("&Randomize"));
            menubar->Append(gridmenu, wxT("&Grid"));

            SetMenuBar(menubar);

            Centre();
        }

        void Frame::OnPaint(wxPaintEvent& event)
        {
            wxBufferedPaintDC dc(this);

            unsigned int rows = m_grid->GetRows();
            unsigned int columns = m_grid->GetColumns();

            wxSize clientSize = GetClientSize();
            wxSize cellSize(clientSize.GetWidth() / columns, clientSize.GetHeight() / rows);

            for (unsigned int row = 0; row < rows; ++row)
            {
                for (unsigned int column = 0; column < columns; ++column)
                {
                    wxPoint position(column * cellSize.GetWidth(), row * cellSize.GetHeight());

                    if (m_grid->IsCellAlive(row, column))
                    {
                        dc.SetBrush(wxBrush(wxColour(97, 158, 27)));
                    }
                    else
                    {
                        dc.SetBrush(wxBrush(wxColour(212, 212, 212)));
                    }

                    dc.DrawRectangle(position, cellSize);
                }
            }
        }

        void Frame::OnClick(wxMouseEvent& event)
        {
            unsigned int rows = m_grid->GetRows();
            unsigned int columns = m_grid->GetColumns();

            wxPoint position = event.GetLogicalPosition(wxClientDC(this));
            wxSize clientSize = GetClientSize();
            wxSize cellSize(clientSize.GetWidth() / columns, clientSize.GetHeight() / rows);

            ToggleCommand command(position.y / cellSize.GetHeight(), position.x / cellSize.GetWidth());
            command.Execute(m_grid);

            Refresh();
        }

        void Frame::OnTimer(wxTimerEvent& event)
        {
            TickCommand command;
            command.Execute(m_grid);

            Refresh();
        }

        void Frame::OnPlay(wxCommandEvent& event)
        {
            if (m_timer->IsRunning())
            {
                m_timer->Stop();
            }
            else
            {
                m_timer->Start(1000);
            }
        }

        void Frame::OnQuit(wxCommandEvent& event)
        {
            Close(true);
        }

        void Frame::OnWrap(wxCommandEvent& event)
        {
            WrapCommand command;
            command.Execute(m_grid);
        }

        void Frame::OnClear(wxCommandEvent& event)
        {
            ClearCommand command;
            command.Execute(m_grid);

            Refresh();
        }

        void Frame::OnRandomize(wxCommandEvent& event)
        {
            RandomizeCommand command;
            command.Execute(m_grid);

            Refresh();
        }
    }
}
