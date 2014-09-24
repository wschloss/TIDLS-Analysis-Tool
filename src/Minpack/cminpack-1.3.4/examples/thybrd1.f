C     DRIVER FOR HYBRD1 EXAMPLE.
C     DOUBLE PRECISION VERSION
C
C     **********
      INTEGER J,N,INFO,LWA,NWRITE
      DOUBLE PRECISION TOL,FNORM
      DOUBLE PRECISION X(9),FVEC(9),WA(180)
      DOUBLE PRECISION ENORM,DPMPAR
      EXTERNAL FCN
C
C     LOGICAL OUTPUT UNIT IS ASSUMED TO BE NUMBER 6.
C
      DATA NWRITE /6/
C
      N = 9
C
C     THE FOLLOWING STARTING VALUES PROVIDE A ROUGH SOLUTION.
C
      DO 10 J = 1, 9
         X(J) = -1.D0
   10    CONTINUE
C
      LWA = 180
C
C     SET TOL TO THE SQUARE ROOT OF THE MACHINE PRECISION.
C     UNLESS HIGH PRECISION SOLUTIONS ARE REQUIRED,
C     THIS IS THE RECOMMENDED SETTING.
C
      TOL = DSQRT(DPMPAR(1))
C
      CALL HYBRD1(FCN,N,X,FVEC,TOL,INFO,WA,LWA)
      FNORM = ENORM(N,FVEC)
      WRITE (NWRITE,1000) FNORM,INFO,(X(J),J=1,N)
      STOP
 1000 FORMAT (5X,31H FINAL L2 NORM OF THE RESIDUALS,D15.7 //
     *        5X,15H EXIT PARAMETER,16X,I10 //
     *        5X,27H FINAL APPROXIMATE SOLUTION // (5X,3D15.7))
C
C     LAST CARD OF DRIVER FOR HYBRD1 EXAMPLE.
C
      END
      SUBROUTINE FCN(N,X,FVEC,IFLAG)
      INTEGER N,IFLAG
      DOUBLE PRECISION X(N),FVEC(N)
C

C     SUBROUTINE FCN FOR HYBRD1 EXAMPLE.
C
      INTEGER K
      DOUBLE PRECISION ONE,TEMP,TEMP1,TEMP2,THREE,TWO,ZERO
      DATA ZERO,ONE,TWO,THREE /0.D0,1.D0,2.D0,3.D0/
C
      DO 10 K = 1, N
         TEMP = (THREE - TWO*X(K))*X(K)
         TEMP1 = ZERO
         IF (K .NE. 1) TEMP1 = X(K-1)
         TEMP2 = ZERO
         IF (K .NE. N) TEMP2 = X(K+1)
         FVEC(K) = TEMP - TEMP1 - TWO*TEMP2 + ONE
   10    CONTINUE
      RETURN
C
C     LAST CARD OF SUBROUTINE FCN.
C
      END