typedef enum
{
  RADIO_RESET = 0,

  //Point-To-Point: Bring up the link
  RADIO_P2P_LINK_DOWN,
  RADIO_P2P_WAIT_TX_PING_DONE,
  RADIO_P2P_WAIT_ACK_1,
  RADIO_P2P_WAIT_TX_ACK_1_DONE,
  RADIO_P2P_WAIT_ACK_2,
  RADIO_P2P_WAIT_TX_ACK_2_DONE,

  //Point-to-Point: Link up, data exchange
  RADIO_P2P_LINK_UP,
  RADIO_P2P_LINK_UP_WAIT_ACK_DONE,
  RADIO_P2P_LINK_UP_WAIT_TX_DONE,
  RADIO_P2P_LINK_UP_WAIT_ACK,
  RADIO_P2P_LINK_UP_HB_ACK_REXMT,

  //Server-client discovery
  RADIO_DISCOVER_BEGIN,
  RADIO_DISCOVER_SCANNING,
  RADIO_DISCOVER_WAIT_TX_PING_DONE,

  //Multi-Point: Datagrams
  RADIO_MP_WAIT_TX_ACK_DONE,
  RADIO_MP_STANDBY,
  RADIO_MP_WAIT_TX_DONE,

  //Training client states
  RADIO_TRAIN_WAIT_TX_PING_DONE,
  RADIO_TRAIN_WAIT_RX_RADIO_PARAMETERS,
  RADIO_TRAIN_WAIT_TX_PARAM_ACK_DONE,

  //Training server states
  RADIO_TRAIN_WAIT_FOR_PING,
  RADIO_TRAIN_WAIT_TX_RADIO_PARAMS_DONE,

  //Virtual-Circuit states
  RADIO_VC_WAIT_TX_DONE,
  RADIO_VC_WAIT_RECEIVE,

  RADIO_MAX_STATE,
} RadioStates;

RadioStates radioState = RADIO_RESET;

#define P2P_LINK_BREAK_MULTIPLIER       3

typedef struct _RADIO_STATE_ENTRY
{
  RadioStates state;
  bool rxState;
  const char * name;
  const char * description;
} RADIO_STATE_ENTRY;

