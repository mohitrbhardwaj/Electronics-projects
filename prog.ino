
const int lbPin = 2;
const int rbPin = 3;

const int trigPin1 = 48;
const int echoPin1 = 49;

const int trigPin2 = 25;
const int echoPin2 = 24;

const int trigPin3 = 10;
const int echoPin3 = 11;

const int trigPin4 = 4;
const int echoPin4 = 5;

const int ledPin = 10;
bool left=false,right=false,up=false,down=false,firsttime=true;

long  leftb;
long  leftbState = 0;
long  statusbl = 0;

long  rightb;
long  rightbState = 0;
long  statusbr = 0;

long duration1,duration2,duration3,inches1,inches2,inches3,cm1,cm2,cm3;
long downq,leftq,rightq,upq;
long  x,y,a=700,b=1200,prevx,prevy;
  
void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(lbPin, INPUT);
  pinMode(rbPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(trigPin4, OUTPUT);
  
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(echoPin4, INPUT);
  
  Serial.begin(9600);
}

void loop()
{
  
  ultrasonic();
  if(x-prevx>10||prevx==0)
  {
    right=true;
    left=false;
    rightq=x-prevx;
    delayMicroseconds(2);
  }
  else if(x-prevx<-10||x==0)
  {
    left=true;
    right=false;
    leftq=prevx-x;
    delayMicroseconds(2);
  }
  else
  {
    left=false;
    right=false;
    delayMicroseconds(2);
  }
  if(y-prevy>10||prevy==0)
  {
    up=true;
    down=false;
    upq=y-prevy;
    delayMicroseconds(2);
  }
  else if(y-prevy<-10||y==0)
  {
    down=true;
    up=false;
    downq=prevy-y;
    delayMicroseconds(2);
  }
  else
  {
    up=false;
    down=false;
    delayMicroseconds(2);
  }
  if(right == true)
  {
    if(rightq>20)
    {
      Serial.println("right"+String(rightq));
    }
    delayMicroseconds(50);
  };

  if(left == true)
  {
    if(leftq>20)
    {
      Serial.println("left"+String(leftq));
    }
    delayMicroseconds(50);
  };

  if(up == true)
  {
    if(upq>20)
    {
      Serial.println("up"+String(upq));
    }    
    delayMicroseconds(50);
  };

  if(down == true)
  {
    if(downq>20)
    {
      Serial.println("down"+String(downq));
    }    
    delayMicroseconds(50);
  };

  leftb = digitalRead(lbPin);
  if(leftb != leftbState && statusbl==0)
  {
    statusbl = 1;
    Serial.println("lb");
    delayMicroseconds(50);

  }
  else if (leftb != leftbState && statusbl==1)
  {
    statusbl = 0;
    Serial.println("lbr");
    delayMicroseconds(50);
  }
  leftbState = leftb;

  rightb = digitalRead(rbPin);
  if(rightb != rightbState && statusbr == 0)
  {
    statusbr = 1;
    Serial.println("rb");
    delayMicroseconds(50);
  } 
  else if (rightb != rightbState && statusbr == 1)
  {
    statusbr = 0;
    Serial.println("rbr");
    delayMicroseconds(50);
  }
  rightbState = rightb;

}
void txrx()
{
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(5);
  
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin4, LOW);

  duration1 = pulseIn(echoPin1, HIGH);

  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(5);
  
  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin4, LOW);

  duration2 = pulseIn(echoPin2, HIGH);

  digitalWrite(trigPin3, LOW);
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(5);
  
  digitalWrite(trigPin3, LOW);
  digitalWrite(trigPin4, LOW);

  duration3 = pulseIn(echoPin3, HIGH);
  
}
void ultrasonic()
{
    txrx();
   cm1 = duration1 / 29.1 ;
   cm2 = duration2 / 29.1 ;
   cm3 = duration3 / 29.1 ;
  
  long ra=(long)cm1;
  long rb = (long)cm2;
  long rc = (long)cm3;
  if(firsttime==false)
  {
    prevx=x;
    prevy=y;
  }
  y=(((rb*rb)-(ra*ra))/(2*a)); 
  if(y>700)
  {
    y=700;
  }
  x=(((ra*ra)-(rc*rc))/(2*b));
  if(x>1200)
  {
    x=1200;
  }
  if(firsttime==true)
  {
    firsttime=false;
    if(x>10||x<-10)
    {
      prevx=x-10;
    }
    else
    {
      prevx=0;
    }
    if(y>10||y<-10)
    {
      prevy=y-10;
    }
    else
    {
      prevy=0;
    }
 }
 delay(100);
}
