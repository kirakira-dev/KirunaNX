#include "nya/windows/menu_system.h"
#include "utilites/input_mgr.h"

namespace nya {
    namespace menu {
        // Global instances
        MenuNavigation g_MenuNav;
        FeatureToggles g_Features;

        void handleInput() {
            // L button to toggle menu
            if (nya::hid::isPressL()) {
                toggleMenu();
            }

            // Only handle navigation if menu is visible
            if (!g_MenuNav.menuVisible) {
                return;
            }

            // Left stick button to close menu
            if (nya::hid::isPressStickL()) {
                goBack();
                return;
            }

            // DPAD Up/Down for navigation
            if (nya::hid::isPressPadUp()) {
                navigateUp();
            }
            if (nya::hid::isPressPadDown()) {
                navigateDown();
            }

            // A button to select (using existing A button function)
            if (nya::hid::isPressA()) {
                selectOption();
            }
        }

        void navigateUp() {
            if (g_MenuNav.selectedOption > 0) {
                g_MenuNav.selectedOption--;
            } else {
                g_MenuNav.selectedOption = g_MenuNav.maxOptions - 1;
            }
        }

        void navigateDown() {
            if (g_MenuNav.selectedOption < g_MenuNav.maxOptions - 1) {
                g_MenuNav.selectedOption++;
            } else {
                g_MenuNav.selectedOption = 0;
            }
        }

        void selectOption() {
            switch (g_MenuNav.currentState) {
                case MenuState::Main:
                    switch (g_MenuNav.selectedOption) {
                        case 0: g_MenuNav.currentState = MenuState::Combat; break;
                        case 1: g_MenuNav.currentState = MenuState::Movement; break;
                        case 2: g_MenuNav.currentState = MenuState::Visual; break;
                        case 3: g_MenuNav.currentState = MenuState::Render; break;
                        case 4: g_MenuNav.currentState = MenuState::Debug; break;
                    }
                    g_MenuNav.selectedOption = 0;
                    break;

                case MenuState::Combat:
                    switch (g_MenuNav.selectedOption) {
                        case 0: g_Features.infiniteAmmo = !g_Features.infiniteAmmo; break;
                        case 1: g_Features.noRecoil = !g_Features.noRecoil; break;
                        case 2: g_Features.rapidFire = !g_Features.rapidFire; break;
                        case 3: g_Features.autoAim = !g_Features.autoAim; break;
                        case 4: g_MenuNav.currentState = MenuState::Main; g_MenuNav.selectedOption = 0; break;
                    }
                    break;

                case MenuState::Movement:
                    switch (g_MenuNav.selectedOption) {
                        case 0: g_Features.speedHack = !g_Features.speedHack; break;
                        case 1: g_Features.noClip = !g_Features.noClip; break;
                        case 2: g_Features.flyMode = !g_Features.flyMode; break;
                        case 3: g_Features.teleport = !g_Features.teleport; break;
                        case 4: g_MenuNav.currentState = MenuState::Main; g_MenuNav.selectedOption = 0; break;
                    }
                    break;

                case MenuState::Visual:
                    switch (g_MenuNav.selectedOption) {
                        case 0: g_Features.espPlayers = !g_Features.espPlayers; break;
                        case 1: g_Features.espItems = !g_Features.espItems; break;
                        case 2: g_Features.wallhack = !g_Features.wallhack; break;
                        case 3: g_Features.noFog = !g_Features.noFog; break;
                        case 4: g_MenuNav.currentState = MenuState::Main; g_MenuNav.selectedOption = 0; break;
                    }
                    break;

                case MenuState::Render:
                    switch (g_MenuNav.selectedOption) {
                        case 0: g_Features.wireframe = !g_Features.wireframe; break;
                        case 1: g_Features.noTextures = !g_Features.noTextures; break;
                        case 2: /* Brightness slider - implement later */ break;
                        case 3: /* Contrast slider - implement later */ break;
                        case 4: g_MenuNav.currentState = MenuState::Main; g_MenuNav.selectedOption = 0; break;
                    }
                    break;

                case MenuState::Debug:
                    switch (g_MenuNav.selectedOption) {
                        case 0: g_Features.showFPS = !g_Features.showFPS; break;
                        case 1: g_Features.showCoordinates = !g_Features.showCoordinates; break;
                        case 2: g_Features.memoryViewer = !g_Features.memoryViewer; break;
                        case 3: g_Features.console = !g_Features.console; break;
                        case 4: g_MenuNav.currentState = MenuState::Main; g_MenuNav.selectedOption = 0; break;
                    }
                    break;
            }
        }

        void goBack() {
            if (g_MenuNav.currentState == MenuState::Main) {
                g_MenuNav.menuVisible = false;
                g_MenuNav.currentState = MenuState::Hidden;
            } else {
                g_MenuNav.currentState = MenuState::Main;
                g_MenuNav.selectedOption = 0;
            }
        }

        void toggleMenu() {
            g_MenuNav.menuVisible = !g_MenuNav.menuVisible;
            if (g_MenuNav.menuVisible) {
                g_MenuNav.currentState = MenuState::Main;
                g_MenuNav.selectedOption = 0;
            } else {
                g_MenuNav.currentState = MenuState::Hidden;
            }
        }

