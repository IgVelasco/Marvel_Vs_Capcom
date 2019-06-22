#ifndef SERVER_CURSOR_H
#define SERVER_CURSOR_H

#include "data_structs.h"
#include <iostream>



#define TEAM_ONE_POSITION 61
#define TEAM_TWO_POSITION 353

#define SPIDERMAN_POSITION 97
#define WOLVERINE_POSITION 449
/*#define IRONMAN_POSITION
#define RYU_POSITION*/


class ServerCursor{
public:

	ServerCursor(int posX, int posY, bool isVisible);

	bool moveRight();
	bool moveLeft();
	bool selectCharacter();

	bool update(client_menu_t* action_msg);

	void makeMenuUpdater(cursor_updater_t* updater);

	bool getFinalSelection();
	character_number_t getCharacterSelected();

	void setVisible(bool condition);


private:

	int posX, posY;
	bool visible;
	bool finalSelection;
	character_number_t characterSelected;


};


#endif /*SERVER_CURSOR_H*/
