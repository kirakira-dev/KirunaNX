#include "lib/hook/trampoline.hpp"
#include "nn/fs.h" 
#include "imgui_nvn.h" 
#include "nya.h"
#include "imgui.h"
#include "utilites/input_mgr.h"
#include "nya/windows/menu_system.h"
 
HOOK_DEFINE_TRAMPOLINE(nnMain_hook) { 
    static void Callback() { 
        nn::fs::MountSdCardForDebug("sd");
        nya::nya_sd_avalible = true; 
        nya::nya_log("[nya] hewwo wowld :3\n");
        Orig(); 
    }
}; 

static void KirunaOverlay() {
    // Drive menu input and rendering
    nya::menu::handleInput();
    nya::menu::renderMenu();
}

extern "C" void exl_main(void *x0, void *x1) { 
    exl::hook::Initialize();
    // Install input hooks to allow disabling game input while menu is open
    nya::hid::install_hooks();
    nnMain_hook::InstallAtSymbol("nnMain"); 
    nvnImGui::InstallHooks();
    nvnImGui::addDrawFunc(nya::nya_main);
    nvnImGui::addDrawFunc(KirunaOverlay);
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}