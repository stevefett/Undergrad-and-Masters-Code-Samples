#include <spede/stdlib.h>
#include "mailbox.h"
#include "list.h"

MailBoxPtr MailBoxCreate(int ID, int type)
{
	MailBoxPtr mbox;
	mbox = (MailBoxPtr)malloc(sizeof(MailBox));
	mbox->id = ID;
	mbox->type = type;
    mbox->messages = (EnvelopeListPtr) malloc(sizeof(EnvelopeList));
	mbox->messages->head = NULL;
	mbox->messages->tail = NULL;
	Initialize(&(mbox->receivers));
	return mbox;
}


void AddEnvelopeToMailBox(MailBoxPtr mailbox, EnvelopePtr envl){
    
    if(mailbox->messages->head == NULL){
        mailbox->messages->head = envl;
        mailbox->messages->tail = envl;
    }
    else{
        mailbox->messages->tail->next = envl;
        mailbox->messages->tail = envl;
    }
}

EnvelopePtr RemoveHeadEnvelopeFromMailBox(MailBoxPtr mailbox){
    
    EnvelopePtr removedEnvl = mailbox->messages->head;
    mailbox->messages->head = mailbox->messages->head->next;
    
    if(mailbox->messages->head == NULL){
        mailbox->messages->tail = NULL;
    }
    return removedEnvl;
}

EnvelopePtr RemoveEnvelopeFromMailBox(MailBoxPtr mailbox, EnvelopePtr envl){
    
    EnvelopePtr prev, current;
    bool found;
    
    current = mailbox->messages->head;
    found = FALSE;
    while(current != NULL && !found){
        if(current == envl){
            found = TRUE;
            if(prev != NULL){
                prev->next = current->next;
                if(mailbox->messages->tail == current){
                    mailbox->messages->tail = prev;
                }
            }
            else{
                mailbox->messages->head = current->next;
            }
        }
        else{
            prev = current;
            current = current->next;
        }
    }
    
    return current;
}

/* void MailBoxDestroy(MailBoxPtr mbox)
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
} */
