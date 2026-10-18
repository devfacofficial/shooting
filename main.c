//-----------------------------------------------------------------------------
//! @brief   パーティクル描画
//! @details コンソール上に、円形に広がる"*"を描画する
//!
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <math.h>

//----------------------------------------------------------------------------
// const
#define PARTICLE_COUNT  500
#define FRAME_COUNT     100

//-----------------------------------------------------------------------------
// global
HANDLE Output;                      //!< コンソール出力ハンドル
CONSOLE_SCREEN_BUFFER_INFO Info;    //!< コンソールの表示領域情報
double AngleArray[PARTICLE_COUNT];  //!< Particleの進行方向の角度
double XArray[PARTICLE_COUNT];      //!< ParticleのX座標
double YArray[PARTICLE_COUNT];      //!< ParticleのY座標
double DxArray[PARTICLE_COUNT];     //!< ParticleのX方向の移動量
double DyArray[PARTICLE_COUNT];     //!< ParticleのY方向の移動量

int main(void);
void DrawParticles(uint8_t ch, double xArray[], double yArray[], uint32_t count);
bool PutChar(int32_t x, int32_t y, uint8_t ch);

//-----------------------------------------------------------------------------
//! @brief   メイン
//! @details コンソールにParticleを描画する
//! @return  無し
//!
int main(void)
{
    int32_t centerX = 0;
    int32_t centerY = 0;

    // 描画情報の初期化
    Output = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(Output, &Info);
    centerX = Info.srWindow.Left + (Info.srWindow.Right - Info.srWindow.Left + 1) / 2;
    centerY = Info.srWindow.Top + (Info.srWindow.Bottom - Info.srWindow.Top + 1) / 2;

    // Particle初期化
    for(uint32_t idx=0; idx<PARTICLE_COUNT; idx++)
    {
        AngleArray[idx] = (double)idx * (2.0 * 3.141592653589793 / PARTICLE_COUNT);
        XArray[idx]     = (double)centerX;
        YArray[idx]     = (double)centerY;
        DxArray[idx]    = cos(AngleArray[idx]);
        DyArray[idx]    = sin(AngleArray[idx]);
    }

    // Particle描画
    for (int32_t repeat = 0; repeat < FRAME_COUNT; repeat++)
    {
        DrawParticles('*', XArray, YArray, PARTICLE_COUNT);
        Sleep(80);
        DrawParticles(' ', XArray, YArray, PARTICLE_COUNT);

        // 座標を更新
        for (uint32_t idx=0; idx<PARTICLE_COUNT; idx++)
        {
            XArray[idx] += DxArray[idx];
            YArray[idx] += DyArray[idx];
        }
    }

    // 後処理
    return 0;
}

//-----------------------------------------------------------------------------
//! @brief   Particle配列の全要素を描画または消去する
//! @details 無し
//! @return  無し
//!
void DrawParticles(
    uint8_t ch,                         //!< [I]描画するキャラクタ
    double xArray[],                    //!< [I]X座標の配列
    double yArray[],                    //!< [I]Y座標の配列
    uint32_t count)                     //!< [I]配列数
{
    // 指定された座標に1文字描画する
    for (uint32_t idx = 0; idx < count; idx++)
    {
        int32_t x = (int32_t)lround(xArray[idx]);
        int32_t y = (int32_t)lround(yArray[idx]);
        PutChar(x, y, ch);
    }
}

//-----------------------------------------------------------------------------
//! @brief   指定位置に1文字描画する
//! @details 表示領域外の座標は描画しない
//! @return  成功時true
//!
bool PutChar(
    int32_t x,                          //!< [I]キャラクタを描画するX座標
    int32_t y,                          //!< [I]キャラクタを描画するY座標
    uint8_t ch)                         //!< [I]描画するキャラクタ
{
    // 表示領域外の座標は描画しない
    if (x < Info.srWindow.Left ||
        x > Info.srWindow.Right ||
        y < Info.srWindow.Top ||
        y > Info.srWindow.Bottom)
    {
        return true;
    }

    // 文字を描画する位置にカーソルを移動する
    COORD position = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(Output, position);

    // カーソルの位置に1文字描画する
    DWORD written = 0;
    return WriteConsoleA(Output, &ch, 1, &written, NULL) && (written == 1);
}
