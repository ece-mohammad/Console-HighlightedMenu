#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdint.h>
#include "key.h"

/*  initialize a key instance   */
Key_t * KEY_Init(void)
{
    Key_t * new_key = (Key_t *) calloc(sizeof(Key_t), 1);
    if (new_key)
    {
        new_key->code = 0;
        new_key->type = KEY_TYPE_NORMAL;
    }   /*  end if  */

    return new_key;
}

/*  gets key code   */
unsigned char KEY_CodeGet(Key_t * self)
{
    return self->code;
}

/*  sets key code   */
void KEY_CodeSet(Key_t * self, unsigned char code)
{
    self->code = code;
}

/*  gets keys type  */
Key_Type_t KEY_TypeGet(Key_t * self)
{
    return self->type;
}

/*  sets key type   */
void KEY_TypeSet(Key_t * self, Key_Type_t type)
{
    self->type = type;
}

/*  gets key from user  */
void KEY_GetKey(Key_t * self)
{

    self->code = getch();

    switch (self->code)
    {
        case KCODE_SCROLL_PREFIX:
            self->type = KEY_TYPE_SCROLL;
            self->code = getch();
            break;

        case KCODE_CONTROL_PREFIX:
            self->type = KEY_TYPE_CONTROL;
            self->code = getch();
            break;

        default:
            self->type = KEY_TYPE_NORMAL;
            break;

    }   /*  end switch  */
}

/*  destroy */
void KEY_TearDown(Key_t *self)
{
    free(self);
}
