function f1 : integer;
function f2 : integer;
procedure f3;
begin
   f3;
   f2;
end; { f3 }
function f4 : char;
begin
   f4;
   f2;
end; { f4 }

begin
   f1;
   f3;
   f4;
end; { f2 }

begin
   f2;
end; { f1 }
