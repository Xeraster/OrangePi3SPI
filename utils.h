#ifndef UTILS_H
#define UTILS_H

// 4 bit numbers only, bits 7-4 will be ignored
string nibbleToBinary(unsigned char nibble)
{
    string result = "";
    // its not stupid if it works
    switch (nibble)
    {
    case 0:
        result = "0000";
        break;
    case 1:
        result = "0001";
        break;
    case 2:
        result = "0010";
        break;
    case 3:
        result = "0011";
        break;
    case 4:
        result = "0100";
        break;
    case 5:
        result = "0101";
        break;
    case 6:
        result = "0110";
        break;
    case 7:
        result = "0111";
        break;
    case 8:
        result = "1000";
        break;
    case 9:
        result = "1001";
        break;
    case 10:
        result = "1010";
        break;
    case 11:
        result = "1011";
        break;
    case 12:
        result = "1100";
        break;
    case 13:
        result = "1101";
        break;
    case 14:
        result = "1110";
        break;
    case 15:
        result = "1111";
        break;
    }

    return result;
}

// convert an 8 bit value to a binary string
string intToBinary(unsigned char input)
{
    string result = "";

    for (int i = 0; i < 8; i++)
    {
        result = nibbleToBinary((input & 0xF0) >> 4);
        result += nibbleToBinary((input & 0x0F));
    }

    return result;
}

char intToHexChar(int input)
{
    char val = 0;
    if (input < 10)
        val = input + 48;
    else if (input < 16)
        val = input + 55;
    else
        val = 78;

    return val;
}

/*prints a number as binary, useful for debugging gpio stuff
@param input the number to print
@param size_bits the size of the number in bits
@param doBinaryInstead if set to true, this makes it print in binary instead of
hex
*/
void printAsHex(unsigned long int input, unsigned int size_bits, bool doBinaryInstead = false)
{
    char *printableResult = (char *)malloc(sizeof(char) * 16);

    for (int i = 0; i < size_bits; i++)
    {
        // printableResult[62] = (input & 0x00000000000000F0)>>4;
        // printableResult[63] = input & 0x000000000000000F;
        printableResult[i] = (input & (0xF000000000000000 >> ((i * 4)))) >> (60 - (i * 4));
        // cout << "shift var =" << (i*4) << " and " << (56-(i*4)) << "for i = " <<
        // i << endl;
    }

    // if binary is set to false, print out the results in hex or whatever
    if (!doBinaryInstead)
    {
        for (int i = 0; i < 16; i++)
        {
            // printableResult[i] = intToHexChar(printableResult[i]);
            cout << intToHexChar(printableResult[i]) << " ";
        }
        cout << endl;
    }
    else
    {
        // print in binary instead of hex
        for (int i = 0; i < 16; i++)
        {
            cout << intToBinary(printableResult[i]);
        }
        cout << endl;
    }

    free(printableResult);
}

char binaryStringNibbleToHex(string nibble)
{
    // string soFar = "";
    // goddammit
    if (nibble == "0000")
    {
        return '0';
    }
    else if (nibble == "0001")
    {
        return '1';
    }
    else if (nibble == "0010")
    {
        return '2';
    }
    else if (nibble == "0011")
    {
        return '3';
    }
    else if (nibble == "0100")
    {
        return '4';
    }
    else if (nibble == "0101")
    {
        return '5';
    }
    else if (nibble == "0110")
    {
        return '6';
    }
    else if (nibble == "0111")
    {
        return '7';
    }
    else if (nibble == "1000")
    {
        return '8';
    }
    else if (nibble == "1001")
    {
        return '9';
    }
    else if (nibble == "1010")
    {
        return 'A';
    }
    else if (nibble == "1011")
    {
        return 'B';
    }
    else if (nibble == "1100")
    {
        return 'C';
    }
    else if (nibble == "1101")
    {
        return 'D';
    }
    else if (nibble == "1110")
    {
        return 'E';
    }
    else if (nibble == "1111")
    {
        return 'F';
    }
    else
    {
        return 'x';
    }
}

/*input a string containing nothing but zeros and ones and then it will output an equivalent hex string based on that
@param the string you want to convert to hex. for now, it only works if the string consists of exactly 8 characters that are either 1 or 0
@param endianness if the endianness is wrong, set this to true. if its still wrong, set this to false
*/
string binaryStringToHex(string input, bool endianness = false)
{
    string resultSoFar = "";

    for (int i = 0; i + 8 <= input.length(); i += 8)
    {
        resultSoFar += binaryStringNibbleToHex(input.substr(i, 4));
        resultSoFar += binaryStringNibbleToHex(input.substr(i + 4, 4));
    }

    //not tested at all
    if (endianness)
    {
        string reversedResult;
        for (int i = 0; i < 8; i++)
        {
            reversedResult += resultSoFar[7-i];
        }
    }

    return resultSoFar;
}

//input an array of 8 ints (presumably only containing 0s and 1s) and this will return the number of 1s
int parityBitFromArray(int *array)
{
    int numOfOnes = 0;
    for (int i = 0; i < 8; i++)
    {
        if (array[i] == 1)
        {
            numOfOnes++;
        }
    }

    return numOfOnes;
}

#endif