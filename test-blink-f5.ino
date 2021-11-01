#include <Ticker.h> //witty cloud стенд частот для проверки счетчика импульсов
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#ifndef APSSID
#define APSSID "boxfreq11111111"
#define APPSK  "11111111"
#endif //Монитор для телефона/планшета показівающий переданнв COMпорт данные
const char *ssid = APSSID;
const char *password = APPSK;
const byte DNS_PORT = 53;
DNSServer dnsServer;
IPAddress apIP(192, 168, 4, 1);
ESP8266WebServer server(80);
const int secrefresh=10; //обновление страницы
String teststr="";
unsigned long t=10,f,k=512;// по умолчанию 10 мкс (10 Гц), меандр, длительность имульса равна скважности k=512 (50%)
byte k1,kn,kn1,kn2;
int enled3,enled4,enled5,enled6,drive,drive0;
Ticker blink1;Ticker blink2;Ticker blink3;Ticker blink4;Ticker blink5;Ticker blink6;Ticker blink7;Ticker blink8;Ticker blink9;
const int led1 = 16; 
const int led2 = 14; 
const int led3 = 12; //зеленый
const int led4 = 13; //синий
const int led5 = 15; //красный
const int led6 = 2; ////синий  мелкий 
const int led7 = 0; //
const int led8 = 4; //
const int led9 = 5; //
int led6_ms=1000;
void setup() { // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("setup start");
pinMode(led1, OUTPUT);  pinMode(led2, OUTPUT);  pinMode(led3, OUTPUT);  pinMode(led4, OUTPUT);  pinMode(led5, OUTPUT);
pinMode(led6, OUTPUT);  pinMode(led7, OUTPUT);  pinMode(led8, OUTPUT);  pinMode(led9, OUTPUT);
// 400-2.5Гц  // 200-5Гц  // 100-10Гц
blink1.attach_ms(10,blink1set);blink2.attach_ms(25,blink1set2); 
blink3.attach_ms(200,blink1set3);blink4.attach_ms(1000,blink1set4);blink5.attach_ms(200,blink1set5);blink6.attach_ms(led6_ms,blink1set6);  //диоды
blink7.attach_ms(2000,blink1set7);blink8.attach_ms(4000,blink1set8);blink9.attach_ms(10000,blink1set9);
enled6=1; //включаем синий маленький
/* You can remove the password parameter if you want the AP to be open. */
WiFi.mode(WIFI_AP); WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));WiFi.softAP(ssid, password);
// if DNSServer is started with "*" for domain name, it will reply with
// provided IP to all DNS request
dnsServer.start(DNS_PORT, "*", apIP); 
server.onNotFound([]() {server.send(200, "text/html", SendHTML("ok","ok","ok","ok"));}); 
server.on("/actin",getaction);
server.begin();
Serial.println("setup OK"); 
}
void loop() {
// put your main code here, to run repeatedly://Timer1.initialize(t); // период //Timer1.pwm(9, k); // k - коэффициент заполнения 0-1023. Сигнал снимаем с выхода 9
dnsServer.processNextRequest();   
server.handleClient();
}
void blink1set(){//периодически мигаем 
//if (digitalRead(led1)==HIGH) digitalWrite(led1, LOW); else digitalWrite(led1, HIGH);
digitalWrite(led1,!(digitalRead(led1)));}
void blink1set2(){//периодически мигаем 
//if (digitalRead(led2)==HIGH) digitalWrite(led2, LOW); else digitalWrite(led2, HIGH);
digitalWrite(led2,!(digitalRead(led2)));}
void blink1set3(){//периодически мигаем 
//if (digitalRead(led3)==HIGH) digitalWrite(led3, LOW); else digitalWrite(led3, HIGH);
if(enled3==1)digitalWrite(led3,!(digitalRead(led3)));}
void blink1set4(){//периодически мигаем 
//if (digitalRead(led4)==HIGH) digitalWrite(led4, LOW); else digitalWrite(led4, HIGH);
if(enled4==1)digitalWrite(led4,!(digitalRead(led4)));}
void blink1set5(){//периодически мигаем 
//if (digitalRead(led5)==HIGH) digitalWrite(led5, LOW); else digitalWrite(led5, HIGH);
if(enled5==1)digitalWrite(led5,!(digitalRead(led5)));}
void blink1set6(){//периодически мигаем //if (digitalRead(led6)==HIGH) digitalWrite(led6, LOW); else digitalWrite(led6, HIGH);
if(enled6==1)digitalWrite(led6,!(digitalRead(led6)));}
void blink1set7(){//периодически мигаем
digitalWrite(led7,!(digitalRead(led7)));}
void blink1set8(){//периодически мигаем красным//if (digitalRead(led8)==HIGH) digitalWrite(led8, LOW); else digitalWrite(led8, HIGH);
digitalWrite(led8,!(digitalRead(led8)));}
void blink1set9(){//периодически мигаем красным
//if (digitalRead(led9)==HIGH) digitalWrite(led9, LOW); else digitalWrite(led9, HIGH);
digitalWrite(led9,!(digitalRead(led9)));}
void getaction() //обработчик
{//теоретически аргумент всегда должен быть один
Serial.println("action get");
String message = "Number of args received:";
message += server.args();      // получить количество параметров
message += "\n";               // переход на новую строку
for (int i = 0; i < server.args(); i++) 
{
int arg=server.arg(i).toInt();
Serial.println(arg);
switch (arg){
case 1:
led6_ms=led6_ms/2;
blink6.attach_ms(led6_ms,blink1set6); 
break;
case 10:
blink6.attach_ms(led6_ms,blink1set6); 
break;
case 100:
blink6.attach_ms(led6_ms,blink1set6); 
break;
case 1000:
blink6.attach_ms(led6_ms,blink1set6); 
break;
case -1://on/off
enled6=1-enled6;
digitalWrite(led6,LOW);
break;
case 0://reset
led6_ms=1000;
blink6.attach_ms(led6_ms,blink1set6); 
break;
case -10://red
enled5=1-enled5;
digitalWrite(led5,LOW);
break;
case -12://green
enled3=1-enled3;
digitalWrite(led3,LOW);
break;
case -13://blue
enled4=1-enled4;
digitalWrite(led4,LOW);
break;
}
    //message += "Arg nº" + (String)i + " –> "; // добавить текущее значение счетчика
    //message += server.argName(i) + ": ";      // получить имя параметра
    //message += server.arg(i) + "\n";          // получить значение параметра
  } 

 // server.send(200, "text/plain", message);    // ответить на HTTP запрос
 server.send(200, "text/html", SendHTML("ok","ok","ok","ok"));
}
String SendHTML(String r,String g,String b,String bs)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  //ptr +="<head> <meta http-equiv='refresh' content='11'/>";
  ptr +="<head> <meta http-equiv='refresh' content='" + String(secrefresh) + "'/>";
  ptr +="<title>boxfreq</title>\n";
