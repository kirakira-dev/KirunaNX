#pragma once

#include "imgui.h"
#include "utilites/input_mgr.h"

namespace nya {
    namespace menu {
        // Menu states
        enum class MenuState {
            Hidden,
            Main,
            Combat,
            Movement,
            Visual,
            Render,
            Debug
        };

        // Menu navigation
        struct MenuNavigation {
            MenuState currentState = MenuState::Hidden;
            int selectedOption = 0;
            int maxOptions = 0;
            bool menuVisible = false;
        };

        // Menu options for each state
        struct MenuOptions {
            static constexpr const char* mainOptions[] = {
                "Combat",
                "Movement", 
                "Visual",
                "Render",
                "Debug/Test"
            };
            static constexpr int mainOptionsCount = 5;

            static constexpr const char* combatOptions[] = {
                "Infinite Ammo",
                "No Recoil",
                "Rapid Fire",
                "Auto Aim",
                "Back"
            };
            static constexpr int combatOptionsCount = 5;

            static constexpr const char* movementOptions[] = {
                "Speed Hack",
                "No Clip",
                "Fly Mode",
                "Teleport",
                "Back"
            };
            static constexpr int movementOptionsCount = 5;

            static constexpr const char* visualOptions[] = {
                "ESP Players",
                "ESP Items",
                "Wallhack",
                "No Fog",
                "Back"
            };
            static constexpr int visualOptionsCount = 5;

            static constexpr const char* renderOptions[] = {
                "Wireframe",
                "No Textures",
                "Brightness",
                "Contrast",
                "Back"
            };
            static constexpr int renderOptionsCount = 5;

            static constexpr const char* debugOptions[] = {
                "Show FPS",
                "Show Coordinates",
                "Memory Viewer",
                "Console",
                "Back"
            };
            static constexpr int debugOptionsCount = 5;
        };

        // Feature toggles
        struct FeatureToggles {
            // Combat features
            bool infiniteAmmo = false;
            bool noRecoil = false;
            bool rapidFire = false;
            bool autoAim = false;

            // Movement features
            bool speedHack = false;
            bool noClip = false;
            bool flyMode = false;
            bool teleport = false;

            // Visual features
            bool espPlayers = false;
            bool espItems = false;
            bool wallhack = false;
            bool noFog = false;

            // Render features
            bool wireframe = false;
            bool noTextures = false;
            float brightness = 1.0f;
            float contrast = 1.0f;

            // Debug features
            bool showFPS = false;
            bool showCoordinates = false;
            bool memoryViewer = false;
            bool console = false;
        };

        // Global instances
        extern MenuNavigation g_MenuNav;
        extern FeatureToggles g_Features;

        // Input handling
        void handleInput();
        
        // Menu rendering
        void renderMainMenu();
        void renderCombatMenu();
        void renderMovementMenu();
        void renderVisualMenu();
        void renderRenderMenu();
        void renderDebugMenu();
        
        // Navigation functions
        void navigateUp();
        void navigateDown();
        void selectOption();
        void goBack();
        void toggleMenu();
        
        // Main menu function
        void renderMenu();
    }
}
