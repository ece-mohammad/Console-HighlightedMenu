
#ifndef _KEY_H_
#define _KEY_H_

/* ------------------ Custom Types --------------------------- */
typedef enum
{

    KEY_TYPE_NORMAL,
    KEY_TYPE_SCROLL,
    KEY_TYPE_CONTROL,

} Key_Type_t;

typedef struct
{

    Key_Type_t type;
    unsigned char code;

} Key_t;

/*      Key codes       */
#define KCODE_SCROLL_PREFIX  224
#define KCODE_CONTROL_PREFIX 0

#define KCODE_ENTER          13
#define KCODE_ESC            27
#define KCODE_TAB            9

#define KCODE_UP             72
#define KCODE_DOWN           80
#define KCODE_LEFT           75
#define KCODE_RIGHT          77
#define KCODE_HOME           71
#define KCODE_END            81
#define KCODE_PG_UP          73
#define KCODE_PG_DWN         79

/* ------------------------------- public APIs ----------------------------------- */

/*  initialize a key instance   */
Key_t * KEY_Init(void);

/*  gets key code   */
unsigned char KEY_CodeGet(Key_t * self);

/*  sets key code   */
void KEY_CodeSet(Key_t * self, unsigned char code);

/*  gets keys type  */
Key_Type_t KEY_TypeGet(Key_t * self);

/*  sets key type   */
void KEY_TypeSet(Key_t * self, Key_Type_t type);

/*  gets key from user  */
void KEY_GetKey(Key_t * self);

/*  destroy */
void KEY_TearDown(Key_t *self);

#endif // _KEY_H_
