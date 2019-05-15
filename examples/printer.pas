unit printer;
interface
var
    LST : text;
implementation
begin
   assign(LST, 'prn');
   rewrite(LST);
end.
