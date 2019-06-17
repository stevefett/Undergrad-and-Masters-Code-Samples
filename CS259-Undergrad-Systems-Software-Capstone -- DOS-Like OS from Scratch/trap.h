typedef unsigned short seg_type_t;

struct trap_frame{
	seg_type_t gs;
	seg_type_t _notgs;
	seg_type_t fs;
	seg_type_t _notfs;
	seg_type_t es;
	seg_type_t _notes;
	seg_type_t ds;
	seg_type_t _notds;
	
	unsigned int edi;
	unsigned int esi;
	unsigned int ebp;
	unsigned int esp;
	unsigned int ebx;
	unsigned int edx;
	unsigned int ecx;
	unsigned int eax;

	unsigned int trapno;
	unsigned int err;
	
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;

};
