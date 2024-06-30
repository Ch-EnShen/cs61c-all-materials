#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "matrix.h"
#include <stdio.h>

/* Test Suite setup and cleanup functions: */
int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************* Test case functions ****************/
void add_test(void) {
  matrix *result = NULL;
  matrix *mat1 = NULL;
  matrix *mat2 = NULL;
  CU_ASSERT_EQUAL(allocate_matrix(&result, 2, 2), 0);
  CU_ASSERT_EQUAL(allocate_matrix(&mat1, 2, 2), 0);
  CU_ASSERT_EQUAL(allocate_matrix(&mat2, 2, 2), 0);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      set(mat1, i, j, i * 2 + j);
      set(mat2, i, j, i * 2 + j);
    }
  }
  add_matrix(result, mat1, mat2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      CU_ASSERT_EQUAL(get(result, i, j), 2 * (i * 2 + j));
    }
  }
  deallocate_matrix(result);
  deallocate_matrix(mat1);
  deallocate_matrix(mat2);
}

void sub_test(void) {
  matrix *result = NULL;
  matrix *mat1 = NULL;
  matrix *mat2 = NULL;
  CU_ASSERT_EQUAL(allocate_matrix(&result, 2, 2), 0);
  CU_ASSERT_EQUAL(allocate_matrix(&mat1, 2, 2), 0);
  CU_ASSERT_EQUAL(allocate_matrix(&mat2, 2, 2), 0);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      set(mat1, i, j, i * 2 + j);
      set(mat2, i, j, (i * 2 + j) * 3);
    }
  }
  sub_matrix(result, mat1, mat2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      CU_ASSERT_EQUAL(get(result, i, j), (-2) * (i * 2 + j));
    }
  }
  deallocate_matrix(result);
  deallocate_matrix(mat1);
  deallocate_matrix(mat2);
}

void mul_test(void) {
  matrix *result = NULL;
  matrix *mat1 = NULL;
  matrix *mat2 = NULL;
  CU_ASSERT_EQUAL(allocate_matrix(&result, 3, 3), 0);
  CU_ASSERT_EQUAL(allocate_matrix(&mat1, 3, 3), 0);
  CU_ASSERT_EQUAL(allocate_matrix(&mat2, 3, 3), 0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      set(mat1, i, j, i * 3 + j + 1);
      set(mat2, i, j, i * 3 + j + 1);
    }
  }
  mul_matrix(result, mat1, mat2);
  CU_ASSERT_EQUAL(get(result, 0, 0), 30);
  CU_ASSERT_EQUAL(get(result, 0, 1), 36);
  CU_ASSERT_EQUAL(get(result, 0, 2), 42);
  CU_ASSERT_EQUAL(get(result, 1, 0), 66);
  CU_ASSERT_EQUAL(get(result, 1, 1), 81);
  CU_ASSERT_EQUAL(get(result, 1, 2), 96);
  CU_ASSERT_EQUAL(get(result, 2, 0), 102);
  CU_ASSERT_EQUAL(get(result, 2, 1), 126);
  CU_ASSERT_EQUAL(get(result, 2, 2), 150);
  deallocate_matrix(result);
  deallocate_matrix(mat1);
  deallocate_matrix(mat2);
}

void neg_test(void) {
  matrix *result = NULL;
  matrix *mat = NULL;
  CU_ASSERT_EQUAL(allocate_matrix(&result, 2, 2), 0);
  CU_ASSERT_EQUAL(allocate_matrix(&mat, 2, 2), 0);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      set(mat, i, j, i * 2 + j);
    }
  }
  neg_matrix(result, mat);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      CU_ASSERT_EQUAL(get(result, i, j), -(i * 2 + j));
    }
  }
  deallocate_matrix(result);
  deallocate_matrix(mat);
}

void abs_test(void) {
  matrix *result = NULL;
  matrix *mat = NULL;
  CU_ASSERT_EQUAL(allocate_matrix(&result, 2, 2), 0);
  CU_ASSERT_EQUAL(allocate_matrix(&mat, 2, 2), 0);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (j % 2 == 0)
        set(mat, i, j, i * 2 + j);
      else
        set(mat, i, j, -(i * 2 + j));
    }
  }
  abs_matrix(result, mat);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      CU_ASSERT_EQUAL(get(result, i, j), i * 2 + j);
    }
  }
  deallocate_matrix(result);
  deallocate_matrix(mat);
}

void pow_test(void) {
  matrix *result = NULL;
  matrix *mat = NULL;
  CU_ASSERT_EQUAL(allocate_matrix(&result, 2, 2), 0);
  CU_ASSERT_EQUAL(allocate_matrix(&mat, 2, 2), 0);
  set(mat, 0, 0, 1);
  set(mat, 0, 1, 1);
  set(mat, 1, 0, 1);
  set(mat, 1, 1, 0);
  pow_matrix(result, mat, 3);
  CU_ASSERT_EQUAL(get(result, 0, 0), 3);
  CU_ASSERT_EQUAL(get(result, 0, 1), 2);
  CU_ASSERT_EQUAL(get(result, 1, 0), 2);
  CU_ASSERT_EQUAL(get(result, 1, 1), 1);
  pow_matrix(result, mat, 10);
  CU_ASSERT_EQUAL(get(result, 0, 0), 89);
  CU_ASSERT_EQUAL(get(result, 0, 1), 55);
  CU_ASSERT_EQUAL(get(result, 1, 0), 55);
  CU_ASSERT_EQUAL(get(result, 1, 1), 34);
  deallocate_matrix(result);
  deallocate_matrix(mat);
}

