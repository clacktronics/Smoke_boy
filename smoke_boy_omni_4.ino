int smoke_delay = 1000;
int smoke_end = 5000;

int 
trigger_smoke,
pir_on,
door_open,
smoke_machine_status,
test_button,
wait_for_pir,
wait_for_door,
button_pressed,
start_smoke,
test;

unsigned long trigger_time;

void setup() {
  
  pinMode(12,INPUT); // Smoke machine ready
  digitalWrite(12,1); // Pull up pin 12 for LDR
  pinMode(2,OUTPUT); // Smoke Machine Ready indicator
  
  pinMode(11,INPUT); // PIR sensor
  pinMode(3,OUTPUT); // PIR activated indicator
  
  pinMode(10,INPUT); // Door reed switch
  digitalWrite(10,1); // Pull up pin 10 for reed switch
  pinMode(4,OUTPUT); // Door Activated Indicator
  
  pinMode(9, OUTPUT); // Smoke machine trigger
  pinMode(5, OUTPUT); // Smoke Machine Activated indicator
  
  pinMode(6, INPUT); // Test Button
  digitalWrite(6,1); // Pull up pin 6 for button
  
  digitalWrite(12,1); // Pull up so detecting LDR will pull input down
  digitalWrite(10,1); // Pull up for reed switch in door sensor
  
  pinMode(13,OUTPUT);
  digitalWrite(13,0);
  
}

void loop() {

pir_on = digitalRead(11);
door_open = digitalRead(10);
smoke_machine_status = digitalRead(12);
test_button = digitalRead(6);

digitalWrite(3,pir_on);
digitalWrite(4,door_open);
//digitalWrite(5,!test_button);
digitalWrite(2,!smoke_machine_status);

if(door_open & !pir_on & !wait_for_door & !wait_for_pir) {wait_for_door = 1; wait_for_pir = 1;}

if(door_open & pir_on & wait_for_door & !wait_for_pir) {wait_for_door = 1; wait_for_pir = 1;}

if(door_open & pir_on & !wait_for_door & !wait_for_pir) {wait_for_door = 1; wait_for_pir = 1; trigger_smoke = 1; }

if(!pir_on) { wait_for_pir = 0; }
if(!door_open ) {wait_for_door = 0;}

if(!test_button & !button_pressed ){trigger_smoke = 1; button_pressed = 1;}
if(test_button){button_pressed = 0;}



if( !smoke_machine_status &  !wait_for_door & trigger_smoke ) {trigger_smoke = 0; trigger_time = millis(); start_smoke = 1; }

if(start_smoke & millis() - trigger_time >= smoke_delay & millis() - trigger_time < smoke_end){digitalWrite(5,1); digitalWrite(9,1);}

if(start_smoke & millis() - trigger_time >= smoke_end) {digitalWrite(5,0); digitalWrite(9,0); start_smoke = 0;}

delay(10);


}