const RADIO_STATE_ENTRY radioStateTable[] =
{
  {RADIO_RESET,                          0, "RESET",                          NULL},                         // 0

  //Point-to-Point link handshake
  //    State                           RX      Name                              Description
  {RADIO_P2P_LINK_DOWN,                  1, "P2P_LINK_DOWN",                  "P2P: [No Link] Waiting for Ping"}, // 4
  {RADIO_P2P_WAIT_TX_PING_DONE,          0, "P2P_WAIT_TX_PING_DONE",          "P2P: [No Link] Wait Ping TX Done"},// 5
  {RADIO_P2P_WAIT_ACK_1,                 1, "P2P_WAIT_ACK_1",                 "P2P: [No Link] Waiting for ACK1"}, // 6
  {RADIO_P2P_WAIT_TX_ACK_1_DONE,         0, "P2P_WAIT_TX_ACK_1_DONE",         "P2P: [No Link] Wait ACK1 TX Done"},// 7
  {RADIO_P2P_WAIT_ACK_2,                 1, "P2P_WAIT_ACK_2",                 "P2P: [No Link] Waiting for ACK2"}, // 8
  {RADIO_P2P_WAIT_TX_ACK_2_DONE,         0, "P2P_WAIT_TX_ACK_2_DONE",         "P2P: [No Link] Wait ACK2 TX Done"},// 9

  //Point-to-Point, link up, data exchange
  //    State                           RX      Name                              Description
  {RADIO_P2P_LINK_UP,                    1, "P2P_LINK_UP",                    "P2P: Receiving Standby"},          //10
  {RADIO_P2P_LINK_UP_WAIT_ACK_DONE,      0, "P2P_LINK_UP_WAIT_ACK_DONE",      "P2P: Waiting ACK TX Done"},        //11
  {RADIO_P2P_LINK_UP_WAIT_TX_DONE,       0, "P2P_LINK_UP_WAIT_TX_DONE",       "P2P: Waiting TX done"},            //12
  {RADIO_P2P_LINK_UP_WAIT_ACK,           1, "P2P_LINK_UP_WAIT_ACK",           "P2P: Waiting for ACK"},            //13
  {RADIO_P2P_LINK_UP_HB_ACK_REXMT,       0, "P2P_LINK_UP_HB_ACK_REXMT",       "P2P: Heartbeat ACK ReXmt"},        //14

  //Server-client discovery
  //    State                           RX      Name                              Description
  {RADIO_DISCOVER_BEGIN,                 0, "DISCOVER_BEGIN",                 "Disc: Setup for scanning"},        //15
  {RADIO_DISCOVER_SCANNING,              0, "DISCOVER_SCANNING",              "Disc: Scanning for servers"},      //16
  {RADIO_DISCOVER_WAIT_TX_PING_DONE,     0, "DISCOVER_WAIT_TX_PING_DONE",     "Disc: Wait for ping to xmit"},     //17

  //Multi-Point data exchange
  //    State                           RX      Name                              Description
  {RADIO_MP_WAIT_TX_ACK_DONE,            0, "MP_WAIT_TX_ACK_DONE",            "MP: Wait for ACK to xmit"},        //18
  {RADIO_MP_STANDBY,                     1, "MP_STANDBY",                     "MP: Wait for TX or RX"},           //19
  {RADIO_MP_WAIT_TX_DONE,                0, "MP_WAIT_TX_DONE",                "MP: Waiting for TX done"},         //20

  //Training client states
  //    State                           RX      Name                              Description
  {RADIO_TRAIN_WAIT_TX_PING_DONE,        0, "TRAIN_WAIT_TX_PING_DONE",        "Train: Wait TX training PING done"},  //21
  {RADIO_TRAIN_WAIT_RX_RADIO_PARAMETERS, 1, "TRAIN_WAIT_RX_RADIO_PARAMETERS", "Train: Wait for radio parameters"},   //22
  {RADIO_TRAIN_WAIT_TX_PARAM_ACK_DONE,   0, "TRAIN_WAIT_TX_PARAM_ACK_DONE",   "Train: Wait for TX param ACK done"},  //23

  //Training server states
  //    State                           RX      Name                              Description
  {RADIO_TRAIN_WAIT_FOR_PING,            1, "TRAIN_WAIT_FOR_PING",            "Train: Wait for training PING"},      //24
  {RADIO_TRAIN_WAIT_TX_RADIO_PARAMS_DONE,0, "TRAIN_WAIT_TX_RADIO_PARAMS_DONE","Train: Wait for TX params done"},     //25

  //Virtual circuit states
  //    State                           RX      Name                              Description
  {RADIO_VC_WAIT_TX_DONE,                0, "VC_WAIT_TX_DONE",                "VC: Wait for TX done"},            //27
  {RADIO_VC_WAIT_RECEIVE,                1, "VC_WAIT_RECEIVE",                "VC: Wait for receive"},            //28
};

//Possible types of packets received
typedef enum
{
  //Packet types must start at zero
  //Point-to-Point training
  DATAGRAM_P2P_TRAINING_PING = 0,   // 0
  DATAGRAM_P2P_TRAINING_PARAMS,     // 1

  //Link establishment handshake
  DATAGRAM_PING,                    // 2
  DATAGRAM_ACK_1,                   // 3
  DATAGRAM_ACK_2,                   // 4

  //Point-to-Point data exchange
  DATAGRAM_DATA,                    // 5
  DATAGRAM_DATA_ACK,                // 6
  DATAGRAM_HEARTBEAT,               // 7
  DATAGRAM_REMOTE_COMMAND,          // 8
  DATAGRAM_REMOTE_COMMAND_RESPONSE, // 9

  //Multi-Point data exchange
  DATAGRAM_DATAGRAM,                //10

  //Multi-Point training exchange
  DATAGRAM_TRAINING_PING,           //11
  DATAGRAM_TRAINING_PARAMS,         //12
  DATAGRAM_TRAINING_ACK,            //13

  //Virtual-Circuit (VC) exchange
  DATAGRAM_VC_HEARTBEAT,            //14

  //Add new datagram types before this line
  MAX_DATAGRAM_TYPE,

  //Add new protocol datagrams above this line

  //Common datagram types
  DATAGRAM_BAD,
  DATAGRAM_CRC_ERROR,
  DATAGRAM_NETID_MISMATCH,
  DATAGRAM_DUPLICATE,
  DATAGRAM_NOT_MINE,
} PacketType;

