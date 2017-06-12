/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModuleController.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 20:08:54 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/12 20:10:44 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModuleController.hpp"

IModule*    ModuleController::module = NULL;

ModuleController::ModuleController(const char *filename)
{
    //std::cout << "ModuleController::Parameterized constructor" << std::endl;
    (void)filename;
    //this->loadLibrary(filename);
}

ModuleController::ModuleController(ModuleController const & src)
{
    //std::cout << "ModuleController::Copy constructor" << std::endl;
    *this = src;
}

ModuleController & ModuleController::operator=(ModuleController const & rhs)
{
    //std::cout << "ModuleController::Assignation Operator" << std::endl;
    if (this != &rhs)
    {
        this->module = rhs.module;
        this->_destroy_module = rhs._destroy_module;
    }
    return (*this);
}

ModuleController::~ModuleController(void)
{
    //std::cout << "ModuleController::Destructor" << std::endl;
    if (module != NULL)
        _destroy_module(module);
    dlclose(_handle);
}

int     ModuleController::loadLibrary(const char *filename)
{
    //std::cout << "ModuleController::loadLibrary()" << std::endl;
    createModule_t  create_module;

    // open the library
    _handle = dlopen(filename, RTLD_NOW);
    
    if (!_handle) {
        std::cerr << "Cannot open library: " << filename << "\nERROR :" << dlerror() << '\n';
        return (0);
    }
    // reset errors
    dlerror();

    // load the 'create_module' symbol
    create_module = reinterpret_cast<createModule_t>(this->loadSymbol(_handle, "create_module"));
    if (create_module != NULL)
    {
        // load the 'destroy_module' symbol
        this->_destroy_module = reinterpret_cast<destroyModule_t>(this->loadSymbol(_handle, "destroy_module"));
        if (this->_destroy_module != NULL)
        {
            // Create module
            this->module = create_module();
        }
    }
    return (1);
}

void*   ModuleController::loadSymbol(void *handle, const char *symName)
{
    //std::cout << "ModuleController::loadSymbol()" << std::endl;
    const char  *dlsym_error;
    void*       symbol = NULL;
    
    symbol = dlsym(handle, symName);
    dlsym_error = dlerror();
    if (dlsym_error)
        std::cerr << "Cannot load symbol '" << symName << "'\nERROR : " << dlsym_error << '\n';
    return (symbol);
}