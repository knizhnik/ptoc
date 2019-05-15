{$N+}
uses crt,graph;
const
   eps: double=1e-8{cm/s};
   del: double=1e-5{cm};
   alp: double=0.975;
   height: double=8{cm};
   g: double=980{cm/s^2};
   d: double=0.1{cm};
   w: double=200{s-1};
   A: double=-0.2{cm};
   n=69;
   Nimpact: longint=500000;
type
   mas1=array[1..100] of double;
   mas2=array[1..100] of integer;
var
   xn,vn,AddXn,Addvn2	 : mas1;
   Xnav,Vn2av		 : mas1;
   t,delta01,delta	 : double;
   ygr1,ygr2,ygr3,ygr4	 : mas2;
   k,rad		 : integer;
   l			 : longint;
   maxx,maxy,ygrp1,ygrp2 : integer;
   title1		 : string;
   ps0,ps1,pc0,pc1	 : pointer;
   {---------------------------------------------------------------------}
function x0(t : double) : double;
begin
   x0:=A*sin(w*t);
end;

function v0(t : double) : double;
begin
   v0:=A*w*cos(w*t);
end;
{---------------------------------------------------------------------}
procedure init;
var 
   i : integer;
begin
   title1:='  n     <Xn>    <Vn^2>     Vn      Xn';
   t:=0;
   for i:=1 to n do
   begin
      xn[i]:=d/2+2*del+2*(d/2+2*del)*(i-1);
      vn[i]:=0;
      AddXn[i]:=0;
      AddVn2[i]:=0;
   end;
end;
   {-----------------------------------------------------------------}
procedure initgr;
var
   gd,gm : integer;
   error : integer;
begin
   gd:=detect;
   initgraph(gd,gm,'D:\BP\BGI');
   error:=graphresult;
   if error<>grOK then
   begin
      writeln(grapherrormsg(error));
      readln;
      halt;
   end;
   cleardevice;
   setbkcolor(blue);
end{initgr};
   {-------------------------------------------------------------------}
procedure newton(tt1 : double; var t2 : double);
var
   f,derf : double;
   p	  : integer;
begin
   for p:=1 to 10 do
   begin
      f:=-x0(t+tt1)+xn[1]+vn[1]*tt1-g*sqr(tt1)/2-d/2;
      derf:=-v0(t+tt1)+vn[1]-g*tt1;
      tt1:=tt1-f/derf;
   end;
   t2:=tt1;
end{newton};
   {--------------------------------------------------------------------}
procedure predict1;
var
   tf,t1,dt    : double;
   dx0,dx0init : double;
begin
   t1:=0;
   dx0init:=-x0(t)+xn[1]-d/2;
   dt:=1/(1000*w);
   repeat
   begin
      repeat
	 t1:=t1+dt;
	 dx0:=-x0(t+t1)+xn[1]+vn[1]*t1-g*sqr(t1)/2-d/2;
      until dx0<0;
      newton(t1,delta01);
   end;
   until delta01>0;
end{predict1};
   {---------------------------------------------------------------------}
procedure change;
var
   vnold : double;
begin
   if k=0 then
   begin
      vn[1]:=-alp*vn[1]+2*v0(t);
      xn[1]:=x0(t)+d/2+del;
   end
   else
   begin
      vnold:=vn[k+1];
      vn[k+1]:=-1/2*((alp-1)*vn[k+1]+vn[k]*(-1-alp));
      vn[k]:=1/2*((alp+1)*vnold+vn[k]*(1-alp));
   end;
end{change};
   {---------------------------------------------------------------------}
procedure re_count;
var
   i : integer;
begin
   if delta>0 then
   begin
      for i:=1 to n do
      begin
	 xn[i]:=xn[i]+vn[i]*delta-g*sqr(delta)/2;
	 vn[i]:=vn[i]-g*delta;
      end;
      for i:=2 to n do
      begin
	 if xn[i]<(xn[i-1]+d) then xn[i]:=xn[i-1]+d+del;
      end;
      t:=t+delta;
      change;
      if (k=1) or (k=0) then
	 predict1
      else
	 delta01:=abs(delta01-delta)
   end;
end{re-count};
   {---------------------------------------------------------------------}
procedure predict;
var
   delta1 : double;
   i	  : integer;
begin
   delta:=1e25;
   for i:=1 to n-1 do
   begin
      if vn[i]<>vn[i+1] then
	 delta1:=(abs(xn[i+1]-xn[i]-d))/(vn[i]-vn[i+1])
      else
	 delta1:=1e25;
      if (delta1>0) and (delta1<delta) then
      begin
	 delta:=delta1;
	 k:=i;
      end;
   end;
   if (k>0) and (abs(vn[k+1]-vn[k])<eps) and (abs(xn[k+1]-xn[k]-d)<del/10) then
   begin
      vn[k+1]:=vn[k];
      delta:=0;
   end;
   if delta>delta01 then
   begin
      delta:=delta01;
      k:=0;
   end;
end{predict};
   {----------------------------------------------------------------}
procedure mean;
var
   i : integer;
begin
   for i:=1 to n do
   begin
      AddXn[i]:=AddXn[i]+Xn[i]*delta;
      AddVn2[i]:=AddVn2[i]+sqr(Vn[i])*delta;
      Xnav[i]:=AddXn[i]/t;
      Vn2av[i]:=AddVn2[i]/t;
   end;
end;{mean}
   {-----------------------------------------------------------------}
