ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c      written by the UFO converter
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc

      SUBROUTINE COUP1()

      IMPLICIT NONE
      INCLUDE 'model_functions.inc'

      DOUBLE PRECISION PI, ZERO
      PARAMETER  (PI=3.141592653589793D0)
      PARAMETER  (ZERO=0D0)
      INCLUDE 'input.inc'
      INCLUDE 'coupl.inc'
      GC_1 = -(MDL_EE*MDL_COMPLEXI)/3.000000D+00
      GC_2 = (2.000000D+00*MDL_EE*MDL_COMPLEXI)/3.000000D+00
      GC_3 = -(MDL_EE*MDL_COMPLEXI)
      GC_76 = (MDL_EE*MDL_COMPLEXI*MDL_SW)/(3.000000D+00*MDL_CW)
      GC_77 = (-2.000000D+00*MDL_EE*MDL_COMPLEXI*MDL_SW)/(3.000000D+00
     $ *MDL_CW)
      GC_79 = (MDL_EE*MDL_COMPLEXI*MDL_SW)/MDL_CW
      GC_83 = -(MDL_CW*MDL_EE*MDL_COMPLEXI)/(2.000000D+00*MDL_SW)
     $ -(MDL_EE*MDL_COMPLEXI*MDL_SW)/(6.000000D+00*MDL_CW)
      GC_84 = (MDL_CW*MDL_EE*MDL_COMPLEXI)/(2.000000D+00*MDL_SW)
     $ -(MDL_EE*MDL_COMPLEXI*MDL_SW)/(6.000000D+00*MDL_CW)
      GC_94 = -(MDL_COMPLEXI*MDL_LAM1*MDL_VEV)
      GC_114 = -((MDL_COMPLEXI*MDL_YC)/MDL_SQRT__2)
      GC_117 = -((MDL_COMPLEXI*MDL_YDO)/MDL_SQRT__2)
      GC_146 = -((MDL_COMPLEXI*MDL_YS)/MDL_SQRT__2)
      GC_157 = -((MDL_COMPLEXI*MDL_YUP)/MDL_SQRT__2)
      END
