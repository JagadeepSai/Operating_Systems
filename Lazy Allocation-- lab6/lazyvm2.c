#include "types.h"
#include "stat.h"
#include "user.h"

#define ARRAY_SIZE 2048
int buf[ARRAY_SIZE];

#define EXTRA_SPACE 8182
#define PAGE_GRANUALITY 4096
#define KERNBASE 0x80000000  
#define PHYSTOP 0xE000000 

long long int max_space =  4294967295;


#define EXTRA_SPACE 8182

int getpusz()
{
	
	/* todo */
	long long int va = 0;
	uint pa;
	int s_count = 0;
	int flags;
	while(va < KERNBASE)
	{	
		long long int val = (int) get_va_to_pa(va, &pa, &flags);
		if(val != 0){
			s_count+= PAGE_GRANUALITY;
		}
		//else { return s_count; }
		//printf(1,"%d\n",s_count);
		//printf(1,"%d\n",val);
		//printf(1,"VA: 0x%x   PA: 0x%x, %d, %d\n", va, pa,val,s_count);

		va += PAGE_GRANUALITY;
	}

	return s_count;
}


void print_status()
{
	int vp;
	int pp;
	int sz;

	sz = getpsz();
	vp = sz / 4096;
	if((sz % 4096) != 0)
		vp += 1;
	pp = getpusz() / 4096;

	printf(1, "sz: %d, vp: %d, pp: %d\n", sz, vp, pp);
}


int
main(int argc, char *argv[])
{	
	buf[ARRAY_SIZE-1] = 1234;

	print_status();

	int * ptr = (int *)&buf[ARRAY_SIZE-1];
	printf(1, "addr: %d, value: %d\n", ((int)ptr), *ptr);

	sbrk(EXTRA_SPACE);

	print_status();

	ptr = (int *)20484;
	printf(1, "addr: %d, value: %d\n", ((int)ptr), *ptr);

	print_status();

	ptr = (int *)28668;
	printf(1, "addr: %d\n", ((int)ptr));
	printf(1, "value: %d\n", *ptr);

	print_status();

	ptr = (int *)28676;
	printf(1, "addr: %d\n", ((int)ptr));
	printf(1, "value: %d\n", *ptr);

	print_status();
	
	exit();
}