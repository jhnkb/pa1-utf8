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

    while(str[index] != '\0')
    {
        if (str[index] >= 0b00000000 || str[index] <= 0b11111111)
        {
            count++;
            index++;
        }
        else if ((str[index] & 0b11000000) == 0b11000000)
        {
            count ++;
            index += 2;
        }
        else if ((str[index] & 0b11100000) == 0b11100000)
        {
            count ++;
            index += 3;
        }
        else if ((str[index] & 0b11110000) == 0b11110000)
        {
            count ++;
            index += 4;
        }
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
    int string_length = utf8_strlen(str);
    int number_of_codepoints = string_length; 

    if (cpi_start < 0 || cpi_end <= cpi_start || cpi_start >= number_of_codepoints || cpi_end > number_of_codepoints) 
    {
        int index = 0;
        while (str[index] != '\0') 
        {
            result[index] = str[index];
            index++;
        }
        result[index] = '\0';
        return;
    }

    int start_byte_index = codepoint_index_to_byte_index(str, cpi_start);
    int end_byte_index = codepoint_index_to_byte_index(str, cpi_end);

    int index = 0;
    for (int i = start_byte_index; i < end_byte_index; i++) {
        result[index++] = str[i];
    }
    result[index] = '\0';
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
   return ((c1 & 0b00011111) * 64) + (c2 & 0b00111111);
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
    if (cpi < 0 || cpi >= utf8_strlen(str))
    {
        return -1;
    }

    int start_byte_index = codepoint_index_to_byte_index(str, cpi);
    int width_of_codepoint = width_from_start_byte(str[start_byte_index]);

    unsigned char cp_array[4];

    for (int i = 0; i < width_of_codepoint; i++)
    {
        cp_array[i] = str[start_byte_index + i];
    }

    int32_t codepoint_value = 0;

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
    int codepoint_of_test = codepoint_at(str, cpi);
    
    if (cpi < 0 || cpi >= utf8_strlen(str))
    {
        return 0;
    }

    if ((codepoint_of_test >= 128000 && codepoint_of_test <= 128063) || (codepoint_of_test >= 129408 && codepoint_of_test <= 129454)) 
    {
        return 1;
    }
    return 0;
}

int main()
{   
    unsigned char buffer[1000];
    unsigned char buffer_capped[1000];

    printf("%s\n", "Enter a UTF-8 encoded string: ");
    fgets(buffer, 1000, stdin);

    int length = utf8_strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') 
    {
        buffer[length - 1] = '\0';
    }

    printf("%s", "Valid ASCII: ");
    if (is_ascii(buffer) == 1)
    {
        printf("%s\n", "true");
    }
    else if (is_ascii(buffer) ==  0)
    {
        printf("%s\n", "false");
    }
    
    int index = 0;
    while (buffer[index] != 0)
    {
        buffer_capped[index] = upper(buffer[index]);
        index += 1;
    }

    buffer_capped[index] = '\0';

    printf("%s%s\n", "Uppercased ASCII: ", buffer_capped);
    printf("%s%d\n", "Length in bytes: ", utf8_strlen(buffer)); 

    int count = 0;
    int index_1 = 0;
    while (buffer[index_1] != '\0')
    {
        if (buffer[index_1] <= 127)
        {
            count ++;
            index_1 ++;
        }
        else if ((buffer[index_1] & 0b11100000) == 0b11000000)
        {
            count ++;
            index_1 += 2;
        }
        else if ((buffer[index_1] & 0b11110000) == 0b11100000)
        {
            count ++;
            index_1 += 3;
        }
        else if ((buffer[index_1] & 0b11111000) == 0b11110000)
        {
            count ++;
            index_1 += 4;
        }
        else 
        {
            index_1++;
        }
    }

    printf("%s%d\n", "Number of code points: ", count);
    int index_2 = 0;
    unsigned int code_point_index = 0;
    unsigned int bytes_per_codepoint[100];
    while (buffer[index_2] != '\0')
    {
        if (buffer[index_2] <= 127)
        {
            bytes_per_codepoint[code_point_index] = 1;
            index_2 ++;
            code_point_index++;
        }
        else if ((buffer[index_2] & 0b11100000) == 0b11000000)
        {
            bytes_per_codepoint[code_point_index] = 2;
            index_2 += 2;
            code_point_index++;
        }
        else if ((buffer[index_2] & 0b11110000) == 0b11100000)
        {
            bytes_per_codepoint[code_point_index] = 3;
            index_2 += 3;
            code_point_index++;
        }
        else if ((buffer[index_2] & 0b11111000) == 0b11110000)
        {
            bytes_per_codepoint[code_point_index] = 4;
            index_2 += 4;
            code_point_index++;
        }
        else 
        {
            index_2++;
        }

    }

    printf("%s", "Bytes per code point: ");
    for (int i = 0; i < count; i++)
    {
        printf("%d ", bytes_per_codepoint[i]);
    }
    printf("\n");

    unsigned char substring[6];
    utf8_substring(buffer, 0, 6, substring);

    printf("%s", "Substring of the first 6 code points: \"");
    printf("%s", substring);
    printf("%s\n", "\"");


    int index_4 = 0;
    unsigned int code_points_decimal [1000];
    int cpid_index = 0;

    printf("%s", "Code points as decimal numbers: ");
    
    while (buffer[index_4] != '\0')
    {
        if (buffer[index_4] <= 127) 
        {
            code_points_decimal[cpid_index] = buffer[index_4];
            index_4++;
            cpid_index++;
        }
        else if ((buffer[index_4] & 0b11100000) == 0b11000000)
        {
            code_points_decimal[cpid_index] = code_point2(buffer[index_4], buffer[index_4+1]);
            index_4 += 2;
            cpid_index++;
        }
        else if ((buffer[index_4] & 0b11110000) == 0b11100000)
        {
            code_points_decimal[cpid_index] = code_point3(buffer[index_4], buffer[index_4+1], buffer[index_4+2]);
            index_4 += 3;
            cpid_index++;
        }
        else if ((buffer[index_4] & 0b11111000) == 0b11110000)
        {
            code_points_decimal[cpid_index] = code_point4(buffer[index_4], buffer[index_4+1], buffer[index_4+2], buffer[index_4+3]);
            index_4 += 4;
            cpid_index++;
        }
        else 
        {
            index_4++;
        }
        code_points_decimal[index_4] = '\0';
    }

    int y = 0;
    while (code_points_decimal[y] != '\0')
    {
    printf("%d ", code_points_decimal[y]);
    y++;
    }
    printf("\n");

    printf("%s", "Animal emojis: ");

    int index_3 = 0;
    char animal_emoji[100] = "";
    unsigned int animal_emoji_index = 0;

    while (buffer[index_3] != '\0')
    {
        if(is_animal_emoji_at(buffer, index_3))
        {
            int width_of_codepoint = width_from_start_byte(buffer[index_3]);
            if(animal_emoji_index + width_of_codepoint < sizeof(animal_emoji)-1)
            {
                for (int i = 0; i < width_of_codepoint; i++)
                    {
                        animal_emoji[animal_emoji_index] = buffer[index_3 + i];
                        animal_emoji_index++;
                    }  
                animal_emoji[animal_emoji_index] = '\0';
            } 
            index_3 += width_of_codepoint;
        }
       else 
        {
            index_3++;
        }

        }
    

printf("%s\n", animal_emoji); 

return 0;

}