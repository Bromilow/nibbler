/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:43:32 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/23 19:18:14 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int     main(int argc, char **argv)
{
    if (checkInput(argc, argv))
    {
        int             menu_choice;
        Core            *game;
        bool            quit;
        
        quit = false;
        while (!quit)
        {
            // Display menu         // 0: EXIT    1: First Lib    2: Second Lib    3: Third Lib
            menu_choice = main_menu();
            std::cout << "You chose option : " << menu_choice << std::endl;
            if (menu_choice <= 0)
                quit = true;
            else if (menu_choice > 0 && menu_choice < 4)
            {
                try {
                    // Set up player, map, and module handler
                    game = new Core(std::atoi(argv[1]), std::atoi(argv[2]), menu_choice - 1);
                    // Start game loop
                    game->gameLoop();
                    // Game has ended
                    delete game;
                }
                catch (std::exception & e) {
                    std::cerr << "ERROR: " << e.what() << std::endl;
                    quit = true;
                }          
            }
        }
    }
    return (0);
}

int     checkInput(int ac, char **av)
{
    if (ac != 3)
    {
        std::cerr << "error : invlid arguments. Try this:\n"
        << "make run   OR   ./nibbler width height\n" << std::endl;
        return (0);
    }
    else if (!(std::atoi(av[1]) || std::atoi(av[2])))
    {
        // error : map width and height not valid
        std::cerr << "error : map width and/or height not valid" << std::endl;
        return (0);
    }
    else if (!(std::atoi(av[1]) >= MIN_MAP_W && std::atoi(av[2]) >= MIN_MAP_H))
    {
        // error : map dimentions too small
        std::cerr << "error : map dimentions too small" << std::endl;
        return (0);
    }
    else if (!(std::atoi(av[1]) <= MAX_MAP_W && std::atoi(av[2]) <= MAX_MAP_H))
    {
        // error : map dimentions too large
        std::cerr << "error : map dimentions too large" << std::endl;
        return (0);
    }
    else
        return (1);
}

int     main_menu(void)
{
    main_menu_t         menu_module;
    const char          *dlsym_error;
    int                 menu_choice;
    
    // open the library
    void* handle = dlopen("./main_menu/lib0_MainMenu.so", RTLD_NOW);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return (-1);
    }
    // reset errors
    dlerror();

    menu_module = reinterpret_cast<main_menu_t>(dlsym(handle, "main_menu"));
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << dlsym_error << std::endl;
        dlclose(handle);
        return (-1);
    }
    
    menu_choice = menu_module();

    // close the library
    dlclose(handle);

    return (menu_choice);
}