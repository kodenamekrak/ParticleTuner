#pragma once

#include "bsml/shared/Helpers/creation.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/Helpers/getters.hpp"

#include "SettingsViewController/SettingsFlowCoordinator.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

namespace ParticleTuner
{
    class UIManager
    {
        ParticleTuner::SettingsFlowCoordinator *flow;

        public:
            void Init()
            {
                BSML::Register::RegisterMenuButton("ParticleTuner", "ParticleTuner", [this]()
                {
                    ShowFlow();
                });
            }

            void ShowFlow()
            {
                if (!flow || !flow->m_CachedPtr.m_value)
                    flow = BSML::Helpers::CreateFlowCoordinator<ParticleTuner::SettingsFlowCoordinator *>();
                
                auto parentFlow = BSML::Helpers::GetMainFlowCoordinator()->YoungestChildFlowCoordinatorOrSelf();
                parentFlow->PresentFlowCoordinator(flow, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, HMUI::ViewController::AnimationType::Out, false);
            }
    };
    inline static UIManager manager;
}