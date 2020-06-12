#include <IRLib.h>
#include <IRLibMatch.h>

class IRsendRCMM : public virtual IRsendBase
{
public:
  void send(unsigned long data, unsigned char nbits);
};

#define RCMM (LAST_PROTOCOL + 1)
#define RCMM_HEAD_MARK 417
#define RCMM_DATA_MARK 167
#define RCMM_ZERO 278
#define RCMM_ONE 444
#define RCMM_TWO 611
#define RCMM_THREE 778
#define RCMM_TOLERANCE 80

void IRsendRCMM::send(unsigned long data, unsigned char nbits)
{
  Extent = 0;
  data = data << (32 - nbits);
  nbits = nbits / 2;
  enableIROut(36);
  mark(RCMM_HEAD_MARK);
  space(RCMM_ZERO); //Send header
  for (int i = 0; i < nbits; i++)
  {
    mark(RCMM_DATA_MARK);
    switch (data & 0xC0000000UL)
    { //use the leftmost two bits
    case 0x00000000UL:
      space(RCMM_ZERO);
      break;
    case 0x40000000UL:
      space(RCMM_ONE);
      break;
    case 0x80000000UL:
      space(RCMM_TWO);
      break;
    case 0xC0000000UL:
      space(RCMM_THREE);
      break;
    }
    data <<= 2;
  };
  mark(RCMM_DATA_MARK);
  space(27778 - Extent);
};

//Create a custom class that combines this new protocol with all the others
class MyCustomSend : public virtual IRsend,
                     public virtual IRsendRCMM
{
public:
  void send(IRTYPES Type, unsigned long data, int nbits);
};
void MyCustomSend::send(IRTYPES Type, unsigned long data, int nbits)
{
  if (Type == RCMM)
    IRsendRCMM::send(data, nbits);
  else
    IRsend::send(Type, data, nbits);
}

MyCustomSend My_Sender;
int ledPin = 2;

void setup()
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, HIGH);
  My_Sender.send(RCMM, 0x2340A65C, 32); // OK 1
  My_Sender.send(RCMM, 0x2340265C, 32); // OK 2
  My_Sender.send(RCMM, 0x23402655, 32); // Exit to TV
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(50);
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(50);
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(4500);
}
