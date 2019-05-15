{$N+}
program impact;
uses crt;
const
   alp: double=0.975;
   n=12;
   v: double=10;

type
   mas1=array[1..50,1..50] of double;
   mas2=array[1..50] of double;
var
   matr                     : mas1;
   vel1,vel2                : mas2;
   d,b                      : double;
   i,j,k                    : integer;
{-------------------------------------------------------------------}
procedure calc;
var i,j    : integer;
begin
  b:=(1+alp)/2;
  d:=1-b;
  matr[1,1]:=d;
  matr[1,2]:=b;
  matr[2,1]:=b;
  matr[2,2]:=d;
  for i:=3 to n do
     begin
        for j:=1 to i-1 do
          begin
             matr[i,j]:=matr[i-1,j]*b;
             matr[i-1,j]:=matr[i-1,j]*d;
          end;
        matr[i-1,i]:=b;
        matr[i,i]:=d;
     end;
  for i:=1 to n do
     matr[i,1]:=matr[i,1]*(-alp);
end;{calc}
{-----------------------------------------------------------------}
procedure multi;
var  i,j         : integer;
begin
   for i:=1 to n do vel2[i]:=0;
   for i:=1 to n do
      begin
        for j:=1 to n do
           begin
              vel2[i]:=vel2[i]+matr[i,j]*vel1[j];
           end;
       end;
   for i:=1 to n do vel1[i]:=vel2[i];
end;{multi}
{--------------------------------------------------------------------}
procedure print;
var  i         : integer;
begin
   writeln;
   for i:=1 to n do
     writeln('  V[',i:2,'] = ',vel1[i]:12:7);
   readln;
end{print};
{--------------------------------------------------------------------}
BEGIN
   for i:=1 to n do  vel1[i]:=-v;
   calc;
   print;
   repeat
      begin
         multi;
         print;
      end;
   until vel1[1]>0;
END.



