
#include "Menu.h"
#include <iostream>

#define EXIT_SUCCESS    0



int main(void) {
   Menu * menu = new Menu();
   menu->run();
   delete menu;
   return EXIT_SUCCESS;
}
