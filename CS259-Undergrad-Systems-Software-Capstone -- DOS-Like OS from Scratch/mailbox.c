#include <stdlib.h>
#include "mailbox.h"
#include "list.h"

MailBoxPtr MailBoxCreate(int ID, int type)
{
	MailBoxPtr mbox;
	mbox = (MailBoxPtr)malloc(sizeof(MailBox));
	mbox->id = ID;
	mbox->type = type;
	mbox->messages->head = (EnvelopePtr)malloc(sizeof(Envelope));
	mbox->messages->tail = (EnvelopePtr)malloc(sizeof(Envelope));
	Initialize(mbox->receivers);
	return mbox;
}


void MailBoxDestroy(MailBoxPtr mbox)
{
	PCBNodePtr node;
	PCBNodePtr temp;
	node = mbox->messages->head;
	while (node != NULL)
	{
		temp = RemoveHead(mbox->receivers);
		free(temp);
		node = node->next;
	}
}
