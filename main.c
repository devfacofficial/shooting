//-----------------------------------------------------------------------------
//! @brief   パーティクル描画
//! @details コンソール上に、円形に広がる"*"を描画する
//!
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include "BomArray.h"
#include "DrawObject.h"

#define PARTICLE_COUNT  500
#define FRAME_COUNT     100

int main(void);
bool DrawBoms(DrawObject* drawObject, const BomArray* bomArray, uint8_t ch);

#define MSG_INITIALIZE_FAILED "Failed to initialize console drawing.\n"
#define MSG_ALLOCATE_FAILED   "Failed to allocate particle array.\n"
#define MSG_DIMENSION_FAILED  "Failed to get console dimensions.\n"
#define MSG_DRAW_FAILED       "Failed to draw boms.\n"
#define MSG_CLEAR_FAILED      "Failed to clear boms.\n"

//-----------------------------------------------------------------------------
//! @brief   メイン
//! @details コンソールにBomを描画する
//! @return  無し
//!
int main(void)
{
    int result = 1;
    int32_t centerX = 0;
    int32_t centerY = 0;
    DrawObject* drawObject = NULL;
    BomArray* bomArray = NULL;

    // 初期化
    drawObject = DrawObject_New();
    if(drawObject == NULL)
    {
        fputs(MSG_INITIALIZE_FAILED, stderr);
        goto END;
    }

    bomArray = BomArray_New(PARTICLE_COUNT);
    if(bomArray == NULL)
    {
        fputs(MSG_ALLOCATE_FAILED, stderr);
        goto END;
    }

    if(!DrawObject_GetCenter(drawObject, &centerX, &centerY))
    {
        fputs(MSG_DIMENSION_FAILED, stderr);
        goto END;
    }
    BomArray_Init(bomArray, centerX, centerY);

    // Bom描画
    for (int32_t repeat = 0; repeat < FRAME_COUNT; repeat++)
    {
        if(!DrawBoms(drawObject, bomArray, '*'))
        {
            fputs(MSG_DRAW_FAILED, stderr);
            goto END;
        }
        Sleep(80);
        if(!DrawBoms(drawObject, bomArray, ' '))
        {
            fputs(MSG_CLEAR_FAILED, stderr);
            goto END;
        }
        BomArray_Update(bomArray);
    }
    result = 0;

END:
    // 後処理
    if(bomArray != NULL) BomArray_Delete(bomArray);
    if(drawObject != NULL) DrawObject_Delete(drawObject);
    return result;
}

//-----------------------------------------------------------------------------
//! @brief   Bom配列の全要素を描画または消去する
//! @details 描画または消去に失敗した場合はfalseを返す
//! @return  成功時true
//!
bool DrawBoms(
    DrawObject* drawObject,
    const BomArray* bomArray,
    uint8_t ch)
{
    for (uint32_t idx = 0; idx < bomArray->count; idx++)
    {
        int32_t x = (int32_t)lround(bomArray->Boms[idx].x);
        int32_t y = (int32_t)lround(bomArray->Boms[idx].y);
        if (!DrawObject_PutChar(drawObject, x, y, ch))
        {
            return false;
        }
    }

    return true;
}
