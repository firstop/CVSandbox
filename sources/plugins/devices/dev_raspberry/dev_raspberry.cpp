/*
    Raspberry Pi plug-ins for Computer Vision Sandbox

    Copyright (C) 2011-2019, cvsandbox
    http://www.cvsandbox.com/contacts.html

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <imodule.h>
#include <image_raspberry_16x16.h>

// Descriptor of the module
ModuleDescriptor moduleInfo =
{
    { 0xAF000001, 0x00000000, 0x00000000, 0x00000014 },
    { 1, 0, 0 },
    "Raspberry Pi Plug-ins",
    "dev_raspberry",
    "The module contains plug-ins to access different hardware modules of Raspberry Pi.",
    "Computer Vision Sandbox",
    "Copyright Computer Vision Sandbox, 2011-2019",
    "http://www.cvsandbox.com/",
    (ximage*) &image_raspberry_16x16, // small icon
    nullptr, // icon
    0
};

// Module's exported API
extern "C"
{

    // Initialize module and provide its descriptor
    MODULE_PUBLIC ModuleDescriptor* ModuleInitialize( )
    {
        moduleInfo.PluginsCount = GetPluginsCount( );

        return CopyModuleDescriptor( &moduleInfo );
    }

    // Perform module clean-up routines
    MODULE_PUBLIC void ModuleCleanup( )
    {
        UnregisterAllPlugins( );
    }

    // Get descriptor of the requested plug-in
    MODULE_PUBLIC PluginDescriptor* GetDescriptor( uint32_t plugin )
    {
        return GetPluginDescriptor( plugin );
    }

}
