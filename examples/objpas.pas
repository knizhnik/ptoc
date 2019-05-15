program main;
type 
    class = object
      y: integer;
    end;
    T = object(class)
      x: integer;
      procedure f1;
      procedure f2; virtual;
      function  f3 : integer; 
      function  f4(i : integer) : integer ; virtual;
      constructor init(i : integer);
      destructor  remove; 
    end;     
    PT = ^T;
var
    obj : PT;
procedure T.f1;
begin
   x := y;
end;

procedure T.f2;
begin
end;

function T.f3 : integer; 
begin
	f3 := x;
end;
function  T.f4(i : integer) : integer;
begin
	x := i;
	f4 := 0; 
	self.x := 0;
	i := self.f3;
end; 

constructor T.init(i : integer);
begin
	x := i;
end;

destructor  T.remove;
begin
end; 

begin
    obj := New(PT);		
    New(obj);		 
    obj := New(PT);
    obj := New(PT, Init(1));		
    obj^.f1;
    obj^.f2;
    obj^.f4(1);
    Dispose(obj);
    Dispose(obj, Remove);
end.
