program main;
type
    short = 1..10;
    as	  = array [short] of integer;
    tarr  = array [0..10] of char;
    color = (red, blue, green, yellow, white); 
    cset  = set of color;
    str11 = array [1..11] of char;
    rec	  = record
	       x : integer;	   
	       y : integer;
	       case c : color of
	           red	         : (r : real);
		   blue          : ((*no components*));
		   green	 : (p, q: boolean; v : tarr);
		   yellow, white : (f, g : array [1..2] of integer)
	      end;			   
    recptr  = ^rec;
    complex = record im, re : real end;

const
    zero = complex(0.0, 0.0);
    primes = as(1, 3, 5, 7, 11, 13, 17, 19, 23, 29);
    hello = 'Hello world';
    letters = ['a', 'b', 'p'..'q', 'z']; 
    pi = 3.14;  

var
    cs	    : cset; 
    i, j, k : integer; { integer variables }   
    c	    : char;
    cp	    : ^complex; 
    alp	    : set of char;
    state   : (one,   {1}
               two,   {2}
               three, {3}
               four,  {4}
               five); {5}

    a : array [color] of integer;        
    p : recptr;
    arr : tarr;
    str : str11;
    rrr : record
	     i  : integer;
	     rr : record
		     j : integer;
		     r : record
			    k : integer;
			 end;
		  end;
	  end;
   
{*** Procedures declaration ***} 

procedure recursive_proc;
var
   out : integer;
procedure inner;
begin
   i := short(i);
   out := 0;
   recursive_proc;
end; { inner }
begin
   inner;
end;
	       

function Foo(var a, b : array [l..h : integer] of char) : str11;
var
    i, j, k : integer;
    bool    : boolean;
    r	    : real;
    struct  : rec;
    P	    : array [1..10, 1..10] of real;
    Q	    : array [1..10] of array [1..10] of real;
    f	    : file of rec; 

const
    e	      = 2.81;
    empty_set = [];

    function f1 : integer;
    type
        x = integer;
    
        procedure h(x : integer); 
        begin 
        end;    

(* function g (inside f1) *)
        function g(procedure f(x: integer)) : integer;
        begin
	    if k < 0 then g := j
            else g := trunc(e) + -j;
 	    j := succ(red);
            f(0)
	end {g};

    begin {f1}
        P := Q; 
        f1 := i + g(h);
    end {f1};

    function f2(M : array [l1..h1: integer; l2..h2: integer] of real) 
    : integer;
(*
 * function g (inside f2)
 *)
    var
        i, j : integer;

        function g : integer; {yet another g}
        begin
            g := trunc(M[1, 1]);
	    cs := cs + [red, green];
	    if cs = [] then cs := [];
	   
	    case i of
	      'a'..'z', '0'..'9': g := 0;
	      0..31: g := 32;
	      -1 : g := -1; 
              1  : begin
                      g := 1
		   end;
	      otherwise g := 0 
            end 
        end; {g}

    begin {f2}
        for i := l1 to h1 do
            for j := h2 downto l2 do
                M[i,j] := M[j][i];
        f2 := g;
    end; {f2}


begin {foo}
    i := 1;
    repeat
        j := 1;
        while (j < 2#1010) do
        begin
            Q[i,j] := 1.0;
            j := j + 1;
        end;
        i := i + 1;
    until i = 10;

    P := Q;
    bool := true;
    i := 1;
    j := i + 1;
    k := (i + j) * 2 div 2;  
    r := pi;

    writeln('bool = ', bool, 'i = ', i:2, 'r = ', r:5:3);  
    write('bool = ', bool, 'i = ', i:2, 'r = ', r:5:3);  
    writeln(output, 'bool = ', bool, 'i = ', i:2, 'r = ', r:5:3);  
    write(output, 'bool = ', bool, 'i = ', i:2, 'r = ', r:5:3);  

    struct.p := struct.q;
    if not eof then
       readln(i, struct.v, j);
    read(input, i, struct.v, j);

    write(f, struct, struct);
    read(f, struct, struct);
    struct := f^;
    f^ := struct;
   
    i := f1 + f1; 
    j := f2(P) + f2(Q);
    k := i mod j;

    foo := 'abcdefgijkl'
end {foo};

    

begin
    if 'aaaaaaaaaaa' < arr then
       str := foo('hello','world');
    str := foo(foo(str,str),foo(str,str)); 
    a[green] := 8#377; 
    a[red] := 16#ff00; 
    a[blue] := 77600000b; 
    str := '"a*z"''"A*Z"'; 
    str[5] := '''';  
    str[5] := '-';  
    writeln(arr);

    if c in letters then alp := alp + ['0'..'9', 'a'..'f'];

    new(p);
    p^.x := 1;
    p^.x := p^.y;
    p^ := p^;
    cp := ref(zero);
    with p^, cp^ do
    begin
        x := 1;
        y := 2;
        re := im;
        r := re;
        im := r;
    end;
    dispose(p);
    with rrr, rrr.rr, rrr.rr.r do
    begin
       i := j;
       j := k;
    end;
end.


