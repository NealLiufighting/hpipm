/**************************************************************************************************
*                                                                                                 *
* This file is part of HPIPM.                                                                     *
*                                                                                                 *
* HPIPM -- High-Performance Interior Point Method.                                                *
* Copyright (C) 2017-2018 by Gianluca Frison.                                                     *
* Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              *
* All rights reserved.                                                                            *
*                                                                                                 *
* This program is free software: you can redistribute it and/or modify                            *
* it under the terms of the GNU General Public License as published by                            *
* the Free Software Foundation, either version 3 of the License, or                               *
* (at your option) any later version                                                              *.
*                                                                                                 *
* This program is distributed in the hope that it will be useful,                                 *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                                  *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                                   *
* GNU General Public License for more details.                                                    *
*                                                                                                 *
* You should have received a copy of the GNU General Public License                               *
* along with this program.  If not, see <https://www.gnu.org/licenses/>.                          *
*                                                                                                 *
* The authors designate this particular file as subject to the "Classpath" exception              *
* as provided by the authors in the LICENSE file that accompained this code.                      *
*                                                                                                 *
* Author: Gianluca Frison, gianluca.frison (at) imtek.uni-freiburg.de                             *
*                                                                                                 *
**************************************************************************************************/



#include <stdio.h>
#include <stdlib.h>

#include <blasfeo_target.h>
#include <blasfeo_common.h>
#include <blasfeo_s_aux.h>

#include <hpipm_s_ocp_qp_dim.h>
#include <hpipm_s_ocp_qp.h>
#include <hpipm_aux_string.h>



#define CREATE_STRMAT blasfeo_create_smat
#define CREATE_STRVEC blasfeo_create_svec
#define CVT_MAT2STRMAT blasfeo_pack_smat
#define CVT_STRMAT2MAT blasfeo_unpack_smat
#define CVT_TRAN_MAT2STRMAT blasfeo_pack_tran_smat
#define CVT_TRAN_STRMAT2MAT blasfeo_unpack_tran_smat
#define CVT_VEC2STRVEC blasfeo_pack_svec
#define CVT_STRVEC2VEC blasfeo_unpack_svec
#define GESE blasfeo_sgese
#define OCP_QP s_ocp_qp
#define OCP_QP_DIM s_ocp_qp_dim
#define REAL float
#define STRMAT blasfeo_smat
#define STRVEC blasfeo_svec
#define SIZE_STRMAT blasfeo_memsize_smat
#define SIZE_STRVEC blasfeo_memsize_svec
#define VECCP_LIBSTR blasfeo_sveccp
#define VECSC_LIBSTR blasfeo_svecsc
#define VECSE blasfeo_svecse

#define CAST_OCP_QP s_cast_ocp_qp
#define COPY_OCP_QP s_copy_ocp_qp
#define CREATE_OCP_QP s_create_ocp_qp
#define CVT_COLMAJ_TO_OCP_QP s_cvt_colmaj_to_ocp_qp
#define CVT_ROWMAJ_TO_OCP_QP s_cvt_rowmaj_to_ocp_qp
#define MEMSIZE_OCP_QP s_memsize_ocp_qp
#define CHANGE_BOUNDS_DIMENSIONS_OCP_QP s_change_bounds_dimensions_ocp_qp



#define CVT_COLMAJ_TO_OCP_QP_GF s_cvt_colmaj_to_ocp_qp_gf

#define CVT_COLMAJ_MAT_TO_OCP_QP s_cvt_colmaj_mat_to_ocp_qp
#define CVT_OCP_QP_TO_COLMAJ_MAT s_cvt_ocp_qp_to_colmaj_mat
#define CVT_COLMAJ_VEC_TO_OCP_QP s_cvt_colmaj_vec_to_ocp_qp
#define CVT_OCP_QP_TO_COLMAJ_VEC s_cvt_ocp_qp_to_colmaj_vec



