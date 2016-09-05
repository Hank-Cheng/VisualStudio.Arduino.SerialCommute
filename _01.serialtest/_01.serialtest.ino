/*Serial commute
20160905
by Hank Cheng
*/
void setup() {
  Serial.begin(115200);
  pinMode(ledPin , OUTPUT);
}
int neme = 100 ;
void loop() {
  
  if(Serial.available() > 0){
    char inChar =Serial.read();
    if(inChar=='h'||inChar=='H'){
      digitalWrite(ledPin,HIGH);
      Serial.print(neme*2,DEC);
      Serial.print("###");
    
     
    }else if (inChar=='I'||inChar=='i'){
          digitalWrite(ledPin,LOW);
          Serial.print(neme,DEC);
          Serial.print("!!!");
          }
          
   }

  
}

