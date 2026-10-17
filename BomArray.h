#ifndef BOM_ARRAY_H
#define BOM_ARRAY_H

#include <stdint.h>

#define BOM_ARRAY_MAX_COUNT 10000u

//=============================================================================
// struct
//=============================================================================
//-----------------------------------------------------------------------------
//! @brief   Bom構造体
//! @details ボムの情報を保持する
//!
typedef struct
{
    double angle;                       //!< Bomの進行方向の角度
    double x;                           //!< BomのX座標
    double y;                           //!< BomのY座標
    double dx;                          //!< BomのX方向の移動量
    double dy;                          //!< BomのY方向の移動量
} Bom;

//-----------------------------------------------------------------------------
//! @brief   Bom配列構造体
//! @details Bom構造体の配列を保持する
//!
typedef struct
{
    uint32_t count;                     //!< Bomの個数  
    Bom      Boms[];                    //!< Bom構造体の配列
} BomArray;

BomArray* BomArray_New(uint32_t count);
void BomArray_Delete(BomArray* bomArray);
void BomArray_Init(BomArray* bomArray, int32_t cx, int32_t cy);
void BomArray_Update(BomArray* bomArray);

#endif
