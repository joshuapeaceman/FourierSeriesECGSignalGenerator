#define BLUE_LED 11
#define RED_LED 10

const int lower = 150;
const int array_length = 900;
const int fourier_n = 50;
const int delay_time = 2;
// array storing brightness values calculated from ecg-signal generated using fourier series
uint8_t values[array_length - lower];

int settings_case = 0;

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(9, INPUT);
  
  initialize_data(0);
}

int analog_in_one = 0;
int analog_in_two = 0;
int case_ctr = 0;
void loop() {
    Serial.print("Case: ");
    Serial.println(case_ctr);

    if (digitalRead(9) == 0){
      case_ctr++;
      delay(300);
    }

   
    switch (case_ctr){
      case 0:      
        for (int x = 0; x < array_length - lower; x++) {
          analogWrite(BLUE_LED, values[x]);
          analogWrite(RED_LED, values[x]);
          delay(delay_time);
        }
        break;
        
      case 1:
          analogWrite(RED_LED, 0);
          for (int x = 0; x < array_length - lower; x++) {
            analogWrite(BLUE_LED, values[x]);
            delay(delay_time);
          } 
        break;

      case 2:
        analogWrite(BLUE_LED, 0);
        for (int x = 0; x < array_length - lower; x++) {          
          analogWrite(RED_LED, values[x]);
          delay(delay_time);
          }
        break;
      
        case 3:
          analogWrite(BLUE_LED, 1);
          for (int x = 0; x < array_length - lower; x++) {          
            analogWrite(RED_LED, values[x]);
            delay(delay_time);
          }
        break;

        case 4:
          analogWrite(RED_LED, 1);
          for (int x = 0; x < array_length - lower; x++) {          
            analogWrite(BLUE_LED, values[x]);
            delay(delay_time);
          }
          break;

         case 5:
          analogWrite(BLUE_LED, 0);
          for (int x = 0; x < array_length - lower; x++) {          
            analogWrite(RED_LED, values[x]);
            delay(delay_time);
          }
        break;

        case 6:
          analogWrite(RED_LED, 0);
          for (int x = 0; x < array_length - lower; x++) {          
            analogWrite(BLUE_LED, values[x]);
            delay(delay_time);
          }
          break;

        case 7:
          analogWrite(RED_LED, 0);
          analogWrite(BLUE_LED, 255);

          delay(100);

          analogWrite(RED_LED, 255);
          analogWrite(BLUE_LED, 0);

          delay(100);
          
          break;

         case 8:
          analogWrite(RED_LED, 0);
          analogWrite(BLUE_LED, 0);

          break;
          
        case 9:
          blink_led(15);
          if (settings_case == 0){
            settings_case = 1;
            delay(100);
            blink_led(5);
            initialize_data(1);
          }
          else{
            settings_case = 0;
            delay(100);
            blink_led(10);
            initialize_data(0);
            
          }
          case_ctr = 0;
          
        
          break;
        
        
        }
     
}


void initialize_data(int setting) {
  Serial.print("Setting: ");
  Serial.println(setting);
  delay(250);
  Serial.print(fourier_n);
  Serial.println(" Fourier sums");
  Serial.print(array_length - lower);
  Serial.println(" data points");
  Serial.println("Starting... this will take some time!");

  blink_led(5);
  int x = lower;
  for (int i = 0; i < array_length - lower; i++) {
  float val = 0;

    if (setting == 0){
      val = (fourier_fP(fourier_n, x)+fourier_fR(fourier_n, x)+fourier_fT(fourier_n, x))*100;
    }
    else{
      val = (fourier_fP(fourier_n, x) + fourier_fR(fourier_n, x)) * 100;
    }

    if (val <= 4) {
      values[i] = 1;
    }
    else {
      values[i] = round(val);
    }
    x++;
    Serial.print(x - lower);
    Serial.print("/");
    Serial.print(array_length - lower);
    Serial.println(" brightness values calculated");
  }
  blink_led(10);
}

void blink_led(int no) {
  for (int i = 0; i < no; i++) {
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(3);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(100);

    
  }
}

