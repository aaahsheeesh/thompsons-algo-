#include<stdio.h>
#include<conio.h>
#include<string.h>
#define max 20
int nfa[max][4],st=1;
typedef struct r{
int s;
int f;
}re;
re opnd[max];
char opr[max];
int topd=1,top=0;
void pushd(re od){
if(topd==20){
printf("Stack Overflow");
exit(0);
}
topd++;
opnd[topd]=od;
}
re popd(){
re x;
if(topd==-1){
printf("Underflow");
exit(0);
}
x=opnd[topd];
topd--;
return x;
}
void push(char op){
if(top==20){
printf("Stack Overflow");
exit(0);
}
top++;
opr[top]=op;
}
void pop(){
if(top==-1){
printf("Stack Underflow");
exit(0);
}
top--;
}
int preced(char c)
{
int j;
switch(c){
case '#':j=1;
break;
case '/':j=3;
break;
case '.':j=4;
break;
case '*':j=5;
break;
}
return j;
}
void unio(){
re rp,r1,r2;
r2=popd();
r1=popd();
nfa[st][2]=r1.s;
nfa[st][3]=r2.s;
nfa[r1.f][2]=st+1;
nfa[r2.f][2]=st+1;
rp.s=st;
rp.f=st+1;
pushd(rp);
st=st+2;
}
void concat(){
re rp,r1,r2;
r2=popd();
r1=popd();
nfa[r1.f][2]=r2.s;
rp.s=r1.s;
rp.s=r2.s;
pushd(rp);
}
void star(){
re rp,r1;
r1=popd();
nfa[st][2]=r1.s;
nfa[st][3]=st+1;
nfa[r1.f][2]=r1.s;
nfa[r1.f][3]=st+1;
rp.s=st;
rp.f=st+1;
pushd(rp);
st=st+2;
}
void tran(){
char che;
che=opr[top];
pop();
switch(che){
case '/':unio();
break;
case '*':unio();
break;
case '.':unio();
break;
}
}
void eval(char ch){
if(top==0)
push(ch);
else if(ch=='(')
push(ch);
else if(ch==')')
{
while(opr[top]!='('){
tran();
}
pop();
}
else{
while(preced(opr[top])>=preced(ch))
tran();
push(ch);
}}
void state(char cc)
{
re r1;
if(cc=='a'){
nfa[st][0]=st+1;
r1.s=st;
r1.f=st+1;
pushd(r1);
st=st+2;
}
if(cc=='b'){
nfa[st][1]=st+1;
r1.s=st;
r1.f=st+1;
pushd(r1);
st=st+2;
}}
void main(){
char reg[100];
int i,j;
clrscr();
opr[0]='#';
for(i=0;i<=19;i++){
for(j=0;j<=3;j++){
nfa[i][j]=0;
}}
printf("Enter The Regular Expression -->");
}}
gets(reg);
for(i=0;reg[i]!='\0';i++)
{
if(reg[i]=='a'||reg[i]=='b'){
state(reg[i]);
}
else if(reg[i]=='/'||reg[i]=='.'||reg[i]=='*'||reg[i]==')'||reg[i]=='('){
eval(reg[i]);
}
else{
printf("Conversion Not Possible");
exit(0);}}
while(top!=0)
{
tran();
}
printf("\nInitial State==> %d",opnd[topd].s);
printf("\nFinal State==> %d",opnd[topd].f);
printf("\nstate\ta\tb\te1\te2\n");
for(i=1;i<st;i++){
printf("%d",i);
for(j=0;j<4;j++){
if(nfa[i][j]!=0)
printf("\t %d",nfa[i][j]);
else
printf("\t -");
}
printf("\n");
}
getch();
}
