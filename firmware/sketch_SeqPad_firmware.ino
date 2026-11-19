
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int times_pressed = 0;
int is_being_pressed = 0;
unsigned long previous_time = 0;
int threshold = 20;
int which_key_has_been_pressed = 0; // 0 = null, 1 = first, 2 = second, and so on ... (or analogpin number + 1)
int is_input_system_working = 0;
int activation_button_once = 1;


Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  pinMode(2, INPUT_PULLUP);

  Serial.begin(9600);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
  display.display();
};

void loop(){

  unsigned long current_time = millis();

  Serial.println(analogRead(A0));
  display.setCursor(0, 0);
  display.clearDisplay();

  if (digitalRead(2) == 0) {
    activation_button_once = 1;
  }

  if (digitalRead(2) == 1 and activation_button_once == 1) {
    if (is_input_system_working == 0) {
     is_input_system_working = 1;
    }
    else {
      is_input_system_working = 0;
    }
    activation_button_once = 0;
  }




  if (is_input_system_working == 1) {
   if (is_being_pressed == 0){
     if (analogRead(A0) > threshold) {
      times_pressed += 1;
     is_being_pressed = 1;
     which_key_has_been_pressed = 1;
     }

     if (analogRead(A1) > threshold) {
     times_pressed += 1;
     is_being_pressed = 1;
     which_key_has_been_pressed = 2;
      }
    }
  }
  if (analogRead(A0) < threshold) {
    is_being_pressed = 0;
  }

  display.print("You pressed ");
  display.print(times_pressed);
  display.println(" times");
  display.print("you pressed ");
  display.println(which_key_has_been_pressed);
  display.display();

};