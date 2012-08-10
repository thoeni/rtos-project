//#ifndef _LIBBBQUE_H_
#define _LIBBBQUE_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int get_core_availability();
extern int send_message_to_bbqued(char*, int*);
extern int send_message_to_app(char*);

#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
//#endif /* End of the _LIBBBQUE_H_ block */
