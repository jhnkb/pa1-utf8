The main trade off that I can think of is that UTF-8's are smaller in size than UTF-32s. For example, UTF-8s can be stored as one (ASCII) to four bytes (emojis) and not with a fixed 4 bytes. I would assume then that programs/systems that use UTF-8s would run faster than those that utilize UTF-32 because UTF-8 require less demand in memory or space. Though because of its fixed 4 bytes size, UTF-32 would be much simpler to work with than UTF-8.

I believe the leading 10 is useful because it is a mark to let users know if it is a single byte or multi byte character - specifically being a continuation byte. If the encoding didnt include this restriction on multi-byte code points, I believe that the computer would not be able to differentiate characters from  one another. Sometimes the leading 10 also "tells" the computer when a character ends.

For example, the binary equivalent of 😊 emoji is 

11110000:10011111:10011000:10001010 

But if there wasnt the leading 10, and replaced by the suggestion like below:

11110000:1110XXXX XXXXXXXX XXXXXXXX

The computer could get confused and would not know when to stop reading a multi byte character. This could lead some programs to display texts that would not make sense and readable to the intended audience. For example, like in an email. 

