#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>

#define MAX_BUFF 256

volatile uint8_t uart_buffer[MAX_BUFF];
volatile uint16_t head = 0;
volatile uint16_t tail = 0;

void receiveByte(uint8_t byte){
  uint16_t next_head = (head+1) % MAX_BUFF;
  if(next_head != tail){
    uart_buffer[head] = byte;
    head = next_head;
  }
  else{
    printf("Buffer Overflow!! Byte lost : %u\n", (unsigned int)byte);
  }
}

bool readByte(uint8_t *byte){
  if(tail == head){
    printf("Buffer Underflow\n");
    return false;
  }
  else{
    *byte = uart_buffer[tail];
    tail = (tail+1) % MAX_BUFF;
    return true;
  }
}

int main(){
  char input[MAX_BUFF];
  printf("Receiving Byte!!\n");
  strcpy(input, "This is the test string!!");
  int i;
  for (i = 0 ; i < strlen(input) ; i++){
    receiveByte(input[i]);
  }
  printf("Reading Byte!!\n");
  uint8_t reader;
  while(readByte(&reader)){
    putchar(reader);//printf("%c", reader);
  }
  printf("\n");
  return 0;
}
