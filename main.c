#include <stdint.h>
#include <stdio.h>


// ****FUNCTIONS - MILESTONE 1****

// ********************************************************
// name:      is_ascii(char str[])
// called by: main()
// passed:    string
// returns:   int32_t, 1 or 0
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
// name:      upper(char c)
// called by: capitalize_ascii()
// passed:    char
// returns:   char, capitalized char of passed lower case char
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
// name:      capitalize_ascii(char str[])
// called by: main()
// passed:    string
// returns:   int32_tnumber of characters updated from 
//            lower case to upper case
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
// name:      firstfour (char c)
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
// name:      width_from_start_byte(char start_byte)
// called by: main()
// passed:    char
// returns:   int32_t, how many bytes the sequence will
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
    else if (start_byte <= 0b11111111 && start_byte >= 0b00000000)
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
// name:      utf8_strlen(char str[])
// called by: main()
// passed:    char
// returns:  int_32t, number of UTF-8 codepoints the char
//           represents
// calls:     width_from_start_byte()
// ********************************************************
int32_t utf8_strlen(char str[])
{
    int index = 0;
    int count = 0;

    while(str[index] != 0)
    {
        if(str[index] <= 0b11111111 && str[index] >= 0b00000000)
        {
            count += 1;
        }
        else if (width_from_start_byte(str[index]) > 1)
        {
            count += 1;
            index += (width_from_start_byte(str[index])-1);
        }
        else 
        {
            return -1;
        }
        index += 1;
    }
    return count;
}

// ********************************************************
// name:      codepoint_index_to_byte_index(char str[], int32_t cpi)
// called by: main()
// passed:    char, int_32t
// returns:   int32_t, byte index in the string where the 
//            Unicode character at the given codepoint index 
//            starts
// calls:     width_from_start_byte()
// ********************************************************
int32_t codepoint_index_to_byte_index(char str[], int32_t cpi)
{

    int byte_index = 0;
    int codepoint_index = 0;
    int index = 0;

    if (cpi < 0)
    {
        return -1;
    }

    while (str[index] != 0)
    {
        int width = width_from_start_byte(str[index]);
        if (width == 0)
        {
            return -1;
        }
        if (codepoint_index == cpi)
        {
            return byte_index;
        }
        byte_index += width;
        codepoint_index++;
        index += width;
    }
    return -1;
}

// ********************************************************
// name:      void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[])
// called by: main()
// passed:    char, int32_t, int32_t, char
// returns:   none
// calls:     codepoint_index_to_byte_index(), 
//            width_from_start_byte
// ********************************************************
void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[])
{

    
    int start_byte_index = codepoint_index_to_byte_index(str, cpi_start);

    int end_char_start_index= codepoint_index_to_byte_index(str, cpi_end-1);

    int width_last_char = width_from_start_byte(str[end_char_start_index]);

    int end_byte_index = end_char_start_index + width_last_char;

    if (cpi_start > cpi_end || cpi_start < 0 || cpi_end < 0)
    {
       return;
    }
    else
    {
        int index = 0;
        for (int i = start_byte_index; i < end_byte_index ; i++)
        {
           result[index] = str[i];
           index++;
        }
        result[index] = '\0';
    }
}

// ****FUNCTIONS - MILESTONE 3****

// ********************************************************
// name:      int32_t code_point2(char c1, char c2)
// called by: main()
// passed:    char, char
// returns:   int32_t
// calls:     none
// ********************************************************
int32_t code_point2(char c1, char c2)
{
    return (c1 & 0b00011111) * 64 + (c2 * 0b00111111);
}

// ********************************************************
// name:      int32_t code_point3(char c1, char c2, char c3)
// called by: main()
// passed:    char, char, char
// returns:   int32_t
// calls:     none
// ********************************************************
int32_t code_point3(char c1, char c2, char c3)
{
    return (c1 & 0b00001111) * 4096 + (c2 & 0b00111111) * 64 + (c3 & 0b00111111);
}

// name:      int32_t code_point4(char c1, char c2, char c3, char c4)
// called by: main()
// passed:    char, char, char, char
// returns:   int32_t
// calls:     none
// ********************************************************
int32_t code_point4(char c1, char c2, char c3, char c4)
{
    return (c1 & 0b00000111) * 262144 + (c2 & 0b00111111) * 4096 + (c3 & 0b00111111) * 64 + (c4 & 0b00111111);
}

// ********************************************************
// name:      int32_t codepoint_at(char str[], int32_t cpi)
// called by: main()
// passed:    char, int32_t
// returns:   int32_t
// calls:     codepoint_index_to_byte_index(),
//            width_from_start_byte(), code_point4(),
//            code_point3(), code_point2()
// ********************************************************
int32_t codepoint_at(char str[], int32_t cpi)
{
    if (cpi < 0 || cpi > utf8_strlen(str)-1)
    {
        return -1;
    }

    int index = 0;
    int codepoint_value = 0;
    int start_byte_index = codepoint_index_to_byte_index(str, cpi);
    int width_of_codepoint = width_from_start_byte(str[start_byte_index]);

    unsigned char cp_array[width_of_codepoint];

    for (int i = start_byte_index; index < start_byte_index + width_of_codepoint; i++)
    {
        cp_array[index] = str[i];
        index++;
    }

    if (width_of_codepoint == 4)
    {
        codepoint_value = code_point4(cp_array[0], 
        cp_array[1], cp_array[2], cp_array[3]);
        return codepoint_value;
    }
    else if (width_of_codepoint == 3)
    {
        codepoint_value = code_point3(cp_array[0], 
        cp_array[1], cp_array[2]);
        return codepoint_value;
    }
     else if (width_of_codepoint == 2)
    {
        codepoint_value = code_point2(cp_array[0], 
        cp_array[1]);
        return codepoint_value;
    }
    else if (width_of_codepoint == 1)
    {
        unsigned char value = str[start_byte_index];
        return value;
    }
    else
    {
        return -1;
    }
}

// ********************************************************
// name:      char is_animal_emoji_at(char str[], int32_t cpi)
// called by: main()
// passed:    char, int32_t
// returns:   char
// calls:     codepoint_index_to_byte_index(),
//            width_from_start_byte(), code_point4(),
//            code_point3(), code_point2()
// ********************************************************
char is_animal_emoji_at(char str[], int32_t cpi)
{
    int index = 0;
    
}

int main()
{

    return 0;
}