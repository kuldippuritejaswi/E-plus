#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
int YES = 0, NO = 1;
//char lattitude = "", longitude;
String latt="72.14",longi = "82.11"; // temporarily hardcoded, accquiring commented
//string latt,longi;
void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  gsm_init();
}

void loop() {
  if (analogRead(A0) > 10)
  {
    http_init();
    sent_loc();
  }
}

//GSM INITIALISATION IF OK RETURN 'YES'
int gsm_init(void)
{
  int stat = YES;
  unsigned long int count;
  Serial.println("AT");
  char back = Serial.read();
  for (count = 0; back != 'K' && back != 'E'; count++)
  {
    back = Serial.read();
  }
  if (back == 'E')
  {
    stat = NO;
  }
  Serial.println("AT+CREG?");
  back = Serial.read();
  for (count = 0; back != 'K' ; count++) // in trhis case 'E' cannot be checked due to "+CREG" response
  {
    back = Serial.read();
  }
  if (back == 'E' )
  {
    stat = NO;
  }
  Serial.println("AT+CMGF=1");
  back = Serial.read();
  for (count = 0; back != 'K' && back != 'E' ; count++)
  {
    back = Serial.read();
  }
  if (back == 'E' )
  {
    stat = NO;
  }
  Serial.println("AT+CNMI=1,0,0,0,0");
  back = Serial.read();
  for (count = 0; back != 'K' && back != 'E' ; count++)
  {
    back = Serial.read();
  }
  if (back == 'E' )
  {
    stat = NO;
  }
  Serial.println("ATE0");
  back = Serial.read();
  for (count = 0; back != 'K' && back != 'E'; count++)
  {
    back = Serial.read();
  }
  if (back == 'E' )
  {
    stat = NO;
  }
  Serial.println("AT+CSCLK=0");    // to turn off sleepmode
  back = Serial.read();
  for (count = 0; back != 'K' && back != 'E' ; count++)
  {
    back = Serial.read();
  }
  if (back == 'E' )
  {
    stat = NO;
  }
  return stat;
}

// HTTP INITIALISATION IF OK RETURN 'YES'
int http_init()
{
  int stat = YES;
  char back;
  unsigned long int count;
  Serial.println("AT+SAPBR=2,1");  //bearer profile
  back = Serial.read();
  for (count = 0; back != 'K' && back != 'E'; count++)
  {
    back = Serial.read();
  }
  if (back == 'E' )
  {
    stat = NO;
  }
  Serial.println("AT+SAPBR=1,1");
  back = Serial.read();
  for (count = 0; back != 'K' && back != 'E'; count++)
  {
    back = Serial.read();
  }
  if (back == 'E' )
  {
    Serial.println("AT+SAPBR=0,1");
    back = Serial.read();
    for (count = 0; back != 'K' && back != 'E' ; count++)
    {
      back = Serial.read();
    }
    if (back == 'E')
    {
      stat = NO;
    }
    Serial.println("AT+SAPBR=1,1");
    //for(count=0;!Serial.available()&&count<600000;count++);
    back = Serial.read();
    for (count = 0; back != 'K' && back != 'E'; count++)
    {
      back = Serial.read();
    }
    if (back == 'E')
    {
      stat = NO;
    }
  }
  Serial.println("AT+HTTPINIT");// initialise HTTP connection
  back = Serial.read();
  for (count = 0; back != 'K' && back != 'E'; count++) // read until an ERROR/OK recive
  {
    back = Serial.read();
  }
  if (back == 'E') // IF ERROR TERMINATE INITIALISATION AND RE INITIALISE ONE MORE TIME
  {
    Serial.println("AT+HTTPTERM");
    back = Serial.read();
    for (count = 0; back != 'K' && back != 'E'; count++)
    {
      back = Serial.read();
    }
    Serial.println("AT+HTTPINIT");//RE INITIALISATION
    back = Serial.read();
    for (count = 0; back != 'K' && back != 'E'; count++)
    {
      back = Serial.read();
    }
    if (back == 'E')
    {
      stat = NO;
    }
  }
  return stat;
}
//location senting
int sent_loc()
{
  char latt[7];
  char longi[6];
  int i;
  //  for (i = 0; i < 5; i++)    // copying first 6 characters to latt array
  //  {
  //    latt[i] = lattitude[i];
  //  }
  //  latt[i] = '\0';
  //  for (i = 0; i < 4; i++)    // copying first 5 characters to longi array
  //  {
  //    longi[i] = longitude[i];
  //  }
  //  longi[i] = '\0';
   //Serial.println("AT+HTTPPARA=\"URL\",\"http://callambulance.esy.es/abc.php?alat=" + String(latt) + "&long=" + String(longi) + " \"");
  // Serial.println("AT+HTTPPARA=\"URL\",\"http://techant.co.in/ext/botz/p1/pg1.aspx?a=0959&b=07617\"");
  Serial.println("AT+HTTPPARA=\"URL\",\"http://callambulance.esy.es/abc.php?alat=0959&along=07617999\"");
  char back = Serial.read();
  while (back != 'E' && back != 'K')   // wait until a ERROR/OK return
  {
    back = Serial.read();
  }
  if (back == 'E')   // if error is got then retun NO
  {
    return NO;
  }
  else               // if OK is got then retun YES
  {
    Serial.println("AT+HTTPPARA=\"CID\",1");
    char back = Serial.read();
    while (back != 'E' && back != 'K')   // wait until a ERROR/OK return
    {
      back = Serial.read();
    }
    if (back == 'E')   // if error is got then retun NO
    {
      return NO;
    }
    else
    {
      Serial.println("AT+HTTPACTION=0");
      char back = Serial.read();
      while (back != 'E' && back != 'K')   // wait until a ERROR/OK return
      {
        back = Serial.read();
      }
      if (back == 'E')   // if error is got then retun NO
      {
        return NO;
      }
      else
      {
        return YES;
      }
    }
  }
}
// HTTP TERMINATION
void http_termination()
{
  char back;
  Serial.println("AT+HTTPTERM");
  back = Serial.read();
  for (int i = 0; back != 'K' && back != 'E'; i++)
  {
    back = Serial.read();
  }
}



