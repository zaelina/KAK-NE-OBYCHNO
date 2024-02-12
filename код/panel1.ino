#include <Servo.h>    
#include <Stepper.h>    
int cc = A0;    
int oo = A1;    
int gg = A3;    
int bb = A2;  
int secc = 0;
int ii = 0;
int j = -1;  
int top;  
int st;  
int rgh;  
int lft;  
int bk;     
int i = 20; // шаг степпера   
Stepper pon(200, 2, 3, 4, 5);    
float q = 20.00;
float qq = 50.00;
Servo servo;     
int servoPin = 6;    
float c;    
float o;    
float g;    
float b;   
int raz = 0; 
int gr = 0;
int pongr = 0;  
int n = 0;    
double a = 0; 
int ponstep = 20; 
double w = 0;  
int servwr = 5;  
int servgr = 0;  
    
 
void topp() { 
  digitalWrite(8, HIGH); 
  digitalWrite(9, LOW); 
} 
 
void green() { 
  digitalWrite(9, HIGH); 
  digitalWrite(8, LOW); 
} 
    
void setup() {    
    Serial.begin(9600);    
  servo.attach(servoPin);    
  pon.setSpeed(10);    
  servo.write(0); 
  topp(); 
  for (int j = 1; j <= 20; j ++){ 
    ponn(); 
    servgr += w; 
    raz += a; 
    delay(100);
  }    
  servgr /= 20; 
  raz /= 20; 
  servo.write(servgr); 
  pon.step(raz - gr); 
  gr = raz; 
  delay(5000);
}    
  
void ponn() {   
  topp(); 
  top = 1024 - analogRead(A3); 
  st = 1024 - analogRead(A7);   
  rgh = (1024 - analogRead(A4)) * (880.00/760.00);   
  bk = (1024 - analogRead(A6)) * (760.00/850.00);   
  lft = (1024 - analogRead(A5)) * (600.00/900.00);  
  float y = bk - st;   
  float x = rgh - lft;   
  a = atan(y / x) * (200.00 / (2.00 * PI)); 
  if (a != 0) { 
  if ((x < 0 and y < 0) or (x > 0 and y < 0)) {// третья и четвертая  
    a = atan(y / x) * (200.00 / (2.00 * PI)); 
    a += 100 + (1 - (a / abs(a))) * 50; 
  } else {// первая и вторая   
     a = atan((y / x)) * (200.00 / (2.00 * PI)); 
     a += (1 - (a / abs(a))) * 50; 
  } 
  float xy = pow(x * x + y * y, 0.5); 
  w = round(atan((top)/xy) * (180.00 / (2.00 * PI)) * 2); 
  } 
} 

void ponisec() {
  int sec = millis() + secc;
  if (sec >= 10000){
    secc = 10000 * i;
    i -= 1;
    for (int j = 1; j <= 20; j ++){ 
      ponn(); 
      servgr += w; 
      raz += a; 
      delay(100); 
    }    
    servgr /= 20; 
    raz /= 20; 
    if ((abs(pongr - raz) > 80) and (abs(pongr - raz) < 120)){
      raz = pongr;
      servgr = 180 - servgr;
    }
    if (abs(pongr - raz) > 30){
      pon.step(raz - pongr); 
    }
    if (abs(servgr - n) > 30){
      servo.write(servgr); 
    }
    Serial.println("11");
  }
}
 
void loop(){ 
  o = (analogRead(oo) * (180.00/226.00));
  g = (analogRead(gg));
  c = (analogRead(cc));
  b = (analogRead(bb)); 
  Serial.print(c); 
  Serial.print(" "); 
  Serial.print(o); 
  Serial.print(" "); 
  Serial.print(b); 
  Serial.print(" "); 
  Serial.println(g);
  //ponn(); 
  while((abs(c - b) > q) or (abs(g - o) > q) or (abs(b - g) > q)){   
    green();
      c = analogRead(cc);  
      o = (analogRead(oo) * (180.00/226.00));  
      g = analogRead(gg);  
      b = analogRead(bb);    
    float m = min(min(g, b), min(c, o));   
    if (m == c){   
      while((o - c) > qq){   
        c = analogRead(cc);  
        o = analogRead(bb);  
        pon.step(i);
        pongr += i;
        delay(10);     
        }}   
    if (m == o){   
        while((c - o) > qq){   
          o = (analogRead(oo) * (180.00/226.00)); 
          c = analogRead(cc);  
          pon.step(-i);   
          pongr -= i;
          delay(10);   
        }}   
    if (m == g){   
      while((b - g) > qq){   
        b = (analogRead(bb) * (180.00/226.00));  
        g = analogRead(gg);  
        pon.step(-i); 
        pongr -= i;   
        delay(10);   
        }}   
    if (m == b){   
      while((g - b) > qq){   
        g = analogRead(gg);  
        b = analogRead(bb);  
        pon.step(i);
        pongr += i;    
        delay(10);   
        }}   
    c = analogRead(cc);  
    o = (analogRead(oo) * (180.00/226.00));  
    g = analogRead(gg);  
    b = analogRead(bb);   
  while((abs(c - g) > q)){   
        c = analogRead(cc);  
        o = (analogRead(oo) * (180.00/226.00));  
        g = analogRead(gg);  
        b = analogRead(bb);    
      float p = (min(c, g));     
          if (p == c) {   
            n = n - 1;    
          if (n < 0){   
            servo.write(180);   
            n = 180;   
          }    
          servo.write(n);   
    
            
        }   
      Serial.println(p);   
          if (p == g) {   
          n = n + 1;   
          if (n > 180){   
            servo.write(0);   
            n = 0;   
          }   
          servo.write(n);   
            
        }   
      }
    ponisec();   
  }
}
 