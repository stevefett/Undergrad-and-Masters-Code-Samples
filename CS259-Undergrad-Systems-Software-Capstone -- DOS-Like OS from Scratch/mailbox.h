#ifndef MAILBOX_H
#define MAILBOX_H

#include "kerneldata.h"

#define UNDIRECTED 0
#define DIRECTED 1

typedef struct envelope
{
	struct envelope* next;
	int senderPID;
	int mw1;
	int mw2;
	int mw3;
	int mw4;
	int mw5;
	int mw6;
} Envelope;

typedef Envelope* EnvelopePtr;

typedef struct envelope_list
{
	Envelope* head;
	Envelope* tail;
} EnvelopeList;

typedef struct mail_box
{
	int id;
	int type;
	EnvelopeList messages;
	PCBListPtr receivers;


} MailBox;

typedef struct MailBox* MailboxPtr;

MailBoxPtr MailBoxCreate(int, int);
void MailBoxDestroy(MailBoxPtr);

#endif
