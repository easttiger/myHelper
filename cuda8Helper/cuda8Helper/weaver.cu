
#include<stdio.h>
#include<math.h>
const int lena = 83;
const int lenb = 1543;
float a[ lena ], b[ lenb ], x[ lena ], xnew[ lena ], tau[ lenb ];
int De[ lena * lenb ];
int tDe[ lenb * lena ];

inline float sum(float* a, const int lena) {
  float res = *a;
  for(int i = 1; i < lena; ++i) {
    res += a[ i ];
  }
  return res;
}
void transpose(int* tm, int* m, const int nrow, const int ncol) {
  for(int i = 0; i < nrow; ++i) {
    for(int j = 0; j < ncol; ++j) {
      tm[ j * nrow + i ] = m[ i * ncol + j ];
    }
  }
}
float M_v(int* M, int row, float* v, const int len) {
  float res = 0.;
  int* p = M + row * len;
  for(int i = 0; i < len; ++i) {
    if(*p++) res += v[ i ];
  }
  return res;
}


void cpuweaver(float tol) {
  float sa = sum(a, lena);
  for(int i = 0; i < lena; ++i) x[ i ] = a[ i ] / sa;
  float m = sa + sum(b, lenb);

  int iter = 0;
  float e = 999, tmp;
  for(iter = 0; e > 1e-15; ++iter) {
    for(int j = 0; j < lenb; ++j) {
      tau[ j ] = b[ j ] / M_v(tDe, j, x, lena);
    }
    for(int i = 0; i < lena; ++i) {
      xnew[ i ] = a[ i ] / (m - M_v(De, i, tau, lenb));
    }
    e = 0.;
    for(int i = 0; i < lena; ++i) {
      tmp = fabs(xnew[ i ] - x[ i ]);
      if(e < tmp) e = tmp;
    };
    for(int i = 0; i < lena; ++i) {
      x[ i ] = xnew[ i ];
    }
  }
}


void test_weaver() {
  FILE* fp;
  //load a
  fp = fopen("C:/Users/easttiger/Dropbox/Subjects/W/Weaver Paper Reading list/Hunter matlab code/a.txt", "r");
  for(int i = 0; i < lena; ++i) {
    fscanf(fp, "%f\n", a + i);
  }
  fclose(fp);
  //load b
  fp = fopen("C:/Users/easttiger/Dropbox/Subjects/W/Weaver Paper Reading list/Hunter matlab code/b.txt", "r");
  for(int i = 0; i < lenb; ++i) {
    fscanf(fp, "%f\n", b + i);
  }
  fclose(fp);
  //load b
  fp = fopen("C:/Users/easttiger/Dropbox/Subjects/W/Weaver Paper Reading list/Hunter matlab code/tDe.txt", "r");
  for(int j = 0; j < lenb; ++j) {
    for(int i = 0; i < lena - 1; ++i) {
      fscanf(fp, "%d ", tDe + j * lena + i);
    }
    fscanf(fp, "%d\n", tDe + (j + 1) * lena - 1);
  }
  fclose(fp);

  //initialize De as transpose of tDe
  transpose(De, tDe, lenb, lena);


  cpuweaver(0.00000001);
  for(int i = 0; i < lena; ++i) {
    printf("%f,", x[ i ]);
  }
}