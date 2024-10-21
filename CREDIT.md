https://www.reddit.com/r/C_Programming/comments/hze4iy/how_can_i_get_rid_of_the_n_in_fgets_in_a_string/

I used this reddit thread to figure out why fgets() adds '\n' at the end of the string. I also used the following line to help me get going with my code (how to get rid of it!!!),suggested by reddit user avelez6,  which I tailored to my code.

str[strlen(str) - 1] = '\0' 

I also used ChatGPT, with the prompt

"fgets is adding a \n"

in which I got the response that fgets() "reads the newline character (\n) into the buffer when you press Enter."

I also used ChatGPT, with the prompt

"why am i getting segmentation core dumped"

ChatGPT replied with the usual suspects like array out of bounds, stack overflow, bufferoverflow etc... but I still was not able to find the culprit. I then sent ChatGPT a bit of my code where I thought the error was coming from. ChatGPT suggested a tool called valgrind and I thought that was helpful because I was able to pinpoint where my issues were. I was actually close but ChatGPT/Valgrind helped me find the specific issue. 