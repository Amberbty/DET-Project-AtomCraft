************************************************************************************
********** Design for Emerging Technologies VT24 - Stockholm University ************
************************************************************************************
********************************** Server Setup ************************************
************************************************************************************
** Step 1 - Make sure you have Python 3 installed in your machine (Not python2!)  **
** (Tip: you can check if you have python on your system by running "py" or "py3" **
**  and checking the version)						          **
** Step 2 - Make sure "pip" is recognized if your system			  **
** Step 3 - Install the "websocket" python module on your system by running:      **
**									          **
**			    "pip install websockets"			       	  **
** 									       	  **
** (If that doesn't work try "py -m pip install websockets" or 		       	  **
**  "python -m pip install websockets")					       	  **
**									       	  **
** Step 4 - Run the Server File on your machine by opening the terminal on the    **
** right directory and running: 					 	  **
**									       	  **
**				"py wbserver.py"			       	  **
** 									       	  **
** If you performed the correct steps above your WebSocket Server should be       **
** running and you should see the following message on the terminal:	       	  **
**									       	  **
**		  "Server listening on Port " + YOUR PORT NUMBER	       	  **
**									       	  **
** IMPORTANT: Make sure no one else is using the same port as you or your project **
** will not work. Communicate with your colleagues should you face this issue.    **
************************************************************************************
********************************** ESP32 Setup *************************************
************************************************************************************
** Step 1 - Make sure you have the ArduinoIDE (or equivalent installed)	       	  **
** Step 2 - Install the ESP32 plugin by going to "Tools -> Board ->               **
**          Boards Manager" and then searching for "Esp32".                       **
**          Install the "Esp32 by Espresif option 	       	                  **
** Step 3 - Open the "Esp32_Client_test" file 				       	  **
** Step 4 - Install the "WebSockets2_Generic" library and all it's dependencies   **
**	    (To do so go to "Tools -> Manage Libraries" and search for it)        **
** Step 5 - Check if the network settings and IP address and correct on 	  **
**	    the "defines.h" file (ssid, password, server_host, server_port)       **
** Step 6 - Select the correct board and upload the code			  **
** Step 7 - Navigate to "Serial Monitor" (it's on the right corner of the Arduino **
**	    IDE), and change it to "115200 baud"				  **
**										  **
** If you performed the correct steps above your ESP32 should say something like: **
**									      	  **
**		"Connected! Hello to Server from + Your Board Name"	       	  **
**									       	  **
** While your server should say:						  **
**									       	  **
**	"A client just connected. Received message from client:" + Message     	  **
**									       	  **
************************************************************************************
*************** Made by António Pinheiro Braga and Jordi Solsona *******************
************************************************************************************