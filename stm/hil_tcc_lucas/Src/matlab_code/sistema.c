/*
 * File: sistema.c
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

/* Block states (auto storage) */
DW_sistema_T sistema_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_sistema_T sistema_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_sistema_T sistema_Y;

/* Real-time model */
RT_MODEL_sistema_T sistema_M_;
RT_MODEL_sistema_T *const sistema_M = &sistema_M_;

/* Model step function */
void sistema_step(void)
{
  real32_T arg_phi;
  real32_T lambdas[16];
  real_T f[4];
  real32_T s[4];
  real32_T u_phi;
  real32_T w1d_sq;
  real32_T rtb_theta;
  real32_T rtb_phi;
  real32_T rtb_psi;
  real32_T rtb_TmpSignalConversionAtSFun_f[4];
  int32_T i;
  real32_T tmp[16];
  real32_T f_0[4];
  real32_T tmp_0[16];
  real32_T s_idx_0;
  real32_T s_idx_1;
  real_T y_idx_0;
  real_T y_idx_1;
  real_T y_idx_2;
  real_T y_idx_3;
  real32_T Vy_XPlane;
  real32_T q_XPlane;
  real32_T r_XPlane;
  real32_T Delay_DSTATE;
  real32_T Vx_XPlane;
  real32_T Vz_XPlane;

  /* Inport: '<Root>/Vz_XPlane' */
  Vz_XPlane = sistema_U.Vz_XPlane;

  /* Inport: '<Root>/Vx_XPlane' */
  Vx_XPlane = sistema_U.Vx_XPlane;

  /* Update for Delay: '<S8>/Delay' */
  Delay_DSTATE = sistema_DW.Delay_DSTATE;

  /* Inport: '<Root>/r_XPlane' */
  r_XPlane = sistema_U.r_XPlane;

  /* Inport: '<Root>/q_XPlane' */
  q_XPlane = sistema_U.q_XPlane;

  /* Inport: '<Root>/Vy_XPlane' */
  Vy_XPlane = sistema_U.Vy_XPlane;

  /* MATLAB Function: '<S4>/MATLAB Function' incorporates:
   *  Inport: '<Root>/heading_XPlane'
   *  Inport: '<Root>/pitch_XPlane'
   *  Inport: '<Root>/roll_XPlane'
   */
  /* MATLAB Function 'sistema de controle quad xplane/conversao Plane2Matlab/MATLAB Function': '<S15>:1' */
  /* this block is responsible to make the variables of Xplane compatible with */
  /* the variables of the control system. */
  /* '<S15>:1:6' */
  /* Initial position of the Quadcopter on X-Plane  */
  /* '<S15>:1:7' */
  /* TODO: Get the values autonomously */
  /* '<S15>:1:8' */
  /* '<S15>:1:11' */
  /*  CONVERTION FOR NED SYSTEM */
  /* '<S15>:1:12' */
  /* '<S15>:1:13' */
  /* '<S15>:1:15' */
  /*  CONVERTION FOR NED SYSTEM  */
  /* '<S15>:1:16' */
  /* '<S15>:1:17' */
  /* '<S15>:1:19' */
  /*  EQUAL */
  /* '<S15>:1:20' */
  /* '<S15>:1:21' */
  /* '<S15>:1:23' */
  rtb_theta = sistema_U.pitch_XPlane * 0.0174532924F;

  /*  CONVERTION FROM DEG TO RAD */
  /* '<S15>:1:24' */
  rtb_phi = sistema_U.roll_XPlane * 0.0174532924F;

  /* '<S15>:1:25' */
  rtb_psi = sistema_U.heading_XPlane * 0.0174532924F;

  /* MATLAB Function: '<S9>/MATLAB Function' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant3'
   *  Constant: '<S9>/Constant4'
   *  Inport: '<Root>/Vx_XPlane'
   *  Inport: '<Root>/Vz_XPlane'
   *  Inport: '<Root>/X_XPlane'
   *  Inport: '<Root>/Z_XPlane'
   *  Inport: '<Root>/referencias'
   *  MATLAB Function: '<S4>/MATLAB Function'
   */
  /* MATLAB Function 'sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Controle/Controlador sliding mode/pqr_to_euler_dot': '<S10>:1' */
  /* '<S10>:1:3' */
  /* '<S10>:1:5' */
  /* '<S10>:1:7' */
  /* MATLAB Function 'sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Controle/Controlador sliding mode/Controle de Translacao/MATLAB Function': '<S12>:1' */
  /* '<S12>:1:3' */
  /* '<S12>:1:6' */
  /* '<S12>:1:9' */
  /* '<S12>:1:12' */
  w1d_sq = (-sistema_U.Z_XPlane - -2784.36F) - sistema_U.referencias[0];				// (ORIGINAL) Z0 positivo
  u_phi = (sistema_U.X_XPlane - -35162.5313F) - sistema_U.referencias[1];				// (ORIGINAL) X0 negativo
  s_idx_0 = (0.25F * w1d_sq + 0.0F * u_phi) + -Vz_XPlane;
  s_idx_1 = (0.0F * w1d_sq + 0.25F * u_phi) + Vx_XPlane;

  /* '<S12>:1:14' */
  if ((real32_T)fabs(s_idx_0) < sistema_P.limit_pos[0]) {
    y_idx_0 = s_idx_0 / sistema_P.limit_pos[0];
  } else if (s_idx_0 < 0.0F) {
    y_idx_0 = -1.0;
  } else if (s_idx_0 > 0.0F) {
    y_idx_0 = 1.0;
  } else if (s_idx_0 == 0.0F) {
    y_idx_0 = 0.0;
  } else {
    y_idx_0 = s_idx_0;
  }

  if ((real32_T)fabs(s_idx_1) < sistema_P.limit_pos[1]) {
    y_idx_1 = s_idx_1 / sistema_P.limit_pos[1];
  } else if (s_idx_1 < 0.0F) {
    y_idx_1 = -1.0;
  } else if (s_idx_1 > 0.0F) {
    y_idx_1 = 1.0;
  } else if (s_idx_1 == 0.0F) {
    y_idx_1 = 0.0;
  } else {
    y_idx_1 = s_idx_1;
  }

  w1d_sq = (0.0F - (0.25F * -Vz_XPlane + 0.0F * Vx_XPlane)) - (1.6F * (real32_T)
    y_idx_0 + 0.0F * (real32_T)y_idx_1);
  u_phi = (0.0F - (0.0F * -Vz_XPlane + 0.25F * Vx_XPlane)) - (0.0F * (real32_T)
    y_idx_0 + 1.6F * (real32_T)y_idx_1);
  s_idx_0 = -sistema_P.m / Delay_DSTATE * w1d_sq + 0.0F * u_phi;
  u_phi = -sistema_P.m / Delay_DSTATE * u_phi + 0.0F * w1d_sq;

  /* MATLAB Function: '<S9>/conversao ref. angulos' incorporates:
   *  MATLAB Function: '<S9>/MATLAB Function'
   */
  /* '<S12>:1:16' */
  /* '<S12>:1:17' */
  /* MATLAB Function 'sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Controle/Controlador sliding mode/Controle de Translacao/conversao ref. angulos': '<S13>:1' */
  /* '<S13>:1:3' */
  arg_phi = s_idx_0 * (real32_T)sin(rtb_psi) - u_phi * (real32_T)cos(rtb_psi);
  if (arg_phi > 1.0F) {
    /* '<S13>:1:6' */
    /* '<S13>:1:7' */
    arg_phi = 1.0F;
  } else {
    if (arg_phi < -1.0F) {
      /* '<S13>:1:8' */
      /* '<S13>:1:9' */
      arg_phi = -1.0F;
    }
  }

  /* '<S13>:1:12' */
  s_idx_1 = (s_idx_0 * (real32_T)cos(rtb_psi) + u_phi * (real32_T)sin(rtb_psi)) /
    (real32_T)cos(rtb_phi);
  if (s_idx_1 > 1.0F) {
    /* '<S13>:1:14' */
    /* '<S13>:1:15' */
    s_idx_1 = 1.0F;
  } else {
    if (s_idx_1 < -1.0F) {
      /* '<S13>:1:16' */
      /* '<S13>:1:17' */
      s_idx_1 = -1.0F;
    }
  }

  /* SignalConversion: '<S11>/TmpSignal ConversionAt SFunction Inport7' incorporates:
   *  Inport: '<Root>/Vy_XPlane'
   *  Inport: '<Root>/p_XPlane'
   *  Inport: '<Root>/q_XPlane'
   *  Inport: '<Root>/r_XPlane'
   *  MATLAB Function: '<S4>/MATLAB Function'
   *  MATLAB Function: '<S8>/pqr_to_euler_dot'
   *  MATLAB Function: '<S8>/sliding_mode'
   */
  /* '<S13>:1:21' */
  /* '<S13>:1:23' */
  rtb_TmpSignalConversionAtSFun_f[0] = -Vy_XPlane;
  rtb_TmpSignalConversionAtSFun_f[1] = ((real32_T)tan(rtb_theta) * (real32_T)sin
    (rtb_phi) * q_XPlane + sistema_U.p_XPlane) + (real32_T)tan(rtb_theta) *
    (real32_T)cos(rtb_phi) * r_XPlane;
  rtb_TmpSignalConversionAtSFun_f[2] = (real32_T)cos(rtb_phi) * q_XPlane -
    (real32_T)sin(rtb_phi) * r_XPlane;
  rtb_TmpSignalConversionAtSFun_f[3] = q_XPlane * (real32_T)sin(rtb_phi) /
    (real32_T)cos(rtb_theta) + r_XPlane * (real32_T)cos(rtb_phi) / (real32_T)cos
    (rtb_theta);

  /* MATLAB Function: '<S8>/sliding_mode' incorporates:
   *  Constant: '<S8>/Constant'
   *  Constant: '<S8>/Constant1'
   *  Constant: '<S8>/Constant2'
   *  Constant: '<S8>/Constant5'
   *  Inport: '<Root>/Vy_XPlane'
   *  Inport: '<Root>/Y_XPlane'
   *  Inport: '<Root>/referencias'
   *  MATLAB Function: '<S4>/MATLAB Function'
   *  MATLAB Function: '<S9>/conversao ref. angulos'
   *  SignalConversion: '<S11>/TmpSignal ConversionAt SFunction Inport6'
   *  SignalConversion: '<S11>/TmpSignal ConversionAt SFunction Inport8'
   */
  /* MATLAB Function 'sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Controle/Controlador sliding mode/sliding_mode': '<S11>:1' */
  /* '<S11>:1:3' */
  /* '<S11>:1:4' */
  /* '<S11>:1:5' */
  /* '<S11>:1:7' */
  lambdas[0] = 1.0F;
  lambdas[4] = 0.0F;
  lambdas[8] = 0.0F;
  lambdas[12] = 0.0F;
  lambdas[1] = 0.0F;
  lambdas[5] = 5.0F;
  lambdas[9] = 0.0F;
  lambdas[13] = 0.0F;
  lambdas[2] = 0.0F;
  lambdas[6] = 0.0F;
  lambdas[10] = 5.0F;
  lambdas[14] = 0.0F;
  lambdas[3] = 0.0F;
  lambdas[7] = 0.0F;
  lambdas[11] = 0.0F;
  lambdas[15] = 0.5F;

  /* '<S11>:1:12' */
  /* '<S11>:1:13' */
  /* '<S11>:1:14' */
  /* '<S11>:1:18' */
  f[0] = sistema_P.g;

  /* '<S11>:1:20' */
  f[1] = ((((rtb_TmpSignalConversionAtSFun_f[1] -
             rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)sin(rtb_theta)) *
            (sistema_P.J[0] - sistema_P.J[1]) *
            (rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)cos(rtb_theta) *
             (real32_T)sin(rtb_phi) + rtb_TmpSignalConversionAtSFun_f[2] *
             (real32_T)cos(rtb_phi)) / sistema_P.J[2] * ((real32_T)cos(rtb_phi) *
             (real32_T)tan(rtb_theta)) + (rtb_TmpSignalConversionAtSFun_f[1] -
             rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)sin(rtb_theta)) *
            (sistema_P.J[0] - sistema_P.J[2]) *
            (rtb_TmpSignalConversionAtSFun_f[2] * (real32_T)sin(rtb_phi) -
             rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)cos(rtb_phi) *
             (real32_T)cos(rtb_theta)) / sistema_P.J[1] * ((real32_T)sin(rtb_phi)
             * (real32_T)tan(rtb_theta))) + rtb_TmpSignalConversionAtSFun_f[3] *
           rtb_TmpSignalConversionAtSFun_f[2] / (real32_T)cos(rtb_theta)) +
          rtb_TmpSignalConversionAtSFun_f[1] * rtb_TmpSignalConversionAtSFun_f[2]
          * (real32_T)tan(rtb_theta)) - (rtb_TmpSignalConversionAtSFun_f[3] *
    (real32_T)cos(rtb_theta) * (real32_T)sin(rtb_phi) +
    rtb_TmpSignalConversionAtSFun_f[2] * (real32_T)cos(rtb_phi)) * (sistema_P.J
    [1] - sistema_P.J[2]) * (rtb_TmpSignalConversionAtSFun_f[2] * (real32_T)sin
    (rtb_phi) - rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)cos(rtb_phi) *
    (real32_T)cos(rtb_theta)) / sistema_P.J[0];

  /* '<S11>:1:24' */
  f[2] = ((rtb_TmpSignalConversionAtSFun_f[1] - rtb_TmpSignalConversionAtSFun_f
           [3] * (real32_T)sin(rtb_theta)) * (sistema_P.J[0] - sistema_P.J[2]) *
          (rtb_TmpSignalConversionAtSFun_f[2] * (real32_T)sin(rtb_phi) -
           rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)cos(rtb_phi) *
           (real32_T)cos(rtb_theta)) / sistema_P.J[1] * (real32_T)cos(rtb_phi) +
          (rtb_TmpSignalConversionAtSFun_f[1] - rtb_TmpSignalConversionAtSFun_f
           [3] * (real32_T)sin(rtb_theta)) * (sistema_P.J[0] - sistema_P.J[1]) *
          (rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)cos(rtb_theta) *
           (real32_T)sin(rtb_phi) + rtb_TmpSignalConversionAtSFun_f[2] *
           (real32_T)cos(rtb_phi)) / sistema_P.J[2] * -(real32_T)sin(rtb_phi)) -
    rtb_TmpSignalConversionAtSFun_f[1] * rtb_TmpSignalConversionAtSFun_f[3] *
    (real32_T)cos(rtb_theta);

  /* '<S11>:1:27' */
  f[3] = ((((rtb_TmpSignalConversionAtSFun_f[1] -
             rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)sin(rtb_theta)) *
            sistema_P.J[0] * (rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)cos
             (rtb_theta) * (real32_T)sin(rtb_phi) +
             rtb_TmpSignalConversionAtSFun_f[2] * (real32_T)cos(rtb_phi)) -
            (rtb_TmpSignalConversionAtSFun_f[1] -
             rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)sin(rtb_theta)) *
            sistema_P.J[1] * (rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)cos
             (rtb_theta) * (real32_T)sin(rtb_phi) +
             rtb_TmpSignalConversionAtSFun_f[2] * (real32_T)cos(rtb_phi))) *
           (real32_T)cos(rtb_phi) / (sistema_P.J[2] * (real32_T)cos(rtb_theta))
           + rtb_TmpSignalConversionAtSFun_f[1] *
           rtb_TmpSignalConversionAtSFun_f[2] / (real32_T)cos(rtb_theta)) +
          ((rtb_TmpSignalConversionAtSFun_f[1] -
            rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)sin(rtb_theta)) *
           sistema_P.J[0] * (rtb_TmpSignalConversionAtSFun_f[2] * (real32_T)sin
            (rtb_phi) - rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)cos
            (rtb_phi) * (real32_T)cos(rtb_theta)) -
           (rtb_TmpSignalConversionAtSFun_f[1] -
            rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)sin(rtb_theta)) *
           sistema_P.J[2] * (rtb_TmpSignalConversionAtSFun_f[2] * (real32_T)sin
            (rtb_phi) - rtb_TmpSignalConversionAtSFun_f[3] * (real32_T)cos
            (rtb_phi) * (real32_T)cos(rtb_theta))) * (real32_T)sin(rtb_phi) /
          (sistema_P.J[1] * (real32_T)cos(rtb_theta))) +
    rtb_TmpSignalConversionAtSFun_f[3] * rtb_TmpSignalConversionAtSFun_f[2] *
    (real32_T)sin(rtb_theta) / (real32_T)cos(rtb_theta);

  /* '<S11>:1:30' */
  w1d_sq = (-sistema_U.Y_XPlane - -180.6F) - sistema_U.referencias[2]; 					// (ORIGINAL) Y0 positivo
  u_phi = rtb_phi - (real32_T)asin(arg_phi);
  s_idx_1 = rtb_theta - (real32_T)asin(s_idx_1);
  s_idx_0 = rtb_psi - sistema_U.referencias[3];
  for (i = 0; i < 4; i++) {
    s[i] = (((lambdas[i + 4] * u_phi + lambdas[i] * w1d_sq) + lambdas[i + 8] *
             s_idx_1) + lambdas[i + 12] * s_idx_0) +
      rtb_TmpSignalConversionAtSFun_f[i];
  }

  /* '<S11>:1:33' */
  /* '<S11>:1:38' */
  /* '<S11>:1:43' */
  if ((real32_T)fabs(s[0]) < sistema_P.limit[0]) {
    y_idx_0 = s[0] / sistema_P.limit[0];
  } else if (s[0] < 0.0F) {
    y_idx_0 = -1.0;
  } else if (s[0] > 0.0F) {
    y_idx_0 = 1.0;
  } else if (s[0] == 0.0F) {
    y_idx_0 = 0.0;
  } else {
    y_idx_0 = s[0];
  }

  if ((real32_T)fabs(s[1]) < sistema_P.limit[1]) {
    y_idx_1 = s[1] / sistema_P.limit[1];
  } else if (s[1] < 0.0F) {
    y_idx_1 = -1.0;
  } else if (s[1] > 0.0F) {
    y_idx_1 = 1.0;
  } else if (s[1] == 0.0F) {
    y_idx_1 = 0.0;
  } else {
    y_idx_1 = s[1];
  }

  if ((real32_T)fabs(s[2]) < sistema_P.limit[2]) {
    y_idx_2 = s[2] / sistema_P.limit[2];
  } else if (s[2] < 0.0F) {
    y_idx_2 = -1.0;
  } else if (s[2] > 0.0F) {
    y_idx_2 = 1.0;
  } else if (s[2] == 0.0F) {
    y_idx_2 = 0.0;
  } else {
    y_idx_2 = s[2];
  }

  if ((real32_T)fabs(s[3]) < sistema_P.limit[3]) {
    y_idx_3 = s[3] / sistema_P.limit[3];
  } else if (s[3] < 0.0F) {
    y_idx_3 = -1.0;
  } else if (s[3] > 0.0F) {
    y_idx_3 = 1.0;
  } else if (s[3] == 0.0F) {
    y_idx_3 = 0.0;
  } else {
    y_idx_3 = s[3];
  }

  tmp[0] = 2.5F;
  tmp[4] = 0.0F;
  tmp[8] = 0.0F;
  tmp[12] = 0.0F;
  tmp[1] = 0.0F;
  tmp[5] = 6.236F;
  tmp[9] = 0.0F;
  tmp[13] = 0.0F;
  tmp[2] = 0.0F;
  tmp[6] = 0.0F;
  tmp[10] = 6.236F;
  tmp[14] = 0.0F;
  tmp[3] = 0.0F;
  tmp[7] = 0.0F;
  tmp[11] = 0.0F;
  tmp[15] = 0.4927F;
  for (i = 0; i < 4; i++) {
    f_0[i] = (real32_T)-f[i] - (((lambdas[i + 4] *
      rtb_TmpSignalConversionAtSFun_f[1] + lambdas[i] * -Vy_XPlane) + lambdas[i
      + 8] * rtb_TmpSignalConversionAtSFun_f[2]) + lambdas[i + 12] *
      rtb_TmpSignalConversionAtSFun_f[3]);
  }

  for (i = 0; i < 4; i++) {
    s[i] = 0.0F;
    s[i] += tmp[i] * (real32_T)y_idx_0;
    s[i] += tmp[i + 4] * (real32_T)y_idx_1;
    s[i] += tmp[i + 8] * (real32_T)y_idx_2;
    s[i] += tmp[i + 12] * (real32_T)y_idx_3;
  }

  tmp_0[0] = -sistema_P.m / ((real32_T)cos(rtb_phi) * (real32_T)cos(rtb_theta));
  tmp_0[4] = 0.0F;
  tmp_0[8] = 0.0F;
  tmp_0[12] = 0.0F;
  tmp_0[1] = 0.0F;
  tmp_0[5] = sistema_P.J[0];
  tmp_0[9] = 0.0F;
  tmp_0[13] = -sistema_P.J[0] * (real32_T)sin(rtb_theta);
  tmp_0[2] = 0.0F;
  tmp_0[6] = 0.0F;
  tmp_0[10] = sistema_P.J[1] * (real32_T)cos(rtb_phi);
  tmp_0[14] = sistema_P.J[1] * (real32_T)cos(rtb_theta) * (real32_T)sin(rtb_phi);
  tmp_0[3] = 0.0F;
  tmp_0[7] = 0.0F;
  tmp_0[11] = -(sistema_P.J[2] * (real32_T)sin(rtb_phi));
  tmp_0[15] = sistema_P.J[2] * (real32_T)cos(rtb_phi) * (real32_T)cos(rtb_theta);
  s_idx_1 = f_0[0] - s[0];
  u_phi = f_0[1] - s[1];
  s_idx_0 = f_0[2] - s[2];
  arg_phi = f_0[3] - s[3];
  for (i = 0; i < 4; i++) {
    s[i] = 0.0F;
    s[i] += tmp_0[i] * s_idx_1;
    s[i] += tmp_0[i + 4] * u_phi;
    s[i] += tmp_0[i + 8] * s_idx_0;
    s[i] += tmp_0[i + 12] * arg_phi;
  }

  /* MATLAB Function: '<S7>/commands_conv' incorporates:
   *  Constant: '<S7>/Constant1'
   *  Constant: '<S7>/Constant2'
   *  Constant: '<S7>/Constant4'
   *  MATLAB Function: '<S8>/sliding_mode'
   */
  /* '<S11>:1:46' */
  /* '<S11>:1:47' */
  /* '<S11>:1:48' */
  /* '<S11>:1:49' */
  /* MATLAB Function 'sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Conversao dos comandos/commands_conv': '<S14>:1' */
  /* '<S14>:1:4' */
  s_idx_1 = s[0] / (4.0F * sistema_P.ct);

  /* '<S14>:1:5' */
  u_phi = s[1] / (2.0F * sistema_P.d * sistema_P.ct);

  /* '<S14>:1:6' */
  arg_phi = s[2] / (2.0F * sistema_P.d * sistema_P.ct);

  /* '<S14>:1:7' */
  s_idx_0 = s[3] / (4.0F * sistema_P.cq);

  /* '<S14>:1:9' */
  w1d_sq = (s_idx_1 + arg_phi) + s_idx_0;

  /* '<S14>:1:10' */
  rtb_psi = (s_idx_1 - u_phi) - s_idx_0;

  /* '<S14>:1:11' */
  rtb_theta = (s_idx_1 - arg_phi) + s_idx_0;

  /* '<S14>:1:12' */
  s_idx_1 = (s_idx_1 + u_phi) - s_idx_0;
  if (w1d_sq < 0.0F) {
    /* '<S14>:1:15' */
    /* '<S14>:1:16' */
    w1d_sq = 0.0F;
  }

  if (rtb_psi < 0.0F) {
    /* '<S14>:1:18' */
    /* '<S14>:1:19' */
    rtb_psi = 0.0F;
  }

  if (rtb_theta < 0.0F) {
    /* '<S14>:1:21' */
    /* '<S14>:1:22' */
    rtb_theta = 0.0F;
  }

  if (s_idx_1 < 0.0F) {
    /* '<S14>:1:24' */
    /* '<S14>:1:25' */
    s_idx_1 = 0.0F;
  }

  /* MATLAB Function: '<S2>/MATLAB Function' incorporates:
   *  MATLAB Function: '<S7>/commands_conv'
   */
  /* '<S14>:1:28' */
  /* '<S14>:1:29' */
  /* '<S14>:1:30' */
  /* '<S14>:1:31' */
  /* MATLAB Function 'sistema de controle quad xplane/Conversao Matlab2XPlane/MATLAB Function': '<S5>:1' */
  /*  this block is responsible for convert the angular velocity of each motor calculated on */
  /*  the control system and make it compatible with X-Plane. */
  /* '<S5>:1:7' */
  arg_phi = 16.4725361F * (real32_T)sqrt(w1d_sq);

  /*  Convertion from rad/s to rpm and multiplied by a constant to make it compatible with hover velocity of X-Plane. */
  /* t1= 0.00000000000075*w1_rpm*w1_rpm*w1_rpm; */
  /* '<S5>:1:10' */
  /*  Convertion from angular velocity of the motors to thrust command. This value is sent to X-Plane. */
  /* t1= 0.0000342*w1_rpm; */
  /* '<S5>:1:14' */
  u_phi = 16.4725361F * (real32_T)sqrt(rtb_psi);

  /* t2= 0.00000000000075*w2_rpm*w2_rpm*w2_rpm; */
  /* '<S5>:1:17' */
  /* t2= 0.0000342*w2_rpm; */
  /* '<S5>:1:21' */
  s_idx_0 = 16.4725361F * (real32_T)sqrt(rtb_theta);

  /* t3= 0.00000000000075*w3_rpm*w3_rpm*w3_rpm; */
  /* '<S5>:1:24' */
  /* t3= 0.0000342*w3_rpm; */
  /* '<S5>:1:28' */
  s_idx_1 = 16.4725361F * (real32_T)sqrt(s_idx_1);

  /* Outport: '<Root>/t1' incorporates:
   *  MATLAB Function: '<S2>/MATLAB Function'
   */
  /* t4= 0.00000000000075*w4_rpm*w4_rpm*w4_rpm; */
  /* '<S5>:1:31' */
  /* t4= 0.0000342*w4_rpm; */
  sistema_Y.t1 = 4.5E-9F * arg_phi * arg_phi;

  /* Outport: '<Root>/t2' incorporates:
   *  MATLAB Function: '<S2>/MATLAB Function'
   */
  sistema_Y.t2 = 4.5E-9F * u_phi * u_phi;

  /* Outport: '<Root>/t3' incorporates:
   *  MATLAB Function: '<S2>/MATLAB Function'
   */
  sistema_Y.t3 = 4.5E-9F * s_idx_0 * s_idx_0;

  /* Outport: '<Root>/t4' incorporates:
   *  MATLAB Function: '<S2>/MATLAB Function'
   */
  sistema_Y.t4 = 4.5E-9F * s_idx_1 * s_idx_1;

  /* MATLAB Function: '<S8>/sliding_mode' */
  Delay_DSTATE = s[0];

  /* Update for Delay: '<S8>/Delay' */
  sistema_DW.Delay_DSTATE = Delay_DSTATE;
}

/* Model initialize function */
void sistema_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(sistema_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&sistema_DW, 0,
                sizeof(DW_sistema_T));

  /* external inputs */
  (void) memset((void *)&sistema_U, 0,
                sizeof(ExtU_sistema_T));

  /* external outputs */
  (void) memset((void *)&sistema_Y, 0,
                sizeof(ExtY_sistema_T));
}

/* Model terminate function */
void sistema_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
