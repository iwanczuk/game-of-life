#ifndef _GOL_GAME_APP_H_
#define _GOL_GAME_APP_H_

#include <wx/app.h>

namespace GoL
{
    namespace Game
    {
        class App : public wxApp
        {
        public:
            virtual bool OnInit();
        };
    }
}

#endif // !_GOL_GAME_APP_H_