const char * const radioDatagramType[] =
{ //       0                    1
  "P2P_TRAINING_PING", "P2P_TRAINING_PARAMS",
  // 2       3        4
  "PING", "ACK-1", "ACK-2",
  // 5        6           7            8           9
  "DATA", "DATA-ACK", "HEARTBEAT", "RMT-CMD", "RMT_RESP",
  //  10
  "DATAGRAM",
  //     11                12               13
  "TRAINING_PING", "TRAINING_PARAMS", "TRAINING_ACK",
  //    14
  "VC_HEARTBEAT",
};

typedef struct _VIRTUAL_CIRCUIT
{
  uint8_t uniqueId[UNIQUE_ID_BYTES];
  unsigned long firstHeartbeatMillis; //Time VC link came up
  unsigned long lastTrafficMillis; //Last time a frame was received
  unsigned long lastPingMillis; //Last time a ping was sent or ACK received

  //Link quality metrics
  uint32_t framesSent;        //myVc --> VC, Total number of frames sent
  uint32_t framesReceived;    //myVc <-- VC, Total number of frames received
  uint32_t messagesSent;      //myVc --> VC, Total number of messages sent
  uint32_t messagesReceived;  //myVc <-- VC, Total number of messages received
  uint32_t badLength;         //myVc <-- VC, Total number of bad lengths received
  uint32_t linkFailures;      //myVc <-> VC, Total number of link failures

  //Link management
  bool valid;                 //Unique ID is valid
  uint8_t vcState;            //State of VC

  /* ACK number management

              System A                              System B
             (in destVc)                           (in srcVc)

             txAckNumber
                  |
                  V
            Tx DATA Frame -----------------------> Rx DATA Frame
                                                        |
                                                        V
                                                    AckNumber == rmtTxAckNumber
                                                        |
                                                        | yes
                                                        V
                                                   rxAckNumber = rmtTxAckNumber++
                                                        |
                                                        V
          Rx DATA_Ack Frame <--------------------- Tx DATA_ACK Frame
                  |
                  V
              ackNumber == txAckNumber
                  |
                  | yes
                  V
             txAckNumber++
  */

  uint8_t rmtTxAckNumber; //Next expected ACK # from remote system in DATA frame,
  //incremented upon match to received DATA frame ACK number,
  //indicates frame was received and processed
  //Duplicate frame if received ACK # == (rmtTxAckNumber -1)
  uint8_t rxAckNumber;    //Received ACK # of the most recent acknowledged DATA frame,
  //does not get incremented, used to ACK the data frame
  uint8_t txAckNumber;    //# of next ACK to be sent by the local system in DATA frame,
  //incremented when successfully acknowledged via DATA_ACK frame
} VIRTUAL_CIRCUIT;

#define ADD_VC_STATE_NAMES_TABLE
#include "Virtual_Circuit_Protocol.h"

//Train button states
typedef enum
{
  TRAIN_NO_PRESS = 0,
  TRAIN_PRESSED,
  TRAIN_IN_PROCESS,
} TrainStates;

enum
{ //#, Width - Computed with:
  //        triggerWidth = 25
  //        triggerUseWidthAsMultiplier = true
  //        triggerEnable = 0xffffffff

