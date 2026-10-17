#include <stdint.h>
#include <stdlib.h>
#include <windows.h>
#include "DrawObject.h"

//-----------------------------------------------------------------------------
//! @brief   描画オブジェクトを作成する
//! @return  成功時はオブジェクトのポインタ、失敗時はNULL
//!
DrawObject* DrawObject_New(void)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    if (output == INVALID_HANDLE_VALUE || output == NULL)
    {
        return NULL;
    }

    DrawObject* drawObject = malloc(sizeof *drawObject);
    if (drawObject == NULL)
    {
        return NULL;
    }

    if (!GetConsoleScreenBufferInfo(output, &drawObject->Info))
    {
        free(drawObject);
        return NULL;
    }

    drawObject->Output = output;
    return drawObject;
}

//-----------------------------------------------------------------------------
//! @brief   描画オブジェクトを解放する
//!
void DrawObject_Delete(DrawObject* drawObject)
{
    free(drawObject);
}

//-----------------------------------------------------------------------------
//! @brief   指定位置に1文字描画する
//! @details 表示領域外の座標は描画せず、APIエラー時はfalseを返す
//! @return  成功時true
//!
bool DrawObject_PutChar(
    DrawObject* drawObject,
    int32_t x,
    int32_t y,
    uint8_t ch)
{
    if (drawObject == NULL)
    {
        return false;
    }

    if (x < drawObject->Info.srWindow.Left ||
        x > drawObject->Info.srWindow.Right ||
        y < drawObject->Info.srWindow.Top ||
        y > drawObject->Info.srWindow.Bottom)
    {
        return true;
    }

    COORD position = { (SHORT)x, (SHORT)y };
    if (!SetConsoleCursorPosition(drawObject->Output, position))
    {
        return false;
    }

    DWORD written = 0;
    return WriteConsoleA(drawObject->Output, &ch, 1, &written, NULL) && (written == 1);
}

//-----------------------------------------------------------------------------
//! @brief   表示領域の中心座標を取得する
//! @return  成功時true
//!
bool DrawObject_GetCenter(
    DrawObject* drawObject,
    int32_t* centerX,
    int32_t* centerY)
{
    if (drawObject == NULL || centerX == NULL || centerY == NULL)
    {
        return false;
    }

    *centerX = drawObject->Info.srWindow.Left +
        (drawObject->Info.srWindow.Right -
         drawObject->Info.srWindow.Left + 1) / 2;
    *centerY = drawObject->Info.srWindow.Top +
        (drawObject->Info.srWindow.Bottom -
         drawObject->Info.srWindow.Top + 1) / 2;
    return true;
}
