#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32,16,2);
char k[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};

byte rpins[4]={2,3,4,5};
byte cpins[4]={6,7,8,9};
char myk;
Keypad mypad (makeKeymap(k),rpins,cpins,4,4);
char pass[]={'1','3','4','5'};
char upass[sizeof(pass)]={0};
byte counter=0,ii=0,i=0;
byte buttonstate=-1;
byte ID[]={A2,11,12,13,A0,A1};
byte c =0;
byte cont=0;

void reslcd(){
 lcd.home();
 lcd.clear();
 lcd.print("Enter password");
 lcd.setCursor(0,1);
}

void setup() {
  for(c=0;c<6;c++)
    pinMode(ID[c],INPUT_PULLUP);
 lcd.init();
 lcd.backlight();
 reslcd();
 

}

void loop() {
  myk=mypad.getKey();
  while(!myk)myk=mypad.getKey();
  lcd.print("*");
  if(myk=='D'){
    Serial.println(counter);
    lcd.clear();  
    lcd.home();
    for(i=0;i<sizeof(upass);i++){
      if(upass[i]!=pass[i])break;}
    
  
    
  if((i==sizeof(upass))&&(counter==0)){
  counter=-1;
  lcd.clear();
  lcd.home();
  lcd.print("User authorized");
  digitalWrite(10,1);
  delay(3000);
  digitalWrite(10,0);
  reslcd();
  id_button();
  }
  else {
    
  counter=-1;
  lcd.clear();
  lcd.home();
  lcd.print("Wrong password");
  delay(2000);
  id_button();
  reslcd();
  }
  }
  else
    *(upass+counter)=myk;
 counter=(counter>=3)?-1:counter;
 counter++; 
}
void id_button() {
  bool l = false;
  lcd.clear();
  lcd.print("Enter you finger");
  delay(2000);
  buttonstate=0xFF;
  for(c=0;buttonstate==0xFF;c++){
  buttonstate=(!digitalRead(ID[c]))?c:0xFF;
  c=(c>=6)?-1:c;
  }
  if (buttonstate==0xFF){  
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.home();
    lcd.print("Enter you finger");
    delay(2000);
    buttonstate=0xFF;
  }
  else{
    lcd.clear();
    lcd.print("The ID is : "+String(c));
      delay(2000);
    reslcd();
    buttonstate=0xFF;
  }
    
    }    
    
