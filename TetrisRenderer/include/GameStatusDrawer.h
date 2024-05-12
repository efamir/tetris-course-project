#ifndef COURSEWORK_GAMESTATUSDRAWER_H
#define COURSEWORK_GAMESTATUSDRAWER_H

#include "BlocksWindow.h"
#include "Cursor.h"


class GameStatusDrawer {
    Cursor & _cursor;
public:
    GameStatusDrawer(Cursor & cursor);

    void drawPause();

    void drawGameOver();
};


#endif //COURSEWORK_GAMESTATUSDRAWER_H
