#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "BomArray.h"

//-----------------------------------------------------------------------------
//! @brief   コンストラクタ
//! @details 最大1万個のBomを生成可能
//! @return  オブジェクトのポインタ
//!
BomArray* BomArray_New(
    uint32_t count)                     //!< [I] 配列の要素数
{
    if (count == 0 || count > BOM_ARRAY_MAX_COUNT)
    {
        return NULL;
    }

    BomArray* bomArray =
        malloc(sizeof *bomArray + (size_t)count * sizeof bomArray->Boms[0]);

    if (bomArray == NULL)
    {
        return NULL;
    }

    bomArray->count = (uint32_t)count;
    return bomArray;
}

//-----------------------------------------------------------------------------
//! @brief   デストラクタ
//! @details 無し
//! @return  無し
//!
void BomArray_Delete(
    BomArray* bomArray)                 //!< [I] オブジェクトのポインタ
{
    if (bomArray != NULL)
    {
        free(bomArray);
    }
}  

//-----------------------------------------------------------------------------
//! @brief   初期化
//! @details 角度、始点（画面中央）、X/Y方向の移動量を設定する
//! @return  無し
//!
void BomArray_Init(
    BomArray* bomArray,                     //!< [I] オブジェクトのポインタ
    int32_t   cx,                           //!< [I] 画面中央X座標    
    int32_t   cy)                           //!< [I] 画面中央Y座標
{
    if (bomArray == NULL)
    {
        return;
    }

    for(uint32_t idx=0; idx<bomArray->count; idx++)
    {
        bomArray->Boms[idx].angle = (double)idx * (2.0 * 3.141592653589793 / bomArray->count);
        bomArray->Boms[idx].x     = (double)cx;
        bomArray->Boms[idx].y     = (double)cy;
        bomArray->Boms[idx].dx    = cos(bomArray->Boms[idx].angle);
        bomArray->Boms[idx].dy    = sin(bomArray->Boms[idx].angle);
    }
}

//-----------------------------------------------------------------------------
//! @brief   X/Y更新
//! @details X/Y座標に移動量を加算する
//! @return  無し
//!
void BomArray_Update(
    BomArray* bomArray)                 //!< [I] オブジェクトのポインタ        
{
    if (bomArray == NULL)
    {
        return;
    }

    for (uint32_t idx=0; idx<bomArray->count; idx++)
    {
        bomArray->Boms[idx].x += bomArray->Boms[idx].dx;
        bomArray->Boms[idx].y += bomArray->Boms[idx].dy;
    }
}
