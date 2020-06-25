#include <SArduino.h>

#define PRIVATE 0
#define PUBLIC 1

void dump(byte* buf, int len) {
  int i;
  for(i=0; i<len; i++) {
    Serial.print((char)buf[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600, SERIAL_8E2);

  if(!Init_SE()){
    Serial.println("SE Connection Failure");
  }

  int key_num = 0x0;
  int verification = 1;
  
  byte plain_data[] = "나는 2018년 6월 1일에 홍길동에게 100만원을 입금하였다";
  int plain_len = strlen(plain_data);

  byte digest[32];
  int digest_len = 32;

  byte enc_data[128];
  int enc_len;

  byte dec_data[64];
  int dec_len;

  Serial.print("plain data: ");
  dump(plain_data, plain_len);

  if(SHA_256(plain_data, plain_len, digest, &digest_len)) {
    Serial.print("digest: ");
    dump(digest, digest_len);
  }

  else {
    Serial.println("SHA_256 Failure");
  }

  if(!Generate_RSA1024Key(key_num)) 
    Serial.println("Set RSA1024 Key Pair Failure");

  if(Encrypt_RSA1024(key_num, PUBLIC, digest, digest_len, enc_data, &enc_len)) {
    Serial.print("enc_data: ");
    dump(enc_data, enc_len);
  }

  else 
    Serial.println("Encrypt plain_data Failure");

  if(Decrypt_RSA1024(key_num, PRIVATE, enc_data, enc_len, dec_data, &dec_len)) {
    Serial.print("dec_data: ");
    dump(dec_data, dec_len);
  }

  else
    Serial.println("Decrpyt enc_data Failure");

  for(int i=0; i<dec_len; i++) {
    if(digest[i] != dec_data[i]) {
      Serial.println("Verication Fail");
      verification = 0;
      break;
    }
  }

  if(verification == 1) 
    Serial.println("Veiricaion Success!");
}

void loop() {
  
}
