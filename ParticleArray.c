#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "ParticleArray.h"

//-----------------------------------------------------------------------------
//! @brief   コンストラクタ
//! @details 最大1万個のParticleを生成可能
//! @return  オブジェクトのポインタ
//!
ParticleArray* ParticleArray_New(
    uint32_t count)                     //!< [I] 配列の要素数
{
    if (count == 0 || count > PARTICLE_ARRAY_MAX_COUNT)
    {
        return NULL;
    }

    ParticleArray* particleArray =
        malloc(sizeof *particleArray + (size_t)count * sizeof particleArray->Particles[0]);

    if (particleArray == NULL)
    {
        return NULL;
    }

    particleArray->count = (uint32_t)count;
    return particleArray;
}

//-----------------------------------------------------------------------------
//! @brief   デストラクタ
//! @details 無し
//! @return  無し
//!
void ParticleArray_Delete(
    ParticleArray* particleArray)                 //!< [I] オブジェクトのポインタ
{
    if (particleArray != NULL)
    {
        free(particleArray);
    }
}  

//-----------------------------------------------------------------------------
//! @brief   初期化
//! @details 角度、始点（画面中央）、X/Y方向の移動量を設定する
//! @return  無し
//!
void ParticleArray_Init(
    ParticleArray* particleArray,                     //!< [I] オブジェクトのポインタ
    int32_t   cx,                           //!< [I] 画面中央X座標    
    int32_t   cy)                           //!< [I] 画面中央Y座標
{
    if (particleArray == NULL)
    {
        return;
    }

    for(uint32_t idx=0; idx<particleArray->count; idx++)
    {
        particleArray->Particles[idx].angle = (double)idx * (2.0 * 3.141592653589793 / particleArray->count);
        particleArray->Particles[idx].x     = (double)cx;
        particleArray->Particles[idx].y     = (double)cy;
        particleArray->Particles[idx].dx    = cos(particleArray->Particles[idx].angle);
        particleArray->Particles[idx].dy    = sin(particleArray->Particles[idx].angle);
    }
}

//-----------------------------------------------------------------------------
//! @brief   X/Y更新
//! @details X/Y座標に移動量を加算する
//! @return  無し
//!
void ParticleArray_Update(
    ParticleArray* particleArray)                 //!< [I] オブジェクトのポインタ        
{
    if (particleArray == NULL)
    {
        return;
    }

    for (uint32_t idx=0; idx<particleArray->count; idx++)
    {
        particleArray->Particles[idx].x += particleArray->Particles[idx].dx;
        particleArray->Particles[idx].y += particleArray->Particles[idx].dy;
    }
}
