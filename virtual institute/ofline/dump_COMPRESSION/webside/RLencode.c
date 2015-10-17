#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#define RMAX 69



void   print_encoded( int ) ;

int main( int argc , char *argv[] ){
  FILE *fp;
  int r;
  //  unsigned char c ; 
  int c , tot0 = 0 , tot1 = 0  ; 
  fp=stdin;
  r = 0 ; 
  while( (c=getc(fp)) != EOF ) {
    //    printf("\n%d\n",c) ;
    if( c == '1' ) {
      print_encoded(r) ;
      r = 0 ; tot1++;
    }    else if (c=='0') {
      r++   ; tot0++;
      if(r==RMAX) {
	print_encoded(r) ;
	r=0;
      }
    } else {
      // carriage returns
    }
  }
  // clear the buffer of remaining stuff.
  if(r>0){
    fprintf(stderr,"The final run of %d 0s has been replaced by a run of %d\n",r,RMAX) ; 
    r=RMAX;
    print_encoded(r) ;
  }
  fprintf(stderr,"Shannon information content of the file is %d log(f) + %d log(1-f) = %8.3f\n",tot0,tot1, (tot0*log(0.99)+tot1*log(0.01))/log(0.5) ) ; 
  
}

void   print_encoded( int r) {
  switch(r) {
  case 0	:  printf("0000000");break;  
  case 1	:  printf("0000010");break;  
  case 2	:  printf("0000011");break;  
  case 3	:  printf("0001000");break;  
  case 4	:  printf("0001001");break;  
  case 5	:  printf("0001010");break;  
  case 6	:  printf("0001011");break;  
  case 7	:  printf("0001100");break;  
  case 8	:  printf("0001101");break;  
  case 9	:  printf("0001110");break;  
  case 10	:  printf("0001111");break;  
  case 11	:  printf("0010000");break;  
  case 12	:  printf("0010001");break;  
  case 13	:  printf("0010010");break;  
  case 14	:  printf("0010011");break;  
  case 15	:  printf("0010100");break;  
  case 16	:  printf("0010101");break;  
  case 17	:  printf("0010110");break;  
  case 18	:  printf("0010111");break;  
  case 19	:  printf("0011000");break;  
  case 20	:  printf("0011001");break;  
  case 21	:  printf("0011010");break;  
  case 22	:  printf("0011011");break;  
  case 23	:  printf("0011100");break;  
  case 24	:  printf("0011101");break;  
  case 25	:  printf("0011110");break;  
  case 26	:  printf("0011111");break;  
  case 27	:  printf("0100000");break;  
  case 28	:  printf("0100001");break;  
  case 29	:  printf("0100010");break;  
  case 30	:  printf("0100011");break;  
  case 31	:  printf("0100100");break;  
  case 32	:  printf("0100101");break;  
  case 33	:  printf("0100110");break;  
  case 34	:  printf("0100111");break;  
  case 35	:  printf("0101000");break;  
  case 36	:  printf("0101001");break;  
  case 37	:  printf("0101010");break;  
  case 38	:  printf("0101011");break;  
  case 39	:  printf("0101100");break;  
  case 40	:  printf("0101101");break;  
  case 41	:  printf("0101110");break;  
  case 42	:  printf("0101111");break;  
  case 43	:  printf("0110000");break;  
  case 44	:  printf("0110001");break;  
  case 45	:  printf("0110010");break;  
  case 46	:  printf("0110011");break;  
  case 47	:  printf("0110100");break;  
  case 48	:  printf("0110101");break;  
  case 49	:  printf("0110110");break;  
  case 50	:  printf("0110111");break;  
  case 51	:  printf("0111000");break;  
  case 52	:  printf("0111001");break;  
  case 53	:  printf("0111010");break;  
  case 54	:  printf("0111011");break;  
  case 55	:  printf("0111100");break;  
  case 56	:  printf("0111101");break;  
  case 57	:  printf("0111110");break;  
  case 58	:  printf("0111111");break;  
  case 59	:  printf("00001000");break; 
  case 60	:  printf("00001001");break; 
  case 61	:  printf("00001010");break; 
  case 62	:  printf("00001011");break; 
  case 63	:  printf("00001100");break; 
  case 64	:  printf("00001101");break; 
  case 65	:  printf("00001110");break; 
  case 66	:  printf("00001111");break; 
  case 67	:  printf("00000010");break; 
  case 68	:  printf("00000011");break; 
  case 69	:  printf("1");break;
  }


}
