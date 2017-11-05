/*
 * File: sistema_data.c
 *
 * Code generated for Simulink model 'sistema'.
 *
 * Model version                  : 1.134
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Fri Nov 18 17:36:15 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "sistema.h"
#include "sistema_private.h"

/* Block parameters (auto storage) */
P_sistema_T sistema_P = {
  /*  Variable: J
   * Referenced by: '<S8>/Constant1'
   */
  { 0.01683F, 0.01683F, 0.02834F, 3.7882E-6F },
  2.4086E-7F,                          /* Variable: cq
                                        * Referenced by: '<S7>/Constant2'
                                        */
  1.4341E-5F,                          /* Variable: ct
                                        * Referenced by: '<S7>/Constant1'
                                        */
  0.26F,                               /* Variable: d
                                        * Referenced by: '<S7>/Constant4'
                                        */
  9.8065F,                             /* Variable: g
                                        * Referenced by: '<S8>/Constant'
                                        */

  /*  Variable: limit
   * Referenced by: '<S8>/Constant5'
   */
  { 0.5F, 0.5F, 0.5F, 0.5F },

  /*  Variable: limit_pos
   * Referenced by: '<S9>/Constant3'
   */
  { 0.5F, 0.5F },
  1.03F                                /* Variable: m
                                        * Referenced by:
                                        *   '<S8>/Constant2'
                                        *   '<S9>/Constant'
                                        */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