void gsm_msg_delete(String loc)
{
  //loc STORE LOCATION ADRESS
  if (Serial.available())// to read out previou responses before new command
  {
    int m = 0;
    while (Serial.available() && m < 5000) // to read out null values
    {
      char nul = Serial.read();
      m++;
    }
  }

  Serial.print("AT+CMGD=");
  Serial.println(loc);
  delay(2);
  char back = Serial.read();
  for (int count = 0; back != 'K' && back != 'E' && count < 500; count++ )
  {
    delay(2);
    back = Serial.read();
  }
  delay(200);
}

//READ MESSAGE


//-----------------GPS FUNCTIONS------------------//
//void gps_read()
//{
//  char a;// variable to read characters
//  int coma_count;// variable to store ',' count in gps data reading
//  if (mySerial.available()) // only enter if there is gps data available
//  {
//    for (a = mySerial.read(); a != '$' && mySerial.available(); a = mySerial.read()); // wait for '$' symbol that appear in first of a gps data
//    delay(2);// small delay needed beteween each character read
//    a = mySerial.read(); // read gps Serial data through 'gps' software serial
//    if (a == 'G') ///////// the following section is to find "CPGGA" other datas neglected
//    {
//      delay(2);
//      a = mySerial.read();
//      if (a == 'P')
//      {
//        delay(2);
//        a = mySerial.read();
//        if (a == 'G')
//        {
//          delay(2);
//          a = mySerial.read();
//          if (a == 'G')
//          {
//            delay(2);
//            a = mySerial.read();
//            if (a == 'A') // if "CPGGA" detected read the following lattitude and longittude
//            {
//              lattitude = ""; // CLEAR "NO DATA" FROM STRING
//              longitude = ""; // CLEAR "NO DATA" FROM STRING
//              for (int i = 0, coma_count = 0; i < 47; i++) // only need 47 charater to be read to get lattitude and longittude
//              {
//                delay(2);
//                a = mySerial.read();
//                if (a == ',') // updating comma count
//                {
//                  coma_count++;
//                }
//                else if (coma_count >= 2 && coma_count <= 3) // the data between 2nd comma and 4 th comma is lattitude
//                {
//                  lattitude += a; // store lattitude data
//                }
//                else if (coma_count >= 4 && coma_count <= 5) // the data between 4th comma and 6 th comma is longitude
//                {
//                  longitude += a; //store longittude data
//                }
//              }
//            }
//          }
//        }
//      }
//    }
//  }
//}