void alloc_fail_test(void) {
  matrix *mat = NULL;
  CU_ASSERT_EQUAL(allocate_matrix(&mat, 0, 0), -1);
  CU_ASSERT_EQUAL(allocate_matrix(&mat, 0, 1), -1);
  CU_ASSERT_EQUAL(allocate_matrix(&mat, 1, 0), -1);
}

void alloc_success_test(void) {
  matrix *mat = NULL;
  CU_ASSERT_EQUAL(allocate_matrix(&mat, 3, 2), 0);
  CU_ASSERT_EQUAL(mat->parent, NULL);
  CU_ASSERT_EQUAL(mat->ref_cnt, 1);
  CU_ASSERT_EQUAL(mat->rows, 3);
  CU_ASSERT_EQUAL(mat->cols, 2);
  CU_ASSERT_NOT_EQUAL(mat->data, NULL);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      CU_ASSERT_EQUAL(get(mat, i, j), 0);
    }
  }
  deallocate_matrix(mat);
}

void alloc_ref_fail_test(void) {
  matrix *mat = NULL;
  matrix *from = NULL;
  CU_ASSERT_EQUAL(allocate_matrix_ref(&mat, from, 0, 0, 0), -1);
  CU_ASSERT_EQUAL(allocate_matrix_ref(&mat, from, 0, 0, 1), -1);
  CU_ASSERT_EQUAL(allocate_matrix_ref(&mat, from, 0, 1, 0), -1);
}

void alloc_ref_success_test(void) {
  matrix *mat = NULL;
  matrix *from = NULL;
  allocate_matrix(&from, 3, 2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      set(from, i, j, i * 2 + j);
    }
  }
  CU_ASSERT_EQUAL(allocate_matrix_ref(&mat, from, 2, 2, 2), 0);
  CU_ASSERT_PTR_EQUAL(mat->data, from->data + 2);
  CU_ASSERT_PTR_EQUAL(mat->parent, from);
  CU_ASSERT_EQUAL(mat->parent->ref_cnt, 2);
  CU_ASSERT_EQUAL(mat->rows, 2);
  CU_ASSERT_EQUAL(mat->cols, 2);
  deallocate_matrix(from);
  deallocate_matrix(mat);
}

void dealloc_null_test(void) {
  matrix *mat = NULL;
  deallocate_matrix(mat); // Test the null case doesn't crash
}

void get_test(void) {
  matrix *mat = NULL;
  allocate_matrix(&mat, 2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      set(mat, i, j, i * 2 + j);
    }
  }
  CU_ASSERT_EQUAL(get(mat, 0, 0), 0);
  CU_ASSERT_EQUAL(get(mat, 0, 1), 1);
  CU_ASSERT_EQUAL(get(mat, 1, 0), 2);
  CU_ASSERT_EQUAL(get(mat, 1, 1), 3);
  deallocate_matrix(mat);
}

void set_test(void) {
  matrix *mat = NULL;
  allocate_matrix(&mat, 2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      set(mat, i, j, i * 2 + j);
    }
  }
  CU_ASSERT_EQUAL(get(mat, 0, 0), 0);
  CU_ASSERT_EQUAL(get(mat, 0, 1), 1);
  CU_ASSERT_EQUAL(get(mat, 1, 0), 2);
  CU_ASSERT_EQUAL(get(mat, 1, 1), 3);
  deallocate_matrix(mat);
}

/************* Test Runner Code goes here **************/

int main (void)
{
  Py_Initialize(); // Need to call this so that Python.h functions won't segfault
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("mat_test_suite", init_suite, clean_suite);
  if (pSuite == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

   /* add the tests to the suite */
   if ((CU_add_test(pSuite, "add_test", add_test) == NULL) ||
        (CU_add_test(pSuite, "sub_test", sub_test) == NULL) ||
        (CU_add_test(pSuite, "mul_test", mul_test) == NULL) ||
        (CU_add_test(pSuite, "neg_test", neg_test) == NULL) ||
        (CU_add_test(pSuite, "abs_test", abs_test) == NULL) ||
        (CU_add_test(pSuite, "pow_test", pow_test) == NULL) ||
        (CU_add_test(pSuite, "alloc_fail_test", alloc_fail_test) == NULL) ||
        (CU_add_test(pSuite, "alloc_success_test", alloc_success_test) == NULL) ||
        (CU_add_test(pSuite, "alloc_ref_fail_test", alloc_ref_fail_test) == NULL) ||
        (CU_add_test(pSuite, "alloc_ref_success_test", alloc_ref_success_test) == NULL) ||
        (CU_add_test(pSuite, "dealloc_null_test", dealloc_null_test) == NULL) ||
        (CU_add_test(pSuite, "get_test", get_test) == NULL) ||
        (CU_add_test(pSuite, "set_test", set_test) == NULL)
     )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

  // Run all tests using the basic interface
  CU_basic_set_mode(CU_BRM_NORMAL);
  // CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  printf("\n");
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n\n");

  /* Clean up registry and return */
  CU_cleanup_registry();
  return CU_get_error();
}