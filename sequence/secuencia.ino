
int IN1 = 2; //MOTOR IZQUIERDO
int IN2 = 3;
int ENA = 5;

int IN3 = 10; //MOTOR DERECHO
int IN4 = 11;
int ENB = 6;

int TRIGF = 13; //SENSOR FRENTE
int ECOF = 4;
int DURACIONF;
int DISTANCIAF;

int TRIGD = 12; //SENSOR DERECHO
int ECOD = 9;
int DURACIOND;
int DISTANCIAD;

int TRIGI = 8; //SENSOR IZQUIERDO
int ECOI = 7;
int DURACIONI;
int DISTANCIAI;

int input;


void setup() {
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);
  
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENB, OUTPUT);

  pinMode(TRIGF, OUTPUT);
  pinMode(ECOF, INPUT);

  pinMode(TRIGD, OUTPUT);
  pinMode(ECOD, INPUT);

  pinMode(TRIGI, OUTPUT);
  pinMode(ECOI, INPUT);
  
   Serial.begin(9600);

}

void loop() {

digitalWrite(TRIGF, HIGH);
delay(1);
digitalWrite(TRIGF, LOW);
DURACIONF = pulseIn(ECOF, HIGH);
DISTANCIAF =DURACIONF / 58.2;
Serial.println(DISTANCIAF);
delay(200);

digitalWrite(TRIGD, HIGH);
delay(1);
digitalWrite(TRIGD, LOW);
DURACIOND = pulseIn(ECOD, HIGH);
DISTANCIAD =DURACIOND / 58.2;
Serial.println(DISTANCIAD);
delay(200);


digitalWrite(TRIGI, HIGH);
delay(1);
digitalWrite(TRIGI, LOW);
DURACIONI = pulseIn(ECOI, HIGH);
DISTANCIAI =DURACIONI / 58.2;
Serial.println(DISTANCIAI);
delay(200);

if (DISTANCIAD <=9 && DISTANCIAD >=3){
  analogWrite(ENA, 255);//los dos motores avanzan hacia delante
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);  
  analogWrite(ENB, 255);
  digitalWrite(IN3, LOW);                              
  digitalWrite(IN4, HIGH); 
}

if (DISTANCIAF <=7 && DISTANCIAF >=0){
   digitalWrite(ENA, 0);//paro
   digitalWrite(IN1, 0);
   digitalWrite(IN2, 0);  
   digitalWrite(ENB, 0);
   digitalWrite(IN3, 0);
   digitalWrite(IN4, 0); 
}
if (DISTANCIAF <=7 && DISTANCIAF >=0 && DISTANCIAD <=9    && DISTANCIAD >=3){
   analogWrite(ENA, 100);//vuelta izquierda
   digitalWrite(IN1, 1);
   digitalWrite(IN2, 0);  
   digitalWrite(ENB, 1);
   digitalWrite(IN3, 0);
   digitalWrite(IN4, 1); 
   delay(3000);
   
   digitalWrite(ENA, 0);//paro
   digitalWrite(IN1, 0);
   digitalWrite(IN2, 0);  
   digitalWrite(ENB, 0);
   digitalWrite(IN3, 0);
   digitalWrite(IN4, 0); 
}

if (DISTANCIAD <=100 && DISTANCIAD >=20){
  //BUSCAR SENTIDO
  //DISTANCIAF <=100 && DISTANCIAF >=9 &&
   delay(3000);
   digitalWrite(ENA, 1);//vuelta derecha
   digitalWrite(IN1, 0);
   digitalWrite(IN2, 1);  
   analogWrite(ENB, 100);
   digitalWrite(IN3, 1);
   digitalWrite(IN4, 0); 
   delay(2900);
   analogWrite(ENA, 255);//los dos motores avanzan hacia delante
   digitalWrite(IN1, LOW);
   digitalWrite(IN2, HIGH);  
   analogWrite(ENB, 255);
   digitalWrite(IN3, LOW);                              
   digitalWrite(IN4, HIGH); 
   delay(4900);
   digitalWrite(ENA, 0);//paro
   digitalWrite(IN1, 0);
   digitalWrite(IN2, 0);  
   digitalWrite(ENB, 0);
   digitalWrite(IN3, 0);
   digitalWrite(IN4, 0); 
}
if (DISTANCIAD <=3 && DISTANCIAD >=0){
   analogWrite(ENA, 100);//RESOLVER COLISON
   digitalWrite(IN1, 1);
   digitalWrite(IN2, 0);  
   digitalWrite(ENB, 1);
   digitalWrite(IN3, 0);
   digitalWrite(IN4, 1); 
   delay(100);
   digitalWrite(ENA, 0);//paro
   digitalWrite(IN1, 0);
   digitalWrite(IN2, 0);  
   digitalWrite(ENB, 0);
   digitalWrite(IN3, 0);
   digitalWrite(IN4, 0); 
}


