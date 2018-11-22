
#include <stdio.h>
#include <stdlib.h>
#include "program.h"

/*  initialize a program instance */
Program_t * PROG_Initialize(void)
{
    Program_t * new_prog = (Program_t *) calloc(sizeof(Program_t), 1);
    return new_prog;
}

/*  setters and getters */
ProgState_t PROG_StateGet(Program_t * self)
{
    return self->current_state;
}

void PROG_StateSet(Program_t * self, ProgState_t new_state)
{
    self->current_state = new_state;
}

/*  destroys a program instance    */
void PROG_TearDown(Program_t * self)
{
    free(self);
}
