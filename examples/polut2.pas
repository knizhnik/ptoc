
      PROGRAM CORONA_DISCHARGE_POLUTION_REMOVEMENT;
{$N+}
uses graph;
const
     kmin=1;                        e=1.6e-19;
                                    el=2.6e6;{ el=2.6e6;}
     emax=2.88e-18;                 ener3=1.07e-18;

     nf=18;                         q0=1e-20;
     nn=144;
     nm=4;
     m1=1836.2;
     me=0.9e-30;
     n0=2.6e25;

type
     mas1=array[0..180] of real;
     mas2=array[1..4] of integer;
     mas3=array[1..4,1..5] of real;
     mas4=array[0..180] of integer;
     mas5=array[1..4,1..5] of array [0..180] of real;
     mas6=array[1..4] of real;
     mas7=array[1..4,1..5] of array [0..180] of real;
     stat1=array[1..4] of string[5];
     stat2=array[1..4] of integer;
     stat3=array[1..4,1..5] of string[18];
     stat4=array[1..4,1..5] of real;
     stat5=array[1..4,0..20] of real;
     stat6=array[1..4,1..3] of real;
     stat7=array[1..4,1..5] of word;
     stat8=array[1..4,1..5] of word;
const
     s : stat1 =('CO2','N2','O2','H2O');
     nr : stat2 =(3,5,1,1);
     gaz1 : stat2 =(100,0,0,0);
     gaz2 : stat2 =(0,100,0,0);
     m    : stat2 =(44,28,32,18);
     sr : stat3 =(('e+CO2->e+CO+O','e+CO2->2e+CO2+','e+CO2->e+CO2(W)','',''),
                ('e+N2->e+N+N','e+N2->e+N2+','e+N2->e+N2(A)','e+N2->e+N2(B)',
                  'e+N2->e+N2(W)'),
                ('e+O2->e+O+O(P)','e+O2->e+O+O(D)','e+O2->e+O2+','',''),
                ('e+H2O->H- +OH','e+H2O->e+H2O+','','',''));
     enr : stat4 =((5.5,13.8,0,0,0),(9.8,15.6,0,0,0),
                   (6,7,12.1,0,0),(6,12.6,0,0,0));
     fm  : stat5 =({(0.42,0.23,0.195,0.18,0.035,0.018,0.013,0.0095,0.0066,
                   0.0044,0.0027,1.69e-3,9.79e-4,5.25e-4,2.56e-4,1.13e-4,4.57e-5,
                   1.7e-5,5.9e-6,0,0),}
               (0.28,0.19,0.16,0.11,0.045,0.027,0.02,0.015,0.011,0.008,5.4e-3,
                3.6e-3,2.3e-3,1.36e-3,7.5e-4,3.8e-4,1.8e-4,8.3e-5,3.54e-5,0,0),

                  {(0.48,0.46,0.226,0.025,0.0127,0.0085,0.006,0.004,2.5e-3,
                    1.3e-3,6.8e-4,3.3e-4,1.5e-4,6.8e-5,3e-5,1.4e-5,6.4e-6,
                    3e-6,1.44e-6,0,0)  }
                 {(0.4,0.38,0.2,0.04,2.3e-2,1.6e-2,1.2e-2,8.3e-3,5.4e-3,3.3e-3,
                  1.8e-3,1e-3,5.4e-4,2.8e-4,1.5e-4,7.9e-5,4.2e-5,2.3e-5,1.3e-5,0,0),}
              (0.4,0.38,0.2,0.046,1.8e-2,1.4e-2,1.1e-2,8.3e-3,5.4e-3,3.3e-3,
               1.8e-3,1e-3,5.4e-4,2.8e-4,1.5e-4,7.9e-5,4.2e-5,2.3e-5,1.3e-5,0,0),
               (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
               (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)   );
     vdm  : stat5 =((14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,
                    14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6),
                   (10e6,10e6,10e6,10e6,10e6,10e6,10e6,10e6,10e6,10e6,
                    10e6,10e6,10e6,10e6,10e6,10e6,10e6,10e6,10e6,10e6,10e6),
                   (14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,
                    14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6),
                   (14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,
                    14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6,14e6));
     yield1 : stat4 =((4e-1,1e-2,0,0,0),(5e-1,1e-2,0,0,0),
                      (3e-1,3e-1,6e-3,0,0),(1e-2,0,0,0,0));
     hw : stat6 =((0.15*2.7e-20,0.2*1.3e-20,0.45*4.7e-20),(3.8e-20,0,0),(0,0,0),
                  (0,0,0));
     bool1 : stat7 =((4,2,2,2,2),(2,2,2,2,2),(1,1,1,1,1),(2,1,1,1,1));
     bool2 : stat8 =((2,2,4,4,4),(2,2,4,4,4),(1,1,1,1,1),(1,1,2,2,1));
var
     k,i,j                    : integer;
     mmax,ci                  : integer;
     df,dv,v                  : mas1;
     evvb,velec               : mas1;
     dfm1,dfm2                : mas1;
     mixt1,mixt               : mas2;
     ki,yield2                : mas3;
     xgr,ygr                  : mas4;
     qcol                     : mas5;
     d                        : mas6;
     qreac                    : mas7;
     fmax,yn,vd               : real;
     mean,de,de1              : real;
     s1,s2,s3,s4              : string;
{--------------------------------------------------------------------}
procedure start;
var i,j ,k         : integer;
    f              : text;
    g              : real;
begin
  assign(f,'q2.txt');
  reset(f);
  for i:=1 to nm do
    begin
      for j:=1 to 5 do
        begin
          for k:=0 to (nn div 2) do
            begin
              read(f,g);
              qcol[i,j,k]:=g;
            end;
        end;
    end;
  for i:=1 to nm do
    begin
      for j:=1 to nr[i] do
        begin
          for k:=0 to (nn div 2) do
            begin
              read(f,g);
              qreac[i,j,k]:=g;
            end;
        end;
    end;
  close(f);
  de:=nf/nn*e;
  de1:=nf/nn;
end{start};
{---------------------------------------------------------------------}
procedure delta(mm1 : stat2; var d2 :mas6 );
var i  : integer;
    dl : real;
begin
  for i:=1 to nm do
    d2[i]:=2/(mm1[i]*m1);
end{delta};
{---------------------------------------------------------------------}
function fr(mxt : integer ; q1 : real; en1 : real ) : real;
begin
  fr:=q1*q0*sqrt(2*en1/me)*n0*mxt/100;
end{frec};
{-----------2-----------------------------------------------------------}
procedure interpol( mask : word; f1 : mas1 ; var f2 : mas1);
var aa,bb,fp,d1,b1,c1            : mas1;
    c,i,mk,nk1                   : integer;
    h,dh                         : real;
begin
  case mask of
     4:   mk:=2;
     2:   mk:=4;
     1:   mk:=8;
  end;
  nk1:=nn div mk;
  h:=nf/nk1;
  c:=-4;
  for i:=1 to nk1 do
    fp[i]:=-6*(f1[i+1]+f1[i-1]-2*f1[i])/(h*h);
  aa[1]:=0;
  bb[1]:=0;
  for i:=1 to nk1-1 do
    begin
      aa[i+1]:=1/(c-aa[i]);
      bb[i+1]:=(bb[i]+fp[i])/(c-aa[i]);
    end;
  c1[0]:=0;
  c1[nk1]:=0;
  for i:=nk1-1 downto 1 do
    c1[i]:=aa[i+1]*c1[i+1]+bb[i+1];
   for i:=1 to nk1 do
     begin
       d1[i]:=(c1[i]-c1[i-1])/h;
       b1[i]:=h*c1[i]/2-h*h*d1[i]/6+(f1[i]-f1[i-1])/h;
     end;

   for i:=0 to nk1-1 do
      begin
         for j:=0 to mk-1 do
           begin
              dh:=h*(j/mk-1);
              f2[mk*i+j]:=f1[i+1]+b1[i+1]*dh+c1[i+1]*sqr(dh)/2+
                          d1[i+1]*dh*sqr(dh)/6;
           end;
      end;
   f2[mk*nk1]:=f1[nk1];
end{interpol};
{-------------------------------------------------------------------}
procedure interpolq;
var  q1,q2        : mas1;
     i,j,k,nn2    : integer;
begin
   for i:=1 to nm do
     begin
       for j:=1 to nr[i] do
         begin
              for k:=0 to (nn div 2) do q1[k]:=qreac[i,j,k];
              interpol(bool1[i,j],q1,q2);
              for k:=0 to nn do qreac[i,j,k]:=q2[k];
         end;
     end;
   for i:=1 to nm do
     begin
       for j:=1 to 5 do
         begin
              for k:=0 to (nn div 2) do q1[k]:=qcol[i,j,k];
              interpol(bool2[i,j],q1,q2);
              for k:=0 to nn do qcol[i,j,k]:=q2[k];
         end;
     end;
end{interpolq};
{----------------------------------------------------------------------}
procedure interpolf;
var fq1,fq2        : mas1;
    k,nf1          : integer;
begin
  for k:=0 to nf do fq1[k]:=fm[1,k];
  interpol(1,fq1,dfm1);
  for k:=0 to nf do fq1[k]:=fm[2,k];
  interpol(1,fq1,dfm2);
end{interpolf};
{-----------------------------------------------------------------------}
procedure vdr(mixt : mas2 ; ener : real ; var vdn : real);
var i      : integer;
begin
  k:=round(ener/de);
  for i:=1 to nm do
     vdn:=vdn+mixt[i]/(100*vdm[i,k]);
  vdn:=1/vdn;
end{vd};
{---------------------------------------------------------------------}
procedure init;
var  gm,gd,error     : integer;
     maxx,maxy,j     : integer;
begin
  gd:=detect;
  initgraph(gd,gm,'D:\BP\bgi');
  error:=graphresult;
  if error<>grOk then
      begin
        writeln(grapherrormsg(error));
        readln;
        halt;
      end;
  cleardevice;
end{init};
{------------------------------------------------------------------}
procedure print;
var  maxx,maxy,j,r,f,count        : integer;
     lgki                         : real;
begin
  cleardevice;
  setcolor(red);
  setbkcolor(green);
  count:=0;
  s1:=' Initial Yield ( per 100 eV )';
  outtextxy(180,50,s1);
  maxx:=getmaxx;
  maxy:=getmaxy;
  setcolor(blue);
  s1:='Mixture  :';
  for i:=1 to 4 do
    begin
      str(mixt[i],s2);
      s4:=s4+s[i]+'='+s2+'%   ';
    end;
  outtextxy(150,80,s1+s4);
  outtextxy(50,100,'Reaction             Yield             K                 Lg(K)');
  for i:=1 to nm do
    begin
         for j:=1 to nr[i] do
        begin
          str(yield2[i,j] : 13 ,s2);
          outtextxy(200,120+(count)*12,s2);
          str((ki[i,j]*1e6) : 13 ,s2);
          outtextxy(350,120+(count)*12,s2);
          if ki[i,j]<>0 then
            begin
              lgki:=ln(ki[i,j]*1e6)/ln(10);
              str(lgki :11,s1);
            end
                 else
              s1:='   -----';
          s3:=sr[i,j];
          outtextxy(50,120+(count)*12,s3);
          outtextxy(500,120+(count)*12,s1);
          count:=count+1;
        end;
    end;
    readkey;
  repeat until keypressed;
end{print};
{---------------------------------------------------------------------}
procedure drawf;
var maxx,maxy,j,r,f         : integer;
    minflg                  : integer;
    minf,fmin               : real;
begin
  cleardevice;
  setcolor(red);
  setbkcolor(green);
  setlinestyle(solidln,$AAA,normwidth);
  maxx:=getmaxx;
  maxy:=getmaxy;
  line(50,maxy-50,maxx,maxy-50);
  line(50,maxy-50,50,0);
  fmin:=1;
  for k:=0 to nn do
    if df[k]<fmin then fmin:=df[k];
   minf:=1;
  repeat
    minf:=minf/10;
   until fmin>minf;
    for k:=0 to nn do
    begin
      yn:=1-ln(df[k])/ln(minf);
      xgr[k]:=round((maxx-50)/(nn)*k)+50;
      ygr[k]:=-round((maxy-50)*yn)+maxy-50;
    end;
   for k:=0 to nn do
    if k mod 4 = 0 then
      line(xgr[k],maxy-42,xgr[k],maxy-58);
  minflg:=round(ln(minf)/ln(10));
  for j:=0 downto minflg do
    line(42,round(abs((maxy-50)*j/minflg)),58,round(abs((maxy-50)*j/minflg)));
  setlinestyle(dottedln,$AAA,normwidth);
  for j:=1 downto minflg do
    line(58,round(abs((maxy-50)*j/minflg)),maxx,round(abs((maxy-50)*j/minflg)));
  setcolor(blue);
  setlinestyle(solidln,$AAA,thickwidth);
  for k:=0 to nn-1 do
    line(xgr[k],ygr[k],xgr[k+1],ygr[k+1]);
    s1:=' Lg[f(e)] ';
  outtextxy(60,10,s1);
  for j:=0 downto minflg do
    begin
      str(j,s2);
      outtextxy(10,round(abs((maxy-50)*j/minflg)),s2);
    end;
  str(nf,s1);
     outtextxy(maxx-50,maxy-30,s1);
 for i:=1 to 2 do
   begin
     for k:=0 to nn do
      begin
        if i=1 then yn:=1-ln(dfm1[k])/ln(minf)
          else yn:=1-ln(dfm2[k])/ln(minf);
        xgr[k]:=round((maxx-50)/(nn)*k)+50;
        ygr[k]:=-round((maxy-50)*yn)+maxy-50;
      end;
    if i=1 then setcolor(6) else setcolor(11);
    for k:=0 to nn-1 do
      line(xgr[k],ygr[k],xgr[k+1],ygr[k+1]);
      str(mixt[i],s2);
      s1:=s[i]+' = '+s2;
      outtextxy(maxx-100,maxy-300+15*(i-1),s1);
   end;
   repeat until KeyPressed;
   readkey;
end{drawf};
{---------------------------------------------------------------------}
procedure drawq;
var maxx,maxy,j,r,f,i       : integer;
    minf,qmax,qm            : real;
begin
setbkcolor(green);
setcolor(red);
for j:=1 to 5 do
 begin
  cleardevice;
  setlinestyle(solidln,$AAA,normwidth);
  maxx:=getmaxx;
  maxy:=getmaxy;
  qmax:=0;
  line(50,maxy-50,maxx,maxy-50);
  line(50,maxy-50,50,0);
  for i:=1 to nm do
    for k:=0 to nn do
      if qcol[i,j,k]>qmax then qmax:=qcol[i,j,k];
  for k:=0 to nn do
    if k mod 4 = 0 then
      line(xgr[k],maxy-42,xgr[k],maxy-58);
  for k:=0 to 10 do
    line(42,round((maxy-50)*k/10),58,round((maxy-50)*k/10));
  setlinestyle(dottedln,$AAA,normwidth);
  for k:=1 to 10 do
    line(58,round((maxy-50)*k/10),maxx,round((maxy-50)*k/10));
  for i:=1 to nm do
    begin
      case i of
        1:  setcolor(blue);
        2:  setcolor(red);
        3:  setcolor(green);
        4:  setcolor(yellow);
      end;
      setlinestyle(solidln,$AAA,thickwidth);
        for k:=0 to nn do
          begin
            yn:=qcol[i,j,k]/(round(qmax)+1);
            xgr[k]:=round((maxx-50)/(nn)*k)+50;
            ygr[k]:=-round((maxy-50)*yn)+maxy-50;
          end;
      for k:=0 to nn-1 do
        line(xgr[k],ygr[k],xgr[k+1],ygr[k+1]);
      outtextxy(300+100*(i-1),10,s[i]);
    end;
  s1:=' Q(e)= ';
  qm:=q0*(round(qmax)+1);
  str(qm :12, s2);
  s1:=s1+s2;
  setcolor(blue);
  outtextxy(10,10,s1);
  case j of
   1 : outtextxy(maxx-150,maxy-30,'Elastic');
   2 : outtextxy(maxx-150,maxy-30,'Electronic');
   else  outtextxy(maxx-150,maxy-30,'Vibrational');
  end;
  str(nf,s1);
  outtextxy(maxx-50,maxy-30,s1);
  repeat until KeyPressed;
  readkey;
 end;
end{drawq};
{---------------------------------------------------------------------}
procedure frec(mixt2 : mas2 );
var i,j                           : integer;
    del                           : mas6;
    ener                          : real;
begin
for j:=0 to nn do
 begin
    ener:=j*de;
    delta(m,del);
    dv[j]:=0;
    v[j]:=0;
    evvb[j]:=0;
    velec[j]:=0;
    for i:=1 to nm do
      begin
        dv[j]:=dv[j]+del[i]*fr(mixt2[i],qcol[i,1,j],ener);
        v[j]:=v[j]+fr(mixt2[i],qcol[i,1,j],ener);
        for k:=1 to 3 do
           evvb[j]:=evvb[j]+hw[i,k]*fr(mixt2[i],qcol[i,2+k,j],ener);
        velec[j]:=velec[j]+fr(mixt2[i],qcol[i,2,j],ener);
      end;
 end;
end{frec};
{---------------------------------------------------------------------}
procedure distr;
var i,n1                  : integer;
    con,c0,c1,c4          : double;
    int                   : real;
begin
  frec(mixt);
  con:=3*me/(2*e*e*el*el);
  n1:=round(ener3/de);
  df[0]:=1;
  int:=0;
  for i:=1 to n1 do
    begin
      int:=int+de*con*dv[i]*v[i]*(1+evvb[i]/(i*de*dv[i]));
      df[i]:=exp(-int);
    end;
      int:=0;
  for i:=n1+1 to nn do
    begin
      int:=int+de*sqrt(con*v[i]*velec[i]/(de*i));
      df[i]:=exp(-int);
       end;
      c4:=df[n1]*(dv[n1]*v[n1]*(1+evvb[n1]/(n1*de*dv[n1]))*con/
     sqrt(con*v[n1]*velec[n1]/(de*n1)));
  c1:=-df[n1]+c4;
  for i:=0 to n1 do
    df[i]:=(df[i]+c1);
  for i:=n1+1 to nn do
    df[i]:=c4*df[i];
    c0:=0;
  for i:=1 to nn do
    c0:=c0+de1*(df[i]*sqrt(i*de1)+df[i-1]*sqrt((i-1)*de1))/2;
  c0:=1/c0;
  for i:=0 to nn do
    df[i]:=c0*df[i];
end{distr};
{-----------------------------------------------------------------------}
procedure meanener(var en1 : real);
var i            : integer;
begin
  en1:=0;
  for i:=1 to nn do
    en1:= en1+de*(df[i]*i*de*sqrt(i*de)+df[i-1]*(i-1)*de*sqrt((i-1)*de))/2;
end{meanener};
procedure yield;
begin
  meanener(mean);
  vdr(mixt,mean,vd);
  for i:=1 to nm do
    begin
      for j:=1 to nr[i] do
        begin
          ki[i,j]:=0;
          for k:=1 to nn do
           ki[i,j]:= ki[i,j]+de1*q0*(df[k]*qreac[i,j,k]*sqrt(2*k*de/me)*
           sqrt(k*de1)+
           df[k-1]*qreac[i,j,k-1]*sqrt(2*(k-1)*de/me)*sqrt((k-1)*de1))/2;
          yield2[i,j]:=mixt[i]*ki[i,j]*n0/(el*(vd/100));
        end;
    end;
end{yield};
{----------------------------------------------------------------------}
procedure qhelp;
var con,c4,v1          : double;
    i,k,n1             : integer;
begin
  con:=2*e*e*el*el/(3*me);
  n1:=round(ener3/de);
  c4:=fm[i,n1];
  for k:=n1+1 to nn do
    begin
        v1:=fr(100,qcol[1,1,k],k*de);
        qcol[1,3,k]:=con*sqr(dfm1[k]-dfm1[k-1])/(de*de*c4*v1*n0*
        sqrt(2*de*k/me));
        v1:=fr(100,qcol[2,1,k],k*de);
        qcol[2,3,k]:=con*sqr(dfm2[k]-dfm2[k-1])/(de*de*c4*v1*n0*
        sqrt(2*de*k/me));
    end;
end{qhelp};
{----------------------------------------------------------------------}
procedure inputm;
var i     : integer;
begin
  writeln(' Input new mixture =>');
  for i:=1 to nm do
    begin
      writeln(s[i]);
      read(mixt[i]);
    end;
end{inputm};
{-----------------------------------------------------------------------}
{procedure pr;
var i,j : integer;
begin
  for i=0 to nk do
    begin
      writeln('N[',i,']=',n[i]:12);
      i:=i+1;
      if i-j>40  then
                  begin
                    j:=i;
                    readln;
                  end;
    end;
  readln;
end;}
{----------------------------------------------------------------------}

BEGIN
  mixt1[1]:=15; mixt1[2]:=70; mixt1[3]:=5; mixt1[4]:=10;
  {---------------------------------------------------}
  start;
  inputm;
  interpolq;
  interpolf;
  {qhelp;}
  init;
  drawq;
  distr;
  drawf;
  yield;
  print;
  closegraph;
END.
