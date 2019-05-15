program main (input, output);
var
   t	   : text;
   i, j, k : integer;
   s	   : packed array [1..10] of char;
begin
   writeln('Hello world !');
   rewrite(t, 'test.txt');
   writeln(t, 1, 2, 3, 'hello');
   reset(t);
   readln(t, i, j, k, s);
   writeln('i =', i, ', j =', j, ', k =', k, ', s = "', s, '"');
   close(t);
end.
