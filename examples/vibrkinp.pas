PROGRAM CORONA_DISCHARGE;
{$N+}
uses graph;
const
   kmin=0;
   kev01: double=3e-8;
   kvv01: double=1e-12;
   kvt: double=1e1;
   Tv0: double=0.15;
   a: double=0.6;
   b: double=0.005;
   dvv: double=0.36;
   xe: double=6e-3;
   tt: double=0.12;
   n0: double=2.6e19;
   dt: double=5e-11;
   tk: double=1e-7;
   nn=60;
   ne0=3.3e14;
   g: double=1.0;
   v0: double=1.3e7;
type
   mas1=array[0..60] of double;
   mas3=array[0..60,0..60] of double;
   mas4=array[0..60] of integer;
var
   n			    : mas1;
   kev,kvv		    : mas3;
   xgr1,ygr1,ygr2,ygr3,ygr4 : mas4;
   ygr5,ygr6		    : mas4;
   fmax,yn,pump,ne,n1	    : double;
   t,dn,count,fe,Tv	    : double;
   dfe,dcount,dpump	    : double;
   v1tr,v2tr,dv2tr,v2tr2    : double;
   k,i,j,m		    : integer;
   mmax,ci,Tr		    : integer;
   s,s1,s2,s3,s4	    : string;
   f			    : text;
   {--------------------------------------------------------------------}
procedure fkev( var kev1 : mas3 );
var
   i,j : integer;
begin
   for i:=0 to nn do
   begin
      for j:=0 to nn do
      begin
	 if i<j then
	    kev1[i,j]:=kev01*exp(-a*abs(i-j))/(1+b*i)
	 else
	    kev1[i,j]:=0;
      end;
   end;
end{kev};
   {---------------------------------------------------------------------}
procedure fkvv(var kvv1 : mas3);
var
   i,j : integer;
begin
   for i:=0 to nn-1 do
   begin
      for m:=0 to nn-1 do
	 kvv1[i+1,m]:=(i+1)*(m+1)*kvv01*exp(-dvv*abs(i-m))*
	 (3/2-0.5*exp(-dvv*abs(i-m)));
   end;
end{fkvv};
   {---------------------------------------------------------------------}
function nelectr( t1 : double) : double;
begin
   nelectr:=ne0*exp(-v0*t1);
end;
{--------------------------------------------------------------------}
procedure init;
var
   i : integer;
begin
   {n[0]:=1.3e19;
    n[1]:=5.9e18;
    n[2]:=3e18;
    n[3]:=1.64e18;
    n[4]:=8.52e17;
    n[5]:=5.8e17;
    n[6]:=3.64e17;
    n[7]:=2.35e17; }
   for i:=0 to nn do n[i]:=n0*(1-exp(-1/Tv0))*exp(-i/Tv0);
   pump:=1/(exp(1/Tv0)-1);
end{bg};
   {---------------------------------------------------------------------}
procedure initgr;
var
   gm,gd,error : integer;
   maxx,maxy,j : integer;
begin
   gd:=detect;
   initgraph(gd,gm,'d:\bp\bgi');
   error:=graphresult;
   if error<>grOk then
   begin
      writeln(grapherrormsg(error));
      readln;
      halt;
   end;
   setbkcolor(green);
   cleardevice;
end{init};
   {------------------------------------------------------------------}
procedure draw;
var
   maxx,maxy,j,r,f : integer;
