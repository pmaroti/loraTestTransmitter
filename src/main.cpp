///
///                 Arduino      SX1278_Lora
///                 GND----------GND   (ground in)
///                 3V3----------3.3V  (3.3V in)
/// interrupt 0 pin D2-----------DIO0  (interrupt request out)
///          SS pin D10----------NSS   (CS chip select in)
///         SCK pin D13----------SCK   (SPI clock in)
///        MOSI pin D11----------MOSI  (SPI Data in)
///        MISO pin D12----------MISO  (SPI Data out)
///


#include <SPI.h>
#include <RH_RF95.h>
// Singleton instance of the radio driver
RH_RF95 SX1278;
byte counter;
char counter_string[]="Counter: 00";


void setup()
{
    Serial.begin(9600);
    while (!Serial) ; // Wait for serial port to be available
   
    if (!SX1278.init())
        Serial.println("Notice:init failed");
    Serial.println("Initialization OK");
    counter = 0;
}

void loop()
{
    Serial.print("Sending to SX1278_server");
    itoa(counter,counter_string+9,10);
    Serial.println(counter_string);
    // Send a message to SX1278_server
    SX1278.send(counter_string, sizeof(counter_string));
    Serial.println("mark0");
    SX1278.waitPacketSent();
    Serial.println("mark1");
    // Now wait for a reply
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    delay(1000);
    Serial.println("mark2");
    counter++;
}