#ifndef FINGER_MAIN_FUNCTIONS_H
#define FINGER_MAIN_FUNCTIONS_H

//Defines
#define BUFF_SZ     512


//Funcitons
void clear_transmitter(void);
void fingerprint_main_init(void);
void match_function(void);
void matchprints_mainloop(void);
void templates_mainloop(void);
void enroll_mainloop(void);
void empty_database(void);
void enroll_finger(int16_t fid);
void match_prints(int16_t fid, int16_t otherfid);

uint8_t get_free_id(int16_t * fid);
uint16_t read_template(uint16_t fid, uint8_t * buffer, uint16_t buff_sz);
uint16_t usart_start(void);
uint16_t usart_okuma(uint8_t * bytes, uint16_t len);
void usart_yazma(uint8_t * bytes, uint16_t len);

#endif