//  ptr +="<body><H1>";
 ////////////////////////
//ptr +="<p>box_freq</p><form id=\"form1\" name=\"form1\" method=\"get\" action=\"http://192.168.4.1/action\">";
ptr +="<body><H1> <p>box_freq</p> <form id=\"form1\" name=\"form1\" method=\"get\" action=\"http://192.168.4.1/actin\">   <table width=\"99%\" border=\"1\">     <tr>       <td width=\"24%\" bgcolor=\"#33FFFF\">pin11 =&gt;s2</td>       <td width=\"76%\"><a href=\"http://192.168.4.1/actin?add=1\">+1 Hz</a></td>     </tr>     <tr>       <td>now= {}ms</td>       <td>or {} Hz</td>     </tr>     <tr>       <td>&nbsp; </td>       <td><a href=\"http://192.168.4.1/actin?add=10\">+10 Hz</a></td>     </tr>     <tr>       <td><a href=\"http://192.168.4.1/actin?add=100\">+100 Hz</a></td>       <td>&nbsp;</td>     </tr>     <tr>       <td>&nbsp;</td>       <td><a href=\"http://192.168.4.1/actin?add=1000\">+1000 Hz</a></td>     </tr>     <tr>       <td><a href=\"http://192.168.4.1/actin?add=-1\">On/Off></a></td>       <td>&nbsp;</td>     </tr>         <tr>       <td>reset to 1Hz</td>       <td><a href=\"http://192.168.4.1/actin?add=0\">**reSet**</a></td>     </tr>     <tr>       <td bgcolor=\"#FFaaaa\">pin10=&gt;s15</td>       <td bgcolor=\"#FFaaaa\">20 Hz</td>     </tr>     <tr>       <td bgcolor=\"#FF0000\">&nbsp;</td>       <td bgcolor=\"#FF0000\"><a href=\"http://192.168.4.1/actin?add=-10\">xRed/on_Red</a></td>     </tr>     <tr>       <td bgcolor=\"#aaFFaa\">pin6=&gt;s12</td>       <td bgcolor=\"#aaFFaa\">5 Hz</td>     </tr>     <tr>       <td bgcolor=\"#00FF00\">&nbsp;</td>       <td bgcolor=\"#00FF00\"><a href=\"http://192.168.4.1/actin?add=-12\">xGree/on_Green</a></td>     </tr>     <tr>       <td bgcolor=\"#aaaaFF\">pin7=&gt;s13</td>       <td bgcolor=\"#aaaaFF\">1 Hz</td>     </tr>     <tr>       <td bgcolor=\"#0000FF\">&nbsp;</td>       <td bgcolor=\"#CCFFFF\"><a href=\"http://192.168.4.1/actin?add=-13\">xBlue/on_Blue</a></td>     </tr>   </table> </form> <p>&nbsp;</p> <table width=\"99%\" border=\"1\">   <tr>     <td align=\"right\">&nbsp;</td>     <td>&nbsp;</td>     <td width=\"33%\" bgcolor=\"#333333\">&nbsp;</td>     <td>&nbsp;</td>     <td>&nbsp;</td>   </tr>   <tr>     <td align=\"right\">1</td>     <td>&nbsp;</td>     <td width=\"33%\" bgcolor=\"#333333\">&nbsp;</td>     <td>&nbsp;</td>     <td>16</td>   </tr>   <tr>     <td align=\"right\">2</td>     <td>&nbsp;</td>     <td width=\"33%\" bgcolor=\"#333333\">&nbsp;</td>     <td>&nbsp;</td>     <td>15</td>   </tr>   <tr>     <td align=\"right\">3</td>     <td>&nbsp;</td>     <td width=\"33%\" bgcolor=\"#333333\">&nbsp;</td>     <td>10kHz</td>     <td>14(s5)</td>   </tr>   <tr>     <td align=\"right\">4(s16)</td>     <td>100Hz</td>     <td width=\"33%\" bgcolor=\"#333333\">&nbsp;</td>     <td>5kHz</td>     <td>13(s4)</td>   </tr>   <tr>     <td align=\"right\">5(s14)</td>     <td>40Hz</td>     <td width=\"33%\" bgcolor=\"#333333\">&nbsp;</td>     <td>1kHz</td>     <td>12(s0)</td>   </tr>   <tr>     <td align=\"right\" bgcolor=\"#00FF00\"><strong>6(s12)</strong></td>     <td bgcolor=\"#00FF00\">5Hz</td>     <td width=\"33%\" bgcolor=\"#333333\">&nbsp;</td>     <td bgcolor=\"#33FFFF\">1Hz</td>     <td bgcolor=\"#33FFFF\">11(s2)</td>   </tr>   <tr>     <td align=\"right\" bgcolor=\"#0099FF\"><strong>7(s13)</strong></td>     <td bgcolor=\"#0099FF\">1Hz</td>     <td width=\"33%\" bgcolor=\"#333333\">&nbsp;</td>     <td bgcolor=\"#FF0000\">20Hz</td>     <td bgcolor=\"#FF0000\"><strong>10(s15)</strong></td>   </tr>   <tr>     <td align=\"right\" bgcolor=\"#FFFF00\"><strong>8(VCC)</strong></td>     <td bgcolor=\"#FFFF00\"><strong>+3.3V</strong></td>     <td width=\"33%\" bgcolor=\"#333333\">&nbsp;</td>     <td><strong>GND</strong></td>     <td bgcolor=\"#666666\"><strong>9(GND)</strong></td>   </tr>   <tr>     <td align=\"right\">&nbsp;</td>     <td>&nbsp;</td>     <td width=\"33%\" bgcolor=\"#333333\">&nbsp;</td>     <td>&nbsp;</td>     <td>&nbsp;</td>   </tr> </table> <p>&nbsp;</p> </body>";
ptr +="</H1></body>\n";ptr +="</html>\n";
  return ptr;
}
