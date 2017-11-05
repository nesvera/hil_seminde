/*
 * File: sistema.h
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

#ifndef RTW_HEADER_sistema_h_
#define RTW_HEADER_sistema_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef sistema_COMMON_INCLUDES_
# define sistema_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* sistema_COMMON_INCLUDES_ */

#include "sistema_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T Delay_DSTATE;               /* '<S8>/Delay' */
} DW_sistema_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real32_T X_XPlane;                   /* '<Root>/X_XPlane' */
  real32_T Y_XPlane;                   /* '<Root>/Y_XPlane' */
  real32_T Z_XPlane;                   /* '<Root>/Z_XPlane' */
  real32_T Vx_XPlane;                  /* '<Root>/Vx_XPlane' */
  real32_T Vy_XPlane;                  /* '<Root>/Vy_XPlane' */
  real32_T Vz_XPlane;                  /* '<Root>/Vz_XPlane' */
  real32_T q_XPlane;                   /* '<Root>/q_XPlane' */
  real32_T p_XPlane;                   /* '<Root>/p_XPlane' */
  real32_T r_XPlane;                   /* '<Root>/r_XPlane' */
  real32_T pitch_XPlane;               /* '<Root>/pitch_XPlane' */
  real32_T roll_XPlane;                /* '<Root>/roll_XPlane' */
  real32_T heading_XPlane;             /* '<Root>/heading_XPlane' */
  real32_T referencias[4];             /* '<Root>/referencias' */
} ExtU_sistema_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real32_T t1;                         /* '<Root>/t1' */
  real32_T t2;                         /* '<Root>/t2' */
  real32_T t3;                         /* '<Root>/t3' */
  real32_T t4;                         /* '<Root>/t4' */
} ExtY_sistema_T;

/* Parameters (auto storage) */
struct P_sistema_T_ {
  real32_T J[4];                       /* Variable: J
                                        * Referenced by: '<S8>/Constant1'
                                        */
  real32_T cq;                         /* Variable: cq
                                        * Referenced by: '<S7>/Constant2'
                                        */
  real32_T ct;                         /* Variable: ct
                                        * Referenced by: '<S7>/Constant1'
                                        */
  real32_T d;                          /* Variable: d
                                        * Referenced by: '<S7>/Constant4'
                                        */
  real32_T g;                          /* Variable: g
                                        * Referenced by: '<S8>/Constant'
                                        */
  real32_T limit[4];                   /* Variable: limit
                                        * Referenced by: '<S8>/Constant5'
                                        */
  real32_T limit_pos[2];               /* Variable: limit_pos
                                        * Referenced by: '<S9>/Constant3'
                                        */
  real32_T m;                          /* Variable: m
                                        * Referenced by:
                                        *   '<S8>/Constant2'
                                        *   '<S9>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_sistema_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern P_sistema_T sistema_P;

/* Block states (auto storage) */
extern DW_sistema_T sistema_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_sistema_T sistema_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_sistema_T sistema_Y;

/* Model entry point functions */
extern void sistema_initialize(void);
extern void sistema_step(void);
extern void sistema_terminate(void);

/* Real-time Model object */
extern RT_MODEL_sistema_T *const sistema_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('SITL_gerador_codigo/sistema de controle quad xplane')    - opens subsystem SITL_gerador_codigo/sistema de controle quad xplane
 * hilite_system('SITL_gerador_codigo/sistema de controle quad xplane/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SITL_gerador_codigo'
 * '<S1>'   : 'SITL_gerador_codigo/sistema de controle quad xplane'
 * '<S2>'   : 'SITL_gerador_codigo/sistema de controle quad xplane/Conversao Matlab2XPlane'
 * '<S3>'   : 'SITL_gerador_codigo/sistema de controle quad xplane/Sistema de Controle do Quadrirotor'
 * '<S4>'   : 'SITL_gerador_codigo/sistema de controle quad xplane/conversao Plane2Matlab'
 * '<S5>'   : 'SITL_gerador_codigo/sistema de controle quad xplane/Conversao Matlab2XPlane/MATLAB Function'
 * '<S6>'   : 'SITL_gerador_codigo/sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Controle'
 * '<S7>'   : 'SITL_gerador_codigo/sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Conversao dos comandos'
 * '<S8>'   : 'SITL_gerador_codigo/sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Controle/Controlador sliding mode'
 * '<S9>'   : 'SITL_gerador_codigo/sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Controle/Controlador sliding mode/Controle de Translacao'
 * '<S10>'  : 'SITL_gerador_codigo/sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Controle/Controlador sliding mode/pqr_to_euler_dot'
 * '<S11>'  : 'SITL_gerador_codigo/sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Controle/Controlador sliding mode/sliding_mode'
 * '<S12>'  : 'SITL_gerador_codigo/sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Controle/Controlador sliding mode/Controle de Translacao/MATLAB Function'
 * '<S13>'  : 'SITL_gerador_codigo/sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Controle/Controlador sliding mode/Controle de Translacao/conversao ref. angulos'
 * '<S14>'  : 'SITL_gerador_codigo/sistema de controle quad xplane/Sistema de Controle do Quadrirotor/Conversao dos comandos/commands_conv'
 * '<S15>'  : 'SITL_gerador_codigo/sistema de controle quad xplane/conversao Plane2Matlab/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_sistema_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
