#include "types.h"
#include "stat.h"
#include "user.h"

char b[1024];
//#define ARRAY_SIZE 10
#define PAGE_GRANUALITY 4096
#define KERNBASE 0x80000000  
#define PHYSTOP 0xE000000 

long long int max_space =  4294967295;
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
int getpksz()
{
	/* todo */
	long long int va = KERNBASE;
	//long long int end = (int)KERNBASE + (int)PHYSTOP;
	uint pa;
	int s_count = 0;
	int flags;
	while(va<=max_space)
	{	
		long long int val = (int) get_va_to_pa(va, &pa, &flags);
		if(val != 0){
			s_count+= PAGE_GRANUALITY;
		}
		//printf(1,"%d\n",val);
		//printf(1,"VA: 0x%x   PA: 0x%x, %d, %d\n", va, pa,val,s_count);
		//else { return s_count; }

		va += PAGE_GRANUALITY;
	}

	return s_count;
	// return 1;

}

int
main(int argc, char *argv[])
{
	char *buf;

	printf(1, "\ngetpsz: %d bytes \n", getpsz());
	printf(1,"getpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());


	buf=sbrk(4096);
	buf[0]='\0';
	printf(1, "\ngetpsz: %d bytes \n", getpsz());
	printf(1,"getpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());

	
	buf=sbrk(4096*7);
	printf(1, "\ngetpsz: %d bytes \n", getpsz());
	printf(1,"getpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());

	buf=sbrk(1);
	printf(1, "\ngetpsz: %d bytes \n", getpsz());
	printf(1,"getpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());

	buf=sbrk(2);
	printf(1, "\ngetpsz: %d bytes \n", getpsz());
	printf(1,"getpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());


	exit();
}