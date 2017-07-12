#include "app.h"
#include "frame.h"

namespace GoL
{
    namespace Game
    {
        bool App::OnInit()
        {
            Frame* frame = new Frame();
            frame->Show(true);

            return true;
        }
    }
}
