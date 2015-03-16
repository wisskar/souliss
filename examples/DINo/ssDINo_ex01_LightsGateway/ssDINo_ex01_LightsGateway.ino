/**************************************************************************
	Souliss - Lights
	
	It handle the four relays either via IN1 to IN4 inputs or using the
	Android interface. Connecting the relays to lights or similar electrial 
	appliace, you can get remote control of them.
		
 	Applicable for:
		- Light
		- Other ON/OFF electrical appliance
	
***************************************************************************/
#include "bconf/DINo_v2_Gateway.h"			// Load QuickCfg.h configuration parameters automatically
#include "Souliss.h"
#include "SpeakEasy.h"						// Is a library to code easy Souliss examples
#include <SPI.h>

// By default the board will get an IP address with .77 as last byte, you can change it
// in runtime using the Android application SoulissApp

#define RELAY1					0			// This is the memory slot used for the execution of the logic
#define RELAY2					1			
#define RELAY3					2			
#define RELAY4					3			

void setup()
{	
	// Init the board
	InitDINo();
	
	// Set the inputs
	SetInput1();
    SetInput2();
    SetInput3();
    SetInput4();
	
	// Set the outputs
	SetRelay1();
	SetRelay2();
	SetRelay3();
	SetRelay4();
	
	// Set and turn ON the status LED
	SetLED();
	TurnOnLED();
	
	// Define two Simple Light logics and the relays
	Set_SimpleLight(RELAY1);
	Set_SimpleLight(RELAY2);
	Set_SimpleLight(RELAY3);
	Set_SimpleLight(RELAY4);	
	
	// We don't assign a fixed IP address to the board, the board will get the base IP
	// information from the first broadcast frame sent out with the Android application.
	// By default the board will get an IP address with .77 as last byte, you can change
	// it in runtime using the Android application SoulissApp.
	SetAddressingServer();
}

void loop()
{ 
	// Here we start to play
	EXECUTEFAST() {						
		UPDATEFAST();	
		
		FAST_50ms() {	// We process the logic and relevant input and output every 50 milliseconds
		
			ReadInput1(RELAY1);									// Read inputs from IN1
			ReadInput2(RELAY2);									// Read inputs from IN2
			ReadInput3(RELAY3);									// Read inputs from IN3
			ReadInput4(RELAY4);									// Read inputs from IN4
		
			Logic_SimpleLight(RELAY1);							// Execute the logic for Relay 1
			Logic_SimpleLight(RELAY2);							// Execute the logic for Relay 2
			Logic_SimpleLight(RELAY3);							// Execute the logic for Relay 3
			Logic_SimpleLight(RELAY4);							// Execute the logic for Relay 4
			
			CntRelay1(RELAY1);									// Drive the Relay 1
			CntRelay2(RELAY2);                                  // Drive the Relay 2
			CntRelay3(RELAY3);									// Drive the Relay 3
			CntRelay4(RELAY4);                                  // Drive the Relay 4			
		} 
		
		// Here we process all communication with other nodes
		FAST_GatewayComms();	
	}
	
	EXECUTESLOW() {	
		UPDATESLOW();

		SLOW_10s() {  // Process the timer every 10 seconds  
			Timer_SimpleLight(RELAY1);
			Timer_SimpleLight(RELAY2);	
			Timer_SimpleLight(RELAY3);
			Timer_SimpleLight(RELAY4);				
		} 	  
	}
} 