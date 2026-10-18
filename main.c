//-----------------------------------------------------------------------------
//! @brief   パーティクル描画
//! @details コンソール上に、円形に広がる"*"を描画する
//!
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include "ParticleArray.h"
#include "DrawObject.h"

#define PARTICLE_COUNT  500
#define FRAME_COUNT     100

int main(void);
bool DrawParticles(DrawObject* drawObject, const ParticleArray* particleArray, uint8_t ch);

#define MSG_INITIALIZE_FAILED "Failed to initialize console drawing.\n"
#define MSG_ALLOCATE_FAILED   "Failed to allocate particle array.\n"
#define MSG_DIMENSION_FAILED  "Failed to get console dimensions.\n"
#define MSG_DRAW_FAILED       "Failed to draw particles.\n"
#define MSG_CLEAR_FAILED      "Failed to clear particles.\n"

//-----------------------------------------------------------------------------
//! @brief   メイン
//! @details コンソールにParticleを描画する
//! @return  無し
//!
int main(void)
{
    int result = 1;
    int32_t centerX = 0;
    int32_t centerY = 0;
    DrawObject* drawObject = NULL;
    ParticleArray* ParticleArray = NULL;

    // 初期化
    drawObject = DrawObject_New();
    if(drawObject == NULL)
    {
        fputs(MSG_INITIALIZE_FAILED, stderr);
        goto END;
    }

    ParticleArray = ParticleArray_New(PARTICLE_COUNT);
    if(ParticleArray == NULL)
    {
        fputs(MSG_ALLOCATE_FAILED, stderr);
        goto END;
    }

    if(!DrawObject_GetCenter(drawObject, &centerX, &centerY))
    {
        fputs(MSG_DIMENSION_FAILED, stderr);
        goto END;
    }
    ParticleArray_Init(ParticleArray, centerX, centerY);

    // Particle描画
    for (int32_t repeat = 0; repeat < FRAME_COUNT; repeat++)
    {
        if(!DrawParticles(drawObject, ParticleArray, '*'))
        {
            fputs(MSG_DRAW_FAILED, stderr);
            goto END;
        }
        Sleep(80);
        if(!DrawParticles(drawObject, ParticleArray, ' '))
        {
            fputs(MSG_CLEAR_FAILED, stderr);
            goto END;
        }
        ParticleArray_Update(ParticleArray);
    }
    result = 0;

END:
    // 後処理
    if(ParticleArray != NULL) ParticleArray_Delete(ParticleArray);
    if(drawObject != NULL) DrawObject_Delete(drawObject);
    return result;
}

//-----------------------------------------------------------------------------
//! @brief   Particle配列の全要素を描画または消去する
//! @details 描画または消去に失敗した場合はfalseを返す
//! @return  成功時true
//!
bool DrawParticles(
    DrawObject* drawObject,
    const ParticleArray* particleArray,
    uint8_t ch)
{
    for (uint32_t idx = 0; idx < particleArray->count; idx++)
    {
        int32_t x = (int32_t)lround(particleArray->Particles[idx].x);
        int32_t y = (int32_t)lround(particleArray->Particles[idx].y);
        if (!DrawObject_PutChar(drawObject, x, y, ch))
        {
            return false;
        }
    }

    return true;
}
