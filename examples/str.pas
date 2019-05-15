type
   string =  array [1..20] of char;
var 
   s : string;
   c : char;
procedure print(s : string);
begin
   writeln('"', s, '"');
end;
procedure puts(s : array [lo..hi :intger] of char);
begin
   writeln('"', s, '"');
end;

begin
   s := 'abd s''Anto s''Pet';
   print(s);
   print('abc');
   print('a');
   print('');
   puts('abc');
   puts('a');
   puts('');
   c := 'a';
end.