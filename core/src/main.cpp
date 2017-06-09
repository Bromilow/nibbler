/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:43:32 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/09 14:46:24 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.hpp"

int     main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "error : invlid arguments. Try this:\n"
        << "make run   OR   ./nibbler width height\n" << std::endl;
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

        std::cout << "You chose option : " << game_choice << std::endl;

        if (game_choice > 0 && game_choice < 4)
        {
            IModule *module = NULL;
            if (initialize_module(game_choice, module))
            {
                // Create a snake object
                // Create food object and any obstacles

                gameLoop(module);

                // Delete module
                delete_module(game_choice, module);

            }
        }
    }
    return (0);
}

int     main_menu(void)
{
    int     menu_choice = 0;

    // open the library
    void* handle = dlopen("./mod_MainMenu.so", RTLD_NOW);
    
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return -1;
    }
    
    // load the symbol
    typedef int (*main_menu_t)();

    // reset errors
    dlerror();

    main_menu_t menu = reinterpret_cast<main_menu_t>(dlsym(handle, "main_menu"));

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

int     initialize_module(int option, IModule *module)
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
}