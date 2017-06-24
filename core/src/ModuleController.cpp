/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModuleController.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 20:08:54 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/23 19:23:20 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModuleController.hpp"

ModuleController::ModuleController(GameEnvironment & data) : input(NONE), gameData(data)
{}

ModuleController::ModuleController(ModuleController const & src) : input(NONE), gameData(src.gameData)
{
    *this = src;
}

ModuleController & ModuleController::operator=(ModuleController const & rhs)
{
    if (this != &rhs)
    {
        this->module = rhs.module;
        this->input = rhs.input;
        this->gameData = rhs.gameData;
        this->_destroy_module = rhs._destroy_module;
        this->_handle = rhs._handle;
    }
    return (*this);
}

ModuleController::~ModuleController(void)
{
    if (module != NULL)
        _destroy_module(module);
    dlclose(_handle);
}

int     ModuleController::loadLibrary(const char *filename)
{
    createModule_t  create_module;

    _handle = dlopen(filename, RTLD_NOW | RTLD_GLOBAL);
    if (!_handle) {
        std::cerr << dlerror() << std::endl;;
        throw ModuleCannotOpen();
    }
    // Clear any errors
    dlerror();

    // load the 'create_module' symbol
    create_module = reinterpret_cast<createModule_t>(this->loadSymbol(_handle, "create_module"));
    // load the 'destroy_module' symbol
    this->_destroy_module = reinterpret_cast<destroyModule_t>(this->loadSymbol(_handle, "destroy_module"));
    if (this->_destroy_module != NULL)
    {
        this->module = create_module(this->gameData);
        return (1);
    }
    return (0);
}

void*   ModuleController::loadSymbol(void *handle, const char *symName)
{
    const char  *dlsym_error;
    void*       symbol = NULL;
    
    symbol = dlsym(handle, symName);
    dlsym_error = dlerror();
    if (dlsym_error)
    {
        std::cerr << dlsym_error << '\n';
        throw ModuleBadSymbol();
    }
    return (symbol);
}

const char *	ModuleController::ModuleCannotOpen::what() const throw()
{
	return "Cannot open module(Dynamic Library)";
}

const char *	ModuleController::ModuleBadSymbol::what() const throw()
{
	return "Bad symbol in module(Dynamic Library)";
}