%enabling pins and header files
#include<at89x52.h>
#include<string.h>
#define LCD P0
sbit rs=P1^0;//RESET
sbit rw=P1^1;//READ/WRITE
sbit en=P1^2;//ENABLe
sbit in1=P2^0;
sbit in2=P2^1;

void delay(unsigned int ms)
{
unsigned int i,j;
for(i=0;i<=ms;i++)
for(j=0;j<=750;j++);
}

void lcd_cmd(unsigned char a)
{
LCD =a;
rs=0;
rw=0;
en=1;
delay(1);
en=0;
}

void lcd_init(void)
{
delay(1);
lcd_cmd(0x38);
lcd_cmd(0x0c);
lcd_cmd(0x01);
lcd_cmd(0x06);
lcd_cmd(0x80);
}

void lcd_clear(void)
{
lcd_cmd(0x01);
lcd_cmd(0x80);
}

void lcd_data(unsigned char ch) //convertr the integer value to writting format
{
LCD=(int)ch;
rs=1;
rw=0;
en=1;
delay(1);
en=0;
}

void lcd_print(char s[])
{
int i=0;
for(i=0;s[i]!='\0';i++)
lcd_data(s[i]);
delay(50);
}

%intialsing uart channel
void uart_init(void)
{
SCON=0x50;//MODE 1..8 BIT DATA,..1 STOP BIT,..1 START BIT
TMOD=0x20;//TIMER 1....MODE 2...8 BIT AUTO RELOAD
TL1 = 0xFD;
TH1=0xFD;//BAUD RATE 9600
TR1 = 1;
}

void number(int a)
{
int r=a;
int i;
if (r==0)
lcd_data(48);
else{
while(r)
{
char c[17];
for(i=0;r!=0;i++)
{
c[i]=(char)((r%10)+48); // converting number to character
r=r/10; //
}
for(i=i-1;i!=-1;i--)
lcd_data(c[i]); // display the frequency on lcd
}
}
}

unsigned int b1=60,b2=40,b3=20,b4=0;



void main()
{

unsigned char RF[12];
unsigned int k=0;
lcd_init();
lcd_print("LCD is ready");
delay(500);
lcd_clear();
uart_init();
lcd_print("UART is ready");
delay(500);
lcd_clear();
lcd_cmd(0x81);
lcd_print("Automatic Toll");
lcd_cmd(0xc2);
lcd_print("Gate System");
delay(500);

P1=0x07;
P3=0x11;
P2=0x00;

while(1)
{

lcd_clear();
lcd_cmd(0x82);
lcd_print("Place the tag");
lcd_cmd(0xc2);
lcd_print("before reader");
delay(50);

for(k=0;k<12;k++)
{
while(!RI);
RF[k]=SBUF;
RI=0;
}
lcd_clear();

if(RF[6]=='6')
{
if(b1>=20){
b1=b1-20;
in1=0;
in2=1;
delay(40);
in1=0;
in2=0;

lcd_clear();
lcd_print("GATE OPENED");
delay(50);
lcd_clear();
lcd_print("Balance is");
lcd_cmd(0xc2);
number(b1);

delay(500);

in1=1;
in2=0;
delay(40);
in1=0;
in2=0;


lcd_clear();
lcd_print("GATE CLOSED");
delay(500);}
else
{
lcd_clear();
delay(500);
lcd_print("LOW BALANCE");
delay(100);
lcd_clear();
lcd_cmd(0x82);
lcd_print("Divert to Lane2 ");
lcd_cmd(0xc2);
lcd_print("& pay manually");
delay(200);

}
}

else if(RF[8]=='u')
{
if(b2>=20){
b2=b2-20;
in1=0;
in2=1;
delay(40);
in1=0;
in2=0;

lcd_clear();
lcd_print("GATE OPENED");
delay(50);
lcd_clear();
lcd_print("Balance is");
lcd_cmd(0xc2);
number(b2);

delay(500);

in1=1;
in2=0;
delay(40);
in1=0;
in2=0;


lcd_clear();
lcd_print("GATE CLOSED");
delay(500);}
else
{
lcd_clear();
delay(500);
lcd_print("LOW BALANCE");
delay(100);
lcd_clear();
lcd_cmd(0x82);
lcd_print("Divert to Lane2 ");
lcd_cmd(0xc2);
lcd_print("& pay manually");
delay(200);
}
}

else if(RF[9]=='s')

{
if(b3>=20){
b3=b3-20;
in1=0;
in2=1;
delay(40);
in1=0;
in2=0;

lcd_clear();
lcd_print("GATE OPENED");
delay(50);
lcd_clear();
lcd_print("Balance is");
lcd_cmd(0xc2);
number(b3);

delay(500);

in1=1;
in2=0;
delay(40);
in1=0;
in2=0;



lcd_clear();
lcd_print("GATE CLOSED");
delay(500);}
else
{
lcd_clear();
delay(500);
lcd_print("LOW BALANCE");
delay(100);
lcd_clear();
lcd_cmd(0x82);
lcd_print("Divert to Lane2 ");
lcd_cmd(0xc2);
lcd_print("& pay manually");
delay(200);

}
}

else if(RF[6]=='5')
{
if(b4>=20){
b4=b4-20;
in1=0;
in2=1;
delay(40);
in1=0;
in2=0;

lcd_clear();
lcd_print("GATE OPENED");
delay(50);
lcd_clear();
lcd_print("Balance is");
lcd_cmd(0xc2);
number(b4);

delay(500);

in1=1;
in2=0;
delay(40);
in1=0;
in2=0;


lcd_clear();
lcd_print("GATE CLOSED");
delay(500);}
else
{
lcd_clear();
delay(500);
lcd_print("LOW BALANCE");
delay(100);
lcd_clear();
lcd_cmd(0x82);
lcd_print("Divert to Lane2 ");
lcd_cmd(0xc2);
lcd_print("& pay manually");
delay(200);

}
}

else
{
delay(10);
lcd_clear();
lcd_print("INVALID CARD");
delay(500);
}

}
}