//if (DISTANCIAF <=9 && DISTANCIAF >=0 && DISTANCIAD <=9 && DISTANCIAD >=0 && DISTANCIAI <=8 && DISTANCIAI >=0){
//  //REGRESAR
//  
//   analogWrite(ENA, 100);//vuelta izquierda
//   digitalWrite(IN1, 1);
//   digitalWrite(IN2, 0);  
//   digitalWrite(ENB, 1);
//   digitalWrite(IN3, 0);
//   digitalWrite(IN4, 1);
//   delay(5600);
//   analogWrite(ENA, 255);//los dos motores avanzan hacia delante
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);  
//   analogWrite(ENB, 255);
//   digitalWrite(IN3, LOW);                              
//   digitalWrite(IN4, HIGH); 
//   delay(5000);
//   digitalWrite(ENA, 0);//paro
//   digitalWrite(IN1, 0);
//   digitalWrite(IN2, 0);  
//   digitalWrite(ENB, 0);
//   digitalWrite(IN3, 0);
//   digitalWrite(IN4, 0); 
//}
//if (DISTANCIAI <=100 && DISTANCIAF >=10 && DISTANCIAD <=100 && DISTANCIAD >=10){
//  //REGRESAR A LA RUTA
//   delay(3500);
//   digitalWrite(ENA, 1);//vuelta derecha
//   digitalWrite(IN1, 0);
//   digitalWrite(IN2, 1);  
//   analogWrite(ENB, 100);
//   digitalWrite(IN3, 1);
//   digitalWrite(IN4, 0); 
//   delay(300);
//   analogWrite(ENA, 255);//los dos motores avanzan hacia delante
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);  
//   analogWrite(ENB, 255);
//   digitalWrite(IN3, LOW);                              
//   digitalWrite(IN4, HIGH); 
//   delay(400);
//   digitalWrite(ENA, 0);//paro
//   digitalWrite(IN1, 0);
//   digitalWrite(IN2, 0);  
//   digitalWrite(ENB, 0);
//   digitalWrite(IN3, 0);
//   digitalWrite(IN4, 0); 
//}

// if (Serial.available()>0){
//    input=Serial.read();
//    if (input=='0'){
//  analogWrite(ENA, 255);//los dos motores avanzan hacia delante
//  digitalWrite(IN1, LOW);
//  digitalWrite(IN2, HIGH);  
//  analogWrite(ENB, 255);
//  digitalWrite(IN3, LOW);
//  digitalWrite(IN4, HIGH); 
//  }
//   if (input=='2'){  
//   analogWrite(ENA, 255);//los dos motores avanzan hacia atras
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);  
//   analogWrite(ENB, 255);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW); 
//}
//   if (input=='3'){  
//   analogWrite(ENA, 100);//vuelta izquierda
//   digitalWrite(IN1, 1);
//   digitalWrite(IN2, 0);  
//   digitalWrite(ENB, 1);
//   digitalWrite(IN3, 0);
//   digitalWrite(IN4, 1); 
//}
//   if (input=='4'){   
//   digitalWrite(ENA, 1);//vuelta derecha
//   digitalWrite(IN1, 0);
//   digitalWrite(IN2, 1);  
//   analogWrite(ENB, 100);
//   digitalWrite(IN3, 1);
//   digitalWrite(IN4, 0); 
//}
//   if (input=='6'){  
//   digitalWrite(ENA, 0);//paro
//   digitalWrite(IN1, 0);
//   digitalWrite(IN2, 0);  
//   digitalWrite(ENB, 0);
//   digitalWrite(IN3, 0);
//   digitalWrite(IN4, 0); 
//}
   
//
//}
}
