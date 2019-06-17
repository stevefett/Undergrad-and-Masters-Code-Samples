#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H

extern char boundedBuffer[][10];

void Producer(int delay, int spaceAvailSemID, int dataAvailSemID, int lineNum);
void Consumer(int delay, int spaceAvailSemID, int dataAvailSemID, int lineNum);

#endif
