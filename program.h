
#ifndef _PROGRAM_H_
#define _PROGRAM_H_

/* -------------------- Constants ------------------------- */
typedef enum
{
    STATE_DISPLAY_UPDATE,
    STATE_INPUT,
    STATE_EXIT,
    NUMBER_OF_STATES,
} ProgState_t;

typedef struct
{
    unsigned int current_state;
} Program_t;


/* ------------------ Public APIs --------------------------- */

/*  initialize a program instance */
Program_t * PROG_Initialize(void);

/*  setters and getters */
ProgState_t PROG_StateGet(Program_t * self);
void PROG_StateSet(Program_t * self, ProgState_t new_state);

/*  destroys a program instance    */
void PROG_TearDown(Program_t * self);

#endif // _PROGRAM_H_
