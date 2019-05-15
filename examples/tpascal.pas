program main;

label 1;

function print(s : string) : string;
begin
   writeln(s, ':', s+'!':10);
   print := s;
end;

type
   str10   = string[10];
   struct  = record
		i : integer;
		f : double;
		s : string[20];
		a : array [1..2] of boolean;
		       c : record re, im : real; end;
	     end; 
   records = array [1..3] of struct;
   list	   = array [1..5] of string;
   complex =  record re, im : real; end;
   handler = function (error : integer) : integer;
   callback_1 = procedure;
   callback_2 = procedure(s : string);
		 
const
   zero : complex = (re:0.0; im:0.0);
   recs	: records = ((i:1;f:1.0;s:'first record'; a:(true,true); c:(re:0.0; im:0.0)),
		     (i:2;f:2.0;s:'second record'; a:(true, false)),
		     (i:3;f:4.0;s:'third record'));
   lst : list	  = ('one','two','three','four','five');


var
   s  : string[5];
   ss : str10;
   f  : text;
   i  : longint;
   ip : ^longint;
   hnd : handler; 
   cb1 : callback_1;
   cb2 : callback_2;

const
   x : double = 0.5;
   c	      = #12;
   crlf	      = #13#10;
   beep	      = #7'Beep '#7#7#7'!';

function exception_handler(error : integer) : integer;  far;
begin
   writeln('exception', error, ' is raised');
   exception_handler := error;
end;

procedure my_callback_1; far;
var
   i : integer;
function foo : integer;
begin
   foo := i;
end; { foo }
begin
   i := 1998;
   writeln(foo);
end;

procedure my_callback_2 (msg : string); far;
begin
   writeln(msg);
end;

procedure raise(f1 : handler; p1 : callback_1; p2 : callback_2);
begin
   hnd := f1;
   cb1 := p1;
   cb2 := p2;
   hnd(1);
   cb2('exception');
end;

procedure dummy(var F);
begin
end;

begin
   raise(exception_handler, my_callback_1, my_callback_2);
   dummy(i);
   write(beep+crlf);
   print('hello world');
   s := 'hi';
   s[1] := lst[1][1];
   print(s);
   ss := 'hi' + ' ' + 'everybody';
   print(ss);
   s := ss;
   ss := print(s);
   print(ss);
   assign(f, 'test.txt');
   rewrite(f);
   writeln(f, 'Hello world', 1997:5);
   close(f);
   i := i xor (i shr 2);
   ip := @i;
   ip^ := $ABCD;
end.






