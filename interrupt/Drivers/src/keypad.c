#include "stm32f4xx.h"
#include "gpio.h"
#include "keypad.h"

const int no_raws = 4;
const int no_cols = 3;
char rows[4]={1,2,3,4}; //fill the array
char cols[3]={5,6,7}; //fill the array

char lookupTable[4][3]={{1,2,3},{4,5,6},{7,8,9},{'*',0,'#'}};// fill the array
char lookupTable_7Seg[10][7]={{0,0,0,0,0,0,1},{1,0,0,1,1,1,1},{0,0,1,0,0,1,0},{0,0,0,0,1,1,0},{1,0,0,1,1,0,0},{0,1,0,0,1,0,0}
,{0,1,0,0,0,0,0},{0,0,0,1,1,1,1},{0,0,0,0,0,0,0},{0,0,0,0,1,0,0}};

char currentvalue;
char a ;

void KeyPad_INIT(void)
{
	 for(int i = 8; i<14; i++)
	 {
		 GPIO_Init(GPIOA,i,1,0);
	 }

	GPIO_Init(GPIOA,15,1,0);

	    // set input and ouput pins
		// get pins from raw and set it as input
	for (int i = 0; i < no_raws; i++) {
		char pin = rows[i];
		GPIO_Init (GPIOA,pin,0,0);
	}
		// get pins from cols and set it as output
	for (int j = 0; j < no_cols; j++) {
			char pin_out = cols[j];
			GPIO_Init (GPIOA,pin_out,1,0);
//			GPIO_Write(GPIOA,pin_out,0);
		}
}

void KeyPad_MANAGE(void)
{
//	nested for loop to check which button is pressed
	for (int i = 0; i < no_cols; i++) {
				char pin = cols[i];
				for(int y = 0; y<no_cols;y++)
				{
					GPIO_Write(GPIOA,cols[y],1);
				}
				GPIO_Write(GPIOA,pin,0);
				for (int j = 0; j < no_raws; j++) {
						char pin_in = rows[j];
						 a = GPIO_Read(GPIOA,pin_in);
						if(a ==0)
						{
							while(GPIO_Read(GPIOA,pin_in)==0);
							currentvalue = lookupTable[j][i];
							KeypadCallouts_KeyPressNotificaton(); //momkn hna nhot break lw mshtaghlsh
						}

					}
			}


	//if pressed wait until released then change the value;
	//call KeypadCallouts_KeyPressNotificaton
}

char KeyPad_GET_VALUE(void)
{
	return currentvalue;
}

void KeypadCallouts_KeyPressNotificaton(void)
{


	// set seven segment
	char val = KeyPad_GET_VALUE();
	switch(val){
	          case 0:
	        	    for(int i = 8; i<14; i++){
	        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg[0][i-8]);
	        	    }
//        			GPIO_Write(GPIOA,8,0);
//        		    GPIO_Write(GPIOA,9,0);
//        		    GPIO_Write(GPIOA,10,0);
//        		    GPIO_Write(GPIOA,11,0);
//        		    GPIO_Write(GPIOA,12,0);
//        		    GPIO_Write(GPIOA,13,0);
        		    GPIO_Write(GPIOA,15,1);
        		    for(int j =0 ; j<500000;j++){}// delay for some time
        		    break;
        		case 1:
        			for(int i = 8; i<14; i++){
        				        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg[1][i-8]);
        				        	    }
        		    GPIO_Write(GPIOA,15,1);
        		    for(int j =0 ; j<500000;j++){}// delay for some time
        		    break;
        		case 2:
        			for(int i = 8; i<14; i++){
        				        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg[2][i-8]);
        				        	    }
					GPIO_Write(GPIOA,15,0);

					for(int j =0 ; j<500000;j++){}// delay for some time
					break;
				case 3:
					for(int i = 8; i<14; i++){
						        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg[3][i-8]);
						        	    }
					GPIO_Write(GPIOA,15,0);

					for(int j =0 ; j<500000;j++){}// delay for some time
					break;
				case 4:
					for(int i = 8; i<14; i++){
						        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg[4][i-8]);
						        	    }
					GPIO_Write(GPIOA,15,0);

					for(int j =0 ; j<500000;j++){}// delay
					break;
				case 5:
					for(int i = 8; i<14; i++){
						        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg[5][i-8]);
						        	    }
					GPIO_Write(GPIOA,15,0);

					for(int j =0 ; j<500000;j++){}// delay
					break;
				case 6:
					for(int i = 8; i<14; i++){
						        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg[6][i-8]);
						        	    }
					GPIO_Write(GPIOA,15,0);
					for(int j =0 ; j<500000;j++){}// delay for some time
					break;
				case 7:
					for(int i = 8; i<14; i++){
						        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg[7][i-8]);
						        	    }
					GPIO_Write(GPIOA,15,1);
					for(int j =0 ; j<500000;j++){}// delay for some time
					break;
				case 8:
					for(int i = 8; i<14; i++){
						        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg[8][i-8]);
						        	    }
					GPIO_Write(GPIOA,15,0);
					for(int j =0 ; j<500000;j++){}// delay for some time
					break;
				case 9:
					for(int i = 8; i<14; i++){
						        	    	GPIO_Write(GPIOA,i,lookupTable_7Seg[9][i-8]);
						        	    }
					GPIO_Write(GPIOA,15,0);

					for(int j =0 ; j<500000;j++){}// delay for some time
					break;

	}

}

