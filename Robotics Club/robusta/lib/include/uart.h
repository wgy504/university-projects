#ifndef _UART_H_
#define _UART_H_


//--------------------------------------------------------------
// Liste aller UARTs
// (keine Nummer doppelt und von 0 beginnend)
//--------------------------------------------------------------
typedef enum
{
  COM2 = 0,  // COM2 (TX=PA2, RX=PA3)
  COM3 = 1   // COM3 (TX=PD8, RX=PD9)
}UART_NAME_t;

#define  UART_ANZ   2 // Anzahl von UART_NAME_t


//--------------------------------------------------------------
// Endekennung beim Senden
//--------------------------------------------------------------
typedef enum {
  NONE = 0,  // keine Endekennung
  LFCR,      // LineFeed + CarriageReturn (0x0A,0x0D)
  CRLF,      // CarriageReturn + LineFeed (0x0D,0x0A)
  LF,        // nur LineFeed (0x0A)
  CR         // nur CarriageReturn (0x0D)
}UART_LASTBYTE_t;


//--------------------------------------------------------------
// Status beim Empfangen
//--------------------------------------------------------------
typedef enum {
  RX_EMPTY = 0,  // nichts empfangen
  RX_READY,      // es steht was im Empfangspuffer
  RX_FULL        // RX-Puffer ist voll
}UART_RXSTATUS_t;


//--------------------------------------------------------------
// Struktur eines UART-Pins
//--------------------------------------------------------------
typedef struct {
  GPIO_TypeDef* PORT;     // Port
  const uint16_t PIN;     // Pin
  const uint32_t CLK;     // Clock
  const uint8_t SOURCE;   // Source
}UART_PIN_t;

//--------------------------------------------------------------
// Struktur eines UARTs
//--------------------------------------------------------------
typedef struct {
  UART_NAME_t UART_NAME;    // Name
  const uint32_t CLK;       // Clock
  const uint8_t AF;         // AF
  USART_TypeDef* UART;      // UART
  const uint32_t BAUD;      // Baudrate
  const uint8_t INT;        // Interrupt
  UART_PIN_t TX;            // TX-Pin
  UART_PIN_t RX;            // RX-Pin
}UART_t;


//--------------------------------------------------------------
// Defines fuer das Empfangen
//--------------------------------------------------------------
#define  RX_BUF_SIZE   50    // Groesse vom RX-Puffer in Bytes
#define  RX_FIRST_CHR  0x20  // erstes erlaubte Zeichen (Ascii-Wert)
#define  RX_LAST_CHR   0x7E  // letztes erlaubt Zeichen (Ascii-Wert)
#define  RX_END_CHR    0x0D  // Endekennung (Ascii-Wert)


//--------------------------------------------------------------
// Struktur fuer UART_RX
//--------------------------------------------------------------
typedef struct {
  char rx_buffer[RX_BUF_SIZE]; // RX-Puffer (Ringpuffer)
  uint16_t wr_ptr;             // Schreib Pointer
  uint16_t rd_ptr;             // Lese Pointer
  UART_RXSTATUS_t status;      // RX-Status
}UART_RX_t;
UART_RX_t UART_RX[UART_ANZ];


//--------------------------------------------------------------
// Globale Funktionen
//--------------------------------------------------------------
void uartInit(void);
int charToInt(char c[], int firstComp, int lastComp);
short isSame(char buffer[], char word[], int length) ;
void uartPutByte(UART_NAME_t uart, uint16_t wert);
void uartPrintf(UART_NAME_t uart, char *ptr);
UART_RXSTATUS_t uartGets(UART_NAME_t uart, char *ptr);



//--------------------------------------------------------------
#endif // __STM32F4_UB_UART_H
