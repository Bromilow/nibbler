/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:43:32 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/12 19:03:46 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int     main(int argc, char **argv)
{
    if (!checkInput(argc, argv))
        return (0);
    else {
        const char      *modules[3] = {"./module_1/mod_NCurses.so", "./module_2/mod_OpenGL.so", "./module_3/mod_SDL.so"};
        int             menu_choice;
        GameEnvironment *game;

        // Display menu
        menu_choice = main_menu();
        std::cout << "You chose option : " << menu_choice << std::endl;

        if (menu_choice > 0 && menu_choice < 4)
        {
            // Set up player, map, and module handler
            game = new GameEnvironment(std::atoi(argv[1]), std::atoi(argv[2]), modules[menu_choice - 1]);
            game->moduleController->loadLibrary(modules[menu_choice - 1]);
            game->gameLoop();
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
        // error : screen width and height not valid
        std::cout << "error : screen width and/or height not valid" << std::endl;
        return (0);
    }
    else if (!(std::atoi(av[1]) >= MIN_SCREEN_W && std::atoi(av[2]) >= MIN_SCREEN_H))
    {
        // error : screen dimentions too small
        std::cout << "error : screen dimentions too small" << std::endl;
        return (0);
    }
    else if (!(std::atoi(av[1]) <= MAX_SCREEN_W && std::atoi(av[2]) <= MAX_SCREEN_H))
    {
        // error : screen dimentions too large
        std::cout << "error : screen dimentions too large" << std::endl;
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
    void* handle = dlopen("./main_menu/mod_MainMenu.so", RTLD_NOW);
    if (!handle) {
        std::cerr << "Cannot open library: 'mod_MainMenu.so'\nERROR : " << dlerror() << '\n';
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

/*int     initialize_module(int option, IModule *module)
{
    std::string modules[3] = {"./mod_NCurses.so", "./mod_OpenGL.so", "./mod_SDL.so"};

    // open the library
    void* handle = dlopen(modules[option - 1].c_str(), RTLD_NOW);
    
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return 0;
    }
    // reset errors
    dlerror();

    // load the 'create_module' symbol
    createModule_t create_module = reinterpret_cast<createModule_t>(dlsym(handle, "create_module"));
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'create_module': " << dlsym_error << '\n';
        return 0;
    }

    // Create module
    module = create_module();

    // close the library
    dlclose(handle);

    return (1);
}

int     delete_module(int option, IModule *module)
{
    std::string modules[3] = {"./mod_NCurses.so", "./mod_OpenGL.so", "./mod_SDL.so"};

    // open the library
    void* handle = dlopen(modules[option - 1].c_str(), RTLD_NOW);
    
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return 0;
    }
    // reset errors
    dlerror();

    // load the 'destroy_module' symbol
    destroyModule_t destroy_module = reinterpret_cast<destroyModule_t>(dlsym(handle, "destroy_module"));
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'destroy_module': " << dlsym_error << '\n';
        return 0;
    }

    // Create module
    destroy_module(module);

    // close the library
    dlclose(handle);

    return (1);
}*/