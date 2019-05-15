type
   smallstr = array [1..64] of char;

procedure foo(var x : integer; a : smallstr); external c; 



procedure sprintf(var s	     : smallstr;
		      format : zero_terminated_string); external c;
		      
		      
procedure main(a : array [lo..hi : integer] of char);
var
   i : integer;
   s :  smallstr;
begin 
   foo(i, a);
   sprintf(s, a, i);
   sprintf('s', 'a', i);
end;
	     
type 
   