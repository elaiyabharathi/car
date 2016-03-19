/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 *
 * This file is part of XBee-Arduino.
 *
 * XBee-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XBee-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <XBee.h>

/*
This example is for Series 2 XBee
 Sends a ZB TX request with the value of analogRead(pin5) and checks the status response for success
*/

// create the XBee object
XBee xbee = XBee();

//uint8_t payload[] = { 0, 0 };
char* payload = "hello";
// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x408bacd8);
ZBTxRequest zbTx = ZBTxRequest(addr64, (uint8_t *)payload, strlen(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();


//response object
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
ZBRxResponse rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();


void setup() {
  Serial.begin(115200);
  Serial3.begin(9600);
  xbee.setSerial(Serial3);
}

void loop() {   
  // break down 10-bit reading into two bytes and place in payload
  

  xbee.send(zbTx);

  
  // after sending a tx request, we expect a status response
  // wait up to half second for the status response
  if (xbee.readPacket(500)) {
    // got a response!

    // should be a znet tx status            	
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);

      // get the delivery status, the fifth byte
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        // success.  time to celebrate
        Serial.print("success\n");
      } else {
        // the remote XBee did not receive our packet. is it powered on?
        Serial.print("Failed");
      }
    }
  } else if (xbee.getResponse().isError()) {
    //nss.print("Error reading packet.  Error code: ");  
    //nss.println(xbee.getResponse().getErrorCode());
  } else {
    // local XBee did not provide a timely TX Status Response -- should not happen
    Serial.print("Totally failed");    
  }

  delay(1000);

  //reading a packet.......
  xbee.readPacket();
    
    if (xbee.getResponse().isAvailable()) {
      // got something
      //Serial.print("aleast got something");
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        // got a zb rx packet
        //Serial.print("ZB_RX_RESPONSE");        
        // now fill our zb rx class
        xbee.getResponse().getZBRxResponse(rx);
            
        if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) {
            // the sender got an ACK
            Serial.print("sender got ack\n");
        } else {
            // we got it (obviously) but sender didn't get an ACK
            Serial.print("Sender didn't get ack");
        }
        // set dataLed PWM to value of the first byte in the data
//        Serial.print(rx.getFrameData()[0]);
//        Serial.print("rx length\n");
//        Serial.print(rx.getDataLength());
//        Serial.print("rx 0\n");
//        Serial.print(rx.getData(0));
//        Serial.print("rx 1\n");
//        Serial.print(rx.getData(1));
//        Serial.print("rx 2\n");
//        Serial.print(rx.getData(2));
//        Serial.print("rx 3\n");
//        Serial.print(rx.getData(3));
        
         Serial.println();
                for (int i= 0; i < rx.getDataLength(); i++){
                  Serial.write(' ');
                  if (iscntrl(rx.getData()[i]))
                    Serial.write(' ');
                  else
                    Serial.write(rx.getData()[i]);
                  Serial.write(' ');
                }
        
      } else if (xbee.getResponse().getApiId() == MODEM_STATUS_RESPONSE) {
        xbee.getResponse().getModemStatusResponse(msr);
        // the local XBee sends this response on certain events, like association/dissociation
        
        if (msr.getStatus() == ASSOCIATED) {
          // yay this is great.  flash led
          Serial.print("associated");
        } else if (msr.getStatus() == DISASSOCIATED) {
          // this is awful.. flash led to show our discontent
          Serial.print("disassociated");
        } else {
          // another status
          Serial.print("other");
        }
      } else {
        // not something we were expecting
        Serial.print("something's wrong");    
      }
    } else if (xbee.getResponse().isError()) {
      Serial.print("something is wrong");
      //nss.print("Error reading packet.  Error code: ");  
      //nss.println(xbee.getResponse().getErrorCode());
    }
}