  TRIGGER_CHANNEL_TIMER_ISR, //0
  TRIGGER_RADIO_RESET,
  TRIGGER_HOP_TIMER_START,
  TRIGGER_HOP_TIMER_STOP,
  TRIGGER_HEARTBEAT,
  TRIGGER_FREQ_CHANGE,
  TRIGGER_SYNC_CHANNEL,
  TRIGGER_LINK_SEND_ACK_FOR_DATA,
  TRIGGER_LINK_SEND_ACK_FOR_DUP,
  TRIGGER_LINK_RETRANSMIT,
  TRIGGER_LINK_SEND_ACK_FOR_HEARTBEAT,
  TRIGGER_LINK_WAIT_FOR_ACK,
  TRIGGER_LINK_DATA_XMIT,
  TRIGGER_LINK_RETRANSMIT_FAIL,
  TRIGGER_LINK_REQUEST_YIELD_SENT,
  TRIGGER_LINK_REQUEST_YIELD_RECEIVED,
  TRIGGER_MP_SCAN,
  TRIGGER_MP_DATA_PACKET,
  TRIGGER_MP_PACKET_RECEIVED,
  TRIGGER_MP_SEND_ACK_FOR_PING,
  TRIGGER_TRANSMIT_CANCELED,
  TRIGGER_HANDSHAKE_ACK1_TIMEOUT,
  TRIGGER_HANDSHAKE_SEND_PING,
  TRIGGER_HANDSHAKE_SEND_PING_COMPLETE,
  TRIGGER_HANDSHAKE_SEND_ACK1_COMPLETE,
  TRIGGER_SEND_ACK1,
  TRIGGER_SEND_ACK2,
  TRIGGER_HANDSHAKE_COMPLETE,
  TRIGGER_LINK_ACK_SENT,
  TRIGGER_LINK_ACK_RECEIVED,
  TRIGGER_HANDSHAKE_ACK2_TIMEOUT,
  TRIGGER_RECEIVE_IN_PROCESS_START,
  TRIGGER_RECEIVE_IN_PROCESS_END,
  TRIGGER_LINK_HB_ACK_REXMIT,
  TRIGGER_UNKNOWN_PACKET,
  TRIGGER_LINK_SEND_ACK_FOR_REMOTE_COMMAND,
  TRIGGER_LINK_SEND_ACK_FOR_REMOTE_COMMAND_RESPONSE,
  TRIGGER_BAD_PACKET,
  TRIGGER_CRC_ERROR,
  TRIGGER_NETID_MISMATCH,
  TRIGGER_RTR_SHORT_PACKET,
  TRIGGER_RTR_255BYTE,
  TRIGGER_TRAINING_CONTROL_PACKET,
  TRIGGER_TRAINING_DATA_PACKET,
  TRIGGER_TRAINING_NO_ACK,
  TRIGGER_TRAINING_CLIENT_TX_PING_DONE,
  TRIGGER_TRAINING_CLIENT_RX_PARAMS,
  TRIGGER_TRAINING_CLIENT_TX_ACK_DONE,
  TRIGGER_TRAINING_SERVER_RX,
  TRIGGER_TRAINING_SERVER_TX_PARAMS_DONE,
  TRIGGER_TRAINING_SERVER_RX_ACK,
  TRIGGER_TRAINING_SERVER_STOPPED,
  TRIGGER_VC_TX_DONE,
  TRIGGER_VC_TX_DATA,
};

//Control where to print command output
typedef enum
{
  PRINT_TO_SERIAL = 0,
  PRINT_TO_RF,
} PrinterEndpoints;
PrinterEndpoints printerEndpoint = PRINT_TO_SERIAL;

//Select the operating mode
typedef enum
{
  MODE_MULTIPOINT = 0,
  MODE_POINT_TO_POINT,
  MODE_VIRTUAL_CIRCUIT,
} OPERATING_MODE;

typedef struct _CONTROL_U8
{
  PacketType datagramType: 4;
  uint8_t ackNumber : 2;
  uint8_t requestYield : 1;
  uint8_t filler : 1;
} CONTROL_U8;

typedef bool (* VALIDATION_ROUTINE)(void * value, uint32_t valMin, uint32_t valMax);

typedef struct _COMMAND_ENTRY
{
  char letter;
  char requireAll;
  bool forceRadioReset;
  uint32_t minValue;
  uint32_t maxValue;
  uint8_t digits;
  uint8_t type;
  VALIDATION_ROUTINE validate;
  const char * name;
  void * setting;
} COMMAND_ENTRY;

