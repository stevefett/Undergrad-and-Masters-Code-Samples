#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H

#define TOP 0
#define BOTTOM 1

extern char boundedBuffer[][10];

void Producer(int delay, int spaceAvailSemID, int dataAvailSemID, int lineNum);
void Consumer(int delay, int spaceAvailSemID, int dataAvailSemID, int lineNum);
void Producer5(int ConsumerMailboxID, int P5Delay);
void Consumer5(int ConsumerMailboxID, int Delay, int ScreenLocation);

#endif
