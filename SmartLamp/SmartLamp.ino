#define relay D4 //inisialisasi relay sebagai 4(pin dari relay)
#define pir D2 //inisialisasi pir sebagai 2(pin dari pir)
#define ldr A0 //inisialisasi ldr sebagai A0(pin dari ldr)
int statusldr = 0; //inisialisasi variabel pembacaan ldr

void setup()
{
  pinMode(relay, OUTPUT); //relay(pin 4) sebagai output
  pinMode(pir, INPUT); //pir(pin 2) sebagai input
  pinMode(ldr, INPUT); //ldr(pin A0) sebagai input
  Serial.begin(115200); //inisialisasi serial dengan 115200 baud
}

void loop()
{
  digitalWrite(relay, HIGH); //set relay high(lampu mati)
  statusldr = analogRead(ldr); //membaca data ldr
  //dibawah ini code untuk konversi data ldr ke lux
  float Vout = statusldr * (3.3 / 675); //Vout = inputLDR * (Vin / ADC_maks)
  float RLDR = (1000 * (3.3 - Vout)) / Vout; //RLDR = (Resistor * (Vin - Vout)) / Vout
  statusldr = 500 / (RLDR*0.001); //Lux = 500 / (RLDR * 0.001)
  
  if(digitalRead(pir) == HIGH && statusldr < 200){ //cek kondisi jika ada gerakan(statuspir == HIGH) dan cahaya kurang(statusldr < 200)
    Serial.printf("Lampu Menyala\n"); //output "Lampu Menyala" pada serial
    digitalWrite(relay, LOW); //set relay low(lampu menyala)
    delay(300000); //delay 300000 ms / 300 second / 5 minute
  }
  else{ //jika kondisi diatas tidak terpenuhi
    Serial.printf("Status PIR : %d\n",statuspir); //output nilai pir pada serial
    Serial.printf("Status LDR : %d Lux\n",statusldr); //output nilai ldr pada serial
  }
}