#define CVT_COLMAJ_TO_OCP_QP_A s_cvt_colmaj_to_ocp_qp_A
#define CVT_OCP_QP_TO_COLMAJ_A s_cvt_ocp_qp_to_colmaj_A
#define CVT_COLMAJ_TO_OCP_QP_B s_cvt_colmaj_to_ocp_qp_B
#define CVT_OCP_QP_TO_COLMAJ_B s_cvt_ocp_qp_to_colmaj_B
#define CVT_COLMAJ_TO_OCP_QP_BVEC s_cvt_colmaj_to_ocp_qp_b
#define CVT_OCP_QP_TO_COLMAJ_BVEC s_cvt_ocp_qp_to_colmaj_b
#define CVT_COLMAJ_TO_OCP_QP_Q s_cvt_colmaj_to_ocp_qp_Q
#define CVT_OCP_QP_TO_COLMAJ_Q s_cvt_ocp_qp_to_colmaj_Q
#define CVT_COLMAJ_TO_OCP_QP_S s_cvt_colmaj_to_ocp_qp_S
#define CVT_OCP_QP_TO_COLMAJ_S s_cvt_ocp_qp_to_colmaj_S
#define CVT_COLMAJ_TO_OCP_QP_R s_cvt_colmaj_to_ocp_qp_R
#define CVT_OCP_QP_TO_COLMAJ_R s_cvt_ocp_qp_to_colmaj_R
#define CVT_COLMAJ_TO_OCP_QP_QVEC s_cvt_colmaj_to_ocp_qp_q
#define CVT_OCP_QP_TO_COLMAJ_QVEC s_cvt_ocp_qp_to_colmaj_q
#define CVT_COLMAJ_TO_OCP_QP_RVEC s_cvt_colmaj_to_ocp_qp_r
#define CVT_OCP_QP_TO_COLMAJ_RVEC s_cvt_ocp_qp_to_colmaj_r
#define CVT_COLMAJ_TO_OCP_QP_LBX s_cvt_colmaj_to_ocp_qp_lbx
#define CVT_OCP_QP_TO_COLMAJ_LBX s_cvt_ocp_qp_to_colmaj_lbx
#define CVT_COLMAJ_TO_OCP_QP_UBX s_cvt_colmaj_to_ocp_qp_ubx
#define CVT_OCP_QP_TO_COLMAJ_UBX s_cvt_ocp_qp_to_colmaj_ubx
#define CVT_COLMAJ_TO_OCP_QP_LBU s_cvt_colmaj_to_ocp_qp_lbu
#define CVT_OCP_QP_TO_COLMAJ_LBU s_cvt_ocp_qp_to_colmaj_lbu
#define CVT_COLMAJ_TO_OCP_QP_UBU s_cvt_colmaj_to_ocp_qp_ubu
#define CVT_OCP_QP_TO_COLMAJ_UBU s_cvt_ocp_qp_to_colmaj_ubu
#define CVT_COLMAJ_TO_OCP_QP_IDXB s_cvt_colmaj_to_ocp_qp_idxb
#define CVT_OCP_QP_TO_COLMAJ_IDXB s_cvt_ocp_qp_to_colmaj_idxb
#define CVT_COLMAJ_TO_OCP_QP_LB s_cvt_colmaj_to_ocp_qp_lb
#define CVT_OCP_QP_TO_COLMAJ_LB s_cvt_ocp_qp_to_colmaj_lb
#define CVT_COLMAJ_TO_OCP_QP_UB s_cvt_colmaj_to_ocp_qp_ub
#define CVT_OCP_QP_TO_COLMAJ_UB s_cvt_ocp_qp_to_colmaj_ub
#define CVT_COLMAJ_TO_OCP_QP_C s_cvt_colmaj_to_ocp_qp_C
#define CVT_OCP_QP_TO_COLMAJ_C s_cvt_ocp_qp_to_colmaj_C
#define CVT_COLMAJ_TO_OCP_QP_D s_cvt_colmaj_to_ocp_qp_D
#define CVT_OCP_QP_TO_COLMAJ_D s_cvt_ocp_qp_to_colmaj_D
#define CVT_COLMAJ_TO_OCP_QP_LG s_cvt_colmaj_to_ocp_qp_lg
#define CVT_OCP_QP_TO_COLMAJ_LG s_cvt_ocp_qp_to_colmaj_lg
#define CVT_COLMAJ_TO_OCP_QP_UG s_cvt_colmaj_to_ocp_qp_ug
#define CVT_OCP_QP_TO_COLMAJ_UG s_cvt_ocp_qp_to_colmaj_ug
#define CVT_COLMAJ_TO_OCP_QP_ZL s_cvt_colmaj_to_ocp_qp_Zl
#define CVT_OCP_QP_TO_COLMAJ_ZL s_cvt_ocp_qp_to_colmaj_Zl
#define CVT_COLMAJ_TO_OCP_QP_ZU s_cvt_colmaj_to_ocp_qp_Zu
#define CVT_OCP_QP_TO_COLMAJ_ZU s_cvt_ocp_qp_to_colmaj_Zu
#define CVT_COLMAJ_TO_OCP_QP_ZLVEC s_cvt_colmaj_to_ocp_qp_zl
#define CVT_OCP_QP_TO_COLMAJ_ZLVEC s_cvt_ocp_qp_to_colmaj_zl
#define CVT_COLMAJ_TO_OCP_QP_ZUVEC s_cvt_colmaj_to_ocp_qp_zu
#define CVT_OCP_QP_TO_COLMAJ_ZUVEC s_cvt_ocp_qp_to_colmaj_zu
#define CVT_COLMAJ_TO_OCP_QP_IDXS s_cvt_colmaj_to_ocp_qp_idxs
#define CVT_OCP_QP_TO_COLMAJ_IDXS s_cvt_ocp_qp_to_colmaj_idxs
#define CVT_COLMAJ_TO_OCP_QP_LS s_cvt_colmaj_to_ocp_qp_ls
#define CVT_OCP_QP_TO_COLMAJ_LS s_cvt_ocp_qp_to_colmaj_ls
#define CVT_COLMAJ_TO_OCP_QP_US s_cvt_colmaj_to_ocp_qp_us
#define CVT_OCP_QP_TO_COLMAJ_US s_cvt_ocp_qp_to_colmaj_us

#include "x_ocp_qp.c"