typedef enum
{
  LEDS_RSSI = 0,    //Green: RSSI, Blue: Serial TX, Yellow: Serial RX
  LEDS_RADIO_USE,   //Green1: RX, Green2: Link, Green3: RSSI, Green4: TX
                    //Blue: Bad frames, Yellow: Bad CRC
  LEDS_CYLON,       //Display the cylon pattern on the green LEDs, others off
  LEDS_ALL_OFF,     //All LEDs off
  LEDS_BLUE_ON,     //Blue: ON, other: OFF
  LEDS_YELLOW_ON,   //Yellow: ON, other: OFF
  LEDS_GREEN_1_ON,  //Green 1: ON, other: OFF
  LEDS_GREEN_2_ON,  //Green 2: ON, other: OFF
  LEDS_GREEN_3_ON,  //Green 3: ON, other: OFF
  LEDS_GREEN_4_ON,  //Green 4: ON, other: OFF

  //Add user LED types from 255 working down
} LEDS_USE_TYPE;

//These are all the settings that can be set on Serial Terminal Radio. It's recorded to NVM.
typedef struct struct_settings {
  uint16_t sizeOfSettings = 0; //sizeOfSettings **must** be the first entry and must be int
  uint16_t strIdentifier = LRS_IDENTIFIER; // strIdentifier **must** be the second entry

  uint32_t serialSpeed = 57600; //Default to 57600bps to match RTK Surveyor default firmware
  uint32_t airSpeed = 4800; //Default to ~523 bytes per second to support RTCM. Overrides spread, bandwidth, and coding
  uint8_t netID = 192; //Both radios must share a network ID
  uint8_t operatingMode = MODE_POINT_TO_POINT; //Receiving unit will check netID and ACK. If set to false, receiving unit doesn't check netID or ACK.
  bool encryptData = true; //AES encrypt each packet
  uint8_t encryptionKey[AES_KEY_BYTES] = { 0x37, 0x78, 0x21, 0x41, 0xA6, 0x65, 0x73, 0x4E, 0x44, 0x75, 0x67, 0x2A, 0xE6, 0x30, 0x83, 0x08 };
  bool dataScrambling = false; //Use IBM Data Whitening to reduce DC bias
#if defined(ENABLE_DEVELOPER)
#define TX_POWER_DB     14
#else   //ENABLE_DEVELOPER
#define TX_POWER_DB     30
#endif  //ENABLE_DEVELOPER
  uint8_t radioBroadcastPower_dbm = TX_POWER_DB; //Transmit power in dBm. Max is 30dBm (1W), min is 14dBm (25mW).
  float frequencyMin = 902.0; //MHz
  float frequencyMax = 928.0; //MHz
  uint8_t numberOfChannels = 50; //Divide the min/max freq band into this number of channels and hop between.
  bool frequencyHop = true; //Hop between frequencies to avoid dwelling on any one channel for too long
  uint16_t maxDwellTime = 400; //Max number of ms before hopping (if enabled). Useful for configuring radio to be within regulator limits (FCC = 400ms max)
  float radioBandwidth = 500.0; //kHz 125/250/500 generally. We need 500kHz for higher data.
  uint8_t radioSpreadFactor = 9; //6 to 12. Use higher factor for longer range.
  uint8_t radioCodingRate = 8; //5 to 8. Higher coding rates ensure less packets dropped.
  uint8_t radioSyncWord = 18; //18 = 0x12 is default for custom/private networks. Different sync words does *not* guarantee a remote radio will not get packet.
  uint16_t radioPreambleLength = 8; //Number of symbols. Different lengths does *not* guarantee a remote radio privacy. 8 to 11 works. 8 to 15 drops some. 8 to 20 is silent.
  uint16_t serialTimeoutBeforeSendingFrame_ms = 50; //Send partial buffer if time expires
  bool debug = false; //Print basic events: ie, radio state changes
  bool echo = false; //Print locally inputted serial
  uint16_t heartbeatTimeout = 5000; //ms before sending ping to see if link is active
  bool flowControl = false; //Enable the use of CTS/RTS flow control signals
  bool autoTuneFrequency = false; //Based on the last packets frequency error, adjust our next transaction frequency
  bool printPacketQuality = false; //Print RSSI, SNR, and freqError for received packets
  uint8_t maxResends = 0; //Attempt resends up to this number, 0 = infinite retries
  bool printFrequency = false; //Print the updated frequency
  bool debugRadio = false; //Print radio info
  bool debugStates = false; //Print state changes
  bool debugTraining = false; //Print training info
#if defined(ENABLE_DEVELOPER)
#define WAIT_SERIAL_DEFAULT     true
#else   //ENABLE_DEVELOPER
#define WAIT_SERIAL_DEFAULT     false
#endif  //ENABLE_DEVELOPER
  bool usbSerialWait = WAIT_SERIAL_DEFAULT; //Wait for USB serial initialization
  bool printRfData = false; //Print RX and TX data
  bool printPktData = false; //Print data, before encryption and after decryption
  bool verifyRxNetID = false; //Verify RX netID value when not operating in point-to-point mode
  uint8_t triggerWidth = 25; //Trigger width in microSeconds or multipler for trigger width
  bool triggerWidthIsMultiplier = true; //Use the trigger width as a multiplier
  uint32_t triggerEnable = 0; //Determine which triggers are enabled: 31 - 0
  uint32_t triggerEnable2 = 0; //Determine which triggers are enabled: 63 - 32
  bool debugReceive = false; //Print receive processing
  bool debugTransmit = false; //Print transmit processing
  bool printTxErrors = false; //Print any transmit errors
  bool printTimestamp = false; //Print a timestamp: days hours:minutes:seconds.milliseconds
  bool debugDatagrams = false; //Print the datagrams
  uint16_t overheadTime = 10; //ms added to ack and datagram times before ACK timeout occurs
  bool enableCRC16 = false; //Append CRC-16 to packet, check CRC-16 upon receive
  bool displayRealMillis = false; //true = Display the millis value without offset, false = use offset
  bool server = false; //Default to being a client, enable server for multipoint, VC and training
  uint8_t clientPingRetryInterval = 3; //Number of seconds before retransmiting the client PING
  bool copyDebug = false; //Copy the debug parameters to the training client
  bool copySerial = false; //Copy the serial parameters to the training client
  bool copyTriggers = false; //Copy the trigger parameters to the training client
  uint8_t trainingKey[AES_KEY_BYTES] = { 0x53, 0x70, 0x61, 0x72, 0x6b, 0x46, 0x75, 0x6E, 0x54, 0x72, 0x61, 0x69, 0x6e, 0x69, 0x6e, 0x67 };
  bool printLinkUpDown = false; //Print the link up and link down messages
  bool invertCts = false; //Invert the input of CTS
  bool invertRts = false; //Invert the output of RTS
  uint8_t selectLedUse = 0; //Select LED use
  uint8_t trainingTimeout = 1; //Timeout in minutes to complete the training
  bool debugSerial = false; //Debug the serial input
  bool debugSync = false; //Print clock sync processing
  bool debugNvm = false; //Debug NVM operation
  bool printAckNumbers = false; //Print the ACK numbers
  bool debugHeartbeat = false; //Print the HEARTBEAT timing values
  uint8_t framesToYield = 3; //If remote requests it, supress transmission for this number of max packet frames

  //Add new parameters immediately before this line
  //-- Add commands to set the parameters
  //-- Add parameters to routine updateRadioParameters
} Settings;
Settings settings;

