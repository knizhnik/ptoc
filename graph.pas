unit graph;

interface
{*****  Dos Style - Const  *****}
const
  {for SetBkColor, SetColor, SetFillStyle, SetRGBPalette / 16Color}
    Black            =  0;
    Blue             =  1;
    Green            =  2;
    Cyan             =  3;
    Red              =  4;
    Magenta          =  5;
    Brown            =  6;
    LightGray        =  7;
    DarkGray         =  8;
    LightBlue        =  9;
    LightGreen       = 10;
    LightCyan        = 11;
    LightRed         = 12;
    LightMagenta     = 13;
    Yellow           = 14;
    White            = 15;

  {for SetLineStyle}
    SolidLn          =  0;
    DottedLn         =  1;
    CenterLn         =  2;
    DashedLn         =  3;
    UserBitLn        =  4;
    NormWidth        =  1;
    ThickWidth       =  3;

  {for SetTextJustify}
    LeftText         =  0;
    CenterText       =  1;
    RightText        =  2;
    BottomText       =  0;
   {CenterText       =  1;}
    TopText          =  2;
  {for SetTextStyleÅ}
    DefaultFont      =  0; 
    TriplexFont      =  1; 
    SmallFont        =  2;
    SansSerifFont    =  3;
    GothicFont       =  4;
    HorizDir         =  0;
    VertDir          =  1;

  {for SetFillStyle}
    EmptyFill        =  0;  
    SolidFill        =  1;  
    LineFill         =  2;  {-----}
    LtSlashFill      =  3;  {/////}
    SlashFill        =  4;  {/////}
    BkSlashFill      =  5;  {\\\\\}
    LtBkSlashFill    =  6;  {\\\\\}
    HatchFill        =  7;  {+++++}
    XHatchFill       =  8;  {XXXXX}
    InterleaveFill   =  9;  
    WideDotFill      = 10;  
    CloseDotFill     = 11;  
    UserFill         = 12;  

  {for SetWriteMode}
    CopyPut          =  0; { MOV }
    XORPut           =  1; { XOR }

  {Graphics drivers constants }

    detect = 0;
    cga = 1;
    mcga = 2;
    ega = 3;
    ega64 = 4;
    egamono = 5;
    ibm8514 = 6;
    hercmono = 7;
    att400 = 8;
    vga = 9;
    pc3270 = 10;

  { graphics modes constants. }
    cgac0 = 						0;
    cgac1 = 						1;
    cgac2 = 						2;
    cgac3 = 						3;
    cgahi = 						4;
    cgac0 = 						0;
    mcgac1 = 						1;
    mcgac2 = 						2;
    mcgac3 = 						3;
    mcgamed = 						4;
    mcgahi = 						5;
    egalo = 						0;
    egahi = 						1;
    ega64lo = 						0;
    ega64hi = 						1;
    egamonohi = 					3;
    hercmonohi = 					0;
    att400c0 = 					        0;
    att400c1 = 					        1;
    att400c2 = 					        2;
    att400c3 = 				        	3;
    att400med = 					4;
    att400hi = 					        5;
    vgalo = 						0;
    vgamed = 						1;
    vgahi = 						2; 
    pc3270hi = 	   				        0;
    ibm8514lo = 					0;
    ibm8514hi = 					1;
    

  {Graphics error codes}

    grok = 0;
    grnoinitgraph = -1;
    grnotdetected = -2;
    grfilenotfound = -3;
    grinvaliddriver	= -4;
    grnoloadmem = -5;
    grnoscanmem = -6;
    grnofloodmem = -7;
    grfontnotfound = -8;
    grnofontmem = -9;
    grinvalidmode =	-10;
    grerror = -11;
    grioerror = -12;
    grinvalidfont = -13;
    grinvalidfontnum = -14;
    grinvaliddevicenum = -15;
    grinvalidversion = -18;

    TopOn = true;
    TopOff = false;

    ClipOn = true;
    ClipOff = false;

    UserCharSize = 0;

{*****  Dos Style - Type  *****}
type
  Tcolor =  integer;
   
  ArcCoordsType = record
     x, y, 
     xstart, ystart,
     xend, yend : integer;
  end;

  FillPatternType = array [1..8] of byte;

  FillSettingsType = record
     pattern : word;
     color   : word;
   end;

  LineSettingsType = record
     linestyle : word;
     pattern   : word;
     thickness : word;
   end;

  const
     MaxColors = 15;
  type
     PaletteType = record
       size    : byte;
       colors  : array[0..maxcolors] of shortint;
     end;

  PointType = record
     x, y : integer;
   end;

  TextSettingsType = record
     font      : word;
     direction : word;
     charsize  : word;
     horiz     : word;
     vert      : word;
   end;

  ViewPortType = record
     x1, y1, x2, y2 : integer;
     clip           : boolean;
   end;

  PointsType = array [1..100] of integer;

procedure InitGraph(var GraphDrv, GraphMode : integer;
			path_to_driver	    : zero_terminated_string);
		    
procedure CloseGraph;


function  GetMaxX : integer;
function  GetMaxY : integer;

function  GetX : integer;
function  GetY : integer;

procedure SetViewPort(x1, y1, x2, y2: integer; clip: Boolean);

procedure SetFillStyle(Pattern, Color: word);
procedure SetFillPattern(upattern : FillPatternType; Color: word);
procedure SetLineStyle(LineStyle, Pattern, Thickness: word);
procedure SetWriteMode(WriteMode: integer);

procedure GetArcCoords(var ArcCoords: ArcCoordsType);

procedure GetFillSettings(var FillInfo: FillSettingsType);
procedure GetFillPAttern(var FillPattern:  FillPatternType);
procedure GetLineSettings(var LineInfo: LineSettingsType);

function  GetDriverName : zero_terminated_string;
function  GetGraphMode : integer;
procedure SetGraphMode(mode : integer);
function  GetModeName(GraphMode	: integer): string;

procedure GetAspectRatio(var ax, ay : word); 
procedure SetAspectRatio(ax, ay : word); 

procedure SetUserCharSize(multx, divx, multy, divy : word);

procedure GetTextSettings(var TextInfo : TextSettingsType);
procedure GetViewSettings(var ViewPort: ViewPortType);

procedure PutPixel(X, Y, Pixel : integer);
function  GetPixel(X, Y : integer) : integer;

function  GraphResult : integer; 
function  GraphErrorMsg(code : integer) : zero_terminated_string;

function  ImageSize(x1, y1, x2, y2 : integer) : integer;
procedure GetImage(x1, y1, x2, y2 : integer; p : pointer);
procedure PutImage(x, y	: integer; p : pointer; i : integer); 

procedure Arc(x, y : integer; StAngle, EndAngle, Radius: Word);
procedure Bar(x1, y1, x2, y2 : integer);
procedure Bar3D(x1, y1, x2, y2 : integer; Depth: word; Top: boolean);
procedure Circle(X, Y : integer; Radius : word);
procedure DrawPoly(NumPoints : word; var Points : integer);
procedure Ellipse(x, y: integer; StAngle, EndAngle, XRadius, YRadius: Word);
procedure FillEllipse(x, y: integer; XRadius, YRadius: Word);
procedure FillPoly(NumPoints : word; Points : PointsType); external c;
procedure FloodFill(X, Y : integer; Color: TColor);
procedure MoveTo(X, Y : integer);
procedure LineTo(X, Y : integer);
procedure Line(x1, y1, x2, y2 : integer);
procedure LineRel(Dx, Dy : integer);
procedure MoveRel(Dx, Dy : integer);
procedure PieSlice(x, y: integer; StAngle, EndAngle, Radius: Word);
procedure Rectangle(x1, y1, x2, y2 : integer);
procedure RoundRect(x1, y1, x2, y2, x3, y3 : integer);
procedure Sector(x, y: integer; StAngle, EndAngle, XRadius, YRadius: Word);

{ *** color and palette routines *** }
procedure SetBkColor(Color : TColor);
procedure SetColor(Color : TColor);
function  GetColor : TColor;
procedure SetRGBPalette(I, R, G, B: word);
procedure SetAllPalette(Palette	: PaletteType );
procedure SetPalette(ColorNum	: word; Color : shortint);
procedure SetRGBPalette(ColorNum : word; red, green, blue : byte);

function  GetBkColor: word;
procedure GetDefaultPalette(var Palette: PaletteType);
function  GetMaxColor: word;
procedure GetPalette(var Palette: PaletteType);

{ *** text routines *** }
procedure OutText(Text: zero_terminated_string);
procedure OutTextXY(X, Y: Integer; Text: zero_terminated_string);
procedure SetTextJustify(Horiz, Vert: word);
procedure SetTextStyle(Font, Direction, CharSize: Word);
function  TextHeight(Text : zero_terminated_string) : integer;
function  TextWidth(Text : zero_terminated_string) : integer;


function KeyPressed : Boolean;
function ReadKey    : Char;

procedure Delay(msec : integer);

procedure ClearViewPort;
procedure ClearDevice;

implementation 
end.	       