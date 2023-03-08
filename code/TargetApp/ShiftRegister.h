#ifndef __SHIFT_REGISTER_H__
#define __SHIFT_REGISTER_H__

#include "General.h"
#include <stddef.h>

typedef struct ShiftRegisterStruct
{
	void   *registers;    /* Array of elements functioning as shift register */
	size_t  registerSize; /* Sizeof(register[0]) */
	uint32  capacity;     /* Total number of possible elements */
	uint32  size;	      /* Number of used elements */
	uint32  start;        /* Points to the first element inserted */
	uint32  end;		  /* Points to the NEXT available free slot */
} ShiftRegister;

void ShiftRegister_Initialise(ShiftRegister *shiftRegister, void *registers, size_t registerSize, uint32 capacity);
void ShiftRegister_Reset(ShiftRegister *shiftRegister);
Bool ShiftRegister_Add(ShiftRegister *shiftRegister, void const *element);
Bool ShiftRegister_Shift(ShiftRegister *shiftRegister, void *element);
Bool ShiftRegister_IsFull(ShiftRegister const *shiftRegister);
const void* ShiftRegister_Index(ShiftRegister *shiftRegister, uint32 index);

#endif /* __TIME_STAMP_SHIFT_REGISTER_H__ */
