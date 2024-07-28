#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

void FillMatrix(S21Matrix* m, int rows_, int cols_) {
  double index = 1;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      m->SetElement(i, j, index);
      index++;
    }
  }
}
void FillMatrixNum(S21Matrix* A, double num) {
  for (int i = 0; i < A->GetRows(); ++i) {
    for (int j = 0; j < A->GetCols(); ++j) {
      (*A)(i, j) = num;
    }
  }
}

TEST(Cnstr_Default, Numer_1) {
  S21Matrix m;
  int res = 3;

  EXPECT_EQ(m.GetRows(), res);
  EXPECT_EQ(m.GetCols(), res);
}

TEST(Cnstr_par, Numer_1) {
  S21Matrix m(4, 5);

  EXPECT_EQ(m.GetRows(), 4);
  EXPECT_EQ(m.GetCols(), 5);
}

TEST(Cnstr_par, Numer_2) {
  EXPECT_THROW(S21Matrix m(0, 5), std::invalid_argument);
}

TEST(Copy, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrix(&m, m.GetRows(), m.GetCols());
  S21Matrix b = m;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(m.GetElement(i, j), b.GetElement(i, j));
    }
  }
}

TEST(Move, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrix(&m, m.GetRows(), m.GetCols());
  S21Matrix c = m;
  S21Matrix b(std::move(m));

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(c.GetElement(i, j), b.GetElement(i, j));
    }
  }
}

TEST(Set, Numer_1) {
  S21Matrix m;
  m.SetElement(1, 1, 6.);
}

TEST(Set, Numer_2) {
  S21Matrix m;
  EXPECT_THROW(m.SetRows(0), std::invalid_argument);
}

TEST(Set, Numer_3) {
  S21Matrix m;
  EXPECT_THROW(m.SetCols(0), std::invalid_argument);
}

TEST(Set, Numer_4) {
  S21Matrix m(3, 3);
  FillMatrix(&m, 3, 3);
  m.SetRows(6);
  // PrintMatrix(m);
}

TEST(Set, Numer_5) {
  S21Matrix m(3, 3);
  FillMatrix(&m, 3, 3);
  m.SetCols(6);
  // PrintMatrix(m);
}

TEST(Set, Numer_6) {
  S21Matrix m(4, 4);
  FillMatrix(&m, 4, 4);
  m.SetCols(2);
  // PrintMatrix(m);
}

TEST(Sum, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 2.);
  S21Matrix c(4, 5);
  FillMatrixNum(&c, 3.);
  S21Matrix m1(4, 5);
  FillMatrixNum(&m1, 5.);

  m.SumMatrix(c);

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(Sum, Numer_2) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 2.);
  S21Matrix c(5, 5);
  FillMatrixNum(&c, 3.);

  EXPECT_THROW(m.SumMatrix(c), std::invalid_argument);
}

TEST(OperatorPlus, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 2.);
  S21Matrix c(4, 5);
  FillMatrixNum(&c, 3.);
  S21Matrix m1(4, 5);
  FillMatrixNum(&m1, 5.);

  S21Matrix res = m + c;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(res.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(OperatorPlus, Numer_2) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 2.);
  S21Matrix c(5, 5);
  FillMatrixNum(&c, 3.);

  EXPECT_THROW(S21Matrix res = m + c, std::invalid_argument);
}

TEST(Eq, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 2.);
  S21Matrix c(4, 5);
  FillMatrixNum(&c, 2.);
  S21Matrix m1(4, 5);
  FillMatrixNum(&m1, 5.);
  EXPECT_EQ(m.EqMatrix(c), 1);
  EXPECT_EQ(m.EqMatrix(m1), 0);
}

TEST(OpEq, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 2.);
  S21Matrix c(4, 5);
  FillMatrixNum(&c, 2.);
  S21Matrix m1(4, 5);
  FillMatrixNum(&m1, 5.);
  EXPECT_EQ(m == c, 1);
  EXPECT_EQ(m == m1, 0);
}

