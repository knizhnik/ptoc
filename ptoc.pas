const
   maxint = 2147483647; 

type
   word	    = 0..65535; 
   byte	    = -128..127;

var
   input  : text;
   output : text;

function inc(x :  integer) : integer; external;

function dec(x :  integer) : integer; external;

function abs(x : real) : real; external;

function arctan(x : real) : real; external;

function bitsize(x : integer) : integer; external;

function size(x : integer) : integer; external;

function chr(x : integer) : char; external;

function cos(x : real) : real; external;

function eof(f : text) : boolean; external;

function eoln(f : text) : boolean; external;

function exp(x :  real) : real; external;

function ioerror(f : text) : boolean; external;

function iostatus(f : text) : integer; external;

function ln(x : real) : real; external;

function odd(x : integer) : boolean; external;

function ord(c : char) : integer; external;

function pred(x : integer) : integer; external;

function ref(x : integer) : ^integer; external;

function round(x : real) : integer; external;

function sin(x : real) : real; external;

function sqr(x : real) : real; external;

function sqrt(x : real) : real; external;

function succ(x : integer) : integer; external;

function time : real; external;

procedure timestamp(var day, month, year, hour, min, sec : integer); external;

function  trunc(x : real) : integer; external;


procedure break(x : text); external;

procedure close(x : text); external;

procedure delete(x : text); external;

procedure get(x : text); external;

procedure noioerror; external;

procedure pack(a : array [l..h:integer] of integer; i : integer; 
	       z : integer); 
external; 

procedure unpack(z : integer; 
	         var a : array [l..h:integer] of integer; i : integer);
external;

procedure page(f : text); external;

procedure put(x : text); external;

procedure assign(f : text; name : zero_terminated_string );
external;
		   
procedure rename(f : text; name : zero_terminated_string );
external;

procedure open(f : text; name, history : zero_terminated_string;
	       var error_code : integer ); 
external; 

procedure reset(f : text; name, options : zero_terminated_string;
		var error_code : integer ); 
external; 

procedure rewrite(f: text; name, options: zero_terminated_string;
		  var error_code : integer);
external; 
		  
procedure seek(s : text; offset : integer); 
external;

