// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
/*
 * IDct10 -- the reduced inverse transform belonging to the On2 VP6 decoder
 * that game.dat links (the donor's name: the transform for blocks of at
 * most ten coefficients).  Retail body at RVA 0x001D6660 (1529 bytes):
 * calls dequant_slow10 (0x001D65A0, Code/Libraries/Source/VP6/Dequant.cpp)
 * into a 64-entry int32 block, runs the first pass over the four leading
 * rows and the second pass over the eight columns into the int16 output.
 * It sits in the codec's region of the image, directly ahead of IDct1
 * (0x001D6C60).  VP6 descends from On2's VP3, and this helper is
 * VP3-heritage text that On2 carried into VP6.
 *
 * Text donor: libtheora 1.0alpha3, lib/idct.c, IDct10 (as Open-BFME-1
 * records it) -- Xiph.org's BSD-licensed copy of the same On2 VP3 text
 * (Copyright (c) 2002, Xiph.org Foundation; COPYING in this directory is the
 * licence that covers the text).
 * Carried via Open-BFME-1 game/GameEngine/Source/Common/Rva009C5D60.cpp
 * (submodule fea964f854, compiled there with the flags above), whose
 * lotrbfme.exe body is byte-identical to retail here once relocation slots
 * are set aside; the libtheora names are restored.
 *
 * libtheora itself is NOT linked into game.dat (see IDct1.c): the retail
 * body is On2 VP6 decoder code, so the ledger row carries no vendored= claim.
 */
typedef short ogg_int16_t;
typedef short Q_LIST_ENTRY;
typedef int ogg_int32_t;

void dequant_slow10( ogg_int16_t *first, ogg_int16_t *second,
                     ogg_int32_t *result );

#define IdctAdjustBeforeShift 8
#define xC1S7 64277
#define xC2S6 60547
#define xC3S5 54491
#define xC4S4 46341
#define xC5S3 36410
#define xC6S2 25080
#define xC7S1 12785

void IDct10( Q_LIST_ENTRY * InputData,
             ogg_int16_t *QuantMatrix,
             ogg_int16_t * OutputData ){
  ogg_int32_t IntermediateData[64];
  ogg_int32_t * ip = IntermediateData;
  ogg_int16_t * op = OutputData;

  ogg_int32_t _A, _B, _C, _D, _Ad, _Bd, _Cd, _Dd, _E, _F, _G, _H;
  ogg_int32_t _Ed, _Gd, _Add, _Bdd, _Fd, _Hd;
  ogg_int32_t t1, t2;

  int loop;

  dequant_slow10( QuantMatrix, InputData, IntermediateData );

  /* Inverse DCT on the rows now */
  for ( loop = 0; loop < 4; loop++){
    /* Check for non-zero values */
    if ( ip[0] | ip[1] | ip[2] | ip[3] ){
      t1 = (xC1S7 * ip[1]);
      t1 >>= 16;
      _A = t1;

      t1 = (xC7S1 * ip[1]);
      t1 >>= 16;
      _B = t1 ;

      t1 = (xC3S5 * ip[3]);
      t1 >>= 16;
      _C = t1;

      t2 = (xC5S3 * ip[3]);
      t2 >>= 16;
      _D = -t2;


      t1 = (xC4S4 * (_A - _C));
      t1 >>= 16;
      _Ad = t1;

      t1 = (xC4S4 * (_B - _D));
      t1 >>= 16;
      _Bd = t1;


      _Cd = _A + _C;
      _Dd = _B + _D;

      t1 = (xC4S4 * ip[0] );
      t1 >>= 16;
      _E = t1;

      _F = t1;

      t1 = (xC2S6 * ip[2]);
      t1 >>= 16;
      _G = t1;

      t1 = (xC6S2 * ip[2]);
      t1 >>= 16;
      _H = t1 ;


      _Ed = _E - _G;
      _Gd = _E + _G;

      _Add = _F + _Ad;
      _Bdd = _Bd - _H;

      _Fd = _F - _Ad;
      _Hd = _Bd + _H;

      /* Final sequence of operations over-write original inputs. */
      ip[0] = (ogg_int16_t)((_Gd + _Cd )   >> 0);
      ip[7] = (ogg_int16_t)((_Gd - _Cd )   >> 0);

      ip[1] = (ogg_int16_t)((_Add + _Hd )  >> 0);
      ip[2] = (ogg_int16_t)((_Add - _Hd )  >> 0);

      ip[3] = (ogg_int16_t)((_Ed + _Dd )   >> 0);
      ip[4] = (ogg_int16_t)((_Ed - _Dd )   >> 0);

      ip[5] = (ogg_int16_t)((_Fd + _Bdd )  >> 0);
      ip[6] = (ogg_int16_t)((_Fd - _Bdd )  >> 0);

    }

    ip += 8;                    /* next row */
  }

  ip = IntermediateData;

  for ( loop = 0; loop < 8; loop++) {
    /* Check for non-zero values (bitwise or faster than ||) */
    if ( ip[0 * 8] | ip[1 * 8] | ip[2 * 8] | ip[3 * 8] ) {

      t1 = (xC1S7 * ip[1*8]);
      t1 >>= 16;
      _A = t1 ;

      t1 = (xC7S1 * ip[1*8]);
      t1 >>= 16;
      _B = t1 ;

      t1 = (xC3S5 * ip[3*8]);
      t1 >>= 16;
      _C = t1 ;

      t2 = (xC5S3 * ip[3*8]);
      t2 >>= 16;
      _D = - t2;


      t1 = (xC4S4 * (_A - _C));
      t1 >>= 16;
      _Ad = t1;

      t1 = (xC4S4 * (_B - _D));
      t1 >>= 16;
      _Bd = t1;


      _Cd = _A + _C;
      _Dd = _B + _D;

      t1 = (xC4S4 * ip[0*8]);
      t1 >>= 16;
      _E = t1;
      _F = t1;

      t1 = (xC2S6 * ip[2*8]);
      t1 >>= 16;
      _G = t1;

      t1 = (xC6S2 * ip[2*8]);
      t1 >>= 16;
      _H = t1;


      _Ed = _E - _G;
      _Gd = _E + _G;

      _Add = _F + _Ad;
      _Bdd = _Bd - _H;

      _Fd = _F - _Ad;
      _Hd = _Bd + _H;

      _Gd += IdctAdjustBeforeShift;
      _Add += IdctAdjustBeforeShift;
      _Ed += IdctAdjustBeforeShift;
      _Fd += IdctAdjustBeforeShift;

      /* Final sequence of operations over-write original inputs. */
      op[0*8] = (ogg_int16_t)((_Gd + _Cd )   >> 4);
      op[7*8] = (ogg_int16_t)((_Gd - _Cd )   >> 4);

      op[1*8] = (ogg_int16_t)((_Add + _Hd )  >> 4);
      op[2*8] = (ogg_int16_t)((_Add - _Hd )  >> 4);

      op[3*8] = (ogg_int16_t)((_Ed + _Dd )   >> 4);
      op[4*8] = (ogg_int16_t)((_Ed - _Dd )   >> 4);

      op[5*8] = (ogg_int16_t)((_Fd + _Bdd )  >> 4);
      op[6*8] = (ogg_int16_t)((_Fd - _Bdd )  >> 4);
    }else{
      op[0*8] = 0;
      op[7*8] = 0;
      op[1*8] = 0;
      op[2*8] = 0;
      op[3*8] = 0;
      op[4*8] = 0;
      op[5*8] = 0;
      op[6*8] = 0;
    }

    ip++;                       /* next column */
    op++;
  }
}
