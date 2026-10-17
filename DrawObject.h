#ifndef DRAW_OBJECT_H
#define DRAW_OBJECT_H

#include <stdbool.h>
#include <stdint.h>
#include <windows.h>

typedef struct
{
    HANDLE Output;
    CONSOLE_SCREEN_BUFFER_INFO Info;
} DrawObject;

DrawObject* DrawObject_New(void);
void DrawObject_Delete(DrawObject* drawObject);
bool DrawObject_PutChar(DrawObject* drawObject, int32_t x, int32_t y, uint8_t ch);
bool DrawObject_GetCenter(DrawObject* drawObject, int32_t* centerX, int32_t* centerY);

#endif