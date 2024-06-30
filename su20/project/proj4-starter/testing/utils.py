"""
This file contains some helper functions for testing
Provided by CS 61C staff
"""

import dumbpy as dp
import numc as nc
import numpy as np
import hashlib, struct
from typing import Union

"""
Global vars
"""
num_samples = 1000
decimal_places = 6

"""
Returns a dumbpy matrix and a numc matrix with the same data
"""
def rand_dp_nc_matrix(*args, **kwargs):
    dp_mat, nc_mat = None, None
    if len(kwargs) == 0:
        dp_mat, nc_mat = dp.Matrix(*args), nc.Matrix(*args)
    else:
        dp_mat, nc_mat = dp.Matrix(*args, **kwargs), nc.Matrix(*args, **kwargs)
    return dp_mat, nc_mat

"""
Returns whether the given dumbpy matrix dp_mat is equal to the numc matrix nc_mat
This function allows a reasonable margin of floating point errors
"""
def cmp_dp_nc_matrix(dp_mat: dp.Matrix, nc_mat: nc.Matrix):
    return rand_md5(dp_mat) == rand_md5(nc_mat)

"""
Generate a md5 hash by sampling random elements in nc_mat
"""
def rand_md5(mat: Union[dp.Matrix, nc.Matrix]):
    np.random.seed(1)
    rows, cols = mat.shape
    m = hashlib.md5()
    total_cnt = mat.shape[0] * mat.shape[1]
    if total_cnt < num_samples:
        for i in range(rows):
            for j in range(cols):
                m.update(struct.pack("f", round(mat.get(i, j), decimal_places)))
    else:
        for _ in range(num_samples):
            i = np.random.randint(rows)
            j = np.random.randint(cols)
            m.update(struct.pack("f", round(mat.get(i, j), decimal_places)))
    return m.digest()
