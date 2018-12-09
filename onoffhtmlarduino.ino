

#include <SPI.h> 
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address 
byte ip[] = { 10, 10, 110, 131 }; // IP address in LAN – need to change according to your Network address 
byte gateway[] = { 10, 10, 110, 1 }; // internet access via router 
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask 
EthernetServer server(80); //server port

String readString; 
#define RELAY1 7
#define RELAY2 8

void setup(){
Serial.begin(9600);
   pinMode(RELAY1, OUTPUT); 
  pinMode(RELAY2, OUTPUT);
    //start Ethernet 
    Ethernet.begin(mac, ip, gateway, subnet); 
    server.begin(); 
}

void loop(){ 
    // Create a client connection 
    EthernetClient client = server.available(); 
    if (client) { 
        while (client.connected()) { 
            if (client.available()) { 
                char c = client.read();

                //read char by char HTTP request 
                if (readString.length() < 100) {

                    //store characters to string 
                    readString += c; 
                }

                //if HTTP request has ended– 0x0D is Carriage Return \n ASCII 
                if (c == 0x0D) { 
                    client.println("HTTP/1.1 200 OK"); //send new page 
                    client.println("Content-Type: text/html"); 
                    client.println();

                    client.println("<HTML>"); 
                    client.println("<HEAD>"); 
                    client.println("<TITLE> ARDUINO ETHERNET SHIELD</TITLE>"); 
                    client.println("</HEAD>"); 
                    client.println("<BODY>"); 
                    client.println("<hr>"); 
                    client.println("<hr>"); 
                    client.println("<br>"); 
                    client.println("<H1 style=\"color:green;\">ARDUINO ETHERNET SHIELD </H1>"); 
                    client.println("<hr>"); 
                    client.println("<br>");

                    client.println("<H2><a href=\"/?FANON\"\">Turn On FAN</a><br></H2>"); 
                    client.println("<H2><a href=\"/?FANOFF\"\">Turn Off FAN</a><br></H2>");
                    client.println("<H2><a href=\"/?LIGHTON\"\">Turn On LIGHT</a><br></H2>"); 
                    client.println("<H2><a href=\"/?LIGHTOFF\"\">Turn Off LIGHT</a><br></H2>"); 
                    client.println("<H2><a href=\"/?LIGHTFANON\"\">Turn On LIGHT and Fan</a><br></H2>"); 
                    client.println("<H2><a href=\"/?LIGHTFANOFF\"\">Turn Off LIGHT and Fan</a><br></H2>"); 

                    client.println("</BODY>"); 
                    client.println("</HTML>");

                    delay(10); 
                    //stopping client 
                    client.stop();

                    // control arduino pin 
                    if(readString.indexOf("?FANON") > -1) //checks for LEDON 
                    { 
                        digitalWrite(RELAY1, 0); // set pin high 
                    } 
                    else if(readString.indexOf("?FANOFF") > -1) //checks for LEDOFF 
                        { 
                            digitalWrite(RELAY1, 1); // set pin low 
                        } 
                         else if(readString.indexOf("?LIGHTON") > -1) //checks for LEDOFF 
                        { 
                            digitalWrite(RELAY2, 0); // set pin low 
                        } 
                         else if(readString.indexOf("?LIGHTOFF") > -1) //checks for LEDOFF 
                        { 
                            digitalWrite(RELAY2, 1); // set pin low 
                        } 
                        else if(readString.indexOf("?LIGHTFANON") > -1) //checks for LEDOFF 
                        { 
                          digitalWrite(RELAY1, 0);
                            digitalWrite(RELAY2, 0); // set pin low 
                        } 
                        else if(readString.indexOf("?LIGHTFANOFF") > -1) //checks for LEDOFF 
                        { 
                          digitalWrite(RELAY1, 1);
                            digitalWrite(RELAY2, 1); // set pin low 
                        } 
                   
                    //clearing string for next read 
                    readString="";

                } 
            } 
        } 
    } 
}
