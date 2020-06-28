#include "MQTT.h"
int analogvalue = 0;

// Create an MQTT client
MQTT client("test.mosquitto.org", 1883, callback);


// This is called when a message is received. However, we do not use this feature in
// this project so it will be left empty
void callback(char* topic, byte* payload, unsigned int length) 
{
}


// Setup the Photon
void setup() 
{
    // Connect to the server and call ourselves "photonDev"
    client.connect("photona");
    
    // Configure GPIO 0 to be an input
    pinMode(A0, INPUT);
}


// Main loop
void loop() 
{
    analogvalue = analogRead(A0);
    
 
    // Only try to send messages if we are connected
    if (client.isConnected())
    {
        
        // If the button is pressed it will be read as 0V since the button is
        // in an inverting configuation. 
        
            
            // Publish our message to the test server
            Serial.println(analogvalue);
            Spark.publish("analogvalue", PRIVATE);
            client.publish("plantademo/test", String(analogvalue));
            delay(1000);
           
            client.loop();
        // CALL THIS at the end of your loop
        
    }
    
}