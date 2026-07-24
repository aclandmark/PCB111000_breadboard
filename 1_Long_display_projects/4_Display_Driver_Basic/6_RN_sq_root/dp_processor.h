

#define remove_dp_and_count_post_dp_digits \
for(int m = 0; m <= 7; m++){if (!(real_num_string[m] & 0x80));\
else {real_num_string[m] &= ~0x80; digits_pre_dp = m+1; break;}}\
if (digits_pre_dp)\
{for(int m = digits_pre_dp; m <= 7; m++)\
{if (real_num_string[m])digits_post_dp+=1; else break;}}



/************************************************************************************/
#define add_trailing_zero_for_even_number_of_post_dp_digits \
if(!(digits_post_dp%2)); else{\
real_num_string[digits_post_dp + digits_pre_dp] = '0';\
real_num_string[digits_post_dp + digits_pre_dp +1] = 0;\
digits_post_dp += 1;}



/************************************************************************************/
#define integrate_dp_for_integer_root \
/*String_to_PC_Basic("\r\n");*/\
/*String_to_PC_Basic(digits);*/\
for(int m = 0; m <=14; m++)\
{if (digits[m] == '.'){digits_pre_dp = m-1; break;}}\
digits[digits_pre_dp] |= 0x80;\
for(int m = digits_pre_dp + 1; m < 14; m++)digits[m] = digits[m+1];



/************************************************************************************/
#define real_num_greater_than_1 \
if (digits_pre_dp >= digits_post_dp)\
{digits[digits_pre_dp - digits_post_dp]  |= 0x80;\
digits[digits_pre_dp] &= ~0x80;}



/************************************************************************************/
#define real_num_less_than_1 \
if (digits_post_dp > digits_pre_dp){\
digits[digits_pre_dp] &= ~0x80;\
  for(int m = 0; m < (digits_post_dp - digits_pre_dp); m++){\
   for(int p = 0; p < 14; p++)\
   digits[14 - p] = digits[14 - p-1]; digits[0] = '0';}\
digits[digits_pre_dp] &= ~0x80;digits[0] |= 0x80;}



/************************************************************************************/
#define diagnostic_print_out \
String_to_PC_Basic("\r\n");Char_to_PC_Basic(digits_pre_dp + '0');\
Char_to_PC_Basic('\t'); Char_to_PC_Basic(digits_post_dp + '0');\
String_to_PC_Basic("\r\n"); String_to_PC_Basic("\tA");\
String_to_PC_Basic(real_num_string);String_to_PC_Basic("\r\n");



/*******************************************************************************************/
