#pragma once
#include "custom-types/shared/macros.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "SettingsViewController/SettingsViewController.hpp"

DECLARE_CLASS_CODEGEN(ParticleTuner, SettingsFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_INSTANCE_FIELD(ParticleTuner::SettingsViewController*, settingsViewController);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController *topViewController);   
)