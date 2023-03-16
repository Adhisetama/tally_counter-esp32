// author: Muhammad Azka Adhisetama
//         21/477807/TK/52628
// program Tally Counter dengan microcontroller ESP32

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 


// deklarasi konstanta
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int PIN_1 = 27;
int PIN_2 = 26;
unsigned long UPDATE_INTERVAL = 50;


// deklarasi class
class Button
{
  public:
    int pin;
    byte curr_state;
    byte prev_state;

    Button (int pin) {
      this->curr_state = LOW;
      this->prev_state = LOW;
      this->pin = pin;
    }

    void initialize() {
      pinMode(this->pin, INPUT_PULLUP);
    }

    void readState() {
      this->curr_state = digitalRead(this->pin);
    }

    void updateState() {
      this->prev_state = this->curr_state;
    }

    bool pressed() {
      return prev_state == HIGH and curr_state == LOW;
    }
};


// deklarasi global variable
unsigned long prev_millis = millis();
unsigned long curr_millis = millis();
Button btn_inc(PIN_1);
Button btn_dec(PIN_2);
int count = 0;

void setup() {
  
  // inisialisasi button
  btn_inc.initialize();
  btn_dec.initialize();

  // inisialisasi display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  
}

void loop() {
  
  curr_millis = millis();
  if (curr_millis - prev_millis >= UPDATE_INTERVAL)
  {
    // update semua curr_state
    btn_inc.readState();
    btn_dec.readState();

    // logika counter
    if (btn_inc.curr_state == LOW and btn_dec.curr_state == LOW)
      count = 0;
    else if (btn_inc.pressed())
      count++;
    else if (btn_dec.pressed())
      count--;

    // update semua prev_state;
    btn_inc.updateState();
    btn_dec.updateState();
    
    prev_millis = curr_millis;
  }

  // update display
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10,5);
  display.print("21/477807/TK/52628");
  display.setCursor(20, 20);
  display.setTextSize(5);
  display.print(String(count));
  display.display();

}
