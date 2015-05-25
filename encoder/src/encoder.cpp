#include "encoder.h"
#include "serial_lnx.h"
	
	Encoder::Encoder(char *port, int baudRate) {
		
		serialConnection = new Tserial();
        serialConnection->connect(BOT_COM_PORT, BOT_BAUD_RATE, spNONE);
        usleep(100);
        
	}
	
	EncoderData Encoder::fetchEncoderData() {
		
		EncoderData returnValue;
		char input = ' ';
		
		returnValue.leftCount = 0;
		returnValue.rightCount = 0;
		int checker=0;
		ROS_INFO("inside fetch\n");

        input = serialConnection->getChar();
        ROS_INFO("char : %c\n",input);
        if(input==108)
        {ROS_INFO("inside l\n");
		do {
		     
			input = serialConnection->getChar();
			ROS_INFO("char : %c\n",input);
		      
		      if(input==45)
			{
			   checker=1;
			}
			
			else if ( (input < 58 && input > 47) ) 
			{
				returnValue.leftCount *= 10;
				returnValue.leftCount += input - 48;
				ROS_INFO("inside left\n");
			}
		      
		} while (input != ' ');
	
		    
		if(checker==1)
		returnValue.leftCount=(0 - returnValue.leftCount ) ;

		checker=0;
		}
		if(input==' ')
		{input = serialConnection->getChar();
		ROS_INFO("char : %c\n",input);}
		if(input==114)
        {
		do {
		     
			input = serialConnection->getChar();
			ROS_INFO("char : %c\n",input);
		      
		      if(input==45)
			{
			   checker=1;
			}
			
			else if ( (input < 58 && input > 47) ) 
			{
				returnValue.rightCount *= 10;
				returnValue.rightCount += input - 48;
				ROS_INFO("inside right\n");
				
			}
		      
		} while (input != ' ');
	

		if(checker==1)
		returnValue.rightCount=(0 - returnValue.rightCount ) ;
		}
		
		return returnValue;

		
	}
	

