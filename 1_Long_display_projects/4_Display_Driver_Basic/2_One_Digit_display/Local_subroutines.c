



void Char_to_PC_B(char);
void Int_to_PC_B(long);
void String_to_PC_B(char*);
void newline_B(void);


#define zero "abcdef"                   //chars a,b,c,d,e and f are stored in an array named "zero"
#define one "bc"                        //chars b and c are stored in an array named "one"
#define two "abdeg"                     //Note: the compiler terminates each string in zero
#define three "abcdg"
#define four "bcfg"
#define five "acdfg"
#define six "gcdef"
#define seven "bca"
#define eight "abcdefg"
#define nine "gabcf"



#define print_memory_contents \
String_to_PC_B(message_1);\
while(1){if (!(*(zero + letter_counter))){Char_to_PC_B('0');string_counter += 1;\
if(string_counter == 10)break;\
}else Char_to_PC_B(*(zero + letter_counter));\
letter_counter += 1;}\
\
String_to_PC_B(message_2);\
for(int m = 0; m < 10; m++)String_memory_dump(digit++);\
\
Int_to_PC_B((int)message_1);\
newline_B();\
Int_to_PC_B((int)message_2);\
newline_B();





void String_memory_dump(char num){
Char_to_PC_B(num); Char_to_PC_B('\t');
switch(num){
case '0': Int_to_PC_B((int)zero);break;
case '1': Int_to_PC_B((int)one);break;
case '2': Int_to_PC_B((int)two);break;
case '3': Int_to_PC_B((int)three);break;
case '4': Int_to_PC_B((int)four);break;
case '5': Int_to_PC_B((int)five);break;
case '6': Int_to_PC_B((int)six);break;
case '7': Int_to_PC_B((int)seven);break;
case '8': Int_to_PC_B((int)eight);break;
case '9': Int_to_PC_B((int)nine);break;}
Char_to_PC_B('\t');
switch(num){
case '0': String_to_PC_B(zero);break;
case '1': String_to_PC_B(one);break;
case '2': String_to_PC_B(two);break;
case '3': String_to_PC_B(three);break;
case '4': String_to_PC_B(four);break;
case '5': String_to_PC_B(five);break;
case '6': String_to_PC_B(six);break;
case '7': String_to_PC_B(seven);break;
case '8': String_to_PC_B(eight);break;
case '9': String_to_PC_B(nine);break;}
newline_B();}



/********************************************************************************************/
