#ifndef BUTTERWORTH_H
#define BUTTERWORTH_H
/* Digital filter designed by mkfilter/mkshape/gencode   A.J. Fisher
   Command line: /www/usr/fisher/helpers/mkfilter -Bu -Lp -o 8 -a 6.2500000000e-02 0.0000000000e+00 -l */

#define NZEROS 8
#define NPOLES 8


class Butterworth
{
public:

            Butterworth();

    double  process( double in);

private:

    double xv[NZEROS+1], yv[NPOLES+1];
};

#endif
