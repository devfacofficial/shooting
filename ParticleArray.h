#ifndef PARTICLE_ARRAY_H
#define PARTICLE_ARRAY_H

#include <stdint.h>

#define PARTICLE_ARRAY_MAX_COUNT 10000u

//=============================================================================
// struct
//=============================================================================
//-----------------------------------------------------------------------------
//! @brief   Particle構造体
//! @details パーティクルの情報を保持する
//!
typedef struct
{
    double angle;                       //!< Particleの進行方向の角度
    double x;                           //!< ParticleのX座標
    double y;                           //!< ParticleのY座標
    double dx;                          //!< ParticleのX方向の移動量
    double dy;                          //!< ParticleのY方向の移動量
} Particle;

//-----------------------------------------------------------------------------
//! @brief   Particle配列構造体
//! @details Particle構造体の配列を保持する
//!
typedef struct
{
    uint32_t count;                     //!< Particleの個数  
    Particle Particles[];               //!< Particle構造体の配列
} ParticleArray;

ParticleArray* ParticleArray_New(uint32_t count);
void ParticleArray_Delete(ParticleArray* particleArray);
void ParticleArray_Init(ParticleArray* particleArray, int32_t cx, int32_t cy);
void ParticleArray_Update(ParticleArray* particleArray);

#endif