TEST(Sub, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 5.);
  S21Matrix c(4, 5);
  FillMatrixNum(&c, 3.);
  S21Matrix m1(4, 5);
  FillMatrixNum(&m1, 2.);

  m.SubMatrix(c);

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(Sub, Numer_2) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 2.);
  S21Matrix c(5, 5);
  FillMatrixNum(&c, 3.);

  EXPECT_THROW(m.SumMatrix(c), std::invalid_argument);
}

TEST(Sub, Numer_3) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 5.);
  S21Matrix c(4, 5);
  FillMatrixNum(&c, 3.);
  S21Matrix m1(4, 5);
  FillMatrixNum(&m1, 2.);
  S21Matrix res = m - c;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(res.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(OperatorPE, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 2.);
  S21Matrix c(4, 5);
  FillMatrixNum(&c, 3.);
  S21Matrix m1(4, 5);
  FillMatrixNum(&m1, 5.);
  m += c;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(OperatorPE, Numer_2) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 2.);
  S21Matrix c(5, 5);
  FillMatrixNum(&c, 3.);

  EXPECT_THROW(m += c, std::invalid_argument);
}

TEST(OperatorME, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 5.);
  S21Matrix c(4, 5);
  FillMatrixNum(&c, 3.);
  S21Matrix m1(4, 5);
  FillMatrixNum(&m1, 2.);
  m -= c;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(OperatorME, Numer_2) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 2.);
  S21Matrix c(5, 5);
  FillMatrixNum(&c, 3.);

  EXPECT_THROW(m -= c, std::invalid_argument);
}

