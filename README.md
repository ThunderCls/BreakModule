# BreakModule
BreakModule plugin for x64dbg

BreakModule v1 plugin by ThunderCls - 2016
Blog: http://reversec0de.wordpress.com

This plugin is intended to give the user the option to pause the execution of the debugged application when the specified modules are loaded. The modules specifications are saved to disk hence in any new debuggin session the breakpoints are gonna remain untouched. The user can include or exclude modules to the list as he or she wishes.

Installation:
 - Copy BreakModule.dp32 to x32 plugins directory of x64dbg
 - Look under the "Plugins" menu in the main x64dbg window or in the secondary menu in the Disasm window as well

Features:
 - Breakpoint on every Entrypoint of any modules (DLL) you choose when loading
 - Configuration file used to maintain the modules breakpoints active
 - Friendly GUI
