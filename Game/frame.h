#ifndef _GOL_GAME_FRAME_H_
#define _GOL_GAME_FRAME_H_

#include <wx/wx.h>
#include "grid.h"

namespace GoL
{
    namespace Game
    {
        class Frame :public wxFrame
        {
        public:
            Frame();

            void OnPaint(wxPaintEvent& event);
            void OnClick(wxMouseEvent& event);
            void OnTimer(wxTimerEvent& event);
            void OnPlay(wxCommandEvent& event);
            void OnQuit(wxCommandEvent& event);
            void OnWrap(wxCommandEvent& event);
            void OnClear(wxCommandEvent& event);
            void OnRandomize(wxCommandEvent& event);

        private:
            wxTimer* m_timer;

            GoL::Engine::Grid* m_grid;
        };
    }
}

#endif // !_GOL_GAME_FRAME_H_
