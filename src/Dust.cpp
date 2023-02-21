#include "main.hpp"
#include "Dust.hpp"

#include "UnityEngine/ParticleSystem.hpp"
#include "UnityEngine/ParticleSystem_EmissionModule.hpp"
#include "UnityEngine/Resources.hpp"

void ParticleTuner::Dust::SetDustActive(bool value)
{
    for(auto particle : UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::ParticleSystem*>())
    {
        if(particle->get_name() == "DustPS")
        {
            particle->get_emission().set_enabled(value);
        }
    }
}