double fourier_fR(int cnt_R, int x) {
  double pi = 3.14159265;
  double ret = 0;
  for (int n = 1; n < cnt_R; n++) {
    ret += ((2.0 / 1000.0) * ((2.0 * ((pow(pi, 4.0) * pow(n, 4.0) + 4680000.0 * pow(pi, 2.0) * pow(n, 2.0) - 5850000000.0) * sin(
                                        (22.0 * pi * n) / 25.0) - 62400.0 * pi * n * (pow(pi, 2.0) * pow(n, 2.0) - 3750.0) * cos((22.0 * pi * n) / 25.0) - (
                                        pow(pi, 4.0) * pow(n, 4.0) + 4680000.0 * pow(pi, 2.0) * pow(n, 2.0) - 5850000000.0) * sin(
                                        (4 * pi * n) / 5.0) - 62400.0 * pi * n * (pow(pi, 2.0) * pow(n, 2.0) - 3750.0) * cos((4.0 * pi * n) / 5.0))) / (
                                pow(pi, 5.0) * pow(n, 5.0))) * cos((2.0 * pi * n * x) / 1000.0) +

            ((2.0 / 1000.0) * (-(2.0 * (62400.0 * pi * n * (pow(pi, 2.0) * pow(n, 2.0) - 3750.0) * sin((22.0 * pi * n) / 25.0) + (
                                          (pow(pi, 4.0) * pow(n, 4.0) + 4680000.0 * pow(pi, 2.0) * pow(n, 2.0) - 5850000000.0) * cos(
                                            (22.0 * pi * n) / 25.0) + 62400.0 * pi * n * (pow(pi, 2.0) * pow(n, 2.0) - 3750.0) * sin((4.0 * pi * n) / 5.0) - (
                                            pow(pi, 4.0) * pow(n, 4.0) + 4680000.0 * pow(pi, 2.0) * pow(n, 2.0) - 5850000000.0) * cos(
                                            (4.0 * pi * n) / 5.0))) / (pow(pi, 5.0) * pow(n, 5.0))) * sin((2.0 * pi * n * x) / 1000.0))));
  }
  return (2 / 1000) * 0.160000 + ret;
}


double fourier_fP(int cnt_P, int x) {
  double pi = 3.14159265;
  double ret = 0;
  for (int n = 1; n < cnt_P; n++) {
    ret += (2.0 / 1000.0 * ((1250.0 * (25.0 * sin((17.0 * pi * n) / 25.0) - 2.0 * pi * n * (
                                         cos((17.0 * pi * n) / 25.0) + cos((13.0 * pi * n) / 25.0)) - 25.0 * sin((13.0 * pi * n) / 25.0))) / (
                              pow(pi, 3) * pow(n, 3))) * cos((2 * pi * n * x) / 1000.0) +
            (2 / 1000.0 * (-(1250.0 * (2.0 * pi * n * (sin((17.0 * pi * n) / 25.0) + sin((13.0 * pi * n) / 25.0)) + 25.0 * cos(
                                         (17.0 * pi * n) / 25.0) - 25.0 * cos((13.0 * pi * n) / 25.0))) / (pow(pi, 3) * pow(n, 3))) * sin(
               (2 * pi * n * x) / 1000.00)));
  }
  return (2 / 1000.0) * (32 / 3.0) + ret;

}


double fourier_fT(int cnt_T, int x) {
  double pi = 3.14159265;
  double ret = 0;
  for (int n = 1; n < cnt_T; n++) {
    ret += (2.0 / 1000.0 * (((224.0 * pow(pi, 2) * pow(n, 2) + 500000.0) * sin((767.0 * pi * n) / 500.0) - 76000.0 * pi * n * cos(
                               (767.0 * pi * n) / 500.0) + (241.0 * pow(pi, 2) * pow(n, 2) - 500000.0) * sin(
                               (153.0 * pi * n) / 125.0) - 79000.0 * pi * n * cos((153.0 * pi * n) / 125.0)) / (20.0 * pow(pi, 3) * pow(n, 3))) * cos(
              (2.0 * pi * n * x) / 1000.0) +
            (2.0 / 1000.0 * (-(76000.0 * pi * n * sin((767.0 * pi * n) / 500.0) + (224.0 * pow(pi, 2) * pow(n, 2) + 500000.0) * cos(
                                 (767.0 * pi * n) / 500.0) + 79000.0 * pi * n * sin((153.0 * pi * n) / 125.0) + (
                                 241.0 * pow(pi, 2) * pow(n, 2) - 500000.0) * cos((153.0 * pi * n) / 125.0)) / (
                               20.0 * pow(pi, 3) * pow(n, 3))) * sin(
               (2.0 * pi * n * x) / 1000.0)));
  }
  return (2 / 1000.0) * (61.9328) + ret;

}