        void renderMainMenu() {
            ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
            
            if (ImGui::Begin("KirunaNX - Main Menu", &g_MenuNav.menuVisible)) {
                ImGui::Text("Use L to toggle menu, DPAD to navigate, A to select, Left Stick to go back");
                ImGui::Separator();
                
                for (int i = 0; i < MenuOptions::mainOptionsCount; i++) {
                    bool isSelected = (i == g_MenuNav.selectedOption);
                    if (isSelected) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.5f, 1.0f, 1.0f));
                    }
                    
                    if (ImGui::Button(MenuOptions::mainOptions[i], ImVec2(200, 30))) {
                        g_MenuNav.selectedOption = i;
                        selectOption();
                    }
                    
                    if (isSelected) {
                        ImGui::PopStyleColor();
                    }
                }
            }
            ImGui::End();
        }

        void renderCombatMenu() {
            ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
            
            if (ImGui::Begin("Combat Options", &g_MenuNav.menuVisible)) {
                ImGui::Text("Combat Features");
                ImGui::Separator();
                
                for (int i = 0; i < MenuOptions::combatOptionsCount; i++) {
                    bool isSelected = (i == g_MenuNav.selectedOption);
                    if (isSelected) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.5f, 1.0f, 1.0f));
                    }
                    
                    if (ImGui::Button(MenuOptions::combatOptions[i], ImVec2(200, 30))) {
                        g_MenuNav.selectedOption = i;
                        selectOption();
                    }
                    
                    if (isSelected) {
                        ImGui::PopStyleColor();
                    }
                }
            }
            ImGui::End();
        }

        void renderMovementMenu() {
            ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
            
            if (ImGui::Begin("Movement Options", &g_MenuNav.menuVisible)) {
                ImGui::Text("Movement Features");
                ImGui::Separator();
                
                for (int i = 0; i < MenuOptions::movementOptionsCount; i++) {
                    bool isSelected = (i == g_MenuNav.selectedOption);
                    if (isSelected) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.5f, 1.0f, 1.0f));
                    }
                    
                    if (ImGui::Button(MenuOptions::movementOptions[i], ImVec2(200, 30))) {
                        g_MenuNav.selectedOption = i;
                        selectOption();
                    }
                    
                    if (isSelected) {
                        ImGui::PopStyleColor();
                    }
                }
            }
            ImGui::End();
        }

        void renderVisualMenu() {
            ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
            
            if (ImGui::Begin("Visual Options", &g_MenuNav.menuVisible)) {
                ImGui::Text("Visual Features");
                ImGui::Separator();
                
                for (int i = 0; i < MenuOptions::visualOptionsCount; i++) {
                    bool isSelected = (i == g_MenuNav.selectedOption);
                    if (isSelected) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.5f, 1.0f, 1.0f));
                    }
                    
                    if (ImGui::Button(MenuOptions::visualOptions[i], ImVec2(200, 30))) {
                        g_MenuNav.selectedOption = i;
                        selectOption();
                    }
                    
                    if (isSelected) {
                        ImGui::PopStyleColor();
                    }
                }
            }
            ImGui::End();
        }

        void renderRenderMenu() {
            ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
            
            if (ImGui::Begin("Render Options", &g_MenuNav.menuVisible)) {
                ImGui::Text("Render Features");
                ImGui::Separator();
                
                for (int i = 0; i < MenuOptions::renderOptionsCount; i++) {
                    bool isSelected = (i == g_MenuNav.selectedOption);
                    if (isSelected) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.5f, 1.0f, 1.0f));
                    }
                    
                    if (ImGui::Button(MenuOptions::renderOptions[i], ImVec2(200, 30))) {
                        g_MenuNav.selectedOption = i;
                        selectOption();
                    }
                    
                    if (isSelected) {
                        ImGui::PopStyleColor();
                    }
                }
            }
            ImGui::End();
        }

        void renderDebugMenu() {
            ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
            
            if (ImGui::Begin("Debug Options", &g_MenuNav.menuVisible)) {
                ImGui::Text("Debug Features");
                ImGui::Separator();
                
                for (int i = 0; i < MenuOptions::debugOptionsCount; i++) {
                    bool isSelected = (i == g_MenuNav.selectedOption);
                    if (isSelected) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.5f, 1.0f, 1.0f));
                    }
                    
                    if (ImGui::Button(MenuOptions::debugOptions[i], ImVec2(200, 30))) {
                        g_MenuNav.selectedOption = i;
                        selectOption();
                    }
                    
                    if (isSelected) {
                        ImGui::PopStyleColor();
                    }
                }
            }
            ImGui::End();
        }

        void renderMenu() {
            // Update max options based on current state
            switch (g_MenuNav.currentState) {
                case MenuState::Main:
                    g_MenuNav.maxOptions = MenuOptions::mainOptionsCount;
                    renderMainMenu();
                    break;
                case MenuState::Combat:
                    g_MenuNav.maxOptions = MenuOptions::combatOptionsCount;
                    renderCombatMenu();
                    break;
                case MenuState::Movement:
                    g_MenuNav.maxOptions = MenuOptions::movementOptionsCount;
                    renderMovementMenu();
                    break;
                case MenuState::Visual:
                    g_MenuNav.maxOptions = MenuOptions::visualOptionsCount;
                    renderVisualMenu();
                    break;
                case MenuState::Render:
                    g_MenuNav.maxOptions = MenuOptions::renderOptionsCount;
                    renderRenderMenu();
                    break;
                case MenuState::Debug:
                    g_MenuNav.maxOptions = MenuOptions::debugOptionsCount;
                    renderDebugMenu();
                    break;
                case MenuState::Hidden:
                    // Don't render anything
                    break;
            }
        }
    }
}
