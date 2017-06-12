/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModuleController.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 20:09:16 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/12 18:46:43 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODULE_CONTROLLER_HPP
# define MODULE_CONTROLLER_HPP

/*load, initialize, manage, deinitialize, unload library*/

# include <dlfcn.h>
# include <string>
# include <iostream>
# include "GameEnvironment.hpp"
# include "IModule.hpp"

// Class factory types
typedef IModule* (*createModule_t)(void);
typedef void     (*destroyModule_t)(IModule*);

class ModuleController {
public:
    static IModule*    module;

    ModuleController(const char *filename);
	ModuleController(ModuleController const & src);
	ModuleController & operator=(ModuleController const & rhs);
	~ModuleController(void);

    int     loadLibrary(const char *filename);
    void*   loadSymbol(void *handle, const char *symName);
    
private:
    destroyModule_t _destroy_module;
    void            *_handle;
};

#endif /* MODULE_CONTROLLER_HPP */