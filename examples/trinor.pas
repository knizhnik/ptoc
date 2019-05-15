   program Trinor;
uses crt;
const
  t0=0.12;
  xe=0.006;
  e1=16;
  a=0.8;
  alf=0.7;
  g=1.4;
  jk=5000;
type
  mas1=array[0..20] of real;
var
  i,n,e2          : integer;
  f,fb            : mas1;
  tr,c,fe,tv      : real;
  tv1,tv2,tvt     : real;
  v0,v0b,tvb1     : real;
  e               : real;
  v1,v2,v1b,v2b   : real;
  flag            : boolean;
procedure momtr(tvr : real ; var v1tr : real ; var v2tr : real );
var n         : integer;
    v0tr      : real;
begin
  v0tr:=0; v1tr:=0; v2tr:=0;
  tr:=t0/(2*xe*tvr);
  e2:=round(tr);
  for n:=0 to e1 do
   f[n]:=exp(-n/tvr+n*(n-1)/(2*tvr*tr));
  for n:=0 to e1 do
   begin
    if n<=e2 then
     begin
       v0tr:=v0tr+f[n];
       v1tr:=v1tr+n*f[n];
       v2tr:=v2tr+n*(n-1)*f[n];
     end
    else
     begin
       v0tr:=v0tr+f[e2]/(n)*e2;
       v1tr:=v1tr+n*f[e2]/(n)*e2;
       v2tr:=v2tr+n*(n-1)*f[e2]/(n)*e2;
     end;
   end;
  v1tr:=v1tr/v0tr;
  v2tr:=v2tr/v0tr;
end{momtr};
procedure momb(tvb : real ;tvbb1 : real; var v1b1 : real ; var v2b1 : real );
var i             : integer;
    v0b1          : real;
begin
  v0b1:=0; v1b1:=0; v2b1:=0;
  fb[0]:=1;
  fb[1]:=exp(-1/tvbb1);
  for n:=2 to e1 do
   begin
    fb[n]:=fb[n-1]*exp(-1/tvb);
   end;
  for n:=0 to e1 do
     begin
       v0b1:=v0b1+fb[n];
       v1b1:=v1b1+n*fb[n];
       v2b1:=v2b1+n*(n-1)*fb[n];
     end;
  v1b1:=v1b1/v0b1;
  v2b1:=v2b1/v0b1;
end{momb};
{-------------------------------------------------------------------}
procedure find(ee : real);
begin
 flag:=true;
 momb(alf,alf,v1b,v2b);
 if ee<=v1b then
   begin
     flag:=false;
     tv1:=alf;
     tv2:=0;
     repeat
       tvb1:=(tv1+tv2)/2;
       momb(alf,tvb1,v1b,v2b);
        if v1b>ee then
          tv1:=tvb1
        else
          tv2:=tvb1;
     until abs(v1b-ee)<(ee/jk);
   end
   else
     begin
       tvb1:=alf;
       momb(alf,tvb1,v1b,v2b);
     end;
    tv1:=5*ee;
    tv2:=0;
    repeat
     tvt:=(tv1+tv2)/2;
     momtr(tvt,v1,v2);
       if v1>ee then
         tv1:=tvt
        else
         tv2:=tvt;
     until abs(v1-ee)<(ee/jk);
end{find};
{-----------------------------------------------------------------}
BEGIN
 write(' Input E = [0..3] ');
 readln(e);
 repeat
     find(e);
     if flag= true then fe:=a*xe*(v2-v2b)/(g*e)
       else fe:=a*xe*(v2-v2b)/e;
     writeln('   V1tr = ',v1:3:7,'  V2tr = ',v2:3:7,'  Ttr = ',tr:3:7);
     writeln('   V1b = ',v1b:2:7,'  V2b = ',v2b:2:7,'  Tv1 = ',tvb1:3:7);
     writeln('   Fe = ',(fe*100):2:7,' %.');
   write(' Input E = ');
   readln(e);
 until e=0;
END.


