#define BLUE_LED 11
#define RED_LED 10

const int lower = 150;
const int array_length = 850;
const int fourier_n = 50;
const int delay_time = 2;
// array storing brightness values calculated from ecg-signal generated using fourier series
uint8_t values[array_length - lower];


void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  initialize_data();
}


void loop() {
  for (int x = 0; x < array_length - lower; x++) {
    analogWrite(BLUE_LED, values[x]);
    analogWrite(RED_LED, values[x]);

    delay(delay_time);
  }
}


void initialize_data() {
  Serial.print(fourier_n);
  Serial.println(" Fourier sums");
  Serial.print(array_length - lower);
  Serial.println(" data points");
  Serial.println("Starting... this will take some time!");

  blink_led(5);
  int x = lower;
  for (int i = 0; i < array_length - lower; i++) {

    //float val = (fourier_fP(fourier_n, x)+fourier_fR(fourier_n, x)+fourier_fT(fourier_n, x))*100;

    float val = (fourier_fP(fourier_n, x) + fourier_fR(fourier_n, x)) * 100;

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
    digitalWrite(RED_LED, LOW);
    delay(3);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
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
