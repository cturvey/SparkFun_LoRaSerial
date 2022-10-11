const uint16_t crc16Table[256] =
{
  0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
  0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
  0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
  0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
  0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
  0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
  0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
  0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
  0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
  0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
  0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
  0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
  0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
  0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
  0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
  0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
  0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
  0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
  0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
  0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
  0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
  0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
  0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
  0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
  0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
  0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
  0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
  0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
  0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
  0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
  0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
  0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//Point-To-Point: Bring up the link
//
//A three way handshake is used to get both systems to agree that data can flow in both
//directions.  This handshake is also used to synchronize the HOP timer.
/*
                    System A                 System B

                     RESET                     RESET
                       |                         |
             Channel 0 |                         | Channel 0
                       V                         V
           .----> P2P_NO_LINK               P2P_NO_LINK
           |           | Tx PING                 |
           | Timeout   |                         |
           |           V                         |
           | P2P_WAIT_TX_PING_DONE               |
           |           |                         |
           |           | Tx Complete - - - - - > | Rx PING
           |           |   Start Rx              |
           |           |   MAX_PACKET_SIZE       |
           |           V                         V
           `---- P2P_WAIT_ACK_1                  +<----------------------.
                       |                         | Tx PING ACK1          |
                       |                         V                       |
                       |              P2P_WAIT_TX_ACK_1_DONE             |
                       |                         |                       |
          Rx PING ACK1 | < - - - - - - - - - - - | Tx Complete           |
                       |                         |   Start Rx            |
                       |                         |   MAX_PACKET_SIZE     |
                       |                         |                       |
                       V                         V         Timeout       |
           .---------->+                   P2P_WAIT_ACK_2 -------------->+
           |   TX PING |                         |                       ^
           |      ACK2 |                         |                       |
           |           V                         |                       |
           | P2P_WAIT_TX_ACK_2_DONE              |                       |
           |           | Tx Complete - - - - - > | Rx PING ACK2          |
           | Stop      |   Start HOP timer       |   Start HOP Timer     | Stop
           | HOP       |   Start Rx              |   Start Rx            | HOP
           | Timer     |   MAX_PACKET_SIZE       |   MAX_PACKET_SIZE     | Timer
           |           |                         |                       |
           | Rx        |                         |                       |
           | PING ACK  V                         V         Rx PING       |
           `----- P2P_LINK_UP               P2P_LINK_UP -----------------’
                       |                         |
                       | Rx Data                 | Rx Data
                       |                         |
                       V                         V

  Two timers are in use:
    datagramTimer:  Set at end of transmit, measures ACK timeout
    heartbeatTimer: Set upon entry to P2P_NO_LINK, measures time to send next PING
*/
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//First packet in the three way handshake to bring up the link
void xmitDatagramP2PPing()
{
  /*
          endOfTxData ---.
                         |
                         V
      +--------+---------+----------+
      |        |         |          |
      | NET ID | Control | Trailer  |
      | 8 bits | 8 bits  | n Bytes  |
      +--------+---------+----------+
  */

  txControl.datagramType = DATAGRAM_PING;
  txControl.ackNumber = 0;
  transmitDatagram();
}

//Second packet in the three way handshake to bring up the link
void xmitDatagramP2PAck1()
{
  uint16_t channelTimerElapsed = millis() - timerStart;
  memcpy(endOfTxData, &channelTimerElapsed, sizeof(channelTimerElapsed));
  endOfTxData += sizeof(channelTimerElapsed);

  /*
                     endOfTxData ---.
                                    |
                                    V
      +--------+---------+----------+----------+
      |        |         | Channel  | Optional |
      | NET ID | Control |  Timer   | Trailer  |
      | 8 bits | 8 bits  | 2 bytes  | n Bytes  |
      +--------+---------+----------+----------+
  */

  txControl.datagramType = DATAGRAM_ACK_1;
  txControl.ackNumber = 0;
  transmitDatagram();
}

//Last packet in the three way handshake to bring up the link
void xmitDatagramP2PAck2()
{
  /*
          endOfTxData ---.
                         |
                         V
      +--------+---------+----------+
      |        |         |          |
      | NET ID | Control | Trailer  |
      | 8 bits | 8 bits  | n Bytes  |
      +--------+---------+----------+
  */

  txControl.datagramType = DATAGRAM_ACK_2;
  txControl.ackNumber = 0;
  transmitDatagram();
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Point-to-Point Data Exchange
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Send a command datagram to the remote system
void xmitDatagramP2PCommand()
{
  /*
                       endOfTxData ---.
                                      |
                                      V
      +--------+---------+---  ...  ---+----------+
      |        |         |             | Optional |
      | NET ID | Control |    Data     | Trailer  |
      | 8 bits | 8 bits  |   n bytes   | n Bytes  |
      +--------+---------+-------------+----------+
  */

  txControl.datagramType = DATAGRAM_REMOTE_COMMAND;
  txControl.ackNumber = expectedDatagramNumber;
  expectedDatagramNumber = (expectedDatagramNumber + ((datagramsExpectingAcks & (1 << txControl.datagramType)) != 0)) & 3;
  transmitDatagram();
}

//Send a command response datagram to the remote system
void xmitDatagramP2PCommandResponse()
{
  /*
                       endOfTxData ---.
                                      |
                                      V
      +--------+---------+---  ...  ---+----------+
      |        |         |             | Optional |
      | NET ID | Control |    Data     | Trailer  |
      | 8 bits | 8 bits  |   n bytes   | n Bytes  |
      +--------+---------+-------------+----------+
  */

  txControl.datagramType = DATAGRAM_REMOTE_COMMAND_RESPONSE;
  txControl.ackNumber = expectedDatagramNumber;
  expectedDatagramNumber = (expectedDatagramNumber + ((datagramsExpectingAcks & (1 << txControl.datagramType)) != 0)) & 3;
  transmitDatagram();
}

//Send a data datagram to the remote system
void xmitDatagramP2PData()
{
  /*
                       endOfTxData ---.
                                      |
                                      V
      +--------+---------+---  ...  ---+----------+
      |        |         |             | Optional |
      | NET ID | Control |    Data     | Trailer  |
      | 8 bits | 8 bits  |   n bytes   | n Bytes  |
      +--------+---------+-------------+----------+
  */

  txControl.datagramType = DATAGRAM_DATA;
  txControl.ackNumber = expectedDatagramNumber;
  expectedDatagramNumber = (expectedDatagramNumber + ((datagramsExpectingAcks & (1 << txControl.datagramType)) != 0)) & 3;
  transmitDatagram();
}

//Heartbeat packet to keep the link up
void xmitDatagramP2PHeartbeat()
{
  /*
          endOfTxData ---.
                         |
                         V
      +--------+---------+----------+
      |        |         | Optional |
      | NET ID | Control | Trailer  |
      | 8 bits | 8 bits  | n Bytes  |
      +--------+---------+----------+
  */

  txControl.datagramType = DATAGRAM_HEARTBEAT;
  txControl.ackNumber = expectedDatagramNumber;
  expectedDatagramNumber = (expectedDatagramNumber + ((datagramsExpectingAcks & (1 << txControl.datagramType)) != 0)) & 3;
  transmitDatagram();
}

//Create short packet of 2 control bytes - do not expect ack
void xmitDatagramP2PAck()
{
  uint16_t channelTimerElapsed = millis() - timerStart;
  memcpy(endOfTxData, &channelTimerElapsed, sizeof(channelTimerElapsed));
  endOfTxData += sizeof(channelTimerElapsed);

  /*
                     endOfTxData ---.
                                    |
                                    V
      +--------+---------+----------+----------+
      |        |         | Channel  | Optional |
      | NET ID | Control |  Timer   | Trailer  |
      | 8 bits | 8 bits  | 2 bytes  | n Bytes  |
      +--------+---------+----------+----------+
  */

  txControl.datagramType = DATAGRAM_DATA_ACK;
  txControl.ackNumber = expectedAckNumber;
  expectedAckNumber = (expectedAckNumber + 1) & 3;
  transmitDatagram();
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Multi-Point Data Exchange
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Send a data datagram to the remote system
void xmitDatagramMpDatagram()
{
  /*
                          endOfTxData ---.
                                         |
                                         V
      +----------+---------+---  ...  ---+----------+
      | Optional |         |             | Optional |
      |  NET ID  | Control |    Data     | Trailer  |
      |  8 bits  | 8 bits  |   n bytes   | n Bytes  |
      +----------+---------+-------------+----------+
  */

  txControl.datagramType = DATAGRAM_DATAGRAM;
  txControl.ackNumber = 0;
  transmitDatagram();
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//Datagram reception
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Determine the type of datagram received
PacketType rcvDatagram()
{
  PacketType datagramType;
  uint8_t receivedNetID;
  CONTROL_U8 rxControl;

  //Get the received datagram
  radio.readData(incomingBuffer, MAX_PACKET_SIZE);
  rxDataBytes = radio.getPacketLength();
  rxData = incomingBuffer;

  /*
      |<---------------------- rxDataBytes ---------------------->|
      |                                                           |
      +----------+----------+------------+---  ...  ---+----------+
      | Optional |          |  Optional  |             | Optional |
      |  NET ID  | Control  | SF6 Length |    Data     | Trailer  |
      |  8 bits  |  8 bits  |   8 bits   |   n bytes   | n Bytes  |
      +----------+----------+------------+-------------+----------+
      ^
      |
      '---- rxData
  */

  //Display the received data bytes
  if (settings.printRfData || settings.debugReceive)
  {
    systemPrintln("----------");
    systemPrintTimestamp();
    systemPrint("RX: ");
    systemPrint((settings.dataScrambling || settings.encryptData) ? "Encrypted " : "Unencrypted ");
    systemPrint("Frame ");
    systemPrint(rxDataBytes);
    systemPrint(" (0x");
    systemPrint(rxDataBytes, HEX);
    systemPrintln(") bytes");
    petWDT();
    if (settings.printRfData && rxDataBytes)
      dumpBuffer(incomingBuffer, rxDataBytes);
  }

  if (settings.dataScrambling == true)
    radioComputeWhitening(incomingBuffer, rxDataBytes);

  if (settings.encryptData == true)
    decryptBuffer(incomingBuffer, rxDataBytes);

  //Display the received data bytes
  if ((settings.dataScrambling || settings.encryptData)
    && (settings.printRfData || settings.debugReceive))
  {
    systemPrintTimestamp();
    systemPrint("RX: Unencrypted Frame ");
    systemPrint(rxDataBytes);
    systemPrint(" (0x");
    systemPrint(rxDataBytes, HEX);
    systemPrintln(") bytes");
    petWDT();
    if (settings.printRfData && rxDataBytes)
      dumpBuffer(incomingBuffer, rxDataBytes);
  }

  //All packets must include the 2-byte control header
  if (rxDataBytes < minDatagramSize)
  {
    //Display the packet contents
    if (settings.printPktData || settings.debugReceive)
    {
      systemPrintTimestamp();
      systemPrint("RX: Bad Frame ");
      systemPrint(rxDataBytes);
      systemPrint(" (0x");
      systemPrint(rxDataBytes, HEX);
      systemPrintln(") bytes");
      petWDT();
      if (settings.printRfData && rxDataBytes)
        dumpBuffer(incomingBuffer, rxDataBytes);
    }
    return (PACKET_BAD);
  }

  /*
      |<---------------------- rxDataBytes ---------------------->|
      |                                                           |
      +----------+----------+------------+---  ...  ---+----------+
      | Optional |          |  Optional  |             | Optional |
      |  NET ID  | Control  | SF6 Length |    Data     | Trailer  |
      |  8 bits  |  8 bits  |   8 bits   |   n bytes   | n Bytes  |
      +----------+----------+------------+-------------+----------+
      ^
      |
      '---- rxData
  */

  //Verify the netID if necessary
  if (settings.pointToPoint || settings.verifyRxNetID)
  {
    receivedNetID = *rxData++;
    if (settings.debugReceive)
    {
      systemPrintTimestamp();
      systemPrint("RX: NetID ");
      systemPrint(receivedNetID);
      systemPrint(" (0x");
      systemPrint(receivedNetID, HEX);
      systemPrint(")");
      if (receivedNetID != settings.netID)
      {
        systemPrint(" expecting ");
        systemPrintln(settings.netID);
        petWDT();
        if (settings.printPktData && rxDataBytes)
          dumpBuffer(incomingBuffer, rxDataBytes);
        return (PACKET_NETID_MISMATCH);
      }
      systemPrintln();
    }
  }

  //Process the trailer
  petWDT();
  if (settings.enableCRC16)
  {
    uint16_t crc;
    uint8_t * data;

    //Compute the CRC-16 value
    crc = 0xffff;
    for (data = incomingBuffer; data < &incomingBuffer[rxDataBytes - 2]; data++)
      crc = crc16Table[*data ^ (uint8_t)(crc >> (16 - 8))] ^ (crc << 8);
    if ((incomingBuffer[rxDataBytes - 2] != (crc >> 8))
      && (incomingBuffer[rxDataBytes - 1] != (crc & 0xff)))
    {
      //Display the packet contents
      if (settings.printPktData || settings.debugReceive)
      {
        systemPrintTimestamp();
        systemPrint("RX: Bad CRC-16, received 0x");
        systemPrint(incomingBuffer[rxDataBytes - 2], HEX);
        systemPrint(incomingBuffer[rxDataBytes - 1], HEX);
        systemPrint(" expected 0x");
        systemPrintln(crc, HEX);
        petWDT();
        if (settings.printRfData && rxDataBytes)
            dumpBuffer(incomingBuffer, rxDataBytes);
      }
      return (PACKET_BAD);
    }
  }

  /*
      |<---------------------- rxDataBytes ---------------------->|
      |                                                           |
      +----------+----------+------------+---  ...  ---+----------+
      | Optional |          |  Optional  |             | Optional |
      |  NET ID  | Control  | SF6 Length |    Data     | Trailer  |
      |  8 bits  |  8 bits  |   8 bits   |   n bytes   | n Bytes  |
      +----------+----------+------------+-------------+----------+
                 ^
                 |
                 '---- rxData
  */

  //Get the control byte
  rxControl = *((CONTROL_U8 *)rxData++);
  datagramType = rxControl.datagramType;
  uint8_t packetNumber = rxControl.ackNumber;
  if (settings.debugReceive)
    printControl(*((uint8_t *)&rxControl));
  if (datagramType >= MAX_DATAGRAM_TYPE)
    return (PACKET_BAD);

  //Display the CRC
  if (settings.enableCRC16 && (settings.printPktData || settings.debugReceive))
  {
    systemPrintTimestamp();
    systemPrint("    CRC-16: 0x");
    systemPrint(incomingBuffer[rxDataBytes - 2], HEX);
    systemPrintln(incomingBuffer[rxDataBytes - 1], HEX);
  }

  /*
      |<---------------------- rxDataBytes ---------------------->|
      |                                                           |
      +----------+----------+------------+---  ...  ---+----------+
      | Optional |          |  Optional  |             | Optional |
      |  NET ID  | Control  | SF6 Length |    Data     | Trailer  |
      |  8 bits  |  8 bits  |   8 bits   |   n bytes   | n Bytes  |
      +----------+----------+------------+-------------+----------+
                            ^
                            |
                            '---- rxData
  */

  //Get the spread factor 6 length
  if (datagramType == DATAGRAM_SF6_DATA)
  {
    if (rxDataBytes >= (*rxData + minDatagramSize))
      rxDataBytes = *rxData++;
    else
    {
      if (settings.debugReceive)
      {
        systemPrintTimestamp();
        systemPrint("Invalid SF6 length, received SF6 length");
        systemPrint(*rxData);
        systemPrint(" > ");
        systemPrint((int)rxDataBytes - minDatagramSize);
        systemPrintln(" received bytes");
      }
      return (PACKET_BAD);
    }
  }
  rxDataBytes -= minDatagramSize;

  //Verify the packet number last so that the expected datagram or ACK number can be updated
  if (settings.pointToPoint)
  {
    switch (datagramType)
    {
      default:
        break;

      case DATAGRAM_DATA_ACK:
        if (packetNumber != expectedAckNumber)
        {
          if (settings.debugReceive)
          {
            systemPrintTimestamp();
            systemPrint("Invalid ACK number, received ");
            systemPrint(packetNumber);
            systemPrint(" expecting ");
            systemPrintln(expectedAckNumber);
          }
          return (PACKET_BAD);
        }

        //Increment the expected ACK number
        expectedAckNumber = (expectedAckNumber + 1) & 3;
        break;

      case DATAGRAM_DATA:
      case DATAGRAM_SF6_DATA:
      case DATAGRAM_REMOTE_COMMAND:
      case DATAGRAM_REMOTE_COMMAND_RESPONSE:
      case DATAGRAM_HEARTBEAT:
        if (packetNumber != expectedDatagramNumber)
        {
          //Determine if this is a duplicate datagram
          if (packetNumber == ((expectedDatagramNumber - 1) & 3))
          {
            linkDownTimer = millis();
            return PACKET_DUPLICATE;
          }

          //Not a duplicate
          if (settings.debugReceive)
          {
            systemPrintTimestamp();
            systemPrint("Invalid datagram number, received ");
            systemPrint(packetNumber);
            systemPrint(" expecting ");
            systemPrintln(expectedDatagramNumber);
          }
          return PACKET_BAD;
        }

        //Receive this data packet and set the next expected datagram number
        expectedDatagramNumber = (expectedDatagramNumber + 1) & 3;
        break;
    }
  }

  /*
                                         |<-- rxDataBytes -->|
                                         |                   |
      +----------+----------+------------+------  ...  ------+----------+
      | Optional |          |  Optional  |                   | Optional |
      |  NET ID  | Control  | SF6 Length |       Data        | Trailer  |
      |  8 bits  |  8 bits  |   8 bits   |      n bytes      | n Bytes  |
      +----------+----------+------------+-------------------+----------+
                                         ^
                                         |
                                         '---- rxData
  */

  //Display the packet contents
  if (settings.printPktData || settings.debugReceive)
  {
    systemPrintTimestamp();
    systemPrint("RX: Datagram ");
    systemPrint(rxDataBytes);
    systemPrint(" (0x");
    systemPrint(rxDataBytes, HEX);
    systemPrintln(") bytes");
    petWDT();
    if (settings.printPktData && rxDataBytes)
      dumpBuffer(rxData, rxDataBytes);
  }

  //Display the datagram type
  if (settings.debugDatagrams)
  {
    systemPrintTimestamp();
    systemPrint("RX: ");
    systemPrint(v2DatagramType[datagramType]);
    switch (datagramType)
    {
      default:
        systemPrintln();
        break;

      case DATAGRAM_DATA:
      case DATAGRAM_DATA_ACK:
      case DATAGRAM_SF6_DATA:
      case DATAGRAM_REMOTE_COMMAND:
      case DATAGRAM_REMOTE_COMMAND_RESPONSE:
      case DATAGRAM_HEARTBEAT:
        if (settings.pointToPoint)
        {
          systemPrint(" (ACK #");
          systemPrint(packetNumber);
          systemPrint(")");
        }
        systemPrintln();
        break;
    }
  }

  //Process the packet
  linkDownTimer = millis();
  return datagramType;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//Datagram transmission
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Push the outgoing packet to the air
void transmitDatagram()
{
  uint8_t control;
  uint8_t * header;
  uint8_t length;

  //Determine the packet size
  txDatagramSize = endOfTxData - outgoingPacket;
  length = txDatagramSize - headerBytes;

  //Process the packet
  if (settings.debugDatagrams)
  {
    systemPrintTimestamp();
    systemPrint("TX: ");
    systemPrint(v2DatagramType[txControl.datagramType]);
    switch (txControl.datagramType)
    {
      default:
        systemPrintln();
        break;

      case DATAGRAM_DATA:
      case DATAGRAM_DATA_ACK:
      case DATAGRAM_SF6_DATA:
      case DATAGRAM_REMOTE_COMMAND:
      case DATAGRAM_REMOTE_COMMAND_RESPONSE:
      case DATAGRAM_HEARTBEAT:
        if (settings.pointToPoint)
        {
          systemPrint(" (ACK #");
          systemPrint(txControl.ackNumber);
          systemPrint(")");
        }
        systemPrintln();
        break;
    }
  }

  /*
                                        endOfTxData ---.
                                                       |
                                                       V
      +----------+----------+------------+---  ...  ---+----------+
      | Optional |          |  Optional  |             | Optional |
      |  NET ID  | Control  | SF6 Length |    Data     | Trailer  |
      |  8 bits  |  8 bits  |   8 bits   |   n bytes   | n Bytes  |
      +----------+----------+------------+-------------+----------+
      |                                  |             |
      |                                  |<- Length -->|
      |<--------- txDatagramSize --------------------->|
  */

  //Display the packet contents
  if (settings.printPktData || settings.debugTransmit)
  {
    systemPrintTimestamp();
    systemPrint("TX: Datagram ");
    systemPrint(length);
    systemPrint(" (0x");
    systemPrint(length, HEX);
    systemPrintln(") bytes");
    petWDT();
    if (settings.printPktData)
      dumpBuffer(&endOfTxData[-length], length);
  }

  //Build the datagram header
  header = outgoingPacket;
  if (headerBytes && settings.debugTransmit)
  {
    systemPrintTimestamp();
    systemPrint("TX: Header");
    systemPrint(headerBytes);
    systemPrint(" (0x");
    systemPrint(headerBytes);
    systemPrintln(") bytes");
  }

  //Add the netID if necessary
  if (settings.pointToPoint || settings.verifyRxNetID)
  {
    *header++ = settings.netID;

    //Display the netID value
    if (settings.debugTransmit)
    {
      systemPrintTimestamp();
      systemPrint("    NetID: ");
      systemPrint(settings.netID);
      systemPrint(" (0x");
      systemPrint(settings.netID, HEX);
      systemPrintln(")");
      petWDT();
    }
  }

  //Add the control byte
  control = *(uint8_t *)&txControl;
  *header++ = control;

  //Display the control value
  if (settings.debugTransmit)
    printControl(control);

  //Add the spread factor 6 length is required
  if (txControl.datagramType == DATAGRAM_SF6_DATA)
  {
    *header++ = length;
    txDatagramSize = MAX_PACKET_SIZE - trailerBytes; //We're now going to transmit a full size datagram
    if (settings.debugTransmit)
    {
      systemPrintTimestamp();
      systemPrint("    SF6 Length: ");
      systemPrintln(length);
    }
  }

  /*
                                        endOfTxData ---.
                                                       |
                                                       V
      +----------+----------+------------+---  ...  ---+
      | Optional |          |  Optional  |             |
      |  NET ID  | Control  | SF6 Length |    Data     |
      |  8 bits  |  8 bits  |   8 bits   |   n bytes   |
      +----------+----------+------------+-------------+
      |                                                |
      |<--------------- txDatagramSize --------------->|
  */

  //Add the datagram trailer
  if (settings.enableCRC16)
  {
    uint16_t crc;
    uint8_t * txData;

    //Compute the CRC-16 value
    crc = 0xffff;
    for (txData = outgoingPacket; txData < endOfTxData; txData++)
      crc = crc16Table[*txData ^ (uint8_t)(crc >> (16 - 8))] ^ (crc << 8);
    *endOfTxData++ = (uint8_t)(crc >> 8);
    *endOfTxData++ = (uint8_t)(crc & 0xff);
  }
  txDatagramSize += trailerBytes;

  //Display the trailer
  if (trailerBytes && settings.debugTransmit)
  {
    systemPrintTimestamp();
    systemPrint("TX: Trailer ");
    systemPrint(trailerBytes);
    systemPrint(" (0x");
    systemPrint(trailerBytes);
    systemPrintln(") bytes");

    //Display the CRC
    if (settings.enableCRC16 && (settings.printPktData || settings.debugReceive))
    {
      systemPrintTimestamp();
      systemPrint("    CRC-16: 0x");
      systemPrint(endOfTxData[-2], HEX);
      systemPrintln(endOfTxData[-1], HEX);
    }
  }

  /*
                                                   endOfTxData ---.
                                                                  |
                                                                  V
      +----------+----------+------------+---  ...  ---+----------+
      | Optional |          |  Optional  |             | Optional |
      |  NET ID  | Control  | SF6 Length |    Data     | Trailer  |
      |  8 bits  |  8 bits  |   8 bits   |   n bytes   | n Bytes  |
      +----------+----------+------------+-------------+----------+
      |                                                           |
      |<-------------------- txDatagramSize --------------------->|
  */

  //Display the transmitted packet bytes
  if (settings.printRfData || settings.debugTransmit)
  {
    systemPrintTimestamp();
    systemPrint("TX: Unencrypted Frame ");
    systemPrint(txDatagramSize);
    systemPrint(" (0x");
    systemPrint(txDatagramSize, HEX);
    systemPrintln(") bytes");
    petWDT();
    if (settings.printRfData)
      dumpBuffer(outgoingPacket, txDatagramSize);
  }

  //Encrypt the datagram
  if (settings.encryptData == true)
    encryptBuffer(outgoingPacket, txDatagramSize);

  //Scramble the datagram
  if (settings.dataScrambling == true)
    radioComputeWhitening(outgoingPacket, txDatagramSize);

  //Display the transmitted packet bytes
  if ((settings.printRfData || settings.debugTransmit)
    && (settings.encryptData || settings.dataScrambling))
  {
    systemPrintTimestamp();
    systemPrint("TX: Encrypted Frame ");
    systemPrint(txDatagramSize);
    systemPrint(" (0x");
    systemPrint(txDatagramSize, HEX);
    systemPrintln(") bytes");
    petWDT();
    if (settings.printRfData)
      dumpBuffer(outgoingPacket, txDatagramSize);
  }

  //If we are trainsmitting at high data rates the receiver is often not ready for new data. Pause for a few ms (measured with logic analyzer).
  if (settings.airSpeed == 28800 || settings.airSpeed == 38400)
    delay(2);

  //Reset the buffer data pointer for the next transmit operation
  endOfTxData = &outgoingPacket[headerBytes];

  //Compute the time needed for this packet. Part of ACK timeout.
  datagramAirTime = calcAirTime(txDatagramSize);

  //Transmit this datagram
  packetSent = 0; //This is the first time this packet is being sent
  retransmitDatagram();
}

//Print the control byte value
void printControl(uint8_t value)
{
  CONTROL_U8 * control = (CONTROL_U8 *)&value;

  systemPrintTimestamp();
  systemPrint("    Control: 0x");
  systemPrintln(value, HEX);
  systemPrintTimestamp();
  systemPrint("        ACK # ");
  systemPrintln(value & 3);
  systemPrintTimestamp();
  systemPrint("        datagramType ");
  if (control->datagramType < MAX_DATAGRAM_TYPE)
    systemPrintln(v2DatagramType[control->datagramType]);
  else
  {
    systemPrint("Unknown ");
    systemPrintln(control->datagramType);
  }
  petWDT();
}

//The previous transmission was not received, retransmit the datagram
void retransmitDatagram()
{
  /*
      +----------+----------+------------+---  ...  ---+----------+
      | Optional |          |  Optional  |             | Optional |
      |  NET ID  | Control  | SF6 Length |    Data     | Trailer  |
      |  8 bits  |  8 bits  |   8 bits   |   n bytes   | n Bytes  |
      +----------+----------+------------+-------------+----------+
      |                                                           |
      |<-------------------- txDatagramSize --------------------->|
  */

  //Display the transmitted packet bytes
  if (packetSent && (settings.printRfData || settings.debugTransmit))
  {
    systemPrintTimestamp();
    systemPrint("TX: Retransmit ");
    systemPrint((settings.encryptData || settings.dataScrambling) ? "Encrypted " : "Unencrypted ");
    systemPrint("Frame ");
    systemPrint(txDatagramSize);
    systemPrint(" (0x");
    systemPrint(txDatagramSize, HEX);
    systemPrintln(") bytes");
    petWDT();
    if (settings.printRfData)
      dumpBuffer(outgoingPacket, txDatagramSize);
  }

  int state = radio.startTransmit(outgoingPacket, txDatagramSize);
  if (state == RADIOLIB_ERR_NONE)
  {
    packetAirTime = calcAirTime(txDatagramSize); //Calculate packet air size while we're transmitting in the background
    uint16_t responseDelay = packetAirTime / responseDelayDivisor; //Give the receiver a bit of wiggle time to respond
    if (settings.debugTransmit)
    {
      systemPrintTimestamp();
      systemPrint("TX: PacketAirTime ");
      systemPrint(packetAirTime);
      systemPrintln(" mSec");

      systemPrintTimestamp();
      systemPrint("TX: responseDelay ");
      systemPrint(responseDelay);
      systemPrintln(" mSec");
    }
    packetAirTime += responseDelay;
  }
  else if (settings.debugTransmit)
  {
    systemPrintTimestamp();
    systemPrint("TX: Transmit error, state ");
    systemPrintln(state);
  }

  datagramTimer = millis(); //Move timestamp even if error
}

void startChannelTimer()
{
  channelTimer.disableTimer();
  channelTimer.setInterval_MS(settings.maxDwellTime, channelTimerHandler);
  channelTimer.enableTimer();
  timerStart = millis(); //ISR normally takes care of this but allow for correct ACK sync before first ISR
  triggerEvent(TRIGGER_HOP_TIMER_START);
}

void stopChannelTimer()
{
  channelTimer.disableTimer();
  triggerEvent(TRIGGER_HOP_TIMER_STOP);
}

//Given the remote unit's amount of channelTimer that has elapsed,
//adjust our own channelTimer interrupt to be synchronized with the remote unit
void syncChannelTimer()
{
  triggerEvent(TRIGGER_SYNC_CHANNEL);

  uint16_t channelTimerElapsed;
  memcpy(&channelTimerElapsed, rxData, sizeof(channelTimerElapsed));
  channelTimerElapsed += ackAirTime;
  channelTimerElapsed += SYNC_PROCESSING_OVERHEAD;

  if (channelTimerElapsed > settings.maxDwellTime) channelTimerElapsed -= settings.maxDwellTime;

  partialTimer = true;
  channelTimer.disableTimer();
  channelTimer.setInterval_MS(settings.maxDwellTime - channelTimerElapsed, channelTimerHandler); //Shorten our hardware timer to match our mate's
  channelTimer.enableTimer();
}

//This function resets the heartbeat time and re-rolls the random time
//Call when something has happened (ACK received, etc) where clocks have been sync'd
void resetHeartbeat()
{
  heartbeatTimer = millis();
  heartbeatRandomTime = random(settings.heartbeatTimeout * 8 / 10, settings.heartbeatTimeout); //20-100%
}
