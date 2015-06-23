#include "rdp.h"

/**
 * Description du réseau de Petri
**/

t_net *init_net(char* name) {
  t_place *p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9, *p10, *p11, *p12, *p13, *p14, *p15, *p16;
  t_transition *t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10, *t11, *t12, *t13, *t14, *t15, *t16, *t17, *t18, *t19;
  t_net* net = init(name);

  p0 = add_place(net, "0_1_5_103_post");
  p1 = add_place(net, "0_1_2_76_post");
  p2 = add_place(net, "0_0_3_29_post");
  p3 = add_place(net, "0_0_exit");
  p4 = add_place(net, "0_0_3_26_post");
  p5 = add_place(net, "0_1_6_110_post");
  p6 = add_place(net, "0_1_8_135_post");
  p7 = add_place(net, "0_1_8_134_post");
  p8 = add_place(net, "0_1_7_117_post");
  p9 = add_place(net, "0_0_3");
  p10 = add_place(net, "0_1_exit");
  p11 = add_place(net, "0_1_8");
  p12 = add_place(net, "0_0_entry");
  p13 = add_place(net, "0_1_8_127_post");
  p14 = add_place(net, "0_1_3_84_post");
  p15 = add_place(net, "0_1_4_96_post");
  p16 = add_place(net, "0_1_entry");
        set_flag(p3, FLAG_END);

  t0 = add_transition(net, "sys_0_1_3_84_perror", PERROR);
  t1 = add_transition(net, "proc_0_1_5_104_exit", EXIT);
  t2 = add_transition(net, "struct_0_0_3_3", STRUCT);
  t3 = add_transition(net, "proc_0_1_3_85_exit", EXIT);
  t4 = add_transition(net, "network_0_0_3_29_send", SEND);
  t5 = add_transition(net, "proc_0_1_7_118_exit", EXIT);
  t6 = add_transition(net, "network_0_0_3_26_recv", RECV);
  t7 = add_transition(net, "struct_0_0_entry_2", STRUCT);
  t8 = add_transition(net, "sys_0_1_9_142_perror", PERROR);
  t9 = add_transition(net, "sys_0_1_5_103_perror", PERROR);
  t10 = add_transition(net, "thread_0_1_10_150_pthread_detach", PTHREAD_DETACH);
  t11 = add_transition(net, "sys_0_1_8_134_printf", PRINTF);
  t12 = add_transition(net, "sys_0_1_7_117_perror", PERROR);
  t13 = add_transition(net, "network_0_1_6_110_listen", LISTEN);
  t14 = add_transition(net, "thread_0_1_8_135_pthread_create", PTHREAD_CREATE);
  t15 = add_transition(net, "network_0_1_8_127_accept", ACCEPT);
  t16 = add_transition(net, "network_0_1_4_96_bind", BIND);
  t17 = add_transition(net, "io_0_0_4_37_close", CLOSE);
  t18 = add_transition(net, "network_0_1_2_76_socket", SOCKET);
  t19 = add_transition(net, "struct_0_1_6_8", STRUCT);
  set_initial_place_marking(p16,ID_TOKEN);
  add_hash(net, p0, t1, p0);    /* 0_1_5_103_post -> proc_0_1_5_104_exit (p0)*/
  add_hash(net, p1, t0, p1);    /* 0_1_2_76_post -> sys_0_1_3_84_perror (p1)*/
  add_hash(net, p1, t16, p1);   /* 0_1_2_76_post -> network_0_1_4_96_bind (p1)*/
  add_hash(net, p2, t6, p9);    /* 0_0_3_29_post -> network_0_0_3_26_recv (p9)*/
  add_hash(net, p2, t17, p2);   /* 0_0_3_29_post -> io_0_0_4_37_close (p2)*/
  add_hash(net, p4, t4, p4);    /* 0_0_3_26_post -> network_0_0_3_29_send (p4)*/
  add_hash(net, p5, t15, p11);  /* 0_1_6_110_post -> network_0_1_8_127_accept (p11)*/
  add_hash(net, p5, t12, p5);   /* 0_1_6_110_post -> sys_0_1_7_117_perror (p5)*/
  add_hash(net, p6, t8, p6);    /* 0_1_8_135_post -> sys_0_1_9_142_perror (p6)*/
  add_hash(net, p6, t10, p6);   /* 0_1_8_135_post -> thread_0_1_10_150_pthread_detach (p6)*/
  add_hash(net, p7, t14, p7);   /* 0_1_8_134_post -> thread_0_1_8_135_pthread_create (p7)*/
  add_hash(net, p8, t5, p8);    /* 0_1_7_117_post -> proc_0_1_7_118_exit (p8)*/
  add_hash(net, p9, t6, p9);    /* 0_0_3 -> network_0_0_3_26_recv (p9)*/
  add_hash(net, p11, t15, p11); /* 0_1_8 -> network_0_1_8_127_accept (p11)*/
  add_hash(net, p12, t6, p9);   /* 0_0_entry -> network_0_0_3_26_recv (p9)*/
  add_hash(net, p13, t11, p13); /* 0_1_8_127_post -> sys_0_1_8_134_printf (p13)*/
  add_hash(net, p14, t3, p14);  /* 0_1_3_84_post -> proc_0_1_3_85_exit (p14)*/
  add_hash(net, p15, t13, p15); /* 0_1_4_96_post -> network_0_1_6_110_listen (p15)*/
  add_hash(net, p15, t9, p15);  /* 0_1_4_96_post -> sys_0_1_5_103_perror (p15)*/
  add_hash(net, p16, t18, p16); /* 0_1_entry -> network_0_1_2_76_socket (p16)*/
  /* Transision sys_0_1_3_84_perror / t0 */
  add_precond(t0, p1, 1);
  add_postcond(t0, p14, 1);
  /* Transision proc_0_1_5_104_exit / t1 */
  add_precond(t1, p0, 1);
  add_postcond(t1, p10, 1);
  /* Transision struct_0_0_3_3 / t2 */
  add_precond(t2, p2, 1);
  add_postcond(t2, p9, 1);
  /* Transision proc_0_1_3_85_exit / t3 */
  add_precond(t3, p14, 1);
  add_postcond(t3, p10, 1);
  /* Transision network_0_0_3_29_send / t4 */
  add_precond(t4, p4, 1);
  add_postcond(t4, p2, 1);
  /* Transision proc_0_1_7_118_exit / t5 */
  add_precond(t5, p8, 1);
  add_postcond(t5, p10, 1);
  /* Transision network_0_0_3_26_recv / t6 */
  add_precond(t6, p9, 1);
  add_postcond(t6, p4, 1);
  /* Transision struct_0_0_entry_2 / t7 */
  add_precond(t7, p12, 1);
  add_postcond(t7, p9, 1);
  /* Transision sys_0_1_9_142_perror / t8 */
  add_precond(t8, p6, 1);
  add_postcond(t8, p11, 1);
  /* Transision sys_0_1_5_103_perror / t9 */
  add_precond(t9, p15, 1);
  add_postcond(t9, p0, 1);
  /* Transision thread_0_1_10_150_pthread_detach / t10 */
  add_precond(t10, p6, 1);
  add_postcond(t10, p11, ID_TOKEN);
  /* Transision sys_0_1_8_134_printf / t11 */
  add_precond(t11, p13, 1);
  add_postcond(t11, p7, 1);
  /* Transision sys_0_1_7_117_perror / t12 */
  add_precond(t12, p5, 1);
  add_postcond(t12, p8, 1);
  /* Transision network_0_1_6_110_listen / t13 */
  add_precond(t13, p15, 1);
  add_postcond(t13, p5, 1);
  /* Transision thread_0_1_8_135_pthread_create / t14 */
  add_precond(t14, p7, 1);
  add_postcond(t14, p6, ID_TOKEN);
  add_postcond(t14, p12, NEWID_TOKEN);
  /* Transision network_0_1_8_127_accept / t15 */
  add_precond(t15, p11, 1);
  add_postcond(t15, p13, 1);
  /* Transision network_0_1_4_96_bind / t16 */
  add_precond(t16, p1, 1);
  add_postcond(t16, p15, 1);
  /* Transision io_0_0_4_37_close / t17 */
  add_precond(t17, p2, 1);
  add_postcond(t17, p3, 1);
  /* Transision network_0_1_2_76_socket / t18 */
  add_precond(t18, p16, 1);
  add_postcond(t18, p1, 1);
  /* Transision struct_0_1_6_8 / t19 */
  add_precond(t19, p5, 1);
  add_postcond(t19, p11, 1);
  return net;
}