//Monitor which devices on the device are on or offline.
struct struct_online {
  bool radio = false;
  bool eeprom = false;
} online;

#include <RadioLib.h> //Click here to get the library: http://librarymanager/All#RadioLib v5.5.0

typedef void (* ARCH_BEGIN_BOARD)();
typedef void (* ARCH_BEGIN_SERIAL)(uint16_t serialSpeed);
typedef void (* ARCH_BEGIN_WDT)();
typedef void (* ARCH_EEPROM_BEGIN)();
typedef void (* ARCH_EEPROM_COMMIT)();
typedef void (* ARCH_PET_WDT)();
typedef Module * (* ARCH_RADIO)();
typedef bool (* ARCH_SERIAL_AVAILABLE)();
typedef void (* ARCH_SERIAL_FLUSH)();
typedef uint8_t (* ARCH_SERIAL_READ)();
typedef void (* ARCH_SERIAL_WRITE)(uint8_t value);
typedef void (* ARCH_SYSTEM_RESET)();
typedef void (* ARCH_UNIQUE_ID)(uint8_t * unique128_BitID);

typedef struct _ARCH_TABLE
{
  ARCH_BEGIN_BOARD beginBoard;    //Initialize the board
  ARCH_BEGIN_SERIAL beginSerial;  //Finish initializing the serial port
  ARCH_BEGIN_WDT beginWDT;        //Initialize the watchdog timer
  ARCH_EEPROM_BEGIN eepromBegin;  //Start an EEPROM operation
  ARCH_EEPROM_COMMIT eepromCommit;//Done with the EEPROM operation
  ARCH_PET_WDT petWDT;            //Reset the expiration time for the WDT
  ARCH_RADIO radio;               //Initialize the radio
  ARCH_SERIAL_AVAILABLE serialAvailable;  //Determine if serial data is available
  ARCH_SERIAL_FLUSH serialFlush;  //Flush the serial port
  ARCH_SERIAL_READ serialRead;    //Read a byte from the serial port
  ARCH_SERIAL_WRITE serialWrite;  //Print the specified character
  ARCH_SYSTEM_RESET systemReset;  //Reset the system
  ARCH_UNIQUE_ID uniqueID;        //Get the 128 bit unique ID value
} ARCH_TABLE;

