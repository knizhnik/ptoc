#include "ptoc.h"


typedef unsigned char short_;
const int min_short_ = 1;
const int max_short_ = 10;
typedef array<min_short_,max_short_,integer> as_;
typedef array<0,10,char> tarr;
enum color {red, blue, green, yellow, white, last_color}; 
typedef set_of_enum(color) cset;
typedef array<1,11,char> str11;
struct rec {
           integer x;	   
           integer y;
           color c;
           union {
               real r;
                                /*no components*/
               struct {boolean p, q; tarr v;} s_green;
               struct {array<1,2,integer> f, g;} s_yellow;
           };
};			   
typedef rec* recptr;
struct complex { real im, re; };

const complex zero = {0.0, 0.0};
const as_ primes = {{1, 3, 5, 7, 11, 13, 17, 19, 23, 29}};
const char hello[] = "Hello world";
const set letters = set::of('a', 'b', range('p','q'), 'z', eos); 
const real pi = 3.14;  

cset cs; 
integer i, j, k;   /* integer variables */   
char c;
complex* cp; 
set alp;
enum {     one,   /*1*/
           two,   /*2*/
           three, /*3*/
           four,  /*4*/
           five} state; /*5*/

array<0,last_color,integer> a;        
recptr p;
tarr arr;
str11 str;
struct A2 {
         integer i;
         struct A1 {
                 integer j;
                 struct A3 {
                        integer k;
                 } r;
         } rr;
} rrr;

/*** Procedures declaration ***/ 

void recursive_proc();

static void inner(integer& out)
{
   i = (short_)(i);
   out = 0;
   recursive_proc();
}    /* inner */

void recursive_proc()
{
   integer out;

   inner(out);
}


str11 foo(conf_array<char> a, conf_array<char> b);

static integer i1, j2, k1;

static matrix<1,10, 1,10,real> p1;

static matrix<1,10,1,10,real> q;

const real e = 2.81;


const set empty_set = set::of(eos);

static integer f1();

typedef integer x;



static void h(integer x) 
{; 
}    



/* function g (inside f1) */
static integer g(void (*f)(integer x))
{
    integer g_result;
    if (k1 < 0)  g_result = j2;
    else g_result = trunc(e) + -j2;
    j2 = succ(color,red);
    f(0);
    return g_result;
}   /*g*/



static integer f1()

{     /*f1*/
    integer f1_result;
    p1 = q; 
    f1_result = i1 + g(h);
    return f1_result;
}   /*f1*/

static integer f2(conf_matrix<real> m)
             ;


static integer g1(conf_matrix<real>& m, integer& i) /*yet another g*/
{
    const int l1 = m.low1;
    const int h1 = m.high1;
    const int l2 = m.low2;
    const int h2 = m.high2;
    copy_conformant_array(m);
    integer g1_result;
    g1_result = trunc(m[1][1]);
    cs = cs + set_of_enum(color)::of(red, green, eos);
    if (cs == set_of_enum(color)::of(eos))  cs = set_of_enum(color)::of(eos);

    switch (i) {
      case RANGE_26('a','z'): case RANGE_10('0','9'): g1_result = 0;
      break;
      case RANGE_32(0,31): g1_result = 32;
      break;
      case -1 : g1_result = -1; break; 
      case 1  : {
              g1_result = 1;
           }
           break;
      default: g1_result = 0; 
    } 
    return g1_result;
}            /*g*/



static integer f2(conf_matrix<real> m)

/*
 * function g (inside f2)
 */
{
    integer i, j;

      /*f2*/
    const int l1 = m.low1;
    const int h1 = m.high1;
    const int l2 = m.low2;
    const int h2 = m.high2;
    copy_conformant_array(m);
    integer f2_result;
    for( i = l1; i <= h1; i ++)
        for( j = h2; j >= l2; j --)
            m[i][j] = m[j][i];
    f2_result = g1(m, i);
    return f2_result;
}        /*f2*/

str11 foo(conf_array<char> a, conf_array<char> b)
{
    boolean bool_;
    real r;
    rec struct_;
    file<rec> f;


      /*foo*/
    const int l = a.low;
    const int h = a.high;
    str11 foo_result;
    i1 = 1;
    do {
        j2 = 1;
        while (j2 < 012) 
        {
            q[i1][j2] = 1.0;
            j2 = j2 + 1;
        }
        i1 = i1 + 1;
    } while (!(i1 == 10));

    p1 = q;
    bool_ = true;
    i1 = 1;
    j2 = i1 + 1;
    k1 = (i1 + j2) * 2 / 2;  
    r = pi;

    output << "bool = " << btos(bool_) << "i = " << format(i1,2) << "r = " << format(r,5,3) << NL;  
    output << "bool = " << btos(bool_) << "i = " << format(i1,2) << "r = " << format(r,5,3);  
    output << "bool = " << btos(bool_) << "i = " << format(i1,2) << "r = " << format(r,5,3) << NL;  
    output << "bool = " << btos(bool_) << "i = " << format(i1,2) << "r = " << format(r,5,3);  

    struct_.s_green.p = struct_.s_green.q;
    if (! eof()) 
       input >> i1 >> struct_.s_green.v >> j2 >> NL;
    input >> i1 >> struct_.s_green.v >> j2;

    f << struct_ << struct_;
    f >> struct_ >> struct_;
    struct_ = *f;
    store(f, struct_);

    i1 = f1() + f1(); 
    j2 = f2(p1) + f2(q);
    k1 = i1 % j2;

    foo_result = "abcdefgijkl";
    return foo_result;
}   /*foo*/



int main(int argc, const char* argv[])
{
    pio_initialize(argc, argv);
    if (arr > "aaaaaaaaaaa") 
       str = foo("hello","world");
    str = foo(foo(str,str),foo(str,str)); 
    a[green] = 0377; 
    a[red] = 0xff00; 
    a[blue] = 0; 
    str = "\"a*z\"'\"A*Z\""; 
    str[5] = '\'';  
    str[5] = '-';  
    output << arr << NL;

    if (letters.has(c))  alp = alp + set::of(range('0','9'), range('a','f'), eos);

    p = new rec;
    p->x = 1;
    p->x = p->y;
    *p = *p;
    cp = &zero;
    {
        rec& with = *p;
        complex& with1 = *cp; 

        with.x = 1;
        with.y = 2;
        with1.re = with1.im;
        with.r = with1.re;
        with1.im = with.r;
    }
    delete p;
    {
       A2::A1& with1 = rrr.rr;
       A2::A1::A3& with2 = rrr.rr.r; 

       rrr.i = with1.j;
       with1.j = with2.k;
    }
    return EXIT_SUCCESS;
}