TEST(MulNumber, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 10.);
  const double kNum = 0.5;
  S21Matrix m1(4, 5);
  FillMatrixNum(&m1, 5.);
  m.MulNumber(kNum);

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(OpMulNumber, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 10.);
  const double kNum = 0.5;
  S21Matrix m1(4, 5);
  FillMatrixNum(&m1, 5.);
  S21Matrix res = m * kNum;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(res.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(OpMulNumberChanged, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 10.);
  const double kNum = 0.5;
  S21Matrix m1(4, 5);
  FillMatrixNum(&m1, 5.);
  S21Matrix res = kNum * m;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(res.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(OpEq1, Numer_1) {
  S21Matrix m(4, 5);
  FillMatrixNum(&m, 10.);
  S21Matrix m1(4, 5);
  FillMatrixNum(&m1, 5.);
  m = m1;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(MulMatrix, Numer_1) {
  S21Matrix m(3, 3);
  FillMatrixNum(&m, 2.);
  S21Matrix c(3, 3);
  FillMatrixNum(&c, 3.);
  S21Matrix m1(3, 3);
  FillMatrixNum(&m1, 18.);
  m.MulMatrix(c);
  // PrintMatrix(m);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(MulMatrix, Numer_2) {
  S21Matrix m(2, 3);
  FillMatrixNum(&m, 2.);
  S21Matrix c(3, 1);
  FillMatrixNum(&c, 3.);
  S21Matrix m1(2, 1);
  FillMatrixNum(&m1, 18.);
  m.MulMatrix(c);
  // PrintMatrix(m);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 1; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(MulMatrix, Numer_3) {
  S21Matrix m(2, 3);
  S21Matrix c(2, 1);

  EXPECT_THROW(m.MulMatrix(c), std::invalid_argument);
}

TEST(OpMulMatrix, Numer_1) {
  S21Matrix m(3, 3);
  FillMatrixNum(&m, 2.);
  S21Matrix c(3, 3);
  FillMatrixNum(&c, 3.);
  S21Matrix m1(3, 3);
  FillMatrixNum(&m1, 18.);
  m = m * c;
  // PrintMatrix(m);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(OpMulMatrix, Numer_2) {
  S21Matrix m(2, 3);
  FillMatrixNum(&m, 2.);
  S21Matrix c(3, 1);
  FillMatrixNum(&c, 3.);
  S21Matrix m1(2, 1);
  FillMatrixNum(&m1, 18.);
  m = m * c;
  // PrintMatrix(m);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 1; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(OpMulEqMatrix, Numer_1) {
  S21Matrix m(3, 3);
  FillMatrixNum(&m, 2.);
  S21Matrix c(3, 3);
  FillMatrixNum(&c, 3.);
  S21Matrix m1(3, 3);
  FillMatrixNum(&m1, 18.);
  m *= c;
  // PrintMatrix(m);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(OpMulEqMatrix, Numer_2) {
  S21Matrix m(2, 3);
  FillMatrixNum(&m, 2.);
  S21Matrix c(3, 1);
  FillMatrixNum(&c, 3.);
  S21Matrix m1(2, 1);
  FillMatrixNum(&m1, 18.);
  m *= c;
  // PrintMatrix(m);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 1; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(Transpose, Numer_1) {
  S21Matrix m(3, 2);
  FillMatrixNum(&m, 18);
  S21Matrix m1(2, 3);
  FillMatrixNum(&m1, 18);
  m.Transpose();
  // PrintMatrix(m);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(m.GetElement(i, j), m1.GetElement(j, i));
    }
  }
}

TEST(Det, Numer_1) {
  S21Matrix m(3, 3);
  FillMatrix(&m, m.GetRows(), m.GetCols());
  m.SetElement(0, 0, 9);
  double origin_res = -24;
  double res = m.Determinant();

  EXPECT_EQ(res, origin_res);
}

TEST(Det, Numer_2) {
  S21Matrix m(3, 4);
  FillMatrix(&m, m.GetRows(), m.GetCols());

  EXPECT_THROW(m.Determinant(), std::invalid_argument);
}

TEST(CalcCompliments, Numer_1) {
  S21Matrix m(3, 3);
  m.SetElement(0, 0, 1);
  m.SetElement(0, 1, 2);
  m.SetElement(0, 2, 3);
  m.SetElement(1, 0, 0);
  m.SetElement(1, 1, 4);
  m.SetElement(1, 2, 2);
  m.SetElement(2, 0, 5);
  m.SetElement(2, 1, 2);
  m.SetElement(2, 2, 1);
  S21Matrix m1(3, 3);
  m1.SetElement(0, 0, 0);
  m1.SetElement(0, 1, 10);
  m1.SetElement(0, 2, -20);
  m1.SetElement(1, 0, 4);
  m1.SetElement(1, 1, -14);
  m1.SetElement(1, 2, 8);
  m1.SetElement(2, 0, -8);
  m1.SetElement(2, 1, -2);
  m1.SetElement(2, 2, 4);

  S21Matrix res = m.CalcComplements();

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(res.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(CalcCompliments, Numer_2) {
  S21Matrix m(3, 4);
  FillMatrix(&m, m.GetRows(), m.GetCols());

  EXPECT_THROW(m.CalcComplements(), std::invalid_argument);
}

TEST(Inverse, Numer_1) {
  S21Matrix m(3, 3);
  m.SetElement(0, 0, 2);
  m.SetElement(0, 1, 5);
  m.SetElement(0, 2, 7);
  m.SetElement(1, 0, 6);
  m.SetElement(1, 1, 3);
  m.SetElement(1, 2, 4);
  m.SetElement(2, 0, 5);
  m.SetElement(2, 1, -2);
  m.SetElement(2, 2, -3);
  S21Matrix m1(3, 3);
  m1.SetElement(0, 0, 1);
  m1.SetElement(0, 1, -1);
  m1.SetElement(0, 2, 1);
  m1.SetElement(1, 0, -38);
  m1.SetElement(1, 1, 41);
  m1.SetElement(1, 2, -34);
  m1.SetElement(2, 0, 27);
  m1.SetElement(2, 1, -29);
  m1.SetElement(2, 2, 24);

  S21Matrix res = m.InverseMatrix();

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(res.GetElement(i, j), m1.GetElement(i, j));
    }
  }
}

TEST(Inverse, Numer_2) {
  S21Matrix m(3, 4);
  FillMatrix(&m, m.GetRows(), m.GetCols());

  EXPECT_THROW(m.InverseMatrix(), std::invalid_argument);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
