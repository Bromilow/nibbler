/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:43:32 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/15 13:31:18 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int     main(int argc, char **argv)
{
    if (!checkInput(argc, argv))
        return (0);
    else {
        const char      *modules[3] = {"./module_1/lib1_NCurses.so", "./module_2/lib2_OpenGL.so", "./module_3/lib3_SDL.so"};
        int             menu_choice;
        GameEnvironment *game;

        // Display menu
        menu_choice = main_menu();
        std::cout << "You chose option : " << menu_choice << std::endl;

        if (menu_choice > 0 && menu_choice < 4)
        {
            // Set up player, map, and module handler
            game = new GameEnvironment(std::atoi(argv[1]), std::atoi(argv[2]), modules[menu_choice - 1]);
            
            // Initialize graphic library
            //game->moduleController->loadLibrary(modules[menu_choice - 1]);

            // Load game level
            //game->moduleController->loadScene();

            // Start game loop
            game->gameLoop();

            // Game has ended
            delete game;
            
        } else {
            // handle other menu options
        }
    }
    return (0);
}

int     checkInput(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "error : invlid arguments. Try this:\n"
        << "make run   OR   ./nibbler width height\n" << std::endl;
        return (0);
    }
    else if (!(std::atoi(av[1]) || std::atoi(av[2])))
    {
        // error : map width and height not valid
        std::cout << "error : map width and/or height not valid" << std::endl;
        return (0);
    }
    else if (!(std::atoi(av[1]) >= MIN_MAP_W && std::atoi(av[2]) >= MIN_MAP_H))
    {
        // error : map dimentions too small
        std::cout << "error : map dimentions too small" << std::endl;
        return (0);
    }
    else if (!(std::atoi(av[1]) <= MAX_MAP_W && std::atoi(av[2]) <= MAX_MAP_H))
    {
        // error : map dimentions too large
        std::cout << "error : map dimentions too large" << std::endl;
        return (0);
    }
    else
        return (1);
}

int     main_menu(void)
{
    typedef int (*main_menu_t)();
    main_menu_t         menu_module;
    const char          *dlsym_error;
    int                 menu_choice;

    // open the library
    void* handle = dlopen("./main_menu/lib0_MainMenu.so", RTLD_NOW);
    if (!handle) {
        std::cerr << "Cannot open library: 'lib0_MainMenu.so'\nERROR : " << dlerror() << '\n';
        return (-1);
    }
    // reset errors
    dlerror();

    menu_module = reinterpret_cast<main_menu_t>(dlsym(handle, "main_menu"));
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'main_menu': " << dlsym_error << '\n';
        dlclose(handle);
        return (-1);
    }
    
    menu_choice = menu_module();

    // close the library
    dlclose(handle);

    return (menu_choice);
}