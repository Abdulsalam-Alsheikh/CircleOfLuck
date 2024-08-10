#define clockPin 10 // Clock pin of 74HC595 is connected to Digital pin 10
#define dataPin  9  // Data  pin of 74HC595 is connected to Digital pin 9 
#define latchPin 8  // Latch pin of 74HC595 is connected to Digital pin 8
#define clr 7

int win_arr[12];
void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clr, OUTPUT);

  digitalWrite(clr, HIGH);

  led_diplay_start_finish_forward();


}

void loop() {
  int t = 0;
  for (int i = 0; i < 12; i++) {
    if (win_arr[i] == 1) {
      t++;
    }
  }
  Serial.println(digitalRead(3));
  if (digitalRead(3) == LOW || t == 12) {
    start_finish_control();
    // generate a random value for loop
    int A0_loop = analogRead(A0);
    int ran_loop = A0_loop % 2 + 3;
    // generate a random winer
    int A0_winer = analogRead(A0);
    int winer = A0_winer % 12 + 1;
    //for every click on buttom chose a difernent winer
    while (win_arr[winer - 1] == 1) {
      A0_winer = analogRead(A0);
      winer = A0_winer % 12 + 1;
    }
    win_arr[winer - 1] = 1;
    winer = winer + 12 * (ran_loop - 1);

    //loop that is decide how much led move before stop in one of 12 led
    for (int j = 0; j < ran_loop; j++) {
      int iter = 0;
      if (winer >= 12) {
        iter = 12;
        winer -= 12;
      }
      else {
        iter = winer;
      }

      for (long int i = 1; i < int(pow(2, iter)); i *= 2) {

        digitalWrite(latchPin, LOW);
        if (i < 256) {
          shiftOut(dataPin, clockPin, MSBFIRST, 0 );
          shiftOut(dataPin, clockPin, MSBFIRST, i );
        }
        else {
          shiftOut(dataPin, clockPin, MSBFIRST, i / 256);
          shiftOut(dataPin, clockPin, MSBFIRST, 0);
        }
        digitalWrite(latchPin, HIGH);
        delay(100);
      }
      //for blink led after stop
      if (iter < 12 || (iter==12 && winer==0)) {
        long int sum_blink = 1;
        int bli_iter = iter - 1;
        for(int f=0; f<bli_iter ;f++){
            sum_blink*=2;
          }
        for (int k = 0; k < 3; k++) {
          delay(400);
          digitalWrite(latchPin, LOW);
          shiftOut(dataPin, clockPin, MSBFIRST, 0 );
          shiftOut(dataPin, clockPin, MSBFIRST, 0 );
          digitalWrite(latchPin, HIGH);
          delay(400);
          
          digitalWrite(latchPin, LOW);
          if (iter <= 8) {
            shiftOut(dataPin, clockPin, MSBFIRST, 0 );
            shiftOut(dataPin, clockPin, MSBFIRST, sum_blink);
          }
          else {
            shiftOut(dataPin, clockPin, MSBFIRST, sum_blink / 256 );
            shiftOut(dataPin, clockPin, MSBFIRST, 0);
          }
          digitalWrite(latchPin, HIGH);
        }
      }



    }
  }
}

void led_diplay_start_finish_forward() {

  int sum_first = 0;
  int sum_second = 0;
  for (long int i = 1; i < int(pow(2, 12)); i *= 2) {
    digitalWrite(latchPin, LOW);

    if (i < 256) {
      sum_first += i;
      shiftOut(dataPin, clockPin, MSBFIRST, 0 );
      shiftOut(dataPin, clockPin, MSBFIRST, sum_first);
    }
    else {
      sum_second += i / 256;
      shiftOut(dataPin, clockPin, MSBFIRST, sum_second);
      shiftOut(dataPin, clockPin, MSBFIRST, sum_first);
    }
    digitalWrite(latchPin, HIGH);
    delay(500);
  }
}

void led_diplay_start_again_back() {

  int sum_first = 0;
  int sum_second = 0;
  for (long int i = int(pow(2, 11)); i >= 1; i /= 2) {
    digitalWrite(latchPin, LOW);

    if (i < 256) {
      sum_first += i;
      shiftOut(dataPin, clockPin, MSBFIRST, sum_second );
      shiftOut(dataPin, clockPin, MSBFIRST, sum_first);
    }
    else {
      sum_second += i / 256;
      shiftOut(dataPin, clockPin, MSBFIRST, sum_second);
      shiftOut(dataPin, clockPin, MSBFIRST, sum_first);
    }
    digitalWrite(latchPin, HIGH);
    delay(500);
  }
}

void start_finish_control() {
  int n = 0;
  for (int i = 0; i < 12; i++) {
    if (win_arr[i] == 1) {
      n++;
    }
  }
  int ones = 0;
  while (n == 12) {
    if (ones == 0) {
      delay(4000);
      led_diplay_start_finish_forward();
      ones = 1;
    }
    if (digitalRead(3) == LOW) {
      led_diplay_start_again_back();
      n = 0;
      for (int i = 0; i < 12; i++) {
        win_arr[i] = 0;
      }
    }
  }
}
