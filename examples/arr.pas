procedure modify(var a : array [lo..hi : integer] of char);
begin
   a[lo] := a[hi];
end;

procedure f(a, b : array [lo..hi : integer] of char);
begin
   writeln(a[lo]);
   writeln(b[lo]);
   if a[lo] <> '2' then
   begin
      a[lo] := '1';
      b[lo] := '2';
      a := b;
      f(a, b);
      modify(a);
   end
end;

procedure g(var a, b : array [lo..hi : integer] of char);
begin 
   writeln(a[lo]);
   writeln(b[lo]);
   if a[lo] = '0' then
   begin
      a[lo] := '3';
      b[lo] := '4';
      a := b;
      f(a, b);
      g(a, b);
   end;
end;

var
   a, b	:  array [1..100] of char;
begin 
   a[1] := '0';
   b[1] := '0';
   f(a, b);
   g(a, b);
   f(a, b);
   writeln(a[1]);
end.

