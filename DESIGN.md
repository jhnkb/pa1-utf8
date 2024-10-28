New DESIGN question:

11100000 10000000 10100001

What code point does it encode in UTF-8, and what character is that?
The 3 byte sequence encodes to 33 in UTF-8. The character is "!".

What are the three other ways to encode that character?

00100001
11000000 10100001
11110000 10000000 10000000 10100001

Give an example of a character that has exactly three encodings (but not four, like the one in the previous example does)

The character ¼ , which is normally represented by 2 bytes. Cannot be represented as 1 byte (meaning it is not ASCII)

11000010 10111100
11100000 11000010 10111100
11110000 11000000 11000010 10111100

What are some problems with having these multiple encodings, especially for ASCII characters? A web search for “overlong UTF-8 encoding” may be useful here.

First, having multiple encodings (especially for ASCII characters) can lead to "funny" handling of data by some applications or programs, especially those that do not support UTF-8. For example, if someone creates a file in a UTF-8 supported program, and then subsequently attempts to share it to a person who only has the capability to view this file in ASCII, then they would probably would just see weird/gibberish characters instead. This also suggests compatibility issues in older programs if they are not updated to handle UTF-8. This would lead to confusion all around. Another example is that the unnecesary bytes may just lead to unnecesary need for data storage, thus users may need to invest more on hardware to store their data. Lastly, according to herolab.usd.de, a security analysis and pentesting service, overlong utf-8 encoding presents security risks. Attackers can exploit a program's mishandling of utf-8 encoding by "sending payloads encoded in a longer format" which allows them to bypass security checks. 
________

The main trade off that I can think of is that UTF-8's are smaller in size than UTF-32s. For example, UTF-8s can be stored as one (ASCII) to four bytes (emojis) and not with a fixed 4 bytes. I would assume then that programs/systems that use UTF-8s would run faster than those that utilize UTF-32 because UTF-8 require less demand in memory or space. Though because of its fixed 4 bytes size, UTF-32 would be much simpler to work with than UTF-8.

I believe the leading 10 is useful because it is a mark to let users know if it is a single byte or multi byte character - specifically being a continuation byte. If the encoding didnt include this restriction on multi-byte code points, I believe that the computer would not be able to differentiate characters from  one another. Sometimes the leading 10 also "tells" the computer when a character ends.

For example, the binary equivalent of 😊 emoji is 

11110000:10011111:10011000:10001010 

But if there wasnt the leading 10, and replaced by the suggestion like below:

11110000:1110XXXX XXXXXXXX XXXXXXXX

The computer could get confused and would not know when to stop reading a multi byte character. This could lead some programs to display texts that would not make sense and readable to the intended audience. For example, like in an email. 

