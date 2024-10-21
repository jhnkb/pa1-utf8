#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

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
// name:      width_from_start_byte(char start_byte)
// called by: main()
// passed:    char
// returns:   int32_t, how many bytes the sequence will
//            take (start byte + continuation bytes)
// calls:     firstfour();
// ********************************************************
int32_t width_from_start_byte(char start_byte)
{
    int width = 0;

    if ((start_byte & 0b11111000) == 0b11110000) 
        {
        width = 4;
        }
    else if ((start_byte & 0b11110000) == 0b11100000)
        {
        width = 3;
        }
    else if ((start_byte & 0b11100000) == 0b11000000)
        {
        width = 2;
        }
    else if ((start_byte & 0b10000000) == 0)
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
// ********************************************************
int32_t utf8_strlen(const char str[]) {
    int count = 0;  
    int i = 0;      

    while (str[i] != '\0') {  
        if ((str[i] & 0b10000000) == 0) 
        {
            count++;
            i += 1;
        } 
        else if ((str[i] & 0b11100000) == 0b11000000) 
        {
            count++;
            i += 2;
        } 
        else if ((str[i] & 0b11110000) == 0b11100000) 
        {
            count++;
            i += 3;  
        } else if ((str[i] & 0b11111000) == 0b11110000) {
            count++;
            i += 4;
        } else {
            count++;
            i++;
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
        unsigned char test = (unsigned char)str[index];
        int width = width_from_start_byte(test);
        if (width < 1)
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
    int number_of_codepoints = utf8_strlen(str);

    if (cpi_start < 0 || cpi_end <= cpi_start || cpi_start >= number_of_codepoints || 
    cpi_end > number_of_codepoints) 
    {
        strcpy(result, str);
    }

    int start_byte_index = codepoint_index_to_byte_index(str, cpi_start);
    int end_byte_index = codepoint_index_to_byte_index(str, cpi_end);

    if (start_byte_index < 0 || end_byte_index < 0) {
        strcpy(result, str);
        return;
    }

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
   return ((c1 & 0b00011111) << 6) + (c2 & 0b00111111);
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
    return ((c1 & 0b00001111) << 12) + ((c2 & 0b00111111) << 6) + (c3 & 0b00111111);
}

// name:      int32_t code_point4(char c1, char c2, char c3, char c4)
// called by: main()
// passed:    char, char, char, char
// returns:   int32_t
// calls:     none
// ********************************************************
int32_t code_point4(char c1, char c2, char c3, char c4)
{
    return ((c1 & 0b00000111) << 18) + ((c2 & 0b00111111) << 12) + ((c3 & 0b00111111) << 6) + (c4 & 0b00111111);
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
unsigned int codepoint_at(char str[], int32_t cpi)
{
    if (cpi < 0 || cpi >= utf8_strlen(str))
        {
            return -1;
        }

    int index = 0;        
    int codepoint_index = 0; 

    while (str[index] != '\0') 
    {
        int width = width_from_start_byte(str[index]); 

        if (width <= 0) 
        {
            return -1; 
        }

        if (codepoint_index == cpi) 
        {
            if (width == 1) 
            {
                return str[index]; 
            } 
            else if (width == 2) 
            {
                return code_point2(str[index], str[index+1]);
            } 
            else if (width == 3) 
            {
                return code_point3(str[index], str[index+1], str[index+2]);
            } 
            else if (width == 4) 
            {
                return code_point4(str[index], str[index+1], str[index+2], str[index+3]);
            }
        }

        index += width;        
        codepoint_index++;     
    }

    return -1; 
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
int32_t is_animal_emoji_at(char str[], int32_t cpi)
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

void next_utf8_char(char str[], int32_t cpi, char result[])
{
    int width = width_from_start_byte(str[cpi]);

    if (width == 1)
        {
            result[0] = str[cpi] + 1;
            result[1] = '\0';
            return;
        }
    else if (width == 2)
        {
            result[0] = str[cpi];
            result[1] = str[cpi + 1] + 1;
            result[2] = '\0';
            return;
        }
    else if (width == 3)
        {
            result[0] = str[cpi];
            result[1] = str[cpi + 1];
            result[2] = str[cpi + 2] + 1;
            result[3] = '\0';
            return;
        }
    else if (width == 4)
        {
            result[0] = str[cpi];
            result[1] = str[cpi + 1];
            result[2] = str[cpi + 2];
            result[3] = str[cpi + 3] + 1;
            result[4] = '\0';
            return;
        }
}

int main()
{   

    unsigned char buffer[1000];
    unsigned char buffer_capped[1000];

    //ask user to enter a UTF-8 string
    printf("%s\n", "Enter a UTF-8 encoded string: ");
    fgets(buffer, 1000, stdin);

    //nullify the string
    buffer[strlen(buffer) - 1] = '\0';

    //**PRINTING IF VALID ASCII**/
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

    //**PRINTING CAPITALIZED VERSION**/
    printf("%s%s\n", "Uppercased ASCII: ", buffer_capped);

    //**PRINT THE LENGTH OF STRING IN BYTES**/
    int count_1 = 0;
    int index_5 = 0;
    while (buffer[index_5] != '\0')
    {
        if (buffer[index_5] <= 127)
        {
            count_1 ++;
            index_5 ++;
        }
        else if ((buffer[index_5] & 0b11100000) == 0b11000000)
        {
            count_1 += 2;
            index_5 += 2;
        }
        else if ((buffer[index_5] & 0b11110000) == 0b11100000)
        {
            count_1 += 3;
            index_5 += 3;
        }
        else if ((buffer[index_5] & 0b11111000) == 0b11110000)
        {
            count_1 += 4;
            index_5 += 4;
        }
        else 
        {
            index_5++;
        }
    }

    printf("%s%d\n", "Length in bytes: ", count_1); 

    /**PRINT THE NUMBER OF CODEPOINTS**/
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

    /**PRINT BYTES / CODE PT**/
    printf("%s", "Bytes per code point: ");
    for (int i = 0; i < count; i++)
    {
        printf("%d ", bytes_per_codepoint[i]);
    }
    printf("\n");

    /**PRINT SUBSTRING OF FIRST 6 CPs**/
    unsigned char substring[50];
    utf8_substring(buffer, 0, 6, substring);

    printf("Substring of the first 6 code points: \"%s\" \n", substring);


    /**PRINT CODEPOINTS AS DECIMALS**/
    int index_4 = 0;
    unsigned int code_points_decimal [100];
    int cpid_index = 0;

    printf("%s", "Code points as decimal numbers: ");
    
    while (buffer[index_4] != '\0') 
    {
        if ((buffer[index_4] & 0b10000000) == 0) 
        {
            code_points_decimal[cpid_index++] = buffer[index_4];
            index_4 += 1;
        } else if ((buffer[index_4] & 0b11100000) == 0b11000000) 
        {
            code_points_decimal[cpid_index++] = code_point2(buffer[index_4], buffer[index_4 + 1]);
            index_4 += 2;
        } else if ((buffer[index_4] & 0b11110000) == 0b11100000) 
        {
            
            code_points_decimal[cpid_index++] = code_point3(buffer[index_4], buffer[index_4 + 1], buffer[index_4 + 2]);
            index_4 += 3;
        } else if ((buffer[index_4] & 0b11111000) == 0b11110000) 
        {
            
            code_points_decimal[cpid_index++] = code_point4(buffer[index_4], buffer[index_4 + 1], buffer[index_4 + 2], buffer[index_4 + 3]);
            index_4 += 4;
        } else 
        {
            index_4++;
        }
    }

    for (int y = 0; y < cpid_index; y++) 
    {
        printf("%d ", code_points_decimal[y]);
    }
    printf("\n");

    /**PRINT CODEPOINTS AS DECIMALS**/
    unsigned char animal_emojis [1000];
    int animal_index = 0;
    int codepoint = 0;
    int index_6 = 0;

    printf("%s", "Animal emojis: ");
    
    while (buffer[index_6] != '\0')
    {
        if(is_animal_emoji_at(buffer, codepoint))
        {
                for (int i = 0; i < 4; i++)
                    {
                        animal_emojis[animal_index] = buffer[index_6 + i];
                        animal_index++;
                    }  
            index_6 += 4;
            codepoint ++;        
        }

       else 
        {
            int width = width_from_start_byte(buffer[index_6]);

            if (width == 4)
            {
                index_6+= 4;
                codepoint++;
            }
            else if (width == 3)
            {
                index_6+= 3;
                codepoint++;
            }
            else if (width == 2)
            {
                index_6+= 2;
                codepoint++;
            }
            else if (width == 1)
            {
                index_6++;
                codepoint++;
            }

        }

    }

    animal_emojis[animal_index] = '\0';
    
    int u = 0;

    while(animal_emojis[u] != 0)
    {
        printf("%c", animal_emojis[u]);
        u+=1;
    }

    printf("\n");

    /**PRINT NEXT CHARACTER OF CODEPOINT AT INDEX 3**/
    
    char next_char[10];
    next_utf8_char(buffer, 3, next_char);
    printf("Next Character of Codepoint at Index 3: %s\n", next_char);


    

return 0;

}