typedef struct _U8_TO_STRING
{
  uint8_t value;
  const char * string;
} U8_TO_STRING;

typedef struct _I16_TO_STRING
{
  int16_t value;
  const char * string;
} I16_TO_STRING;

//Declare the radio call types
typedef enum
{
  RADIO_CALL_configureRadio = 0,
  RADIO_CALL_setRadioFrequency,
  RADIO_CALL_returnToReceiving,
  RADIO_CALL_calcAirTime,
  RADIO_CALL_xmitDatagramP2PTrainingPing,
  RADIO_CALL_xmitDatagramP2pTrainingParams,
  RADIO_CALL_xmitDatagramP2PPing,
  RADIO_CALL_xmitDatagramP2PAck1,
  RADIO_CALL_xmitDatagramP2PAck2,
  RADIO_CALL_xmitDatagramP2PCommand,
  RADIO_CALL_xmitDatagramP2PCommandResponse,
  RADIO_CALL_xmitDatagramP2PData,
  RADIO_CALL_xmitDatagramP2PHeartbeat,
  RADIO_CALL_xmitDatagramP2PAck,
  RADIO_CALL_xmitDatagramMpData,
  RADIO_CALL_xmitDatagramMpHeartbeat,
  RADIO_CALL_xmitDatagramMpAck,
  RADIO_CALL_xmitDatagramMpPing,
  RADIO_CALL_xmitDatagramTrainingPing,
  RADIO_CALL_xmitDatagramTrainingAck,
  RADIO_CALL_xmitDatagramTrainRadioParameters,
  RADIO_CALL_xmitVcDatagram,
  RADIO_CALL_xmitVcHeartbeat,
  RADIO_CALL_xmitVcAckFrame,
  RADIO_CALL_xmitVcPing,
  RADIO_CALL_xmitVcAck1,
  RADIO_CALL_xmitVcAck2,
  RADIO_CALL_rcvDatagram,
  RADIO_CALL_transmitDatagram,
  RADIO_CALL_retransmitDatagram,
  RADIO_CALL_startChannelTimer,
  RADIO_CALL_stopChannelTimer,
  RADIO_CALL_syncChannelTimer,
  RADIO_CALL_setHeartbeatShort,
  RADIO_CALL_setHeartbeatLong,
  RADIO_CALL_setHeartbeatMultipoint,
  RADIO_CALL_setVcHeartbeatTimer,
  //Insert new values before this line
  RADIO_CALL_transactionCompleteISR,
  RADIO_CALL_hopISR,
#ifdef  RADIOLIB_LOW_LEVEL
  RADIO_CALL_readSX1276Register,
  RADIO_CALL_printSX1276Registers,
#endif  //RADIOLIB_LOW_LEVEL
  RADIO_CALL_MAX
} RADIO_CALLS;
