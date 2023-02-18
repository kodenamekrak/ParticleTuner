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
        HMUI::FlowCoordinator *parentFlow;
        ParticleTuner::SettingsFlowCoordinator *flow;

        public:
            void Init()
            {
                BSML::Register::RegisterMenuButton("ParticleTuner", "yes", [this]()
                {
                    ShowFlow(false);
                });
            }

            void ShowFlow(bool immediately)
            {
                if (flow == nullptr || flow->m_CachedPtr.m_value == nullptr)
                    flow = BSML::Helpers::CreateFlowCoordinator<ParticleTuner::SettingsFlowCoordinator *>();
                
                parentFlow = BSML::Helpers::GetMainFlowCoordinator()->YoungestChildFlowCoordinatorOrSelf();
                parentFlow->PresentFlowCoordinator(flow, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, HMUI::ViewController::AnimationType::Out, false);
            }
    };
    inline static UIManager manager;
}