begin
   setcolor(red);
   maxx:=getmaxx;
   maxy:=getmaxy;
   line(50,maxy-50,maxx,maxy-50);
   line(50,maxy-50,50,0);
   fmax:=0;
   for k:=kmin to nn do
      if ln(n[k])>fmax then fmax:=ln(n[k]);
   for k:=kmin to nn do
   begin
      yn:=ln(n[k])/ln(n0);
      xgr1[k]:=round((maxx-50)/(nn)*k)+50;
      ygr1[k]:=-round((maxy-50)*yn)+maxy-50;
   end;
   if nn<= 100 then
   begin
      for k:=kmin to nn do
	 line(xgr1[k],maxy-42,xgr1[k],maxy-58);
   end;
   for j:=1 to 10 do
      line(42,round((maxy-50)*j/10),58,round((maxy-50)*j/10));
   setlinestyle(dottedln,$AAA,normwidth);
   for j:=1 to 10 do
      line(58,round((maxy-50)*j/10),maxx,round((maxy-50)*j/10));
   setlinestyle(solidln,$AAA,normwidth);
   setcolor(green);
   for k:=kmin to nn-1 do
      line(xgr1[k],ygr2[k],xgr1[k+1],ygr2[k+1]);
   setcolor(blue);
   for k:=kmin to nn-1 do
   begin
      line(xgr1[k],ygr1[k],xgr1[k+1],ygr1[k+1]);
      ygr2[k]:=ygr1[k];
   end;
   ygr2[nn]:=ygr1[nn];
   setfillstyle(1,green);
   bar(200,10,600,30);
   str(pump:12,s);
   str(t:12,s3);
   s1:='V1 ='+s+' t = '+s3;
   outtextxy(200,10,s1);
   Tv:=2/(ln(n[0]/n[2]));
   Tr:=round(tt/(2*xe*Tv));
   if Tr > 30 then Tr := 30;
   n1:=pump-v1tr;
   {if t>(1.05)*t0 then}
   for k:=kmin to nn do
   begin
      yn:=ln(n[0])/ln(n0)-(dvv*(k-1)+ln(k+1))/ln(n0);
      ygr5[k]:=-round((maxy-50)*yn)+maxy-50;
   end;
   setcolor(green);
   for k:= kmin to nn-1 do
      line(xgr1[k],ygr6[k],xgr1[k+1],ygr6[k+1]);
   setcolor(LightBlue);
   for k:=kmin to nn-1 do
   begin
      line(xgr1[k],ygr5[k],xgr1[k+1],ygr5[k+1]);
      ygr6[k]:=ygr5[k];
   end;
   ygr6[nn]:=ygr5[nn];

   for k:=kmin to nn do
   begin
      if  k<Tr then
	 yn:=ln(n[0]*exp(-k/Tv+xe*k*k/(tt)))/ln(n0)
      else
	 yn:=ln(n[0]*exp(-Tr/(2*Tv)-1/2)*(Tr+1)/(k+1))/ln(n0);
      ygr3[k]:=-round((maxy-50)*yn)+maxy-50;
   end;
   setcolor(green);
   for k:=kmin to nn-1 do
      line(xgr1[k],ygr4[k],xgr1[k+1],ygr4[k+1]);
   setcolor(red);
   for k:=kmin to nn-1 do
   begin
      line(xgr1[k],ygr3[k],xgr1[k+1],ygr3[k+1]);
      ygr4[k]:=ygr3[k];
   end;
   ygr4[nn]:=ygr3[nn];
   setcolor(blue);
   v1tr:=0;
   v2tr:=0;
   for k:=1 to Tr do
   begin
      v1tr:=v1tr+k*(n[k]/n0);
      v2tr:=v2tr+k*(k-1)*(n[k]/n0);
   end;
   str(v1tr:12,s4);
   str(fe:12,s3);
   str(dfe:12,s1);
   str(Tv:12,s2);
   s1:='V1Tr = '+s4+' Tv = '+s2+' fe = '+s3+' dfe ='+s1;
   bar(20,maxy-35,maxx,maxy);
   outtextxy(20,maxy-35,s1);
   str(v2tr:12,s1);
   str(n1:12,s2);
   s1:='V2Tr = '+s1+' n1 = '+s2;
   outtextxy(20,maxy-20,s1);
   str(nn,s2);
   s1:='n='+s2;
   outtextxy(maxx-60,maxy-60,s1);
end{draw};
   {---------------------------------------------------------------------}
procedure print;
var
   i,j : integer;
begin
   write(f,(t*1e9):10:5,'  ',fe:10:5,'  ',n1:10:5,'  ',(ln(t*1e9)):10:5);
   writeln(f,'  ',(ln(fe)):10:5,'  ',(ln(n1)):10:5,'  ',(sqr(fe*100)):10:5);
end;
   {----------------------------------------------------------------------}

BEGIN
   count:=0;
   pump:=0;
   fkev(kev);
   fkvv(kvv);
   init;
   initgr;
   assign(f,'vibrkinp.txt');
   rewrite(f);
   writeln(f,' Time          fe          n1         Ln(Time)     Ln(fe)     Ln(n1)       fe^2');
   draw;
   t:=0;

   repeat
      ne:=nelectr(t);
      dpump:=0;
      dcount:=0;
      for m:=1 to nn do
      begin
	 for k:=0 to m do
	 begin
	    dn:=n[k]*kev[k,m]*ne*dt;
	    dpump:=dpump+dn*(m-k-xe*(sqr(m+1/2)-sqr(k+1/2)))/n0;
	    n[m]:=n[m]+dn;
	    n[k]:=n[k]-dn;
	 end;
      end;
      for m:=0 to nn-1 do
      begin
	 for i:=0 to nn-1 do
	 begin
	    dn:=n[m]*n[i+1]*kvv[i+1,m]*dt/2;
	    dcount:=dcount+2*xe*dn*(m-i)/n0;
	    n[m+1]:=n[m+1]+dn;
	    n[m]:=n[m]-dn;
	    n[i+1]:=n[i+1]-dn;
	    n[i]:=n[i]+dn;

	    dn:=n[m+1]*n[i]*kvv[i+1,m]*exp(-2*xe*(m-i)/tt)*dt/2;
	    dcount:=dcount+2*xe*dn*(i-m)/n0;
	    n[m+1]:=n[m+1]-dn;
	    n[m]:=n[m]+dn;
	    n[i+1]:=n[i+1]+dn;
	    n[i]:=n[i]-dn;
	 end;
      end;
      pump:=pump+dpump;
      count:=count+dcount;
      n[nn]:=n[nn]-kvt*dt*n[nn];
      n[0]:=n[0]+kvt*dt*n[nn];
      fe:=g*count/pump;
      dfe:=g*dcount/dpump;
      if (round(t/dt) mod 10)=0 then draw;
      {if ((t=50e-9) or (t=150e-9)) then print;
       if ((round(t/dt) mod round(1e-7/dt) =0) and (t>dt)) then print;}
      t:=t+dt;
   until (t > tk) or keypressed;
   closegraph;
   close(f);
END.

