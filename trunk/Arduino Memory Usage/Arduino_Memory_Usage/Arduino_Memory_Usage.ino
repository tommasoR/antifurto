//************************************************************************
//*	http://www.nongnu.org/avr-libc/user-manual/malloc.html
//*	thanks to John O for the pointer to this info and the insperation to do it
void	Ram_TableDisplay(void) 
{
char stack = 1;
extern char *__data_start;
extern char *__data_end;

extern char *__bss_start;
extern char *__bss_end;
//extern char *__brkval;
extern char *__heap_start;
extern char *__heap_end;
//extern char *__malloc_heap_end;
//extern size_t __malloc_margin;


	int	data_size	=	(int)&__data_end - (int)&__data_start;
	int	bss_size	=	(int)&__bss_end - (int)&__data_end;
	int	heap_end	=	(int)&stack - (int)&__malloc_margin;
//	int	heap_size	=	(int)__brkval - (int)&__bss_end;
	int	heap_size	=	heap_end - (int)&__bss_end;
	int	stack_size	=	RAMEND - (int)&stack + 1;
	int	available	=	(RAMEND - (int)&__data_start + 1);
	
	available	-=	data_size + bss_size + heap_size + stack_size;

	Serial.print("+----------------+  __data_start  =");	Serial.println((int)&__data_start);
	Serial.print("+      data      +");						Serial.println();
	Serial.print("+    variables   +  data_size     =");	Serial.println(data_size);
	Serial.print("+                +");						Serial.println();
	Serial.print("+----------------+  __data_end    =");	Serial.println((int)&__data_end);
	Serial.print("+----------------+  __bss_start   =");	Serial.println((int)&__bss_start);
	Serial.print("+       bss      +");						Serial.println();
	Serial.print("+    variables   +  bss_size      =");	Serial.println(bss_size);
	Serial.print("+                +");						Serial.println();
	Serial.print("+----------------+  __bss_end     =");	Serial.println((int)&__bss_end);
	Serial.print("+----------------+  __heap_start  =");	Serial.println((int)&__heap_start);
	Serial.print("+                +");						Serial.println();
	Serial.print("+       heap     +  heap_size     =");	Serial.println(heap_size);
	Serial.print("+                +");						Serial.println();
	Serial.print("+----------------+  heap_end      =");	Serial.println(heap_end);
	Serial.print("+----------------+  Current STACK =");	Serial.println((int)&stack);
	Serial.print("+                +");						Serial.println();
	Serial.print("+      stack     +  stack_size    =");	Serial.println(stack_size);
	Serial.print("+                +");						Serial.println();
	Serial.print("+----------------+  RAMEND        =");	Serial.println(RAMEND);

//	Serial.print("__brkval      =");
//	Serial.println((int)__brkval);

	Serial.print("available =");
	Serial.println(available);

	Serial.println();
	Serial.println();
}

int get_free_memory()
{
extern char __bss_end;
extern char *__brkval;

  int free_memory;

  if((int)__brkval == 0)
    free_memory = ((int)&free_memory) - ((int)&__bss_end);
  else
    free_memory = ((int)&free_memory) - ((int)__brkval);

  return free_memory;
}

//************************************************************************
void setup()
{

	Serial.begin(9600);
	
	Serial.println("CPU USAGE");
	Ram_TableDisplay();
	
	Serial.println();
	Serial.print("Free memory");
	Serial.println(get_free_memory());
	
}


//************************************************************************
void loop()
{


}

