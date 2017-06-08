#include <string>
#include <cstdlib>
#include <iostream>
#include <dlfcn.h>
#include "GameLoop.hpp"

#define MIN_SCREEN_W    640
#define MIN_SCREEN_H    480
#define MAX_SCREEN_W    1280
#define MAX_SCREEN_H    960

int     main_menu(void);

/*

    Get time in nano seconds and render data 60 times per second (60 fps)
    1 sec == 1 000 000 000 nanoseconds
    1 000 000 000 / 60 == 16666666.6667

    When old_time is 16666666 nanoseonds away from current time
    then render the data

*/

int     main(int argc, char **argv)
{
    if (argc != 3)
    {
        // error : not enough args
        std::cout << "error : not enough args" << std::endl;
    }
    else if (!(std::atoi(argv[1]) >= MIN_SCREEN_W && std::atoi(argv[2]) >= MIN_SCREEN_H))
    {
        // error : screen dimentions too small
        std::cout << "error : screen dimentions too small" << std::endl;
    }
    else if (!(std::atoi(argv[1]) <= MAX_SCREEN_W && std::atoi(argv[2]) <= MAX_SCREEN_H))
    {
        // error : screen dimentions too large
        std::cout << "error : screen dimentions too large" << std::endl;
    }
    else
    {
        int     game_choice;

        game_choice = main_menu();

 //       initialize_module(game_choice);
        // Initialise display
            // NCURSES - OPTION 1 (default)
                // Create terminal (SCREEN *)
                // Create new window (WINDOW *stdscr)
                // Create bottom-bar for info (score, lives, highscore)
                // Create map area (open square at first)

        // Create a snake object
        // Create food object and any obstacles

        gameLoop();

    }

    return (0);
}

int     main_menu(void)
{
    int     menu_choice = 0;

    // open the library
    void* handle = dlopen("./main_menu.so", RTLD_LAZY);
    
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return -1;
    }
    
    // load the symbol
    typedef int (*main_menu_t)();

    // reset errors
    dlerror();

    main_menu_t menu = (main_menu_t) dlsym(handle, "main_menu");

    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'main_menu': " << dlsym_error <<
            '\n';
        dlclose(handle);
        return -1;
    }
    
    menu_choice = menu();
    
    // close the library
    dlclose(handle);

    return (menu_choice);
}