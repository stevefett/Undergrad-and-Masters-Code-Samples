#ifndef TTY_DRIVER_H
#define TTY_DRIVER_H

extern int baseIO[];
extern BOOL ScreenInt[];

void PutChar(int);
void GetChar(int);

void TTYRead(int, int, int);
void TTYWrite(int, int, int);

#endif
