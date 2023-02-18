#pragma once
#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,
    CONFIG_VALUE(Enabled, bool, "enabled", true);

    CONFIG_VALUE(ReducedNoteParticles, bool, "reducedNoteParticles", false);
    CONFIG_VALUE(ReducedBombClashEffects, bool, "reducedClashEffects", false);
    CONFIG_VALUE(ReducedDustParticles, bool, "reducedDustParticles", false);
    CONFIG_VALUE(RainbowParticles, bool, "rainbowParticles", false);

    CONFIG_VALUE(SparkleMultiplier, float, "sparkleMultiplier", 1.0f);
    CONFIG_VALUE(SparkleLifetimeMultiplier, float, "lifetimeMultiplier", 1.0f);
    CONFIG_VALUE(SparkleSizeMultiplier, float, "sparkleSizeMultiplier", 1.0f);
    CONFIG_VALUE(ExplosionMultiplier, float, "explosionMultiplier", 1.0f);
    CONFIG_VALUE(ExplosionLifetimeMultiplier, float, "explosionLifetimeMultiplier", 1.0f);
    CONFIG_VALUE(ExplosionSizeMultiplier, float, "explosionSizeMultiplier", 1.0f)
    CONFIG_VALUE(ParticleOpacity, float, "particleOpacity", 1.0f);
)