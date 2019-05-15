#include "ptoc.h"


typedef unsigned char short_;
#define min_short_ 1
#define max_short_ 10

typedef integer as_[max_short_-min_short_+1];
typedef char tarr[11];
typedef unsigned char color;
enum {   red, blue, green, yellow, white, last_color}; 
typedef set16 cset;
typedef char str11[11];
typedef struct rec {
           integer x;	   
           integer y;
           color c;
           union {
               real r;
                                /*no components*/
               struct {boolean p, q; tarr v;} s_green;
               struct {integer f[2], g[2];} s_yellow;
           } u;
} rec;			   
typedef rec* recptr;
typedef struct complex { real im, re; } complex;

static const complex zero = {0.0, 0.0};
static const as_ primes = {1, 3, 5, 7, 11, 13, 17, 19, 23, 29};
static const char hello[] = "Hello world";
#define letters setof('a', 'b', range('p','q'), 'z', eos)

static const real pi = 3.14;  

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

integer a[last_color];        
recptr p;
tarr arr;
str11 str;
struct {
         integer i;
         struct A1 {
                 integer j;
                 struct A2 {
                        integer k;
                 } r;
         } rr;
} rrr;

/*** Procedures declaration ***/ 

void recursive_proc();

static void inner(integer* out)
{
   i = (short_)(i);
   *out = 0;
   recursive_proc();
}    /* inner */

void recursive_proc()
{
   integer out;

   inner(&out);
}


str11* foo(str11 foo_result, const integer l, const integer h, char* a, char* b);

static integer i1, j2, k1;

static real p1[10][10];

static real q[10][10];

static const real e = 2.81;


#define empty_set setof(eos)

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
    memcpy(p1, q, 10*sizeof(*p1)); 
    f1_result = i1 + g(h);
    return f1_result;
}   /*f1*/

static integer f2(const integer l1, const integer h1, const integer l2, const integer h2, real const* m)
             ;


static integer g1(integer* i) /*yet another g*/
{
    integer g1_result;
    g1_result = trunc(m[1*(h1-l1+1) + 1 - l2]);
    cs = JOIN(cs, (ELEM(red)|ELEM(green)));
    if (EQUIVALENT(cs, 0))  cs = 0;

    switch (*i) {
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



static integer f2(const integer l1, const integer h1, const integer l2, const integer h2, real const* m)

/*
 * function g (inside f2)
 */
{
    integer i, j;

      /*f2*/
    integer f2_result;
    for( i = l1; i <= h1; i ++)
        for( j = h2; j >= l2; j --)
            m[i*(h1-l1+1) + j - l2] = m[j*(h1-l1+1) + i - l2];
    f2_result = g1(&i);
    return f2_result;
}        /*f2*/

str11* foo(str11 foo_result, const integer l, const integer h, char* a, char* b)
{
    boolean bool_;
    real r;
    rec struct_;
    file(rec) f = VOID_FILE;



      /*foo*/
    i1 = 1;
    do {
        j2 = 1;
        while (j2 < 012) 
        {
            q[i1-(1)][j2-(1)] = 1.0;
            j2 = j2 + 1;
        }
        i1 = i1 + 1;
    } while (!(i1 == 10));

    arrcpy(p1, q);
    bool_ = true;
    i1 = 1;
    j2 = i1 + 1;
    k1 = (i1 + j2) * 2 / 2;  
    r = pi;

    cwrite("bool = %bi = %2ir = %5.3f\n", bool_, i1, r);  
    cwrite("bool = %bi = %2ir = %5.3f", bool_, i1, r);  
    twrite(&output, "bool = %bi = %2ir = %5.3f\n", bool_, i1, r);  
    twrite(&output, "bool = %bi = %2ir = %5.3f", bool_, i1, r);  

    struct_.u.s_green.p = struct_.u.s_green.q;
    if (! eof(input)) 
       cread("%i%s%i\n", &i1, 0, items(struct_.u.s_green.v)-1, struct_.u.s_green.v, &j2);
    tread(&input, "%i%s%i", &i1, 0, items(struct_.u.s_green.v)-1, struct_.u.s_green.v, &j2);

    swrite(f, struct_), swrite(f, struct_);
    sread(f, struct_), sread(f, struct_);
    struct_ = *currec(f);
    store(f, struct_);

    i1 = f1() + f1(); 
    j2 = f2(1, items(p1), 1, items(*p1), *p1) + f2(1, items(q), 1, items(*q), *q);
    k1 = i1 % j2;

    memcpy(foo_result, "abcdefgijkl", sizeof(str11));

#undef empty_set

    return (str11*)foo_result;
}   /*foo*/



int main(int argc, const char* argv[])
{
    str11 temp1;
    str11 temp2;
    pio_initialize(argc, argv);
    if (arrcmp(arr, "aaaaaaaaaaa") > 0) 
       foo(str, array("hello"),"world");
    foo(str, 1, items(*foo(temp1, 1, items(str), str,str)), *foo(temp1, 1, items(str), str,str),*foo(temp2, 1, items(str), str,str)); 
    a[green] = 0377; 
    a[red] = 0xff00; 
    a[blue] = 0; 
    arrcpy(str, "\"a*z\"'\"A*Z\""); 
    str[4] = '\'';  
    str[4] = '-';  
    cwrite("%s\n", 0, items(arr)-1, arr);

    if (inset(c, letters))  alp = join(alp, setof(range('0','9'), range('a','f'), eos));

    p = (rec*)malloc(sizeof(rec));
    p->x = 1;
    p->x = p->y;
    *p = *p;
    cp = &zero;
    {
        rec* with = p;
        complex* with1 = cp; 

        with->x = 1;
        with->y = 2;
        with1->re = with1->im;
        with->u.r = with1->re;
        with1->im = with->u.r;
    }
    free(p);
    {
       struct A1* with1 = &rrr.rr;
       struct A2* with2 = &rrr.rr.r; 

       rrr.i = with1->j;
       with1->j = with2->k;
    }
    return EXIT_SUCCESS;
}


