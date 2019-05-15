{$N+}
uses crt;
const
   sigma: double=0.5{km};
   R1: double=5{km};
type
   mas1=array[1..100] of double;
   mas2=array[0..8] of integer;
   mas3=array[0..8] of string;
   mas4=array[0..8] of double;
   mas5=array[0..8] of double;
var
   Xb,Yb                                      : mas1;
   npoint,nk                                  : mas2;
   filepath                                   : mas3;
   inp                                        : mas4;
   Xel,Yel,Pk                                 : mas5;
   ngr                                        : integer;
   Mk                                         : double;
{----------------------------------------------------------------------}
procedure init;
begin
         filepath[1]:='random.txt';
         filepath[2]:='coord.txt';
         filepath[3]:='war2.txt';
         filepath[4]:='xy2.txt';
         ngr:=2;
end{init};
{-----------------------------------------------------------------------}
procedure make( i1 : integer ; k1 : integer);
begin
  if i1=1 then
    begin
      Xb[k1]:=sigma*inp[2];
      Yb[k1]:=sigma*inp[3];
    end;
  if i1=2 then
    begin
      Xel[k1]:=inp[2];
      Yel[k1]:=inp[3];
    end;
end{make};
{----------------------------------------------------------------------}
procedure calcul1;
var i,j,k,delta          : integer;
    r                    : double;
begin
   for i:=0 to npoint[2] do nk[i]:=0;
   for i:=1 to npoint[1] do
      begin
        delta:=0;
        for j:=1 to npoint[2] do
          begin
            r:=sqrt(sqr(Xb[i]-Xel[j])+sqr(Yb[i]-Yel[j]));
            if r<R1 then
               delta:=delta+1;
          end;
        nk[delta]:=nk[delta]+1;
      end;
   Mk:=0;
   for k:=1 to npoint[2] do Mk:=Mk+K*nk[k];
   Mk:=Mk/npoint[1];
   for i:=0 to npoint[2] do Pk[i]:=0;
   for i:=0 to npoint[2] do
     begin
       for j:=i to npoint[2] do
          Pk[i]:=Pk[i]+nk[j];
       Pk[i]:=Pk[i]/npoint[1];
     end;
end{calcul1};
{------------------------------------------------------------------------}
procedure main;
var  fil         : text;
     num2        : integer;
     i,j,k       : integer;
begin
  for i:= 1 to ngr do
    begin
      assign(fil,filepath[i]);
      reset(fil);
      read(fil,npoint[i],num2);
      for k:=1 to npoint[i] do
        begin
          for j:=1 to num2 do
            read(fil,inp[j]);
          make(i,k);
        end;
      close(fil);
    end;
  for i:=1 to ngr do calcul1;
end{main};
{-----------------------------------------------------------------------}
procedure mail;
var  fil          : text;
     k            : integer;
begin
      assign(fil,filepath[3]);
      rewrite(fil);
  Writeln(fil,'                 Task 2.1 , 2.2 :' );
  writeln(fil);
  writeln(fil,'     <K> =  ',mk:12:7);
  writeln(fil);
  writeln(fil,'    K          N(k)          P(i >= k) ');
  writeln(fil);
  for k:=0 to npoint[2] do
  writeln(fil,'    ',k,'          ',nk[k],'          ',Pk[k]:12:7);
  writeln(fil);
      close(fil);
      assign(fil,filepath[4]);
      rewrite(fil);
  writeln(fil,'     Xb                         Yb ');
  for k:=1 to npoint[1] do
    Writeln(fil,'  ',Xb[k]:12:7,'               ',Yb[k]:12:7);
      close(fil);
end{mail};
{-----------------------------------------------------------------------}
BEGIN
  INIT;
  MAIN;
  MAIL;
END.
