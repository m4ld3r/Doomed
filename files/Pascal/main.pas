program power;
var a, i, pow, ans: integer;
begin
     writeln ( ‘Возведение в степень’ ) ;
     write ( ‘Введите основание a >> ’ ) ;
     readln ( a ) ;
     write ( ‘Введите степень pow >> ’ ) ;
     readln ( pow ) ;
     ans := 1;
     for i := 1 to pow do
         ans := ans * a;
     writeln ( ‘ans = ’, ans ) ;
end.
