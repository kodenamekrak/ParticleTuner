#pragma once
#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(ReducedNoteParticles, bool, "reducedNoteParticles", false);
    CONFIG_VALUE(ReducedBombCutEffects, bool, "reducedBombCutEffects", false);
    CONFIG_VALUE(ReducedClashEffects, bool, "reducedClashEffects", false);
    CONFIG_VALUE(ReducedDustParticles, bool, "reducedDustParticles", false);
    CONFIG_VALUE(RainbowParticles, bool, "rainbowParticles", false);

    CONFIG_VALUE(SparklesMultiplier, float, "sparkleMultiplier", 1.0f);
    CONFIG_VALUE(SparklesLifetimeMultiplier, float, "lifetimeMultiplier", 1.0f);
    CONFIG_VALUE(ExplosionsMultiplier, float, "explosionMultiplier", 1.0f);
    CONFIG_VALUE(ExplosionsLifetimeMultiplier, float, "explosionLifetimeMultiplier", 1.0f);
    CONFIG_VALUE(ParticleOpacity, float, "particleOpacity", 1.0f);
)