#include <stm32f103c8t6.h>
#include <dma1.h>

unsigned short source[512];
unsigned long count = 0;

void main()
{
  *((unsigned long*)(0x40021000 + 0x18)) |= 0x04;       //bật clock cho GPIOA
  *((unsigned long*)(0x40021000 + 0x14)) |= 0x01;       //bật clock cho DMA1

  for (unsigned long i = 0; i < 512; i++)
  {
    source[i] = i;
  }
  /////  
  
  DMA1.Channel_1.CPAR = (unsigned long)&GPIOA.ODR.REG;               //source
  DMA1.Channel_1.CMAR = (unsigned long)source;                       //destiny
  DMA1.Channel_1.CNTR = 512;   //copy 1024 byte
  
  GPIOA.ODR.REG = 0xFFFF;
  DMA1.Channel_1.CCR.BITS.MEM2MEM = 1;  //thực hiện copy từ vùng nhớ ram sang vùng nhớ ram khác
  DMA1.Channel_1.CCR.BITS.MSIZE = 1;    //chuyển 1 byte 1 lần
  DMA1.Channel_1.CCR.BITS.PSIZE = 1;    //chuyển 1 byte 1 lần
  DMA1.Channel_1.CCR.BITS.MINC = 1;     //tự động tăng địa chỉ của memory (ram)
  DMA1.Channel_1.CCR.BITS.PINC = 0;     //tự động tăng địa chỉ của peri (cũng là ram)
  DMA1.Channel_1.CCR.BITS.CIRC = 0;     //không lặp
  DMA1.Channel_1.CCR.BITS.DIR  = 1;      //copy từ PER đến mem
  DMA1.Channel_1.CCR.BITS.TEIE = 0;     //tắt ngắt
  DMA1.Channel_1.CCR.BITS.HTIE = 0;     //...
  DMA1.Channel_1.CCR.BITS.TCIE = 0;     //...
  DMA1.Channel_1.CCR.BITS.EN = 1;
  
  while (DMA1.Channel_1.CNTR)
    count++;
  while (1)
  {
    
  }
}



