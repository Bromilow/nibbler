/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModuleController.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 20:09:16 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/15 16:19:31 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODULE_CONTROLLER_HPP
# define MODULE_CONTROLLER_HPP

/*load, initialize, manage, deinitialize, unload library*/

# include <dlfcn.h>
# include <string>
# include <iostream>
/*# include "GameEnvironment.hpp"*/
# include "IModule.hpp"
# include "Level.hpp"

// Class factory types
typedef IModule* (*createModule_t)(Level & data);
typedef void     (*destroyModule_t)(IModule*);

class ModuleController {
public:
    ModuleController(const char *filename, Level & data);
	ModuleController(ModuleController const & src);
	ModuleController & operator=(ModuleController const & rhs);
	~ModuleController(void);

    IModule*    module;
    Level &     levelData;
    
    int     loadLibrary(const char *filename);
    void*   loadSymbol(void *handle, const char *symName);
    
private:
    destroyModule_t _destroy_module;
    void            *_handle;
};

#endif /* MODULE_CONTROLLER_HPP */