
#include <Dictionary.h> // WHY DOESN'T C++ HAVE DICTIONARIES ON IT'S OWN
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


Dictionary sequences; // can't set the inside values here, go to setup()



int times_pressed = 0;
int A0_is_being_pressed = 0;
int A1_is_being_pressed = 0;
unsigned long previous_time = 0;
int threshold = 70;
int which_key_has_been_pressed = 0; // 0 = null, 1 = first, 2 = second, and so on ... (or analogpin number + 1)
int is_input_system_working = 0;
int input_activation_button_once = 1;
int sequence_sent = 0;
String current_sequence = "0";
String value = "0";

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  pinMode(3, INPUT);
  pinMode(2, INPUT); // 
  pinMode(5, OUTPUT); // led

  sequences.set("0112", "red_led_light_up"); // key needs to be a str

  Serial.begin(9600);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
  display.display();
};

void loop(){

  unsigned long current_time = millis();

  Serial.print(analogRead(A0));
  Serial.print('\t');
  Serial.println(analogRead(A1));
  display.setCursor(0, 0);
  display.clearDisplay();

  if (digitalRead(2) == 0) {
    input_activation_button_once = 1;
  }

  if (digitalRead(2) == 1 and input_activation_button_once == 1) {
    if (is_input_system_working == 0) {
     is_input_system_working = 1;
    }
    else {
      is_input_system_working = 0;
    }
    input_activation_button_once = 0;
  }

  if (digitalRead(3) == 1) {
    sequence_sent = 1;
  }

  if (sequence_sent == 1) {
    value = sequences[current_sequence];
    if (value == "red_led_light_up") {
      if (digitalRead(5) == LOW) {
        digitalWrite(5, HIGH);
      }
      else {
        digitalWrite(5, LOW);
      }
    }
    else{
      value = "0";
    }

    current_sequence = "0";
    sequence_sent = 0;
  }

  if (is_input_system_working == 1) {
    if (A0_is_being_pressed == 0){
      if (analogRead(A0) > threshold) {
        times_pressed += 1;
        A0_is_being_pressed = 1;
        which_key_has_been_pressed = 1;
        current_sequence = current_sequence + "1";
      }
    }

    if (A1_is_being_pressed == 0){
     if (analogRead(A1) > threshold) {
      times_pressed += 1;
      A1_is_being_pressed = 1;
      which_key_has_been_pressed = 2;
      current_sequence = current_sequence + "2";
      }
    }
  }
  if (analogRead(A0) < threshold - 10) {
    A0_is_being_pressed = 0;
  }
  if (analogRead(A1) < threshold - 10) {
    A1_is_being_pressed = 0;
  }








  display.print("You pressed ");
  display.print(times_pressed);
  display.println(" times");
  display.print("you pressed ");
  display.println(current_sequence);
  display.display();

}





