#include <stdint.h>
#include <stdio.h>


// ****FUNCTIONS - MILESTONE 1****

// ********************************************************
// name:      is_ascii()
// called by: main()
// passed:    string
// returns:   1 or 0
// calls:     none
// The is_ascii() function checks if the string is valid  *
// ASCII.                                                 *
// ********************************************************
int32_t is_ascii(char str[])
{
    int index = 0;
    int max = 127;
    
    while (str[index] != 0)
    {
     if (str[index] > max || str[index] < 0) 
     {
        return 0; 
     }
     index++;
    }
    return 1;
}

// ********************************************************
// name:      upper()
// called by: capitalize_ascii()
// passed:    char
// returns:   capitalized char of passed lower case char
// calls:     none
// ********************************************************
char upper(char c)
{
    if (c > 96 && c < 123) 
    {
        return c-32;
    }
    else
    {
        return c;
    }
}

// ********************************************************
// name:      capitalize_ascii()
// called by: main()
// passed:    string
// returns:   number of characters updated from lower case
//            to upper case
// calls:     upper()
// The capitalize_ascii function changes lower case chars *
// to upper case. Leaves other chars unchanged.           *
// ********************************************************
int32_t capitalize_ascii(char str[])
{
    int index = 0;
    int count = 0;
    
    while(str[index] != 0)
    {
        if (str[index] > 96 && str[index] < 123) 
            {
                str[index] = upper(str[index]);
                count += 1;
            }
        index += 1;
    }
    return count;
}

// ****FUNCTIONS - MILESTONE 2****

// ********************************************************
// name:      firstfour()
// called by: main()
// passed:    char
// returns:   char
// calls:     none
// Performs bitwise function (0b11110000) w/ chars passed *
// ********************************************************
char firstfour (char c)
{
    return (c & 0b11110000);
}


// ********************************************************
// name:      width_from_start_byte()
// called by: main()
// passed:    char
// returns:   how many bytes the sequence will
//            take (start byte + continuation bytes)
// calls:     firstfour();
// ********************************************************
int32_t width_from_start_byte(char start_byte)
{
    unsigned char first_four = firstfour(start_byte);
    int width = 0;
    int index = 0;
    
    if (first_four == 0b11110000) 
    {
        width = 4;
    }
    else if (first_four == 0b11100000)
    {
        width = 3;
    }
    else if (first_four == 0b11000000)
    {
        width = 2;
    }
    else if (start_byte <= 0b11111111 && start_byte >= 00000000)
    {
        width = 1;
    }
    else
    {
        width = -1;
    }
    
    return width;
}

// ********************************************************
// name:      utf8_strlen()
// called by: main()
// passed:    char
// returns:   number of UTF-8 codepoints the char
//            represents
// calls:     
// ********************************************************
int32_t utf8_strlen(char str[])
{
    
}

int main()
{
    printf("Is 🔥 ASCII? %d\n", is_ascii("🔥"));
    printf("Is abcd ASCII? %d\n", is_ascii("abcd"));

    printf("Capitalized %c\n", upper('s'));
    
    int32_t ret = 0;
    char str[] = "ahgZYU@hI!tr";
    ret = capitalize_ascii(str);
    printf("Capitalized String: %s\nCharacters updated: %d\n", str, ret);
    
    char s[] = "Héy"; // same as { 'H', 0xC3, 0xA9, 'y', 0 },   é is start byte + 1 cont. byte
    printf("Width: %d bytes\n", width_from_start_byte(s[1])); // start byte 0xC3 indicates 2-byte sequence
    printf("Width: %d bytes\n", width_from_start_byte(s[2])); 
    printf("Width: %d bytes\n", width_from_start_byte(s[0])); 
    return 0;
}