procedure drawax;
var
   i,j	: integer;
   size	: integer;
   s1	: string;
begin
   setcolor(white);
   maxx:=getmaxx;
   maxy:=getmaxy;
   size:=Imagesize(maxx-220,maxy-50,maxx-130,maxy-40);
   getmem(ps0,size);
   getimage(maxx-220,maxy-50,maxx-130,maxy-40,ps0^);
   setlinestyle(solidln,$AAA,normwidth);
   rectangle(6,6,maxx-6,maxy-6);
   rectangle(3,3,maxx-3,maxy-3);
   settextstyle(defaultfont,horizdir,1);
   line(maxx-120,50,maxx-120,maxy-50);
   line(maxx-220,maxy-50,maxx-20,maxy-50);
   for j:=0 to 10 do
      line(maxx-112,round((maxy-100)*j/10)+50,maxx-128,round((maxy-100)*j/10)+50);
   for j:=1 to 20 do
      line(round(10*j)+maxx-220,maxy-50,round(10*j)+maxx-230,maxy-40);
   str(height:8,s1);
   s1:='H='+s1+' cm';
   settextstyle(defaultfont,vertdir,1);
   outtextxy(maxx-95,50,s1);
   settextstyle(defaultfont,horizdir,1);
   ygrp1:=maxy-50;
   getmem(ps1,size);
   getimage(maxx-220,maxy-50,maxx-130,maxy-40,ps1^);

   rad:=round(d/(2*height)*(maxy-100));
   size:=Imagesize(maxx-200-rad,maxy-100-rad,maxx-200+rad,maxy-100+rad);
   getmem(pc0,size);
   getimage(maxx-200-rad,maxy-100-rad,maxx-200+rad,maxy-100+rad,pc0^);
   setcolor(red);
   setfillstyle(1,12);
   fillellipse(maxx-200,maxy-100,rad,rad);
   getmem(pc1,size);
   getimage(maxx-200-rad,maxy-100-rad,maxx-200+rad,maxy-100+rad,pc1^);
   putimage(maxx-200-rad,maxy-100-rad,pc0^,0);
   for i:=1 to n do
   begin
      ygr1[i]:=round(maxy-50-(maxy-100)*Xn[i]/height-rad);
      ygr2[i]:=round(maxy-50-(maxy-100)*Xn[i]/height-rad);
      putimage(maxx-180,ygr1[i],pc1^,0);
      putimage(maxx-70,ygr2[i],pc1^,0);
   end;
end{drawax};
   {--------------------------------------------------------------------}
procedure table( k1  : longint);
var
   i,j	   : integer;
   s,s1,s2 : string;
begin
   setlinestyle(solidln,$AAA,normwidth);
   setfillstyle(1,1);
   setcolor(15);
   if n>30 then j:=30 else j:=n;
   bar3d(30,25,385,25+12*(j+3)+10,10,TopOn);
   str(k1,s);
   s:='Collision number = '+s;
   str(t:12:5,s1);
   outtextxy(40,30,s);
   str(k:3,s2);
   s:='Time='+s1+'s   K = '+s2;
   outtextxy(40,42,s);
   outtextxy(40,54,title1);
   for i:=1 to j do
   begin
      str(i:3,s);
      str(Xnav[i]:8:5,s1);
      str(Vn2av[i]:8:3,s2);
      s:=s+' '+s1+'  '+s2;
      str(Vn[i]:8:3,s1);
      str(xn[i]:8:5,s2);
      s:=s+' '+s1+'  '+s2;
      outtextxy(40,54+(i)*12,s);
   end;
end;{table}
   {----------------------------------------------------------------}
procedure drawgr;
var
   j,i	   : integer;
   s,s1,s2 : string;
begin
   setlinestyle(solidln,$AAA,normwidth);
   setfillstyle(1,1);
   setcolor(15);
   for i:=1 to n do
   begin
      if abs(xnav[i])<(1.1*height) then
      begin
	 ygr3[i]:=round(maxy-50-(maxy-100)*Xn[i]/height-rad);
	 ygr4[i]:=round(maxy-50-(maxy-100)*Xnav[i]/height-rad);
      end;
      if ygr3[i]<>ygr1[i] then
      begin
	 putimage(maxx-180,ygr1[i],pc0^,0);
	 putimage(maxx-180,ygr3[i],pc1^,0);
	 ygr1[i]:=ygr3[i];
      end
   end;
   for i:=1 to n do
   begin
      if ygr4[i]<>ygr2[i] then
      begin
	 putimage(maxx-70,ygr2[i],pc0^,0);
	 putimage(maxx-70,ygr4[i],pc1^,0);
	 ygr2[i]:=ygr4[i];
      end;
   end;
   ygrp2:=round(maxy-50-(maxy-100)*X0(t)/height);
   if ygrp2<>ygrp1 then
   begin
      putimage(maxx-220,ygrp1,ps0^,0);
      putimage(maxx-220,ygrp2,ps1^,0);
      ygrp1:=ygrp2;
   end;
end;{drawgr}
   {----------------------------------------------------------------}
BEGIN
   init;
   initgr;
   drawax;
   predict1;
   l:=1;
   repeat
   begin
      predict;
      re_count;
      mean;
      if l mod 2 =0 then
	 drawgr;
      if l mod 1000 =0 then
	 table(l);
      l:=l+1;
   end;
   until KeyPressed;
   closegraph;
END.
