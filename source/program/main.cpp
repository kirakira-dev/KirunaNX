#include "lib/hook/trampoline.hpp"
#include "nn/fs.h" 
#include "imgui_nvn.h" 
#include "nya.h"
#include "imgui.h"
 
HOOK_DEFINE_TRAMPOLINE(nnMain_hook) { 
    static void Callback() { 
        nn::fs::MountSdCardForDebug("sd");
        nya::nya_sd_avalible = true; 
        nya::nya_log("[nya] hewwo wowld :3\n");
        Orig(); 
    }
}; 

static void KirunaOverlay() {
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);

    ImGuiWindowFlags flags = 0;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoResize;
    flags |= ImGuiWindowFlags_NoCollapse;
    flags |= ImGuiWindowFlags_NoSavedSettings;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

    if (ImGui::Begin("KirunaNX", nullptr, flags)) {
        ImGui::Selectable("Combat", false);
        ImGui::Selectable("Movement", false);
        ImGui::Selectable("Visual", false);
        ImGui::Selectable("Render", false);
        ImGui::Selectable("Debug/Test", false);
    }
    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

extern "C" void exl_main(void *x0, void *x1) { 
    exl::hook::Initialize();
    nnMain_hook::InstallAtSymbol("nnMain"); 
    nvnImGui::InstallHooks();
    nvnImGui::addDrawFunc(nya::nya_main);
    nvnImGui::addDrawFunc(KirunaOverlay);
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}