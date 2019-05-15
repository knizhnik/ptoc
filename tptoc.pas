const
   maxint = 2147483647; 
   pi	  = 3.14159265359;
   
type
   shortint = 0..255;
   word	    = 0..65535; 
   byte	    = -128..127;
   
var 
   input  : text;
   output : text;


function copy(s : string; p, n: integer) : string; external;

function length(s : string) : integer; external;

function upcase(c : char) : char; external;

function pos(q, z : string) : integer; external;

procedure val(s : string; var v : integer; var c :  integer); external;

procedure insert(ins, s : string; pos : integer); external;

function inc(x	: integer) : integer; external;

function dec(x :  integer) : integer; external;

function abs(x : real) : real; external;

function arctan(x : real) : real; external;

function bitsize(x : integer) : integer; external;

function sizeof(x : integer) : integer; external; { For Turbo Pascal }

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

function time : zero_terminated_string; external;

function date : zero_terminated_string; external;

procedure timestamp(var day, month, year, hour, min, sec : integer); external;

function  trunc(x : real) : integer; external;


procedure break(x : text); external;

procedure close(x : text); external;

procedure delete(x : text); external;

function filesize(x : text) : integer; external;

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

procedure reset(f : text; name, options : zero_terminated_string;
		var error_code : integer ); external; 

procedure rewrite(f: text; name, options: zero_terminated_string;
		  var error_code : integer); external; 
		  
procedure seek(s : text; offset : integer); external;

procedure halt; external; 

procedure GetMem(p : pointer; size : integer); external;
procedure FreeMem(p : pointer; size : integer); external;


function ParamStr(i : integer) : zero_terminated_string; external;

procedure Randomize; 
external;

function Random(range : integer) : integer;
external;

procedure RestoreCrtMode;
external;

procedure halt(code : integer);
external;

function readkey : integer;
external;

function keypressed : integer;
external;

function getdir : string; external;
function chdir(path : string) : integer; external;
function mkdir(path : string) : integer; external;

var 
   ParamCount  : integer;
   ioResult    : integer;
   DirectVideo : boolean;
   ExitProc    : ^integer;
   RandSeed    : integer;
