#ifndef JUMP_SUPPRESSOR_H
#define JUMP_SUPPRESSOR_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NOT_USE
typedef struct
{
	struct ClockPathStruct*		clockPath;
	Bool						enabled;
	float						suppressingJump;

} JumpSuppressor;

void InitialiseJumpSuppressor(JumpSuppressor* js, struct ClockPathStruct* clockPath);
void ResetJumpSuppressor(JumpSuppressor* js);
#define EnableJumpSuppressor(js, enable) ((js)->enabled = (enable))
#define JumpSuppressorEnabled(js) ((js)->enabled)
void SlowTickJumpSuppressor(JumpSuppressor* js);
#define SuppressingJump(js) ((js)->suppressingJump)
#endif

#ifdef __cplusplus
}
#endif

#endif